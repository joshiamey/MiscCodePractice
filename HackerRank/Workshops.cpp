#include<bits/stdc++.h>
#include<algorithm>
#include<string>
using namespace std;

//Define the structs Workshops and Available_Workshops.
struct Workshop
{
    int start_time;
    int duration;
    int end_time;
    
    Workshop() {}
    Workshop(int in_start_time,int in_duration): 
        start_time(in_start_time),
        duration(in_duration),
        end_time()
        {
            end_time = start_time + duration;
        }
    
};

struct Available_Workshops
{
    int n;
    vector<Workshop> workshops;
    
    Available_Workshops(int size): n(size),workshops(size) {}
    
};
//Implement the functions initialize and CalculateMaxWorkshops
Available_Workshops* initialize(int* start_time,int* duration, int in_n)
{
    Available_Workshops* ptr = new Available_Workshops(in_n);
    
    for(int i = 0 ; i < in_n ; ++i)
    {
        Workshop w(start_time[i],duration[i]);
        ptr->workshops[i] = w;
    }
    
    return ptr;
}

int CalculateMaxWorkshops(Available_Workshops* ptr)
{
    auto& workshops = ptr->workshops;
    
    // Use greedy algorithm to find non-overlapping intervals
    // sort the interval based on end time , as a result 
    //  you will have the interval minimum at the start
    // thus greedily you pick up the smallest endtime 
    std::sort(workshops.begin(),workshops.end(),
    [&](const auto& w1, const auto w2)
    {
       return (w1.end_time < w2.end_time);
    });
    
    int maxworkshop = 1; // include the 1st interval as thats the minimum value.
    int end_time = workshops[0].end_time;
    
    for(int i = 1; i < workshops.size(); ++i)
    {
        if(workshops[i].start_time >= end_time)
        {
            ++maxworkshop;
            end_time = workshops[i].end_time;
        }
    }
    
    delete ptr;
    return maxworkshop;
}

int main(int argc, char *argv[]) {
    ifstream ifs;
    string testcase;
    int n; // number of workshops
    cout << "\nEnter test case file path: \n";
    // get test case from user
    cin >> testcase;
    ifs.open(testcase);
    Available_Workshops * ptr;

    if(ifs.is_open())
    {
        ifs >> n;
        // create arrays of unknown size n
        int* start_time = new int[n];
        int* duration = new int[n];

        for(int i=0; i < n; i++){
            ifs >> start_time[i];
        }
        for(int i = 0; i < n; i++){
            ifs >> duration[i];
        }
        ptr = initialize(start_time,duration, n);

    }

    cout << CalculateMaxWorkshops(ptr) << endl;
    return 0;
}