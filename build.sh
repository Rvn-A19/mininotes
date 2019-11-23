#!/bin/bash

files_to_remove=`ls -A | grep -v -e *.cc -e *.pro -e $0 -e README.md`

if [ "$files_to_remove" ]; then
  rm $files_to_remove
fi

if [ "$1" == "clean" ]; then
  exit 0
fi

qmake && make

