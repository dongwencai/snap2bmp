CC ?=gcc
CFLAG :=-g -Wall
SRC :=$(wildcard *.c)
OBJ :=$(SRC:%.c=%.o)
main:$(OBJ)
	$(CC) $(CFLAG) -o $@ $^ -lpthread -lm
$(OBJ):%.o:%.c
	$(CC) $(CFLAG) -c $^ -o $@
clean:
	rm -rf *.o main
