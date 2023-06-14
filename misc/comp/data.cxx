#include <fstream>
#include <random>

using std::endl;

std::ofstream outfile("example.in");

using u8 = char;
using u16 = unsigned short int;

std::random_device seed;
std::mt19937_64 eng(seed());
std::bernoulli_distribution cs(0.5);
std::uniform_int_distribution<u16> rd('a', 'c');
std::uniform_int_distribution<u16> len(1, 10);

int main() {
    u16 n = len(eng), cnt = 0, tmp = 0;
    --n;
    outfile << (u8)rd(eng);
    while (n--) {
        if (cs(eng) && tmp)
            outfile << (u8)(cs(eng) ? (--tmp, 'B') : (++cnt, 'P'));
        else
            outfile << (u8)(++tmp, rd(eng));
    }
    ++cnt;
    outfile << 'P';

    outfile << endl;

    std::uniform_int_distribution<u16> q((cnt >> 1) | 1, cnt);

    n = q(eng);
    outfile << n << endl;
    while (n--) {
        outfile << q(eng) << ' ' << q(eng) << endl;
    }

    return 0;
}
