all: clean trans.o 
	g++ -g -Wall -Wextra -o trans ../src/trans.o ../src/slre.o trans.o -lgtest -pthread -L./gtest/build

trans.o:
	g++ -lgtest -pthread -g -Wall -Wextra -o trans.o -c trans.cpp -I./gtest/include -I./gmock/include/

clean:
	rm -f *.o trans 
