//
// Created by 庞博 on 2018-12-13.
//

#pragma once
#ifndef STRUCTURE_STRING_H
#define STRUCTURE_STRING_H

namespace Structure {
    class String {
    protected:
        char *_data;    // 字符串内容
        size_t _length; // 字符串长度

        void copyFrom(const char *str, size_t lo, size_t hi); // 复制字符串区间
        static int *buildNext(const char *str);               // 构造next数组

    public:
        // 构造函数
        String(const char *str = "\0"); // 默认构造函数
        String(const std::string &str); // 拷贝构造函数
        String(const String &str);      // 拷贝构造函数
        // 析构函数
        ~String();                      //析构函数

        String operator+(const String &str) const; // 重载+
        String &operator=(const String &str);      // 重载=
        String &operator+=(const String &str);     // 重载+=
        bool operator==(const String &rhs) const;  // 重载==
        bool operator!=(const String &rhs) const;  // 重载!=

        bool operator<(const String &rhs) const;

        bool operator>(const String &rhs) const;

        bool operator<=(const String &rhs) const;

        bool operator>=(const String &rhs) const;

        char &operator[](int n) const; //重载[]

        size_t length() const;       //获取长度
        const char *c_str() const;   //获取C字符串
        std::string cpp_str() const; //转C++字符串

        friend std::istream &operator>>(std::istream &is, String &str);       // 输入
        friend std::ostream &operator<<(std::ostream &os, const String &str); // 输出

        char &at(size_t pos);

        String &append(const String &str); // 后端插入

        String &append(const char *str); // 后端插入

        int find(const char *str) const; // 字符匹配

        int find(const String &str) const; // 字符匹配

        int find(char ch) const; // 字符匹配
    };
} // namespace Structure
#endif //STRUCTURE_STRING_H
