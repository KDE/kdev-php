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

if (!isset($_SERVER['argv'][1]) || !isset($_SERVER['argv'][2])) {
    $msg = "Usage:\n".$_SERVER['argv'][0]." [path to phpdoc] [path to php sources]\n";
    $msg .= "you may checkout from the php csv server using this command:\n";
    $msg .= "cvs -d :pserver:cvsread@cvs.php.net:/repository checkout phpdoc\n";
    $msg .= "cvs -d :pserver:cvsread@cvs.php.net:/repository checkout -r PHP_5_2 php5\n";
    file_put_contents('php://stderr', $msg);
    exit(-1);
}
if (!file_exists($_SERVER['argv'][1])) {
    file_put_contents('php://stderr', "phpdoc path not found");
    exit(-1);
}
if (!file_exists($_SERVER['argv'][2])) {
    file_put_contents('php://stderr', "php sources path not found");
    exit(-1);
}

//take ext/spl/spl.php as documentation for spl functions
//make the file valid php
$splContent = file_get_contents($_SERVER['argv'][2].'/ext/spl/spl.php');
$splContent = str_replace('mixed cmp_function', '$cmp_function', $splContent);
$splContent = str_replace('string class_name', '$class_name', $splContent);
$splContent = str_replace('string $', '$', $splContent);
$splContent = str_replace('{/**/};', '{}', $splContent);
$splContent = str_replace('{/**/}', '{}', $splContent);
$splContent = str_replace("\t", '    ', $splContent);
$splContent = str_replace("\r", '', $splContent);
$splContent = preg_replace("#(const [A-Z_]+\s*)(0x[0-9]+;)#", '\1= \2', $splContent);
$splContent = preg_replace("#/\\*\\* @(mainpage|defgroup|file).*?\\*/#s", '', $splContent);
$splContent = trim($splContent);

foreach (new DirectoryIterator($_SERVER['argv'][2].'/ext/spl/internal') as $file) {
    if (!$file->isFile()) continue;
    if (substr($file->getFilename(), -4) != '.inc') continue;
    $c = file_get_contents($file->getPathname());
    $c = str_replace("\t", '    ', $c);
    $c = str_replace("\r", '', $c);
    $c = preg_replace("#/\\*\\* @file.*?\\*/#s", '', $c);
    $c = preg_replace("#(function.*?){\n.*?    }#s", '{}', $c);
    $c = str_replace("rewind();\n    {", "rewind()\n    {", $c);
    $c = trim($c);
    $splContent .= $c;
}
$splContent = str_replace('<?php', '', $splContent);
$splContent = str_replace('?>', '', $splContent);
$spl = preg_replace("#/\\*.*?\\*/#s", '', $splContent);
preg_match_all("#^(class|interface)\s+(\S+)[^{]*{#sm", $spl, $m);
$skipClasses = $m[2];

$skipClasses[] = 'self';
$skipClasses[] = 'parent';
$skipClasses[] = 'exception'; //lowercase
$skipClasses[] = '__PHP_Incomplete_Class';
$skipClasses[] = 'php_user_filter';

$dirs = array("en/reference", "en/appendices", "en/language/predefined/variables");

$classes = array();
$constants = array();
$variables = array();
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
        $xml->registerXPathNamespace('db', 'http://docbook.org/ns/docbook');
        $xml->registerXPathNamespace('phpdoc', 'http://php.net/ns/phpdoc');
        if ($vars = $xml->xpath('//phpdoc:varentry//db:refnamediv')) {
            foreach ($vars as $var) {
                foreach ($var->refname as $i) {
                    $v = array();
                    $i = (string)$i;
                    if (substr($i, 0, 1) != '$') continue;
                    $v['deprecated'] = false;
                    if (substr($i, -13) == ' [deprecated]') {
                        $i = substr($i, 0, -13);
                        $v['deprecated'] = true;
                    }
                    $v['desc'] = $var->refpurpose;
                    $variables[$i] = $v;
                }
            }
        }
        if ($vars = $xml->xpath("//phpdoc:varentry[@xml:id='language.variables.superglobals']//db:member/db:varname")) {
            foreach ($vars as $var) {
                $variables[(string)$var]['superglobal'] = true;
            }
        }
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
        if ($list = $xml->xpath('//db:sect2[starts-with(@xml:id, "reserved.classes")]/db:variablelist/db:varlistentry')) {
            foreach ($list as $l) {
                if (!isset($classes[(string)$l->term->classname])) {
                    $classes[(string)$l->term->classname] = array('functions'=>array());
                }
                $classes[(string)$l->term->classname]['desc'] = trim(strip_tags($l->listitem->asXML()));
            }
        }
        $cEls = $xml->xpath('//db:classsynopsis/db:classsynopsisinfo');
        if ($cEls) {
            foreach ($cEls as $class) {
                $class->registerXPathNamespace('db', 'http://docbook.org/ns/docbook');
                $className = (string)$class->ooclass->classname;
                if (!$className) continue;
                if (!isset($classes[$className])) {
                    $classes[$className] = array('functions'=>array());
                }
                if ($extends = $class->xpath('//db:ooclass')) {
                    foreach ($extends as $c) {
                        if ($c->modifier == 'extends') {
                            $classes[$className]['extends'] = (string)$c->classname;
                        }
                    }
                }
                if ($interfaces = $class->xpath('//db:oointerface/db:interfacename')) {
                    foreach ($interfaces as $if) {
                        $classes[$className]['implements'][] = (string)$if;
                    }
                }
            }
        }
        if (!isset($xml->refsect1)) continue;
        if (isset($xml->refsect1->methodsynopsis)) {
            $methodsynopsis = $xml->refsect1->methodsynopsis;
            $function = (string)$methodsynopsis->methodname;
            $class = 'global';
        } else if (isset($xml->refsect1->classsynopsis) && isset($xml->refsect1->classsynopsis->methodsynopsis)) {
            $methodsynopsis = $xml->refsect1->classsynopsis->methodsynopsis;
            $class = (string)$xml->refsect1->classsynopsis->ooclass->classname;
            $function = (string)$methodsynopsis->methodname;
        } else {
            continue;
        }
        if (strpos($function, '::')) {
            $class = substr($function, 0, strpos($function, '::'));
            $function = substr($function, strpos($function, '::')+2);
        } else if (strpos($function, '->')) {
            $class = substr($function, 0, strpos($function, '->'));
            $function = substr($function, strpos($function, '->')+2);
        } else {
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
        }
        if (strpos($function, '-')) continue;
        if (strpos($class, '-')) continue;
        if ($function == 'isSet') continue; //todo: bug in lexer
        if ($function == 'clone') continue; //todo: bug in lexer
        if (substr($class, 0, 3) == 'DOM') $class = 'Dom'.substr($class, 3);
        $class = trim($class);
        if ($class == 'imagick') $class = 'Imagick';
        if (in_array($class.'::'.$function, $existingFunctions)) continue;
        $existingFunctions[] = $class.'::'.$function;

        $params = array();
        foreach ($methodsynopsis->methodparam as $param) {
            $paramName = $param->parameter;
            if (trim($paramName) == '...') continue;
            if (!trim($paramName)) continue;
            $paramName = str_replace('/', '', $paramName);
            $paramName = str_replace('-', '', $paramName);
            $paramName = trim(trim(trim($paramName), '*'), '&');
            if (is_numeric(substr($paramName, 0, 1))) $paramName = '_'.$paramName;
            $params[] = array(
                'name' => $paramName,
                'type' => (string)$param->type
            );
        }
        $desc = strip_tags($xml->refsect1->para->asXML());
        $desc = trim($desc);
        $desc = preg_replace('#  +#', ' ', $desc);
        $desc = preg_replace('#^ #m', '', $desc);
        if (!isset($classes[$class])) {
            $classes[$class] = array('functions'=>array());
        }
        $classes[$class]['functions'][] = array(
            'name' => $function,
            'params' => $params,
            'type' => (string)$methodsynopsis->type,
            'desc' => $desc
        );
    }
}

/*
 Here be dirty hacks! PHP's documentation isn't as good as could be wished for...
 */

// Clean the functions from imagick
foreach (array_keys($constants) as $c) {
    if ($pos = strpos($c, '::')) {
        $class = substr($c, 0, $pos);
        if ($class == 'imagick') $class = 'Imagick';
        if (!isset($classes[$class])) {
            $classes[$class] = array('functions'=>array());
        }
    }
}

// The dir function, which lacks parseable documentation...
$classes['global']['functions'][] = array(
    'name' => "dir",
    'params' => array(array('name' => "path", 'type' => "string")),
    'type' => "Directory",
    'desc' => "Return an instance of the Directory class"
);

/*
 Here ends the hackings...
 */

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


$fileHeader  = "<?php\n";
$fileHeader .= "// THIS FILE IS GENERATED\n";
$fileHeader .= "// WARNING! All changes made in this file will be lost!\n\n";

$declarationCount = 0;
$out = $fileHeader;

foreach ($variables as $name=>$var) {
    $declarationCount++;
    $out .= "/**\n";
    $out .= " * ";
    $out .= str_replace("\n", "\n * ", $var['desc']);
    $out .= "\n";
    if ($var['deprecated']) {
        $out .= " * @deprecated\n";
    }
    if (isset($var['superglobal']) && $var['superglobal']) {
        $out .= " * @superglobal\n";
    }
    $out .= " **/\n";
    $out .= "$name = array();\n\n";
}

$out .= $splContent;
foreach ($classes as $class => $i) {
    if (in_array($class, $skipClasses)) continue; //skip those as they are documented in spl.php
    if ($class != 'global') {
        if (isset($i['desc']) && $i['desc']) {
            $out .= "/**\n";
            $out .= " * ";
            $out .= str_replace("\n", "\n * ", $i['desc']);
            $out .= "\n";
            $out .= " **/\n";
        }
        $out .= "class $class";
        if (isset($i['extends'])) {
            $out .= " extends {$i['extends']}";
        }
        if (isset($i['implements'])) {
            $out .= " implements ".implode(", ", $i['implements']);
        }
        $out .= " {\n";
        $declarationCount++;
        foreach ($constants as $c=>$ctype) {
            if ($pos = strpos($c, '::')) {
                if (substr($c, 0, $pos) == $class) {
                    unset($constants[$c]);
                    $c = substr($c, $pos+2);
                    $out .= "    const $c = ".constTypeValue($ctype).";\n";
                    $declarationCount++;
                }
            }
        }
    }

    $indent = '';
    if ($class != 'global') $indent = '    ';
    foreach ($i['functions'] as $f) {
        $out .= "$indent/**\n";
        if ($f['desc']) {
            $out .= "$indent * ";
            $out .= str_replace("\n", "\n$indent * ", $f['desc']);
            $out .= "\n";
            $out .= "$indent *\n";
        }
        foreach ($f['params'] as $pi=>$param) {
            $out .= "$indent * @param $param[type]\n";
        }
        if ($f['type']) $out .= "$indent * @return $f[type]\n";
        $out .= "$indent **/\n";
        $out .= "{$indent}function ".$f['name'];
        $out .= "(";
        foreach ($f['params'] as $pi=>$param) {
            if ($pi > 0) $out .= ", ";
            $out .= '$'.$param['name'];
        }
        $out .= ") {}\n\n";
        $declarationCount++;
    }

    if ($class != 'global') $out .= "}\n";
}
foreach ($constants as $c=>$ctype) {
    if (strpos($c, '::')===false) {
        $out .= "define('$c', ".constTypeValue($ctype).");\n";
        $declarationCount++;
    }
}

file_put_contents("phpfunctions.php", $out);
echo "created phpfunctions.php...\n";

echo "wrote ".$declarationCount." declarations\n";
