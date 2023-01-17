#include <vector>
#include <string>
using std::vector;

/**
 * @deprecated Native implementation, O(n^3)
 */
vector<int> prefix_fun(std::string &s)
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
vector<int> prefix_fun(std::string &s)
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
