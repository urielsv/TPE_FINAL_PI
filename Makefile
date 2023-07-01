COMPILER = gcc
FLAGS = -pedantic -std=c99
EXECS = main.c bikeSharing.c
DEBUG = -Wall -fsinitize=address

debug: COMPILER += $(DEBUG_COMPILER)
debug: all

all: $(COMPILER) -o $(OUTPUT_FILE) $(EXECS) $(FLAGS)

clean: rm $(OUTPUT_FILE)