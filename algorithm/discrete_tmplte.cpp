#include <bits/stdc++.h>
using namespace std;
vector<int> nums;

int find(int x)
{
    int l = 0, r = nums.size() - 1;
    while (l < r)
    {
        int mid = (l + r) >> 1;
        if (nums[mid] >= x)
            r = mid;
        else
            l = mid + 1;
    }
    return r + 1; // 映射到1,2,3,···,n
}
int main()
{
    int i;
    while (cin >> i)
        nums.push_back(i);
    {
        sort(nums.begin(), nums.end()); // 排序
        nums.erase(unique(nums.begin(), nums.end()), nums.end()); // 去重
    }
    for (auto i : nums)
        cout << find(i) << " ";
    cout << endl;
    return 0;
}