#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <fstream>
#include <vector>

#define lint long long

using namespace std;

#ifndef CREATEDATA
#define CREATEDATA

class createdata
{
public:
    void createGraph(int n,string s)
    {
        ofstream fout(s);
        vector<int> arr;
        int temp,m,v=0;
        m=(n/5)*n;
        for(int i=0; i<n; i++)
        {
            if((rand()%n)<(n/2))
            {
                arr.push_back(i);
                v++;
            }
        }
        fout<<n<<" "<<m<<" "<<v<<endl;
        for(int i=0; i<arr.size(); i++)
            fout<<arr[i]<<" ";
        fout<<endl;
        srand((int)time(0));
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<(n/5); j++)
            {
                temp=rand()%n;
                while(temp==i)
                {
                    temp=rand()%n;
                }
                fout<<i<<" "<<temp<<endl;
            }
        }
        fout.close();
        cout<<"Success!"<<endl;
    }

    void createBlackNodes(lint n,lint b_n,string s1,string s2)
    {
        srand((int)time(0));
        ofstream fout1(s1);
        ofstream fout2(s2);
        lint num=0;
        for(lint i=0; i<n; i++)
        {
            lint temp = rand()%n;
            if(temp < b_n)
            {
                fout1<<i<<" ";
                num++;
            }
        }
        fout2<<num;
        fout1.close();
        fout2.close();
    }
};

#endif // CREATEDATA
