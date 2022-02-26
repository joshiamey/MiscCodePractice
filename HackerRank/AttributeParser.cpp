
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
        string end_tag = "/";
        sregex_token_iterator it_begin(st.begin(), st.end(), ws, -1);
        sregex_token_iterator it_end;

        ++it_begin; // the first string is space, so skip it

        // now it_begin shall point to the tag name
        string tag = it_begin->str();

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
                // we have explored the tag , clear the curr_tag
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

        // Done processing with the tag, process the attributes
        ++it_begin;
        // Tokens begin from 1, and are in pairs
        // 1,2 3,4
        for (; it_begin != it_end; ++it_begin)
        {
            string key = curr_tag + "~" + it_begin->str();
            ++it_begin;
            m_tag_attr_map[key] = it_begin->str();
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
