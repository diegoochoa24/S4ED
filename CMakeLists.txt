cmake_minimum_required(VERSION 3.28)
project(S4ED C)

set(CMAKE_C_STANDARD 11)

include_directories(practica9/src/app)
include_directories(practica9/src/core)
include_directories(practica9/src/core/file)
include_directories(practica9/src/core/heap)
include_directories(practica9/src/core/queue)
include_directories(practica9/src/core/printer)
include_directories(practica9/src/core/tree)
include_directories(practica9/src/util)

add_executable(S4ED9venti
        practica9venti/src/app/components.c
        practica9venti/src/app/components.h
        practica9venti/src/core/file/file.c
        practica9venti/src/core/file/file.h
        practica9venti/src/core/heap/heap.c
        practica9venti/src/core/heap/heap.h
        practica9venti/src/core/heap/priority.c
        practica9venti/src/core/queue/queue.c
        practica9venti/src/core/queue/queue.h
        practica9venti/src/core/tree/tree.c
        practica9venti/src/core/tree/tree.h
        practica9venti/src/util/const.h
        practica9venti/src/main.c
        practica9venti/src/core/printer/print_queue.c
        practica9venti/src/core/tree/tree_data.c
        practica9venti/src/core/queue/queue_data.c
        practica9venti/src/core/printer/print_queue.h
)

add_executable(S4ED9N
        practica9n/src/structs.h
        practica9n/src/functions.h
        practica9n/src/heap.c
        practica9n/src/main.c
        practica9n/src/heap.c
)

add_executable(S4ED10
        practica10/src/app/components.c
        practica10/src/app/components.h
        practica10/src/core/hash.c
        practica10/src/core/hash.h
        practica10/src/core/movie.c
        practica10/src/core/movie.h
        practica10/src/util/const.h
        practica10/src/main.c
)
