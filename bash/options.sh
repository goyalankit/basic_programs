#!/bin/bash

run(){
    echo "hello";
}


getFileName(){
    filename=$(basename "$1")
    extension="${filename##*.}"
    filename="${filename%.*}"

    echo "$filename"
}

clean(){
    echo "clean"
}

clr(){
    echo "clear"
}

gc(){

    filename=$(basename "$1")
    extension="${filename##*.}"
    filename="${filename%.*}"


    #    filename=$(getFileName($1))
    gcc $1 -o $filename.gcc
}


ic(){

    filename=$(basename "$1")
    extension="${filename##*.}"
    filename="${filename%.*}"

    icc -mno-sse $1 -o $filename.icc
}

case $1 in
    run) run $2;;
clean) clean;;
    clr) clr;;
gcc | gc | g) gc $2;;
    icc | ic | i) ic $2;;
help ) echo "Usage $0 {run|clean|clr|gcc|icc|icrun|gcrun}";;
    *) run $1;;
esac
