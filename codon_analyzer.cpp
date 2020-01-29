//
// Created by ali-masa on 1/29/20.
//

#include "codon_analyzer.h"

using namespace std;

string CodonAnalyzer::endingCodon[] = { "TAG", "TAA", "TGA" };
string CodonAnalyzer::startingCodon = "ATG";
size_t CodonAnalyzer::codonLength = 3;
// should be inline??
bool CodonAnalyzer::isStartingCodon(std::string &codon) {
    return codon == startingCodon;
}

bool CodonAnalyzer::isEndingCodon(std::string &codon) {
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

