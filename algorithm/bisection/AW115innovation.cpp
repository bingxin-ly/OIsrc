#include <bits/stdc++.h>
using namespace std;

// Forward declaration of compare API.
bool compare(int a, int b);
// return bool means whether a is less than b.

class Solution
{
public:
    vector<int> specialSort(int n)
    {
        vector<int> seq;
        seq.emplace_back(1);
        for (int k = 2; k <= n; k++)
        {
            auto l = seq.begin(), r = seq.end();
            while (l < r)
            {
                auto mid = l + ((r - l) >> 1);
                compare(*mid, k) ? (r = mid) : (l = mid + 1);
            }
            seq.insert(l, k);
        }
        return seq;
    }
};