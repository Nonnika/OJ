// ...existing code...
#include <iostream>
#include <cstring>
#include <stdexcept>

using namespace std;

class String{
    private:
    char* str;
    int length;

    public:
    // 默认构造
    String() : str(new char[1]{'\0'}), length(0) {}

    // 从 C 字符串构造
    String(const char* s) {
        if (!s) { str = new char[1]{'\0'}; length = 0; }
        else {
            length = (int)std::strlen(s);
            str = new char[length + 1];
            std::memcpy(str, s, length + 1);
        }
    }

    // 拷贝构造（深拷贝）
    String(const String& other) : length(other.length) {
        str = new char[length + 1];
        std::memcpy(str, other.str, length + 1);
    }

    // 移动构造
    String(String&& other) noexcept : str(other.str), length(other.length) {
        other.str = new char[1]{'\0'};
        other.length = 0;
    }

    // 析构
    ~String() {
        delete[] str;
    }

    // 拷贝赋值
    String& operator=(const String& other) {
        if (this != &other) {
            char* tmp = new char[other.length + 1];
            std::memcpy(tmp, other.str, other.length + 1);
            delete[] str;
            str = tmp;
            length = other.length;
        }
        return *this;
    }

    // 移动赋值
    String& operator=(String&& other) noexcept {
        if (this != &other) {
            delete[] str;
            str = other.str;
            length = other.length;
            other.str = new char[1]{'\0'};
            other.length = 0;
        }
        return *this;
    }

    // 大小 & C-string
    int size() const { return length; }
    const char* c_str() const { return str; }

    // 下标访问（不做越界检查）和安全访问
    char& operator[](int i) { return str[i]; }
    const char& operator[](int i) const { return str[i]; }
    char& at(int i) {
        if (i < 0 || i >= length) throw out_of_range("String::at index out of range");
        return str[i];
    }

    // 清空
    void clear() {
        delete[] str;
        str = new char[1]{'\0'};
        length = 0;
    }

    // 拼接（+= 和 +）
    String& operator+=(const String& rhs) {
        int newlen = length + rhs.length;
        char* tmp = new char[newlen + 1];
        std::memcpy(tmp, str, length);
        std::memcpy(tmp + length, rhs.str, rhs.length + 1);
        delete[] str;
        str = tmp;
        length = newlen;
        return *this;
    }

    friend String operator+(const String& a, const String& b) {
        String res;
        delete[] res.str;
        res.length = a.length + b.length;
        res.str = new char[res.length + 1];
        std::memcpy(res.str, a.str, a.length);
        std::memcpy(res.str + a.length, b.str, b.length + 1);
        return res;
    }

    // 比较（类似 strcmp）
    int compare(const String& other) const {
        return std::strcmp(str, other.str);
    }

    // 查找子串，找不到返回 -1
    int find(const String& needle, int pos = 0) const {
        if (pos < 0) pos = 0;
        if (pos > length) return -1;
        const char* found = std::strstr(str + pos, needle.c_str());
        if (!found) return -1;
        return (int)(found - str);
    }

    // 子串 [pos, pos+len)
    String substr(int pos, int len = -1) const {
        if (pos < 0 || pos > length) throw out_of_range("String::substr pos out of range");
        if (len < 0 || pos + len > length) len = length - pos;
        char* buff = new char[len + 1];
        std::memcpy(buff, str + pos, len);
        buff[len] = '\0';
        String s(buff);
        delete[] buff;
        return s;
    }

    // 输入输出操作符
    friend ostream& operator<<(ostream& os, const String& s) {
        return os << s.c_str();
    }

    friend istream& operator>>(istream& is, String& s) {
        std::string tmp;
        if (!(is >> tmp)) return is;
        s = String(tmp.c_str());
        return is;
    }
};

// 简单示例 / 测试
int main() {
    String a("Hello");
    String b(" World");
    String c = a + b;
    cout << "c = " << c << " size = " << c.size() << "\n";

    c += String("!");
    cout << "after += : " << c << "\n";

    cout << "find 'World' at: " << c.find(String("World")) << "\n";
    cout << "substr(6,5): " << c.substr(6,5) << "\n";

    try {
        cout << "c[0] = " << c[0] << ", c.at(100) -> ";
        cout << c.at(100) << "\n";
    } catch (const exception& e) {
        cout << "caught: " << e.what() << "\n";
    }

    // 交互输入演示（可在终端测试）
    // cout << "输入一个单词: ";
    // String in;
    // cin >> in;
    // cout << "你输入: " << in << "\n";

    return 0;
}
// ...existing code...