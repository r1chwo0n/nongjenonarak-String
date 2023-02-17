#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string> &name, vector<int> &score, vector<char> &grade){
    ifstream source (filename);
    string textline;
    while(getline(source,textline)){
        const char * cStr = textline.c_str();
        char format[] = "%[^:]: %d %d %d";
        char n[100];
        int a, b , c;
        sscanf(cStr,format,n,&a,&b,&c);
        name.push_back(n);
        int sum = a+b+c;
        score.push_back(sum);
        grade.push_back(score2grade(sum));
    }
}

void getCommand(string &command,string &key){
    string ans;
    cout << "Please input your command: ";
    getline(cin,ans);
    int idx = ans.find_first_of(" ");
    command = ans.substr(0,idx);
    key = ans.substr(idx+1,ans.size()-idx-1);
}

void searchName(vector<string> &name, vector<int> &score, vector<char> &grade, string &key){
    cout << "---------------------------------" << endl;
    bool have = false;
    for (unsigned int i = 0; i < name.size();i++){
        if (toUpperStr(key) == toUpperStr(name[i])){
            cout << name[i] << "'s " << "score = " << score[i] << endl;
            cout << name[i] << "'s " << "grade = " << grade[i] << endl;
            have = true;
        }
    }
    if (have == false) cout << "Cannot found." << endl;
    cout << "---------------------------------" << endl;
}

void searchGrade(vector<string> name, vector<int> score, vector<char> grade, string key){
    cout << "---------------------------------" << endl;
    bool have = false;
    for (unsigned int i = 0; i < name.size();i++){
        if (key[0] == grade[i]){
            cout << name[i] << " (" << score[i] << ")" << endl;
            have = true;
        }
    }
    if (have == false) cout << "Cannot found." << endl;
    cout << "---------------------------------" << endl;
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}