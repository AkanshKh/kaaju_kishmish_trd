#!/bin/bash

rm -f *.pdf #
python3 main.py > contents.tex #
make gen #
find . -type f -regextype posix-extended -regex '^.+\.(aux|toc|bcf|blg|bbl|log|xml|out)$' -delete #