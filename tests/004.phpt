--TEST--
Check for xfilter save append parameter
--SKIPIF--
<?php if (!extension_loaded("xfilter")) print "skip"; ?>
--FILE--
<?php 
use Cdoco\Filter;

Filter::setFileName(__DIR__ . '/blackword.dic');

Filter::save(['xfilter']);
$rs = Filter::search('xfilter, By ZiHang Gao。');

print_r($rs);

// 不设置 $append 参数 save 方法会重新建立一个文件
Filter::save(['cdoco']);
$rs = Filter::search('xfilter, By ZiHang Gao。');

print_r($rs);

// 如果设置了 $append 为 true, save 方法会在之前字典的基础上追加敏感词
Filter::save(['xfilter'], true);
$rs = Filter::search('cdoco, By ZiHang Gao。');

print_r($rs);
?>
--EXPECT--
Array
(
    [0] => Array
        (
            [0] => 0
            [1] => 7
        )

)
Array
(
)
Array
(
    [0] => Array
        (
            [0] => 0
            [1] => 5
        )

)