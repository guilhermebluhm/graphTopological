#include <iostream>
#include <stack>
#include <vector>

struct node{

    int value;
    node *proximo;

};

class linkedList{

private:
    node *head;
public:

    linkedList(){
        head = nullptr;
    }

    void push(int v){

        node *newNode = new node;
        newNode->value = v;
        newNode->proximo = nullptr;

        if(head == nullptr){
            newNode->proximo = head;
            head = newNode;
        }
        else{

            newNode->proximo = head;
            head = newNode;

        }

    }

    void pop(){

        node *tmp = head;
        head = tmp->proximo;
        delete tmp;

    }

    int top(){

        node *tmp = head;
        return tmp->value;

    }

    bool empty(){

        if(head == nullptr)
            return true;
        return false;

    }


};

class topological{

private:

    /* tem o papel de definir o dado vertice ora nao visitado como visitado
     * então passando a verificar suas adjacencias como indicado na linha 125
     * e por sua vez chama recursivamente novamente para marcar suas adjacencias
     * e assim por diante, ao fim de cada iteração setando o elemento visitado na pilha
    */
    void dfs(int node, std::vector<int> *visited, linkedList &stck, std::vector<int> adj[]){

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

        //cria uma instancia de um ponteiro para um vetor de inteiros e inicializa
        std::vector<int> *visited = new std::vector<int>(vertex,0);
        //cria a lista ligada definida sua assinatura na linha 12
        linkedList fifo;

        //percorre cada vertice do grafo
        for(int i = 0 ; i < vertex ; i+=1) {

            //seguindo o modelo DFS verifica os vertices não visitados a chama sua ação recursiva
            if(!visited->at(i)) {
                dfs(i, visited, fifo, adjacency);
            }
        }

        //fila já montada apos as iterações do DFS recursivo
        std::vector<int> fifoReturn;
        //passara a remortar o pilha em forma inversa na forma de uma fila para chegar a ordenação topologica.
        while (!fifo.empty()){
            fifoReturn.push_back(fifo.top());
            fifo.pop();
        }

        return fifoReturn;
    }

};

int main() {

    //define a classe topological que tem sua assinatura definida na linha 67
    topological graph;
    //indica o numero de vertices do grafo de referencia utilizado para o exemplo
    int vertex = 6;
    /*
     * define o vector que representa a lista de adjacencias seguindo a seguinte padronizacao
     * |0| ->
     * |1| ->
     * |2| -> 3
     * (...)
     */
    std::vector<int> adj[6] = {{}, {}, {3}, {1}, {0, 1}, {0, 2}};
    //chama o metodo para realizar o comportamento da ordenação topologica
    std::vector<int> resp = graph.topologicalSort(vertex,adj);
    /* realiza o foreach para tornar possivel a impressao reversa pela ação de desempilhamento
     * do pilha introduzida via lista ligada (implementação customizada) para nao seguir o STL
    */
    for(auto it : resp){

        std::cout << "node: " << it << " " << "\n";

    }
    return 0;
}
