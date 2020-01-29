//
// Created by ali-masa on 1/29/20.
//

#include <gtest/gtest.h>
#include "dna_sequence.h"

using namespace std;

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(DNASequenceBasicTests, DNASequenceComplementaryTest)
{

    DNASequence dnaSequence("ATGCAGTCAACTAG");
    DNASequence dnaSequence2(dnaSequence.theOtherStrand());
    stringstream ss, ss2;

    ss2 << dnaSequence2;
    ASSERT_EQ(ss2.str(), "TACGTCAGTTGATC");

    ss << dnaSequence2.theOtherStrand();
    ASSERT_EQ(ss.str(), ss.str());
}

TEST(DNASequenceBasicTests, DNASequenceInvalidSequence)
{
    ASSERT_THROW(DNASequence ("ATGCAGTCAACTAGZ"),
            InvalidNucleotideDNASequence);
}

TEST(DNASequenceBasicTests, DNASequenceCodonTester)
{

    ASSERT_TRUE(CodonAnalyzer::isStartingCodon("ATG"));
    ASSERT_FALSE(CodonAnalyzer::isStartingCodon("GGG"));
    ASSERT_FALSE(CodonAnalyzer::isStartingCodon("TTT"));

    ASSERT_TRUE(CodonAnalyzer::isEndingCodon("TAG"));
    ASSERT_TRUE(CodonAnalyzer::isEndingCodon("TAA"));
    ASSERT_TRUE(CodonAnalyzer::isEndingCodon("TGA"));
    ASSERT_FALSE(CodonAnalyzer::isEndingCodon("GGG"));
    ASSERT_FALSE(CodonAnalyzer::isEndingCodon("TTT"));
}

TEST(DNASequenceBasicTests, DNASequenceSlicing)
{
    string str = "ATGCAGTCAACTAG";
    DNASequence dnaSequence(str);
    for (int i = 0; i < str.length() - 1; ++i) {
        for (int j = i + 1; j < str.length(); ++j) {
            ASSERT_EQ(str.substr(i, j), dnaSequence.slice(i, j).asString());
        }
    }
}

TEST(DNASequenceBasicTests, DNASequencePairing)
{
    string str = "ATGCAGTCAACTAG", str2 = "TACGTCAGTTGATC";
    DNASequence dnaSequence(str);
    reverse(str2.begin(), str2.end());
    ASSERT_EQ(str2, dnaSequence.pairing().asString());
}

TEST(DNASequenceBasicTests, DNASequenceFindAndFindAll)
{
    string str = "ATGCAGTCAACTAG", str2 = "TACGTCAGTTGATC";
    DNASequence dnaSequence(str);
    ASSERT_EQ(dnaSequence.find("CAGTC"), 3);
}