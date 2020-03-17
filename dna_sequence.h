//
// Created by ali-masa on 1/17/20.
//

#ifndef DNA_SEQUENCE_DNA_SEQUENCE_H
#define DNA_SEQUENCE_DNA_SEQUENCE_H

#include <vector>
#include <map>

#include "nucleotide_analyzer.h"
#include "codon_analyzer.h"

class DNASequenceException : public std::exception
{
public:
    explicit DNASequenceException(const std::string& message);
    virtual ~DNASequenceException() throw ();
    virtual const char* what() const throw ();

protected:
    std::string m_msg;
};

class InvalidNucleotideDNASequence : public DNASequenceException
{
public:
    InvalidNucleotideDNASequence() : DNASequenceException("Bad Nucleotide!") {}
};

class InvalidDNASequence : public DNASequenceException
{
public:
    InvalidDNASequence() : DNASequenceException("Bad DNA Sequence!") {}
};

class InvalidSlicingDNASequence : public DNASequenceException
{
public:
    InvalidSlicingDNASequence(const std::string& message) : DNASequenceException(message) {}
};

class OutOfBoundsSlicingDNASequence : public InvalidSlicingDNASequence
{
public:
    OutOfBoundsSlicingDNASequence() : InvalidSlicingDNASequence("Out of bounds slicing!") {}
};

class InvalidIndexesSlicingDNASequence : public InvalidSlicingDNASequence
{
public:
    InvalidIndexesSlicingDNASequence() : InvalidSlicingDNASequence("Worng indexing!") {}
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
    virtual ~DNASequence();
    size_t length() const;
    const char& operator[](size_t index) const;
    char operator[](size_t index);

    bool validSequence() const;

    DNASequence slice(size_t startingIndx) const;
    DNASequence slice(size_t startingIndx, size_t endingIndx) const;
    DNASequence pairing() const;
    size_t find(std::string seq) const;
    size_t count(std::string seq) const;
    std::vector<size_t> findAll(std::string seq) const;
    std::vector<std::pair<size_t , size_t> > findConsensus() const;

    DNASequence& concat(DNASequence& dnaSequence);

    std::string asString() const;

    void writeToFile(std::string path) const;
    void readFromFile(std::string path);

protected:
    std::string m_sequence;

private:
    size_t findEndingCodonAndCount(size_t i, std::vector<size_t> vector,
            size_t i1) const;
    void ifIntersectsWithStartingCodonRemoveAndGoStepBack(size_t i,
            size_t &ending, std::vector<size_t> &startingOccurance) const;

    static std::map<char,char> constructCounterpart();
    static const std::map<char,char> s_counterpartMapper;

};

#endif //DNA_SEQUENCE_DNA_SEQUENCE_H
