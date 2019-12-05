OBJECTS = mp3_20140132.o
EXEC = mp3_20140132
FLAGS = -Wall
CFLAGS = -std=c++11
CC = g++

$(EXEC):$(OBJECTS)
	$(CC) $(FLAGS) -o  $(EXEC) $(OBJECTS)

mp3_20140132.o : mp3_20140132.cpp
	$(CC) $(CFLAGS) -c  mp3_20140132.cpp

clean: 
	rm -f mp3_20140132 mp3_20140132.o make_input a.out make_input.o result_* *.yy *.zz *.txt

