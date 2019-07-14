CC := cc
CPP := c++
#TERM := -mwindows
#CFLAGS := -Wall $(TERM)
CFLAGS := -Wall
#INCLUDES := -I 
#LIBRARY := -L 
#LIBS := -l
SRCDIR := .
#SRC := $(wildcard $(SRCDIR)/*.c)
#OBJ := $(SRC:.c=.o)
SRC := $(wildcard $(SRCDIR)/*.cpp)
OBJ := $(SRC:.cpp=.o)

MAIN = Traffic_Lights.exe

.PHONY: all,clean

all: $(MAIN)
	@echo Done

$(MAIN):$(OBJ)
	$(CPP) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJ) $(LIBRARY) $(LIBS)

.c.o:
	$(CPP) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(SRCDIR)/*.o $(MAIN)
	@echo Clean