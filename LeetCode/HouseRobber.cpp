#include <vector>
#include <iostream>
using namespace std;

static int rob(vector<int> &nums)
{
    auto sz = nums.size();
    vector<int> money(sz );

    money[0] = nums[0];
    money[1] = max(nums[1],money[0]);
    for (auto i = 2; i < sz; ++i)
    {
        // The max money that can be robbed at this ith house is 
        // is either nums[i] + money[i-2] that is money robbed 
        // from previous i - 2 houses or ignore this house
        // and just the one robbed from previous i - 1 house
        money[i] = max(nums[i] + money[i-2],money[i-1]);

    }

    return money[sz - 1];
}

int main(int argc, char const *argv[])
{
    vector<int> nums = {1,2,3,7,1,5,2,1,1};

    cout << "Max money I robbed: " << rob(nums) << endl;

    vector<int> nums2 = {2,1,1,2};

    cout << "Max money I robbed: " << rob(nums2) << endl;
    return 0;
}
