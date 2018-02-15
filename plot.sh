#!/bin/bash
if [ $# -eq 0 ]
then
echo "Please pass an argument"
exit 1
fi


gnuplot<<EOF
set pm3d
set palette rgb 22,13,-31
set terminal postscript color
set output "$1.eps"
splot "$1.dat" with lines
EOF

open "$1".eps
exit 0

#set palette rgbformulae 22,13,-31