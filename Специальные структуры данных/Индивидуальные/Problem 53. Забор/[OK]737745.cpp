#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>

using namespace std;

int max(int a, int b)
{
    if (a > b)
        return a;
    return b;
}

struct fence
{
    int maxW, maxB, l, r;
    bool lw, rw;
    fence()
    {
        maxW = 0;
        maxB = 0;
        l = 0; // left ttt
        r = 0;
        lw = 0;
        rw = 0;
    }
    fence(int l1, int r1, bool flag = true)
    { // true for all white, false for all black
        maxB = flag ? 0 : r1 - l1 + 1;
        maxW = flag ? r1 - l1 + 1 : 0;
        l = r1 - l1 + 1;
        r = r1 - l1 + 1;
        lw = flag;
        rw = flag;
    }
    friend fence &operator+(fence &l, fence &r)
    {
        fence result;
        result.maxW = max(l.r * l.rw + r.l * r.lw, max(l.maxW, r.maxW));
        result.maxB = max(l.r * (!l.rw) + r.l * (!r.lw), max(l.maxB, r.maxB));
        result.l = l.l;
        result.lw = l.lw;
        result.r = r.r;
        result.rw = r.rw;
        if ((l.maxW == 0 || l.maxB == 0) && l.lw == r.lw)
            result.l += r.l;
        if ((r.maxW == 0 || r.maxB == 0) && l.rw == r.rw)
            result.r += l.r;
        return result;
    }
};

fence a[3000000];

class segTree
{
public:
    void build(int v, int l, int r)
    {
        if (l == r)
        {
            a[v] = fence(l, r);
            return;
        }
        int middle = (l + r) >> 1;
        build(v * 2, l, middle);
        build(v * 2 + 1, middle + 1, r);
        a[v] = a[v * 2] + a[v * 2 + 1];
    }
    fence get(int v, int l, int r, int l1, int r1)
    {
        if (l > r)
            return fence();
        if (l1 == l && r1 == r)
            return a[v];
        if (a[v].maxW == 0)
            return fence(l1, r1, false);
        int middle = (l + r) >> 1;
        if (r1 <= middle)
            return get(v * 2, l, middle, l1, r1);
        if (l1 > middle)
            return get(v * 2 + 1, middle + 1, r, l1, r1);

        fence left = get(v * 2, l, middle, l1, middle);
        fence right = get(v * 2 + 1, middle + 1, r, middle + 1, r1);
        return left + right;
    }
    void update(int v, int l, int r, int l1, int r1)
    {
        if (l > r)
            return;
        if (a[v].maxW == 0)
            return;
        if (l1 == l && r1 == r)
        {
            a[v] = fence(l, r, false);
            return;
        }
        int middle = (l + r) >> 1;
        if (r1 <= middle)
            update(v * 2, l, middle, l1, r1);
        else if (l1 > middle)
            update(v * 2 + 1, middle + 1, r, l1, r1);
        else
        {
            update(v * 2, l, middle, l1, middle);
            update(v * 2 + 1, middle + 1, r, middle + 1, r1);
        }
        a[v] = a[v * 2] + a[v * 2 + 1];
    }
};

int main()
{
    int n = 1000000;
    segTree t;
    t.build(1, 0, n - 1);
    FILE *input = fopen("fence.in", "r+");
    FILE *output = fopen("fence.out", "w+");
    char c;
    int l, r;
    fence f;
    fscanf(input, "%c", &c);
    while (c != 'F')
    {
        l -= 1;
        r -= 1;
        if (c == 'L')
        {
            fscanf(input, "%d %d", &l, &r);
            t.update(1, 0, n - 1, l, r);
        }
        else if (c == 'W')
        {
            fscanf(input, "%d %d", &l, &r);
            f = t.get(1, 0, n - 1, l, r);
            fprintf(output, "%d %d\n", f.maxW, f.maxB);
        }
        fscanf(input, "%c", &c);
    }
    fclose(input);
    fclose(output);
    return 0;
}