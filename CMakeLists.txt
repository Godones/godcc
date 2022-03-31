cmake_minimum_required(VERSION 3.16)
project(godcc)

set(CMAKE_CXX_STANDARD 17)


aux_source_directory(. DIRSRCS)
include_directories(./ ./frontend ./backend ./IR ./log ./test)

set(FRONTEND ${PROJECT_SOURCE_DIR}/frontend)
set(lexer_path ${FRONTEND}/lexer.cpp)
set(parser_path ${FRONTEND}/parser.cpp)
set(parser_hpp_path ${FRONTEND}/parser.hpp)

if(EXISTS ${lexer_path})
  file(REMOVE ${lexer_path})
endif()
if (EXISTS ${parser_path})
  file(REMOVE ${parser_path})
endif ()
if (EXISTS ${FRONTEND}/parser.hpp)
  file(REMOVE ${FRONTEND}/parser.hpp)
endif ()

add_custom_command(
	OUTPUT ${parser_path} ${parser_hpp_path}
	COMMAND bison -d -o ${parser_path} ${FRONTEND}/sysy.y
	DEPENDS ${FRONTEND}/sysy.y
)
#SET_SOURCE_FILES_PROPERTIES(${lexer_path} GENERATED)
add_custom_command(
	OUTPUT ${lexer_path}
	COMMENT "Compiling lexer"
	COMMAND flex -o ../frontend/lexer.cpp ../frontend/sysy.l
	DEPENDS ${parser_hpp_path} ${FRONTEND}/sysy.l
)

#add_custom_target(LEXER ALL DEPENDS ${lexer_path})
#add_custom_target(PARSER ALL DEPENDS ${parser_path})
#add_dependencies(LEXER PARSER)

add_library(test STATIC
	test/Tparser.cpp
	log/log.cpp
	frontend/ast.cpp
	frontend/visitor.cpp
	IR/IR.cpp
	IR/irvisitor.cpp
	backend/asm.cpp
	json/json.cpp
	${parser_path}
	${lexer_path}
	)

#添加子目录
add_subdirectory(json)


# 生成可执行文件
add_custom_target(
	risc-v
	COMMAND riscv64-unknown-elf-gcc ../riscv/a.s -o ../riscv/a.out
)

add_custom_target(
	tree
	COMMAND cp test.json /mnt/d/2022.2-2022.7/Comiler/lab4
)
link_directories(${PROJECT_SOURCE_DIR}/googletest)
add_executable(main main.cpp)
target_link_libraries(main test)


