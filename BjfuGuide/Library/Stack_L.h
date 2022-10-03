//
// Created by 庞博 on 2018-12-13.
//

#pragma once
#ifndef STRUCTURE_STACK_L_H
#define STRUCTURE_STACK_L_H

#include "List.h" //以列表为基类，派生出栈模板类

namespace Structure {
/**
 * Stack template class
 * 链栈模板类
 * @tparam T 储存的数据类型
 */
    template<typename T>
    class Stack_L : public List<T> { //将列表的首/末端作为栈顶/底
    public:
        void push(T const &e);// 入栈
        T pop(); // 出栈
        T &top(); //取顶
    };

/**
 * 入栈：等效于将新元素作为列表的首元素插入
 * @tparam T
 * @param e
 */
    template<typename T>
    void Stack_L<T>::push(const T &e) {
        this->insertAsLast(e);
    }

/**
 * 出栈：等效于删除列表的首元素
 * @tparam T
 * @return
 */
    template<typename T>
    T Stack_L<T>::pop() {
        return this->remove(this->last());
    }

/**
 * 取顶：直接返回列表的首元素
 * @tparam T
 * @return
 */
    template<typename T>
    T &Stack_L<T>::top() {
        return this->last()->data;;
    }
}

#endif //STRUCTURE_STACK_L_H
