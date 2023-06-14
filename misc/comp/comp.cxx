#include <cassert>
#include <cstdlib>
#include <fstream>
#include <windows.h>

using std::endl;
std::ofstream cout("compare.log");

void compile() {
    system("clang++ data.cxx -o data.exe -O3 -ffast-math -mavx2 -msse4a -march=native -mtune=native -mbmi -mbmi2 -mfma -mpopcnt -mlzcnt");
    system("g++ std.cxx -o std.exe -O2 -lm");
    system("g++ my.cxx -o my.exe -O2 -lm");
}

bool valid() {
    if (system("diff -u my.out std.out > error.diff")) {
        // FILE* er = popen("cmp my.out std.out", "r");
        cout << "\nError" << endl;
        // system("mshta vbscript:msgbox(\"对拍程序找到了一组导致结果不同的样例！\",64,\"小伞发来一条信息\")(window.close)");
        MessageBox(GetForegroundWindow(), (LPCTSTR)TEXT("对拍程序找到了一组导致结果不同的样例！"), (LPCTSTR)TEXT("小伞发来一条信息"), 16);
        // pclose(er);
        return false;
    } else {
        return true;
    }
}

unsigned long long int cnt;

int main() {
    compile();
    cout << "Success " << std::flush;
    do {
        cout << "# " << ++cnt << ' ' << std::flush;
        system("data.exe");
        system("cat example.in | my.exe > my.out");
        system("cat example.in | std.exe > std.out");
    } while (valid());

    return 0;
}
