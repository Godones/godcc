cmake_minimum_required(VERSION 3.16)
project(godcc)

set(CMAKE_CXX_STANDARD 17)


aux_source_directory(. DIRSRCS)
include_directories(./ ./frontend ./backend ./IR ./log ./test)

set(FRONTEND ${PROJECT_SOURCE_DIR}/frontend)
set(lexer_path ${FRONTEND}/lexer.cpp)
set(parser_path ${FRONTEND}/parser.cpp)
set(parser_hpp_path ${FRONTEND}/parser.hpp)

if (EXISTS ${lexer_path})
    file(REMOVE ${lexer_path})
endif ()
if (EXISTS ${parser_path})
    file(REMOVE ${parser_path})
endif ()
if (EXISTS ${FRONTEND}/parser.hpp)
    file(REMOVE ${FRONTEND}/parser.hpp)
endif ()

add_custom_command(
        OUTPUT ${parser_path} ${parser_hpp_path}
        COMMAND bison -d -Wcounterexamples -o ${parser_path} ${FRONTEND}/sysy.y
        #	COMMAND bison -d ${FRONTEND}/sysy.y --graph
        #	COMMAND bison ${FRONTEND}/sysy.y -W
        DEPENDS ${FRONTEND}/sysy.y
)

add_custom_command(
        OUTPUT ${lexer_path}
        COMMENT "Compiling lexer"
        COMMAND flex -o ../frontend/lexer.cpp ../frontend/sysy.l
        DEPENDS ${parser_hpp_path} ${FRONTEND}/sysy.l
)


aux_source_directory(frontend FRONTENDCPP)

add_library(test STATIC
        test/Tparser.cpp
        tools/log.cpp
        IR/IR.cpp
        IR/irvisitor.cpp
        #		backend/asm.cpp
        tools/dot.cpp
        tools/symbolTable.cpp
        ${FRONTENDCPP}
        ${parser_path}
        ${lexer_path}
        )

#添加子目录
add_subdirectory(tools)


# 生成可执行文件
add_custom_target(
        risc-v
        COMMAND riscv64-unknown-elf-gcc ../riscv/a.s -o ../riscv/a.out
)

add_custom_target(
        tree
        #	COMMAND pytm-cli -i test.json -d TB -t 1
        COMMAND dot -Tpdf ast_Tree.dot -o ast_Tree.pdf
        #	COMMAND dot -Tsvg ast_Tree.dot -o ast_Tree.svg
        COMMAND dot -Tpdf cst_Tree.dot -o cst_Tree.pdf
        #	COMMAND dot -Tsvg cst_Tree.dot -o cst_Tree.svg
        COMMAND wslview ast_Tree.pdf && wslview cst_tree.pdf
)

add_executable(main main.cpp)
target_link_libraries(main test)


