CC = gcc
CXX = g++
src = $(wildcard ./fronted/*.cpp)


.PHONY:clean
run:main.cpp hello.c prebuild frontend/ast.cpp frontend/visitor.cpp
	@echo "Building..."
	$(CXX) main.cpp frontend/*.cpp -o build/main
	build/main -nochange hello.c -o hello.change

prebuild:
	flex -o frontend/lexer.lex.cpp frontend/sysy.l
	bison -d -o frontend/parser.tab.cpp frontend/sysy.y
    # 此时 bison 还会生成 `文件名.tab.hpp`

clean:
	rm build/*