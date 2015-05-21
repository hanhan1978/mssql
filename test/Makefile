all: clean unit_test.o 
	g++ -std=c++11 -g -Wall -Wextra -o unit_test ../src/trans.o ../src/slre.o unit_test.o -lgtest -pthread -L./gtest/build

unit_test.o:
	g++ -lgtest -std=c++11 -pthread -g -Wall -Wextra -o unit_test.o -c trans.cpp -I./gtest/include

clean:
	rm -f *.o unit_test 
