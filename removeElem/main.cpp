/*
 * main.cpp
 *
 *  Created on: Jul 29, 2018
 *      Author: ameya
 */

#include <iostream>
#include <string>
#include <vector>
#include <chrono>

using namespace std;


class Solution {
public:
    int removeElement(vector<int>& nums, int val) {

        if (nums.empty())
            return 0;

        auto i = 0u;
        auto len = nums.size();

        while( i < len )
        {
        	if(nums[i] == val)
        	{
        	    auto j = i + 1;
        	    cout << i << ","  << j << endl;
        		while(nums[j] == val )
				{
					++j;
				}
        		cout << i << ","  << j << endl;
        		if( j >= len)
        			break;

        		cout << i << ","  << j << endl;
        		nums[i] = nums[j];
        		nums[j] = val;
        		for (auto i : nums)
        		{
        			cout << i << ",";
        		}
        		cout << endl;
        	}

        	++i;
        }


        return i;
    }
};



int main() {

	vector<int> nums = {4,5,5,6,7,8,9,10,12,34,56,78,98,9,5,5,7};
	Solution sol;

	auto now = std::chrono::steady_clock::now();
	auto len = sol.removeElement(nums,5);
	auto end = std::chrono::steady_clock::now();

	cout << endl << "length = " << len << endl;

	cout << "Timetaken = " << std::chrono::duration<double>(end - now).count() << endl;

	cout << "Nums = " << endl;

	for (auto i : nums)
	{
		cout << i << ",";
	}
     return 0;
}
