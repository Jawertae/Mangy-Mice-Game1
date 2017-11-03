#OBJS specifies which files to compile as part of the project
OBJS = main.cpp actor.cpp

#CC specifies which compiler we're using
CC = g++
WCC = i686-w64-mingw32-g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w
WIN_FLAGS = -w -mwindows

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = p.hawthorne
WIN_NAME = hawthorne.exe

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
win : $(OBJS)
	$(WCC) $(OBJS) $(WIN_FLAGS) $(LINKER_FLAGS) -o $(WIN_NAME)
