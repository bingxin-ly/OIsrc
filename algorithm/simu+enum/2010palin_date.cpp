#include <bits/stdc++.h>
using namespace std;

string getdate(int x)
{
    if ((x % 400 == 0) || (x % 4 == 0 && x % 100))
        return "29";
    else
        return "28";
}
unordered_map<string, string> todate{
    {"01", "31"},
    {"03", "31"},
    {"04", "30"},
    {"05", "31"},
    {"06", "30"},
    {"07", "31"},
    {"08", "31"},
    {"09", "30"},
    {"10", "31"},
    {"11", "30"},
    {"12", "31"}};
int main()
{
    int st, ed, cnt = 0;
    cin >> st >> ed;
    stringstream trans;
    trans << st << endl
          << ed << endl;
    string sst, eed;
    trans >> sst >> eed;
    string year = sst.substr(0, 4), month = sst.substr(4, 2), date = sst.substr(6, 2);
    reverse(sst.begin(), sst.begin() + 4);
    if (sst.substr(0, 2) > month && sst.substr(0, 2) <= "12" && (st / 10000 != ed / 10000 || sst.substr(0, 2) <= eed.substr(4, 2)))
        cnt++;
    else if (sst.substr(0, 2) == month && sst.substr(2, 2) >= date)
    {
        if (((sst.substr(0, 2) == "02" && sst.substr(2, 2) <= getdate(st / 10000)) || date <= todate[month]))
            cnt++;
    }
    st /= 10000, ed /= 10000;
    if (st == ed)
    {
        cout << cnt;
        return 0;
    }
    for (int i = st + 1; i < ed; i++)
    {
        trans << i << endl;
        string s;
        trans >> s;
        reverse(s.begin(), s.end());
        string month = s.substr(0, 2), date = s.substr(2, 2);
        if (month > "00" && month <= "12" && date > "00" && ((month == "02" && date <= getdate(i)) || date <= todate[month]))
            cnt++;
    }

    month = eed.substr(4, 2), date = eed.substr(6, 2);
    reverse(eed.begin(), eed.begin() + 4);
    if (eed.substr(0, 2) <= month)
        if (eed.substr(2, 2) <= date)
            cnt++;

    cout << cnt;
    return 0;
}