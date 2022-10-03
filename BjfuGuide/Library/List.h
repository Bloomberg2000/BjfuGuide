//
// Created by 庞博 on 2018-12-13.
//

#pragma once
#ifndef STRUCTURE_LIST_H
#define STRUCTURE_LIST_H

#include "ListNode.h"

namespace Structure
{
/**
 * List template class
 * 列表模板类（以双向链表形式实现）
 * @tparam T 储存的数据类型
 */
template <typename T>
class List
{
  private:
    int _size;            // 规模
    ListNode<T> *header;  // 头哨兵
    ListNode<T> *trailer; //尾哨兵

  protected:
    void init();                            // 列表初始化
    int clear();                            // 清除所有节点
    void copyNodes(ListNode<T> *, int);     // 复制列表中自位置p起的n项
    void selectionSort(ListNode<T> *, int); // 对从p开始连续的n个节点选择排序
                                            //    void merge(ListNode<T>* &, int, List<T> &, ListNode<T>* , int); // 归并
                                            //    void mergeSort(ListNode<T>* &, int); // 对从p开始连续的n个节点归并排序
                                            //    void insertionSort(ListNode<T>* , int); // 对从p开始连续的n个节点插入排序

  public:
    // 构造函数
    List();                                                       //默认构造函数
    List(List<T> const &L);                                       //拷贝构造函数（整体拷贝）
    List(List<T> const &L, Rank r, int n);                        //拷贝构造函数（列表L中自第r项起的n项）
    List(ListNode<T> *p, int n);                                  //拷贝构造函数（复制列表中自p起的n项）
                                                                  // 析构函数
    ~List();                                                      //释放所有节点
                                                                  // 只读访问接口
    Rank size() const;                                            // 规模
    bool empty() const;                                           // 判空
    T &operator[](Rank r) const;                                  // 重载下表运算符（效率低）
    List<T> &operator=(List<T> const &L);                         // 重载赋值运算符
    ListNode<T> *first() const;                                   // 首节点指针
    ListNode<T> *last() const;                                    // 末节点指针
    bool valid(ListNode<T> *p);                                   // 判断位置p是否对外合法
    int disordered() const;                                       // 判断列表是否已排序
    ListNode<T> *find(T const &e) const;                          // 无序列表查找
    ListNode<T> *find(T const &e, int n, ListNode<T> *p) const;   // 无序区间查找
    ListNode<T> *search(T const &e) const;                        // 有序列表查找
    ListNode<T> *search(T const &e, int n, ListNode<T> *p) const; // 有序区间查找
    ListNode<T> *selectMax(ListNode<T> *p, int n);                // 在p及其n-1个后继中选出最大者
    ListNode<T> *selectMax();                                     // 选取最大者
                                                                  // 可写访问接口
    ListNode<T> *insertAsFirst(T const &e);                       // 将e当作首节点插入
    ListNode<T> *insertAsLast(T const &e);                        // 将e当作末节点插入
    ListNode<T> *insertAfter(ListNode<T> *p, T const &e);         // 将e当作p的后继插入
    ListNode<T> *insertBefore(ListNode<T> *p, T const &e);        // 将e当作p的前驱插入
    T remove(ListNode<T> *p);                                     // 删除合法位置p处的节点,返回被删除节点
                                                                  //    void merge(List<T> &L) { merge(first(), size, L, L.first(), L._size); } // 全列表归并
    void sort(ListNode<T> *p, int n);                             // 列表区间排序
    void sort();                                                  // 列表整体排序
    int deduplicate();                                            // 无序去重
    int uniquify();                                               // 有序去重
    void reverse();                                               // 前后倒置
                                                                  // 遍历
    void traverse(void (*)(T &));                                 // 遍历，依次实施visit操作（函数指针，只读或局部性修改）

    template <typename VST>
    void traverse(VST &); // 遍历，依次实施visit操作（函数对象，可全局性修改）
};                        //List

/**
 * 列表初始化，在创建列表对象时统一调用
 * @tparam T 
 */
template <typename T>
void List<T>::init()
{
    header = new ListNode<T>;
    trailer = new ListNode<T>;
    header->pos = trailer;
    header->pre = nullptr;
    trailer->pre = header;
    trailer->pos = nullptr;
    _size = 0; //记录规模
}

/**
 * 清空列表
 * @tparam T 
 * @return 
 */
template <typename T>
int List<T>::clear()
{
    int oldSize = _size;
    while (0 < _size)
    {
        remove(header->pos); //反复删除首节点，直至列表变空
    }
    return oldSize;
}

/**
 * 复制列表中自位置p起的n项
 * @tparam T 
 * @param p 起始节点
 * @param n 节点总数
 */
template <typename T>
void List<T>::copyNodes(ListNode<T> *p, int n)
{           // p合法，且至少有n-1个真后继节点
    init(); //创建头、尾哨兵节点并做初始化
    while (n--)
    {
        insertAsLast(p->data);
        p = p->pos;
    } //将起自p的n项依次作为末节点插入
}

/**
 * 选择排序算法：对起始于位置p的n个元素排序
 * @tparam T 
 * @param p 起始节点
 * @param n 节点总数
 */
template <typename T>
void List<T>::selectionSort(ListNode<T> *p, int n)
{ // valid(p) && rank(p) + vNum <= size
    ListNode<T> *head = p->pre;
    ListNode<T> *tail = p;
    for (int i = 0; i < n; i++)
    {
        tail = tail->pos; //待排序区间为(head, tail)
    }
    while (1 < n)
    {                                               //在至少还剩两个节点之前，在待排序区间内
        ListNode<T> *max = selectMax(head->pos, n); //找出最大者（歧义时后者优先）
        insertBefore(tail, remove(max));            //将其移至无序区间末尾（作为有序区间新的首元素）
        tail = tail->pre;
        n--;
    }
}

/**
 * 构造函数
 * @tparam T 
 */
template <typename T>
List<T>::List()
{
    init();
}

/**
 * 拷贝构造函数（复制列表中自位置p起的n项）
 * @tparam T 
 * @param p 起始节点
 * @param n 节点总数
 */
template <typename T>
List<T>::List(ListNode<T> *p, int n)
{
    copyNodes(p, n);
}

/**
 * 拷贝构造函数（整体复制）
 * @tparam T 
 * @param L 源列表
 */
template <typename T>
List<T>::List(List<T> const &L)
{
    copyNodes(L.first(), L._size);
}

/**
 * 拷贝构造函数（复制L中自第r项起的n项）
 * @tparam T 
 * @param L 
 * @param r 
 * @param n 
 */
template <typename T>
List<T>::List(List<T> const &L, int r, int n)
{
    copyNodes(L[r], n);
}

/**
 * 析构函数
 * @tparam T 
 */
template <typename T>
List<T>::~List()
{
    clear();
    delete header;
    delete trailer;
}

/**
 * 列表规模
 * @tparam T 
 * @return 列表大小
 */
template <typename T>
Rank List<T>::size() const
{
    return _size;
}

/**
 * 判空
 * @tparam T 
 * @return 列表是否为空
 */
template <typename T>
bool List<T>::empty() const
{
    return _size <= 0;
}

/**
 * 重载[]运算符
 * @tparam T 
 * @param r 
 * @return 
 */
template <typename T>
T &List<T>::operator[](Rank r) const
{
    ListNode<T> *p = first(); //从首节点出发
    while (0 < r--)
    {
        p = p->pos;
    }
    return p->data; //目标节点，返回其中所存元素
}

template <typename T>
List<T> &List<T>::operator=(const List<T> &L)
{
    copyNodes(L.first(), L._size);
    return *this;
}

/**
 * 首节点指针
 * @tparam T 
 * @return 
 */
template <typename T>
ListNode<T> *List<T>::first() const
{
    return header->pos;
}

/**
 * 末结点指针
 * @tparam T 
 * @return 
 */
template <typename T>
ListNode<T> *List<T>::last() const
{
    return trailer->pre;
}

/**
 * 判断位置是否有效
 * @tparam T 
 * @param p 
 * @return 
 */
template <typename T>
bool List<T>::valid(ListNode<T> *p)
{
    return p && (trailer != p) && (header != p); //将头、尾节点等同于NULL
}

/**
 * 判断列表是否已排序
 * @tparam T 
 * @return 逆序相邻元素对的总数
 */
template <typename T>
int List<T>::disordered() const
{
    int n = 0;
    ListNode<T> *p = first();
    for (int i = 0; i < _size - 1; p = p->pos, i++)
    {
        if (p->data > p->pos->data)
        {
            n++;
        }
    }
    return n;
}

/**
 * 无序列表查找
 * @tparam T 
 * @param e 被查找元素
 * @return 
 */
template <typename T>
ListNode<T> *List<T>::find(const T &e) const
{
    return find(e, _size, trailer);
}

/**
 * 在无序列表内节点p的n个前驱中，找到等于e的最后者
 * @tparam T 
 * @param e 被查找元素
 * @param n 查找范围
 * @param p 查找起始点
 * @return 返回所需节点的指针 不存在返回nullptr
 */
template <typename T>
ListNode<T> *List<T>::find(T const &e, int n, ListNode<T> *p) const
{
    while (0 < n--)
    { //对于p的最近的n个前驱，从右向左
        if (e == (p = p->pre)->data)
        {
            return p; //逐个比对，直至命中或范围越界
        }
    }
    return nullptr; //p越出左边界意味着区间内不含e，查找失败
}

/**
 * 有序列表查找
 * @tparam T 
 * @param e 被查找元素
 * @return 
 */
template <typename T>
ListNode<T> *List<T>::search(const T &e) const
{
    return search(e, _size, trailer);
}
//失败时，返回NULL

/**
 * 在有序列表内节点p的n个前驱中，找到不大于e的最后者
 * @tparam T 
 * @param e 被查找元素
 * @param n 查找范围
 * @param p 查找起始点
 * @return 返回所需节点的指针 
 *          失败时，返回区间左边界的前驱
 *          可通过valid()判断成功与否
 */
template <typename T>
//
ListNode<T> *List<T>::search(T const &e, int n, ListNode<T> *p) const
{
    while (0 <= n--)
    { //对于p的最近的n个前驱，从右向左逐个比较
        if (((p = p->pre)->data) <= e)
        {
            break; //直至命中、数值越界或范围越界
        }
    }
    return p; //返回查找终止的位置
}

/**
 * 从起始于位置p的n个元素中选出最大者
 * @tparam T 
 * @param p 起始位置
 * @param n 判断范围
 * @return 最大节点的指针
 */
template <typename T>
//
ListNode<T> *List<T>::selectMax(ListNode<T> *p, int n)
{
    ListNode<T> *max = p;                           //最大者暂定为首节点p
    for (ListNode<T> *cur = p; 1 < n; n--)          //从首节点p出发，将后续节点逐一与max比较
        if (!lt((cur = cur->pos)->data, max->data)) //若当前元素不小于max，则
            max = cur;                              //更新最大元素位置记录
    return max;                                     //返回最大节点位置
}

/**
 * 列表中的最大元素
 * @tparam T 
 * @return 
 */
template <typename T>
ListNode<T> *List<T>::selectMax()
{
    return selectMax(header->pos, _size);
}

/**
 * e作为首节点插入
 * @tparam T 
 * @param e 被插入元素
 * @return 
 */
template <typename T>
ListNode<T> *List<T>::insertAsFirst(T const &e)
{
    _size++;
    return header->insertAsPos(e);
}

/**
 * e作为末节点插入
 * @tparam T 
 * @param e 被插入元素
 * @return 
 */
template <typename T>
ListNode<T> *List<T>::insertAsLast(T const &e)
{
    _size++;
    return trailer->insertAsPre(e);
}

/**
 * e作为p的后继插入
 * @tparam T 
 * @param p 插入位置指针
 * @param e 要插入的元素
 * @return 
 */
template <typename T>
ListNode<T> *List<T>::insertAfter(ListNode<T> *p, T const &e)
{
    _size++;
    return p->insertAsPos(e);
}

/**
 * e作为p的前驱插入
 * @tparam T 
 * @param p 插入位置指针
 * @param e 要插入的元素
 * @return 
 */
template <typename T>
ListNode<T> *List<T>::insertBefore(ListNode<T> *p, T const &e)
{
    _size++;
    return p->insertAsPre(e);
}

/**
 * 删除节点p，返回其数值
 * @tparam T 
 * @param p 
 * @return 
 */
template <typename T>
T List<T>::remove(ListNode<T> *p)
{
    T e = p->data; //备份待删除节点的数值（假定T类型可直接赋值）
    p->pre->pos = p->pos;
    p->pos->pre = p->pre; //后继、前驱
    delete p;
    _size--;  //释放节点，更新规模
    return e; //返回备份的数值
}

/**
 * 列表区间排序
 * @tparam T 
 * @param p 起始节点
 * @param n 节点总数
 */
template <typename T>
void List<T>::sort(ListNode<T> *p, int n)
{
    //    insertionSort(p, vNum);
    selectionSort(p, n);
    //    mergeSort(p, vNum);
}

/**
 * 列表整体排序
 * @tparam T
 */
template <typename T>
void List<T>::sort()
{
    sort(first(), _size);
}

/**
 * 无序列表去重
 * @tparam T
 * @return
 */
template <typename T>
int List<T>::deduplicate()
{
    if (_size < 2)
    {
        return 0; //平凡列表无重复
    }
    int oldSize = _size; //记录原规模
    ListNode<T> *p = header;
    Rank r = 0; //p从首节点开始
    while (trailer != (p = p->pos))
    {                                         //依次直到末节点
        ListNode<T> *q = find(p->data, r, p); //在p的r个（真）前驱中查找雷同者
        q ? remove(q) : r++;                  //若的确存在，则删除之；否则秩加一
    }
    return oldSize - _size; //列表规模变化量，即被删除元素总数
}

/**
 * 有序列表去重
 * @tparam T
 * @return
 */
template <typename T>
int List<T>::uniquify()
{ //成批剔除重复元素，效率更高
    if (_size < 2)
    {
        return 0;
    }
    int oldSize = _size; //记录原规模
    ListNode<T> *p = first();
    ListNode<T> *q; //p为各区段起点，q为其后继
    while (trailer != (q = p->pos))
    { //反复考查紧邻的节点对(p, q)
        if (p->data != q->data)
        {
            p = q; //若互异，则转向下一区段
        }
        else
        {
            remove(q); //否则（雷同），删除后者
        }
    }
    return oldSize - _size; //列表规模变化量，即被删除元素总数
}

/**
 * 列表逆转
 * @tparam T
 */
template <typename T>
void List<T>::reverse()
{
    if (_size < 2)
    {
        return;
    }
    ListNode<T> *p;
    ListNode<T> *q;
    for (p = header, q = p->pos; p != trailer; p = q, q = p->pos)
    {
        p->pre = q; //自前向后，依次颠倒各节点的前驱指针
    }
    trailer->pre = nullptr; //单独设置尾节点的前驱指针
    for (p = header, q = p->pre; p != trailer; p = q, q = p->pre)
    {
        q->pos = p; //自前向后，依次颠倒各节点的后继指针
    }
    header->pos = nullptr; //单独设置头节点的后继指针
    swap(header, trailer); //头、尾节点互换
}

/**
 * 遍历（使用函数指针，只读或局部性修改）
 * @param visit 遍历操作函数
 */
template <typename T>
void List<T>::traverse(void (*visit)(T &))
{
    for (ListNode<T> *p = header->pos; p != trailer; p = p->pos)
    {
        visit(p->data);
    }
}

/**
 * 遍历（使用函数对象，可全局性修改）
 * @tparam VST 遍历函数对象 需重载()运算符
 */
template <typename T>
template <typename VST>
void List<T>::traverse(VST &visit)
{
    for (ListNode<T> *p = header->pos; p != trailer; p = p->pos)
    {
        visit(p->data);
    }
}
} // namespace Structure

#endif //STRUCTURE_LIST_H
