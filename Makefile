CC = gcc
CXX = g++

F = frontend

frontend = $(F)/ast.cpp $(F)/visitor.cpp
Ir = IR/*.cpp
OUT = build/main
OBJ =  build/parser.o build/lexer.o build/log.o build/test.o
SCANNER= sysy.l
PARSER= sysy.y

.PHONY:clean


build:$(OUT)

run:build
	build/main -token hello.c -o build/scanner_example.tokens
$(OUT): $(OBJ) $(Ir)
	@echo "Compiling..."
	$(CXX) -o $(OUT) main.cpp $(OBJ) $(frontend)  $(Ir)


build/lexer.o: frontend/lexer.cpp
	@echo "Compiling lexer..."
	$(CXX) -c frontend/lexer.cpp -o build/lexer.o
build/parser.o: frontend/parser.cpp
	@echo "Compiling parser..."
	$(CXX) -c frontend/parser.cpp -o build/parser.o
build/log.o: log/log.cpp
	@echo "Compiling log..."
	$(CXX) -c log/log.cpp -o build/log.o
build/test.o: test/Tparser.cpp
	@echo "Compiling test..."
	$(CXX) -c test/Tparser.cpp -o build/test.o

frontend/lexer.cpp: frontend/sysy.l
	flex -o frontend/lexer.cpp frontend/sysy.l

frontend/parser.cpp: frontend/sysy.y
	bison -d -o frontend/parser.cpp frontend/sysy.y


test:build

clean:
	rm build/*