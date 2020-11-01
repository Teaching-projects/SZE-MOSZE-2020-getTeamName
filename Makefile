OBJS := creature.o JsonParser.o main.o
CFLAGS := -std=c++17 -Wall -Wextra -g
CC := g++
CPPCH := cppcheck
CPPFLAGS := --enable=warning --error-exitcode=2
CPPFSECFLAGS := --enable=performance,style --output-file=artifact_cppcheck.txt
VLGRND:= valgrind
VLGRNDFLAGS:= --leak-check=full --error-exitcode=3
VLGRNDJSONS:=  ./rpg Units/Kakarott.json Units/Maple.json
RUNCPP := creature.cpp JsonParser.cpp main.cpp

tests: rpg cppcheck_warnings cppcheck_style_and_performance valgrind_memory_leak_check correct_output_check

rpg: $(OBJS)
	$(CC) $(CFLAGS) -o rpg $(OBJS)

creature.o: creature.cpp creature.h JsonParser.h BadJsonException.h
	$(CC) $(CFLAGS) -c creature.cpp

JsonParser.o: JsonParser.cpp JsonParser.h BadJsonException.h
	$(CC) $(CFLAGS) -c JsonParser.cpp

main.o: main.cpp creature.h JsonParser.h BadJsonException.h
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