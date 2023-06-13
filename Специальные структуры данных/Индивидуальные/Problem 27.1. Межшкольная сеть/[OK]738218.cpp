#include <fstream>
#include <vector>
#include <algorithm>
#include <set>

struct Component{
    int leader;
    bool has_income;
    bool has_out_come;
};

// Алгоритм Касайро-Шарира для выделение сильносвязанных компонент

int n, no_in, no_out;
std::vector<std::vector<int>> matrix, matrixT;
std::vector<bool> visited;
std::vector<int> ordered, leaders;
std::vector<Component> components;
std::set<std::pair<int, int>> edges;

void dfs1(int start){
    visited[start] = true;
    for(int i = 1; i < n + 1; ++i){
        if(matrix[start][i] == 1 && !visited[i]){
            dfs1(i);
        }
    }
    ordered.push_back(start);
}

void dfs2(int start, Component &component){
    components[start] = component;
    visited[start] = true;
    for(int i = 1; i < n + 1; ++i){
        if(matrixT[start][i] == 1 && !visited[i])
            dfs2(i, component);
    }
}

void condensation(){
    for(int i = 1; i < n + 1; ++i){
        for(int j = 1; j < n + 1; ++j){
            if(matrix[i][j] == 1 && components[i].leader != components[j].leader){
                edges.insert(std::make_pair(components[i].leader, components[j].leader));
            }
        }
    }
}

void link_components(){
    condensation();
    for(const auto &item: edges){
        components[item.first].has_out_come = true;
        components[item.second].has_income = true;
    }
}

void count(){
    for (const auto &item : leaders){
        if(!components[item].has_out_come){
            ++no_out;
        }
        if(!components[item].has_income){
            ++no_in;
        }
    }
}

void strongly_connected_components(){
    for(int i = 1; i < n + 1; ++i){
        if(!visited[i]){
            dfs1(i);
        }
    }


    std::replace(visited.begin(), visited.end(),true,false);

    for(int i = ordered.size() - 1; i >= 0; --i){
        if(!visited[ordered[i]]){
            Component component = {ordered[i], false, false};
            leaders.push_back(ordered[i]);
            dfs2(ordered[i], component);
        }
    }

    link_components();
    count();
}

int main(){
    std::ifstream fin("input.txt");
    fin >> n;
    matrix.resize(n + 1, std::vector<int>(n + 1));
    matrixT.resize(n + 1, std::vector<int>(n + 1));
    components.resize(n + 1);
    visited.resize(n + 1, false);

    int x;
    for(int i = 1; i < n + 1; ++i){
        while(fin >> x){
            if(x == 0)
                break;
            matrix[i][x] = 1;
            matrixT[x][i] = 1;
        }
    }
    fin.close();

    strongly_connected_components();
    int second_answer;
    if(leaders.size() == 1 && leaders[0] == 1){
        second_answer = 0;
    }else{
        second_answer = std::max(no_in, no_out);
    }

    std::ofstream fout("output.txt");
    fout << no_in << "\n" << second_answer;
    fout.close();
    return 0;
}