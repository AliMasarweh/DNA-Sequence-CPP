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
            InvalidNucleotideSequenceDNA);
}

