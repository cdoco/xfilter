--TEST--
Check for xfilter __construct
--SKIPIF--
<?php if (!extension_loaded("xfilter")) print "skip"; ?>
--FILE--
<?php 
use Cdoco\Filter;

$fr = new Filter(__DIR__ . '/blackword.dic');
print_r($fr);
?>
--EXPECT--
Cdoco\Filter Object
(
)
