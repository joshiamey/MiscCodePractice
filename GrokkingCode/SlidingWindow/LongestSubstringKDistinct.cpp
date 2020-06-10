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
#include <set>
#include <string>
#include <algorithm>

using namespace std;

class LongestSubstringKDistinct
{
public:
    int findLength(string &str, int k)
    {
        auto wstart = 0;
        auto wend = 0;
        auto maxLength = 0;
        set<char> present;

        while (wstart < str.size() && wend < str.size())
        {
            if (!present.count(str[wend]))
            {
                if (present.size() == k)
                {
                    // We have found a string of K distint chars, calculate the length
                    // of the string.
                    auto length = (wend - wstart);
                    maxLength = max(maxLength, length);
                    // shrink window size and remove a character from the set
                    present.erase(str[wstart]);
                    ++wstart;
                    wend = wstart; // reset wend by point back to start
                }
                else
                {
                    // Char not present in set , insert it
                    present.insert(str[wend]);
                }
            }
            else
            { // character present in set, increment wend
                ++wend;
            }

            if (wend == str.length() && present.size() == k)
            {
                // We have reached the end of the string and with K distint characters
                // calculate the length of substring
                auto length = (wend - wstart);
                maxLength = max(maxLength, length);
            }
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
         << " distinct characters is of size: " << soln.findLength(str, S)
         << endl;

    cout << " The longest substring with no more than " << S2
         << " distinct characters is of size: " << soln.findLength(str2, S2)
         << endl;

    cout << " The longest substring with no more than " << S3
         << " distinct characters is of size: " << soln.findLength(str2, S3)
         << endl;

    cout << " The longest substring with no more than " << S
         << " distinct characters is of size: " << soln.findLength(str3, S)
         << endl;

    return 0;
}