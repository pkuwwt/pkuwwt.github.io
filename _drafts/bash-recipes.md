---
vim: wrap expandtab ft=markdown
layout: blog
tags: bash
title: Bash recipes
---

## Pipe

### How to capture the exit status in a pipe

With `PIPESTATUS`, we can get the exit code in the pipe.

```
cat file.txt | tee; test ${PIPESTATUS[0]} -eq 0
```

## File

### How to tar files with split

```
tar tzpf - file1 file2 | split -b 4G - prefix.tar.gz.
```
