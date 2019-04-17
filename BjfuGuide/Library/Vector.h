//
// Created by 庞博 on 2018-12-11.
//

#pragma once
#ifndef STRUCTURE_VECTOR_H
#define STRUCTURE_VECTOR_H

#include "Fib.h"

typedef int Rank;          //秩
#define DEFAULT_CAPACITY 3 //默认的初始容量
namespace Structure
{
/**
 * Vector template class
 * 向量模板类
 * @tparam T 向量储存的数据类型
 */
template <typename T>
class Vector
{
  protected:
    Rank _size;    // 向量规模
    int _capacity; // 向量容量
    T *_elem;      // 数据区

    void copyFrom(T const *A, Rank lo, Rank hi);        // 复制数组区间A[lo, hi)
    void expand();                                      // 向量空间不足时扩容
    void shrink();                                      //向量空间过大时压缩
    Rank binSearch(T *A, T const &e, Rank lo, Rank hi); // 二分查找
    Rank fibSearch(T *A, T const &e, Rank lo, Rank hi); // 斐波那契查找
    Rank partition(Rank lo, Rank hi);                   // 构造轴点
    void quickSort(Rank lo, Rank hi);                   // 快速排序
                                                        //    bool bubble(Rank lo, Rank hi); //扫描交换
                                                        //    void bubbleSort(Rank lo, Rank hi); //起泡排序算法
                                                        //    Rank max(Rank lo, Rank hi); //选取最大元素
                                                        //    void selectionSort(Rank lo, Rank hi); //选择排序算法
                                                        //    void merge(Rank lo, Rank mi, Rank hi); //归并算法
                                                        //    void mergeSort(Rank lo, Rank hi); //归并排序算法
                                                        //    void heapSort(Rank lo, Rank hi); //堆排序（稍后结合完全堆讲解）

  public:
    //构造函数
    explicit Vector(int c = DEFAULT_CAPACITY);

    explicit Vector(int c, int s, T v); // 构造函数）

    explicit Vector(T const *A, Rank n); // 构造函数（拷贝数组整体）

    explicit Vector(T const *A, Rank lo, Rank hi); // 构造函数（拷贝数组指定区间）

    Vector(Vector<T> const &V); // 构造函数（拷贝向量整体）

    explicit Vector(Vector<T> const &V, Rank lo, Rank hi); // 构造函数（拷贝向量指定区间）

    // 析构函数
    ~Vector(); // 析构函数

    Rank size() const;                               // 向量规模
    bool empty() const;                              // 判断是否为空
    int disordered() const;                          // 有序性判别
    Rank find(T const &e) const;                     // 无序向量的查找
    Rank find(T const &e, Rank lo, Rank hi) const;   // 无序向量指定区间的查找
    Rank search(T const &e) const;                   // 有序向量的查找
    Rank search(T const &e, Rank lo, Rank hi) const; // 有序向量指定区间的查找

    T &operator[](Rank r) const;              // 重载下标运算符
    Vector<T> &operator=(Vector<T> const &V); // 重载赋值运算符
    bool operator==(const Vector &rhs) const; // 重载比较运算符
    bool operator!=(const Vector &rhs) const; // 重载比较运算符
    T remove(Rank r);                         // 删除秩为r的元素
    int remove(Rank lo, Rank hi);             // 删除秩在指定区间的元素
    Rank insert(Rank r, T const &e);          // 在指定位置插入元素
    Rank insert(T const &e);                  // 在向量最后插入元素插入元素
    void sort(Rank lo, Rank hi);              // 指定区间排序
    void sort();                              // 整体排序
    int deduplicate();                        // 无序向量的去重
    int uniquify();                           // 有序向量的去重

    // 遍历
    void traverse(void (*visit)(T &m)); // 使用函数指针遍历
    template <typename VST>
    void traverse(VST &visit); // 使用函数对象遍历
};

/**
 * 复制数组区间A[lo, hi)
 * @param A 被复制的数组
 * @param lo 区间上界
 * @param hi 区间下界
 */
template <typename T>
void Vector<T>::copyFrom(T const *A, Rank lo, Rank hi)
{
    _elem = new T[_capacity = 2 * (hi - lo)];
    _size = 0; //分配空间，规模清零
    while (lo < hi)
    {                             //A[lo, hi)内的元素逐一
        _elem[_size++] = A[lo++]; //复制至_elem[0, hi - lo)
    }
}

/**
 * 向量空间不足时扩容
 */
template <typename T>
void Vector<T>::expand()
{
    if (_size < _capacity)
    {
        //尚未满员时，不必扩容
        return;
    }
    if (_capacity < DEFAULT_CAPACITY)
    {
        //不低于最小容量
        _capacity = DEFAULT_CAPACITY;
    }
    T *oldElem = _elem;
    _elem = new T[_capacity <<= 1]; //容量加倍
    for (int i = 0; i < _size; i++)
    {
        _elem[i] = oldElem[i];
    }
    delete[] oldElem; //释放原空间
}

/**
 * 向量空间过大时压缩
 */
template <typename T>
void Vector<T>::shrink()
{ //装填因子过小时压缩向量所占空间
    if (_capacity < DEFAULT_CAPACITY << 1)
    {
        //不致收缩到DEFAULT_CAPACITY以下
        return;
    }
    if (_size << 2 > _capacity)
    {
        //以25%为界
        return;
    }
    T *oldElem = _elem;
    _elem = new T[_capacity >>= 1]; //容量减半
    for (int i = 0; i < _size; i++)
    {
        _elem[i] = oldElem[i]; //复制原向量内容
    }
    delete[] oldElem; //释放原空间
}

/**
 * 二分查找
 * @param A 查找的数组对象
 * @param e 要查找的元素
 * @param lo 区间上界
 * @param hi 区间下界
 * @return有多个命中元素时，总能保证返回秩最大者；查找失败时，能够返回失败的位置
 */
template <typename T>
Rank Vector<T>::binSearch(T *A, const T &e, Rank lo, Rank hi)
{
    while (lo < hi)
    {                                        //每步迭代仅需做一次比较判断，有两个分支
        Rank mi = (lo + hi) >> 1;            //以中点为轴点
        (e < A[mi]) ? hi = mi : lo = mi + 1; //经比较后确定深入[lo, mi)或(mi, hi)
    }                                        //成功查找不能提前终止
    return --lo;                             //循环结束时，lo为大于e的元素的最小秩，故lo - 1即不大于e的元素的最大秩
}

/**
 * 斐波那契查找
 * @param A 查找的数组对象
 * @param e 要查找的元素
 * @param lo 区间上界
 * @param hi 区间下界
 * @return有多个命中元素时，总能保证返回秩最大者；查找失败时，能够返回失败的位置
 */
template <typename T>
Rank Vector<T>::fibSearch(T *A, T const &e, Rank lo, Rank hi)
{
    Fib fib(hi - lo); //创建Fib数列
    while (lo < hi)
    { //每步迭代仅仅做一次比较判断，有两个分支
        while (hi - lo < fib.get())
        {
            fib.prev(); //通过向前顺序查找（分摊O(1)）——至多迭代几次？
        }
        Rank mi = lo + fib.get() - 1;        //确定形如Fib(k) - 1的轴点
        (e < A[mi]) ? hi = mi : lo = mi + 1; //比较后确定深入前半段[lo, mi)或后半段(mi, hi)
    }                                        //成功查找不能提前终止
    return --lo;                             //循环结束时，lo为大于e的元素的最小秩，故lo - 1即不大于e的元素的最大秩
} //有多个命中元素时，总能保证返回最秩最大者；查找失败时，能够返回失败的位置

/**
 * 构造轴点
 * @param lo 区间下界
 * @param hi 区间上界
 * @return
 */
template <typename T>
Rank Vector<T>::partition(Rank lo, Rank hi)
{                                                        //可优化处理多个关键码雷同的退化情况
    swap(_elem[lo], _elem[lo + rand() % (hi - lo + 1)]); //任选一个元素与首元素交换
    T pivot = _elem[lo];                                 //以首元素为候选轴点——经以上交换，等效于随机选取
    while (lo < hi)
    { //从向量的两端交替地向中间扫描
        while (lo < hi)
        {
            //在大于pivot的前提下
            if (pivot < _elem[hi])
            {
                //向左拓展右端子向量
                hi--;
            }
            else
            {
                //直至遇到不大于pivot者
                //将其归入左端子向量
                _elem[lo++] = _elem[hi];
                break;
            }
        }
        while (lo < hi)
        {
            //在小于pivot的前提下
            if (_elem[lo] < pivot)
            {
                lo++; //向右拓展左端子向量
            }
            else
            {
                //直至遇到不小于pivot者
                //将其归入右端子向量
                _elem[hi--] = _elem[lo];
                break;
            }
        }
    }                  //assert: lo == hi
    _elem[lo] = pivot; //将备份的轴点记录置于前、后子向量之间
    return lo;         //返回轴点的秩
}

/**
 * 快速排序
 * @param lo 区间上界
 * @param hi 区间下界
 */
template <typename T>
void Vector<T>::quickSort(Rank lo, Rank hi)
{ //0 <= lo < hi <= length
    if (hi - lo < 2)
    {
        return; //单元素区间自然有序，否则...
    }
    Rank mi = partition(lo, hi - 1); //在[lo, hi - 1]内构造轴点
    quickSort(lo, mi);               //对前缀递归排序
    quickSort(mi + 1, hi);           //对后缀递归排序
}

/**
 * 构造函数（创建默认向量）
 * @param c 容量 default : DEFAULT_CAPACITY;
 * @param s 规模 default : 0 s < c
 */
template <typename T>
Vector<T>::Vector(int c)
{
    _elem = new T[_capacity = c];
    _size = 0;
}

/**
 * 构造函数
 * @param c 容量 default : DEFAULT_CAPACITY;
 * @param s 规模 default : 0 s < c
 * @param v 元素初值 default : 0
 */
template <typename T>
Vector<T>::Vector(int c, int s, T v)
{
    _elem = new T[_capacity = c];
    for (_size = 0; _size < s; _elem[_size++] = v)
        ;
}

/**
 * 构造函数（拷贝数组整体）
 * @param A 被操作数组
 * @param n 数组长度
 */
template <typename T>
Vector<T>::Vector(T const *A, Rank n)
{
    copyFrom(A, 0, n);
}

/**
 * 构造函数（拷贝数组指定区间）
 * @param A 被操作数组
 * @param lo 区间左端点 >=
 * @param hi 区间右端点 <
 */
template <typename T>
Vector<T>::Vector(T const *A, Rank lo, Rank hi)
{
    copyFrom(A, lo, hi);
}

/**
 * 构造函数（拷贝向量整体）
 * @param V 源向量
 */
template <typename T>
Vector<T>::Vector(const Vector<T> &V)
{
    copyFrom(V._elem, 0, V._size);
}

/**
 * 构造函数（拷贝向量指定区间）
 * @param V 源向量
 */
template <typename T>
Vector<T>::Vector(const Vector<T> &V, Rank lo, Rank hi)
{
    copyFrom(V._elem, lo, hi);
}

/**
 * 析构函数
 * @tparam T
 */
template <typename T>
Vector<T>::~Vector()
{
    delete[] _elem;
}

/**
 * 向量规模
 * @return Vector的大小
 */
template <typename T>
Rank Vector<T>::size() const
{

    return _size;
}

/**
 * 判断是否为空
 * @return 是否为空
 */
template <typename T>
bool Vector<T>::empty() const
{
    return !_size;
}

/**
 * 有序性判别
 * @return 向量中逆序相邻元素对的总数
 */
template <typename T>
int Vector<T>::disordered() const
{
    int n = 0; //计数器
    //逐一检查_size - 1对相邻元素
    for (int i = 1; i < _size; i++)
    {
        if (_elem[i - 1] > _elem[i])
        {
            n++; //逆序则计数
        }
    }
    return n; //向量有序当且仅当n = 0
}

/**
 * 无序向量的查找
 * @param e 要查询的数据
 * @return 所查找元素的秩
 */
template <typename T>
Rank Vector<T>::find(const T &e) const
{
    return find(e, 0, _size);
}

/**
 * 无序向量指定区间的查找
 * @param e 要查询的数据
 * @param lo 区间上界
 * @param hi 区间下界
 * @return hi < lo，则意味着失败；否则hi即命中元素的秩
 */
template <typename T>
Rank Vector<T>::find(const T &e, Rank lo, Rank hi) const
{ //assert: 0 <= lo < hi <= _size
    while ((lo < hi--) && (e != _elem[hi]))
        ;      //从后向前，顺序查找
    return hi; //若hi < lo，则意味着失败；否则hi即命中元素的秩
}

/**
 * 有序向量的查找
 * @param e 要查询的数据
 * @return 所查找元素的秩
 */
template <typename T>
Rank Vector<T>::search(const T &e) const
{
    return (0 >= _size) ? -1 : search(e, 0, _size);
}

/**
 * 有序向量指定区间的查找
 * @param e 要查询的数据
 * @param lo 区间上界
 * @param hi 区间下界
 * @return 所查找元素的秩
 */
template <typename T>
Rank Vector<T>::search(const T &e, Rank lo, Rank hi) const
{ //assert: 0 <= lo < hi <= _size
    binSearch(_elem, e, lo, hi);
    //    fibSearch(_elem, eNum, lo, hi);
    return 0;
}

/**
     * 重载下标运算符
     * @param r
     * @return _elem[r]
     */
template <typename T>
T &Vector<T>::operator[](Rank r) const
{
    return _elem[r];
}

/**
 * 重载赋值运算符
 * @return
 */
template <typename T>
Vector<T> &Vector<T>::operator=(const Vector<T> &V)
{
    if (_elem != nullptr)
    {
        delete[] _elem;
    }
    copyFrom(V._elem, 0, V.size());
    return *this;
}

/**
 * 重载比较运算符
 * @param rhs
 * @return
 */
template <typename T>
bool Vector<T>::operator==(const Vector &rhs) const
{
    if (_size != rhs._size)
    {
        return false;
    }
    for (int i = 0; i < _size; i++)
    {
        if (_elem[i] != rhs._elem[i])
        {
            return false;
        }
    }
    return true;
}

/**
 * 重载比较运算符
 * @param rhs
 * @return
 */
template <typename T>
bool Vector<T>::operator!=(const Vector &rhs) const
{
    return !(rhs == *this);
}

/**
 * 删除秩为r的元素
 * @param r 要删除的未知
 * @return 被删除的元素
 */
template <typename T>
T Vector<T>::remove(Rank r)
{                     //删除向量中秩为r的元素，0 <= r < length
    T e = _elem[r];   //备份被删除元素
    remove(r, r + 1); //调用区间删除算法，等效于对区间[r, r + 1)的删除
    return e;         //返回被删除元素
}

/**
 * 删除秩在指定区间的元素
 * @param lo 区间上界
 * @param hi 区间下界
 * @return 被删除元素的个数
 */
template <typename T>
int Vector<T>::remove(Rank lo, Rank hi)
{
    if (lo == hi)
    {
        //出于效率考虑，单独处理退化情况，比如remove(0, 0)
        return 0;
    }
    while (hi < _size)
    {
        _elem[lo++] = _elem[hi++]; //[hi, _size)顺次前移hi - lo个单元
    }
    _size = lo;     //更新规模，直接丢弃尾部[lo, _size = hi)区间
    shrink();       //若有必要，则缩容
    return hi - lo; //返回被删除元素的数目
}

/**
 * 在指定位置插入元素
 * @param r 要插入的位置
 * @param e 要插入的元素
 * @return 元素的秩
 */
template <typename T>
Rank Vector<T>::insert(Rank r, const T &e)
{             //assert: 0 <= r <= length
    expand(); //若有必要，扩容
    for (int i = _size; i > r; i--)
    {
        _elem[i] = _elem[i - 1]; //自后向前，后继元素顺次后移一个单元
    }
    _elem[r] = e;
    _size++;  //置入新元素并更新容量
    return r; //返回秩
}

/**
 * 在向量最后插入元素插入元素
 * @param e
 * @return
 */
template <typename T>
Rank Vector<T>::insert(const T &e)
{
    return insert(_size, e);
}

/**
 * 指定区间排序
 * @param lo
 * @param hi
 */
template <typename T>
void Vector<T>::sort(Rank lo, Rank hi)
{
    //    bubbleSort(lo, hi);
    //    selectionSort(lo, hi);
    //    mergeSort(lo, hi);
    quickSort(lo, hi);
    //    heapSort(lo, hi);
}

/**
 * 整体排序
 */
template <typename T>
void Vector<T>::sort()
{
    sort(0, _size);
}

/**
 * 无序向量的去重
 * @return 被删除元素总数
 */
template <typename T>
int Vector<T>::deduplicate()
{
    int oldSize = _size; //记录原规模
    Rank i = 1;          //从_elem[1]开始
    //自前向后逐一考查各元素_elem[i]
    while (i < _size)
    {
        if (find(_elem[i], 0, i) < 0)
        {
            i++; //在其前缀中寻找与之雷同者（至多一个）
        }
        else
        {
            remove(i); //若无雷同则继续考查其后继，否则删除雷同者
        }
    }
    return oldSize - _size; //向量规模变化量，即被删除元素总数
}

/**
 * 有序向量的去重
 * @return 被删除元素总数
 */
template <typename T>
int Vector<T>::uniquify()
{
    Rank i = 0, j = 0; //各对互异“相邻”元素的秩
    //逐一扫描，直至末元素
    while (++j < _size)
    {
        if (_elem[i] != _elem[j])
        {                          //跳过雷同者
            _elem[++i] = _elem[j]; //发现不同元素时，向前移至紧邻于前者右侧
        }
    }
    _size = ++i;
    shrink();     //直接截除尾部多余元素
    return j - i; //向量规模变化量，即被删除元素总数
}

/**
 * 遍历（使用函数指针，只读或局部性修改）
 * @param visit 遍历操作函数
 */
template <typename T>
void Vector<T>::traverse(void (*visit)(T &))
{
    for (int i = 0; i < _size; i++)
    {
        visit(_elem[i]);
    }
}

/**
 * 遍历（使用函数对象，可全局性修改）
 * @tparam VST 遍历函数对象 需重载()运算符
 */
template <typename T>
template <typename VST>
void Vector<T>::traverse(VST &visit)
{
    for (int i = 0; i < _size; i++)
    {
        visit(_elem[i]);
    }
}
} // namespace Structure
//Vector
#endif //STRUCTURE_VECTOR_H
