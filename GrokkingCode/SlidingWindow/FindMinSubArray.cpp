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
    bool SubArraySum(vector<int> &arr, int k, int S)
    {
        auto sum = 0;
        auto wstart = 0; //Sliding window start

        for (auto wend = 0; wend < arr.size(); ++wend)
        {
            sum += arr[wend];
            // if the iteration has reached the end of window size k
            // slide the window start by 1
            if ((wend - wstart) >= k - 1)
            {
                // Store the max sum
                if (sum >= S)
                {
                    // We found a contigous subarray which is equal to S
                    // return true
                    return true;
                }

                sum -= arr[wstart]; // subtract the start from the current window sum
                ++wstart;           // increment window start
            }
        }

        return false; // we have reached the end return false
    }

    int findMinSubArray(vector<int> &arr, int S)
    {
        // We are going to use maxSubArray algorithm to calculate maximum sum
        // We start will min size window of 1 and keep increasing until array size
        for (auto k = 1; k < arr.size(); ++k)
        {
            if (SubArraySum(arr, k, S))
            {
                return k;
            }
        }

        return 0;
    }
};

int main(int argc, char const *argv[])
{
    Solution soln = Solution();
    vector<int> arr = {2, 1, 5, 2, 3, 2};

    auto S = 7;
    auto smallSubArray = soln.findMinSubArray(arr, S);

    cout << " Smallest contigous subarray whose sum is greater than or equal to " << S
         << " is of size: " << smallSubArray << endl;

    return 0;
}
