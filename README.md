# xfilter

> 关键词过滤扩展，用于检查一段文本中是否出现敏感词，基于Double-Array Trie 树实现。

## Requirement

- PHP 7 +
- libdatrie (Version >= 0.2.4)

## Install

### libdatrie

```shell
$ wget https://github.com/tlwg/libdatrie/releases/download/v0.2.11/libdatrie-0.2.11.tar.xz
$ tar zxvf libdatrie-0.2.11.tar.xz
$ cd libdatrie-0.2.11
$ ./configure && make && make install
```

### php xfilter

```shell
$ git clone https://github.com/cdoco/xfilter.git && cd xfilter
$ phpize && ./configure && make && make install
```

## Quick Example

```php
use Cdoco\Filter;

// Construct.
$fr = new Filter(__DIR__ . '/blackword.dic');

// Save dirty words to file
$fr->save(['word1', 'word2', 'word3']);

// Dirty words in the search string
$fr->search('hello word2 word1');

// Array
// (
//     [0] => Array
//         (
//             [0] => 6
//             [1] => 5
//         )
//
//     [1] => Array
//         (
//             [0] => 12
//             [1] => 5
//         )
//
// )
```
