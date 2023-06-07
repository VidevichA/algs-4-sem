#include <iostream>
#include <vector>
#include <iomanip>
#include "fstream"

using namespace std;

struct order
{
    double a;
    double b;
    double d;
};

struct PriorityQueue
{
private:
    vector<order> A;

    int PARENT(int i)
    {
        return (i - 1) / 2;
    }

    int LEFT(int i)
    {
        return (2 * i + 1);
    }

    int RIGHT(int i)
    {
        return (2 * i + 2);
    }

    void heapify_down(int i)
    {
        int left = LEFT(i);
        int right = RIGHT(i);

        int largest = i;

        if (left < size() && A[left].a > A[i].a)
        {
            largest = left;
        }

        if (right < size() && A[right].a > A[largest].a)
        {
            largest = right;
        }

        if (largest != i)
        {
            swap(A[i], A[largest]);
            heapify_down(largest);
        }
    }

    void heapify_up(int i)
    {

        if (i && A[PARENT(i)].a < A[i].a)
        {

            swap(A[i], A[PARENT(i)]);
            heapify_up(PARENT(i));
        }
    }

public:
    unsigned int size()
    {
        return A.size();
    }

    bool empty()
    {
        return size() == 0;
    }

    void push(order o)
    {
        A.push_back(o);
        int index = size() - 1;
        heapify_up(index);
    }

    bool pop()
    {
        if (size() == 0)
        {
            return false;
        }

        A[0] = A.back();
        A.pop_back();
        heapify_down(0);
        return true;
    }

    order top()
    {
        return A[0];
    }
};

int comp(const void *o1, const void *o2)
{
    if ((*(order *)o1).d - (*(order *)o2).d != 0)
    {
        return (*(order *)o1).d - (*(order *)o2).d;
    }
    else
        return (*(order *)o1).a - (*(order *)o2).a;
}

using namespace std;

int main()
{
    ifstream cin("lazy.in");
    ofstream cout("lazy.out");
    int n;
    cin >> n;
    auto *orders = new order[n];
    double ans = 0;
    double t = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> orders[i].a >> orders[i].b >> orders[i].d;
    }
    qsort(orders, n, sizeof(order), comp);
    t += orders[0].b;
    if (orders[0].b > orders[0].d)
    {
        ans += (orders[0].b - orders[0].d) / orders[0].a;
        orders[0].b = orders[0].d;
        t = orders[0].d;
    }
    PriorityQueue q1;
    if (orders[0].b != 0)
    {
        q1.push(orders[0]);
    }
    for (int i = 1; i < n; i++)
    {
        t += orders[i].b;
        if (orders[i].b != 0)
        {
            q1.push(orders[i]);
        }
        while (t > orders[i].d)
        {
            order temp = q1.top();
            if (t - orders[i].d < temp.b)
            {
                ans += (t - orders[i].d) / temp.a;
                temp.b -= (t - orders[i].d);
                t = orders[i].d;
                q1.pop();
                if (temp.b > 0)
                {
                    q1.push(temp);
                }
            }
            else
            {
                ans += temp.b / temp.a;
                q1.pop();
                t -= temp.b;
            }
        }
    }
    cout << fixed << setprecision(2) << ans;
    return 0;
}