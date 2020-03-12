#!/bin/bash
#
# pgf2pdf.sh
# Martin
# wwthunan@gmail.com
#

template='\documentclass{article} \usepackage{amsmath,amsfonts} \usepackage{mathptmx} \usepackage{tikz} \usepackage{color} \usepackage[active,pdftex,tightpage]{preview} \PreviewEnvironment[]{tikzpicture} \PreviewEnvironment[]{pgfpicture} \DeclareSymbolFont{symbolsb}{OMS}{cmsy}{m}{n} \SetSymbolFont{symbolsb}{bold}{OMS}{cmsy}{b}{n} \DeclareSymbolFontAlphabet{\mathcal}{symbolsb} \begin{document} <> \end{document}'

function get_dir(){
	cwd=`readlink -f $1`
	cwd=`dirname $cwd`
	echo $cwd
}

function process() {
    if ! [[ -f $1 ]];then
    	echo "ERROR:  file \"$1\" is not exist "
    	exit 1
    fi
    
    latexsrc="`echo $template | sed 's/<>/\\\\input\{test.pgf\}/g'`"
    tmpdir=/tmp/pgf2pdf-`date +%Y%m%d-%H%M%S`
    if ! [[ -d $tmpdir ]]; then
    	mkdir -p $tmpdir
    fi
    cp $1 $tmpdir/test.pgf
    
	cwd=`pwd`
    dir=`get_dir $1`
	file=`basename $1`
    echo $latexsrc >$tmpdir/test.tex
    cd $tmpdir
    pdflatex -shell-escape $tmpdir/test.tex
    mv $tmpdir/test.pdf $dir/${file%%.pgf}.pdf
	rm -rf $tmpdir
    cd $cwd
}

if (( $# < 1 )); then
	echo "USAGE: $0 file1.pgf [file2.pgf ...]"
	exit 1
fi

while (( $# > 0 ));do
	file=$1
	shift
	echo "================ processing $file ========================"
	process $file
done

