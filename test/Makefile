all: clean queryfilter utils

queryfilter: queryfilter.o
	g++ -g -Wall -Wextra -o queryfilter ../src/queryfilter.o queryfilter.o -lgtest -pthread -L./gtest/build

utils: utils.o
	g++ -g -Wall -Wextra -o utils ../src/utils.o utils.o -lgtest -pthread -L./gtest/build

queryfilter.o:
	g++ -lgtest -pthread -g -Wall -Wextra -o queryfilter.o -c queryfilter.cpp -I./gtest/include -I./gmock/include/

utils.o:
	g++ -lgtest -pthread -g -Wall -Wextra -o utils.o -c utils.cpp -I./gtest/include -I./gmock/include/

clean:
	rm -f *.o utils queryfilter 
