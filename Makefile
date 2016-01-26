default:
	make clean
	make main
	make test

token.o: 	token.cpp token.h
	g++ -std=c++11 -c token.cpp

exceptions.o: 	exceptions.cpp exceptions.h
	g++ -std=c++11 -c exceptions.cpp

lexer.o: 	lexer.cpp lexer.h
	g++ -std=c++11 -c lexer.cpp

parser.o: 	parser.cpp parser.h
	g++ -std=c++11 -c parser.cpp

main: token.o exceptions.o main.cpp lexer.o parser.o
	g++ -std=c++11 main.cpp token.o exceptions.o lexer.o parser.o -o elc

test: token.o exceptions.o main.cpp lexer.o parser.o
	g++ -std=c++11 test-parser.cpp token.o exceptions.o lexer.o parser.o -o test
	./test

clean:
	rm -rf *.o elc .DS_Store ./Test_Cases/*.cpp
