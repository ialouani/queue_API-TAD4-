cmake_minimum_required(VERSION 3.0)

# Notre projet est étiqueté hello
project(test_all)

# Crée des variables avec les fichiers à compiler
set(SRCS
    queue.c
    tests_API__queue.c
    )
    
set(HEADERS
    queue.h
    )

# On indique que l'on veut un exécutable "hello" compilé à partir des fichiers décrits par les variables SRCS et HEADERS
add_executable(test_all ${SRCS} ${HEADERS})
