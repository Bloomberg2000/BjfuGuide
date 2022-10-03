//
// Created by 庞博 on 2018-12-11.
//

#include "pch.h"
#include "Fib.h"

namespace Structure {
/**
 * Fibonacci数列类实现
 */
//初始化为不小于n的最小Fibonacci项
    Fib::Fib(int n) {
        f = 1;
        g = 0;
        while (g < n) {
            next();
        }
    }

//获取当前Fibonacci项，O(1)时间
    int Fib::get() {
        return g;
    }

//转至下一Fibonacci项，O(1)时间
    int Fib::next() {
        g += f;
        f = g - f;
        return g;
    }

//转至上一Fibonacci项，O(1)时间
    int Fib::prev() {
        f = g - f;
        g -= f;
        return g;
    }
}; // namespace Structure
