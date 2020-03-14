---
vim: wrap expandtab ft=markdown
layout: blog
comments: true
tags: sqlite3 linux
title: How to show Sqlite3 outout as Man page table
---

## Why to use man page?

The output format of Sqlite3 sucks. For example, too many rows, too long rows. Although there are `-html` and `-csv` format, why should I use them if I only want to view the first few rows just like PostgreSQL?

In PostgreSQL prompt, it is always a happy experience to view the query results in a `less`-like interface. I view the first few rows, and press `q` to quit without messing up with the interface.

## How to implement it?

The first words come to a linuxer's mind should be: `terminal`, `less` and `table`.

We know the *manpage* has table format, so we may try to convert the sqlite3 query results to *manpage*, i.e. the `groff` format.

After a few searching, I found that the table in man page is actually related to a format or program called [`tbl`](https://linux.die.net/man/1/tbl). There is no sample code to start with, so I read the original report [Tbl - A Program to Format Tables](http://doc.cat-v.org/unix/v10/10thEdMan/tbl.pdf) and get the following example

![](../img/tbl.jpg)

Given a file `table.txt`

```
.TS
.box;
c c c
l l r.
Fact	Location	Statistics

Largest state	Alaska	591,004 sq. mi.
.TE
```

we can show the table with the following commands

```
tbl table.txt | groff -T ascii -man - | less -S
cat table.txt | tbl - | groff -T ascii -man - | less -S
```

I won't explain these commands, because I don't know and just try them out.

What really matters is I find out how to display a text-represented table in the terminal.

The table rows are just `TAB`-separated lines between `.TS` and `.TE`.

Oh, there are also options like `.box;`, `c c c` and `l l r.`. I guess `c c c` is the format of the header, and 
`l l r.` is the format of the rows of table body. There are `3` columns obviously.

And the final script is
```
# usage:
# sqlite3 -header db.sqlite 'select * from sqlite_master;' | sqlite_to_man
sqlite_to_man() {
	{
		echo ".TS"
		echo "box;"
		first=
		while read line; do
			if [[ $first- == "-" ]]; then
				echo $line | awk 'BEGIN{FS="|";ORS="";}{for (i=1;i<NF;++i) {print "c | "} print "c\n"}'
				echo $line | awk 'BEGIN{FS="|";ORS="";}{for (i=1;i<NF;++i) {print "c | "} print "c.\n"}'
				first=true
			fi
			echo $line | sed "s/|/\t/g"
		done
		echo ".TE"
	} | tbl - | groff -man -T ascii $1 | less -S
}
```

You may have noticed that I replace the default separator `|` to `TAB`, and add row formats before the first line.

## Limitation

The above script ignore the fact that there may be strings container newlines, and the speed is not very satisfactory.

Maybe I need to use the `csv` output format, and write another python script based on `pydoc`.

