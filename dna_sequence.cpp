
//
// Created by ali-masa on 1/17/20.
//

#include "dna_sequence.h"
using namespace std;
using namespace dna_analyzer;

std::map<char,char> DNASequence::constructCounterpart(){
    std::map<char,char> m;
    m['A'] = 'T';
    m['T'] = 'A';
    m['G'] = 'C';
    m['C'] = 'G';
    return m;
}

const std::map<char,char> DNASequence::s_counterpartMapper
        =  DNASequence::constructCounterpart();

DNASequence::DNASequence(const char *dnaSeq):m_sequence(new string(dnaSeq)) {}

DNASequence::DNASequence(const std::string &dnaSeq):m_sequence(new string(dnaSeq)) {}

DNASequence::DNASequence(const DNASequence &dnaSequence)
        :m_sequence(new string(*dnaSequence.m_sequence)) {}

DNASequence &DNASequence::operator=(const DNASequence &dnaSequence) {
    if(this != &dnaSequence) {
        delete this->m_sequence;
        this->m_sequence = new string(*dnaSequence.m_sequence);
    }
    return *this;
}

DNASequence &DNASequence::operator=(const std::string &dnaSeq) {
    if(*this->m_sequence != dnaSeq) {
        delete this->m_sequence;
        this->m_sequence = new string(dnaSeq);
    }
    return *this;
}

DNASequence &DNASequence::operator=(const char *dnaSeq) {
    if(*this->m_sequence != dnaSeq) {
        delete this->m_sequence;
        this->m_sequence = new string(dnaSeq);
    }
    return *this;
}

DNASequence &DNASequence::theOtherStrand() {
    DNASequence ans(*this);
    for (int i = 0; i < this->m_sequence->size(); ++i) {
        ans.m_sequence->at(i) = DNASequence::s_counterpartMapper.at(ans.m_sequence->at(i));
    }

    return ans;
}

DNASequence::~DNASequence() {
    delete this->m_sequence;
}

size_t DNASequence::length() const {
    return this->m_sequence->size();
}

const char &DNASequence::operator[](size_t index) const {
    return this->m_sequence->at(index);
}

char DNASequence::operator[](size_t index) {
    return this->m_sequence->at(index);
}

std::ostream &operator<<(std::ostream &os, const DNASequence &dna) {
    os << dna.m_sequence;
    return os;
}

bool operator<(const DNASequence &dna1, const DNASequence &dna2) {
    return dna1.m_sequence < dna2.m_sequence;
}

bool operator>(const DNASequence &dna1, const DNASequence &dna2) {
    return dna2 > dna1;
}

bool operator==(const DNASequence &dna1, const DNASequence &dna2) {
    return !(dna1 < dna2 || dna1 > dna2);
}

bool operator!=(const DNASequence &dna1, const DNASequence &dna2) {
    return dna1 < dna2 ||dna1 > dna2;
}

bool operator<=(const DNASequence &dna1, const DNASequence &dna2) {
    return !(dna1 > dna2);
}

bool operator>=(const DNASequence &dna1, const DNASequence &dna2) {
    return !(dna1 < dna2);
}
