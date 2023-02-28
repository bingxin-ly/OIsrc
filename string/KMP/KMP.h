// 前缀函数与 KMP 算法: https://oi-wiki.org/string/kmp/
#include <vector>
#include <string>
using std::string;
using std::vector;

/**
 * @deprecated Native implementation, O(n^3)
 */
vector<int> prefix_fun_(string &s)
{
    int sz = s.size();
    vector<int> pi(sz);
    for (int i = 1; i < sz; i++)
        for (int j = i; j >= 0; j--)
            if (s.substr(0, j) == s.substr(i - j + 1, j))
            {
                pi[i] = j;
                break;
            }
    return pi;
}

/**
 * @deprecated Native implementation, O(n^2)
 */
vector<int> prefix_fun__(string &s)
{
    int sz = s.size();
    vector<int> pi(sz);
    for (int i = 1; i < sz; i++)
        for (int j = pi[i - 1] + 1; j >= 0; j--) // improved: j=i => j=pi[i-1]+1
            if (s.substr(0, j) == s.substr(i - j + 1, j))
            {
                pi[i] = j;
                break;
            }
    return pi;
}

/**
 * @brief Searching for the pi substring. Last implementation
 */
vector<int> prefix_fun(string &s)
{
    int n = s.size();
    vector<int> pi(n);
    for (int i = 1; i < n; i++)
    {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j])
            j = pi[j - 1];
        if (s[i] == s[j])
            j++; // found
        pi[i] = j;
    }
    return pi;
}

/**
 * @brief KMP: Searching for the substrings
 */
vector<int> find_occurences(string text, string pattern)
{
    string cur = pattern + "#" + text;
    int n = text.size(), m = pattern.size();
    vector<int> v;
    vector<int> lps = prefix_fun(cur);
    for (int i = m + 1; i <= n + m; i++)
    {
        if (lps[i] == m)
            v.push_back(i - 2 * m);
    }
    return v;
}
