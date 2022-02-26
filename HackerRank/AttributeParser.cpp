
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <fstream>
#include <regex>
#include <unordered_map>
using namespace std;

class AttributeParser
{
private:
    unordered_map<string, string> m_tag_attr_map;

public:
    AttributeParser(/* args */) : m_tag_attr_map(){};
    void parse(const vector<string> &hrml);
    string get_attribute(const string &attribute);
    ~AttributeParser();
};

AttributeParser::~AttributeParser()
{
}

string AttributeParser::get_attribute(const string &attr)
{
    auto found_iter = m_tag_attr_map.find(attr);

    if (found_iter != m_tag_attr_map.end())
    {
        return found_iter->second;
    }

    return "Not Found!";
}

void AttributeParser::parse(const vector<string> &hrml)
{
    string curr_tag = "";
    for (const auto &st : hrml)
    {
        // split strings base on multiple delimiters in the HRML tag
        // that include qoutes in the attr value using regex , this regex
        // will split the line in tokens containing only strings
        // with 0th being tag name and rest being attribute pairs.
        regex ws("[\\s|=|<|>|\"]+");
        vector<string> tokens;
        string end_tag = "/";
        copy(sregex_token_iterator(st.begin(), st.end(), ws, -1),
             sregex_token_iterator(),
             back_inserter(tokens));

        tokens.erase(remove_if(tokens.begin(), tokens.end(),
                               [&](const string &str)
                               { return str.empty(); }));

        string tag = tokens[0];

        if (tag.find(end_tag) != string::npos)
        {
            // Found the end tag for current progress tag
            // find the first '.' from end erase curr_tag
            // from that pos till end.
            auto pos = curr_tag.rfind('.');
            if (pos != string::npos)
            {
                curr_tag.erase(pos);
            }
            else
            {            
                // we just have explored 1 tag , clear the curr_tag     
                curr_tag.clear();
            }
            continue;
        }

        if (curr_tag.empty())
        {
            curr_tag = tag;
        }
        else
        {
            if (curr_tag != tag)
                curr_tag += "." + tag;
        }


        // Tokens begin from 1, and are in pairs 
        // 1,2 3,4 
        for (auto i = 1u; i < tokens.size() - 1; i += 2)
        {
            string key = curr_tag + "~" + tokens[i];
            m_tag_attr_map[key] = tokens[i + 1];
        }
    }
}
int main()
{
    string line;
    int html_len;
    int queries;
    ifstream ifs;
    string testcase;
    

    cout << "\nEnter test case file path: \n";
    // get test case from user
    cin >> testcase;

    ifs.open(testcase);
    vector<string> lines;
    AttributeParser attr_parser;

    if (ifs.is_open())
    {
        // Using filestream instead of std::cin (user input)
        // In case you want to use user input, just replace
        // ifs with cin.
        ifs >> html_len >> queries;

        for (int i = 0; i <= html_len; ++i)
        {
            if (getline(ifs, line))
            {
                if (!line.empty())
                    lines.push_back(line);
            }
        }

        attr_parser.parse(lines);

        for (int i = 0; i < queries; ++i)
        {
            if (getline(ifs, line))
            {
                if (!line.empty())
                    cout << attr_parser.get_attribute(line) << endl;
            }
        }

        ifs.close();
    }
    else
    {
        cerr << "Unable to open file:  " << testcase << endl;
    }
}
