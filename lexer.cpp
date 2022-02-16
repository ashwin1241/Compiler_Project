//LM
//Token code for keywords is 1
//Token code for identifiers is 2
//Token code for numeric literal is 3
//Token code for operators is 4
//Token code for delimiters is 5
#include<bits/stdc++.h>
#include<fstream>
#include<iostream>
#include<algorithm>
#include<string.h>
#include<math.h>
typedef long long int ll;
#define MAX 1000000007

using namespace std;

map<string,ll> keyword_map,token_map;

void initialize_keyword_map()
{
    keyword_map["int"]=1;
    keyword_map["float"]=1;
    keyword_map["boolean"]=1;
    keyword_map["string"]=1;
    keyword_map["while"]=1;
    keyword_map["until"]=1;
    keyword_map["if"]=1;
    keyword_map["else"]=1;
    keyword_map["true"]=1;
    keyword_map["false"]=1;
}

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

void check_ident_or_key(string s)
{
    ll i,f=0;
    for(i=0;i<s.size();i++)
    {
        if((s[0]>='a'&&s[0]<='z')||(s[0]>='A'&&s[0]<='Z')||(s[0]>='0'&&s[0]<='9')||s[i]=='_')
            continue;
        else
        {
            f=1;
            break;
        }
    }
    if(f==0)
    {
        if(keyword_map.find(s)==keyword_map.end())
            token_map[s]=2;
        else
            token_map[s]=1;
    }
}

void check_num_lit(string s)
{
    ll i,f=0;
    for(i=0;i<s.size();i++)
    {
        if(s[i]<'0'||s[i]>'9')
        {
            f=1;
            break;
        }
    }
    if(f==0)
        token_map[s]=3;
    else
        cout<<s<<" is an illegal token\n";
}

void check_special_symbol(string s)
{
    token_map[s]=4;
}

void tokenize(vector<vector<string>> ipcode)
{
    ll i,j;
    for(i=1;i<ipcode.size();i++)
    {
        vector<string> container = ipcode[i];
        for(j=0;j<container.size();j++)
        {
            string s = container[j];
            if(s[s.size()-1]==';')
            s.pop_back();
            if(s[0]>='0'&&s[0]<='9')
                check_num_lit(s);
            else if((s[0]>='a'&&s[0]<='z')||(s[0]>='A'&&s[0]<='Z'))
                check_ident_or_key(s);
            else
                check_special_symbol(s);
        }
    }
}

int main()
{
    initialize_keyword_map();
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
    ipCode.pop_back();
    tokenize(ipCode);
    for(auto x : token_map)
    {
        switch(x.second)
        {
            case 1: cout<<"Token "<<x.first<<" is a keyword\n";
            break;
            case 2: cout<<"Token "<<x.first<<" is an identifier\n";
            break;
            case 3: cout<<"Token "<<x.first<<" is a numeric literal\n";
            break;
            case 4: cout<<"Token "<<x.first<<" is a special character\n";
            break;
            case 5:
            break;
        }
    }
    // for(i=1;i<ipCode.size()-1;i++)
    // {
    //     for(j=0;j<ipCode[i].size();j++)
    //     cout<<ipCode[i][j]<<" ";
    //     cout<<"\n";
    // }
    return 0;
}