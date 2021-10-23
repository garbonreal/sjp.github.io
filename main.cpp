#include <iostream>
#include <vector>
#include <deque>
#include <windows.h>
#include <fstream>
#include <string>
#include "heapBFS.h"
#include "BFS.h"
#include "createdata.h"
#include "myBFS.h"
using namespace std;

#define MAX 400000

/*
n 顶点总数
m 总边数
k 异常点总数
*/
lint n, m, k;
vector<lint> abnodes;

/*
根据读入数据,在BFS,heapBFS两个算法对象中创建图
b BFS对象的索引
hb heapBFS对象的索引
cd createdata对象的索引，按定义随机生成黑点
percent 黑点占总顶点数的比例
s 存储边信息的文件
s_b 存储黑点的文件
s_n 存储黑点个数的文件
*/
void createNewGraph(orgBFS &b, heapBFS &hb, myBFS &mb, createdata cd, int percent, string s, string s_b, string s_n)
{
    lint u, v, temp;

    ifstream fin(s);
    ifstream finb(s_b);
    ifstream finn(s_n);

    //获得总顶点数和边数
    fin >> n >> m;

    //获得黑点数占总点数的概率
    lint b_n = (n * percent) / 100;

    //更新新的黑点情况
    cd.createBlackNodes(n, b_n, s_b, s_n);

    //获得总的黑点数
    finn >> k;

    //标注所有的黑点
    for (lint i = 0; i < k; i++)
    {
        finb >> temp;
        abnodes.push_back(temp);
    }
    hb.setAbnormalPoints(abnodes);
    b.setAbnormalPoints(abnodes);
    mb.setAbnormalPoints(abnodes); 

    //图记录所有的边情况
    for (lint i = 0; i < m; i++)
    {
        fin >> u >> v;
        hb.addEdge_nodict(u, v);
        b.addEdge_nodict(u, v);
        mb.addEdge_nodict(u, v); 
    }

    fin.close();
    finb.close();
    finn.close();
}   

int main()
{   
    createdata cd;
    string in="data/data_properities.txt";
    string out="data/result3.txt";
    ifstream fins(in);
    ofstream fouts;
    fouts.open(out,ios::app);
    string line;
    deque<string> filenames;

    getline(fins,line);
    cout<<line<<endl;

    //从配置文件中得到所有数据文件路径
    while(getline(fins,line))
    {
        filenames.push_back(line);
    }

    //时间的单位是10纳秒
    cout<<"time unit: x 10-8 s "<<endl;
    fouts<<"time unit: x 10-8 s "<<endl;

    while(!filenames.empty())
    {
        string s=filenames.front();
        filenames.pop_front();
        string s_b=filenames.front();
        filenames.pop_front();
        string s_n=filenames.front();
        filenames.pop_front();
        string s_i=filenames.front();
        filenames.pop_front();

        ifstream tempfin(s_i);
        getline(tempfin,line);

        fouts<<line<<endl;
        cout<<line<<endl;

        fouts<<"Black%"<<'\t'<<"BFS"<<'\t'<<"heapBFS"<<'\t'<<"MyBFS"<<endl;
        cout<<"Black%"<<'\t'<<"BFS"<<'\t'<<"heapBFS"<<'\t'<<"MyBFS"<<endl;

        for(int i=5; i<=40; i=i+5)
        {
            heapBFS hb(MAX);
            orgBFS b(MAX);
            myBFS mb(MAX);

            createNewGraph(b,hb,mb,cd,i,s,s_b,s_n);

            //记录BFS所消耗的时间
            LARGE_INTEGER t1,t2,tc;
            QueryPerformanceFrequency(&tc);
            QueryPerformanceCounter(&t1);
            b.BFSALL();
            QueryPerformanceCounter(&t2);
            lint temp1=(t2.QuadPart-t1.QuadPart);

            //记录heapBFS所消耗的时间
            QueryPerformanceCounter(&t1);
            hb.heapBFSALL();
            QueryPerformanceCounter(&t2);
            lint temp2=t2.QuadPart-t1.QuadPart;

            //记录myBFS消耗的时间
            QueryPerformanceCounter(&t1);
            mb.MyBFSALL();
            QueryPerformanceCounter(&t2);
            lint temp3=t2.QuadPart-t1.QuadPart;

            fouts<<i<<"%"<<'\t'<<temp1<<'\t'<<temp2<<'\t'<<temp3<<endl;
            cout<<i<<"%"<<'\t'<<temp1<<'\t'<<temp2<<'\t'<<temp3<<endl;

        }
        fouts<<"---------------------------------------"<<endl;
        cout<<"---------------------------------------"<<endl;
    }
    fins.close();
    fouts.close();
	return 0;
}

// int main()
// {
//     lint temp, u, v;
//     cin >> n >> m >> k;
//     for (int i = 0; i < k; i++)
//     {
//         cin >> temp;
//         abnodes.push_back(temp);
//     }
//     myBFS mbfs(n);
//     orgBFS b(n);
//     mbfs.setAbnormalPoints(abnodes);
//     b.setAbnormalPoints(abnodes);
//     for (int i = 0; i < m; i++)
//     {
//         cin >> u >> v;
//         mbfs.addEdge_nodict(u, v);
//         b.addEdge_nodict(u, v);
//     }
//     LARGE_INTEGER t1, t2, tc;
//     QueryPerformanceFrequency(&tc);
//     QueryPerformanceCounter(&t1);
//     b.BFSALL();
//     QueryPerformanceCounter(&t2);
//     lint temp1 = (t2.QuadPart - t1.QuadPart);

//     QueryPerformanceCounter(&t1);
//     mbfs.MyBFSALL();
//     QueryPerformanceCounter(&t2);
//     lint temp2 = (t2.QuadPart - t1.QuadPart);

//     mbfs.printanw();
//     mbfs.printanw();
    
//     cout<<"BFS used "<<temp1<<" x10-8s"<<endl;
//     cout<<"myBFS used "<<temp2<<" x10-8s"<<endl;
//     return 0;
// }