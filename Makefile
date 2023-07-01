COMPILER = gcc
OUTPUT_FILE = bikeSharing
FLAGS = -pedantic -std=c99
OBJECT_FILES = main.o bikeRenting.o
DEBUG = -Wall -fsinitize=address

all: $(OBJECT_FILES)
	$(COMPILER) -o $(OUTPUT_FILE) $(OBJECT_FILES) $(FLAGS)

debug: COMPILER += $(DEBUG_COMPILER)
debug: all

main.o:
	$(COMPILER) -c main.c $(FLAGS)

bikeRenting.o:
	$(COMPILER) -c bikeRentingADT.c $(FLAGS)


clean: rm $(OUTPUT_FILE)
#cleanQueries:
#cleanAll: