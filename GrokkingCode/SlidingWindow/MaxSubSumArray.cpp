/* Given an array of positive numbers and a positive number k, 
*find the maximum sum of any contiguous subarray of size k.
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int maximumSubArraySum(vector<int> &arr, int k)
    {
        auto maxSum = 0;
        auto sum = 0;
        auto wstart = 0; //Sliding window start
        auto wend = 0;   //Sliding window end

        for (wend = 0; wend < arr.size(); ++wend)
        {
            sum += arr[wend];

            // if the iteration has reached the end of window size k
            // slide the window start by 1
            if ((wend - wstart) >= k - 1)
            {
                // Store the max sum
                if (sum > maxSum)
                {
                    maxSum = sum;
                }
                sum -= arr[wstart]; // subtract the start from the current window sum
                ++wstart;           // increment window start
            }
        }

        return maxSum;
    }
};

int main(int argc, char const *argv[])
{
    Solution soln = Solution();
    vector<int> arr = {2, 1, 5, 1, 3, 2};

    auto maxSumSubarry = soln.maximumSubArraySum(arr, 3);

    cout << " Max Sum for subarray of size 3 is: " << maxSumSubarry << endl;

    return 0;
}
