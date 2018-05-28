elc: token.o exceptions.o lexer.o parser.o ./src/elc.cpp
	@mkdir -p bin
	g++ -std=c++11 ./src/elc.cpp ./build/token.o ./build/exceptions.o ./build/lexer.o ./build/parser.o -o ./bin/elc

token.o: ./src/token.cpp ./include/token.h
	@mkdir -p build
	g++ -std=c++11 -c ./src/token.cpp -o ./build/token.o

exceptions.o: ./src/exceptions.cpp ./include/exceptions.h
	@mkdir -p build
	g++ -std=c++11 -c ./src/exceptions.cpp -o ./build/exceptions.o

lexer.o: ./src/lexer.cpp ./include/lexer.h
	@mkdir -p build
	g++ -std=c++11 -c ./src/lexer.cpp -o ./build/lexer.o

parser.o: ./src/parser.cpp ./include/parser.h
	@mkdir -p build
	g++ -std=c++11 -c ./src/parser.cpp -o ./build/parser.o

clean:
	@rm -rf ./build ./bin ./test/*.cpp && find ./test -iname main.cpp -exec rm {} +

tests: elc ./spike/tests.cpp
	@mkdir -p bin
	g++ -std=c++11 ./spike/tests.cpp -o ./bin/tests
