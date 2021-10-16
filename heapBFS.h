#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

#define lint long long

using namespace std;
#ifndef HEAPBFS_H
#define HEAPBFS_H

class heapNode{
public:
	lint n;
	heapNode(lint n_=0){
		n=n_;
	}
};

bool operator<(heapNode u,heapNode v){
	return u.n<v.n;
}

bool operator>(heapNode u,heapNode v){
	return u.n>v.n;
}

class minIndexNode
{
public:
    lint fromArrayIndex;
    lint nodeIndex;
    minIndexNode(lint i,lint j)
    {
        fromArrayIndex=i;
        nodeIndex=j;
    }
};

bool operator<(minIndexNode u,minIndexNode v){
	return u.nodeIndex<v.nodeIndex;
}

bool operator>(minIndexNode u,minIndexNode v){
	return u.nodeIndex>v.nodeIndex;
}

class vertex
{
public:
    int id;
    lint index;
    lint num;
    vector<heapNode> whiteNodes;
    priority_queue<heapNode,vector<heapNode>,greater<heapNode>> blackNodes;
    vertex(lint i)
    {
        index=i;
        id=0;
        num=0;
    }
};

class heapBFS
{
public:
    lint n;
    vector<vertex> vertexes;

    heapBFS(lint n_)
    {
        n = n_;
        for(lint i=0;i<n;i++)
        {
            vertex v(i);
            vertexes.push_back(v);
        }
    }
    ~heapBFS(){};

    void addEdge(lint i,lint j)
    {
        heapNode h(j);
        if(vertexes[j].id>0)
            vertexes[i].blackNodes.push(h);
        else
            vertexes[i].whiteNodes.push_back(h);
    }

    void addEdge_nodict(lint i,lint j)
    {
        addEdge(i,j);
        addEdge(j,i);
    }

    void setAbnormalPoints(vector<lint> arr)
    {
        for(lint i=0;i<arr.size();i++)
        {
            vertexes[arr[i]].id++;
        }
    }

    void printanw()
    {
        for(lint i=0;i<20;i++)
            cout<<vertexes[i].num<<" ";
        cout<<endl;
    }

    //求一个顶点黑点数的操作
    int heapBFSUtil(lint i)
    {
        //cout<<"node "<<i<<"'s turn now"<<endl;

        //如果没有邻居，直接返回0
        if(vertexes[i].whiteNodes.size()+vertexes[i].blackNodes.size()==0)
            return 0;

        //存储该顶点求得的黑点数
        lint num=0;
        //合并堆到达的最大值
        lint Min=-1;
        //从合并堆中取出最小元素索引
        lint tempMinIndex;
        //取出元素来自哪一个黑点堆
        lint tempFromArrayIndex;
        //暂存中间值
        lint temp;

        //将所有要合并的黑点堆先存在 blackArray 中
        vector<priority_queue<heapNode,vector<heapNode>,greater<heapNode>>> blackArray;
        //合并所有黑点堆的合并堆
        priority_queue<minIndexNode,vector<minIndexNode>,greater<minIndexNode>> mergeBlack;

        //先加上顶点 i 的一阶黑点堆，不然可能会重复计算
        if(!vertexes[i].blackNodes.empty()){
            blackArray.push_back(vertexes[i].blackNodes);
            //cout<<i<<" ";
        }

        //将顶点 i 的白色邻居的黑点堆，存入blackArray中
        for(lint v=0;v<vertexes[i].whiteNodes.size();v++)
        {
            temp = vertexes[i].whiteNodes[v].n;
            if(!vertexes[temp].blackNodes.empty())
            {
                //cout<<vertexes[temp].index<<" ";
                blackArray.push_back(vertexes[temp].blackNodes);
            }
        }

        //将顶点 i 的黑色邻居的黑点堆，存入blackArray中
        priority_queue<heapNode,vector<heapNode>,greater<heapNode>> tempQq;
        tempQq = vertexes[i].blackNodes;
        while(!tempQq.empty())
        {
            temp = tempQq.top().n;
            if(!vertexes[temp].blackNodes.empty())
            {
                blackArray.push_back(vertexes[temp].blackNodes);
                //cout<<vertexes[temp].index<<" ";
            }
            tempQq.pop();
        }
        //cout<<endl;

        //如果blackArray没有存到任何集合，则返回0
        if(blackArray.empty())
            return 0;

        //用mergeBlack堆存储所有黑点堆的第一个元素
        //每次从mergeBlack堆中弹出最小的元素，再从其源堆中取出一个元素放入
        for(lint v=0;v<blackArray.size();v++)
        {
            minIndexNode temp(v,blackArray[v].top().n);
            mergeBlack.push(temp);
            //cout<<"Pop number "<<v<<" blackArray's min nodeIndex: "<<blackArray[v].top().n<<endl;
            blackArray[v].pop();
        }

        while(!mergeBlack.empty())
        {
            //从合并堆中取出最小元素
            tempMinIndex = mergeBlack.top().nodeIndex;
            //记录取出最小元素的黑点堆
            tempFromArrayIndex = mergeBlack.top().fromArrayIndex;
            mergeBlack.pop();
            //cout<<"Pop minIndex "<<tempMinIndex<<" from blackArray "<<tempFromArrayIndex<<endl;

            //取出的最小元素可能出现重复的情况，此时不计数
            //如果大于当前记录的最小值，替换最小值，计数
            if(tempMinIndex > Min)
            {
                Min = tempMinIndex;
                num++;
                //cout<<"num++ and change min to "<<Min<<endl;
            }

            //如果弹出元素的原黑点堆还有元素，则补充
            if(!blackArray[tempFromArrayIndex].empty())
            {
                minIndexNode temp(tempFromArrayIndex,blackArray[tempFromArrayIndex].top().n);
                //cout<<"blackArray "<<tempFromArrayIndex<<" pop node "<<blackArray[tempFromArrayIndex].top().n<<endl;
                mergeBlack.push(temp);
                blackArray[tempFromArrayIndex].pop();
            }
        }
        //如果本身为黑点，则会将自身算入
        if(vertexes[i].id>0) num--;
        //cout<<"num = "<<num<<endl;
        return num;
    }
    void heapBFSALL()
    {
        for(lint i=0;i<n;i++)
            vertexes[i].num=heapBFSUtil(i);
    }
};

#endif
