/* Given an array of positive numbers and a positive number ‘S’, 
find the length of the smallest contiguous subarray whose sum is greater than or equal to ‘S’. 
Return 0, if no such subarray exists. 
Input: [2, 1, 5, 2, 3, 2], S=7 
Output: 2
Explanation: The smallest subarray with a sum great than or equal to '7' is [5, 2].

Input: [2, 1, 5, 2, 8], S=7 
Output: 1
Explanation: The smallest subarray with a sum greater than or equal to '7' is [8].

*/
#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    /* This function will calculate sum of contigous sub array and return true if it is greater
       than or equal to S
     */
    int findMinSubArray(vector<int> &arr, int S)
    {

        auto wstart = 0;                       //Sliding window start
        auto wend = 0;                         // Sliding window end
        auto minWindowLength = arr.size() + 1; // Start with minWindowLength equal to array size + 1
        auto sum = 0;                          // Initialize sum to the first element of the array.

        // while sum of window size 1 is >=S , record the min window length,
        // shrink window by removing elements from the start
        // Else Expand window from the end by increasing the wend
        // Recalculate sum of the new window

        while (wend < arr.size() && wstart < arr.size())
        {
            sum += arr[wend];
            // cout << "DEBUG ELSE: wstart= " << wstart << endl;
            // cout << "DEBUG ELSE: wend= " << wend << endl;
            // cout << "DEBUG ELSE: Sum= " << sum << endl;
            while (sum >= S)
            {
                // We found a contigous subarray which is equal to S
                // calculate window size
                auto windowSize = (wend - wstart) + 1;

                // cout << "DEBUG WHILE: window size= " << windowSize << endl;
                // cout << "DEBUG WHILE: Sum= " << sum << endl;
                // cout << "DEBUG WHILE: wstart= " << wstart << endl;
                // cout << "DEBUG WHILE: wend= " << wend << endl;

                if (windowSize < minWindowLength)
                {
                    minWindowLength = windowSize;
                }

                sum -= arr[wstart];
                // cout << "DEBUG WHILE AFTER: Sum= " << sum << endl;
                ++wstart; //keep shrinking window size
            }

            ++wend; // increase window size by sliding right
        }

        if (minWindowLength == arr.size() + 1)
        {
            return 0;
        }
        return minWindowLength; // we have reached the end return false
    }
};

int main(int argc, char const *argv[])
{
    Solution soln = Solution();
    vector<int> arr = {2, 1, 5, 2, 3, 2};
    vector<int> arr2 = {2, 1, 5, 2, 8};
    vector<int> arr3 = {3, 4, 1, 1, 6};

    auto S = 7;
    auto S2 = 8;

    cout << " Smallest contigous subarray whose sum is greater than or equal to " << S
         << " is of size: " << soln.findMinSubArray(arr, S)
         << endl;

    cout << " Smallest contigous subarray whose sum is greater than or equal to " << S
         << " is of size: " << soln.findMinSubArray(arr2, S)
         << endl;

    cout << " Smallest contigous subarray whose sum is greater than or equal to " << S
         << " is of size: " << soln.findMinSubArray(arr3, S2)
         << endl;

    return 0;
}
