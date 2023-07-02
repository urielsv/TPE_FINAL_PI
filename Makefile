COMPILER = gcc
OUTPUT_FILES = bikeSharingMON bikeSharingNYC
FLAGS = -pedantic -std=c99
OBJECT_FILES = main.o bikeSharingADT.o dataProcessing.o
DEBUG = -Wall -fsinitize=address

all: clean mon nyc

debug: COMPILER += $(DEBUG_COMPILER)
debug: all

mon: $(OBJECT_FILES)
	$(COMPILER) -o bikeSharingMON $(OBJECT_FILES) $(FLAGS)

nyc: $(OBJECT_FILES)
	$(COMPILER) -o bikeSharingNYC $(OBJECT_FILES) $(FLAGS)

main.o: main.c
	$(COMPILER) -c main.c $(FLAGS)

bikeSharingADT.o: bikeSharingADT.o
	$(COMPILER) -c bikeSharingADT.c $(FLAGS)

dataProcessing.o: dataProcessing.c
	$(COMPILER) -c dataProcessing.c $(FLAGS)

clean:
	rm -f $(OUTPUT_FILES) $(OBJECT_FILES)
	@echo "Makefile: Object files and output files deleted."
#cleanQueries:
#cleanAll: