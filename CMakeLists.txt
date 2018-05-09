cmake_minimum_required(VERSION 3.0)
project(bfi C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_VERBOSE_MAKEFILE on)

include_directories(/usr/include/readline)
set(CMAKE_C_FLAGS "-lreadline")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")


include_directories(src)

add_executable(bfi
        src/brainfuck.h
        src/compress.c
        src/compress.h
        src/err_lib.c
        src/err_lib.h
        src/execute.c
        src/execute.h
        src/file_reader.c
        src/file_reader.h
        src/help.h
        src/lib-ttycolor.c
        src/lib-ttycolor.h
        src/lib_args.c
        src/lib_args.h
        src/lib_files.c
        src/lib_files.h
        src/lib_inter.c
        src/lib_inter.h
        src/main.c
        src/mem_lib.c
        src/mem_lib.h
        src/warn_lib.c
        src/warn_lib.h)

target_link_libraries(bfi readline)

install(TARGETS bfi
        RUNTIME DESTINATION bin)

install(FILES man/bfi.1 DESTINATION /usr/share/man/man1)