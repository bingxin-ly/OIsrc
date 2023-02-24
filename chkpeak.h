#define chkmax(a, b) a = max(a, b)
#define chkmax(a, b) b > a ? a = b : a
#undef chkmax
template <typename T>
inline void chkmax(T &a, T b)
{
    a = max(a, b);
}
#define chkmin(a, b) a = min(a, b)
#define chkmin(a, b) b < a ? a = b : a
#undef chkmin
template <typename T>
inline void chkmin(T &a, T b)
{
    a = min(a, b);
}