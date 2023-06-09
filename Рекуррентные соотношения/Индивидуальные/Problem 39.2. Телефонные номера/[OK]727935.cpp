#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <fstream>

#define MAXWORDS 50000
#define MAXNUMBER 100001
#define INF 2147483647
#define BUCKETSIZE 11

using namespace std;

int8_t code[] = {
    2, // A
    2, // B
    2, // C
    3, // D
    3, // E
    3, // F
    4, // G
    4, // H
    1, // I
    1, // J
    5, // K
    5, // L
    6, // M
    6, // N
    0, // O
    7, // P
    0, // Q
    7, // R
    7, // S
    8, // T
    8, // U
    8, // V
    9, // W
    9, // X
    9, // Y
    0, // Z
};

int8_t charToInt(char c)
{
    if (c >= '0' && c <= '9')
        return (int8_t)(c - '0');
    return (int8_t)code[c - 'A'];
}

struct beginning
{
    bool cantBe = true;
    int numberOfWords = INF;
    int wordId = 0;
};

struct word
{
    int id;
    int length;
};

void read(int &n, int &m, int &maxLength, vector<int8_t> &number, vector<string> &words, vector<word> &wordsIDs, vector<vector<int8_t>> &decimalRepresentation)
{
    ifstream fin("input.txt");
    char c;
    while (fin.get(c))
    {
        if (c == '\n')
            break;
        number[n] = (int8_t)(c - '0');
        n++;
    }
    fin >> m;
    for (int i = 0; i < m; i++)
    {
        fin >> words[i];
        wordsIDs[i].id = i;
        wordsIDs[i].length = (int)words[i].size();
        for (int j = 0; j < wordsIDs[i].length; j++)
            decimalRepresentation[i][j] = charToInt(words[i][j]);
        maxLength = maxLength < wordsIDs[i].length ? wordsIDs[i].length : maxLength;
    }
    fin.close();
}

void sortLine(int &m, int &rowId, vector<word> &wordsIDs, vector<word> &wordsIDs2, vector<vector<int8_t>> &decimalRepresentation, vector<vector<int8_t>> &decimalRepresentation2)
{ // counting sort  for row with id rowId
    int bucket[BUCKETSIZE];
    int value;
    int positionNumber;
    for (int i = BUCKETSIZE - 1; i >= 0; i--)
        bucket[i] = 0;
    for (int i = m - 1; i >= 0; i--)
    {
        if (wordsIDs[i].length < rowId)
        {
            value = 0;
        }
        else
            value = 1 + decimalRepresentation[i][rowId];
        bucket[value]++;
    }
    for (int i = 1; i < BUCKETSIZE; i++)
        bucket[i] += bucket[i - 1];
    for (int i = m - 1; i >= 0; i--)
    {
        if (wordsIDs[i].length < rowId)
        {
            value = 0;
        }
        else
            value = 1 + decimalRepresentation[i][rowId];
        positionNumber = bucket[value] - 1;
        bucket[value]--;
        decimalRepresentation2[positionNumber] = decimalRepresentation[i];
        wordsIDs2[positionNumber] = wordsIDs[i];
    }
    for (int i = m - 1; i >= 0; i--)
    {
        decimalRepresentation[i] = decimalRepresentation2[i];
        wordsIDs[i] = wordsIDs2[i];
    }
}

void radixSort(int &m, int &maxLength, vector<word> &wordsIDs, vector<vector<int8_t>> &decimalRepresentation)
{
    vector<word> wordsIDs2(MAXWORDS);
    vector<vector<int8_t>> decimalRepresentation2(MAXWORDS, vector<int8_t>(100));
    for (int i = maxLength - 1; i >= 0; i--)
        sortLine(m, i, wordsIDs, wordsIDs2, decimalRepresentation, decimalRepresentation2);
}

void lowerBound(int &l, int &r, int &rowID, int8_t targetValue, vector<word> &wordsIDs, vector<vector<int8_t>> &decimalRepresentation)
{
    int middle;
    while (l < r)
    {
        middle = (l + r) / 2;
        if (wordsIDs[middle].length <= rowID)
        {
            l = middle + 1;
            continue;
        }
        if (targetValue <= decimalRepresentation[middle][rowID])
            r = middle;
        else
            l = middle + 1;
    }
}

void upperBound(int &l, int &r, int &rowID, int8_t targetValue, vector<word> &wordsIDs, vector<vector<int8_t>> &decimalRepresentation)
{
    int middle;
    while (l < r)
    {
        middle = (l + r) / 2;
        if (wordsIDs[middle].length <= rowID)
        {
            l = middle + 1;
            continue;
        }
        if (targetValue < decimalRepresentation[middle][rowID])
            r = middle;
        else
            l = middle + 1;
    }
}

void dpFunc(int &n, int &m, int &maxLength, vector<int8_t> &number, vector<beginning> &dp, vector<vector<int8_t>> &decimalRepresentation, vector<word> &wordsIDs)
{
    int length, start, end, l, r, temp;
    for (int i = 0; i < n; i++)
    {
        if (dp[i].cantBe)
            continue;
        length = min(maxLength, n - i);
        start = 0;
        end = m;
        for (int j = 0; j < length; j++)
        {
            l = start;
            r = end;
            lowerBound(l, r, j, number[i + j], wordsIDs, decimalRepresentation);
            if (l >= end)
                break;
            start = l;
            r = end;
            upperBound(l, r, j, number[i + j], wordsIDs, decimalRepresentation);
            end = l;
            if (wordsIDs[start].length != j + 1 || decimalRepresentation[start][j] != number[i + j])
                continue;
            temp = i + j + 1;
            dp[temp].cantBe = false;
            if (dp[temp].numberOfWords > 1 + dp[i].numberOfWords)
            {
                dp[temp].numberOfWords = dp[i].numberOfWords + 1;
                dp[temp].wordId = start;
            }
        }
    }
}

void writeAnswer(int &n, vector<beginning> &dp, vector<string> &words, vector<word> &wordsIDs)
{
    ofstream fout("output.txt");
    stack<string> result;
    int temp;
    if (dp[n].cantBe)
    {
        fout << "No solution";
    }
    else
    {
        fout << dp[n].numberOfWords << endl;
        temp = n;
        while (temp > 0)
        {
            result.push(words[wordsIDs[dp[temp].wordId].id]);
            temp -= wordsIDs[dp[temp].wordId].length;
        }
        while (!result.empty())
        {
            fout << result.top() << ' ';
            result.pop();
        }
    }
    fout.close();
}

int main()
{
    int n = 0, m, maxLength = 0;
    vector<int8_t> number(MAXNUMBER);
    vector<string> words(MAXWORDS);
    vector<word> wordsIDs(MAXWORDS);
    vector<vector<int8_t>> decimalRepresentation(MAXWORDS, vector<int8_t>(100, 0));
    vector<beginning> dp(MAXNUMBER);

    dp[0].cantBe = false;
    dp[0].numberOfWords = 0;

    read(n, m, maxLength, number, words, wordsIDs, decimalRepresentation);
    radixSort(m, maxLength, wordsIDs, decimalRepresentation);
    dpFunc(n, m, maxLength, number, dp, decimalRepresentation, wordsIDs);
    writeAnswer(n, dp, words, wordsIDs);
    return 0;
}