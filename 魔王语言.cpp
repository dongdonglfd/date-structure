#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>
#include <cctype>

using namespace std;

// 替换规则
const string rule_A = "sae";
const string rule_B = "tAdA";

// 函数声明
string replace_letters(const string& s);
string expand_brackets(const string& s);

// 递归替换大写字母
string replace_letters(const string& s) {
    string result;
    for (char c : s) {
        if (c == 'A') {
            // 递归替换A
            result += replace_letters(rule_A);
        } else if (c == 'B') {
            // 递归替换B
            result += replace_letters(rule_B);
        } else {
            result += c;
        }
    }
    return result;
}

// 递归展开括号规则
string expand_brackets(const string& s) {
    string result;
    size_t i = 0;
    size_t n = s.length();
    
    while (i < n) {
        if (s[i] == '(') {
            // 找到匹配的右括号
            size_t start = i + 1;
            size_t end = start;
            int count = 1;
            
            while (end < n && count > 0) {
                if (s[end] == '(') count++;
                if (s[end] == ')') count--;
                if (count == 0) break;
                end++;
            }
            
            if (count == 0) {
                // 提取括号内容
                size_t len = end - start;
                string inner = s.substr(start, len);
                
                // 递归处理内层括号
                string expanded_inner = expand_brackets(inner);
                
                if (!expanded_inner.empty()) {
                    // 应用括号规则
                    char theta = expanded_inner[0];
                    string body = expanded_inner.substr(1);
                    
                    // 构建展开后的字符串
                    string temp;
                    temp += theta; // 添加θ
                    
                    // 使用反向迭代器逆序遍历body
                    for (auto it = body.rbegin(); it != body.rend(); ++it) {
                        temp += *it;
                        temp += theta;
                    }
                    
                    result += temp;
                }
                i = end + 1; // 移动到右括号之后
            } else {
                // 未匹配的括号，保留字符
                result += s[i];
                i++;
            }
        } else {
            // 普通字符直接添加
            result += s[i];
            i++;
        }
    }
    return result;
}

int main() {
    string input;
    getline(cin, input);
    
    // 去除输入中的空格
    input.erase(remove_if(input.begin(), input.end(), 
        [](unsigned char c) { return isspace(c); }), input.end());
    
    // 先应用括号规则
    string expanded = expand_brackets(input);
    
    // 再应用替换规则（递归替换）
    string replaced = replace_letters(expanded);
    
    cout << replaced << endl;
    
    return 0;
}