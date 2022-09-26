CC = g++
FLAGS = -Wall -O2
OBJS = ATM.o ATMcontrol.o main.o

ATM.o : ATM.h ATM.cpp
	$(CC) $(FLAGS) -c ATM.cpp

ATMcontrol.o : ATMcontrol.h ATMcontrol.cpp
	$(CC) $(FLAGS) -c ATMcontrol.cpp

main.o : main.cpp ATM.h ATMcontrol.h
	$(CC) $(FLAGS) -c main.cpp

main : ATM.o ATMcontrol.o main.o
	$(CC) $(FLAGS) $(OBJS) -o main

.PHONY: clean
clean :
	rm -f $(OBJS) main
