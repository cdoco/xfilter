--TEST--
Check for xfilter __construct
--SKIPIF--
<?php if (!extension_loaded("xfilter")) print "skip"; ?>
--FILE--
<?php 
use Cdoco\Filter;

var_dump(Filter::setFileName(__DIR__ . '/blackword.dic'));
?>
--EXPECT--
bool(true)
