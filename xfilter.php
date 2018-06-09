<?php
$br = (php_sapi_name() == "cli")? "":"<br>";

if(!extension_loaded('xfilter')) {
	dl('xfilter.' . PHP_SHLIB_SUFFIX);
}

use Cdoco\Filter;

$fr = new Filter(__DIR__ . '/blackword.dic');

var_dump($fr->save(['word1', 'word2', 'word3']));

print_r($fr->search('hello word2 word1'));

?>
