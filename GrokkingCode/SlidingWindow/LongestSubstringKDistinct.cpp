/* Problem Statement #

Given a string, find the length of the longest substring in it with no more than K distinct characters.

Example 1:

Input: String="araaci", K=2
Output: 4
Explanation: The longest substring with no more than '2' distinct characters is "araa".

Example 2:

Input: String="araaci", K=1
Output: 2
Explanation: The longest substring with no more than '1' distinct characters is "aa".

Example 3:

Input: String="cbbebi", K=3
Output: 5
Explanation: The longest substrings with no more than '3' distinct characters are "cbbeb" & "bbebi".

This algorithm also is applicable to Fruits in a basket problem , for that K=2 
Input: Fruit=['A', 'B', 'C', 'A', 'C']
Output: 3
Explanation: We can put 2 'C' in one basket and one 'A' in the other from the subarray ['C', 'A', 'C']

 */
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class LongestSubstringKDistinct
{
public:
    int findLength(const vector<char> &arr, int k)
    {
        auto wstart = 0;
        auto maxLength = 0;
        unordered_map<char, int> present;

        for (auto wend = 0; wend < arr.size(); ++wend)
        {
            // Start inserting characters of string in the hashmap from
            // the start of the string

            ++present[arr[wend]];

            // the moment we detect hashmap has got > k distinct characters
            // We start reducing the windom and removing characters from the
            // map until less than K chars
            while (present.size() > k)
            {
                --present[arr[wstart]];

                if (present[arr[wstart]] == 0)
                {
                    present.erase(arr[wstart]);
                }
                ++wstart;
            }

            // Until we reach hashmap size > K characters, we keep increasing the
            // character window size to capture as much same contigous chars
            auto length = (wend - wstart) + 1;
            maxLength = max(maxLength, length);
        }
        return maxLength;
    }
};

int main(int argc, char const *argv[])
{
    LongestSubstringKDistinct soln = LongestSubstringKDistinct();
    string str = "araabeabee";
    string str2 = "araaci";
    string str3 = "cbeebi";
    auto S = 3;
    auto S2 = 2;
    auto S3 = 1;

    cout << " The longest substring with no more than " << S
         << " distinct characters is of size:"
         << soln.findLength(vector<char>(str.begin(), str.end()), S)
         << endl;

    cout << " The longest substring with no more than " << S2
         << " distinct characters is of size: "
         << soln.findLength(vector<char>(str2.begin(), str2.end()), S2)
         << endl;

    cout << " The longest substring with no more than " << S3
         << " distinct characters is of size: "
         << soln.findLength(vector<char>(str.begin(), str.end()), S3)
         << endl;

    cout << " The longest substring with no more than " << S
         << " distinct characters is of size: " << soln.findLength(vector<char>(str3.begin(), str3.end()), S)
         << endl;

    cout << " The Maximum number of fruits in 2 baskets " << S
         << " distinct characters is of size: " << soln.findLength(vector<char>{'A', 'B', 'C', 'B', 'B', 'C'}, 2)
         << endl;

    return 0;
}