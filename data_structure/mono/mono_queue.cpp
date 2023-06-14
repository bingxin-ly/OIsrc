#include <bits/stdc++.h>
using namespace std;

template <typename _Tp>
class mono_queue
{
    queue<_Tp> queue;
    list<_Tp> maxq, minq;

public:
    size_t size() { return queue.size(); }
    void push(_Tp n)
    {
        queue.push(n);

        // 维护最大值
        while (!maxq.empty() && maxq.back() < n)
            maxq.pop_back();
        maxq.push_back(n);

        // 维护最小值
        while (!minq.empty() && minq.back() > n)
            minq.pop_back();
        minq.push_back(n);
    }
    /* void pop(_Tp n)
    {
        if (maxq.front() == n)
            maxq.pop_front();
    } */
    _Tp pop()
    {
        if (!size())
            return nullptr;

        auto top = queue.front();
        queue.pop();
        if (maxq.front() == top)
            maxq.pop_front();
        if (minq.front() == top)
            minq.pop_front();

        return top;
    }
    _Tp max() { return maxq.front(); }
    _Tp min() { return minq.front(); }
};

vector<int> max_sliding_win(vector<int> nums, int k)
{
    mono_queue<int> window;
    vector<int> res;

    for (int i = 0; i < nums.size(); i++)
    {
        if (i < k - 1)
            window.push(nums[i]);
        else
        {
            window.push(nums[i]);
            res.push_back(window.max());
            window.pop();
        }
    }
    return res;
}

string sliding_window(string s, string t)
{
    unordered_map<char, int> need, window;
    for (char c : t)
        need[c]++;

    int left = 0, right = 0, valid = 0;
    int start = 0, len = INT_MAX;
    while (right < s.size())
    {
        char c = s[right];
        right++;

        if (need.count(c))
        {
            window[c]++;
            if (window[c] == need[c])
                valid++;
        }

        // 缩小左侧窗口
        while (valid == need.size())
        {
            if (right - left < len)
            {
                start = left;
                len = right - left;
            }
            char d = s[left];
            left++;

            if (need.count(d))
            {
                if (window[d] == need[d])
                    valid--;
                window[d]--;
            }
        }
    }

    return len == INT_MAX ? "" : s.substr(start, len);
}

const int MAX = 1e6 + 10;
int arr[MAX], mins[MAX], maxs[MAX];
int qmin[MAX], qmax[MAX]; // 数组模拟队列

int main()
{
    int n, k;
    cin >> n >> k;
    /* for (int i = 0; i < n; i++)
        cin >> arr[i];
    memset(mins, 0x7f, sizeof(mins));

    int l = 1, r = 1;
    for (int i = 1; i <= n; i++)
    {
        while (l <= r && qmin[l] < i - k)
            l++;
        mins[i] = arr[qmin[l]];
        while (l <= r && arr[qmin[r]] >= arr[i])
            r--;
        qmin[++r] = i;
    }
    l = 1, r = 1;
    for (int i = 1; i <= n; i++)
    {
        while (l <= r && qmax[l] < i - k)
            l++;
        maxs[i] = arr[qmax[l]];
        while (l <= r && arr[qmax[r]] <= arr[i])
            r--;
        qmax[++r] = i;
    } */

    mono_queue<int> win;
    vector<int> mins, maxs;
    for (int i = 0, tmp; i < k - 1; i++)
        cin >> tmp, win.push(tmp);

    for (int i = k - 1, tmp; i < n; i++)
    {
        cin >> tmp;
        win.push(tmp);
        mins.push_back(win.min());
        maxs.push_back(win.max());
        win.pop();
    }

    for (auto i : mins)
        cout << i << ' ';
    cout << endl;
    for (auto i : maxs)
        cout << i << ' ';
    return 0;
}