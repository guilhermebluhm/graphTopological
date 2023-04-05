#include <iostream>
#include <stack>
#include <vector>

class topological{

private:

    void dfs(int node, std::vector<int> *visited, std::stack<int> &stck, std::vector<int> adj[]){

        visited->at(node) = 1;
        for(auto it : adj[node]){

            if(!visited->at(it)){

                dfs(it, visited, stck, adj);

            }
        }
        stck.push(node);
    }


public:

    std::vector<int> topologicalSort(int vertex, std::vector<int> adjacency[]) {

        std::vector<int> *visited = new std::vector<int>(vertex,0);
        std::stack<int> fifo;
        for(int i = 0 ; i < vertex ; i+=1) {

            if(!visited->at(i)) {
                dfs(i, visited, fifo, adjacency);
            }
        }

        std::vector<int> fifoReturn;
        while (!fifo.empty()){
            fifoReturn.push_back(fifo.top());
            fifo.pop();
        }

        return fifoReturn;
    }

};

int main() {
    topological graph;
    int vertex = 6;
    std::vector<int> adj[6] = {{}, {}, {3}, {1}, {0, 1}, {0, 2}};
    std::vector<int> resp = graph.topologicalSort(vertex,adj);
    for(auto it : resp){

        std::cout << "node: " << it << " " << "\n";

    }
    return 0;
}
