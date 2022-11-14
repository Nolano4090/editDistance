#include <iostream>
#include <vector>
using namespace std;

int LevenshteinSolver(string s1, string s2) //输入字符串s1,s2
{
    int n = s1.size();
    int m = s2.size();
    vector<vector<int>> minDist(n+1,vector<int>(m+1,0));   
    for(int i=0;i<=n;i++){minDist[i][0]=i;}         //dp数组初始化
    for(int j=0;j<=m;j++){minDist[0][j]=j;}
    for(int i=1;i<=n;i++)                           
    {
        for(int j=1;j<=m;j++)
        {
            if(s1[i-1]==s2[j-1])
            {minDist[i][j] = minDist[i-1][j-1];}
            else
            {minDist[i][j]=min(min(minDist[i-1][j-1],minDist[i-1][j]),minDist[i][j-1])+1;}  //计算每个位置的莱文斯廷编辑距离
        }
    }
    return minDist[n][m];   
}

int main()
{
    string s1 = "sea";
    string s2 = "eat";
    cout << LevenshteinSolver(s1,s2);
    return 0;
}