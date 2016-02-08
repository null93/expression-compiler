# Misc. Tasks

default:
	make clean
	make elc
	make test

clean:
	rm -rf *.o elc .DS_Store ./Tests-Parser/*.cpp

# Compile Objects

token.o: 	token.cpp token.h
	g++ -std=c++11 -c token.cpp

exceptions.o: 	exceptions.cpp exceptions.h
	g++ -std=c++11 -c exceptions.cpp

lexer.o: 	lexer.cpp lexer.h
	g++ -std=c++11 -c lexer.cpp

parser.o: 	parser.cpp parser.h
	g++ -std=c++11 -c parser.cpp

# Compile EL Compiler

elc: token.o exceptions.o elc.cpp lexer.o parser.o
	g++ -std=c++11 elc.cpp token.o exceptions.o lexer.o parser.o -o elc

# Test Out EL Compiler

test:
	./elc ./Tests/test01.el
	./elc ./Tests/test02.el
	./elc ./Tests/test03.el
	./elc ./Tests/test04.el
	./elc ./Tests/test05.el
	./elc ./Tests/test06.el
	./elc ./Tests/test07.el
	./elc ./Tests/test10.el
	./elc ./Tests/test11.el
	./elc ./Tests/test12.el
	./elc ./Tests/test13.el
	./elc ./Tests/test14.el
	./elc ./Tests/test15.el
	./elc ./Tests/test16.el
	./elc ./Tests/test17.el
	./elc ./Tests/test18.el
	./elc ./Tests/test19.el
	./elc ./Tests/test20.el
	./elc ./Tests/test21.el
	./elc ./Tests/test22.el