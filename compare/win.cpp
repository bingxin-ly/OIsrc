#include <bits/stdc++.h>
using namespace std;

int main()
{
    long s, t;
    while (true)
    {
        system("cls");
        while (true)
        {
            system("data.exe > data.in"); // data是数据生成程序
            s = clock();
            system("test.exe < data1.in > data1.out"); // a是要交的程序
            t = clock();
            system("std.exe < data2.in > data2.out"); // b是正确的程序
            if (system("fc data1.out data2.out > nul"))
                break;
            else
                printf("AC, time: %ldms\n", t - s);
        }
        printf("WA, time: %ldms\n", t - s); // 运行时间
        system("fc data1.out data2.out");
        system("pause");
    }
    return 0;
}
