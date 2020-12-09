OBJS := Hero.o JSON.o Monster.o main.o map.o game.o
CFLAGS := -std=c++17 -Wall -Wextra -g -lstdc++fs
CC:= g++-9
CPPCH := cppcheck
CPPFLAGS := --enable=warning --error-exitcode=2
CPPFSECFLAGS := --enable=performance,style --output-file=artifact_cppcheck.txt
VLGRND:= valgrind
VLGRNDFLAGS:= --leak-check=full --error-exitcode=3
VLGRNDJSONS:=  ./rpg scenario1.json
RUNCPP := Hero.cpp JSON.cpp Monster.cpp main.cpp map.cpp game.cpp

tests: rpg cppcheck_warnings cppcheck_style_and_performance valgrind_memory_leak_check correct_output_check

rpg: $(OBJS)
	$(CC) $(CFLAGS) -o rpg $(OBJS)

Hero.o: Hero.cpp Hero.h JSON.h Monster.h damage.h
	$(CC) $(CFLAGS) -c Hero.cpp

map.o: map.cpp map.h
	$(CC) $(CFLAGS) -c map.cpp

JSON.o: JSON.cpp JSON.h damage.h
	$(CC) $(CFLAGS) -c JSON.cpp

Monster.o: Monster.cpp Monster.h JSON.h damage.h
	$(CC) $(CFLAGS) -c Monster.cpp

game.o: game.cpp map.h Hero.h
	$(cc) $(CFLAGS) -c game.cpp
	
main.o: main.cpp JSON.h Hero.h Monster.h damage.h game.h
	$(CC) $(CFLAGS) -c main.cpp

cppcheck_warnings:
	$(CPPCH) $(RUNCPP) $(CPPFLAGS)

cppcheck_style_and_performance:
	$(CPPCH) $(RUNCPP) $(CPPFSECFLAGS)

valgrind_memory_leak_check:
	$(VLGRND) $(VLGRNDFLAGS) $(VLGRNDJSONS)

correct_output_check:
	python3 run_test.py

unittest:
	cd google_test && ./google_test_output

generate_documentation:
	doxygen doxconf