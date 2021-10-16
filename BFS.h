#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

#define lint long long

using namespace std;
#ifndef ORGBFS
#define ORGBFS

struct node
{
    lint id; // id=0 表示正常点，id=1表示异常点
    lint num; // 记录该点二阶邻居内黑点数
    lint flag; // 表记该顶点是否已经被bfs访问过
};

class orgBFS
{
public:
    lint n;
    vector<node> nodes;
    vector<vector<lint>> G;

    orgBFS(lint n_)
    {
        n = n_;
        node temp;
        vector<lint> vec_tmp;
        temp.num=0;
        temp.flag=-1;
        temp.id=0;
        for(lint i=0;i<n;i++)
        {
            nodes.push_back(temp);
            G.push_back(vec_tmp);
        }
    }
    ~orgBFS(){}

    void addEdge_nodict(lint i,lint j)
    {
        for(lint k=0; k<G[j].size(); k++)
        {
            if(G[j][k]==i)
                return;
        }
        G[i].push_back(j);
        G[j].push_back(i);
    }

    void setAbnormalPoints(vector<lint> arr)
    {
        for(lint i=0;i<arr.size();i++)
        {
            nodes[arr[i]].id++;
        }
    }

    void printanw()
    {
        for(lint i=0;i<20;i++)
        {
            cout<<nodes[i].num<<" ";
        }
        cout<<endl;
    }

    void BFSUtil(lint from)
    {
        vector<lint> vec_tmp;
        vector<lint> U; //U记录边缘点，下一次就从其中的点开始扩展
        lint deep=0,i,j;
        vec_tmp.push_back(from);
        nodes[from].flag=from;
        U = vec_tmp;
        vec_tmp.clear();
        while(deep<2)
        {
            for(lint s=0; s<U.size(); s++)
            {
                i=U[s];
                for(lint k=0; k<G[i].size(); k++)
                {
                    j=G[i][k];
                    if(nodes[j].flag==from)
                        continue;
                    nodes[j].flag=from;
                    if(nodes[j].id>0)
                        nodes[from].num++;
                    vec_tmp.push_back(j);
                }
            }
            U=vec_tmp;
            deep++;
        }
    }

    void BFSALL()
    {
        for(lint i=0; i<n; i++)
        {
            BFSUtil(i);
        }
    }
};

#endif // BFS
