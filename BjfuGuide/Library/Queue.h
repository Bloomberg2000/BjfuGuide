//
// Created by 庞博 on 2018-12-13.
//

#pragma once
#ifndef STRUCTURE_QUEUE_H
#define STRUCTURE_QUEUE_H

#include "List.h" //以List为基类

namespace Structure
{
/**
 * Queue template class
 * 链队列模板类
 * @tparam T 储存的数据类型
 */
template <typename T>
class Queue : public List<T>
{
  public:
    void enqueue(T const &e); // 入队
    T dequeue();              // 出队
    T &front();               // 队首
};

/**
 * 入队：尾部插入
 * @tparam T
 * @param e
 */
template <typename T>
void Queue<T>::enqueue(const T &e)
{
    insertAsLast(e);
}

/**
 * 出队：首部删除
 * @tparam T
 * @return
 */
template <typename T>
T Queue<T>::dequeue()
{
    return remove(this->first());
}

/**
 * 队首
 * @tparam T
 * @return
 */
template <typename T>
T &Queue<T>::front()
{
    return this->first()->data;
    ;
}
} // namespace Structure

#endif //STRUCTURE_QUEUE_H
