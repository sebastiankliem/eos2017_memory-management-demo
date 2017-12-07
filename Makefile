CC = g++
OBJ = buddy.o BuddyAllocator.o LinkedList.o

buddy: $(OBJ)
	$(CC) -o buddy $(OBJ)

clean:
	rm -f buddy
	rm -f $(OBJ)
