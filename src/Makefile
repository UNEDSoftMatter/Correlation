CC       := gcc 
LIBS     := -lm -lblas -llapack -Wall -lgsl -lgslcblas -fopenmp -lfftw3 -O2 
DEBUGGER := -O0 -ggdb
FLAGS    := -std=gnu99
TARGET   := ./../correlation
OBJS     := correlation.c.o io.c.o

.SUFFIXES: .c .o  

.PHONY: clean 

%.c.o: %.c 
	$(CC) -c $< -o $@ $(LIBS) $(FLAGS)

$(TARGET): $(OBJS) 
	$(CC) -o $(TARGET) $(OBJS) $(LIBS) $(FLAGS)

all: $(TARGET) 

clean:
	rm *.o $(TARGET)
