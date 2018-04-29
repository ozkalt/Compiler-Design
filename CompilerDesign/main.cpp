//
//  main.cpp
//  CompilerDesign
//
//  Created by Tuğba Özkal on 1.12.2017.
//  Copyright © 2017 Tuğba Özkal. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <set>
#include <stack>

#define INPUT_SIZE 50
#define LINE_SIZE 10

using namespace std;

class Gramer{
public:
    set<char> nonterminal;
    set<string> terminal;
    set<char> ignore;
    char input[LINE_SIZE][INPUT_SIZE];
    
    void read_from_user();
    void print();
private:
    void fill_ignore();
    void find_nonterminal(int);
    void find_terminal(int);
};

void Gramer::fill_ignore(){
    ignore.insert('-');
    ignore.insert('>');
    ignore.insert(' ');
    ignore.insert('\'');
    ignore.insert('\n');
    ignore.insert('\0');
    ignore.insert('0');     // for end
}

void Gramer::read_from_user(){
    fill_ignore();
    int counter = 0;
    cout << "Please enter the example (For ending enter 0)" << endl;
    for (counter = 0; counter < LINE_SIZE; counter++){
        cout << counter + 1 << ". ";
        cin.getline(input[counter], INPUT_SIZE);
        if (strcmp(input[counter], "0") == 0){
            break;
        }
    }
    
    find_nonterminal(counter);
    find_terminal(counter);
    print();
}

void Gramer::find_nonterminal(int counter){
    for (int i = 0; i < counter; i++){
        for (int j = 0; j < INPUT_SIZE; j++){
            if (!ignore.count(input[i][j])){
                nonterminal.insert(input[i][j]);
            }
            if (input[i][j] == '-' && input[i][j+1] == '>'){
                break;
            }
        }
    }
}

void Gramer::find_terminal(int counter){
    //default value of terminal is inserted here
    terminal.insert("$");
    
    for (int i = 0; i < counter; i++){
        for (int j = 0; input[i][j] != '\0'; j++){
            if (!ignore.count(input[i][j]) && !nonterminal.count(input[i][j])){
                char buf[INPUT_SIZE];
                int k = 0;
                buf[k++] = input[i][j];
                if (isalpha(input[i][j])){
                    for (int x = j + k; x < INPUT_SIZE; x++){
                        if (!ignore.count(input[i][x]) && !nonterminal.count(input[i][x]) && isalpha(input[i][x]) ){
                            buf[k++] = input[i][x];
                        }
                        else{
                            buf[k] = '\0';
                            terminal.insert(buf);
                            j = x - 1;
                            break;
                        }
                    }
                }
                else{
                    buf[k] = '\0';
                    terminal.insert(buf);
                }
            }
        }
    }
}

void Gramer::print(){
    cout << endl << "Nonterminal" << endl;
    set<char>::iterator y;
    for (y = nonterminal.begin(); y != nonterminal.end(); y++){
        cout << *y << endl;
    }
    cout << endl << "Terminal" << endl;
    set<string>::iterator x;
    for (x = terminal.begin(); x != terminal.end(); x++){
        cout << *x << endl;
    }
}

int main(int argc, const char * argv[]) {
    Gramer k;
    k.read_from_user();
    return 0;
}
