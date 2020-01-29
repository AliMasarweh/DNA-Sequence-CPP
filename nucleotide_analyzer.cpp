//
// Created by ali-masa on 1/29/20.
//

#include "nucleotide_analyzer.h"

bool NucleotideAnalyzer::isValidNucleotide(char nucleotide) {
    static char *validNucleotides = "ATGC";
    for (unsigned char i = 0; i < sizeof(validNucleotides); ++i) {
        if(validNucleotides[i] == nucleotide)
            return true;
    }
    return false;
}

