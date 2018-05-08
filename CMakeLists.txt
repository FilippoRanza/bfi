cmake_minimum_required(VERSION 3.11)
project(bfi C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS  '-lreadline')

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

install(TARGETS bfi
        RUNTIME DESTINATION bin)

set(MAN_NAMES bfi.1)
set(MAN_FILES)
foreach(m IN LISTS MAN_NAMES)
    set(mf ${CMAKE_BINARY_DIR}/${m})
    set(ms ${CMAKE_SOURCE_DIR}/${m}.txt)
    add_custom_command(OUTPUT ${mf}
            COMMAND ${A2X_EXECUTABLE} ${A2X_OPTS} ${ms}
            DEPENDS ${ms}
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMENT "Building manpage ${mf}"
            VERBATIM)
    list(APPEND MAN_FILES ${mf})
endforeach()

add_custom_target(man ALL DEPENDS ${MAN_FILES})