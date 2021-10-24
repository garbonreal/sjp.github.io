#include <iostream>
#include <queue>
#include <set>
#include <vector>
#include <algorithm>

#define lint long long

using namespace std;
#ifndef MYBFS
#define MYBFS

struct mynode
{
    int id;                // 0表示正常，1表示不正常
    lint num;              // 统计的邻居异常点数
    lint flag;             // 记录是否被该bfs遍历过,-1表示完成统计的点
    vector<lint> visitedF; // 记录其一阶黑点
    set<lint> visited;    // 记录计算该结点前已发现的黑点
};

class myBFS
{
private:
    // 总的结点数
    lint n;
    // 结点数组，标号从0开始
    vector<mynode> nodes;
    // 存储图的边关系
    vector<vector<lint>> G;

public:
    myBFS(lint n_)
    {
        n = n_;
        vector<lint> vec_tmp;
        for (lint i = 0; i < n; i++)
        {
            mynode temp;
            temp.num = 0;
            temp.flag = -1;
            temp.id = 0;
            nodes.push_back(temp);
            G.push_back(vec_tmp);
        }
    }
    ~myBFS(){}

    void addEdge_nodict(lint i, lint j)
    {
        G[i].push_back(j);
        G[j].push_back(i);
        if(nodes[i].id>0){
            nodes[j].visitedF.push_back(i);
            nodes[j].visited.insert(i);
        }
        if(nodes[j].id>0){
            nodes[i].visitedF.push_back(j);
            nodes[i].visited.insert(j);
        }
    }

    void setAbnormalPoints(vector<lint> arr)
    {
        for (lint i = 0; i < arr.size(); i++)
        {
            nodes[arr[i]].id++;
        }
    }

    void printanw()
    {
        for (lint i = 0; i < n; i++)
        {
            cout << nodes[i].num << " ";
        }
        cout << endl;
    }

    void MyBFSUtil(lint from)
    {
        int j,i;
        // 对每个一阶邻居
        for (lint k = 0; k < G[from].size(); k++)
        {
            j = G[from][k];
            // 对每个一阶点，遍历from的一阶黑点集，如果不重复就加入总的黑点集 visit
            for(lint i = 0; i < nodes[from].visitedF.size(); i++){
                lint temp =  nodes[from].visitedF[i];
                // 此点还没有加入 j 的已知黑点集
                if(nodes[j].visited.find(temp)==nodes[j].visited.end()){
                    nodes[j].visited.insert(temp);
                }
            }
        }
    }

    void MyBFSALL()
    {
        for (lint i = 0; i < n; i++)
        {
            MyBFSUtil(i);
        }
        for (lint i = 0; i < n; i++){
            if(nodes[i].id>0)
                nodes[i].num=nodes[i].visited.size()-1;
            else
                nodes[i].num=nodes[i].visited.size();
        }
    }
};

#endif // MYBFS
