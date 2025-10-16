#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

// 三元组结构体
struct SanYuanZu {
    size_t hang;   // 行号（改为 size_t）
    size_t lie;    // 列号（改为 size_t）
    double zhi;    // 值
    
    SanYuanZu(size_t h, size_t l, double z) : hang(h), lie(l), zhi(z) {}
};

// 稀疏矩阵类
class XiShuJuZhen {
private:
    size_t hangShu;  // 矩阵行数（改为 size_t）
    size_t lieShu;   // 矩阵列数（改为 size_t）
    vector<SanYuanZu> shuJu; // 三元组存储
    
public:
    // 构造函数
    XiShuJuZhen(size_t h, size_t l) : hangShu(h), lieShu(l) {}
    
    // 添加元素
    void tianJiaYuanSu(size_t h, size_t l, double z) {
        if (h >= hangShu || l >= lieShu) {
            cerr << "位置无效: (" << h << ", " << l << ")" << endl;
            return;
        }
        if (z != 0) {
            shuJu.push_back(SanYuanZu(h, l, z));
        }
    }
    
    // 矩阵转置
    XiShuJuZhen zhuanZhi() const {
        XiShuJuZhen jieGuo(lieShu, hangShu);
        for (const auto& yuanSu : shuJu) {
            jieGuo.tianJiaYuanSu(yuanSu.lie, yuanSu.hang, yuanSu.zhi);
        }
        return jieGuo;
    }
    
    // 矩阵相加
    XiShuJuZhen operator+(const XiShuJuZhen& lingYiGe) const {
        if (hangShu != lingYiGe.hangShu || lieShu != lingYiGe.lieShu) {
            cerr << "矩阵维度不匹配，无法相加！" << endl;
            return *this;
        }
        
        XiShuJuZhen jieGuo(hangShu, lieShu);
        vector<SanYuanZu> linShi = shuJu;
        
        // 添加另一个矩阵的元素
        for (const auto& yuanSu : lingYiGe.shuJu) {
            linShi.push_back(yuanSu);
        }
        
        // 排序以便合并相同位置的元素
        sort(linShi.begin(), linShi.end(), [](const SanYuanZu& a, const SanYuanZu& b) {
            return (a.hang == b.hang) ? (a.lie < b.lie) : (a.hang < b.hang);
        });
        
        // 合并相同位置的元素
        for (size_t i = 0; i < linShi.size();) {
            size_t h = linShi[i].hang;
            size_t l = linShi[i].lie;
            double he = 0;
            
            // 合并相同位置的值
            while (i < linShi.size() && linShi[i].hang == h && linShi[i].lie == l) {
                he += linShi[i].zhi;
                i++;
            }
            
            if (he != 0) {
                jieGuo.tianJiaYuanSu(h, l, he);
            }
        }
        
        return jieGuo;
    }
    
    // 矩阵相减
    XiShuJuZhen operator-(const XiShuJuZhen& lingYiGe) const {
        if (hangShu != lingYiGe.hangShu || lieShu != lingYiGe.lieShu) {
            cerr << "矩阵维度不匹配，无法相减！" << endl;
            return *this;
        }
        
        XiShuJuZhen jieGuo(hangShu, lieShu);
        vector<SanYuanZu> linShi = shuJu;
        
        // 添加另一个矩阵的元素（取负值）
        for (const auto& yuanSu : lingYiGe.shuJu) {
            linShi.push_back(SanYuanZu(yuanSu.hang, yuanSu.lie, -yuanSu.zhi));
        }
        
        // 排序以便合并相同位置的元素
        sort(linShi.begin(), linShi.end(), [](const SanYuanZu& a, const SanYuanZu& b) {
            return (a.hang == b.hang) ? (a.lie < b.lie) : (a.hang < b.hang);
        });
        
        // 合并相同位置的元素
        for (size_t i = 0; i < linShi.size();) {
            size_t h = linShi[i].hang;
            size_t l = linShi[i].lie;
            double he = 0;
            
            // 合并相同位置的值
            while (i < linShi.size() && linShi[i].hang == h && linShi[i].lie == l) {
                he += linShi[i].zhi;
                i++;
            }
            
            if (he != 0) {
                jieGuo.tianJiaYuanSu(h, l, he);
            }
        }
        
        return jieGuo;
    }
    
    // 矩阵相乘
    XiShuJuZhen operator*(const XiShuJuZhen& lingYiGe) const {
        if (lieShu != lingYiGe.hangShu) {
            cerr << "矩阵维度不匹配，无法相乘！" << endl;
            return *this;
        }
        
        XiShuJuZhen jieGuo(hangShu, lingYiGe.lieShu);
        XiShuJuZhen lingYiGeZhuanZhi = lingYiGe.zhuanZhi();
        
        // 遍历当前矩阵的每个元素
        for (const auto& a : shuJu) {
            // 在转置后的矩阵中查找相同列号（即原矩阵的行号）的元素
            for (const auto& b : lingYiGeZhuanZhi.shuJu) {
                if (a.lie == b.lie) { // 相当于原矩阵的列匹配
                    jieGuo.tianJiaYuanSu(a.hang, b.hang, a.zhi * b.zhi);
                }
            }
        }
        
        // 合并结果矩阵中相同位置的元素
        jieGuo.heBingChongFuXiang();
        return jieGuo;
    }
    
    // 以阵列形式输出矩阵
    void shuChuJuZhen() const {
        // 创建二维数组表示矩阵
        vector<vector<double>> juZhen(hangShu, vector<double>(lieShu, 0.0));
        
        // 填充非零元素
        for (const auto& yuanSu : shuJu) {
            juZhen[yuanSu.hang][yuanSu.lie] = yuanSu.zhi;
        }
        
        // 输出矩阵
        for (size_t i = 0; i < hangShu; i++) {
            for (size_t j = 0; j < lieShu; j++) {
                cout << setw(8) << fixed << setprecision(2) << juZhen[i][j];
            }
            cout << endl;
        }
    }
    
    // 以三元组形式输出矩阵
    void shuChuSanYuanZu() const {
        cout << "行数: " << hangShu << ", 列数: " << lieShu << endl;
        cout << "三元组 (行, 列, 值):" << endl;
        for (const auto& yuanSu : shuJu) {
            cout << "(" << yuanSu.hang << ", " << yuanSu.lie << ", " << yuanSu.zhi << ")" << endl;
        }
    }
    
private:
    // 合并重复位置的三元组
    void heBingChongFuXiang() {
        if (shuJu.empty()) return;
        
        // 排序
        sort(shuJu.begin(), shuJu.end(), [](const SanYuanZu& a, const SanYuanZu& b) {
            return (a.hang == b.hang) ? (a.lie < b.lie) : (a.hang < b.hang);
        });
        
        vector<SanYuanZu> heBingHou;
        size_t i = 0;
        
        while (i < shuJu.size()) {
            size_t h = shuJu[i].hang;
            size_t l = shuJu[i].lie;
            double he = 0;
            
            // 合并相同位置的值
            while (i < shuJu.size() && shuJu[i].hang == h && shuJu[i].lie == l) {
                he += shuJu[i].zhi;
                i++;
            }
            
            if (he != 0) {
                heBingHou.push_back(SanYuanZu(h, l, he));
            }
        }
        
        shuJu = heBingHou;
    }
};

// 创建稀疏矩阵
XiShuJuZhen chuangJianXiShuJuZhen() {
    int hangShu, lieShu, feiLingShu;
    cout << "请输入矩阵行数: ";
    cin >> hangShu;
    cout << "请输入矩阵列数: ";
    cin >> lieShu;
    cout << "请输入非零元素个数: ";
    cin >> feiLingShu;
    
    if (hangShu <= 0 || lieShu <= 0) {
        cerr << "行数和列数必须为正整数！" << endl;
        exit(1);
    }
    
    XiShuJuZhen juZhen(static_cast<size_t>(hangShu), static_cast<size_t>(lieShu));
    
    for (int i = 0; i < feiLingShu; i++) {
        int h, l;
        double z;
        cout << "请输入第 " << i+1 << " 个元素 (行, 列, 值): ";
        cin >> h >> l >> z;
        
        if (h < 0 || l < 0) {
            cerr << "行号和列号不能为负数！" << endl;
            continue;
        }
        
        juZhen.tianJiaYuanSu(static_cast<size_t>(h), static_cast<size_t>(l), z);
    }
    
    return juZhen;
}

int main() {
    cout << "稀疏矩阵计算器" << endl;
    cout << "========================" << endl;
    
    cout << "创建第一个矩阵:" << endl;
    XiShuJuZhen A = chuangJianXiShuJuZhen();
    
    cout << "\n创建第二个矩阵:" << endl;
    XiShuJuZhen B = chuangJianXiShuJuZhen();
    
    cout << "\n矩阵 A:" << endl;
    A.shuChuJuZhen();
    
    cout << "\n矩阵 B:" << endl;
    B.shuChuJuZhen();
    
    cout << "\n矩阵加法 (A + B):" << endl;
    XiShuJuZhen C = A + B;
    C.shuChuJuZhen();
    
    cout << "\n矩阵减法 (A - B):" << endl;
    XiShuJuZhen D = A - B;
    D.shuChuJuZhen();
    
    cout << "\n矩阵乘法 (A * B):" << endl;
    XiShuJuZhen E = A * B;
    E.shuChuJuZhen();
    
    return 0;
}