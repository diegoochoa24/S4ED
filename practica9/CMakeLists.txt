cmake_minimum_required(VERSION 3.28)
project(S4ED C)

set(CMAKE_C_STANDARD 11)

include_directories(src/app)
include_directories(src/core)
include_directories(src/core/file)
include_directories(src/core/heap)
include_directories(src/core/queue)
include_directories(src/core/tree)
include_directories(src/util)

add_executable(S4ED
        src/app/components.c
        src/app/components.h
        src/core/file/file.c
        src/core/file/file.h
        src/core/heap/heap.c
        src/core/heap/heap.h
        src/core/heap/priority.c
        src/core/queue/queue.c
        src/core/queue/queue.h
        src/core/tree/tree.c
        src/core/tree/tree.h
        src/util/const.h
        src/main.c
        src/core/printer/print_queue.c
        src/core/tree/tree_data.c
        src/core/queue/queue_data.c
        src/core/printer/print_queue.h)
