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
        char_map[s[end] - 'A']++;
        auto window = (end - start) + 1;
        auto max_iter = max_element(char_map.begin(),char_map.end());
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
    auto ans = characterReplacement("AAA",0);
    cout << ans << endl;
    return 0;
}
