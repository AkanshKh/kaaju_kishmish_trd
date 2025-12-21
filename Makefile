projectName = iitg-icpc-trd

gen:
	xelatex -shell-escape -jobname=$(projectName) contents.tex
	xelatex -shell-escape -jobname=$(projectName) contents.tex
	xelatex combinatorics.tex
	xelatex combinatorics.tex
