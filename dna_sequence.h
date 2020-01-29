//
// Created by ali-masa on 1/17/20.
//

#ifndef DNA_SEQUENCE_DNA_SEQUENCE_H
#define DNA_SEQUENCE_DNA_SEQUENCE_H

#include <ostream>
#include <map>
#include <vector>

#include "nucleotide_analyzer.h"
#include "codon_analyzer.h"

class DNASequenceException : public std::runtime_error
{
public:
    DNASequenceException(const std::string& message) : std::runtime_error(message) {}
};

class InvalidNucleotideDNASequence : public DNASequenceException
{
public:
    InvalidNucleotideDNASequence(const std::string& message = "Bad Nucleotide!") : DNASequenceException(message) {}
};

class InvalidDNASequence : public DNASequenceException
{
public:
    InvalidDNASequence(const std::string& message = "Bad DNA Sequence!") : DNASequenceException(message) {}
};

class InvalidSlicingDNASequence : public DNASequenceException
{
public:
    InvalidSlicingDNASequence(const std::string& message) : DNASequenceException(message) {}
};

class OutOfBoundsSlicingDNASequence : public InvalidSlicingDNASequence
{
public:
    OutOfBoundsSlicingDNASequence(const std::string& message = "Out of bounds slicing!") : InvalidSlicingDNASequence(message) {}
};

class InvalidIndexesSlicingDNASequence : public InvalidSlicingDNASequence
{
public:
    InvalidIndexesSlicingDNASequence(const std::string& message = "Worng indexing!") : InvalidSlicingDNASequence(message) {}
};


class DNASequence{

    friend std::ostream& operator<<(std::ostream& os, const DNASequence& dna);
    friend bool operator<(const DNASequence& dna1, const DNASequence& dna2);
    friend bool operator>(const DNASequence& dna1, const DNASequence& dna2);
    friend bool operator==(const DNASequence& dna1, const DNASequence& dna2);
    friend bool operator!=(const DNASequence& dna1, const DNASequence& dna2);
    friend bool operator<=(const DNASequence& dna1, const DNASequence& dna2);
    friend bool operator>=(const DNASequence& dna1, const DNASequence& dna2);

public:
    explicit DNASequence(const char dnaSeq[]);
    explicit DNASequence(const std::string&  dnaSeq);
    DNASequence(const DNASequence& dnaSequence);
    DNASequence& operator=(const DNASequence& dnaSequence);
    DNASequence& operator=(const std::string&  dnaSeq);
    DNASequence& operator=(const char dnaSeq[]);
    DNASequence theOtherStrand() const;
    ~DNASequence();
    size_t length() const;
    const char& operator[](size_t index) const;
    char operator[](size_t index);

    bool validSequence() const;

    DNASequence slice(size_t startingIndx) const;
    DNASequence slice(size_t startingIndx, size_t endingIndx) const;
    DNASequence pairing() const;
    DNASequence find(std::string seq) const;
    std::vector<DNASequence> findAll(std::string seq) const;
    std::vector<std::pair<size_t , size_t> > findConsensus() const;

private:
    size_t findEndingCodonAndCount(size_t i, std::vector<size_t> vector,
            size_t i1) const;
    void ifIntersectsWithStartingCodonRemoveAndGoStepBack(size_t i,
            size_t &ending, std::vector<size_t> &startingOccurance) const;
    std::string* m_sequence;
    static std::map<char,char> constructCounterpart();
    static const std::map<char,char> s_counterpartMapper;

};

#endif //DNA_SEQUENCE_DNA_SEQUENCE_H
