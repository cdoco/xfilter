<?php
$br = (php_sapi_name() == "cli")? "":"<br>";

if(!extension_loaded('xfilter')) {
	dl('xfilter.' . PHP_SHLIB_SUFFIX);
}

use Cdoco\Filter;

// $fr = new Filter(__DIR__ . '/blackword.dicxx');

// $fr->save(['管理员','admin','你妈'], true);

// $strContent = '你妈打撒杀死大家阿斯看管理得到顶管理员顶顶顶的dfdfkjdfkjkjdfjrtrtiayuewfjdjsjdfssakcvgadminretyyu速度思考坑';

// echo "start memory=".memory_get_usage(true)."\n";date_default_timezone_set('Asia/Chongqing');
// $test = array('a', 'abd', 'dad', 'admin', 'admin', 'word1f', 'cword1', 'cword1t');
// foreach ($test as $v) {
// 	for ($i = 0;$i <= 10000; $i++) {
// 		$fr->search($v);
// 	}
// }

// echo "end memory=".memory_get_usage(true)."\n";
// echo date('Y-m-d H:i:s');

// foreach ($arrRet as $v) {
// 	echo substr($strContent, $v[0], $v[1]) . "\n";
// }

// 构造方法里可以传入词典的路径
$fr = new Filter(__DIR__ . '/blackword.dic');

// 保存敏感词到字典文件中
$fr->save(['敏感词', '高子航', 'xfilter']);

// 搜索字符串中的敏感词 会返回敏感词的起始位置和长度
$rs = $fr->search('这是一个敏感词测试语句, 由高子航创造, xfilter, By ZiHang Gao。');

// use Cdoco\Filter;

$content = '这是一个敏感词测试语句, 由高子航创造, xfilter, By ZiHang Gao。';
$rs = (new Filter())->search($content);

foreach ($rs as $v) {
    echo substr($content, $v[0], $v[1]) . "\n";
}

?>
