#Compiler
CXX = g++

CFLAGS = -g -Wall -ansi
#CFLAGS = -O -Wall -ansi

OBJ = main.o scene.o clip.o frame.o scenemodel.o sceneview.o \
 scenecontroller.o consolesceneview.o

#goal all
all: prog
prog: $(OBJ)
	$(CXX) $(CFLAGS) -o prog $(OBJ)
clip.o: clip.cpp defines.h clip.h frame.h scene.h
consolesceneview.o: consolesceneview.cpp consolesceneview.h defines.h \
 sceneview.h scenemodel.h scene.h clip.h frame.h scenecontroller.h
frame.o: frame.cpp defines.h frame.h
main.o: main.cpp scenemodel.h defines.h scene.h clip.h frame.h \
 sceneview.h scenecontroller.h consolesceneview.h
scenecontroller.o: scenecontroller.cpp defines.h scenecontroller.h \
 scenemodel.h scene.h clip.h frame.h sceneview.h
scene.o: scene.cpp scene.h defines.h clip.h frame.h
scenemodel.o: scenemodel.cpp defines.h scenemodel.h scene.h clip.h \
 frame.h sceneview.h scenecontroller.h
sceneview.o: sceneview.cpp defines.h sceneview.h scenemodel.h scene.h \
 clip.h frame.h scenecontroller.h

#goal clean
clean: 
	-rm -v prog *.o *~

#make dist
dist: prog-1.0.tar.gz
prog-1.0.tar.gz: prog
	-rm -rf prog-1.0
	mkdir prog-1.0
	cp *.cpp *.h Makefile prog-1.0
	tar zcvf $@ prog-1.0
#clear dist
distclean:
	-rm -rf prog-1.0 prog-1.0.tar.gz
