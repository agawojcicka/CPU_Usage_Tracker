cmake_minimum_required(VERSION 3.10)

project(CPU_Usage_Tracker)

if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
elseif (CMAKE_C_COMPILER_ID STREQUAL "Clang")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Waverything")
else()
	message(WARNING "please use gcc or clang compiler")
#endif()

set(CMAKE_C_STANDARD 99)
set(THREADS_PREFER_PTHREAD_FLAG ON)

add_executable(${PROJECT_NAME}
    source/main.c
	source/reader.c 
	source/reader.h 
	source/cpu_stat.h 
	source/queue.c
	source/queue.h
	source/global_var.h
	source/globar_var.c
	source/analyzer.h
	source/analyzer.c
	source/printer.c
	source/printer.h
)

find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)