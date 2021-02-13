#include <iostream>
#include "hash.h"
#include <string>
#include <fstream>
#include <ctime>

#define SIZE 50000

using namespace std;

int main(){

    string in_Name, out_Name;
    string dict_Name;
    string line;
    string word;
    clock_t start, end;
    ifstream dict, inFile;
    ofstream outFile;
    int lineNo;
    char c;
    bool ignore;

    lineNo = 0;
    word = "";

    hashTable *dict_Hash = new hashTable(SIZE);
    
    cout<< "Enter name of dictionary: ";
    cin >> dict_Name;

    //Load dictionary to the hashtable
    start = clock();
    dict.open(dict_Name);

    while(!dict.eof()){
        getline(dict, line);
        for( int i = 0  ; i < line.length(); i++){
            line[i] = tolower(line[i]);
        }
        dict_Hash->insert(line);
    }
    dict.close();
    end = clock();
    cout << "Total time (in seconds) to load dictionary: " << double(end - start)/CLOCKS_PER_SEC << endl;

    cout << "Enter the name of input file: ";
    cin >> in_Name;
    cout << "Enter the name of output file: ";
    cin >> out_Name;

    //Spell check the input file
    start = clock();
    inFile.open(in_Name);
    outFile.open(out_Name);
    while(!inFile.eof()){
        getline(inFile, line);
        lineNo++;
        for(int i = 0; i <= line.length(); i++){
            // <= to leave one more space for the word at the end of each line
            c = tolower(line[i]);
            if(isalnum(c) || c == '-'||c == '\''){
                if(isdigit(c)){
                    ignore = true;
                }
                word += c;
            }else if(word.length() > 0 && ignore == false){
                if(word.length() > 20){
                    outFile << "Long word at line " << lineNo << ", starts: " << word.substr(0,20) << endl;
                }else if(!dict_Hash->contains(word)){
                    outFile << "Unknown word at line "<< lineNo << ": "<< word << endl;
                }
                
                //valid word
                word = "";
            }else{
                //check next word
                word = "";
                ignore = false;
            }
        }

    }

    inFile.close();
    outFile.close();
    end = clock();
    cout << "Total time (in seconds) to check document: " <<  double(end - start) / CLOCKS_PER_SEC << endl;

    return 0;
}