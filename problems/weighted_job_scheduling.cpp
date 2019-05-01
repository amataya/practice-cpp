///////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>
#include <climits>
#include <algorithm>

using namespace std;
///////////////////////////////////////////////////////////////////////////////

struct Job
{
    int start = 0;
    int finish = 0;
    int profit = 0;

    Job(const int s, const int f, const int p)
        : start(s), finish(f), profit(p) {}
};

// Find the job before current job that does not
// conflict with the current job
int binary_search(vector<Job>& jobs, int index)
{
    int lo = 0, hi = index - 1;
    while (lo <= hi)
    {
        int mid = (lo + hi) / 2;
        if (jobs[mid].finish <= jobs[index].start)
        {
            if(jobs[mid + 1].finish <= jobs[index].start)
                lo = mid + 1;
            else
                return mid;
        }
        else
            hi = mid - 1;
    }

    return -1;
}

int findMaxProfit(vector<Job> jobs)
{
    sort(jobs.begin(), jobs.end(),
         [](Job j1, Job j2){ return j1.finish < j2.finish; });

    vector<int> table(jobs.size(), INT_MIN);
    table[0] = jobs[0].profit;

    int profitIncludingJob = 0, otherJobId = 0;
    for (size_t i = 1; i < jobs.size(); ++i)
    {
        // Find profit including current job
        profitIncludingJob = jobs[i].profit;
        otherJobId = binary_search(jobs, i);
        if (otherJobId != -1)
            profitIncludingJob += table[otherJobId];

        // Store maximum profit (including and excluding current job)
        table[i] = max(profitIncludingJob, table[i - 1]);
    }

    return table[table.size() - 1];
}

///////////////////////////////////////////////////////////////////////////////
TEST_CASE("Weighted Job Scheduling", "[practice]")
{
    REQUIRE(findMaxProfit(vector<Job>{{3, 10, 20},
                                      {1, 2, 50}, 
                                      {6, 19, 100}, 
                                      {2, 100, 200}}) == 250);
}