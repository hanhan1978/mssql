all: clean unit_test.o 
	g++ -g -Wall -Wextra -o unit_test ../src/trans.o ../src/slre.o unit_test.o -lgtest -pthread -L./gtest/build

unit_test.o:
	g++ -lgtest -pthread -g -Wall -Wextra -o unit_test.o -c trans.cpp -I./gtest/include -I./gmock/include/

clean:
	rm -f *.o unit_test 
