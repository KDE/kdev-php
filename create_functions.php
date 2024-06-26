<?php
/*
    SPDX-FileCopyrightText: 2008 Niko Sams <niko.sams@gmail.com>
    SPDX-FileCopyrightText: 2010 Milian Wolff <mail@milianw.de>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

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
$skipClasses[] = 'static'; // O_o where does that come from?
$skipClasses[] = 'componere\abstract\definition'; // invalid namespace identifier, discussed in https://github.com/krakjoe/componere/issues/5

// interfaces wrongly declared as classes
$interfaceClasses = array();
$interfaceClasses[] = 'sessionhandlerinterface';
$interfaceClasses[] = 'yaf_route_interface';
$interfaceClasses[] = 'yaf_view_interface';

$abstractClasses[] = array();
$abstractClasses[] = 'reflectionfunctionabstract';
$abstractClasses[] = 'xmldiff\base';
$abstractClasses[] = 'yaf_action_abstract';

$skipComments = array();
$skipComments[] = ':';
$skipComments[] = '(method):';
$skipComments[] = 'Description here.';
$skipComments[] = 'Description here...';
$skipComments[] = 'Description';
$skipComments[] = 'The function description goes here.';

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
        $_SERVER['argv'][1]."/features",
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

// Add constant only classes
foreach (array_keys($constants) as $c) {
    if ($pos = strpos($c, '::')) {
        $class = substr($c, 0, $pos);
        $isInterface = false;
        $isAbstractClass = false;
        newClassEntry($class);
    }
}

$skipFunctions = array();
// remove delete() function which only acts as a pointer to unlink
// in the documentation but does not actually exist as a alias in PHP
$skipFunctions[] = 'delete';

// awesome uncallable functions - noone knows wth that should be...
$skipMethods = array();
$skipMethods[] = 'list';
$skipMethods[] = 'declare';
$skipMethods[] = 'do';
$skipMethods[] = 'echo';
$skipMethods[] = 'function';

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

function removeTag($xml, $tag) {
    $tag = preg_quote($tag, '#');
    return trim(preg_replace('#(^<'.$tag.'[^>]*>|</'.$tag.'>$)#s', '', trim($xml)));
}

function cleanupComment($comment) {
    // <function|parameter>...</> to {@link ...}
    $comment = preg_replace('#<(function|parameter)>(.+)</\1>#U', '{@link $2}', $comment);
    // remove <para> and other stuff
    ///TODO: support web-links, lists and tables
    $comment = strip_tags($comment);
    $comment = html_entity_decode($comment);

    // make sure no */ occurs in a comment...
    $comment = preg_replace('#\*/#', '* /', $comment);

    $comment = preg_replace('#(?<=[^\n])\n(?=[^\n])#s', ' ', $comment);

    $comment = preg_replace('#  +#', ' ', $comment);
    $comment = preg_replace('#^ | $#m', '', $comment);
    $comment = preg_replace("#\n{3,}#", "\n\n", $comment);

    $comment = trim($comment);
    return $comment;
}

function prepareComment($comment, array $more, $indent = '') {
    $comment = cleanupComment($comment);
    if (empty($comment) && empty($more)) {
        return '';
    }
    $comment = wordwrap($comment, 70, "\n", false);
    if ( !empty($more) ) {
        if ( !empty($comment) ) {
            $comment .= "\n\n";
        }
        foreach($more as $s) {
            $comment .= str_replace("\n", "\n  ", // indent
                            wordwrap(cleanupComment($s), 68, "\n", false)
                        )."\n";
        }
    }
    $comment = rtrim($comment);
    // add indentation and asterisk
    $comment = preg_replace("#^#m", $indent." * ", $comment);
    $comment = str_replace(" * \n", " *\n", $comment);
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

// put some base classes up front
$baseClasses = [ 'exception', 'error', 'throwable', 'iterator', 'traversable' ];
foreach ($baseClasses as $baseClass) {
    if (array_key_exists($baseClass, $classes)) {
        $base = $classes[$baseClass];
        unset($classes[$baseClass]);
        $classes = array_merge(array($baseClass => $base), $classes);
        reset($classes);
    }
}

foreach ($variables as $name=>$var) {
    $declarationCount++;
    $moreDesc = array();
    if ($var['deprecated']) {
        $moreDesc[] = "@deprecated";
    }
    if (isset($var['superglobal']) && $var['superglobal']) {
        $moreDesc[] = "@superglobal";
    }
    $out .= prepareComment($var['desc'], $moreDesc);
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
            $out .= prepareComment($i['desc'], array());
        }
        if (!empty($i['namespace'])) {
            $out .= 'namespace ' . $i['namespace'] . " {\n";
        }
        $class = $i['prettyName'];
        $out .= ($i['isAbstract']) ? 'abstract ' : '';
        $out .= ($i['isFinal'] && !$i['isInterface']) ? 'final ' : '';
        $out .= ($i['isInterface'] ? 'interface' : 'class') . " " . $class;
        if (isset($i['extends'])) {
            if (!is_array($i['extends']) && !in_array(strtolower($i['extends']), $skipClasses)) {
                $out .= " extends {$i['extends']}";
            } elseif (is_array($i['extends'])) {
                $out .= " extends ";
                foreach ($i['extends'] as $entry) {
                    if (!in_array(strtolower($entry), $skipClasses)) {
                        $out .= "$entry, ";
                    }
                }
                $out = rtrim($out, ', ');
            }
        }
        if (isset($i['implements'])) {
            $out .= " implements ".implode(", ", $i['implements']);
        }
        $out .= " {\n";
        $declarationCount++;
    }

    $indent = '';
    if ($class != 'global') $indent = '    ';

    if (array_key_exists('extends', $i)) {
        if (!is_array($i['extends'])) {
            $extends = [ $i['extends'] ];
        } else {
            $extends = $i['extends'];
        }

        foreach ($extends as $entry) {
            if (in_array(strtolower($entry), $skipClasses)) {
                $base = $classes[strtolower($entry)];

                $i['properties'] = array_merge($i['properties'], $base['properties']);
                $i['functions']  = array_merge($i['functions'], $base['functions']);
            }
        }
    }

    foreach ($constants as $c=>$ctype) {
        if ($pos = strpos($c, '::')) {
            if (substr($c, 0, $pos) == $class) {
                $moreDesc = array();
                $moreDesc[] = "@var {$ctype}";
                if ( isset($constants_comments[$c]) ) {
                    $out .= prepareComment($constants_comments[$c], $moreDesc, $indent);
                }
                unset($constants[$c]);
                $c = substr($c, $pos+2);
                $out .= "    const $c = ".constTypeValue($ctype).";\n\n";
                $declarationCount++;
            }
        }
    }

    usort($i['properties'], 'sortByName');
    $handled = [];
    foreach ($i['properties'] as $f) {
        if (in_array($f['name'], $handled)) {
            continue;
        }
        $handled[] = $f['name'];
        $moreDesc = array();
        if ($f['type']) {
            $moreDesc[] = "@var {$f['type']}";
        }
        ///HACK the directory stuff has really bad documentation
        if ($class != 'directory') {
            $out .= prepareComment($f['desc'], $moreDesc, $indent);
        }
        if ($class != 'global' && array_key_exists('modifiers', $f) && is_array($f['modifiers'])) {
            $f['modifiers'] = array_filter($f['modifiers'], function ($value){ return $value != 'readonly'; });
            $modifiers  = implode(' ', $f['modifiers']);
            $modifiers .= empty($modifiers) ? 'public ' : ' ';
        }
        $out .= "{$indent}{$modifiers}$".$f['name'].";\n\n";
        $declarationCount++;
    }

    usort($i['functions'], 'sortByName');
    $handled = [];
    foreach ($i['functions'] as $f) {
        if (in_array($f['name'], $handled)) {
            continue;
        }
        $handled[] = $f['name'];
        if ( $class == 'global' && in_array($f['name'], $skipFunctions) ) {
            continue;
        } else if ( $class != 'global' && in_array($f['name'], $skipMethods) ) {
            continue;
        }
        if ($endpos = strrpos($f['name'], '\\')) {
            $out .= 'namespace ' . substr($f['name'], 0, $endpos) . " {\n\n";
            $f['name'] = substr($f['name'], $endpos + 1);
        }
        $moreDesc = array();
        foreach ($f['params'] as $pi=>$param) {
            $desc = '';
            if ( isset($param['desc']) ) {
                $desc = trim($param['desc']);
            }
            $param_name = str_replace('$...', '...$', '$'.$param['name']);
            $moreDesc[] = "@param {$param['type']} $param_name $desc";
        }
        if ($f['type']) {
            $moreDesc[] = rtrim("@return {$f['type']} {$f['return_desc']}");
        }
        $version_key = strtolower(($class == 'global' ? '' : $class.'::') . $f['name']);
        if (isset($versions[$version_key])) {
            $moreDesc[] = "@since {$versions[$version_key]}";
        }
        ///HACK the directory stuff has really bad documentation
        if ($class != 'directory') {
            $out .= prepareComment($f['desc'], $moreDesc, $indent);
        }
        if ($f['name'] == '__construct' && strtolower($class) == 'eventutil') {
            //HACK: PHP doesn't allow abstract final classes, so make the constructor private instead.
            $f['modifiers'] = [ 'private' ];
        }
        if ($class != 'global' && array_key_exists('modifiers', $f) && is_array($f['modifiers'])) {
            if ($i['isInterface'] === true) {
                $f['modifiers'] = array_filter($f['modifiers'], function ($value){ return $value != 'abstract' && $value != 'final'; });
            }
            $modifiers  = implode(' ', $f['modifiers']);
            $modifiers .= empty($modifiers) ? '' : ' ';
        } else {
            $modifiers = '';
        }
        $out .= "{$indent}{$modifiers}function ".$f['name'];
        $out .= "(";
        $first = true;
        $params_total = count($f['params'])-1;
        foreach ($f['params'] as $pi=>$param) {
            $param_name = str_replace('$...', '...$', '$'.$param['name']);
            $param_name = str_replace('"', '', $param_name);
            if (substr($param_name, 0, 3) == '...' && $pi < $params_total) {
                // varargs in the middle of arguments are invalid syntax.
                // print the documentation, but ignore them in the function signature
                continue;
            }
            if (!$first) $out .= ", ";
            $first = false;
            if ($param['isRef']) $out .= "&";
            $out .= $param_name;
        }
        $out .= ")";
        if ( $i['isInterface'] || (array_key_exists('modifiers', $f) && in_array('abstract', $f['modifiers'])) ) {
            $out .= ";";
        } else {
            $out .= "{}";
        }
        $out .= "\n\n";
        if ($endpos) $out .= "}\n\n";
        $declarationCount++;
    }

    if ($class != 'global') $out .= "}\n";
    if (!empty($i['namespace'])) $out .= "}\n";
}
foreach ($constants as $c=>$ctype) {
    if (strpos($c, '::')===false) {
        if ( isset($constants_comments[$c]) ) {
          $out .= prepareComment($constants_comments[$c], array());
        }
        $out .= "define('$c', ".constTypeValue($ctype).");\n";
        $declarationCount++;
    }
}
chdir(dirname(__FILE__));
if ( !DEBUG ) {
    echo "saving phpfunctions.php file\n";
    file_put_contents("phpfunctions.php", $out);

    if ( shell_exec("which php-parser") ) {
        echo "making sure phpfunctions file is valid...\n";
        system("php-parser phpfunctions.php", $ret);
        if ( $ret != 0 ) {
            die("could not parse file, aborting\n");
        }
    } else {
        echo "note: put php-parser in your path and I can check the generated file directly...\n";
    }

    echo "done\n";
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
function parseFile($file, $funcOverload="", $classOverload="") {
global $existingFunctions, $constants, $constants_comments, $variables, $classes, $isInterface, $isAbstractClass, $isFinalClass, $versions;

    if (substr($file->getFilename(), -4) != '.xml') return false;
    if (substr($file->getFilename(), 0, 9) == 'entities.') return false;
    $string = file_get_contents($file->getPathname());
    $isInterface = (strpos($string, '<phpdoc:classref') !== false &&
                   strpos($string, '&reftitle.interfacesynopsis;') !== false) ||
                   strpos($string, ' interface</title>') !== false;
    $isAbstractClass = false;
    $isFinalClass = false;

    $string = str_replace('&null;', 'NULL', $string);
    $string = str_replace('&true;', 'TRUE', $string);
    $string = str_replace('&false;', 'FALSE', $string);
    $string = preg_replace('#(?:(&amp;|&gt;|&lt;)|&[A-Za-z\\.0-9-_]+;)#', '$1', $string);
    $removeSections = array();
    $removeSections[] = 'apd.installwin32';
    $removeSections[] = 'intl.intldateformatter-constants.calendartypes';
    foreach ($removeSections as $i) {
        $string = preg_replace('#'.preg_quote('<section xml:id="'.$i.'">').'.*?</section>#s', '', $string);
    }
    echo "reading documentation from {$file->getPathname()}\n";

    libxml_use_internal_errors(TRUE);
    $xml = simplexml_load_string($string,  "SimpleXMLElement",  LIBXML_NOCDATA);

    if ($xml === false) {
      echo "  parsing XMl failed!\n";
      return false;
    }

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
                if (substr($i, -10) == ' [removed]') continue;

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
        foreach ($xml->variablelist as $list) {
            foreach ($list->varlistentry as $i=>$varlistentry) {
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
    }
    // handle class constants (and their global aliases) not defined as fieldsynopsis
    $consts = $xml->xpath("db:partintro//db:varlistentry");
    foreach ($consts as $c) {
        foreach ($c->term as $t) {
            if ($name = (string)$t->constant) {
                if (!isset($constants[$name])) {
                    if (strpos($name, '=')) {
                        $c = substr($name, 0, strpos($name, '='));
                    }
                    $constants[$name] = 'mixed';
                    $constants_comments[$name] = cleanupComment($c->listitem->para->asXML());
                }
            }
        }
    }
    // handle constants under section
    if ($file->getFilename() == 'constants.xml') {
        $consts = $xml->xpath("db:section//db:varlistentry");
        foreach ($consts as $c) {
            if ($name = (string)$c->term->constant) {
                if (!isset($constants[$name])) {
                    if (strpos($name, '=')) {
                        $c = substr($name, 0, strpos($name, '='));
                    }
                    $ctype = $c->term->type;
                    if (!$ctype) {
                        $ctype = $c->term->link;
                    }
                    $constants[$name] = (string)$ctype;
                }
            }
        }
    }
    // handle constants within tables
    if ($file->getFilename() == 'constants.xml') {
        $consts = $xml->xpath("db:section//db:row");
        foreach ($consts as $c) {
            if (!$c->entry && !$c->entry[0] && !$c->entry[0]->constant) {
                continue;
            }
            $name = (string)$c->entry[0]->constant;
            switch ($name) {
                case '':
                    continue 2;
                default:
                    if ($c->entry[2]) {
                        $constants[$name] = $c->term->type;
                        $constants_comments[$name] = cleanupComment($c->entry[2]->asXML());
                    } else if ($c->entry[1]) {
                        $constants[$name] = 'mixed';
                        $constants_comments[$name] = cleanupComment($c->entry[1]->asXML());
                    }
            }
        }
    }
    // handle constants within para
    if ($file->getFilename() == 'constants.xml') {
        $consts = $xml->xpath("db:para//db:varlistentry");
        foreach ($consts as $c) {
            if ($name = (string)$c->term->constant) {
                if ($name == '__default') {
                    continue;
                }
                if (!isset($constants[$name])) {
                    if (strpos($name, '=')) {
                        $c = substr($name, 0, strpos($name, '='));
                    }
                    $ctype = $c->term->type;
                    if (!$ctype) {
                        $ctype = $c->term->link;
                    }
                    $constants[$name] = (string)$ctype;
                }
            }
        }
    }
    if ($file->getFilename() == 'constants.xml') {
        $consts = $xml->xpath("db:para//db:simpara");
        foreach ($consts as $c) {
            if ($name = (string)$c->constant) {
                if ($name[0] == '"') {
                    continue;
                }
                if (!isset($constants[$name])) {
                    $constants[$name] = 'mixed';
                }
            }
        }
    }
    if ($file->getFilename() == 'ciphers.xml') {
        $consts = $xml->xpath("db:para//db:simpara");
        foreach ($consts as $c) {
            if ($name = (string)$c) {
                $name = explode(' ', $name)[0];
                $name = explode('(', $name)[0];
                if (!isset($constants[$name])) {
                    $constants[$name] = 'mixed';
                }
            }
        }
    }
    // handle constants in tables within refsect1
    if ($file->getFilename() != 'attr.xml') {
        $consts = $xml->xpath("db:refsect1//db:row");
        foreach ($consts as $c) {
            if (!$c->entry && !$c->entry[0] && !$c->entry[0]->constant) {
                continue;
            }
            $name = (string)$c->entry[0]->constant;
            switch ($name) {
                case '':
                case '0':
                    continue 2;
                case 'ABDAY_(1-7)':
                case 'DAY_(1-7)':
                    for ($i=1; $i<8;$i++) {
                        $cname = substr($name, 0, strpos($name, '_') + 1) . $i;
                        $constants[$cname] = 'mixed';
                        if ($c->entry[1]) {
                            $constants_comments[$cname] = cleanupComment($c->entry[1]->asXML());
                        }
                    }
                    break;
                case 'ABMON_(1-12)':
                case 'MON_(1-12)':
                    for ($i=1; $i<13;$i++) {
                        $cname = substr($name, 0, strpos($name, '_') + 1) . $i;
                        $constants[$cname] = 'mixed';
                        if ($c->entry[1]) {
                            $constants_comments[$cname] = cleanupComment($c->entry[1]->asXML());
                        }
                    }
                    break;
                default:
                    $constants[$name] = 'mixed';
                    if ($c->entry[1]) {
                        $constants_comments[$name] = cleanupComment($c->entry[1]->asXML());
                    }
            }
        }
    }
    // handle constants within file-upload.xml
    if ($file->getFilename() == 'file-upload.xml') {
        $consts = $xml->xpath("db:sect1//db:varlistentry");
        foreach ($consts as $c) {
            if ($name = (string)$c->term->constant) {
                if (!isset($constants[$name])) {
                    if (strpos($name, '=')) {
                        $c = substr($name, 0, strpos($name, '='));
                    }
                    $ctype = $c->term->type;
                    if (!$ctype) {
                        $ctype = $c->term->link;
                    }
                    $constants[$name] = (string)$ctype;
                    $constants_comments[$name] = cleanupComment($c->listitem->para->asXML());
                }
            }
        }
    }
    // handle constants within tokens.xml
    if ($file->getFilename() == 'tokens.xml') {
        $consts = $xml->xpath("db:table//db:row");
        foreach ($consts as $c) {
            if (!$c->entry && !$c->entry[0] && !$c->entry[0]->constant) {
                continue;
            }
            $name = (string)$c->entry[0]->constant;
            switch ($name) {
                case '':
                    continue 2;
                default:
                    $constants[$name] = 'mixed';
            }
        }
    }
    // handle url-stat constants
    if ($file->getFilename() == 'url-stat.xml') {
        $consts = $xml->xpath("db:refsect1//db:informaltable//db:row");
        foreach ($consts as $c) {
            if (!$c->entry && !$c->entry[0]) {
                continue;
            }
            $name = (string)$c->entry[0];
            switch ($name) {
                case '':
                case 'Flag':
                    continue 2;
                default:
                    $constants[$name] = 'mixed';
                    $constants_comments[$name] = cleanupComment($c->entry[1]->asXML());
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
                        $comment = $consts[$i+2]->asXml();
                        if ( !empty($comment) ) {
                            $constants_comments[(string)$p->constant] = $comment;
                        }
                    }
                }
                $name = (string)$p->constant;
                if ($name == 'LOG_LOCAL0 ... LOG_LOCAL7') {
                    for ($i=0; $i<8; $i++) {
                    $constants['LOG_LOCAL' . $i] = (string)$p->type;
                    }
                } else {
                    $constants[$name] = (string)$p->type;
                }
            }
        }
    } else if (!isset($xml->variablelist) && $file->getFilename() == 'commandline.xml') {
        // yay for non-unified xml structures :-X
        $consts = $xml->xpath("//db:row");
        foreach ( $consts as $i=>$p ) {
            $constant = "";
                    // default to integer constants
            $type = "integer";
            if ( isset($p->entry[0]) && isset($p->entry[0]->constant) ) {
                $constant = trim((string) $p->entry[0]->constant);
                if ( isset($p->entry[0]->constant->type) ) {
                    $type = (string)$p->entry[0]->constant->type;
                }
            }
            if (empty($constant)) {
                continue;
            }
            // check for comment
            // next entry is the comment
            if ( isset($p->entry[1]) ) {
                $comment = $p->entry[1]->para->asXml();
                if ( !empty($comment) ) {
                    $constants_comments[$constant] = $comment;
                }
            }
            $constants[$constant] = $type;
        }
    }
    if ($list = $xml->xpath('//db:sect2[starts-with(@xml:id, "reserved.classes")]/db:variablelist/db:varlistentry')) {
        foreach ($list as $l) {
            $classname = newClassEntry((string)$l->term->classname);

            $classes[$classname]['desc'] = cleanupComment(removeTag($l->listitem->asXML(), 'listitem'));
        }
    }

    $cEls = $xml->xpath('//db:classsynopsis/db:classsynopsisinfo');
    if ($cEls) {
        foreach ($cEls as $class) {
            $class->registerXPathNamespace('db', 'http://docbook.org/ns/docbook');
            $className = (string)$class->ooclass->classname;
            if ((string)$class->ooclass->modifier === 'abstract') {
                $isAbstractClass = true;
            }
            if ((string)$class->ooclass->modifier === 'final') {
                $isFinalClass = true;
            }
            if (!$className) continue;
            $className = newClassEntry($className);
            if ($interfaces = $class->xpath('//db:oointerface/db:interfacename')) {
                $key = $isInterface ? 'extends' : 'implements';
                foreach ($interfaces as $if) {
                    $classes[$className][$key][] = (string)$if;
                }
            }
            if ($extends = $class->xpath('//db:ooclass')) {
                foreach ($extends as $c) {
                    if ($c->modifier == 'extends') {
                        if (array_key_exists('extends', $classes[$className]) && is_array($classes[$className]['extends'])) {
                            array_unshift($classes[$className]['extends'], (string)$c->classname);
                        } else {
                            $classes[$className]['extends'] = (string)$c->classname;
                        }
                    } elseif ($c->modifier == 'implements') {
                        if (array_key_exists('implements', $classes[$className]) && is_array($classes[$className]['implements'])) {
                            array_unshift($classes[$className]['implements'], (string)$c->classname);
                        } else {
                            $classes[$className]['implements'][] = (string)$c->classname;
                        }
                    }
                }
            }
            if ($paras = $xml->xpath('//db:section[starts-with(@xml:id, "'.$className.'")]/db:para')) {
                foreach ($paras as $p) {
                    $classes[$className]['desc'] .= "\n". cleanupComment(removeTag($p->asXML(), 'para'));
                }
            } elseif ($paras = $xml->xpath('//db:section[starts-with(@xml:id, "'. str_replace('_', '-', $className) .'")]/db:para')) {
                foreach ($paras as $p) {
                    $classes[$className]['desc'] .= "\n". cleanupComment(removeTag($p->asXML(), 'para'));
                }
            }
        }
    }

    $addedSomething = false;

    if (isset($xml->partintro) && !isset($xml->refsect1)) {
        if (isset($xml->partintro->section[1]->classsynopsis->fieldsynopsis)) {
            $synopsis = $xml->partintro->section[1]->classsynopsis->fieldsynopsis;
            $class    = $xml->partintro->section[1]->classsynopsis->ooclass->classname;

            $classname = newClassEntry($class);

            foreach ($synopsis as $property){
                $name  = $property->varname;

                $modifiers = (array) $property->modifier;
                $type = isset($property->type) ? $property->type : 'mixed';
                $desc = '';

                if (in_array('const', $modifiers)) {
                    $constantname = strtolower(substr((string) $name, strrpos((string) $name, '::') + 2));
                    if ($constant_descs = $xml->xpath('//db:section[@xml:id="' . $classname .'.constants"]//db:varlistentry[@xml:id="'. $classname .'.constants.'. $constantname .'"]') ) {
                        foreach ($constant_descs as $constant_desc) {
                            $desc .= getDocumentationFromPartIntro($constant_desc);
                        }
                    }
                    $constants_comments[(string) $name] = $desc;
                    $constants[(string) $name] = $type;
                } else {
                    if ($property_descs = $xml->xpath('//db:section[@xml:id="' . $classname .'.props"]//db:varlistentry[@xml:id="'. $classname .'.props.'. $name .'"]') ) {
                        foreach ($property_descs as $property_desc) {
                            $desc .= getDocumentationFromPartIntro($property_desc);
                        }
                    }
                    newPropertyEntry($class, $name, $desc, $type, $modifiers);
                }
            }

            $addedSomething = true;
        }
    }

    if (!isset($xml->refsect1)) return $addedSomething;

    $desc = getDocumentation($xml);

    // file could contain function + property
    if (isset($xml->refsect1->classsynopsis) && isset($xml->refsect1->classsynopsis->fieldsynopsis)) {
        $class = (string)$xml->refsect1->classsynopsis->ooclass->classname;

        foreach ( $xml->refsect1->classsynopsis->fieldsynopsis as $synopsis ) {
            newPropertyEntry($class, $synopsis->varname, $desc, $synopsis->type );
            $addedSomething = true;
        }
    }
    if (isset($xml->refsect1->fieldsynopsis)) {
        $synopsis = $xml->refsect1->fieldsynopsis;
        $class = substr($synopsis->varname, 0, strpos($synopsis->varname, '->'));
        $name  = substr($synopsis->varname, strpos($synopsis->varname, '->') + 2);

        newPropertyEntry($class, $name, $desc, $synopsis->type);
        $addedSomething = true;
    }

    if (isset($xml->refsect1->methodsynopsis)) {
        $skip = false;
        if ($funcOverload != "") {
            foreach( $xml->refsect1->methodsynopsis as $synopsis ) {
                if (isset($synopsis->methodname->replaceable)) {
                    if ($funcOverload == (string) $synopsis->methodname->replaceable) {
                        $skip = true;
                    }
                } else {
                    if ($funcOverload == (string) $synopsis->methodname) {
                        $skip = true;
                    }
                }
            }
        }
        if (!$skip) {
            foreach( $xml->refsect1->methodsynopsis as $synopsis ) {
                if (isset($synopsis->methodname->replaceable)) {
                    newMethodEntry('global', $synopsis->methodname->replaceable, $funcOverload, $synopsis, $desc, $xml, $classOverload);
                } else {
                    newMethodEntry('global', $synopsis->methodname, $funcOverload, $synopsis, $desc, $xml, $classOverload);
                }

                $addedSomething = true;
            }
        }
    }
    if (isset($xml->refsect1->classsynopsis) && isset($xml->refsect1->classsynopsis->methodsynopsis)) {
        $methodsynopsis = $xml->refsect1->classsynopsis->methodsynopsis;
        $classOverloadName = $classOverload ?? $xml->refsect1->classsynopsis->ooclass->classname;
        if (isset($synopsis->methodname->replaceable)) {
            newMethodEntry($classOverloadName, $methodsynopsis->methodname->replaceable, $funcOverload, $methodsynopsis, $desc, $xml, $classOverload);
        } else {
            newMethodEntry($classOverloadName, $methodsynopsis->methodname, $funcOverload, $methodsynopsis, $desc, $xml, $classOverload);
        }
        $addedSomething = true;
    }
    if ( !$addedSomething && (isset($xml->refnamediv->refpurpose->function) || isset($xml->refnamediv->refpurpose->methodname)) ) {
        // This is function alias
        $functionNames[] = (string)$xml->refnamediv->refname;
        if ($xml->refnamediv->refpurpose->function) {
            $aliasName    = (string)$xml->refnamediv->refpurpose->function;
            switch ($aliasName) {
                case 'mysqli_stmt_execute':
                    $baseFileName = dirname($file->getPathname()).'/../mysqli_stmt/execute.xml';
                    $overload = "global";
                    break;
                case 'mysqli_options':
                    $functionNames[] = 'mysqli_set_opt';
                    $baseFileName = dirname($file->getPathname()).'/../mysqli/options.xml';
                    $overload = "global";
                    break;
                case 'mysqli_real_escape_string':
                    $baseFileName = dirname($file->getPathname()).'/../mysqli/real-escape-string.xml';
                    $overload = "global";
                    break;
                case 'sql_regcase':
                    $baseFileName = dirname($file->getPathname()).'/../../regex/functions/sql-regcase.xml';
                    $overload = "global";
                    break;
                default:
                    $baseFileName = dirname($file->getPathname()).'/'.str_replace('_', '-', $aliasName).'.xml';
                    $overload = "";
            }
        } else {
            $aliasName    = (string)$xml->refnamediv->refpurpose->methodname;
            $baseFileName = dirname($file->getPathname()).'/'.strtolower(str_replace('::', '/', $aliasName)).'.xml';
            $baseFileName = str_replace('/functions/', '/', $baseFileName);
            $overload = "global";
        }
        if ( $baseFileName == $file->getPathname() || !file_exists($baseFileName) ) {
            return false;
        }
        foreach ($functionNames as $functionName) {
            parseFile(new SplFileInfo($baseFileName), $functionName, $overload);
        }
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
    global $classes, $isInterface, $isAbstractClass, $isFinalClass, $interfaceClasses, $abstractClasses;
    if (strpos($name, '\\') !== false) {
      $endpos = strrpos($name, '\\');
      $class = substr($name, $endpos + 1);
      $namespace = substr($name, 0, $endpos);
    } else {
      $class = $name;
      $namespace = null;
    }
    // This affects OCI-Collection and OCI-Log
    // Technically, this creates wrong class names, but they are otherwise illegal syntax...
    $class = str_replace('-','',$class);
    $lower = strtolower($name);

    if (!$isInterface && in_array($lower, $interfaceClasses)) {
        $isInterface = true;
    }

    if (!$isAbstractClass && in_array($lower, $abstractClasses)) {
        $isAbstractClass = true;
    }

    if (!isset($classes[$lower])) {
        $classes[$lower] = array(
            'functions' => array(),
            'properties' => array(),
            'namespace' => $namespace,
            'prettyName' => $class,
            'desc' => '',
            'isInterface' => $isInterface,
            'isAbstract' => $isAbstractClass,
            'isFinal' => $isFinalClass,
        );
    } else {
        if ( $lower != $class ) {
            $classes[$lower]['prettyName'] = $class;
        }
        if ( $isInterface ) {
            $classes[$lower]['isInterface'] = true;
        }
        if ( $isAbstractClass ) {
            $classes[$lower]['isAbstract'] = true;
        }
        if ( $isFinalClass ) {
            $classes[$lower]['isFinal'] = true;
        }
    }
    return $lower;
}

/**
 * get the documentation for an entry
 * @return string
 */
function getDocumentation(SimpleXMLElement $xml) {
    global $skipComments;

    $descs = array();

    $purpose = $xml->refnamediv->refpurpose;

    if (!in_array($purpose, $skipComments)) {
        $descs[] = $purpose;
    }

    foreach ($xml->refsect1->para as $p ) {
        $p = removeTag($p->asXML(), 'para');
        if ( stripos($p, 'procedural style') !== false || stripos($p, 'procedure style') !== false
            || stripos($p, 'object oriented style') !== false ) {
            // uninteresting
            continue;
        }
        if (in_array($p, $skipComments)) {
            continue;
        }
        if ($p == $purpose || $p == "$purpose.") {
            // avoid duplicate comments
            continue;
        }
        $descs[] = $p;
    }
    return implode("\n\n", $descs);
}

/**
 * get the documentation for an entry
 * @return string
 */
function getDocumentationFromPartIntro(SimpleXMLElement $xml) {
    global $skipComments;

    $descs = array();

    foreach ($xml->listitem->para as $p ) {
        $p = removeTag($p->asXML(), 'para');
        if (in_array($p, $skipComments)) {
            continue;
        }
        $descs[] = $p;
    }
    return implode("\n\n", $descs);
}

/**
 * create a new property entry for @p $class
 */
function newPropertyEntry($class, $name, $desc, $type, $modifiers = []) {
    global $classes;
    $class = newClassEntry($class);
    $classes[$class]['properties'][] = array(
        'name' => (string) $name,
        'desc' => (string) $desc,
        'type' => (string) $type,
        'modifiers' => $modifiers
    );
}

/**
 * create a new method entry for @p $class
 */
function newMethodEntry($class, $function, $funcOverload, $methodsynopsis, $desc, SimpleXMLElement $xml, $classOverload = "") {
    global $existingFunctions, $classes;
    $class = (string) $class;
    $function = (string) $function;
    $funcOverload = (string) $funcOverload;

    if (strpos($function, '::')) {
        if ($classOverload == '') {
            $class = substr($function, 0, strpos($function, '::'));
        }
        $function = substr($function, strpos($function, '::')+2);
        if (strpos($funcOverload, '::')) {
            $class = substr($funcOverload, 0, strpos($funcOverload, '::'));
            $funcOverload = substr($funcOverload, strpos($funcOverload, '::')+2);
        }
    } else if (strpos($funcOverload, '::')) {
        $class = substr($funcOverload, 0, strpos($funcOverload, '::'));
        $funcOverload = substr($funcOverload, strpos($funcOverload, '::')+2);
    } else if (strpos($function, '->')) {
        if ($classOverload == '') {
            $class = substr($function, 0, strpos($function, '->'));
        }
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
        if (trim($paramName) == '...') {
            // Add a variable name for functions taking variable arguments
            $paramName = '...$vararg';
        }
        if (!trim($paramName)) continue;
        $paramName = str_replace('/', '', $paramName);
        $paramName = str_replace('-', '', $paramName);
        $paramName = str_replace('$', '', $paramName);
        $paramName = trim(trim(trim($paramName), '*'), '&');
        if ($pipe_pos = strpos($paramName, '|')) $paramName = substr($paramName, 0, $pipe_pos);
        if (is_numeric(substr($paramName, 0, 1))) $paramName = '_'.$paramName;
        $params[] = array(
            'name' => $paramName,
            'type' => (string)$param->type,
            'isRef' => isset($param->parameter->attributes()->role) ? ($param->parameter->attributes()->role == "reference") : false,
        );
    }
    // get description of params
    if ( $param_descs = $xml->xpath('db:refsect1[@role="parameters"]//db:varlistentry') ) {
        $i = 0;
        foreach ( $param_descs as $d ) {
            if ( !isset($params[$i]) ) {
                continue;
            }
            $paramName = (string) $d->term->parameter;
            $params[$i]['desc'] = '';
            foreach ( $d->listitem->para as $p ) {
                $p = removeTag($p->asXML(), 'para');
                $params[$i]['desc'] .= $p . "\n";
            }
            ++$i;
        }
    }

    if ($return_desc = $xml->xpath('db:refsect1[@role="returnvalues"]//db:para')) {
        $return_desc = removeTag($return_desc[0]->asXML(), 'para');
    } else {
        $return_desc = '';
    }

    $class = newClassEntry($class);
    $classes[$class]['functions'][] = array(
        'name'        => $funcOverload ? $funcOverload : $function,
        'modifiers'   => (array) $methodsynopsis->modifier,
        'params'      => $params,
        'type'        => (string)$methodsynopsis->type,
        'desc'        => $funcOverload ? str_replace($function, $funcOverload, $desc) : $desc,
        'return_desc' => $return_desc,
    );
}

/* don't add a closing ?> here, we use this file in a benchmark as well */
