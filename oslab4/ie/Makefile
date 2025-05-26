CC = gcc
CFLAGS = -g

all: agent smoker

agent: agent.o ipc_smoke.o
	$(CC) $(CFLAGS) -o agent agent.o ipc_smoke.o

smoker: smoker.o ipc_smoke.o
	$(CC) $(CFLAGS) -o smoker smoker.o ipc_smoke.o

agent.o: agent.c ipc_smoke.h
	$(CC) $(CFLAGS) -c agent.c

smoker.o: smoker.c ipc_smoke.h
	$(CC) $(CFLAGS) -c smoker.c

ipc_smoke.o: ipc_smoke.c ipc_smoke.h
	$(CC) $(CFLAGS) -c ipc_smoke.c

clean:
	rm -f *.o agent smoker

