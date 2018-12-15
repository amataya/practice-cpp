// A DNA sequence can be represented as a string consisting of the letters
// A, C, G and T, which correspond to the types of successive nucleotides in
// the sequence. Each nucleotide has an impact factor, which is an integer.
// Nucleotides of types A, C, G and T have impact factors of 1, 2, 3 and 4,
// respectively. You are going to answer several queries of the form:
// What is the minimal impact factor of nucleotides contained in a particular
// part of the given DNA sequence?
//
// The DNA sequence is given as a non-empty string S = S[0]S[1]...S[N-1]
// consisting of N characters. There are M queries, which are given in non-empty
// arrays P and Q, each consisting of M integers. The K-th query (0 ≤ K < M)
// requires you to find the minimal impact factor of nucleotides contained in
// the DNA sequence between positions P[K] and Q[K] (inclusive).
//
// For example, consider string S = CAGCCTA and arrays P, Q such that:
//     P[0] = 2    Q[0] = 4
//     P[1] = 5    Q[1] = 5
//     P[2] = 0    Q[2] = 6
//
// The answers to these M = 3 queries are as follows:
//  - The part of the DNA between positions 2 and 4 contains nucleotides G and
//    C (twice), whose impact factors are 3 and 2 respectively, so the answer
//    is 2.
//  - The part between positions 5 and 5 contains a single nucleotide T,
//    whose impact factor is 4, so the answer is 4.
//  - The part between positions 0 and 6 (the whole string) contains all
//    nucleotides, in particular nucleotide A whose impact factor is 1,
//    so the answer is 1.
//
// Write a function:
//
//  vector<int> solution(string &S, vector<int> &P, vector<int> &Q);
//
// that, given a non-empty string S consisting of N characters and two
// non-empty arrays P and Q consisting of M integers, returns an array
// consisting of M integers specifying the consecutive answers to all queries.
//
// Result array should be returned as a vector of integers.
//
// For example, given the string S = CAGCCTA and arrays P, Q such that:
//     P[0] = 2    Q[0] = 4
//     P[1] = 5    Q[1] = 5
//     P[2] = 0    Q[2] = 6
//
// the function should return the values [2, 4, 1], as explained above.
//
// Write an efficient algorithm for the following assumptions:
//     N is an integer within the range [1..100,000];
//     M is an integer within the range [1..50,000];
//     each element of arrays P, Q is an integer within the range [0..N − 1];
//     P[K] ≤ Q[K], where 0 ≤ K < M;
//     string S consists only of upper-case English letters A, C, G, T
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
vector<int> genomic_range_query(string S, vector<int> P, vector<int> Q)
{
    // At each index we are counting how many of each nucleotide we have seen
    // Two ways - maintain a tuple at the index or maintain separate vectors.
    const size_t size = S.size() + 1;
    vector<int> countA(size), countC(size), countG(size), countT(size);
    int i;
    for (i = 0; i < S.size(); ++i)
    {
        countA[i + 1] = countA[i]+ (S[i] == 'A' ? 1 : 0);
        countC[i + 1] = countC[i]+ (S[i] == 'C' ? 1 : 0);
        countG[i + 1] = countG[i]+ (S[i] == 'G' ? 1 : 0);
        countT[i + 1] = countT[i]+ (S[i] == 'T' ? 1 : 0);
    }

    // If the distance between Q and P is lower than the distance to the last
    // seen genome, we have found the right candidate.
    vector<int> result(P.size());
    bool isAInRange, isCInRange, isGInRange, isTInRange;
    for (i = 0; i < P.size(); ++i)
    {
        isAInRange = (countA[ Q[i] + 1 ] - countA[ P[i] ]) > 0;
        isCInRange = (countC[ Q[i] + 1 ] - countC[ P[i] ]) > 0;
        isGInRange = (countG[ Q[i] + 1 ] - countG[ P[i] ]) > 0;
        isTInRange = (countT[ Q[i] + 1 ] - countT[ P[i] ]) > 0;

        if (isAInRange)
            result[i] = 1;
        else if (isCInRange)
            result[i] = 2;
        else if (isGInRange)
            result[i] = 3;
        else if (isTInRange) // for clarity otherwise an else would do
            result[i] = 4;
    }
    return result;
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Genomic Range Query", "[codility]")
{
    // For the example plot the arrays and then this will start making sense
    // The approach here is described in "PrefixSum.pdf" in docs folder.
    REQUIRE(genomic_range_query("CAGCCTA", {2, 5, 0}, {4, 5, 6}) ==
    vector<int>{2, 4, 1});
}