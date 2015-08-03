all: clean trans queryfilter utils

trans: trans.o
	g++ -g -Wall -Wextra -o trans ../src/trans.o ../src/slre.o trans.o -lgtest -pthread -L./gtest/build

queryfilter: queryfilter.o
	g++ -g -Wall -Wextra -o queryfilter ../src/queryfilter.o queryfilter.o -lgtest -pthread -L./gtest/build

utils: utils.o
	g++ -g -Wall -Wextra -o utils ../src/utils.o utils.o -lgtest -pthread -L./gtest/build

trans.o:
	g++ -lgtest -pthread -g -Wall -Wextra -o trans.o -c trans.cpp -I./gtest/include -I./gmock/include/

queryfilter.o:
	g++ -lgtest -pthread -g -Wall -Wextra -o queryfilter.o -c queryfilter.cpp -I./gtest/include -I./gmock/include/

utils.o:
	g++ -lgtest -pthread -g -Wall -Wextra -o utils.o -c utils.cpp -I./gtest/include -I./gmock/include/

clean:
	rm -f *.o trans queryfilter 
