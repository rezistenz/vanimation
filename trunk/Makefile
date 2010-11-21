################################################################################
#
#	make all
#
################################################################################

all:vanimation

vanimation: ./vanimation-qt4/vanimation-qt4
	cp ./vanimation-qt4/vanimation-qt4 ./vanimation

./vanimation-qt4/vanimation-qt4:  ./vanimation-qt4/Makefile
	cd vanimation-qt4 && \
	make && \
	cd ..
./vanimation-qt4/Makefile: ./vanimation-qt4/vanimation-qt4.pro
	cd vanimation-qt4 && \
	qmake && \
	cd ..


################################################################################
#
#	make clean
#
################################################################################

clean: vanimation-distclean
	-rm -v vanimation *~
vanimation-distclean:
	-cd vanimation-qt4 && \
	make distclean && \
	cd ..


################################################################################
#
#	make doc docclean
#
################################################################################

doc: clean Doxyfile
	doxygen
docclean:
	-rm -vr doc

################################################################################
#
#	make dist distclean
#
################################################################################

dist: vanimation-1.0.tar.gz
vanimation-1.0.tar.gz: clean
	-rm -vr vanimation-1.0
	mkdir vanimation-1.0
	cp --parent ./core/*.cpp ./core/*.h vanimation-1.0/
	cp --parent ./vanimation-qt4/*.cpp ./vanimation-qt4/*.h ./vanimation-qt4/vanimation-qt4.pro vanimation-1.0/
	cp --parent ./Doxyfile ./Makefile vanimation-1.0/
	tar zcvf $@ vanimation-1.0/
distclean:
	-rm -vr vanimation-1.0
	-rm -v vanimation-1.0.tar.gz
