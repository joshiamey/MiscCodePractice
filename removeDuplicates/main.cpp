/*
 * main.cpp
 *
 *  Created on: Jul 29, 2018
 *      Author: ameya
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Solution {
public:
    int removeDuplicates(vector<int>& nums) {

        if (nums.size() < 1)
            return 0;

        auto i = 0;

        for(auto j = 1 ; j < nums.size(); ++j)
        {
            if(nums[i] != nums[j])
            {
                nums[++i] = nums[j];
            }
        }

        return i;
    }
};



int main() {

	vector<int> nums = {1,1,2};
	Solution sol;
	auto len = sol.removeDuplicates(nums);

	cout << "length = " << len << endl;

	cout << "Nums = " << endl;

	for (auto i : nums)
	{
		cout << i << ",";
	}
     return 0;
}
