#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;
//using std::cout; using std::cerr;
//using std::endl; using std::string;
//using std::ifstream; using std::vector;

bool isKeyword(string word){
    vector<string> keywords = {"int","main", "float", "boolean", "string", "while", "until", "if" ,"else", "true", "false", "continue", "break"};
    if(find(keywords.begin(), keywords.end(), word) != keywords.end())
    return true;
    else
    return false;
}

bool isOperator(string word){
    vector<string> oprator = {"<", ">", "<=", ">=", "*", "+", "-", "/", "=", "-=", "*=", "+=", "/=", "++", "--", "=="};
    if(find(oprator.begin(), oprator.end(), word) != oprator.end())
    return true;
    else
    return false;
}

bool isDelimiter(string word){
    vector<string> delimiter = {"{", "}", "(", ")", "[", "]", ";", ","};
    if(find(delimiter.begin(), delimiter.end(), word) != delimiter.end())
    return true;
    else
    return false;
}

bool isString(string word){
    if(word[0] == '"' && word[word.size()-1] == '"')
    return true;
    else
    return false;
}

bool isInteger(string word){
    for(int i=0;i<word.size();i++){
        if(word[i]>='0'&&word[i]<='9')
        continue;
        return false;
    }
    return true;
}

bool isFloat(string word){
    int t=-1;
    for(int i=0;i<word.size();i++){
        if(word[i]=='.'){
            t=i;
            break;
        }
    }

    if(t==-1)
    return false;

    string beforeDecimal = word.substr(0, t);
    string afterDecimal = word.substr(t + 1);

    if(isInteger(beforeDecimal) && isInteger(afterDecimal))
    return true;
    else
    return false;
}

bool isIdentifier(string word)
{
    char x = word[0];
    if((x>='a'&&x<='z')||(x>='A'&&x<='Z'))
    {
        int i;
        for(i=1;i<word.size();i++)
        {
            x=word[i];
            bool t = (x>='0'&&x<='9')||(x>='a'&&x<='z')||(x>='A'&&x<='Z')||(x=='_');
            if(!t)
                return false;
        }
        return true;
    }
    else
    return false;
}

void tokenize(vector<string>inputCode){
    for(int i=0;i<inputCode.size();i++){

        if(inputCode[i][0]=='/' && inputCode[i][1]=='/'){
           cout<<"Token isComment"<<", line number "<<i+1<<endl;
           continue; 
        }

        istringstream ss(inputCode[i]);
        string word;
        while (ss >> word) 
        {
            //cout << word << "\n";
            //word=preProcess(word);
            if(isKeyword(word))
            cout<<"Token is a Keyword, string: "<<word<<" , line number: "<<i+1<<"\n";
            else if(isOperator(word))
            cout<<"Token is an Operator, string: "<<word<<" , line number: "<<i+1<<"\n";
            else if(isDelimiter(word))
            cout<<"Token is a Delimiter, string: "<<word<<" , line number: "<<i+1<<"\n";
            else if(isString(word))
            cout<<"Token is a String literal, string: "<<word<<" , line number: "<<i+1<<"\n";
            else if(isInteger(word))
            cout<<"Token is an Integer literal, string: "<<word<<" , line number: "<<i+1<<"\n";
            else if(isFloat(word))
            cout<<"Token is a Floating point literal, string: "<<word<<" , line number: "<<i+1<<"\n";
            else if(isIdentifier(word))
            cout<<"Token is an Identifier, string: "<<word<<" , line number: "<<i+1<<"\n";
            else
            cout<<"Invalid token, string: "<<word<<" at line number: "<<i+1<<"\n";
        }
    }
}

string preProcess(string line){

    if(line[0]=='/' && line[1]=='/'){
           //cout<<"Token isComment"<<", line number "<<i+1<<endl;
           return line; 
        }

    string newLine="";
    vector<char> spchar = {'!','%','^','&','*','(',')','-','+','+','{','[','}',']',':',';','/',',','<','>'};
    vector<string> binop = {"<=",">=","==","+=","-=","*=","/=","!=","&&","||",":=","++","--"};
    for(int i=0;i<line.size();i++) 
    {
        string bop = ""+line[i]+line[i+1];
        if(i>line.size()-1)
        cout<<bop<<" ";
        if(i>line.size()-1&&find(binop.begin(),binop.end(),bop)!=binop.end()){
            newLine=newLine+" "+line[i]+line[i+1]+" ";
            i++;
        }
        else if(find(spchar.begin(),spchar.end(),line[i])!=spchar.end())
        newLine=newLine+" "+line[i]+" ";
        else 
        newLine=newLine+line[i];
    }
    cout<<newLine<<"\n";
    return newLine;
}

int main(){
    //Name of input code file	
    string filename("test.txt");
    vector<string> inputCode;
    string line;

	//Check if file is already open
    ifstream input_file(filename);
    if (!input_file.is_open()) {
        cerr << "Could not open the file - '"
             << filename << "'" << endl;
        return EXIT_FAILURE;
    }
	
	//Insert each line in a vector
    while (getline(input_file, line)){
        line = regex_replace(line, regex("^ +"), "");
        line=preProcess(line);
        inputCode.push_back(line);
    }

    //Tokenize
    tokenize(inputCode);

	//Closing the input code file
    input_file.close();
    return EXIT_SUCCESS;
}