CC=g++ -std=c++11
CFLAGS=-c -Wall

all: server.out client.out

server.out: Server.o CLI.o SocketIO.o PreProcess.o CLI_Data.o Command.o Command1.o Command2.o Command3.o Command4.o Command5.o ClientDisconnetedException.o Distances.o KNN.o
	$(CC) Server.o CLI.o SocketIO.o PreProcess.o CLI_Data.o Command.o Command1.o Command2.o Command3.o Command4.o Command5.o ClientDisconnetedException.o Distances.o KNN.o -lpthread -o server.out

client.out: client.o
	$(CC) client.o -lpthread -o client.out

ClientDisconnetedException.o: ClientDisconnetedException.cpp ClientDisconnetedException.h
	$(CC) $(CFLAGS) ClientDisconnetedException.cpp -o ClientDisconnetedException.o

Server.o: Server.cpp
	$(CC) $(CFLAGS) Server.cpp -o Server.o

client.o: Client.cpp
	$(CC) $(CFLAGS) Client.cpp -o client.o

SocketIO.o: SocketIO.cpp SocketIO.h DefaultIO.h
	$(CC) $(CFLAGS) SocketIO.cpp -o SocketIO.o

CLI_Data.o: CLI_Data.h CLI_Data.cpp
	$(CC) $(CFLAGS) CLI_Data.cpp -o CLI_Data.o

Distances.o: Distances.cpp Distances.h
	$(CC) $(CFLAGS) Distances.cpp -o Distances.o

Command.o: Command.h Command.cpp DefaultIO.h
	$(CC) $(CFLAGS) Command.cpp -o Command.o

Command1.o: Command1.h Command1.cpp
	$(CC) $(CFLAGS) Command1.cpp -o Command1.o

Command2.o: Command2.h Command2.cpp
	$(CC) $(CFLAGS) Command2.cpp -o Command2.o

Command3.o: Command3.h Command3.cpp
	$(CC) $(CFLAGS) Command3.cpp -o Command3.o

Command4.o: Command4.h Command4.cpp
	$(CC) $(CFLAGS) Command4.cpp -o Command4.o

Command5.o: Command5.h Command5.cpp
	$(CC) $(CFLAGS) Command5.cpp -o Command5.o

CLI.o: CLI.h CLI.cpp
	$(CC) $(CFLAGS) CLI.cpp -o CLI.o

KNN.o: KNN.cpp KNN.h
	$(CC) $(CFLAGS) KNN.cpp -o KNN.o

PreProcess.o: PreProcess.cpp PreProcess.h
	$(CC) $(CFLAGS) PreProcess.cpp -o PreProcess.o

clean:
	rm -rf *.o server client
