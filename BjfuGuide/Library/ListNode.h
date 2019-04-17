//
// Created by 庞博 on 2018-12-13.
//

#pragma once
#ifndef STRUCTURE_LISTNODE_H
#define STRUCTURE_LISTNODE_H

typedef int Rank; //秩
namespace Structure {
/**
 * ListNode template class
 * 列表节点模板类（以双向链表形式实现）
 * @tparam T 储存的数据类型
 */
    template<typename T>
    struct ListNode {
// 成员
        T data; // 数据域
        ListNode<T> *pre; // 前驱
        ListNode<T> *pos; // 后继
// 构造函数
        ListNode() = default; //针对header和trailer的构造
        explicit ListNode(T e, ListNode<T> *p = nullptr, ListNode<T> *s = nullptr);//默认构造函数
// 操作接口
        ListNode<T> *insertAsPre(T const &e); //紧靠当前节点之前插入新节点
        ListNode<T> *insertAsPos(T const &e); //紧随当前节点之后插入新节点
    };

/**
 * 默认构造函数
 * @tparam T
 * @param e
 * @param p
 * @param s
 */
    template<typename T>
    ListNode<T>::ListNode(T e, ListNode<T> *p, ListNode<T> *s): data(e), pre(p), pos(s) {}

/**
 * 将e插入于当前节点之前
 * @tparam T
 * @param e
 * @return
 */
    template<typename T>
    ListNode<T> *ListNode<T>::insertAsPre(T const &e) {
        auto *x = new ListNode(e, pre, this); //创建新节点
        pre->pos = x;
        pre = x;
        return x; //返回新节点的位置
    }

/**
 * 将e插入于当前节点之后
 * @tparam T
 * @param e
 * @return
 */
    template<typename T>
    ListNode<T> *ListNode<T>::insertAsPos(T const &e) {
        auto *x = new ListNode(e, this, pos); //创建新节点
        pos->pre = x;
        pos = x;
        return x; //返回新节点的位置
    }
}

#endif //STRUCTURE_LISTNODE_H
