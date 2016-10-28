CC = g++
SRC = bitmap.cpp houghtrafo.cpp sobel.cpp motion.cpp main.cpp
OBJ = bitmap.o houghtrafo.o sobel.o motion.o main.o
OUT = dvat

$(OUT):	$(OBJ)
	$(CC) -g -o $(OUT) $(OBJ)


main.o:	main.cpp
	$(CC) -c -g main.cpp	 

bitamp.o: bitmap.cpp
	$(CC) -c -g bitmap.c

houghtrafo.o: houghtrafo.cpp
	$(CC) -c -g houghtrafo.cpp

sobel.o: sobel.cpp
	$(CC) -c -g sobel.cpp

motion.o: motion.cpp
	$(CC) -c -g motion.cpp




