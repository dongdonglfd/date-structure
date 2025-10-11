#include <iostream>
#include <iomanip>
#include <stack>
#include <vector>
#include <algorithm>
using namespace std;

// 使用 size_t 定义棋盘大小
const size_t BOARD_SIZE = 8;
const int HTry1[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
const int HTry2[8] = {1, 2, 2, 1, -1, -2, -2, -1};

// 定义棋盘
vector<vector<int>> board(BOARD_SIZE, vector<int>(BOARD_SIZE, 0));

// 定义状态结构体
struct State {
    size_t posX, posY; 
    int step;
    size_t nextTry;
    
    State(size_t x, size_t y, int s, size_t n) 
        : posX(x), posY(y), step(s), nextTry(n) {}
};

// 检查位置是否有效且未被访问
bool isValid(int x, int y) {
    return (x >= 0 && y >= 0 && 
            static_cast<size_t>(x) < BOARD_SIZE && 
            static_cast<size_t>(y) < BOARD_SIZE && 
            board[static_cast<size_t>(x)][static_cast<size_t>(y)] == 0);
}

// 打印棋盘
void printBoard() {
    cout << "马踏棋盘解决方案：" << endl;
    for (size_t i = 0; i < BOARD_SIZE; i++) {
        for (size_t j = 0; j < BOARD_SIZE; j++) {
            cout << setw(3) << board[i][j];
        }
        cout << endl;
    }
}

// 计算当前位置的出口数
int calculateExits(int x, int y) {
    int count = 0;
    for (size_t i = 0; i < 8; i++) {
        int nextX = x + HTry1[i];
        int nextY = y + HTry2[i];
        
        if (isValid(nextX, nextY)) {
            count++;
        }
    }
    return count;
}

// 非递归解决马踏棋盘问题
bool solveKnightTour(int startX, int startY) {
    stack<State> stateStack;
    
    // 初始化起始状态
    board[static_cast<size_t>(startX)][static_cast<size_t>(startY)] = 1;
    stateStack.push(State(static_cast<size_t>(startX), static_cast<size_t>(startY), 1, 0));
    
    while (!stateStack.empty()) {
        State current = stateStack.top();
        stateStack.pop();
        
        int currentX = static_cast<int>(current.posX);
        int currentY = static_cast<int>(current.posY);
        int currentStep = current.step;
        size_t currentNextTry = current.nextTry;
        
        // 如果已经走完所有格子，返回成功
        if (currentStep == static_cast<int>(BOARD_SIZE * BOARD_SIZE)) {
            return true;
        }
        
        // 使用Warnsdorff规则：优先选择出口数少的方向
        vector<pair<int, size_t>> possibleMoves; // <出口数, 方向索引>
        
        // 收集所有可能的移动方向
        for (size_t i = 0; i < 8; i++) {
            int nextX = currentX + HTry1[i];
            int nextY = currentY + HTry2[i];
            
            if (isValid(nextX, nextY)) {
                int exits = calculateExits(nextX, nextY);
                possibleMoves.push_back(make_pair(exits, i));
            }
        }
        
        // 按出口数排序（从小到大）
        sort(possibleMoves.begin(), possibleMoves.end());
        
        bool found = false;
        // 尝试所有可能的方向（从currentNextTry开始）
        for (size_t i = currentNextTry; i < possibleMoves.size(); i++) {
            size_t directionIndex = possibleMoves[i].second;
            int nextX = currentX + HTry1[directionIndex];
            int nextY = currentY + HTry2[directionIndex];
            
            if (isValid(nextX, nextY)) {
                // 标记新位置 - 使用显式转换
                board[static_cast<size_t>(nextX)][static_cast<size_t>(nextY)] = currentStep + 1;
                
                // 保存当前状态（已尝试到第i+1个方向）
                if (i < possibleMoves.size() - 1) {
                    stateStack.push(State(static_cast<size_t>(currentX), static_cast<size_t>(currentY), currentStep, i + 1));
                }
                
                // 压入新状态
                stateStack.push(State(static_cast<size_t>(nextX), static_cast<size_t>(nextY), currentStep + 1, 0));
                found = true;
                break;
            }
        }
        
        // 如果没有找到可行的移动，需要回溯
        if (!found) {
            board[static_cast<size_t>(currentX)][static_cast<size_t>(currentY)] = 0;
        }
    }
    
    return false;
}

int main() {
    int inputX, inputY;
    
    // 输入起始位置
    cout << "请输入马的起始位置 (0-" << BOARD_SIZE - 1 << ", 0-" << BOARD_SIZE - 1 << "): ";
    cin >> inputX >> inputY;
    
    // 验证输入有效性
    if (inputX < 0 || inputY < 0 || 
        static_cast<size_t>(inputX) >= BOARD_SIZE || 
        static_cast<size_t>(inputY) >= BOARD_SIZE) {
        cout << "起始位置无效！" << endl;
        return 1;
    }
    
    // 尝试解决马踏棋盘问题
    if (solveKnightTour(inputX, inputY)) {
        printBoard();
    } else {
        cout << "未找到解决方案" << endl;
    }
    
    return 0;
}