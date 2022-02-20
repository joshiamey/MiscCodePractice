#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

static int removeCoveredIntervals(vector<vector<int>>& intervals)
{
    //first sort the intervals on begin time
    sort(intervals.begin(),intervals.end(),
        [&](const auto& a,const auto& b)
        {
            if(a[0] == b[0])
            {
                // we want to have highest end time at the beginning
                // as that interval will cover rest
                // for example {1,2}{1,4}{3,4}
                return (a[1] > b[1]);
            }

            return a[0] < b[0];
        });

    int curr_end = intervals[0][1];
    int curr_end_index = 0;

    for(int i = 1; i < intervals.size(); ++i)
    {
        int end = intervals[i][1];

        if(end > curr_end)
        {
            //swap the elements of curr_index + 1;
            curr_end = intervals[i][1];
            curr_end_index++;
            swap(intervals[curr_end_index][0],intervals[i][0]);
            swap(intervals[curr_end_index][1],intervals[i][1]);
        }
    }

    intervals.erase(intervals.begin() + curr_end_index + 1, intervals.end());

    return intervals.size();
}

int main(int argc, char const *argv[])
{
    // vector<vector<int>> intervals = {
    //     {1,4},
    //     {3,6},
    //     {2,4},
    //     {4,9},
    //     {2,8}
    // };

    vector<vector<int>> intervals = {
        {1,2},
        {1,4},
        {3,4}
    };

    removeCoveredIntervals(intervals);
    return 0;
}

