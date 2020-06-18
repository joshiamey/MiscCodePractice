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
 */
#include <iostream>
#include <unordered_map>
#include <string>
#include <algorithm>

using namespace std;

class LongestSubstringKDistinct
{
public:
    int findLength(const string &str, int k)
    {
        auto wstart = 0;
        auto maxLength = 0;
        unordered_map<char, int> present;

        for (auto wend = 0; wend < str.length(); ++wend)
        {
            // Start inserting characters of string in the hashmap from
            // the start of the string

            if (!present.empty() && present.find(str[wend]) != present.end())
            {
                ++present[str[wend]];
            }
            else
            {
                present.emplace(str[wend], 1);
            }

            // the moment we detect hashmap has got > k distinct characters
            // We start reducing the windom and removing characters from the
            // map until less than K chars
            while (present.size() > k)
            {
                --present[str[wstart]];

                if (present[str[wstart]] == 0)
                {
                    present.erase(str[wstart]);
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
         << soln.findLength(str, S)
         << endl;

    cout << " The longest substring with no more than " << S2
         << " distinct characters is of size: "
         << soln.findLength(str2, S2)
         << endl;

    cout << " The longest substring with no more than " << S3
         << " distinct characters is of size: "
         << soln.findLength(str2, S3)
         << endl;

    cout << " The longest substring with no more than " << S
         << " distinct characters is of size: " << soln.findLength(str3, S)
         << endl;

    return 0;
}