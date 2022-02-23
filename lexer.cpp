#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>


typedef long long int ll;

using namespace std;
//using std::cout; using std::cerr;
//using std::endl; using std::string;
//using std::ifstream; using std::vector;
//ofstream output_file;


map<string,int> token_id;
ll ctr=1000;
vector<char> spchar = {'!','%','^','&','*','(',')','-','+','+','{','[','}',']',':',';','/',',','<','>','='};
vector<string> binop = {"<<",">>","<=",">=","==","+=","-=","*=","/=","!=","&&","||",":=","++","--","//"};
vector<string> delimiter = {"{", "}", "(", ")", "[", "]", ";", ","};
vector<string> oprator = {"<<",">>","<", ">", "<=", ">=", "*", "+", "-", "/", "=", "-=", "*=", "+=", "/=", "++", "--", "=="};
vector<string> keywords = {"cout","cin","return","void","int","main", "float", "boolean", "string", "while", "until", "if" ,"else", "true", "false", "continue", "break"};

bool isKeyword(string word){
    if(find(keywords.begin(), keywords.end(), word) != keywords.end())
    {
        if(token_id.find(word)==token_id.end())
        {
            token_id[word]=ctr;
            ctr++;
        }
        return true;
    }
    else
    return false;
}

bool isOperator(string word){
    if(find(oprator.begin(), oprator.end(), word) != oprator.end())
    {
        if(token_id.find(word)==token_id.end())
        {
            token_id[word]=ctr;
            ctr++;
        }
        return true;
    }
    else
    return false;
}

bool isDelimiter(string word){
    if(find(delimiter.begin(), delimiter.end(), word) != delimiter.end())
    {
        if(token_id.find(word)==token_id.end())
        {
            token_id[word]=ctr;
            ctr++;
        }
        return true;
    }
    else
    return false;
}

bool isString(string word){
    if(word[0] == '"' && word[word.size()-1] == '"')
    {
        if(token_id.find(word)==token_id.end())
        {
            token_id[word]=ctr;
            ctr++;
        }
        return true;
    }
    else
    return false;
}

bool isInteger(string word){
    for(int i=0;i<word.size();i++){
        if(word[i]>='0'&&word[i]<='9')
        continue;
        return false;
    }
    word= regex_replace(word, regex("^0+"), "");
    if(word.size()==0)
    word+="0";
    //cout<<"Yess "<<word<<endl;
    if(token_id.find(word)==token_id.end())
    {
        token_id[word]=ctr;
        ctr++;
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

    word= regex_replace(word, regex("^0+"), "");
    reverse(word.begin(), word.end());
    word= regex_replace(word, regex("^0+"), "");
    reverse(word.begin(), word.end());
    if(word[0]=='.')
    word="0"+word;

    if(isInteger(beforeDecimal) && isInteger(afterDecimal))
    {
        if(token_id.find(word)==token_id.end())
        {
            token_id[word]=ctr;
            ctr++;
        }
        return true;
    }
    else
    return false;
}

bool isIdentifier(string word){
    char x = word[0];
    if(!isKeyword(word)&&(x>='a'&&x<='z')||(x>='A'&&x<='Z'))
    {
        int i;
        for(i=1;i<word.size();i++)
        {
            x=word[i];
            bool t = (x>='0'&&x<='9')||(x>='a'&&x<='z')||(x>='A'&&x<='Z')||(x=='_');
            if(!t)
                return false;
        }
        if(token_id.find(word)==token_id.end())
        {
            token_id[word]=ctr;
            ctr++;
        }
        return true;
    }
    else
    return false;
}

// void tokenize_string(string inputCode,int i,ofstream& output_file){
    
//     //ofstream output_file;
//     //output_file.open("outputstring.txt");
   
//     if(!output_file.is_open())
//     {
//         cerr << "Could not open the file here- 'output.txt'\n";
//         return;
//     }

//     if(inputCode[0]=='"'){
//         if(isString(inputCode))
//         output_file<<"String literal token, string: "<<inputCode<<" , line number: "<<i+1<<", token id: XXX"<<"\n";
//         else
//         output_file<<"Invalid token, string: "<<inputCode<<" at line number: "<<i+1<<"\n";
//         output_file.close();
//         return;
//     }
// }

void tokenize(string inputCode,int i,ofstream& output_file){
    bool isComment=false;

    //ofstream output_file;
    //output_file.open("output.txt");
  
    /*if(!output_file.is_open())
    {
        cerr << "Could not open the file - 'output.txt'\n";
        return;
    }*/

    if(inputCode[0]=='"'){
        if(isString(inputCode))
        output_file<<"String literal token, string: "<<inputCode<<" , line number: "<<i+1<<", token id: "<<token_id[inputCode]<<"\n";
        else
        output_file<<"Invalid token, string: "<<inputCode<<" at line number: "<<i+1<<"\n";
        return;
    }

        istringstream ss(inputCode);
        string word;
        while (ss >> word) 
        {
            //cout << word << "\n";
            //word=preProcess(word);
            
            if(isKeyword(word))
            output_file<<"Keyword token, string: "<<word<<" , line number: "<<i+1<<", token id: "<<token_id[word]<<"\n";
            else if(isOperator(word))
            output_file<<"Operator token, string: "<<word<<" , line number: "<<i+1<<", token id: "<<token_id[word]<<"\n";
            else if(isDelimiter(word))
            output_file<<"Delimiter token, string: "<<word<<" , line number: "<<i+1<<", token id: "<<token_id[word]<<"\n";
            else if(isString(word))
            output_file<<"String literal token, string: "<<word<<" , line number: "<<i+1<<", token id: "<<token_id[word]<<"\n";
            else if(isInteger(word)){
                word= regex_replace(word, regex("^0+"), "");
                if(word.size()==0)
                word+="0";
                output_file<<"Integer literal token, string: "<<word<<" , line number: "<<i+1<<", token id: "<<token_id[word]<<"\n";
            }
            else if(isFloat(word)){
                word= regex_replace(word, regex("^0+"), "");
                reverse(word.begin(), word.end());
                word= regex_replace(word, regex("^0+"), "");
                reverse(word.begin(), word.end());
                if(word[0]=='.')
                word="0"+word;
                output_file<<"Floating point literal token, string: "<<word<<" , line number: "<<i+1<<", token id: "<<token_id[word]<<"\n";
            }
            else if(isIdentifier(word))
            output_file<<"Identifier token, string: "<<word<<" , line number: "<<i+1<<", token id: "<<token_id[word]<<"\n";
            else
            output_file<<"Invalid token, string: "<<word<<" at line number: "<<i+1<<"\n";

        }
    cout<<inputCode<<"\n";

}

string preProcess(string line){

    if(line[0]=='/' && line[1]=='/'){
           //cout<<"Token isComment"<<", line number "<<i+1<<endl;
           return line; 
        }

    string newLine="";
    for(int i=0;i<line.size();i++) 
    {
    
    	if(line[i]=='"'){
            newLine+=line[i];
            int j=i+1;
            while(line[j]!='"' && j<line.size()){
                newLine+=line[j];
                j++;
            }
            if(j<line.size() && line[j]=='"')
            {newLine+='"';j++;}
            if(j>=line.size())
            return newLine;
            i=j;
        }
    	
        string bop="";
        if(i<line.size()-1){
            bop.push_back(line[i]);
            bop.push_back(line[i+1]);
        }
        
        if(find(binop.begin(),binop.end(),bop)!=binop.end()){
            newLine=newLine+" "+line[i]+line[i+1]+" ";
            i++;
        }
        else if(find(spchar.begin(),spchar.end(),line[i])!=spchar.end())
        newLine=newLine+" "+line[i]+" ";
        else 
        newLine=newLine+line[i];
    }
    //cout<<newLine<<"\n";
    return newLine;
}

void generate_symbol_table(vector<string> inputcode)
{
    ofstream symbolTable("symbol table.txt");
    if(!symbolTable.is_open())
    {
        cerr<<"Coud not generate symbol table\n";
        return;
    }
    int i;
    symbolTable<<"Keywords:\n";
    for(auto x : token_id)
    {
        if(isKeyword(x.first))
        symbolTable<<x.first<<" : "<<x.second<<"\n";
    }
    symbolTable<<"\n";
    symbolTable<<"Identifiers:\n";
    for(auto x : token_id)
    {
        if(isIdentifier(x.first))
        symbolTable<<x.first<<" : "<<x.second<<"\n";
    }
    symbolTable<<"\n";
    symbolTable<<"Operators:\n";
    for(auto x : token_id)
    {
        if(isOperator(x.first))
        symbolTable<<x.first<<" : "<<x.second<<"\n";
    }
    symbolTable<<"\n";
    symbolTable<<"Integer literals:\n";
    for(auto x : token_id)
    {
        if(isInteger(x.first))
        symbolTable<<x.first<<" : "<<x.second<<"\n";
    }
    symbolTable<<"\n";
    symbolTable<<"Float literals:\n";
    for(auto x : token_id)
    {
        if(isFloat(x.first))
        symbolTable<<x.first<<" : "<<x.second<<"\n";
    }
    symbolTable<<"\n";
    symbolTable<<"Delimiters:\n";
    for(auto x : token_id)
    {
        if(isDelimiter(x.first))
        symbolTable<<x.first<<" : "<<x.second<<"\n";
    }
    symbolTable<<"\n";
    symbolTable<<"String literals:\n";
    for(auto x : token_id)
    {
        if(isString(x.first))
        symbolTable<<x.first<<" : "<<x.second<<"\n";
    }
    symbolTable<<"\n";
    cout<<"Symbol table created successfully\n";
    symbolTable.close();
}

void initialize_token_map()
{
    int counter = 50,i;
    for(i=0;i<keywords.size();i++)
    {
        if(token_id.find(keywords[i])==token_id.end())
        {
            token_id[keywords[i]]=counter;
            counter++;
        }
    }
    for(i=0;i<spchar.size();i++)
    {
        if(token_id.find(spchar[i]+"")==token_id.end())
        {
            token_id[spchar[i]+""]=counter;
            counter++;
        }
    }
    for(i=0;i<binop.size();i++)
    {
        if(token_id.find(binop[i])==token_id.end())
        {
            token_id[binop[i]]=counter;
            counter++;
        }
    }
    for(i=0;i<delimiter.size();i++)
    {
        if(token_id.find(delimiter[i])==token_id.end())
        {
            token_id[delimiter[i]]=counter;
            counter++;
        }
    }
    for(i=0;i<oprator.size();i++)
    {
        if(token_id.find(oprator[i])==token_id.end())
        {
            token_id[oprator[i]]=counter;
            counter++;
        }
    }
}

int main(){

    //initialize token map
    initialize_token_map();

    //Name of input code file	
    string filename("input.txt");
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
    //tokenize(inputCode);
    ofstream cc;
    cc.open("output.txt");

    for(int i=0;i<inputCode.size();i++){
        int p=-1,q=-2;
        p = inputCode[i].find("\"");
        if(p==-1){
            tokenize(inputCode[i],i,cc);
            
            //cout<<inputCode[i]<<endl;
            continue;
        }
        reverse(inputCode[i].begin(), inputCode[i].end());
        q = (inputCode[i].size()-1)-(inputCode[i].find("\""));
        reverse(inputCode[i].begin(), inputCode[i].end());
        if(p==q && p>0){
            string sub1 = inputCode[i].substr(0,p);
            string sub2 = inputCode[i].substr(p);
            if(p>1)
            tokenize(sub1,i,cc);
            
            tokenize(sub2,i,cc);
            
        }
        else if(p!=q && p!=-1){
            string sub1 = inputCode[i].substr(0,p);
            string sub2 = inputCode[i].substr(p,q+1);
            string sub3 = inputCode[i].substr(q+1);
            //cout<<sub2<<endl;
            /*for(int j=sub2.size()-1;j>=0;j--){
                if(sub2[j]=='"')
                break;
                //cout<<sub2[j]<<endl;
                sub2[j]=' ';
            }
            reverse(sub2.begin(),sub2.end());
            sub2=regex_replace(sub2, regex("^ +"), "");
            reverse(sub2.begin(),sub2.end());*/
            //cout<<sub2<<endl;
            if(p>0)
            tokenize(sub1,i,cc);
            
            tokenize(sub2,i,cc);
            if(q<inputCode[i].size()-1)
            tokenize(sub3,i,cc);
        }
        
    }

    cout<<"Output file generated successfully\n";

    //Generate symbol table
    generate_symbol_table(inputCode);

    
	//Closing the input code file
    input_file.close();
    return EXIT_SUCCESS;
}