---
vim: wrap expandtab ft=markdown
layout: blog
tags: bash
title: Bash recipes
---

## Pipe

### How to suppress any output including errors

```bash
your-command >/dev/null 2>&1
```

### How to show the output in `stdout` and save it to file

```bash
ls | tee output.txt
```

### How to capture the exit status in a pipe

With `PIPESTATUS`, we can get the exit code in the pipe.

```bash
cat file.txt | tee; test ${PIPESTATUS[0]} -eq 0
```

## File

### How to tar files with split

```bash
tar tzpf - file1 file2 | split -b 4G - prefix.tar.gz.
```

## Execution

### How to show if a command success or failed

```bash
command >/dev/null 2>&1 && echo 'Success' || echo 'Failed'
```

## Script

### How to organize a utility script with usage and documentation

We can add comments before the definitions of commands, and use some keywords, like `Usage:`

```bash
#!/bin/bash

# list file in a column
# Usage: list [file ...]
list() {
	ls -1 $*
}
_help() {
	echo "Usage:"
	grep -B1 '^# Usage:' $0
}
_get_commands() {
	grep -A1 '^# Usage:' $0 | grep '() *{' | sed 's/(.*//g'
}
_main() {
	cmd=$1
	shift
	success=
	for c in `_get_commands`; do
		if [[ "$cmd" == "$c" ]]; then
			success=1
			$cmd $*
		fi
	done
	if [[ "$success" == "" ]];then
		_help
	fi
}
_main $*
```
