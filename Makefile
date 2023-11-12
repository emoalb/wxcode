CC = g++
CFLAGS = -g -Wall
SRCS = image_viewer.cpp
PROG = image_viewer

OPENCV = `pkg-config opencv4 --cflags --libs`
WXCONFIG = `wx-config --cxxflags --libs --gl-libs`
OPENGL = -lGL -lGLU -lglut
LIBS = $(OPENCV) $(WXCONFIG) $(OPENGL)

all: main

main: about_dialog.o image_viewer.o
	$(CC) $(CFLAGS) *.o -o $(PROG) $(LIBS) -I/usr/local/include/opencv4

about_dialog.o: about_dialog.cpp about_dialog.h
	$(CC) $(CFLAGS) -o about_dialog.o -c about_dialog.cpp $(LIBS) -I/usr/local/include/opencv4

image_viewer.o: image_viewer.cpp about_dialog.h
	$(CC) $(CFLAGS) -o image_viewer.o  -c $(SRCS) $(LIBS) -I/usr/local/include/opencv4

