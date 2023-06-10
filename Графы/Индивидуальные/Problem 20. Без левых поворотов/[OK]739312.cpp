#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>
#include <vector>

std::ifstream fin;
std::ofstream fout;
std::vector<long long> way;

class Point
{
private:
    long long x;
    long long y;

public:
    Point()
    {
        this->x = 0;
        this->y = 0;
    }
    Point(long long x_, long long y_)
    {
        this->x = x_;
        this->y = y_;
    }
    void setX(long long x_)
    {
        this->x = x_;
    }
    void setY(long long y_)
    {
        this->y = y_;
    }
    long long getX()
    {
        return this->x;
    }

    long long getY()
    {
        return this->y;
    }

    bool operator==(Point point)
    {
        return this->x == point.getX() && this->y == point.getY();
    }

    bool operator!=(Point point)
    {
        return !(*this == point);
    }
};

class Crossroad
{
private:
    Point coordinates;
    long long number;

public:
    Crossroad()
    {
        this->number = 0;
    }
    Crossroad(long long x, long long y, long long number)
    {
        this->coordinates.setX(x);
        this->coordinates.setY(y);
        this->number = number;
    }
    Crossroad(Point point, long long number)
    {
        this->coordinates = point;
        this->number = number;
    }

    long long getX()
    {
        return this->coordinates.getX();
    }

    long long getY()
    {
        return this->coordinates.getY();
    }

    Point getCoordinates()
    {
        return this->coordinates;
    }

    long long getNumber()
    {
        return this->number;
    }

    bool operator==(Crossroad crossroad)
    {
        return this->coordinates == crossroad.getCoordinates();
    }

    bool operator!=(Crossroad crossroad)
    {
        return !(*this == crossroad);
    }
};

bool WentRightOrAhead(long long x1, long long y1,
                      long long x2, long long y2,
                      long long x3, long long y3)
{
    return (x1 * y2 + y3 * x2 + x3 * y1 - x3 * y2 - x2 * y1 - x1 * y3) <= 0;
}

void FillInAdjacencyMatrix(std::vector<std::vector<bool>> &adjacencyMatrix,
                           std::vector<std::pair<Crossroad, Crossroad>> &roads)
{
    for (auto &road : roads)
    {
        adjacencyMatrix[road.first.getNumber()][road.second.getNumber()] = true;
        adjacencyMatrix[road.second.getNumber()][road.first.getNumber()] = true;
    }
}

bool DFS(long long start, long long finish, long long beforeStart,
         std::vector<std::vector<bool>> &adjacencyMatrix, std::vector<std::vector<bool>> &involvedEdges,
         std::vector<Crossroad> &crossroads)
{
    if (start == finish)
    {
        return true;
    }
    for (long long i = 1; i < adjacencyMatrix.size(); i++)
    {
        if (beforeStart == 0 && crossroads[beforeStart].getX() == crossroads[i].getX() &&
            crossroads[beforeStart].getY() >= crossroads[i].getY())
        {
            continue;
        }
        else if (i != beforeStart && adjacencyMatrix[start][i] && !involvedEdges[start][i] && WentRightOrAhead(crossroads[beforeStart].getX(), crossroads[beforeStart].getY(), crossroads[start].getX(), crossroads[start].getY(), crossroads[i].getX(), crossroads[i].getY()))
        {
            involvedEdges[start][i] = true;
            if (DFS(i, finish, start, adjacencyMatrix, involvedEdges, crossroads))
            {
                way.push_back(i);
                return true;
            }
        }
    }
    return false;
}

int main()
{
    fin.open("input.txt");

    long long N, M, s, f;
    fin >> N >> M;
    std::vector<std::pair<Crossroad, Crossroad>> roads;
    Crossroad empty_crossroad;
    roads.emplace_back(empty_crossroad, empty_crossroad);
    std::vector<Crossroad> crossroads(2 * M + 1);

    for (long long i = 0; i < M; i++)
    {
        long long x, y;
        fin >> x >> y;
        Point firstPoint(x, y);
        fin >> x >> y;
        Point secondPoint(x, y);
        fin >> x >> y;
        Crossroad firstCrossroad(firstPoint, x), secondCrossroad(secondPoint, y);
        roads.emplace_back(firstCrossroad, secondCrossroad);
        crossroads[firstCrossroad.getNumber()] = firstCrossroad;
        crossroads[secondCrossroad.getNumber()] = secondCrossroad;
    }
    fin >> s >> f;

    fin.close();
    fout.open("output.txt");

    std::vector<std::vector<bool>> adjacencyMatrix(N + 1, std::vector<bool>(N + 1, false));
    std::vector<std::vector<bool>> involvedEdges(N + 1, std::vector<bool>(N + 1, false));
    FillInAdjacencyMatrix(adjacencyMatrix, roads);

    Point beforeStartPoint(crossroads[s].getX(), crossroads[s].getY() - 1);
    Crossroad beforeStartCrossroad(beforeStartPoint, 0);
    crossroads[0] = beforeStartCrossroad;

    if (DFS(s, f, 0, adjacencyMatrix, involvedEdges, crossroads))
    {
        way.push_back(s);
        std::reverse(way.begin(), way.end());
        fout << "Yes\n";
        for (long long i : way)
        {
            fout << i << " ";
        }
    }
    else
    {
        fout << "No";
    }
    fout.close();
    return 0;
}