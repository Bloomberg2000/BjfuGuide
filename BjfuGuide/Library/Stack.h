//
// Created by 庞博 on 2018-12-13.
//
#pragma once
#ifndef STRUCTURE_STACK_V_H
#define STRUCTURE_STACK_V_H

#include "Vector.h" //以向量为基类，派生出栈模板类

namespace Structure {
/**
 * Stack template class
 * 顺序栈模板类
 * @tparam T 储存的数据类型
 */
    template<typename T>
    class Stack : public Vector<T> { //将向量的首/末端作为栈底/顶
    public:
        void push(T const &e);// 入栈
        T pop(); // 出栈
        T &top(); //取顶
    };

/**
 * 入栈：等效于将新元素作为向量的末元素插入
 * @param e 要插入的元素
 */
    template<typename T>
    void Stack<T>::push(const T &e) {
        this->insert(this->size(), e);
    }

/**
 * 出栈：等效于删除向量的末元素
 * @tparam T
 * @return
 */
    template<typename T>
    T Stack<T>::pop() {
        return this->remove(this->size() - 1);;
    }

/**
 * 取顶：直接返回向量的末元素
 * @tparam T
 * @return
 */
    template<typename T>
    T &Stack<T>::top() {
        return (*this)[this->size() - 1];;
    }
}

#endif //STRUCTURE_STACK_V_H
