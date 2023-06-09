#include <iostream>
#include <fstream>
#include <queue>

static int idx = 0;
static int n;
static long *numbers;
static int input_value;

struct pair
{
    int count_of_used;
    int value;
    pair(int count_of_used, int value)
    {
        this->value = value;
        this->count_of_used = count_of_used;
        numbers[idx] = value;
        idx++;
    }
};

bool operator<(const pair &first, const pair &second)
{
    long long first_sum;
    long long second_sum;
    if (first.count_of_used < idx)
    {
        first_sum = first.value + numbers[first.count_of_used];
    }
    else
        first_sum = first.value;

    if (first.count_of_used < idx)
    {
        second_sum = second.value + numbers[second.count_of_used];
    }
    else
        second_sum = second.value;

    return first_sum >= second_sum;
}

bool operator<=(const pair &first, const pair &second)
{
    long first_sum;
    long second_sum;
    if (first.count_of_used < idx)
    {
        first_sum = first.value + numbers[first.count_of_used];
    }
    else
        first_sum = first.value;

    if (first.count_of_used < idx)
    {
        second_sum = second.value + numbers[second.count_of_used];
    }
    else
        second_sum = second.value;
    return first_sum > second_sum;
}

bool operator>(const pair &first, const pair &second)
{
    long first_sum;
    long second_sum;
    if (first.count_of_used < idx)
    {
        first_sum = first.value + numbers[first.count_of_used];
    }
    else
        first_sum = first.value;

    if (first.count_of_used < idx)
    {
        second_sum = second.value + numbers[second.count_of_used];
    }
    else
        second_sum = second.value;
    return first_sum <= second_sum;
}

bool operator>=(const pair &first, const pair &second)
{
    long first_sum;
    long second_sum;
    if (first.count_of_used < idx)
    {
        first_sum = first.value + numbers[first.count_of_used];
    }
    else
        first_sum = first.value;

    if (first.count_of_used < idx)
    {
        second_sum = second.value + numbers[second.count_of_used];
    }
    else
        second_sum = second.value;
    return first_sum < second_sum;
}

static std::priority_queue<pair> first_queue, second_queue;

int main()
{
    std::ifstream input("input.txt");
    input >> n;
    input >> input_value;
    int first = input_value / 2;
    numbers = new long[n];
    first_queue.push(pair(1, first));
    while (idx < n)
    {
        input >> input_value;
        if (first_queue.empty() || (first_queue.top().value + numbers[first_queue.top().count_of_used] > input_value))
        {
            first_queue.push(pair(1, input_value - numbers[0]));
            int size = second_queue.size();
            for (int i = 0; i < size; i++)
            {
                first_queue.push(second_queue.top());
                second_queue.pop();
            }
        }
        else
        {
            pair top = first_queue.top();
            top.count_of_used++;
            if (top.count_of_used >= idx)
            {
                first_queue.pop();
                second_queue.push(top);
            }
            else
            {
                first_queue.pop();
                first_queue.push(top);
            }
        }
    }

    std::ofstream output("output.txt");
    for (int i = 0; i < n; ++i)
    {
        output << numbers[i] << "\n";
    }
    input.close();
    output.close();
}