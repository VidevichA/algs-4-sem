#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

bool comp(pair<int, int> &p1, pair<int, int> &p2)
{
    if (p1.first > p2.first)
        return false;
    if (p2.first > p1.first)
        return true;
    if (p1.second > p2.second)
        return false;
    return true;
}

void Merge(vector<pair<int, int>> &bushes, vector<pair<int, int>> &temp, int left, int middle, int right)
{
    int i = left, k = 0, j = middle + 1;
    while (middle >= i && right >= j)
    {
        if (comp(bushes[i], bushes[j]))
        {
            temp[k] = bushes[i];
            k++;
            i++;
        }
        else
        {
            temp[k] = bushes[j];
            k++;
            j++;
        }
    }
    while (i <= middle)
    {
        temp[k] = bushes[i];
        k++;
        i++;
    }
    while (j <= right)
    {
        temp[k] = bushes[j];
        k++;
        j++;
    }
    k--;
    for (i = right; i >= left; i--)
    {
        bushes[i] = temp[k];
        k--;
    }
}

void MergeSort(vector<pair<int, int>> &bushes, vector<pair<int, int>> &temp, int left, int right)
{
    if (left >= right)
        return;
    int middle = (left + right) / 2;
    MergeSort(bushes, temp, left, middle);
    MergeSort(bushes, temp, middle + 1, right);
    Merge(bushes, temp, left, middle, right);
}

int main()
{
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    int r, c, n, maxBushes = 0, count, deltaX, deltaY, posX, posY;
    fin >> r >> c >> n;
    bool t;
    pair<int, int> p;
    vector<pair<int, int>> bushes(n);
    vector<pair<int, int>> tempV(n);
    for (int i = n - 1; i >= 0; i--)
    {
        fin >> bushes[i].first;
        fin >> bushes[i].second;
    }
    MergeSort(bushes, tempV, 0, n - 1);
    for (int i = 1; i < n; i++)
        for (int j = 0; j < i; j++)
        {
            deltaY = bushes[i].first - bushes[j].first;
            deltaX = bushes[i].second - bushes[j].second;
            if (deltaY < 0)
                continue;
            if (deltaY == 0 && deltaX < 0)
                continue;
            posX = bushes[j].second - deltaX;
            posY = bushes[j].first - deltaY;
            if (posY > 0 && posX > 0 && c > posX)
                continue;
            p.second = bushes[i].second + deltaX;
            p.first = bushes[i].first + deltaY;
            count = 2;
            while (p.first <= r && p.second > 0 && c >= p.second)
            {
                t = binary_search(bushes.begin(), bushes.end(), p);
                if (!t)
                {
                    count = 0;
                    break;
                }
                count++;
                p.second += deltaX;
                p.first += deltaY;
            }
            maxBushes = max(count, maxBushes);
        }
    if (maxBushes > 2)
        fout << maxBushes;
    else
        fout << 0;
    fin.close();
    fout.close();
    return 0;
}