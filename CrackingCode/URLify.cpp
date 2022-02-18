#include <string>
#include <iostream>

using namespace std;

void urlify(string& input, int final_len)
{
    string url = "%20";
    int actual_len = input.length();
    int end = actual_len - 1;
    int iter = final_len - 1;

    for(int iter = final_len - 1 ; iter >= 0; --iter)
    {
        // Now iter points to the space
        // so start the replacement
        if(isspace(input[iter]))
        {
            for(int i = url.length()-1; i >= 0 ;--i)
            {
                input[end--] = url[i];
            }
        }
        else
        {
            //else just replace
            input[end--] = input[iter];
        }
    }
}

int main(int argc, char const *argv[])
{
    string url = "Mr John Smith    ";

    urlify(url,13);

    cout << url <<endl;
    return 0;
}
