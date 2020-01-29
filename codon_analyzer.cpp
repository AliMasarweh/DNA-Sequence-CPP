//
// Created by ali-masa on 1/29/20.
//

#include "codon_analyzer.h"

using namespace std;
// should be inline??
bool CodonAnalyzer::isStartingCodon(std::string &codon) {
    static string startingCodon = "ATG";
    return codon == startingCodon;
}

bool CodonAnalyzer::isEndingCodon(std::string &codon) {
    static string endingCodon[] = { "TAG", "TAA", "TGA" };
    for (int i = 0; i < sizeof(endingCodon)/sizeof(endingCodon[0]); ++i) {
        if(endingCodon[i] == codon)
            return true;
    }
    return false;
}

bool CodonAnalyzer::isStartingCodon(const char *codon) {
    std::string str(codon);
    return isStartingCodon(str);
}

bool CodonAnalyzer::isEndingCodon(const char *codon) {
    std::string str(codon);
    return isEndingCodon(str);
}

