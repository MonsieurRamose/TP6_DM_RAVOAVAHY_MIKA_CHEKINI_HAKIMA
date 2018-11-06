CC = g++
CCFLAGS= -Wall -pedantic -ggdb
EXTC = cpp
EXTH = h
EXECUTABLE = main

SRC = $(wildcard *.$(EXTC))
HDR = $(wildcard *.$(EXTH))
OBJ = $(SRC:.$(EXTC)=.o)
DEP = $(OBJ:.o=.d)

.PHONY: all vars clean

all: $(EXECUTABLE)

include $(DEP)

$(EXECUTABLE): $(OBJ)
	@$(CC) $(CCFLAGS) -o $@ $^


%.d: %.$(EXTC)
	@$(CC) $(CCFLAGS) -MM -o $@ -c $<

%.o: %.$(EXTC)
	@$(CC) $(CCFLAGS) -o $@ -c $<

vars:
	echo $(SRC)
	echo $(HDR)
	echo $(OBJ)
	echo $(DEP)

clean:
	rm -rf *.o
	rm -f $(EXECUTABLE)
	rm -rf *.d
