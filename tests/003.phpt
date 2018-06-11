--TEST--
Check for xfilter save and search
--SKIPIF--
<?php if (!extension_loaded("xfilter")) print "skip"; ?>
--FILE--
<?php 
use Cdoco\Filter;

Filter::setFileName(__DIR__ . '/blackword.dic');

// save
Filter::save(['敏感词', '高子航', 'xfilter']);

// search
$rs = Filter::search('这是一个敏感词测试语句, 由高子航创造, xfilter, By ZiHang Gao。');

print_r($rs);
?>
--EXPECT--
Array
(
    [0] => Array
        (
            [0] => 12
            [1] => 9
        )

    [1] => Array
        (
            [0] => 38
            [1] => 9
        )

    [2] => Array
        (
            [0] => 55
            [1] => 7
        )

)
