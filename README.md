# sijimi

## Purpose

I created "sijimi" for the purpose of knowing how shll works.

## Implemented function

- execute

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

- pipe

  ```
  $ cat test.txt | grep fuga
  fuga
  hogefuga
  fugafuga
  hogefuga
  ```
- redirect

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
