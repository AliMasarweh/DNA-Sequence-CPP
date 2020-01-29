//
// Created by ali-masa on 1/29/20.
//

#ifndef DNA_SEQUENCE_CODON_ANALYZER_H
#define DNA_SEQUENCE_CODON_ANALYZER_H

#include <string>

class CodonAnalyzer{
public:
    static bool isStartingCodon(const char* codon);
    static bool isStartingCodon(std::string& codon);
    static bool isEndingCodon(const char* codon);
    static bool isEndingCodon(std::string& codon);

    static std::string startingCodon;
    static std::string endingCodon[];
};
#endif //DNA_SEQUENCE_CODON_ANALYZER_H
