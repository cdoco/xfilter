[![Build Status][travis-image]][travis-url]
![xfilter](https://img.shields.io/badge/branch-master-brightgreen.svg?style=flat-square)

> 关键词过滤扩展，用于检查一段文本中是否出现敏感词，基于 `Double-Array Trie` 树实现。

## 依赖环境

- PHP 7 +
- libdatrie (Version >= 0.2.4)

## 安装

因为本项目依赖于 `libdatrie`, 所以需要先安装 [libdatrie](https://github.com/tlwg/libdatrie), 再安装本扩展。

```shell
$ wget https://github.com/tlwg/libdatrie/releases/download/v0.2.11/libdatrie-0.2.11.tar.xz
$ tar zxvf libdatrie-0.2.11.tar.xz
$ cd libdatrie-0.2.11
$ ./configure && make && make install
```

PS: `libdatrie` 依赖于 `libiconv`, 如果编译的时候报 `undefined reference to libiconv`, 你需要先安装 `libiconv`。如果安装完还有错误可以执行这个命令 `./configure LDFLAGS=-L/usr/local/lib LIBS=-liconv`。

```shell
$ git clone https://github.com/cdoco/xfilter.git && cd xfilter
$ phpize && ./configure && make && make install
```

你可以在 `php.ini` 中设置字典文件的路径, 如果你不想在 `php.ini` 中设置你也可以在 `setFileName` 方法中设置。

```ini
[xfilter]
extension=xfilter.so

// 你可以在这里设置加载的字典文件路径
xfilter.filename=/path/to/xfilter/blackword.dic
```

## 示例

```php
<?php

use Cdoco\Filter;

// 这个方法里可以传入词典的路径或者在 php.ini 中设置
Filter::setFileName(__DIR__ . '/blackword.dic');

// 保存敏感词到字典文件中
Filter::save(['敏感词', '高子航', 'xfilter']);

// 搜索字符串中的敏感词 会返回敏感词的起始位置和长度
$rs = Filter::search('这是一个敏感词测试语句, 由高子航创造, xfilter, By ZiHang Gao。');

// Array
// (
//     [0] => Array
//         (
//             [0] => 12
//             [1] => 9
//         )
//
//     [1] => Array
//         (
//             [0] => 38
//             [1] => 9
//         )
//
//     [2] => Array
//         (
//             [0] => 55
//             [1] => 7
//         )
//
// )
print_r($rs);
```

## 方法

#### setFileName

该方法方法, 可以传入一个敏感词的字典文件路径。

```php
Filter::setFileName(string $filename);

// 示例
Filter::setFileName(__DIR__ . '/blackword.dic');
```

#### save

保存一个敏感词数组到字典文件中, 如果在 `setFileName` 方法中设置了路径, 会优先使用 `setFileName` 方法中的路径, 如果没有会使用 `php.ini` 中设置的 `xfilter.filename`。

```php
boolean Filter::save(array $blackword [, boolean $append = false]);

// 示例
Filter::save(['敏感词', '高子航', 'xfilter'], true);
```

`save` 方法有两个参数, 第一个参数 `$blackword` 是一个敏感词的数组, 第二个参数 `$append` 用来表示是否是追加写入。

```php
<?php

use Cdoco\Filter;

Filter::setFileName(__DIR__ . '/blackword.dic');

Filter::save(['xfilter']);
$rs = Filter::search('xfilter, By ZiHang Gao。');

// Array
// (
//     [0] => Array
//         (
//             [0] => 0
//             [1] => 7
//         )
//
// )
print_r($rs);

// 不设置 $append 参数 save 方法会重新建立一个文件
Filter::save(['cdoco']);
$rs = Filter::search('xfilter, By ZiHang Gao。');

// Array
// (
// )
print_r($rs);

// 如果设置了 $append 为 true, save 方法会在之前字典的基础上追加敏感词
Filter::save(['xfilter'], true);
$rs = Filter::search('cdoco, By ZiHang Gao。');

// Array
// (
//     [0] => Array
//         (
//             [0] => 0
//             [1] => 5
//         )
//
// )
print_r($rs);
```

#### search

搜索一个字符串中是否包含敏感词。

```php
array Filter::search(string $text);

// 示例
Filter::search('这是一个敏感词测试语句, 由高子航创造, xfilter, By ZiHang Gao。');
```

`search` 方法会返回一个二维数组, 包含敏感词出现的位置和长度, 你可以用 `substr` 方法截取出敏感词。

```php
Array
(
    [0] => Array
        (
            [0] => 0 //敏感词出现的位置
            [1] => 5 //敏感词的长度
        )

)

// 截取字符串
$content = '这是一个敏感词测试语句, 由高子航创造, xfilter, By ZiHang Gao。';
$rs = Filter::search($content);

foreach ($rs as $v) {
    echo substr($content, $v[0], $v[1]) . "\n";
}

// 敏感词
// 高子航
// xfilter
```

#### delete

删除字典文件中的敏感词。

```php
boolean Filter::delete(string $keyword);

// 示例
Filter::delete('高子航');
```

## License

PHP License. See the [LICENSE](LICENSE) file.

[travis-url]: https://travis-ci.org/cdoco/xfilter
[travis-image]: https://travis-ci.org/cdoco/xfilter.svg
