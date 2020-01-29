
//
// Created by ali-masa on 1/17/20.
//

#include "dna_sequence.h"
#include <bits/stdc++.h>

using namespace std;

map<char,char> DNASequence::constructCounterpart(){
    map<char,char> m;
    m['A'] = 'T';
    m['T'] = 'A';
    m['G'] = 'C';
    m['C'] = 'G';
    return m;
}

const map<char,char> DNASequence::s_counterpartMapper
        =  DNASequence::constructCounterpart();

DNASequence::DNASequence(const char *dnaSeq): m_sequence(new string(dnaSeq)) {
    if(!this->validSequence()){
        delete this->m_sequence;
        throw InvalidNucleotideDNASequence();
    }
}


DNASequence::DNASequence(const string &dnaSeq):m_sequence(new string(dnaSeq)) {
    if(!this->validSequence()){
        delete this->m_sequence;
        throw InvalidNucleotideDNASequence();
    }
}

DNASequence::DNASequence(const DNASequence &dnaSequence)
        :m_sequence(new string(*dnaSequence.m_sequence)) {}

DNASequence &DNASequence::operator=(const DNASequence &dnaSequence) {
    if(this != &dnaSequence) {
        delete this->m_sequence;
        this->m_sequence = new string(*dnaSequence.m_sequence);
    }
    return *this;
}

DNASequence &DNASequence::operator=(const string &dnaSeq) {
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

DNASequence DNASequence::theOtherStrand() const {
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

ostream &operator<<(ostream &os, const DNASequence &dna) {
    os << * dna.m_sequence;
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

bool DNASequence::validSequence() const {
    for (int i = 0; i < this->m_sequence->length(); ++i) {
        if(!NucleotideAnalyzer::isValidNucleotide(this->m_sequence->at(i)))
            return false;
    }

    return true;
}

DNASequence DNASequence::slice(size_t startingIndx) const {
    return DNASequence(m_sequence->substr(startingIndx));
}

DNASequence DNASequence::slice(size_t startingIndx, size_t endingIndx) const {
    if(endingIndx <= startingIndx)
        throw InvalidIndexesSlicingDNASequence();
    if(startingIndx < 0 || endingIndx > m_sequence->length())
        throw OutOfBoundsSlicingDNASequence();
    return DNASequence(m_sequence->substr(startingIndx, endingIndx));
}

DNASequence DNASequence::pairing() const {
    DNASequence tmp = this->theOtherStrand();
    reverse(tmp.m_sequence->begin(), tmp.m_sequence->end());

    return tmp;
}

DNASequence DNASequence::find(string seq) const {
    size_t indx = m_sequence->find(seq);
    if(indx == string::npos)
        throw DNASequenceException("Seqeunce is not found!");
    return slice(indx, indx + seq.length());
}

vector<DNASequence> DNASequence::findAll(string seq) const {
    vector<DNASequence> ans;
    size_t found = 0;
    while(found != string::npos){
        found = m_sequence->find(seq);
        ans.push_back(slice(found, found + seq.length()));
    }
    return ans;
    const pair<int, int> &x = make_pair(1, 1);
}

vector<pair<size_t , size_t> > DNASequence::findConsensus() const{
    vector<pair<size_t , size_t> > ans;
    vector<size_t> startingOcurr;
    size_t startingIndx = 0, nextStart = 0, endingIndx;
    while(startingIndx != string::npos){
        startingIndx = m_sequence->find(CodonAnalyzer::startingCodon);
        startingOcurr.push_back(startingIndx);
        endingIndx = this->findEndingCodonAndCount(startingIndx,
                startingOcurr, nextStart);
        if(endingIndx == -1){
            break;
        }
        vector<size_t>::iterator it = startingOcurr.begin();
        while (it != startingOcurr.end()) {
            ans.push_back(make_pair(*it, endingIndx));
            ++it;
        }
        startingIndx = nextStart;
        startingOcurr.clear();
    }

    return ans;
}

void DNASequence::ifIntersectsWithStartingCodonRemoveAndGoStepBack(size_t i,
        size_t& ending, vector<size_t>& startingOccurance) const
{
    if(CodonAnalyzer::isStartingCodon(
            m_sequence->substr(i - 1, i - 1 + CodonAnalyzer::codonLength)
                    .c_str())){
        --ending;
        startingOccurance.pop_back();
    }
}

size_t DNASequence::findEndingCodonAndCount(size_t startingIndx,
        vector<size_t> startingOccurance, size_t nextStart) const {
    size_t ending = -1, i = startingIndx + CodonAnalyzer::codonLength;
    for(;i < m_sequence->length();++i){
        if (CodonAnalyzer::isEndingCodon(
                m_sequence->substr(i, i + CodonAnalyzer::codonLength)
                .c_str()))
        {
            ending = i;

            ifIntersectsWithStartingCodonRemoveAndGoStepBack(i, ending,
                    startingOccurance);

            break;
        }

        if(CodonAnalyzer::isStartingCodon(
                m_sequence->substr(i - 1,
                        i - 1 + CodonAnalyzer::codonLength).c_str()))
        {
            startingOccurance.push_back(i);
        }
    }

    return ending;
}

string DNASequence::asString() const {
    stringstream ss;
    ss << * this;
    return ss.str();
}
