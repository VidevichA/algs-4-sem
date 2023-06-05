#include <fstream>
#include <vector>
#include <queue>

long long huffmanCoding(std::vector<long long> &freq)
{
    std::priority_queue<long long, std::vector<long long>, std::greater<>> pq;
    for (long long i : freq)
    {
        pq.push(i);
    }

    long long ans = 0;
    while (pq.size() > 1)
    {
        long long x = pq.top();
        pq.pop();
        long long y = pq.top();
        pq.pop();
        long long sum = x + y;
        ans += sum;
        pq.push(sum);
    }

    return ans;
}

int main()
{
    std::ifstream fin("common/data_struct/huffman/huffman.in");
    std::ofstream ofStream("common/data_struct/huffman/huffman.out");
    int n;
    fin >> n;
    std::vector<long long> a(n);
    for (int i = 0; i < n; i++)
    {
        fin >> a[i];
    }
    ofStream << huffmanCoding(a);

    return 0;
}