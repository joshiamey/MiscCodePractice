/* Given a list of intervals, merge all the overlapping intervals 
to produce a list that has only mutually exclusive intervals. */

#include <iostream>
#include <vector>
#include <algorithm>
#include "Interval.h"
using namespace std;

class MergeIntervals
{
public:
    static vector<Interval> merge(vector<Interval> &intervals)
    {
        vector<Interval> mergedIntervals;

        // First sort the given intervals based on start value so that we get a.start < b.start
        sort(intervals.begin(), intervals.end(),
             [&](const Interval &a, const Interval &b) {
                 return (a.start < b.start);
             });

        // Now that intervals are sorted, extract initial interval and iterate over the rest
        // to compare the end interval and select the max to merge start and end
        Interval *prevInterval = nullptr;
        auto start = 0;
        auto end = 0;
        for (auto &currInterval : intervals)
        {
            if (prevInterval != nullptr)
            {
                // compare if the start position of next interval is less than end position of the interval
                // before then we can merge these two
                if (currInterval.start <= prevInterval->end)
                {
                    // choose the max of previously calulated end or current interval end as the end of new interval
                    end = max(end, currInterval.end);
                }
                else
                {
                    // The intervals dont overlap , push this interval in the result set and restart start and end
                    mergedIntervals.emplace_back(start, end);
                    start = currInterval.start;
                    end = currInterval.end;
                }
            }
            else
            {
                // as previous is null that means we are at the beginning,
                // use that interval as the beginning range
                start = currInterval.start;
                end = currInterval.end;
            }

            prevInterval = &currInterval;
        }

        mergedIntervals.emplace_back(start, end);

        return mergedIntervals;
    }
};

int main(int argc, char const *argv[])
{
    vector<Interval> input = {{1, 4}, {2, 6}, {3, 5}};

    cout << "merged intervals: ";
    for (auto interval : MergeIntervals::merge(input))
    {
        cout << "{" << interval.start << "," << interval.end << "} ";
    }

    cout << endl;

    input = {{1, 3}, {2, 5}, {7, 9}};

    cout << "merged intervals: ";
    for (auto interval : MergeIntervals::merge(input))
    {
        cout << "{" << interval.start << "," << interval.end << "} ";
    }

    cout << endl;

    input = {{6, 7}, {2, 4}, {5, 9}};

    cout << "merged intervals: ";
    for (auto interval : MergeIntervals::merge(input))
    {
        cout << "{" << interval.start << "," << interval.end << "} ";
    }

    cout << endl;
    return 0;
}
