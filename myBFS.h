#include <iostream>
#include <queue>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;
#ifndef MYBFS
#define MYBFS

struct mynode
{
    int id; // 0表示正常，1表示不正常
    int num; // 统计的邻居异常点数
    int flag; // 记录是否被该bfs遍历过
    set<int> visited;
};

class myBFS
{
private:
    int n;
    vector<mynode> nodes;
    vector<vector<int>> G;
    deque<vector<int>> Uarray;

public:
    myBFS(int n_)
    {
        n = n_;
        vector<int> vec_tmp;
        for(int i=0;i<n;i++)
        {
            mynode temp;
            temp.num=0;
            temp.flag=-1;
            temp.id=0;
            temp.visited.insert(i);
            nodes.push_back(temp);
            G.push_back(vec_tmp);
        }
    }
    ~myBFS(){}

    void addEdge_nodict(int i,int j)
    {
        for(int k=0; k<G[j].size(); k++)
        {
            if(G[j][k]==i)
                return;
        }
        G[i].push_back(j);
        G[j].push_back(i);
    }

    void setAbnormalPoints(vector<int> arr)
    {
        for(int i=0;i<arr.size();i++)
        {
            nodes[arr[i]].id++;
        }
    }

    void printanw()
    {
        for(int i=0;i<n;i++)
        {
            cout<<nodes[i].num<<" ";
        }
        cout<<endl;
    }

    void MyBFSUtil_map(int from)
    {
        int j,v,i,num=0;
        vector<int> vec_tmp;
        for(int k=0; k<G[from].size(); k++)
        {
            j=G[from][k];
            if(G[j].empty())
                continue;
            if(nodes[j].visited.find(from)==nodes[j].visited.end())
            {
                nodes[j].visited.insert(from);
                if(nodes[j].id>0)
                    nodes[from].num++;
                if(nodes[from].id>0)
                    nodes[j].num++;
            }
            vec_tmp.push_back(j);
        }
        //给一阶邻居经过该点的二阶信息，得到新的边缘顶点集
        for(int k=0;k<vec_tmp.size();k++)
        {
            j=vec_tmp[k];
            if(nodes[j].id>0)
                num=1;
            else num=0;
            for(int s=0;s<vec_tmp.size();s++)
            {
                v=vec_tmp[s];
                if(nodes[j].visited.find(v)==nodes[j].visited.end()&&v!=j)
                {
                    if(nodes[v].id>0)
                        nodes[j].num++;
                    nodes[v].num+=num;
                    nodes[v].visited.insert(j);
                    nodes[j].visited.insert(v);
                }
            }
        }
        //继续二阶遍历
        for(int s=0; s<vec_tmp.size(); s++)
        {
            i=vec_tmp[s];
            for(int k=0; k<G[i].size(); k++)
            {
                j=G[i][k];
                if(G[j].empty())
                    continue;
                if(nodes[j].visited.find(from)==nodes[j].visited.end())
                {
                    nodes[j].visited.insert(from);
                    if(nodes[j].id>0)
                        nodes[from].num++;
                    if(nodes[from].id>0)
                        nodes[j].num++;
                }
            }
        }
        G[from].clear();
    }

    void MyBFSALL_map()
    {
        for(int i=0; i<n; i++)
        {
            MyBFSUtil_map(i);
        }
    }
};

#endif // MYBFS
