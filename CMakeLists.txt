cmake_minimum_required(VERSION 3.5)

project(C-Chest)

aux_source_directory(. DIR_SRCS)

add_executable(C-Chest ${DIR_SRCS})
