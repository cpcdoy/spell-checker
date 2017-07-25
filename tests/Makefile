CC=g++
CFLAGS= -g -std=gnu99 -pedantic -Wall -Wextra -Werror -fPIC
SRC=test_trie.cc
OBJ=$(SRC:%.c=%.o)
VPATH=. 

all:$(OBJ)
	$(CC) $(SRC) -o bin 
clean:
	${RM}
