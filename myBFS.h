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
    int id;                // 0��ʾ������1��ʾ������
    lint num;              // ͳ�Ƶ��ھ��쳣����
    lint flag;             // ��¼�Ƿ񱻸�bfs������,-1��ʾ���ͳ�Ƶĵ�
    vector<lint> visitedF; // ��¼��һ�׺ڵ�
    set<lint> visited;    // ��¼����ý��ǰ�ѷ��ֵĺڵ�
};

class myBFS
{
private:
    // �ܵĽ����
    lint n;
    // ������飬��Ŵ�0��ʼ
    vector<mynode> nodes;
    // �洢ͼ�ı߹�ϵ
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
        // ��ÿ��һ���ھ�
        for (lint k = 0; k < G[from].size(); k++)
        {
            j = G[from][k];
            // ��ÿ��һ�׵㣬����from��һ�׺ڵ㼯��������ظ��ͼ����ܵĺڵ㼯 visit
            for(lint i = 0; i < nodes[from].visitedF.size(); i++){
                lint temp =  nodes[from].visitedF[i];
                // �˵㻹û�м��� j ����֪�ڵ㼯
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
