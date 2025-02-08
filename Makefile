CC = mpicc
CFLAGS = -Wall -O2
SRC = src/main.c src/utils.c
OUT = rollouts

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT)
