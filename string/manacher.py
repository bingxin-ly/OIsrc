def longestPalindrome5(s):
    """
    :type s: str
    :rtype: str

    马拉车算法。Manacher发明出来的。
    时间复杂度为O(n)。
    """
    if len(s) <= 1:
        return s

    # 每个字符之间插入 \1
    ss = '\0\1' + '\1'.join([x for x in s]) + '\1\2'
    p = [0] * len(ss)
    center = 0
    mx = 0
    max_str = ''
    for i in range(1, len(p) - 1):

        if i < mx:
            j = 2 * center - i  # i 关于 center 的对称点
            p[i] = min(mx - i, p[j])

        # 尝试继续向两边扩展，更新 p[i]
        while ss[i - p[i] - 1] == ss[i + p[i] +
                                     1]:  # 不必判断是否溢出，因为首位均有特殊字符，肯定会退出
            p[i] += 1

        # 更新中心
        if i + p[i] > mx:
            mx = i + p[i]
            center = i

        # 更新最长串
        if 1 + 2 * p[i] > len(max_str):
            max_str = ss[i - p[i]:i + p[i] + 1]

    return max_str.replace('\1', '')

