CC = gcc
CXX = g++

F = frontend

frontend = $(F)/ast.cpp $(F)/visitor.cpp
Ir = IR/*.cpp
OUT = build/main
OBJ = build/lexer.lex.o build/parser.tab.o build/log.o build/test.o
SCANNER= sysy.l
PARSER= sysy.y

.PHONY:clean


build:$(OUT)

run:build
	build/main -token hello.c -o build/scanner_example.tokens
$(OUT): $(OBJ) frontend $(Ir)
	@echo "Compiling..."
	$(CXX) -o $(OUT) main.cpp $(OBJ) $(frontend)  $(Ir)


build/lexer.lex.o: frontend/lexer.lex.cpp
	@echo "Compiling lexer..."
	$(CXX) -c frontend/lexer.lex.cpp -o build/lexer.lex.o
build/parser.tab.o: frontend/parser.tab.cpp
	@echo "Compiling parser..."
	$(CXX) -c frontend/parser.tab.cpp -o build/parser.tab.o
build/log.o: log/log.cpp
	@echo "Compiling log..."
	$(CXX) -c log/log.cpp -o build/log.o
build/test.o: test/Tparser.cpp
	@echo "Compiling test..."
	$(CXX) -c test/Tparser.cpp -o build/test.o

clean:
	rm build/*