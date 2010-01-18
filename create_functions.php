<?php
/*****************************************************************************
 * Copyright (c) 2008 Niko Sams <niko.sams@gmail.com>                        *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Library General Public License as       *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this program; if not, write to the                 *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.         *
 ***************************************************************************/


if (!isset($_SERVER['argv'][1])) {
    $msg = "Usage:\n".$_SERVER['argv'][0]." [path to phpdoc]\n";
    $msg .= "you may checkout from the php svn server using this command:\n";
    $msg .= "svn checkout http://svn.php.net/repository/phpdoc/en/trunk ./phpdoc-en\n";
    $msg .= "\nTo debug files/directories use this: ".$_SERVER['argv'][0]." --debug PATH ...\n";
    file_put_contents('php://stderr', $msg);
    exit(-1);
}

$skipClasses = array();

$skipClasses[] = 'self';
$skipClasses[] = 'parent';
$skipClasses[] = '__php_incomplete_class';
$skipClasses[] = 'php_user_filter';

///TODO: re-enable them once they have their do(), echo() or list() methods removed.
$skipClasses[] = 'gearmanclient';
$skipClasses[] = 'gearmanworker';
$skipClasses[] = 'gearmantask';
$skipClasses[] = 'rararchive';

$classes = array();
$constants = array();
$constants_comments = array();
$variables = array();
$existingFunctions = array();
$versions = array();

if ($_SERVER['argv'][1] == '--debug') {
    // only debug given file
    define('DEBUG', true);
    $dirs = array();
    foreach ( $_SERVER['argv'] as $i => $v ) {
        if ( $i <= 1 ) {
            continue;
        } else if ( is_dir($v) ) {
            $dirs[] = $v;
        } else if ( file_exists($v) ) {
            parseFile(new SplFileInfo($v));
        } else {
            trigger_error("bad argument: ".$v, E_USER_ERROR);
        }
    }
} else {
    define('DEBUG', false);

    if (!file_exists($_SERVER['argv'][1])) {
        file_put_contents('php://stderr', "phpdoc path not found");
        exit(-1);
    }

    $dirs = array(
        $_SERVER['argv'][1]."/reference",
        $_SERVER['argv'][1]."/appendices",
        $_SERVER['argv'][1]."/language/predefined/"
    );
}

foreach ($dirs as $dir) {
    $dirIt = new RecursiveIteratorIterator( new RecursiveDirectoryIterator($dir));
    foreach ($dirIt as $file) {
        parseFile($file);
    }
}

unset($existingFunctions);

/*
 Here be dirty hacks! PHP's documentation isn't as good as could be wished for...
 */

// Clean the functions from imagick
foreach (array_keys($constants) as $c) {
    if ($pos = strpos($c, '::')) {
        $class = substr($c, 0, $pos);
        if ($class == 'imagick') $class = 'Imagick';
        newClassEntry($class);
    }
}

if ( !DEBUG ) {
    // The dir function, which lacks parseable documentation...
    $classes['global']['functions'][] = array(
        'name' => "dir",
        'params' => array(array('name' => "path", 'type' => "string", 'isRef' => false)),
        'type' => "Directory",
        'desc' => "Return an instance of the Directory class"
    );
}

$skipFunctions = array();
// remove delete() function which only acts as a pointer to unlink
// in the documentation but does not actually exist as a alias in PHP
$skipFunctions[] = 'delete';

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
        // default to integer const type
        return "0";
    }
}

function prepareComment($comment, $indent = '') {
    if (trim($comment) == '') {
        return '';
    }
    // remove indentation
    $comment = preg_replace("#^[ \t]*#m", "", trim($comment));
    // merge lines
    $comment = preg_replace("#\n{3,}#", "\n\n", $comment);
    // add indentation and asterisk
    $comment = preg_replace("#^#m", $indent." * ", $comment);
    return $indent."/**\n".
                   $comment."\n".
           $indent." **/\n";
}

function sortByName($a, $b) {
    return strnatcasecmp($a['name'], $b['name']);
}

$fileHeader  = "<?php\n";
$fileHeader .= "// THIS FILE IS GENERATED\n";
$fileHeader .= "// WARNING! All changes made in this file will be lost!\n\n";

$declarationCount = 0;
$out = $fileHeader;

// make sure the output it somehow ordered to prevent huge svn diffs
uksort($variables, 'strnatcasecmp');
uksort($classes, 'strnatcasecmp');
uksort($constants, 'strnatcasecmp');

foreach ($variables as $name=>$var) {
    $declarationCount++;
    if ($var['deprecated']) {
        $var['desc'] .= "\n@deprecated\n";
    }
    if (isset($var['superglobal']) && $var['superglobal']) {
        $var['desc'] .= "\n@superglobal\n";
    }
    $out .= prepareComment($var['desc']);
    $out .= "$name = array();\n\n";
}

// make skipclasses lowercase
foreach ($skipClasses as &$name) {
    $name = strtolower($name);
}

foreach ($classes as $class => $i) {
    if (in_array($class, $skipClasses)) continue; //skip those as they are documented in spl.php
    if ($class != 'global') {
        if (isset($i['desc'])) {
            $out .= prepareComment($i['desc']);
        }
        $class = $i['prettyName'];
        $out .= ($i['isInterface'] ? 'interface' : 'class') . " " . $class;
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

    usort($i['properties'], 'sortByName');
    foreach ($i['properties'] as $f) {
        if ($f['type']) {
            $f['desc'] .= "\n@var {$f['type']}\n";
        }
        ///HACK the directory stuff has really bad documentation
        if ($f['desc'] && $class != 'directory') {
            $out .= prepareComment($f['desc'], $indent);
        }
        $out .= "{$indent}var $".$f['name'].";\n";
        $declarationCount++;
    }

    usort($i['functions'], 'sortByName');
    foreach ($i['functions'] as $f) {
        if ( $class == 'global' && in_array($f['name'], $skipFunctions) ) {
            continue;
        }
        $f['desc'] .= "\n\n";
        foreach ($f['params'] as $pi=>$param) {
            $f['desc'] .= "@param {$param['type']}\n";
        }
        if ($f['type']) {
            $f['desc'] .= "\n@return {$f['type']}\n";
        }
        $version_key = strtolower(($class == 'global' ? '' : $class.'::') . $f['name']);
        if (isset($versions[$version_key])) {
            $f['desc'] .= "\n@since {$versions[$version_key]}\n";
        }
        ///HACK the directory stuff has really bad documentation
        if ($f['desc'] && $class != 'directory') {
            $out .= prepareComment($f['desc'], $indent);
        }
        $out .= "{$indent}function ".$f['name'];
        $out .= "(";
        foreach ($f['params'] as $pi=>$param) {
            if ($pi > 0) $out .= ", ";
            if ($param['isRef']) $out .= "&";
            $out .= '$'.$param['name'];
        }
        $out .= ") {}\n\n";
        $declarationCount++;
    }

    if ($class != 'global') $out .= "}\n";
}
foreach ($constants as $c=>$ctype) {
    if (strpos($c, '::')===false) {
        if ( isset($constants_comments[$c]) ) {
          $out .= prepareComment($constants_comments[$c]);
        }
        $out .= "define('$c', ".constTypeValue($ctype).");\n";
        $declarationCount++;
    }
}

if ( !DEBUG ) {
    file_put_contents("phpfunctions.php", $out);
    echo "created phpfunctions.php...\n";
} else {
    echo "phpfunctions.php\n~~~~\n$out\n~~~~\n";
}
echo "wrote ".$declarationCount." declarations\n";

/**
 * Parse file
 *
 * @param SplFileInfo  $file  File handler
 * @return  bool
 */
function parseFile($file, $funcOverload="") {
global $existingFunctions, $constants, $constants_comments, $variables, $classes, $isInterface, $versions;

    if (substr($file->getFilename(), -4) != '.xml') return false;
    if (substr($file->getFilename(), 0, 9) == 'entities.') return false;
    $string = file_get_contents($file->getPathname());
    $string = preg_replace('#<!\\[CDATA\\[.*?\\]\\]>#s', '', $string);
    $isInterface = strpos($string, '<phpdoc:classref') !== false &&
                   strpos($string, '&reftitle.interfacesynopsis;') !== false;

    $string = preg_replace('#(?:(&amp;|&gt;|&lt;)|&[A-Za-z\\.0-9-_]+;)#', '$1', $string);
    $removeSections = array();
    $removeSections[] = 'apd.installwin32';
    $removeSections[] = 'intl.intldateformatter-constants.calendartypes';
    foreach ($removeSections as $i) {
        $string = preg_replace('#'.preg_quote('<section xml:id="'.$i.'">').'.*?</section>#s', '', $string);
    }
    $xml = new SimpleXMLElement($string);

    if ( $file->getFilename() == 'versions.xml' ) {
        foreach ( $xml->xpath('/versions/function') as $f ) {
            $attrs = $f->attributes();
            $versions[strtolower($attrs['name'])] = (string) $attrs['from'];
        }
        return;
    }

    $xml->registerXPathNamespace('db', 'http://docbook.org/ns/docbook');
    $xml->registerXPathNamespace('phpdoc', 'http://php.net/ns/phpdoc');
    if ($vars = $xml->xpath('//phpdoc:varentry//db:refnamediv')) {
        foreach ($vars as $var) {
            foreach ($var->refname as $i) {
                $i = (string)$i;
                if ( isset($variables[$i]) ) {
                    $v = $variables[$i];
                } else {
                    $v = array();
                }
                if (substr($i, 0, 1) != '$') continue;

                if (substr($i, -13) == ' [deprecated]') {
                    $i = substr($i, 0, -13);
                    $v['deprecated'] = true;
                } else {
                    $v['deprecated'] = false;
                }
                $v['desc'] = (string)$var->refpurpose;
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
    // handle constants.xml with different layout as those above
    if ( !isset($xml->variablelist) && $file->getFilename() == 'constants.xml' && $xml->xpath("//db:constant") ) {
        $consts = $xml->xpath("//db:entry");
        foreach ( $consts as $i=>$p ) {
            if ( isset($p->constant) ) {
                if ( !isset($p->type) ) {
                    // default to integer constants
                    $p->type = 'integer';
                } else {
                    // check for comment
                    // next entry is the value of the constant which is followed by the comment
                    if ( isset($consts[$i+2]) && !$consts[$i+2]->children() ) {
                        $comment = (string)$consts[$i+2];
                        if ( !empty($comment) ) {
                            $constants_comments[(string)$p->constant] = $comment;
                        }
                    }
                }
                $constants[(string)$p->constant] = (string)$p->type;
            }
        }
    }
    if ($list = $xml->xpath('//db:sect2[starts-with(@xml:id, "reserved.classes")]/db:variablelist/db:varlistentry')) {
        foreach ($list as $l) {
            $classname = newClassEntry((string)$l->term->classname);

            $desc = trim(strip_tags($l->listitem->asXML()));
            if ( !empty($desc) ) {
               $classes[$classname]['desc'] = $desc;
            }
        }
    }

    $cEls = $xml->xpath('//db:classsynopsis/db:classsynopsisinfo');
    if ($cEls) {
        foreach ($cEls as $class) {
            $class->registerXPathNamespace('db', 'http://docbook.org/ns/docbook');
            $className = (string)$class->ooclass->classname;
            if (!$className) continue;
            $className = newClassEntry($className);
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
            if ($paras = $xml->xpath('//db:section[starts-with(@xml:id, "'.$className.'")]/db:para')) {
                foreach ($paras as $p) {
                    $classes[$className]['desc'] .= "\n".((string)$p);
                }
            }
        }
    }

    if (!isset($xml->refsect1)) return false;

    $desc = getDocumentation($xml);

    $addedSomething = false;
    // file could contain function + property
    if (isset($xml->refsect1->classsynopsis) && isset($xml->refsect1->classsynopsis->fieldsynopsis)) {
        $class = (string)$xml->refsect1->classsynopsis->ooclass->classname;

        foreach ( $xml->refsect1->classsynopsis->fieldsynopsis as $synopsis ) {
            newPropertyEntry($class, $synopsis->varname, $desc, $synopsis->type );
            $addedSomething = true;
        }
    }

    if (isset($xml->refsect1->methodsynopsis)) {
        $methodsynopsis = $xml->refsect1->methodsynopsis;
        newMethodEntry('global', $methodsynopsis->methodname, $funcOverload, $methodsynopsis, $desc, $xml);
        $addedSomething = true;
    }
    if (isset($xml->refsect1->classsynopsis) && isset($xml->refsect1->classsynopsis->methodsynopsis)) {
        $methodsynopsis = $xml->refsect1->classsynopsis->methodsynopsis;
        newMethodEntry($xml->refsect1->classsynopsis->ooclass->classname, $methodsynopsis->methodname, $funcOverload, $methodsynopsis, $desc, $xml);
        $addedSomething = true;
    }
    if ( !$addedSomething && isset($xml->refnamediv->refpurpose->function) ) {
        // This is function alias
        $functionName = (string)$xml->refnamediv->refname;
        $aliasName    = (string)$xml->refnamediv->refpurpose->function;
        $baseFileName = dirname($file->getPathname()).'/'.str_replace('_', '-', $aliasName).'.xml';
        if ( $baseFileName == $file->getPathname() || !file_exists($baseFileName) ) {
            return false;
        }
        parseFile(new SplFileInfo($baseFileName), $functionName);
        $addedSomething = true;
    }

    return $addedSomething;
} // end of function parseFile()

/**
 * Create a new class entry if it not exists.
 *
 * Key in $classes will be the lower-case @p $name.
 * The prettyName member will be @p $name, if it contains non-lowercase chars.
 *
 * Returns the lower-cased @p $name
 */
function newClassEntry($name) {
    global $classes, $isInterface;
    $lower = strtolower($name);
    if (!isset($classes[$lower])) {
        $classes[$lower] = array(
            'functions' => array(),
            'properties' => array(),
            'prettyName' => $name,
            'desc' => '',
            'isInterface' => $isInterface,
        );
    } else {
        if ( $lower != $name ) {
            $classes[$lower]['prettyName'] = $name;
        }
        if ( $isInterface ) {
            $classes[$lower]['isInterface'] = true;
        }
    }
    return $lower;
}

/**
 * get the documentation for an entry
 * @return string
 */
function getDocumentation(SimpleXMLElement $xml) {
    $descs = array();
    foreach ($xml->refsect1->para as $p ) {
        $p = strip_tags($p->asXML());
        $p = trim($p);
        $p = preg_replace('#  +#', ' ', $p);
        $p = preg_replace('#^ | $#m', '', $p);
        $p = preg_replace('#(?<=[^\n])\n(?=[^\n])#s', ' ', $p);
        $p = preg_replace('#\n\n+#s', "\n\n", $p);
        if ( stripos($p, 'procedural style') !== false || stripos($p, 'procedure style') !== false
            || stripos($p, 'object oriented style') !== false ) {
            // uninteresting
            continue;
        }
        $p = wordwrap($p, 70, "\n", false);
        $descs[] = $p;
    }
    return implode("\n\n", $descs);
}

/**
 * create a new property entry for @p $class
 */
function newPropertyEntry($class, $name, $desc, $type) {
    global $classes;
    $class = newClassEntry($class);
    $classes[$class]['properties'][] = array(
        'name' => (string) $name,
        'desc' => (string) $desc,
        'type' => (string) $type
    );
}

/**
 * create a new method entry for @p $class
 */
function newMethodEntry($class, $function, $funcOverload, $methodsynopsis, $desc, SimpleXMLElement $xml) {
    global $existingFunctions, $classes;
    $class = (string) $class;
    $function = (string) $function;
    $funcOverload = (string) $funcOverload;

    if (strpos($function, '::')) {
        $class = substr($function, 0, strpos($function, '::'));
        $function = substr($function, strpos($function, '::')+2);
    } else if (strpos($function, '->')) {
        $class = substr($function, 0, strpos($function, '->'));
        $function = substr($function, strpos($function, '->')+2);
    } else {
        if ($function == '__halt_compiler') return false;
        if ($function == 'exit') return false;
        if ($function == 'die') return false;
        if ($function == 'eval') return false;
        if ($function == 'echo') return false;
        if ($function == 'print') return false;
        if ($function == 'array') return false;
        if ($function == 'list') return false;
        if ($function == 'isset') return false;
        if ($function == 'unset') return false;
        if ($function == 'empty') return false;
    }

    if (strpos($function, '-')) return false;
    if (strpos($class, '-')) return false;
    if ($function == 'isSet') return false; //todo: bug in lexer
    if ($function == 'clone') return false; //todo: bug in lexer
    if (substr($class, 0, 3) == 'DOM') $class = 'Dom'.substr($class, 3);
    $class = trim($class);
    if ($class == 'imagick') $class = 'Imagick';
    if (in_array($class.'::'.($funcOverload ? $funcOverload : $function), $existingFunctions)) return false;
    $existingFunctions[] = $class.'::'.($funcOverload ? $funcOverload : $function);

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
            'type' => (string)$param->type,
            'isRef' => isset($param->parameter->attributes()->role) ? ($param->parameter->attributes()->role == "reference") : false
        );
    }

    $class = newClassEntry($class);
    $classes[$class]['functions'][] = array(
        'name'   => $funcOverload ? $funcOverload : $function,
        'params' => $params,
        'type'   => (string)$methodsynopsis->type,
        'desc'   => $funcOverload ? str_replace($function, $funcOverload, $desc) : $desc
    );
}