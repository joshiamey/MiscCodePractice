#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

vector<int> productExceptSelf(vector<int> &nums)
{
    vector<int> product_array(nums.size(), 1);

    // first calculate prefix left product
    // i.e a[i] = a[0] * .... a[i-1]
    for (auto i = 1u; i < nums.size(); ++i)
    {
        product_array[i] = product_array[i - 1] * nums[i - 1];
    }

    // then recalculate the suffix right product of the
    // a[i] = a[i+1] * a[i+2] ......
    auto right_prod = 1; // initialize the right suffix prod of n-1 element to 1

    for (int j = nums.size() - 2; j >= 0; --j)
    {
        // update the right product for element n-2 ... 0
        right_prod *= nums[j + 1];
        // update the final product array by multiplying precalculate prefix
        // by multiplying suffix.
        product_array[j] *= right_prod;
    }

    return product_array;
}

int main(int argc, char const *argv[])
{
    vector<int> nums = {1, 2, 3, 4};

    auto ans = productExceptSelf(nums);

    for_each(ans.begin(),ans.end(),
    [&](const auto& elem){
        cout << elem << " ";
    });

    return 0;
}
