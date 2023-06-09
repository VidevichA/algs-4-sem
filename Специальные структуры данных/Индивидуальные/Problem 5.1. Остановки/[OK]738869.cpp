#include <fstream>
#include <vector>
#include <queue>
#include <stack>
#include <sstream>
#include <iostream>

short stations, buses, start, last;

using namespace std;

class Pair {
private:
    Pair() = default;
public:

    short dist;
    short value;
    short busNum;
    Pair *prev;
    short num;

    Pair(short dist, short value, short busNum, short num, Pair *prev = nullptr) {
        this->dist = dist;
        this->value = value;
        this->busNum = busNum;
        this->prev = prev;
        this->num = num;
    }

    friend bool operator>(Pair &first, Pair &second) {
        return first.dist > second.dist;
    }
};

vector<vector<vector<Pair>>> dists;

class greater_pair{
public:
    bool operator()(Pair *& a, Pair*& b){
        return *a > *b;
    }
};

class Dijkstra {

public:
    vector<vector<short>> dist;
    Pair *lastPair = nullptr;

    explicit Dijkstra(int n) {
        priority_queue<Pair *, vector<Pair *>, greater_pair> pq;
        vector<vector<bool>> processed = vector<vector<bool>>(n, vector<bool>(10, false));
        dist = vector<vector<short>>(n, vector<short>(10, INT16_MAX));
        for (short i = 0; i < dists[start - 1].size(); ++i) {
            if (!dists[start - 1][i].empty()) {
                pq.push(new Pair(0, (short) (start - 1), -1, i));
            }
        }

        while (!pq.empty()) {
            Pair *current = pq.top();
            pq.pop();

//            if (processed[current->value][current->num]) {
//                delete current;
//                continue;
//            }
            if (current->value == last - 1) {
                if (lastPair != nullptr){
                    if (lastPair->dist < current->dist){
                        continue;
                    } else{
                        lastPair = current;
                    }
                }
                else {
                    lastPair = current;
                }
            }

            processed[current->value][current->num] = true;
            if (current->dist < dist[current->value][current->num]) {
                dist[current->value][current->num] = current->dist;
            }
            for (const auto &item: dists[current->value][current->num]) {
                if (/*!processed[item.value][item.num] &&*/
                    current->dist + item.dist + 3 * (item.busNum != current->busNum) < dist[item.value][item.num]) {
                        pq.push(new Pair(current->dist + item.dist +
                                         3 * (item.busNum != current->busNum && current->busNum != -1), item.value,
                                         item.busNum, item.num, current));
                }
            }
        }
    }
};

int main() {
    ifstream reader("in.txt");
    reader >> stations >> buses >> last >> start;

    if (last == start) {
        ofstream writer("out.txt");
        writer << 0;
        return 0;
    }

    if (buses == 0){
        ofstream writer("out.txt");
        writer << "NoWay";
        return 0;
    }

    dists = vector<vector<vector<Pair>>>(stations, vector<vector<Pair>>(10));
    for (int i = 0; i < buses; i++) {
        int amount, current;
        reader >> amount >> current;
        vector<short> mas = vector<short>(stations, 0);
        for (int j = 0; j < amount - 1; j++) {
            int next;
            reader >> next;
            if (mas[current - 1] != 0){
                for (int k = 0; k < mas[current - 1]; ++k) {
                    dists[current - 1][k].emplace_back(0, current - 1, -1, mas[current - 1]);
                    dists[current - 1][mas[current - 1]].emplace_back(0, current - 1, -1, k);
                }
            }
            dists[current - 1][mas[current - 1]++].emplace_back(1, next - 1, i, mas[next - 1]);
            dists[next - 1][mas[next - 1]].emplace_back(1, current - 1, i, mas[current - 1] - 1);
            current = next;
        }
    }


    if (dists[start - 1].empty() || dists[last - 1].empty()) {
        ofstream writer("out.txt");
        writer << "NoWay";
        return 0;
    }
    auto dijkstra = new Dijkstra(stations);




    ofstream writer("out.txt");
    if (dijkstra->lastPair == nullptr){
        writer << "NoWay";
        return 0;
    }
    short dist = dijkstra->lastPair->dist;
    if (dist == INT16_MAX) {
        writer << "NoWay";
        return 0;
    }
    writer << dijkstra->lastPair->dist << endl;
    stack<string> output;
    auto current = dijkstra->lastPair;
    short lastBus = current->busNum;
    while (current != nullptr) {
        stringstream ss;
        if (current->busNum == -1 && current->prev != nullptr){
            current = current->prev;
            continue;
        }
        if (lastBus != current->busNum) {
            ss << "StopNo " << current->value + 1 << " BusNo " << lastBus + 1 << endl;
        } else {
            ss << "StopNo " << current->value + 1 << " BusNo " << current->busNum + 1 << endl;
        }
        output.push(ss.str());
        auto temp = current;
        current = current->prev;
        lastBus = temp->busNum;
        delete temp;
    }

    while (!output.empty()) {
        writer << output.top();
        output.pop();
    }
    delete dijkstra;
    return 0;
}