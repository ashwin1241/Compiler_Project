#include<bits/stdc++.h>
#include<fstream>
#include<iostream>
#include<algorithm>
#include<string.h>
#include<math.h>
typedef long long int ll;
#define MAX 1000000007

using namespace std;
int main()
{
    ll i;
    cout<<"Enter the input code:\n";
    vector<string> asp;
    string s="";
    while(s[s.size()-1]!=';')
    {
        cin>>s;
        asp.push_back(s);
    }
    for(i=0;i<asp.size();i++)
    {
        cout<<asp[i]<<" ";
    }
    return 0;
}