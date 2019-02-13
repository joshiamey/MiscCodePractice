#include <string>
#include <unordered_map>
#include <iostream>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {

        int cur_len = 0;
        int max_len = 0;

        cout << "Received string:" << s << endl;
        std::unordered_map<char,int> char_map;

        auto i = 0;
        while( i < s.size())
        {
            if(char_map.find(s[i]) == char_map.end())
            {
                ++cur_len;
                char_map.emplace(s[i],1);
                ++i;
            }
            else
            {
                if(cur_len > max_len)
                {
                    max_len = cur_len;
                }
                cur_len = 0;
                char_map.clear();
            }
        }

        if(cur_len > 0 && cur_len > max_len)
        {
        	max_len = cur_len;
        }

      return max_len;


    }
};

string stringToString(string input) {
//    assert(input.length() >= 2);
    string result;
    for (int i = 1; i < input.length() -1; i++) {
        char currentChar = input[i];
        if (input[i] == '\\') {
            char nextChar = input[i+1];
            switch (nextChar) {
                case '\"': result.push_back('\"'); break;
                case '/' : result.push_back('/'); break;
                case '\\': result.push_back('\\'); break;
                case 'b' : result.push_back('\b'); break;
                case 'f' : result.push_back('\f'); break;
                case 'r' : result.push_back('\r'); break;
                case 'n' : result.push_back('\n'); break;
                case 't' : result.push_back('\t'); break;
                default: break;
            }
            i++;
        } else {
          result.push_back(currentChar);
        }
    }
    return result;
}

//int main() {
//    string line;
//    while (getline(cin, line)) {
//        string s = stringToString(line);
//
//        int ret = Solution().lengthOfLongestSubstring(s);
//
//        string out = to_string(ret);
//        cout << out << endl;
//    }
//    return 0;
//}
