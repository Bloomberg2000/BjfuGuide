//
// Created by 庞博 on 2018-12-13.
//

#include "pch.h"
#include "String.h"
#include <iostream>
#include <cstring>
#include <string>

namespace Structure {
/**
 * 复制字符串区间str[lo, hi)
 * @param str 被复制的字符串
 * @param lo 区间上界
 * @param hi 区间下界
 */
    void String::copyFrom(const char *str, size_t lo, size_t hi) {
        _data = new char[hi - lo + 1];
        _length = 0;
        while (lo < hi) {                                 //str[lo, hi)内的元素逐一
            _data[_length++] = str[lo++]; //复制至data[0, hi - lo)
        }
        _data[lo] = '\0';
    }

/**
 * 默认构造函数
 * @param str
 */
    String::String(const char *str) {
        if (!str) {
            str = "\0";
        }
        copyFrom(str, 0, strlen(str));
    }

/**
 * 拷贝构造函数
 * @param str
 */
    String::String(const String &str) {
        copyFrom(str.c_str(), 0, str.length());
    }

    String::String(const std::string &str) {
        copyFrom(str.c_str(), 0, str.length());
    }

/**
 * 析构函数
 */
    String::~String() {
        delete[] _data;
        _length = 0;
    }

/**
 * 重载+运算符
 * @param str
 * @return
 */
    String String::operator+(const String &str) const {
        String newStr;
        newStr._length = _length + str.length();
        newStr._data = new char[newStr._length + 1];
        strcpy_s(newStr._data, newStr.length() + 1, _data);
        strcat_s(newStr._data, newStr.length() + str.length() + 1, str._data);
        return newStr;
    }

/**
 * 重载=运算符
 * @param str
 * @return
 */
    String &String::operator=(const String &str) {
        if (_data != nullptr) {
            delete[] _data;
        }
        copyFrom(str.c_str(), 0, str.length());
        return *this;
    }

/**
 * 重载+=运算符
 * @param str
 * @return
 */
    String &String::operator+=(const String &str) {
        *this = *this + str;
        return *this;
    }

/**
 * 重载==运算符
 * @param str
 * @return
 */
    bool String::operator==(const String &rhs) const {
        if (_length != rhs._length) {
            return false;
        }
        return strcmp(_data, rhs._data) == 0;
    }

/**
 * 重载!=运算符
 * @param str
 * @return
 */
    bool String::operator!=(const String &rhs) const {
        return !(rhs == *this);
    }

    bool String::operator<(const String &rhs) const {
        return strcmp(_data, rhs._data) < 0;
    }

    bool String::operator>(const String &rhs) const {
        return strcmp(_data, rhs._data) > 0;
    }

    bool String::operator<=(const String &rhs) const {
        return !(rhs < *this);
    }

    bool String::operator>=(const String &rhs) const {
        return !(*this < rhs);
    }

/**
 * 重载[]运算符
 * @param str
 * @return
 */
    char &String::operator[](int n) const {
        return _data[n];
    }

/**
 * 获取长度
 * @return
 */
    size_t String::length() const {
        return _length;
    }

/**
 * 返回C语言风格字符串
 * @return
 */
    const char *String::c_str() const {
        return _data;
    }

/**
 * 返回C++风格字符串
 * @return
 */
    std::string String::cpp_str() const {
        return {this->_data};
    }

/**
 * 重载输入运算符
 * @param is
 * @param str
 * @return
 */
    std::istream &operator>>(std::istream &is, String &str) {
        char temp[1000];
        is >> temp;
        str = temp;
        return is;
    }

/**
 * 重载输出运算符
 * @param os
 * @param str
 * @return
 */
    std::ostream &operator<<(std::ostream &os, const String &str) {
        os << str._data;
        return os;
    }

/**
 * 返回位置为pos的字符的引用
 * @param pos
 * @return
 */
    char &String::at(size_t pos) {
        return _data[pos];
    }

/**
 * 构建next数组
 * @param str 模式串
 * @return
 */
    int *String::buildNext(const char *str) {
        size_t m = strlen(str), j = 0; //“主”串指针
        int *N = new int[m];           //next表
        int t = N[0] = -1;             //模式串指针
		while (j < m - 1) {
			if (0 > t || str[j] == str[t]) { //匹配
				N[j] = (str[++j] != str[++t] ? t : N[t]);
			}
			else {
				//失配
				t = N[t];
			}
		}
        return N;
    }

/**
 * KMP算法模式匹配
 * @param str 模式串
 * @return 返回子串第一次出现的位置 如果未找到返回源字符串长度
 */
    int String::find(const char *str) const {
        int *next = buildNext(str);        //构造next表
        int n = (int) strlen(_data), i = 0; //文本串指针
        int m = (int) strlen(str), j = 0;   //模式串指针
        while (j < m && i < n) { //自左向右逐个比对字符
            //若匹配，或P已移出最左侧（两个判断的次序不可交换）
            if (0 > j || _data[i] == str[j]) {
                //则转到下一字符
                i++;
                j++;
            } else {                //否则
                j = next[j]; //模式串右移（注意：文本串不用回退）
            }
        }
        delete[] next; //释放next表
        return i - j;
    }

    int String::find(const String &str) const {
        return find(str.c_str());
    }

    int String::find(char ch) const {
        char str[] = {ch, '\0'};
        return find(str);
    }

    String &String::append(const String &str) {
        return *this += str;
    }

    String &String::append(const char *str) {
        String temp(str);
        return *this += temp;
    }
} // namespace Structure