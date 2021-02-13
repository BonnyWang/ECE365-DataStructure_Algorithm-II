#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int matrix[1001][1001];

void execute();
bool checkMerge(string stringA, string stringB, string stringC);

int main(){
    
    execute();
    return 0;
}

void execute(){
    string inName;
    string outName;
    ifstream inFile;
    ofstream outFile;
    
    string line;
    int lineNumber;
    string stringA;
    string stringB;
    string stringC;

    lineNumber = 1;
    
    cout << "Please input the name of the input file:" << endl;
    cin >> inName;
    cout << "Plase input the name of the output file:" << endl;
    cin >> outName;

    inFile.open(inName);
    outFile.open(outName);

    while(getline(inFile, line)){
        if(lineNumber%3 == 1){
            stringA = line;
        }else if(lineNumber%3 == 2){
            stringB = line;
        }else{
            stringC = line;
            //Reach the third line, end of a set
            if(checkMerge(stringA,stringB, stringC)){
                // output the format
                int i = stringA.length();
                int j = stringB.length();

                while (i > 0 && j >= 0){
                    if (matrix[i][j] == true && (j == 0 || matrix[i][j-1] == 0)){
                        stringC[i+j-1] = toupper(stringC[i+j-1]);
                        i--;
                    }else{
                        j--;
                    }
                }

                outFile << stringC << endl;
                
            }else{
                outFile << "*** NOT A MERGE ***" << endl;
            }

        }
        lineNumber++;
    } 

    inFile.close();
    outFile.close(); 
}

bool checkMerge(string stringA, string stringB, string stringC){
    if((stringA.length() + stringB.length()) != stringC.length()){
        return false;
    }

    matrix[0][0] = 1;

    //Initialize matrix every time
    for(int i = 0; i <= stringA.length(); i++){
        for(int j = 0; j <= stringB.length(); j++){
            if(i == 0 && j == 0){
                continue;
            }
            matrix[i][j] = 0;
        }
    }

    for(int i = 0; i <= stringA.length(); i++){
        for(int j = 0; j <= stringB.length(); j++){
            if(i == 0 && j == 0 ){
                continue;
            }

            if(stringA[i-1] == stringC[i+j-1] && stringB[j-1] != stringC[i+j-1]){
                matrix[i][j] = matrix[i-1][j];
            }else if(stringB[j-1] == stringC[i+j-1] && stringA[i-1] != stringC[i+j-1]){
                matrix[i][j] = matrix[i][j-1];
            }else if(stringA[i-1] == stringC[i+j-1] && stringB[j-1] == stringC[i+j-1]){
                matrix[i][j] = matrix[i-1][j] || matrix[i][j-1];
            }
        }
    }
    return matrix[stringA.length()][stringB.length()];
}