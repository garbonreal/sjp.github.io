#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

#define lint long long

using namespace std;
#ifndef BLACKBFS
#define BLACKBFS

//图中的顶点
struct bnode
{
    lint id; // id=0 表示正常点，id=1表示异常点
    lint num; // 记录该点二阶邻居内黑点数
    lint flag; // 表记该结点是否已经被bfs访问过
    vector<lint> blacks; //存储该结点的一阶黑点
};

//BFS算法类
class blackBFS
{
public:
    //图的结点数
    lint n;
    //存储结点的数组
    vector<bnode> nodes;
    //存储图
    vector<vector<lint>> G;

    blackBFS(lint n_)
    {
        n = n_;
        bnode temp;
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
    ~blackBFS(){}

    void addEdge_nodict(lint i,lint j)
    {
        G[i].push_back(j);
        G[j].push_back(i);
        if(nodes[i].id>0){
            nodes[j].blacks.push_back(i);
        }
        if(nodes[j].id>0){
            nodes[i].blacks.push_back(j);
        }
    }

    void setAbnormalPoints(vector<lint> arr)
    {
        for(lint i=0;i<arr.size();i++)
        {
            nodes[arr[i]].id++;
        }
    }

    void printanw(lint k)
    {
        for(lint i=0;i<k;i++)
        {
            cout<<nodes[i].num<<" ";
        }
        cout<<endl;
    }

    void blackBFSUtil(lint from)
    {
        int j,num=0;
        vector<lint>::iterator i;
        // 将源点本身标记为已访问
        nodes[from].flag=from;
        // 一阶黑点都算做已访问，并增加黑点数
        for(i=nodes[from].blacks.begin();i!=nodes[from].blacks.end();i++){
            nodes[(*i)].flag=from;
        }
        num += nodes[from].blacks.size();
        // 对所有一阶邻居的黑点集做 bfs 遍历
        for(lint k=0;k<G[from].size();k++){
            j = G[from][k];
            for(i=nodes[j].blacks.begin();i!=nodes[j].blacks.end();i++){
                if(nodes[*i].flag!=from){
                    num++;
                    nodes[*i].flag=from;
                }
            }
        }
        nodes[from].num = num;
    }

    void blackBFSALL()
    {
        for(lint i=0; i<n; i++)
        {
            blackBFSUtil(i);
        }
    }
};

#endif // BFS
