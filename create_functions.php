<?php
/*****************************************************************************
 * Copyright (c) 2008 Niko Sams <niko.sams@gmail.com>                        *
 *                                                                           *
 * Permission is hereby granted, free of charge, to any person obtaining     *
 * a copy of this software and associated documentation files (the           *
 * "Software"), to deal in the Software without restriction, including       *
 * without limitation the rights to use, copy, modify, merge, publish,       *
 * distribute, sublicense, and/or sell copies of the Software, and to        *
 * permit persons to whom the Software is furnished to do so, subject to     *
 * the following conditions:                                                 *
 *                                                                           *
 * The above copyright notice and this permission notice shall be            *
 * included in all copies or substantial portions of the Software.           *
 *                                                                           *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,           *
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF        *
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND                     *
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE    *
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION    *
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION     *
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.           *
 *****************************************************************************/

if (!isset($_SERVER['argv'][1])) {
    $msg = "Usage:\n".$_SERVER['argv'][0]." [path to phpdoc/en]\n";
    $msg .= "you may checkout from the php csv server using this command:\n";
    $msg .= "cvs -d :pserver:cvsread@cvs.php.net:/repository checkout phpdoc\n";
    file_put_contents('php://stderr', $msg);
    exit(-1);
}

$dirs = array("reference", "appendices");

$functions = array();
$constants = array();
$existingFunctions = array();
foreach ($dirs as $dir) {
    $dirIt = new RecursiveIteratorIterator( new RecursiveDirectoryIterator($_SERVER['argv'][1].'/'.$dir));
    foreach ($dirIt as $file) {
        if (substr($file->getFilename(), -4) != '.xml') continue;
        if (substr($file->getFilename(), 0, 9) == 'entities.') continue;
        $string = file_get_contents($file->getPathname());
        $string = preg_replace('#<!\\[CDATA\\[.*?\\]\\]>#s', '', $string);
        $string = preg_replace('#&[A-Za-z\\.0-9-_]+;#', '', $string);
        $removeSections = array();
        $removeSections[] = 'apd.installwin32';
        $removeSections[] = 'intl.intldateformatter-constants.calendartypes';
        foreach ($removeSections as $i) {
            $string = preg_replace('#'.preg_quote('<section xml:id="'.$i.'">').'.*?</section>#s', '', $string);
        }
        $xml = new SimpleXMLElement($string);
        if (isset($xml->variablelist)) {
            foreach ($xml->variablelist->varlistentry as $i=>$varlistentry) {
                if ($c = (string)$varlistentry->term->constant) {
                    if (!isset($constants[$c])) {
                        if (strpos($c, '=')) {
                            $c = substr($c, 0, strpos($c, '='));
                        }
                        $ctype = $varlistentry->term->type;
                        if (!$ctype) {
                            $ctype = $varlistentry->term->link;
                        }
                        $constants[$c] = (string)$ctype;
                    }
                }
            }
        }
        if (!isset($xml->refsect1)) continue;
        if (!$xml->refsect1->methodsynopsis->methodname) continue;
        $function = $xml->refsect1->methodsynopsis->methodname;
        if (strpos($function, '::')) {
            $class = substr($function, 0, strpos($function, '::'));
            $function = substr($function, strpos($function, '::')+2);
        } else if (strpos($function, '->')) {
            $class = substr($function, 0, strpos($function, '->'));
            $function = substr($function, strpos($function, '->')+2);
        } else {
            $class = 'global';
            if ($function == '__halt_compiler') continue;
            if ($function == 'exit') continue;
            if ($function == 'die') continue;
            if ($function == 'eval') continue;
            if ($function == 'echo') continue;
            if ($function == 'print') continue;
            if ($function == 'array') continue;
            if ($function == 'list') continue;
            if ($function == 'isset') continue;
            if ($function == 'unset') continue;
            if ($function == 'empty') continue;

            if (strpos($function, '-')) continue;
        }
        if ($function == 'isSet') continue; //todo: bug in lexer
        if ($function == 'clone') continue; //todo: bug in lexer
        if (substr($class, 0, 3) == 'DOM') $class = 'Dom'.substr($class, 3);
        $class = trim($class);
        if (in_array($class.'::'.$function, $existingFunctions)) continue;
        $existingFunctions[] = $class.'::'.$function;

        $params = array();
        foreach ($xml->refsect1->methodsynopsis->methodparam as $param) {
            $paramName = $param->parameter;
            if (trim($paramName) == '...') continue;
            if (!trim($paramName)) continue;
            $paramName = str_replace('/', '', $paramName);
            $paramName = str_replace('-', '', $paramName);
            $paramName = trim(trim(trim($paramName), '*'), '&');
            if (is_numeric(substr($paramName, 0, 1))) $paramName = '_'.$paramName;
            $p = '';
            //if ($param->type) $p .= $param->type.' ';
            $p .= '$'.$paramName;
            $params[] = $p;
        }
        $functions[$class][] = array(
            'name' => $function,
            'params' => $params
        );
    }
}

foreach (array_keys($constants) as $c) {
    if ($pos = strpos($c, '::')) {
        if (!isset($functions[substr($c, 0, $pos)])) {
            $functions[substr($c, 0, $pos)] = array();
        }
    }
}
function constTypeValue($ctype) {
    if ($ctype == 'integer' || $ctype == 'int') {
        return "0";
    } else if ($ctype == 'string') {
        return "''";
    } else if ($ctype == 'bool') {
        return "false";
    } else if ($ctype == 'float') {
        return "0.0";
    } else {
        die("unknown constType: $ctype");
    }
}
echo "<?php\n";
echo "// THIS FILE IS GENERATED\n";
echo "// WARNING! All changes made in this file will be lost!\n\n";
foreach ($functions as $class => $i) {
    if ($class != 'global') {
        echo "class $class {\n";
        foreach ($constants as $c=>$ctype) {
            if ($pos = strpos($c, '::')) {
                if (substr($c, 0, $pos) == $class) {
                    unset($constants[$c]);
                    $c = substr($c, $pos+2);
                    echo "    const $c = ".constTypeValue($ctype).";\n";
                }
            }
        }
    }

    foreach ($i as $f) {
        if ($class != 'global') echo '    ';
        echo "function ".$f['name'];
        echo "(";
        echo implode(', ', $f['params']);
        echo ") {}\n";
    }

    if ($class != 'global') echo "}\n";
}
foreach ($constants as $c=>$ctype) {
    echo "define('$c', ".constTypeValue($ctype).");\n";
}
