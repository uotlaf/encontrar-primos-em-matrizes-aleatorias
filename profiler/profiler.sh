#!/bin/bash

gprof build/debug/main gmon.out > report.txt
gprof2dot report.txt > report.dot	
dot -Tpng -o profile.png report.dot
xdg-open profile.png