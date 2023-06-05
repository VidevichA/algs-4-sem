#include <iostream>
#include <vector>

std::string solve(const std::vector<long>& arr, long val)
{
    bool find = false;
    int l = 0;
    int r = arr.size();
    int l1 = 0;
    int r1 = arr.size();
    while(l < r)
    {
        int m = (l + r) / 2;
        if(val <= arr[m]) 
        {
            if(val == arr[m]) 
            {
                find = true;
            }
            r = m;
        }
        else
        {
            l = m + 1;
        }
    }
    while(l1 < r1)
    {
        int m1 = (l1 + r1) / 2;
        if(val < arr[m1]) 
        {
            r1 = m1;
        }
        else 
        {
            l1 = m1 + 1;
        }
    }
    return std::to_string(find) + " " + std::to_string(l) + " " + std::to_string(l1) + "\n";
}

int main() 
{
    int n;
    std::cin >> n;
    long temp;
    std::vector<long> arr;
    for(int i = 0; i < n; ++i)
    {
        std::cin >> temp;
        arr.push_back(temp);
    }
    int k;
    std::cin >> k;
    for(int i = 0; i < k; ++i)
    {
        std::cin >> temp;
        std::cout << solve(arr,temp);
    }
    return 0;
}