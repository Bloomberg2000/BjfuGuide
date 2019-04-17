//
// Created by 庞博 on 2018-12-11.
//

#pragma once
#ifndef STRUCTURE_FIB_H
#define STRUCTURE_FIB_H

namespace Structure {
/**
 * Fibonacci数列类
 */
    class Fib {
    private:
        int f, g; //f = fib(k - 1), g = fib(k)。均为int型，很快就会数值溢出
    public:
        //初始化为不小于n的最小Fibonacci项
        explicit Fib(int n);

        //获取当前Fibonacci项，O(1)时间
        int get();

        //转至下一Fibonacci项，O(1)时间
        int next();

        //转至上一Fibonacci项，O(1)时间
        int prev();
    };
} // namespace Structure

#endif //STRUCTURE_FIB_H
