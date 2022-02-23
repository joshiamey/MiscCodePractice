#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

/*
Find the next permuation in lexographical order
A permutation of an array of integers is an arrangement of its members into a sequence or linear order.

For example, for arr = [1,2,3], the following are considered permutations of arr: [1,2,3], [1,3,2], [3,1,2], [2,3,1].
The next permutation of an array of integers is the next lexicographically greater permutation of its integer. More formally, if all the permutations of the array are sorted in one container according to their lexicographical order, then the next permutation of that array is the permutation that follows it in the sorted container. If such arrangement is not possible, the array must be rearranged as the lowest possible order (i.e., sorted in ascending order).

For example, the next permutation of arr = [1,2,3] is [1,3,2].
Similarly, the next permutation of arr = [2,3,1] is [3,1,2].
While the next permutation of arr = [3,2,1] is [1,2,3] because [3,2,1] does not have a lexicographical larger rearrangement
*/
void nextPermutatution(vector<int>& nums)
{
    // find first decreasing index from end to 0
    int decrease = -1;


    for(int i = nums.size() - 2 ; i >=0 ; --i)
    {
        if(nums[i] < nums[i + 1])
        {
            decrease = i;
            break;
        }
    }

    if(decrease != -1)
    {
        // find the next number greater than nums[decrease]
        int swap_index = -1;
        for(int j = decrease + 1; j < nums.size(); ++j)
        {
            if(nums[j] > nums[decrease])
            {
                swap_index = j;
            }
            else
            {
                break;
            }
        }

        if(swap_index != -1)
        {
            swap(nums[decrease],nums[swap_index]);
        }
    }

    //finally reverse everything from i = firstdecrease + 1, till end
    std::reverse(nums.begin() + decrease + 1,nums.end());   

}

int main(int argc, char const *argv[])
{
    vector<int>nums = {1,2,6,5,3};

    nextPermutatution(nums);

    for_each(nums.begin(),nums.end(),[&](const auto& num) {cout << num << " ";});
    cout << endl;
    return 0;
}
