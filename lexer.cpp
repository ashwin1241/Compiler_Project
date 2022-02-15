#include<bits/stdc++.h>
#include<fstream>
#include<iostream>
#include<algorithm>
#include<string.h>
#include<math.h>
typedef long long int ll;
#define MAX 1000000007

using namespace std;

vector<string> input()
{
    vector<string> asp;
    string s="";
    while(s[s.size()-1]!=';')
    {
        cin>>s;
        asp.push_back(s);
    }
    return asp;
}
int main()
{
    ll i,j;
    cout<<"Enter the input code:\n";
    vector<vector<string>> ipCode;
    vector<string> ipLine,end;
    end.push_back("eoc;");
    ipLine.push_back(" ");
    ipLine.push_back(" ");
    ipCode.push_back(ipLine);
    while(ipCode[ipCode.size()-1]!=end)
    {
        ipLine=input();
        ipCode.push_back(ipLine);
    }
    for(i=1;i<ipCode.size()-1;i++)
    {
        for(j=0;j<ipCode[i].size();j++)
        cout<<ipCode[i][j]<<" ";
        cout<<"\n";
    }
    return 0;
}