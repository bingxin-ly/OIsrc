#include <bits/stdc++.h>
#define int long long
using namespace std;

const int MOD = 1e9 + 7;
int from = -1, cache = -1, now;
int qpow(int a, int k)
{
    a %= MOD;
    int res = 1;
    while (k)
    {
        if (k & 1)
            res = res * a % MOD;
        a = a * a % MOD;
        k >>= 1;
    }
    return res;
}
namespace segtr
{
    struct data
    {
        int len, llen, rlen;
        int sum, lsum, rsum;
        short op;

        void update(const data *a, const data *b)
        {
            len = a->len + b->len;
            op = b->op;
            sum = a->op ? (((a->sum + b->sum) % MOD + a->rsum * b->lsum % MOD - a->rsum - b->lsum) % MOD + MOD) % MOD
                        : (a->sum + b->sum) % MOD;

            // 左连乘
            if (a->op && a->llen == a->len)
                lsum = a->sum * b->lsum % MOD,
                llen = a->len + b->llen;
            else
                lsum = a->lsum,
                llen = a->llen;

            // 右连乘
            if (a->op && b->rlen == b->len)
                rsum = b->sum * a->rsum % MOD,
                rlen = b->len + a->rlen;
            else
                rsum = b->rsum,
                rlen = b->rlen;
        }
    };
    struct node : data
    {
        node *ls, *rs;
        int l, r;

        int addsum, mulsum;
        int lval, rval, valtag;
        short optag;
        int *cnt, cntlen;
        vector<int> cntv;

        node(int l_, int r_) : data(), l(l_), r(r_)
        {
            ls = rs = nullptr;
            optag = valtag = -1;
            len = r - l + 1, cntlen = sqrt(len), cnt = new int[cntlen + 2]();
        }

        void pushup(const node *a, const node *b)
        {
            addsum = (a->addsum + b->addsum) % MOD;
            mulsum = (a->mulsum * b->mulsum) % MOD;

            lval = a->lval, rval = b->rval;
            update((data *)a, (data *)b);
            //            optag = valtag = -1;

            for (int i = 1; i <= cntlen; ++i)
                cnt[i] = 0;
            cntv.clear();
            for (int i = 1; i <= cntlen; i++)
                assert(cnt[i] == 0);
            for (int i = 1, up = sqrt(a->len); i <= up; ++i)
                cnt[i] += a->cnt[i];
            for (int i = 1, up = sqrt(b->len); i <= up; ++i)
                cnt[i] += b->cnt[i];
            auto it1 = a->cntv.begin(), it2 = b->cntv.begin(),
                 ed1 = a->cntv.end(), ed2 = b->cntv.end();

            while (it1 != ed1 && it2 != ed2)
            {
                if ((*it1) < (*it2))
                {
                    if (*it1 <= cntlen)
                        cnt[*it1] += 1;
                    else
                        cntv.emplace_back(*it1);
                    it1++;
                }
                else if ((*it1) > (*it2))
                {
                    if (*it2 <= cntlen)
                        cnt[*it2] += 1;
                    else
                        cntv.emplace_back(*it2);
                    it2++;
                }
                else
                {
                    if ((*it1) <= cntlen)
                        cnt[*it1] += 2;
                    else
                        cntv.emplace_back(*it1), cntv.emplace_back(*it2);
                    it1++, it2++;
                }
            }
            while (it1 != ed1)
            {
                if (*it1 <= cntlen)
                    cnt[*it1] += 1;
                else
                    cntv.emplace_back(*it1);
                it1++;
            }
            while (it2 != ed2)
            {
                if (*it2 <= cntlen)
                    cnt[*it2] += 1;
                else
                    cntv.emplace_back(*it2);
                it2++;
            }

            if (a->op)
            {
                if (a->rlen <= cntlen)
                    cnt[a->rlen]--;
                else
                    cntv.erase(lower_bound(cntv.begin(), cntv.end(), a->rlen));
                if (b->llen <= cntlen)
                    cnt[b->llen]--;
                else
                    cntv.erase(lower_bound(cntv.begin(), cntv.end(), b->llen));
                int nlen = a->rlen + b->llen;
                if (nlen <= cntlen)
                    cnt[nlen]++;
                else
                    cntv.insert(lower_bound(cntv.begin(), cntv.end(), nlen), nlen);
            }
        }
        void opdown(short op_)
        {
            op = optag = op_;
            if (op) // MUL
            {
                sum = lsum = rsum = mulsum;
                llen = rlen = len;
                for (int i = 1; i <= cntlen; ++i)
                    cnt[i] = 0;
                cntv.clear();
                for (int i = 1; i <= cntlen; i++)
                    assert(cnt[i] == 0);

                if (len <= cntlen)
                    cnt[len] = 1;
                else
                    cntv.emplace_back(len);
            }
            else
            {
                sum = addsum;
                lsum = lval, rsum = rval;
                llen = rlen = 1;
                for (int i = 1; i <= cntlen; ++i)
                    cnt[i] = 0;
                cntv.clear(), cnt[1] = len;
            }
        }

        void valdown(int val)
        {
            val %= MOD;
            lval = rval = valtag = val;
            addsum = val * len % MOD;
            mulsum = qpow(val, len), lsum = qpow(val, llen), rsum = qpow(val, rlen);
            sum = 0;
            for (int i = 1; i <= cntlen; i++)
            {
                // sum += qpow(val, i) * cnt[i], sum %= MOD;
                if (cnt[i])
                {
                    if (from != val || now > i)
                    {
                        cache = qpow(val, i) % MOD;
                        sum += cache * cnt[i];
                        from = val;
                        now = i;
                    }
                    else
                    {
                        cache = cache * qpow(val, i - now) % MOD;
                        sum += cache * cnt[i];
                        now = i;
                    }
                    sum %= MOD;
                }
            }
            auto it = cntv.begin();
            auto ed = cntv.end();
            while (it != ed)
            {
                // sum += qpow(val, *it);
                if (from != val || now > (*it))
                {
                    cache = qpow(val, (*it)) % MOD;
                    sum += cache;
                    from = val;
                    now = (*it);
                }
                else
                {
                    cache = cache * qpow(val, (*it) - now) % MOD;
                    sum += cache;
                    now = (*it);
                }
                sum %= MOD;
                it++;
            }
        }
        void pushdown()
        {
            if (optag != -1)
            {
                ls->opdown(optag), rs->opdown(optag);
                optag = -1;
            }
            if (valtag != -1)
            {
                ls->valdown(valtag), rs->valdown(valtag);
                valtag = -1;
            }
        }
    } *root;

    void build(node *&o, int l, int r, const int *arr, const short *ops)
    {
        o = new node(l, r);
        if (l == r)
        {
            o->op = ops[l];
            o->llen = o->rlen = 1;
            o->sum = o->addsum = o->mulsum = o->lsum = o->rsum =
                o->lval = o->rval = arr[l] % MOD;
            o->cnt[1] = 1;
            return;
        }
        int mid = (l + r) >> 1;
        build(o->ls, l, mid, arr, ops), build(o->rs, mid + 1, r, arr, ops);
        o->pushup(o->ls, o->rs);
    }

    data query(node *o, int l, int r)
    {
        if (o->l == l && o->r == r)
            return *((data *)o);

        o->pushdown();
        int mid = (o->l + o->r) >> 1;
        if (r <= mid)
            return query(o->ls, l, r);
        else if (l > mid)
            return query(o->rs, l, r);
        else
        {
            data ret, ls = query(o->ls, l, mid), rs = query(o->rs, mid + 1, r);
            ret.update(&ls, &rs);
            return ret;
        }
    }

    void change_op(node *o, int l, int r, const short op)
    {
        if (o->l == l && o->r == r)
            return o->opdown(op);

        o->pushdown();
        int mid = (o->l + o->r) >> 1;
        if (r <= mid)
            change_op(o->ls, l, r, op);
        else if (l > mid)
            change_op(o->rs, l, r, op);
        else
            change_op(o->ls, l, mid, op), change_op(o->rs, mid + 1, r, op);
        o->pushup(o->ls, o->rs);
    }

    void change_val(node *o, int l, int r, const int val)
    {
        if (o->l == l && o->r == r)
            return o->valdown(val);

        o->pushdown();
        int mid = (o->l + o->r) >> 1;
        if (r <= mid)
            change_val(o->ls, l, r, val);
        else if (l > mid)
            change_val(o->rs, l, r, val);
        else
            change_val(o->ls, l, mid, val), change_val(o->rs, mid + 1, r, val);
        o->pushup(o->ls, o->rs);
    }
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    int arr[n + 1];
    for (int i = 1; i <= n; ++i)
        cin >> arr[i];
    short ops[n];
    for (int i = 1; i < n; ++i)
        cin >> ops[i];

    segtr::build(segtr::root, 1, n, arr, ops);
    while (m--)
    {
        short op;
        int l, r;
        cin >> op >> l >> r;
        switch (op)
        {
        case 1:
            int val;
            cin >> val;
            segtr::change_val(segtr::root, l, r, val);
            break;
        case 2:
            short ope;
            cin >> ope;
            segtr::change_op(segtr::root, l, r, ope);
            break;
        case 3:
            cout << segtr::query(segtr::root, l, r).sum << '\n';
            break;
        }
    }
    return 0;
}