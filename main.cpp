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
#include "blackBFS.h"
using namespace std;

#define MAX 400000

/*
n ��������
m �ܱ���
k �쳣������
*/
lint n, m, k;
vector<lint> abnodes;

/*
���ݶ�������,��BFS,heapBFS�����㷨�����д���ͼ
b BFS���������
hb heapBFS���������
cd createdata�����������������������ɺڵ�
percent �ڵ�ռ�ܶ������ı���
s �洢����Ϣ���ļ�
s_b �洢�ڵ���ļ�
s_n �洢�ڵ�������ļ�
*/
void createNewGraph(orgBFS &b, heapBFS &hb, myBFS &mb, blackBFS &bb, createdata cd, lint percent, string s, string s_b, string s_n)
{
    lint u, v, temp;

    ifstream fin(s);
    ifstream finb(s_b);
    ifstream finn(s_n);

    //����ܶ������ͱ���
    fin >> n >> m;

    //��úڵ���ռ�ܵ����ĸ���
    lint b_n = (n * percent) / 100;

    //�����µĺڵ����
    cd.createBlackNodes(n, b_n, s_b, s_n);

    //����ܵĺڵ���
    finn >> k;

    //��ע���еĺڵ�
    for (lint i = 0; i < k; i++)
    {
        finb >> temp;
        abnodes.push_back(temp);
    }
    //hb.setAbnormalPoints(abnodes);
    b.setAbnormalPoints(abnodes);
    //mb.setAbnormalPoints(abnodes);
    bb.setAbnormalPoints(abnodes);

    //ͼ��¼���еı����
    for (lint i = 0; i < m; i++)
    {
        fin >> u >> v;
        //hb.addEdge_nodict(u, v);
        b.addEdge_nodict(u, v);
        //mb.addEdge_nodict(u, v);
        bb.addEdge_nodict(u,v);
    }

    fin.close();
    finb.close();
    finn.close();
}

int main()
{
    createdata cd;
    string in="data/data_properities.txt";
    string out="data/result4.txt";
    ifstream fins(in);
    ofstream fouts;
    fouts.open(out,ios::app);
    string line;
    deque<string> filenames;

    //�������ļ��еõ����������ļ�·��
    while(getline(fins,line))
    {
        filenames.push_back(line);
    }

    //ʱ��ĵ�λ��10����
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

        fouts<<"Black%"<<'\t'<<"BFS"<<'\t'<<"blackBFS"<<endl;//<<'\t'<<"MyBFS"<<'\t'<<"blackBFS"<<endl;
        cout<<"Black%"<<'\t'<<"BFS"<<'\t'<<"blackBFS"<<endl;//'\t'<<"MyBFS"<<'\t'<<"blackBFS"<<endl;

        for(int i=1; i<=20;)
        {
            heapBFS hb(1);
            myBFS mb(1);
            orgBFS b(MAX);
            blackBFS bb(MAX);

            createNewGraph(b, hb, mb, bb, cd, i, s, s_b, s_n);

            //��¼BFS�����ĵ�ʱ��
            LARGE_INTEGER t1,t2,tc;
            QueryPerformanceFrequency(&tc);
            QueryPerformanceCounter(&t1);
            b.BFSALL();
            QueryPerformanceCounter(&t2);
            lint temp1=(t2.QuadPart-t1.QuadPart);

//            //��¼heapBFS�����ĵ�ʱ��
//            QueryPerformanceCounter(&t1);
//            hb.heapBFSALL();
//            QueryPerformanceCounter(&t2);
//            lint temp2=t2.QuadPart-t1.QuadPart;
//
//            //��¼myBFS���ĵ�ʱ��
//            QueryPerformanceCounter(&t1);
//            mb.MyBFSALL();
//            QueryPerformanceCounter(&t2);
//            lint temp3=t2.QuadPart-t1.QuadPart;

            //��¼blackBFS���ĵ�ʱ��
            QueryPerformanceCounter(&t1);
            bb.blackBFSALL();
            QueryPerformanceCounter(&t2);
            lint temp4=t2.QuadPart-t1.QuadPart;

            fouts<<i<<"%"<<'\t'<<temp1<<'\t'<<temp4<<endl;//<<'\t'<<temp3<<'\t'<<temp4<<endl;
            cout<<i<<"%"<<'\t'<<temp1<<'\t'<<temp4<<endl;//<<'\t'<<temp3<<'\t'<<temp4<<endl;

            if(i<5)
                i++;
            else
                i+=5;
        }
        fouts<<"---------------------------------------"<<endl;
        cout<<"---------------------------------------"<<endl;
    }
    fins.close();
    fouts.close();
    return 0;
}

//int main()
//{
//    lint temp, u, v;
//    cin >> n >> m >> k;
//    for (int i = 0; i < k; i++)
//    {
//        cin >> temp;
//        abnodes.push_back(temp);
//    }
//    blackBFS bb(n);
//    myBFS mbfs(n);
//    orgBFS b(n);
//    mbfs.setAbnormalPoints(abnodes);
//    b.setAbnormalPoints(abnodes);
//    bb.setAbnormalPoints(abnodes);
//    for (int i = 0; i < m; i++)
//    {
//        cin >> u >> v;
//        mbfs.addEdge_nodict(u, v);
//        b.addEdge_nodict(u, v);
//        bb.addEdge_nodict(u,v);
//    }
//    LARGE_INTEGER t1, t2, tc;
//    QueryPerformanceFrequency(&tc);
//    QueryPerformanceCounter(&t1);
//    b.BFSALL();
//    QueryPerformanceCounter(&t2);
//    lint temp1 = (t2.QuadPart - t1.QuadPart);
//
//    QueryPerformanceCounter(&t1);
//    mbfs.MyBFSALL();
//    QueryPerformanceCounter(&t2);
//    lint temp2 = (t2.QuadPart - t1.QuadPart);
//
//    QueryPerformanceCounter(&t1);
//    bb.blackBFSALL();
//    QueryPerformanceCounter(&t2);
//    lint temp3 = (t2.QuadPart - t1.QuadPart);
//
//    b.printanw();
//    mbfs.printanw();
//    bb.printanw();
//
//    cout<<"BFS used "<<temp1<<" x10-8s"<<endl;
//    cout<<"myBFS used "<<temp2<<" x10-8s"<<endl;
//    cout<<"blackBFS used "<<temp3<<" x10-8s"<<endl;
//    return 0;
//}
