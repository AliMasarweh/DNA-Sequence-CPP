cmake_minimum_required(VERSION 3.15)
project(DNA_Sequence)

set(CMAKE_CXX_STANDARD 98)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(testDNA_Sequence test_dnasequence.cpp dna_sequence.h dna_sequence.cpp nucleotide_analyzer.h nucleotide_analyzer.cpp codon_analyzer.h codon_analyzer.cpp)
target_link_libraries(testDNA_Sequence gtest gtest_main pthread)
