#OBJS specifies which files to compile as part of the project
MAIN = main.cpp
OTHERS = actor.cpp debug.cpp globals.cpp
OBJS = $(MAIN) $(OTHERS)
#COBJS is a list of compiled, unlinked object files
COBJS = $(OBJS:.cpp=.o)

#CC specifies which compiler we're using
CC = g++
#WCC specifies the mingw compiler for windows targets
WCC = i686-w64-mingw32-g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
# -std=c++11 configures the standard for the compiler to use
COMPILER_FLAGS = -w -std=c++11
DEBUG_FLAGS = $(COMPILER_FLAGS) -D DEBUG -g
WIN_FLAGS = $(COMPILER_FLAGS) -mwindows

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = p_hawthorne
WIN_NAME = hawthorne.exe

.PHONY : clean scratch cleanall

#This is the target that compiles our executable
all : link
#	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
win : $(OBJS)
	$(WCC) $(OBJS) $(WIN_FLAGS) $(LINKER_FLAGS) -o $(WIN_NAME)
$(MAIN:.cpp=.o) : %.o : $(MAIN) $(OTHERS:.cpp=.h)
	$(CC) $< $(COMPILER_FLAGS) -c -o $@ 
$(OTHERS:.cpp=.o) : %.o : %.cpp %.h globals.h
	$(CC) $< $(COMPILER_FLAGS) -c -o $@
$(MAIN:.cpp=_d.o) : %_d.o : $(MAIN) $(OTHERS:.cpp=.h)
	$(CC) $< $(DEBUG_FLAGS) -c -o $@ 
$(OTHERS:.cpp=_d.o) : %_d.o : %.cpp %.h globals.h
	$(CC) $< $(DEBUG_FLAGS) -c -o $@ 


nolink : $(OBJS) $(COBJS)
debugnolink : $(OBJS) $(OBJS:_d.o)

link : $(OBJS) $(COBJS)
	$(CC) $(COBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME) 
scratch : cleanall
clean :
	rm -v -f *.o
cleanall :
	rm -v -f *.o $(OBJ_NAME) $(OBJ_NAME)_debug
debug : $(OBJS:.cpp=_d.o)
	$(CC) $(OBJS:.cpp=_d.o) $(LINKER_FLAGS) -o $(OBJ_NAME)_debug
