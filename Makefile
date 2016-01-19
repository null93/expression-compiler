default:
	make clean
	make main
	make tester

token.o: 	token.cpp token.h
	g++ -std=c++11 -c token.cpp

exceptions.o: 	exceptions.cpp exceptions.h
	g++ -std=c++11 -c exceptions.cpp

lexer.o: 	lexer.cpp lexer.h
	g++ -std=c++11 -c lexer.cpp

main: token.o exceptions.o main.cpp lexer.o
	g++ -std=c++11 main.cpp token.o exceptions.o lexer.o -o elc

tester:
	./elc Test_Cases/test01.el
	./elc Test_Cases/test02.el
	./elc Test_Cases/test03.el
	./elc Test_Cases/test04.el
	./elc Test_Cases/test05.el
	./elc Test_Cases/test10.el
	./elc Test_Cases/test11.el
	./elc Test_Cases/test12.el
	./elc Test_Cases/test13.el

clean:
	rm -rf *.o elc .DS_Store ./Test_Cases/*.cpp
