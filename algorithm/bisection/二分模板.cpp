int find(int low, int high)
{
    int mid;
    while (low + 1 < high)
    {                                 // 找到可行与不可行的分界
        mid = low + (high - low) / 2; // 此处是(low+high)/2的防爆优化
        if (check(mid))               // check函数检查可行性
            low = mid;                // 当可行时[left,mid]也可行
        else
            high = mid; // 当不可行时[mid,high]也不可行
    }
    return low; // 由于low表示可行，返回low
}
