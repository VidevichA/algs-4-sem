//! C++20
#include <fstream>

using namespace std;

#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class SegmentTree
{
private:
    long long *tree;
    int length;

    long long recFindSum(int left, int right, int curLeft, int curRight, int current)
    {
        if (left == curLeft && right == curRight)
        {
            return tree[current];
        }
        int toCmp = (curLeft + curRight) / 2;
        if (left >= toCmp)
        {
            return recFindSum(left, right, toCmp, curRight, current * 2 + 2);
        }
        if (right <= toCmp)
        {
            return recFindSum(left, right, curLeft, toCmp, current * 2 + 1);
        }

        return recFindSum(toCmp, right, toCmp, curRight, current * 2 + 2) +
               recFindSum(left, toCmp, curLeft, toCmp, current * 2 + 1);
    }

public:
    explicit SegmentTree(int length, int *values = nullptr)
    {
        if (values == nullptr)
        {
            values = new int[length];
            for (int i = 0; i < length; ++i)
            {
                values[i] = 0;
            }
        }
        tree = new long long[4 * length];
        this->length = length;
        if (length == 1)
        {
            tree[0] = values[0];
            return;
        }
        for (int i = 0; i < 4 * length; ++i)
        {
            tree[i] = INT32_MIN;
        }
        int *currentBound = new int[]{0, length / 2};
        int current = 1;
        stack<int *> bounds;
        bounds.push(new int[]{0, length});
        while (true)
        {
            if (current == 0 && tree[1] != INT32_MIN && tree[2] != INT32_MIN)
            {
                tree[0] = tree[1] + tree[2];
                break;
            }
            if (currentBound[1] - currentBound[0] == 1)
            {
                tree[current] = values[currentBound[0]];
                current % 2 == 0 ? current = current / 2 - 1 : current /= 2;
                delete[] currentBound;
                currentBound = bounds.top();
                bounds.pop();
                continue;
            }
            if (tree[current * 2 + 1] == INT32_MIN)
            {
                bounds.push(currentBound);
                currentBound = new int[]{currentBound[0], (currentBound[1] + currentBound[0]) / 2};
                current = 2 * current + 1;
                continue;
            }
            if (tree[current * 2 + 2] == INT32_MIN)
            {
                bounds.push(currentBound);
                currentBound = new int[]{(currentBound[1] + currentBound[0]) / 2, currentBound[1]};
                current = 2 * current + 2;
                continue;
            }
            tree[current] = tree[current * 2 + 1] + tree[current * 2 + 2];
            current % 2 == 0 ? current = current / 2 - 1 : current /= 2;
            delete[] currentBound;
            currentBound = bounds.top();
            bounds.pop();
        }
    }

    void add(int i, int x)
    {
        int current = 0;
        int left = 0, right = length;
        while (left != i || right != (i + 1))
        {
            tree[current] += x;
            int bound = (left + right) / 2;
            if (i >= bound)
            {
                left = bound;
                current = 2 * current + 2;
            }
            else
            {
                right = bound;
                current = 2 * current + 1;
            }
        }
        tree[current] += x;
    }

    long long findSum(int leftBound, int rightBound)
    {
        return recFindSum(leftBound, rightBound, 0, length, 0);
    }

    ~SegmentTree()
    {
        delete[] tree;
    }
};

int main()
{
    ifstream reader("chords.in");
    int n;
    reader >> n;
    auto sums = new SegmentTree(2 * n);
    int *lines = new int[2 * n];

    for (int i = 0; i < n; ++i)
    {
        int a, b;
        reader >> a >> b;
        if (a < b)
        {
            lines[a - 1] = b - 1;
            lines[b - 1] = -(a - 1);
        }
        else
        {
            lines[b - 1] = a - 1;
            lines[a - 1] = -(b - 1);
        }
    }
    long long answer = 0;
    for (int i = 0; i < 2 * n; ++i)
    {
        if (lines[i] >= 0)
        {
            sums->add(i, 1);
        }
        else
        {
            sums->add(-lines[i], -1);
            answer += sums->findSum(-lines[i], i);
        }
    }
    ofstream writer("chords.out");
    writer << answer;
    delete sums;
    delete[] lines;
}