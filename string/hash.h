#include <string>

const int P = 13331;
const int M = 998244353; // 有时会卡数据
size_t get_hash(std::string &str)
{
    size_t hsh = 0;
    for (auto i : str)
        hsh = (hsh * P + i) % M;
    return hsh;
}
