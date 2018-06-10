<?php
$br = (php_sapi_name() == "cli")? "":"<br>";

if(!extension_loaded('xfilter')) {
	dl('xfilter.' . PHP_SHLIB_SUFFIX);
}

use Cdoco\Filter;

$fr = new Filter(__DIR__ . '/blackword.dicxx');

$fr->save(['管理员','admin','你妈'], true);

$strContent = '你妈打撒杀死大家阿斯看管理得到顶管理员顶顶顶的dfdfkjdfkjkjdfjrtrtiayuewfjdjsjdfssakcvgadminretyyu速度思考坑';

echo "start memory=".memory_get_usage(true)."\n";date_default_timezone_set('Asia/Chongqing');
$test = array('a', 'abd', 'dad', 'admin', 'admin', 'word1f', 'cword1', 'cword1t');
foreach ($test as $v) {
	for ($i = 0;$i <= 10000; $i++) {
		$fr->search($v);
	}
}

echo "end memory=".memory_get_usage(true)."\n";
echo date('Y-m-d H:i:s');

// foreach ($arrRet as $v) {
// 	echo substr($strContent, $v[0], $v[1]) . "\n";
// }

?>
