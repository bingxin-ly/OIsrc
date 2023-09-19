#include <algorithm>
class MinStack {
   public:
    int idx, stk[105], mnv[105];
    /** initialize your data structure here. */
    MinStack() { idx = 0, mnv[idx] = 1 << 30; }

    void push(int x) {
        idx += 1;
        stk[idx] = x;
        mnv[idx] = std::min(mnv[idx - 1], x);
    }

    void pop() { idx--; }

    int top() { return stk[idx]; }

    int getMin() { return mnv[idx]; }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack obj = new MinStack();
 * obj.push(x);
 * obj.pop();
 * int param_3 = obj.top();
 * int param_4 = obj.getMin();
 */