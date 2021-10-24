#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

#define lint long long

using namespace std;
#ifndef HEAPBFS_H
#define HEAPBFS_H

//ÿ������������б��ֱ�洢��һ���ھӵĺڵ�Ͱ׵㣬�б��е�Ԫ��ΪheapNode
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
    //��vector�ķ�ʽ�洢һ���ھӵİ׵�
    vector<heapNode> whiteNodes;
    //����С�ѵķ�ʽ�洢һ���ھӵĺڵ�
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

    void printanw(lint k)
    {
        for(lint i=0;i<k;i++)
            cout<<vertexes[i].num<<" ";
        cout<<endl;
    }

    //��һ������ڵ����Ĳ���
    int heapBFSUtil(lint i)
    {
        //cout<<"node "<<i<<"'s turn now"<<endl;

        //���û���ھӣ�ֱ�ӷ���0
        if(vertexes[i].whiteNodes.size()+vertexes[i].blackNodes.size()==0)
            return 0;

        //�洢�ö�����õĺڵ���
        lint num=0;
        //�ϲ��ѵ�������ֵ
        lint Min=-1;
        //�Ӻϲ�����ȡ����СԪ������
        lint tempMinIndex;
        //ȡ��Ԫ��������һ���ڵ��
        lint tempFromArrayIndex;
        //�ݴ��м�ֵ
        lint temp;

        //������Ҫ�ϲ��ĺڵ���ȴ��� blackArray ��
        vector<priority_queue<heapNode,vector<heapNode>,greater<heapNode>>> blackArray;
        //�ϲ����кڵ�ѵĺϲ���
        priority_queue<minIndexNode,vector<minIndexNode>,greater<minIndexNode>> mergeBlack;

        //�ȼ��϶��� i ��һ�׺ڵ�ѣ���Ȼ���ܻ��ظ�����
        if(!vertexes[i].blackNodes.empty()){
            blackArray.push_back(vertexes[i].blackNodes);
            //cout<<i<<" ";
        }

        //������ i �İ�ɫ�ھӵĺڵ�ѣ�����blackArray��
        for(lint v=0;v<vertexes[i].whiteNodes.size();v++)
        {
            temp = vertexes[i].whiteNodes[v].n;
            if(!vertexes[temp].blackNodes.empty())
            {
                //cout<<vertexes[temp].index<<" ";
                blackArray.push_back(vertexes[temp].blackNodes);
            }
        }

        //������ i �ĺ�ɫ�ھӵĺڵ�ѣ�����blackArray��
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

        //���blackArrayû�д浽�κμ��ϣ��򷵻�0
        if(blackArray.empty())
            return 0;

        //��mergeBlack�Ѵ洢���кڵ�ѵĵ�һ��Ԫ��
        //ÿ�δ�mergeBlack���е�����С��Ԫ�أ��ٴ���Դ����ȡ��һ��Ԫ�ط���
        for(lint v=0;v<blackArray.size();v++)
        {
            minIndexNode temp(v,blackArray[v].top().n);
            mergeBlack.push(temp);
            //cout<<"Pop number "<<v<<" blackArray's min nodeIndex: "<<blackArray[v].top().n<<endl;
            blackArray[v].pop();
        }

        while(!mergeBlack.empty())
        {
            //�Ӻϲ�����ȡ����СԪ��
            tempMinIndex = mergeBlack.top().nodeIndex;
            //��¼ȡ����СԪ�صĺڵ��
            tempFromArrayIndex = mergeBlack.top().fromArrayIndex;
            mergeBlack.pop();
            //cout<<"Pop minIndex "<<tempMinIndex<<" from blackArray "<<tempFromArrayIndex<<endl;

            //ȡ������СԪ�ؿ��ܳ����ظ����������ʱ������
            //������ڵ�ǰ��¼����Сֵ���滻��Сֵ������
            if(tempMinIndex > Min)
            {
                Min = tempMinIndex;
                num++;
                //cout<<"num++ and change min to "<<Min<<endl;
            }

            //�������Ԫ�ص�ԭ�ڵ�ѻ���Ԫ�أ��򲹳�
            if(!blackArray[tempFromArrayIndex].empty())
            {
                minIndexNode temp(tempFromArrayIndex,blackArray[tempFromArrayIndex].top().n);
                //cout<<"blackArray "<<tempFromArrayIndex<<" pop node "<<blackArray[tempFromArrayIndex].top().n<<endl;
                mergeBlack.push(temp);
                blackArray[tempFromArrayIndex].pop();
            }
        }
        //�������Ϊ�ڵ㣬��Ὣ��������
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
