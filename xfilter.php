<?php
$br = (php_sapi_name() == "cli")? "":"<br>";

if(!extension_loaded('xfilter')) {
	dl('xfilter.' . PHP_SHLIB_SUFFIX);
}

use Cdoco\Filter;

echo 'start memory=' . memory_get_usage(true) . "\n";

$content = '这是一个敏感词测试语句, 由高子航创造, xfilter, By ZiHang Gao。';
var_dump(Filter::setFileName(__DIR__ . '/blackword.dic'));

Filter::save(['敏感词', '高子航', 'xfilter']);
var_dump(Filter::delete('高子航'));

$rs = Filter::search($content);

foreach ($rs as $v) {
    echo substr($content, $v[0], $v[1]) . "\n";
}

echo 'end memory=' . memory_get_usage(true) . "\n";

?>
