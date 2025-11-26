#include <iostream>
#include <vector>
#include <list>
#include <stack>
using namespace std;

class Graph {
private:
    size_t vertexCount;          // 顶点数量
    vector<list<size_t>> adjList;  // 邻接表
    
public:
    // 构造函数，初始化图
    Graph(size_t n) : vertexCount(n), adjList(n) {}
    
    // 添加边
    void addEdge(size_t from, size_t to) {
        if (from < vertexCount && to < vertexCount) {
            adjList[from].push_back(to);
        } else {
            cerr << "错误: 顶点索引超出范围 (" << from << ", " << to << ")" << endl;
        }
    }
    
    // 深度优先遍历（递归实现）
    void DFS(size_t startVertex) {
        if (startVertex >= vertexCount) {
            cout << "起始顶点不存在！" << endl;
            return;
        }
        
        vector<bool> visited(vertexCount, false);
        cout << "从顶点 " << startVertex << " 开始的深度优先遍历（递归）: ";
        DFSRecursive(startVertex, visited);
        cout << endl;
    }
    
    // 深度优先遍历（迭代实现，使用栈）
    void DFSIterative(size_t startVertex) {
        if (startVertex >= vertexCount) {
            cout << "起始顶点不存在！" << endl;
            return;
        }
        
        vector<bool> visited(vertexCount, false);
        stack<size_t> s;
        
        cout << "从顶点 " << startVertex << " 开始的深度优先遍历（迭代）: ";
        
        s.push(startVertex);
        
        while (!s.empty()) {
            size_t currentVertex = s.top();
            s.pop();
            
            if (!visited[currentVertex]) {
                visited[currentVertex] = true;
                cout << currentVertex << " ";
                
                // 将邻接顶点按逆序压入栈，以保持与递归版本相同的顺序
                for (auto it = adjList[currentVertex].rbegin(); it != adjList[currentVertex].rend(); ++it) {
                    if (!visited[*it]) {
                        s.push(*it);
                    }
                }
            }
        }
        cout << endl;
    }
    
    // 打印邻接表
    void printAdjList() {
        cout << "邻接表：" << endl;
        for (size_t i = 0; i < vertexCount; i++) {
            cout << i << " -> ";
            for (size_t neighbor : adjList[i]) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }
    
private:
    // 深度优先遍历的递归辅助函数
    void DFSRecursive(size_t vertex, vector<bool>& visited) {
        visited[vertex] = true;
        cout << vertex << " ";
        
        for (size_t neighbor : adjList[vertex]) {
            if (!visited[neighbor]) {
                DFSRecursive(neighbor, visited);
            }
        }
    }
};

int main() {
    // 创建一个有6个顶点的图
    Graph graph(6);
    
    // 添加边
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 3);
    graph.addEdge(1, 4);
    graph.addEdge(2, 4);
    graph.addEdge(3, 5);
    graph.addEdge(4, 5);
    graph.addEdge(4, 3);
    
    // 打印邻接表
    graph.printAdjList();
    cout << endl;
    
    // 从顶点0开始进行深度优先遍历（递归）
    graph.DFS(0);
    
    // 从顶点0开始进行深度优先遍历（迭代）
    //graph.DFSIterative(0);
    
    cout << endl;
    
    // 从顶点3开始进行深度优先遍历（递归）
    graph.DFS(3);
    
    // 从顶点3开始进行深度优先遍历（迭代）
    graph.DFSIterative(3);
    
    return 0;
}