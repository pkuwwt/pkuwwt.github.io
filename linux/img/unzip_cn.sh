#!/bin/bash

if (( $# < 1 ));then
	echo "USAGE: $0 input.zip [outdir]"
	exit 1
fi
CWD=`readlink -f .`
inputfile="`readlink -f "$1"`"

outdir="$CWD"
if (( $# >= 2 ));then
	outdir="$2"
fi

tmpdir="/tmp/unzip_cn-`date +%Y%m%d-%H%M%S`"
mkdir -p $tmpdir
cd $tmpdir

LANG=C 7za x "$inputfile"
convmv -f GBK -t utf8 --notest -r .
mv * "$outdir"

cd "$CWD"
