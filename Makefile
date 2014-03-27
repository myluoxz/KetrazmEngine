# Makefile for making dll
CC= g++
LIBNAME= Engine
DIR= lib/
SYSTEM= $(shell uname)
ifeq ($(SYSTEM), Linux)
LIB= -Iinclude -fPIC
else
BIN= bin/
LIB= -Iinclude -I/c/MinGW/tiers/include -L/c/MinGW/tiers/lib -lopengl32 -lglu32 -lglew32 -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lm
endif
FLAGS= -O3 -Wall -Werror -Wfatal-errors $(LIB)
SRC= GL.cpp Object.cpp Window.cpp Camera.cpp FreeCam.cpp PlayerCam.cpp ShaderProgram.cpp GLcontext.cpp Model.cpp OBJModel.cpp matrix.cpp
OBJ= $(SRC:%.cpp=obj/%.o)
IMPORT= -Wl,--out-implib,$(DIR)lib$(LIBNAME).a

all:	$(OBJ)
ifeq ($(SYSTEM), Linux)
	$(CC) -shared -o $(DIR)lib$(LIBNAME).so $^ $(FLAGS)
else
	$(CC) -shared -o $(BIN)$(LIBNAME).dll $^ $(FLAGS) $(IMPORT)
endif

obj/%.o:	%.cpp
	$(CC) -c -o $@ $^ $(FLAGS)

clean:	
	rm -f $(OBJ)
ifeq ($(SYSTEM), Linux)
	rm -f *~
	rm -f include/Engine/*~
	rm -f *#
	rm -f $(DIR)lib$(LIBNAME).so
else
	rm -f $(BIN)$(LIBNAME).dll $(DIR)lib$(LIBNAME).a
endif
