extern "C" int Seniorious(int);
extern "C" int Chtholly(int n, int c)
{
    int l = 1, r = n;
    while (true)
    {
        int mid = (l + r) >> 1;
        switch (Seniorious(mid))
        {
        case 0:
            return mid;
        case 1:
            r = mid - 1;
            break;
        case -1:
            l = mid + 1;
            break;
        }
    }
    return 0;
}