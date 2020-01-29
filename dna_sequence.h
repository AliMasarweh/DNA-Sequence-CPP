//
// Created by ali-masa on 1/17/20.
//

#ifndef DNA_SEQUENCE_DNA_SEQUENCE_H
#define DNA_SEQUENCE_DNA_SEQUENCE_H

#include <ostream>
#include <map>

#include "nucleotide_analyzer.h"
#include "codon_analyzer.h"

class DNASequenceException : public std::runtime_error
{
public:
    DNASequenceException(const std::string& message) : std::runtime_error(message) {}
};

class InvalidNucleotideSequenceDNA : public DNASequenceException
{
public:
    InvalidNucleotideSequenceDNA(const std::string& message = "Bad Nucleotide!") : DNASequenceException(message) {}
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

private:
    std::string* m_sequence;
    static std::map<char,char> constructCounterpart();
    static const std::map<char,char> s_counterpartMapper;

};

#endif //DNA_SEQUENCE_DNA_SEQUENCE_H
