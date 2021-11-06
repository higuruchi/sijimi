# sijimi

## PURPOSE

shllがどのように動くのかを知ることを目的として「sijimi」を作成しました。

### 実装した機能

- コマンドの実行

```
$ ls
test.txt
$ cat test.txt
hoge
fuga
hogefuga
fugafuga
hogefuga
```

- パイプ

```
$ cat test.txt | grep fuga
fuga
hogefuga
fugafuga
hogefuga
```
- リダイレクト

```
$ echo rararara > test1.txt
$ cat test1.txt
rararara
```

## Requirement

- gcc
- make

## Installation

```bash
$ git clone git@github.com:higuruchi/sijimi.git
$ cd ./sijimi/src
$ make run
```
## Usage

```bash
$ git clone git@github.com:higuruchi/sijimi.git
$ cd ./sijimi
$ docker build -t sijimi .
$ docker run -it --rm sijimi
```