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
        if(word[i]=='0' || word[i]=='1' || word[i]=='2' || word[i]=='3' || word[i]=='4' || word[i]=='5' || word[i]=='6' || word[i]=='7' || word[i]=='8' || word[i]=='9')
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
            cout<<"Token isKeyword, string "<<word<<", line number "<<i+1<<endl;
            else if(isOperator(word))
            cout<<"Token isOperator, string "<<word<<", line number "<<i+1<<endl;
            else if(isDelimiter(word))
            cout<<"Token isDelimiter, string "<<word<<", line number "<<i+1<<endl;
            else if(isString(word))
            cout<<"Token isString, string "<<word<<", line number "<<i+1<<endl;
            else if(isInteger(word))
            cout<<"Token isInteger, string "<<word<<", line number "<<i+1<<endl;
            else if(isFloat(word))
            cout<<"Token isFloat, string "<<word<<", line number "<<i+1<<endl;
            else
            cout<<"Token isIdentifier, string "<<word<<", line number "<<i+1<<endl;
        }
    }
}

string preProcess(string line){

    if(line[0]=='/' && line[1]=='/'){
           //cout<<"Token isComment"<<", line number "<<i+1<<endl;
           return line; 
        }

    string newLine="";
    for(int i=0;i<line.length();i++) 
    {
        if((line[i]=='!'&&line[i+1]== '=')||(line[i]=='<'&&line[i+1]=='=')||(line[i]=='>'&&line[i+1]=='=')||(line[i]=='='&&line[i+1]=='=')||(line[i]=='&'&&line[i+1]=='&')||(line[i]=='|'&&line[i+1]=='|')){
            newLine=newLine+" "+line[i]+line[i+1]+" ";
            i++;
        }
        else if(line[i]=='=' || line[i]=='?' || line[i]=='&' || line[i]=='%' || line[i]=='^' || line[i]=='!' || line[i]=='>' || line[i]=='<' || line[i]=='+' || line[i]=='-' || line[i]=='*' || line[i]=='/' || line[i]==';' || line[i]=='(' || line[i]==')' || line[i]=='{' || line[i]=='}' || line[i]=='[' || line[i]==']') 
        newLine=newLine+" "+line[i]+" ";
        else 
        newLine=newLine+line[i];
    }
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