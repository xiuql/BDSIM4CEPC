#MOPT=--no-split
MOPT=

all: htmlmanual pdfmanual
                                                                               
htmlmanual: manual.texi
	makeinfo $(MOPT) --html manual.texi
pdfmanual:  manual.texi
	texi2pdf manual.texi
	rm -f *.aux *.cp *.fn *.toc *.pg *.ky *.log *.vr *.tp

clean:
	rm -f *.aux *.cp *.fn *.toc *.pg *.ky *.log *.vr *.tp \
	manual.pdf bdsim.html
