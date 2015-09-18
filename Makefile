COMPILER = gcc
CCFLAGS = -Wall -g


ifeq ($(DEBUG), TRUE)
CCFLAGS += -g
endif

make: tokenizer.c
	$(COMPILER) $(CCFLAGS) -o tokenizer tokenizer.c
	
clean: 
	rm -f tokenizer
	rm -f *o 
