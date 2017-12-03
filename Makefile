CC = g++
CFLAGS = -Wall -c
LFLAGS = -Wall
OBJS = stem.o main.o parse.o except.o tfidf.o readlevel.o
INCLUDE = -I.

PA7 : $(OBJS)
	$(CC) $(OBJS) $(LFLAGS) $(INCLUDE) -o PA8

stem.o : stem.cpp stem.h
	$(CC) stem.cpp $(INCLUDE) $(CFLAGS)

parse.o : parse.cpp parse.h
	$(CC) parse.cpp $(INCLUDE) $(CFLAGS)

except.o : except.cpp except.h
	$(CC) except.cpp $(INCLUDE) $(CFLAGS)

tfidf.o : tfidf.cpp tfidf.h
	$(CC) tfidf.cpp $(INCLUDE) $(CFLAGS)

readlevel.o : readlevel.cpp readlevel.h
	$(CC) readlevel.cpp $(INCLUDE) $(CFLAGS)

main.o : main.cpp
	$(CC) main.cpp $(INCLUDE) $(CFLAGS)

clean :
	-rm *.o PA8
