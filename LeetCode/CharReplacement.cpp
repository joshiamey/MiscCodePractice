#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

static int characterReplacement(string s, int k)
{
    vector<int> char_map(26,0);
    int maxCharReplaced = 0;
    int start = 0;

    for(auto end = 0 ; end < s.length(); ++end)
    {
        char_map[s[end] - 'A']++; // increase char frequency
        auto window = (end - start) + 1;
        auto max_iter = max_element(char_map.begin(),char_map.end());

        // within the window calculate the diff between window length 
        // and char that has max repetition frequency, if its greater 
        // than k, then start reducing window from the left, else if its 
        // less than K then within this window i can replace k chars to
        // get max window.
        if(window - *max_iter > k)
        {
            while(window - *max_iter > k)
            {
                char_map[s[start++] - 'A']--;
                window = (end - start) + 1;
                max_iter = max_element(char_map.begin(),char_map.end());
            }
        }

        maxCharReplaced = max(maxCharReplaced,window);
    }

    return maxCharReplaced;
}

int main(int argc, char const *argv[])
{
    cout << characterReplacement("AAA",0) << endl;
    cout << characterReplacement("SDCABAABBDDDEF",2) << endl;
    cout << characterReplacement("ABBB",1) << endl;
    cout << characterReplacement("ABAB",2) << endl;
    cout << characterReplacement("ABCDEFA",2) << endl;
    return 0;
}
