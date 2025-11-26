// #include <iostream>
// #include <vector>
// #include <queue>
// using namespace std;

// class Graph {
// private:
//     size_t vertexCount;          // 使用 size_t 代替 int
//     vector<vector<int>> adjMatrix;  // 邻接矩阵
    
// public:
//     // 构造函数，初始化图
//     Graph(size_t n) : vertexCount(n) {
//         adjMatrix.resize(n, vector<int>(n, 0));
//     }
    
//     // 添加边 - 使用 size_t 参数避免符号转换
//     void addEdge(size_t from, size_t to) {
//         if (from < vertexCount && to < vertexCount) {
//             adjMatrix[from][to] = 1;
//         } else {
//             cerr << "错误: 顶点索引超出范围 (" << from << ", " << to << ")" << endl;
//         }
//     }
    
//     // 计算并打印所有顶点的入度和出度
//     void calculateDegrees() {
//         cout << "顶点入度和出度统计：" << endl;
//         cout << "顶点\t入度\t出度" << endl;
        
//         for (size_t i = 0; i < vertexCount; i++) {
//             int outDegree = 0;  // 出度
//             int inDegree = 0;   // 入度
            
//             // 计算出度：统计第i行中1的个数
//             for (size_t j = 0; j < vertexCount; j++) {
//                 if (adjMatrix[i][j] == 1) {
//                     outDegree++;
//                 }
//             }
            
//             // 计算入度：统计第i列中1的个数
//             for (size_t j = 0; j < vertexCount; j++) {
//                 if (adjMatrix[j][i] == 1) {
//                     inDegree++;
//                 }
//             }
            
//             cout << i << "\t" << inDegree << "\t" << outDegree << endl;
//         }
//     }
    
//     // 广度优先遍历
//     void BFS(size_t startVertex) {
//         if (startVertex >= vertexCount) {
//             cout << "起始顶点不存在！" << endl;
//             return;
//         }
        
//         vector<bool> visited(vertexCount, false);  // 访问标记数组
//         queue<size_t> q;  // 队列用于BFS
        
//         cout << "从顶点 " << startVertex << " 开始的广度优先遍历: ";
        
//         // 从起始顶点开始
//         visited[startVertex] = true;
//         q.push(startVertex);
        
//         while (!q.empty()) {
//             size_t currentVertex = q.front();
//             q.pop();
//             cout << currentVertex << " ";
            
//             // 遍历当前顶点的所有邻接顶点
//             for (size_t i = 0; i < vertexCount; i++) {
//                 if (adjMatrix[currentVertex][i] == 1 && !visited[i]) {
//                     visited[i] = true;
//                     q.push(i);
//                 }
//             }
//         }
//         cout << endl;
//     }
    
//     // 打印邻接矩阵
//     void printAdjMatrix() {
//         cout << "邻接矩阵：" << endl;
//         cout << "  ";
//         for (size_t i = 0; i < vertexCount; i++) {
//             cout << i << " ";
//         }
//         cout << endl;
        
//         for (size_t i = 0; i < vertexCount; i++) {
//             cout << i << " ";
//             for (size_t j = 0; j < vertexCount; j++) {
//                 cout << adjMatrix[i][j] << " ";
//             }
//             cout << endl;
//         }
//     }
// };

// int main() {
//     // 创建一个有6个顶点的图
//     Graph graph(6);
    
//     // 添加边 - 使用 size_t 字面量
//     graph.addEdge(0, 1);
//     graph.addEdge(0, 2);
//     graph.addEdge(1, 3);
//     graph.addEdge(1, 4);
//     graph.addEdge(2, 4);
//     graph.addEdge(3, 5);
//     graph.addEdge(4, 5);
//     graph.addEdge(4, 3);
    
//     // 打印邻接矩阵
//     graph.printAdjMatrix();
//     cout << endl;
    
//     // 计算并打印入度和出度
//     graph.calculateDegrees();
//     cout << endl;
    
//     // 从顶点0开始进行广度优先遍历
//     graph.BFS(0);
    
//     // 从顶点3开始进行广度优先遍历
//     graph.BFS(3);
    
//     return 0;
// }
#include <iostream>
#include <vector>
#include <list>
#include <queue>
using namespace std;

class Graph {
private:
    size_t vertexCount;          // 顶点数量
    vector<list<size_t>> adjList;  // 邻接表
    vector<size_t> inDegree;     // 入度数组，改为 size_t 类型
    
public:
    // 构造函数，初始化图
    Graph(size_t n) : vertexCount(n), adjList(n), inDegree(n, 0) {}
    
    // 添加边
    void addEdge(size_t from, size_t to) {
        if (from < vertexCount && to < vertexCount) {
            adjList[from].push_back(to);
            inDegree[to]++;  // 更新入度
        } else {
            cerr << "错误: 顶点索引超出范围 (" << from << ", " << to << ")" << endl;
        }
    }
    
    // 计算并打印所有顶点的入度和出度
    void calculateDegrees() {
        cout << "顶点入度和出度统计：" << endl;
        cout << "顶点\t入度\t出度" << endl;
        
        for (size_t i = 0; i < vertexCount; i++) {
            size_t outDegree = adjList[i].size();  // 出度就是邻接表的大小，使用 size_t
            
            cout << i << "\t" << inDegree[i] << "\t" << outDegree << endl;
        }
    }
    
    // 广度优先遍历
    void BFS(size_t startVertex) {
        if (startVertex >= vertexCount) {
            cout << "起始顶点不存在！" << endl;
            return;
        }
        
        vector<bool> visited(vertexCount, false);  // 访问标记数组
        queue<size_t> q;  // 队列用于BFS
        
        cout << "从顶点 " << startVertex << " 开始的广度优先遍历: ";
        
        // 从起始顶点开始
        visited[startVertex] = true;
        q.push(startVertex);
        
        while (!q.empty()) {
            size_t currentVertex = q.front();
            q.pop();
            cout << currentVertex << " ";
            
            // 使用范围-based for 循环简化代码
            for (size_t neighbor : adjList[currentVertex]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
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
};

int main() {
    // 创建一个有6个顶点的图
    Graph graph(6);
    
    // 添加边（与之前相同的图结构）
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
    
    // 计算并打印入度和出度
    graph.calculateDegrees();
    cout << endl;
    
    // 从顶点0开始进行广度优先遍历
    graph.BFS(0);
    
    // 从顶点3开始进行广度优先遍历
    graph.BFS(3);
    
    return 0;
}
