//
// Created by 庞博 on 2018-12-13.
//

#pragma once
#ifndef STRUCTURE_PRIORITYUPDATER_H
#define STRUCTURE_PRIORITYUPDATER_H
#include "Graph.h"
namespace Structure
{
template <typename Tv, typename Te>
struct BfsPU
{ //针对BFS算法的顶点优先级更新器
    virtual void operator()(Graph<Tv, Te> *g, int uk, int v)
    {
        if (g->status(v) == UNDISCOVERED) //对于uk每一尚未被发现的邻接顶点v
            if (g->priority(v) > g->priority(uk) + 1)
            {                                         //将其到起点的距离作为优先级数
                g->priority(v) = g->priority(uk) + 1; //更新优先级（数）
                g->parent(v) = uk;                    //更新父节点
            }                                         //如此效果等同于，先被发现者优先
    }
};

template <typename Tv, typename Te>
struct DfsPU
{ //针对DFS算法的顶点优先级更新器
    virtual void operator()(Graph<Tv, Te> *g, int uk, int v)
    {
        if (g->status(v) == UNDISCOVERED) //对于uk每一尚未被发现的邻接顶点v
            if (g->priority(v) > g->priority(uk) - 1)
            {                                         //将其到起点距离的负数作为优先级数
                g->priority(v) = g->priority(uk) - 1; //更新优先级（数）
                g->parent(v) = uk;                    //更新父节点
                return;                               //注意：与BfsPU()不同，这里只要有一个邻接顶点可更新，即可立即返回
            }                                         //如此效果等同于，后被发现者优先
    }
};

template <typename Tv, typename Te>
struct PrimPU
{ //针对Prim算法的顶点优先级更新器
    virtual void operator()(Graph<Tv, Te> *g, int uk, int v)
    {
        if (UNDISCOVERED == g->status(v)) //对于uk每一尚未被发现的邻接顶点v
            if (g->priority(v) > g->weight(uk, v))
            {                                      //按Prim策略做松弛
                g->priority(v) = g->weight(uk, v); //更新优先级（数）
                g->parent(v) = uk;                 //更新父节点
            }
    }
};

template <typename Tv, typename Te>
struct DijkstraPU
{ //针对Dijkstra算法的顶点优先级更新器
    virtual void operator()(Graph<Tv, Te> *g, int uk, int v)
    {
        if (UNDISCOVERED == g->status(v)) //对于uk每一尚未被发现的邻接顶点v，按Dijkstra策略
            if (g->priority(v) > g->priority(uk) + g->weight(uk, v))
            {                                                        //做松弛
                g->priority(v) = g->priority(uk) + g->weight(uk, v); //更新优先级（数）
                g->parent(v) = uk;                                   //并同时更新父节点
            }
    }
};
} // namespace Structure
#endif //STRUCTURE_PRIORITYUPDATER_H
