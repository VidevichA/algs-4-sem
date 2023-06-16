#include <fstream>
#include <vector>

int count(0);

int find_set(int value, const std::vector<int> &parent)
{
    if (value == parent[value])
        return value;
    else
        find_set(parent[value], parent);
}

void union_sets(int first_parent, int second_parent, std::vector<int> &parent)
{
    first_parent = find_set(first_parent, parent);
    second_parent = find_set(second_parent, parent);
    if (first_parent != second_parent)
    {
        parent[second_parent] = first_parent;
        count--;
    }
}

int main()
{
    std::ifstream in("in.txt");

    int n, m, value;

    in >> n >> m;

    std::vector<int> matrix(n * m, -1), parent(n * m, -1);
    for (int i = 0; i < n * m; ++i)
    {
        in >> value;
        if (!value)
        {
            count++;
            matrix[i] = 0;
            parent[i] = i;
        }
    }
    in.close();

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            if (!matrix[i * m + j])
            {
                if (j < m - 1 && !matrix[i * m + j + 1])
                    union_sets(i * m + j, i * m + j + 1, parent);
                if (i < n - 1 && !matrix[(i + 1) * m + j])
                    union_sets(i * m + j, (i + 1) * m + j, parent);
            }
        }
    }

    std::ofstream out("out.txt");
    out << count;
    out.close();

    return 0;
}