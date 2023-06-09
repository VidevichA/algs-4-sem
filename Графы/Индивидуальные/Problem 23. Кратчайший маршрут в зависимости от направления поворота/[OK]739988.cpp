#include <fstream>
#include <vector>

using namespace std;

class Vertex {
public:

    int ownDistance;
    int wholeDistance = INT32_MAX;
    int end;
    int start;
    bool processed = false;

    Vertex(int dist, int start, int end) {
        this->ownDistance = dist;
        this->end = end;
        this->start = start;
    }

    void setProcessed() {
        this->processed = true;
    }

    friend bool operator>(Vertex &first, Vertex &second) {
        return first.ownDistance > second.ownDistance;
    }
};

vector<vector<Vertex *>> list;
vector<pair<int, int>> crossroads;
short n, m, k, startNum, lastNum;

class Dijkstra {
public:
    static int isLeft(const Vertex &pair1, const Vertex &pair2) {
        if (pair1.end == pair2.start && pair1.start == pair2.end){
            return 1;
        }
        int x1, y1, x2, y2, x3, y3;
        if (pair1.start == -1) {
            x1 = crossroads[pair1.end].first, y1 = crossroads[pair1.end].second - 1;
        } else {
            x1 = crossroads[pair1.start].first, y1 = crossroads[pair1.start].second;
        }
        x2 = crossroads[pair1.end].first, y2 = crossroads[pair1.end].second,
        x3 = crossroads[pair2.end].first, y3 = crossroads[pair2.end].second;

        return (x1 * (y2 - y3) - y1 * (x2 - x3) + (x2 * y3 - x3 * y2)) > 0;
    }

    int result = INT32_MAX;
    Dijkstra() {
        auto *start = new Vertex(0, -1, startNum - 1);
        start->processed = true;
        for (const auto &item: list[start->end]) {
            if (item->wholeDistance > start->ownDistance + k * isLeft(*start, *item) * list[start->end].size()) {
                item->wholeDistance = start->ownDistance + k * isLeft(*start, *item) * list[start->end].size();
            }
        }
        while (true) {
            Vertex *current = nullptr;
            for (const auto &curVertexes: list) {
                for (const auto &vertex: curVertexes) {
                    if (!vertex->processed && vertex->wholeDistance != INT32_MAX) {
                        if (current == nullptr) {
                            current = vertex;
                        }
                        if (current->wholeDistance > vertex->wholeDistance) {
                            current = vertex;
                        }
                    }
                }
            }
            if (current == nullptr) break;
            current->processed = true;
            if (current->end == lastNum - 1 && result > current->ownDistance + current->wholeDistance){
                result = current->ownDistance + current->wholeDistance;
            }
            for (const auto &item: list[current->end]) {
                if (item->wholeDistance > current->wholeDistance + current->ownDistance +
                                          k * isLeft(*current, *item) * list[current->end].size()) {
                    item->wholeDistance = current->wholeDistance + current->ownDistance +
                                          k * isLeft(*current, *item) * list[current->end].size();
                }
            }
        }
    }
};

int main() {
    ifstream reader("input.txt");
    reader >> n >> m >> k;
    list = vector<vector<Vertex *>>(n);
    for (int i = 0; i < n; ++i) {
        int a, b;
        reader >> a >> b;
        crossroads.emplace_back(a, b);
    }

    for (int i = 0; i < m; ++i) {
        int a, b, value;
        reader >> a >> b >> value;
        list[a - 1].push_back(new Vertex(value, a - 1, b - 1));
        list[b - 1].push_back(new Vertex(value, b - 1, a - 1));
    }
    reader >> startNum >> lastNum;

    auto *dijkstra = new Dijkstra();

    ofstream writer("output.txt");
    if (dijkstra->result == INT32_MAX) {
        writer << "No";
    } else {
        writer << "Yes" << endl << dijkstra->result;
    }
    delete dijkstra;
    return 0;
}