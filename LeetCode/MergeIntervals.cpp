#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

vector<vector<int>> merge(vector<vector<int>> &intervals)
{
    if (intervals.size() <= 1)
    {
        return intervals;
    }

    // sort the array as it doesnt say its sorted or not
    sort(intervals.begin(), intervals.end(), [&](const auto &arr1, const auto &arr2)
         { return arr1[0] < arr2[0]; });

    vector<vector<int>> result;
    vector<int> current_interval(2);
    current_interval[0] = intervals[0][0];
    current_interval[1] = intervals[0][1];

    for (const auto &interval : intervals)
    {
        int curr_start = current_interval[0];
        int curr_end = current_interval[1];

        if (curr_end >= interval[0])
        {
            current_interval[1] = max(curr_end, interval[1]);
        }
        else
        {
            result.push_back(current_interval);
            current_interval = interval;
        }
    }

    result.push_back(current_interval);

    return result;
}

int main(int argc, char const *argv[])
{
    vector<vector<int>> arr = {{1,3},{2,6},{8,10},{15,18}};
    merge(arr);
    return 0;
}
