#include <fstream>
#include <vector>
#include <cmath>

int main()
{
    std::ifstream inputFile("input.txt");
    int temp;
    inputFile >> temp;
    std::vector<int> elements;
    while (inputFile >> temp)
    {
        elements.push_back(temp);
    }
    std::ofstream outputFile("output.txt");
    if (elements.size() == 1)
    {
        outputFile << 1;
        return 0;
    }
    if (elements.size() == 2)
    {
        outputFile << 2;
        return 0;
    }
    std::vector<int> leastLastElementsOfIncreasingSequences;    // leastLastElementsOfSequences[i] == least last element of increasing sequence which has length i
    std::vector<int> lengthOfIncreasingSequences;               // lengthOfIncreasingSequences[i] == length of increasing sequence which end's with elements[i] (left to right)
    std::vector<int> biggestFirstElementsOfDecreasingSequences; // biggestFirstElementsOfDecreasingSequences[i] == biggest first element of  decreasing sequence which has length i
    std::vector<int> lengthOFDecreasingSequences;               // lengthOFDecreasingSequences[i] == length of decreasing sequence which end's with elements[i]  (left to right)
    lengthOfIncreasingSequences.push_back(0);
    biggestFirstElementsOfDecreasingSequences.push_back(INT_MAX);
    leastLastElementsOfIncreasingSequences.push_back(INT_MIN);
    for (int i = 0; i < elements.size(); ++i)
    {
        leastLastElementsOfIncreasingSequences.push_back(INT_MAX);
        biggestFirstElementsOfDecreasingSequences.push_back(INT_MIN);
    }
    for (int i = 0; i < elements.size(); ++i)
    {
        int leftBorder = 0;
        int rightBorder = leastLastElementsOfIncreasingSequences.size();
        while (leftBorder < rightBorder)
        {
            int middle = (leftBorder + rightBorder) / 2;
            if (elements[i] < leastLastElementsOfIncreasingSequences[middle])
            {
                rightBorder = middle;
            }
            else
            {
                leftBorder = middle + 1;
            }
        }
        if (elements[i] > leastLastElementsOfIncreasingSequences[leftBorder - 1])
        {
            leastLastElementsOfIncreasingSequences[leftBorder] = elements[i];
            lengthOfIncreasingSequences.push_back(leftBorder);
        }
        else
        {
            leftBorder = 0;
            rightBorder = leastLastElementsOfIncreasingSequences.size();
            while (leftBorder < rightBorder)
            {
                int middle = (leftBorder + rightBorder) / 2;
                if (elements[i] <= leastLastElementsOfIncreasingSequences[middle])
                {
                    rightBorder = middle;
                }
                else
                {
                    leftBorder = middle + 1;
                }
            }
            lengthOfIncreasingSequences.push_back(leftBorder);
        }
        leftBorder = 0;
        rightBorder = biggestFirstElementsOfDecreasingSequences.size();
        while (leftBorder < rightBorder)
        {
            int middle = (leftBorder + rightBorder) / 2;
            if (elements[elements.size() - i - 1] >= biggestFirstElementsOfDecreasingSequences[middle])
            {
                rightBorder = middle;
            }
            else
            {
                leftBorder = middle + 1;
            }
        }
        if (elements[elements.size() - i - 1] < biggestFirstElementsOfDecreasingSequences[leftBorder - 1])
        {
            biggestFirstElementsOfDecreasingSequences[leftBorder] = elements[elements.size() - i - 1];
            lengthOFDecreasingSequences.push_back(leftBorder);
        }
        else
        {
            leftBorder = 0;
            rightBorder = biggestFirstElementsOfDecreasingSequences.size();
            while (leftBorder < rightBorder)
            {
                int middle = (leftBorder + rightBorder) / 2;
                if (elements[elements.size() - i - 1] < biggestFirstElementsOfDecreasingSequences[middle])
                {
                    rightBorder = middle;
                }
                else
                {
                    leftBorder = middle + 1;
                }
            }
        }
    }
    std::vector<int> maximumLengthOfSequences;
    for (int i = 0; i < lengthOFDecreasingSequences.size(); ++i)
    {
        if (i == 0)
        {
            maximumLengthOfSequences.push_back(lengthOFDecreasingSequences[i]);
            continue;
        }
        if (i == lengthOFDecreasingSequences.size() - 1)
        {
            maximumLengthOfSequences.push_back(0);
            continue;
        }
        maximumLengthOfSequences.push_back(maximumLengthOfSequences[i - 1] > lengthOFDecreasingSequences[i] ? maximumLengthOfSequences[i - 1] : lengthOFDecreasingSequences[i]);
    }
    int max = 0;
    for (int i = 0; i < elements.size(); ++i)
    {
        max = max > (lengthOfIncreasingSequences[i] + maximumLengthOfSequences[maximumLengthOfSequences.size() - i - 1]) ? max : lengthOfIncreasingSequences[i] + maximumLengthOfSequences[maximumLengthOfSequences.size() - i - 1];
    }
    outputFile << max;
    return 0;
}