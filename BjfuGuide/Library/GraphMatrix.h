//
// Created by 庞博 on 2018-12-13.
//

#pragma once
#ifndef STRUCTURE_GRAPHMATRIX_H
#define STRUCTURE_GRAPHMATRIX_H

#include "Vector.h" //引入向量
#include "Graph.h"  //引入图
#include "Stack.h"
#include "PriorityUpdater.h"

namespace Structure
{
/**
 * 顶点对象
 * @tparam Tv
 */
template <typename Tv>
struct Vertex
{
    Tv data;                 // 数据
    int inDegree, outDegree; // 出入度数
    VStatus status;          // 状态
    int dTime, fTime;        // 时间标签
    int parent;
    int priority; //在遍历树中的父节点、优先级数
    // 构造函数
    explicit Vertex(Tv const &d = (Tv)0) : data(d), inDegree(0), outDegree(0), status(UNDISCOVERED),
                                           dTime(-1), fTime(-1), parent(-1), priority(INT_MAX) {}
};

/**
 * 边对象
 * @tparam Te
 */
template <typename Te>
struct Edge
{
    Te data;    // 数据
    int weight; // 权重
    EType type; // 类型
    // 构造函数
    Edge(Te const &d, int w) : data(d), weight(w), type(UNDETERMINED) {}
};

/**
 * GraphMatrix template class
 * 邻接矩阵模板类
 * @tparam Tv 顶点类型
 * @tparam Te 边类型
 */
template <typename Tv, typename Te>
class GraphMatrix : public Graph<Tv, Te>
{ //基于向量，以邻接矩阵形式实现的图
  private:
    Vector<Vertex<Tv>> V;         //顶点集（向量）
    Vector<Vector<Edge<Te> *>> E; //边集（邻接矩阵）
  public:
    /**
         * 构造函数
         */
    GraphMatrix()
    {
        this->vNum = this->eNum = 0;
    }

    /**
         * 析构函数
         */
    ~GraphMatrix()
    {
        for (int j = 0; j < this->vNum; j++)     //所有动态创建的
            for (int k = 0; k < this->vNum; k++) //边记录
                delete E[j][k];                  //逐条清除
    }

	GraphMatrix<Tv, Te> &operator=(const GraphMatrix<Tv, Te> &G) {
		this->V = G.V;
		this->E = G.E;
		return *this;
	}

    // 顶点的基本操作：查询第i个顶点（0 <= i < vNum）
    /**
         * 返回顶点数据
         * @param i
         * @return 第i个顶点的数据
         */
    virtual Tv &vertex(int i)
    {
        return V[i].data;
    }

    /**
         * 返回入度
         * @param i
         * @return 第i个顶点入度
         */
    virtual int inDegree(int i)
    {
        return V[i].inDegree;
    }

    /**
         * 返回出度
         * @param i
         * @return 第i个顶点出度
         */
    virtual int outDegree(int i)
    {
        return V[i].outDegree;
    }

    /**
         * 找到i的首个邻接顶点
         * @param i
         * @return 首个邻接顶点
         */
    virtual int firstNbr(int i)
    {
        return nextNbr(i, this->vNum);
    }

    /**
         * 逆向线性试探
         * 相对于顶点j的下一邻接顶点（改用邻接表可提高效率）
         * @param i
         * @param j
         * @return
         */
    virtual int nextNbr(int i, int j)
    {
        while ((-1 < j) && (!exists(i, --j)))
            ;
        return j;
    }

    /**
         * 返回第i个顶点的状态
         * @param i
         * @return 第i个顶点的状态
         */
    virtual VStatus &status(int i)
    {
        return V[i].status;
    }

    /**
         * 时间标签dTime
         * @param i
         * @return 时间标签dTime
         */
    virtual int &dTime(int i)
    {
        return V[i].dTime;
    }

    /**
         * 时间标签fTime
         * @param i
         * @return 时间标签fTime
         */
    virtual int &fTime(int i)
    {
        return V[i].fTime;
    }

    /**
         * 在遍历树中的父亲
         * @param i
         * @return 在遍历树中的父亲
         */
    virtual int &parent(int i)
    {
        return V[i].parent;
    }

    /**
         * 在遍历树中的优先级数
         * @param i
         * @return
         */
    virtual int &priority(int i)
    {
        return V[i].priority;
    }

    // 顶点的动态操作
    /**
         * 插入顶点
         * @param vertex
         * @return 顶点编号
         */
    virtual int insert(Tv const &vertex)
    {
        for (int j = 0; j < this->vNum; j++)
        {
            E[j].insert(NULL); //各顶点预留一条潜在的关联边
        }
        this->vNum++;
        // Vector<Edge<Te> *>(容量，规模，初值)
        E.insert(Vector<Edge<Te> *>(this->vNum, this->vNum, (Edge<Te> *)NULL)); //创建新顶点对应的边向量
        return V.insert(Vertex<Tv>(vertex));                                    //顶点向量增加一个顶点
    }

    /**
         * 删除第i个顶点及其关联边（0 <= i < n）
         * @param i
         * @return
         */
    virtual Tv remove(int i)
    {
        for (int j = 0; j < this->vNum; j++)
        { // 所有出边
            if (exists(i, j))
            {
                delete E[i][j];
				E[i][j] = NULL;
                V[j].inDegree--;
            } //逐条删除
        }
        E.remove(i);
        this->vNum--; //删除第i行
        Tv vBak = vertex(i);
        V.remove(i); //删除顶点i
        for (int j = 0; j < this->vNum; j++)
        { //所有入边
            if (Edge<Te> *e = E[j].remove(i))
            {
                delete e;
				e = NULL;
                V[j].outDegree--;
            } //逐条删除
        }
        return vBak; //返回被删除顶点的信息
    }

    // 边的确认操作
    /**
         * 边(i, j)是否存在
         * @param i
         * @param j
         * @return
         */
    virtual bool exists(int i, int j)
    {
        return (0 <= i) && (i < this->vNum) && (0 <= j) && (j < this->vNum) && E[i][j] != NULL;
    }
    // 边的基本操作：查询顶点i与j之间的联边（0 <= i, j < n且exists(i, j)）
    /**
         * 边(i, j)的类型
         * @param i
         * @param j
         * @return 边(i, j)的类型
         */
    virtual EType &type(int i, int j)
    {
        return E[i][j]->type;
    }

    /**
         * 边(i, j)的数据
         * @param i
         * @param j
         * @return 边(i, j)的数据
         */
    virtual Te &edge(int i, int j)
    {
        return E[i][j]->data;
    }

    /**
         * 边(i, j)的权重
         * @param i
         * @param j
         * @return
         */
    virtual int &weight(int i, int j)
    {
        return E[i][j]->weight;
    }

    // 边的动态操作
    /**
         * 插入权重为w的边e = (i, j)
         * @param edge
         * @param w
         * @param i
         * @param j
         */
    virtual void insert(Te const &edge, int w, int i, int j)
    {
        if (exists(i, j))
        {
            return; //确保该边尚不存在
        }
        E[i][j] = new Edge<Te>(edge, w); //创建新边
        this->eNum++;
        V[i].outDegree++;
        V[j].inDegree++; //更新边计数与关联顶点的度数
    }

    /**
         * 删除顶点i和j之间的联边（exists(i, j)）
         * @param i
         * @param j
         * @return
         */
    virtual Te remove(int i, int j)
    {
        Te eBak = edge(i, j);
        delete E[i][j];
        E[i][j] = NULL; //备份后删除边记录
        this->eNum--;
        V[i].outDegree--;
        V[j].inDegree--; //更新边计数与关联顶点的度数
        return eBak;     //返回被删除边的信息
    }

    Vector<Stack<Tv>> &dfsFindAllPath(int i, int j)
    {
        this->reset();
        int clock = 0;
        auto allPath = new Vector<Stack<Tv>>; // 注意内存泄漏
        Stack<Tv> path;
        path.push(vertex(i));
        DFS(i, j, clock, *allPath, path);
        return *allPath;
    }

    void DFS(int i, int j, int &clock, Vector<Stack<Tv>> &allPath, Stack<Tv> &path)
    { //assert: 0 <= i < vNum
        if (i == j)
        {
            allPath.insert(path);
            path.pop();
            return;
        }
        dTime(i) = ++clock;
        status(i) = DISCOVERED; //发现当前顶点v
        for (int u = firstNbr(i); - 1 < u; u = nextNbr(i, u))
        { //枚举v的所有邻居u
            switch (status(u))
            {                  //并视其状态分别处理
            case UNDISCOVERED: //u尚未发现，意味着支撑树可在此拓展
                type(i, u) = TREE;
                parent(u) = i;
                path.push(vertex(u));
                DFS(u, j, clock, allPath, path);
                while (path.top() != vertex(i))
                {
                    Tv temp = path.pop();
                    int k;
                    for (k = 0; k < this->vNum; k++)
                    {
                        if (vertex(k) == temp)
                        {
                            break;
                        }
                    }
                    status(k) = UNDISCOVERED;
                }
                break;
            case DISCOVERED: //u已被发现但尚未访问完毕，应属被后代指向的祖先
                type(i, u) = BACKWARD;
                break;
            default: //u已访问完毕（VISITED，有向图），则视承袭关系分为前向边或跨边
                type(i, u) = (dTime(i) < dTime(u)) ? FORWARD : CROSS;
                break;
            }
        }
        status(i) = VISITED;
        fTime(i) = ++clock; //至此，当前顶点v方告访问完毕
    }

    const Vector<Vertex<Tv>> &getV() const
    {
        return V;
    }

    const Vector<Vector<Edge<Te> *>> &getE() const
    {
        return E;
    }
};

} // namespace Structure

#endif //STRUCTURE_GRAPHMATRIX_H
