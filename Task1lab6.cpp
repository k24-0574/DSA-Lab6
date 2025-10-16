#include <iostream>
using namespace std;

class Stack{
    int size;
    char *arr;
    int top;

    public:
    Stack(int size){
        this->size = size;
        arr = new char[size];
        top = -1;
    }
    ~Stack(){
        delete[] arr;
    }
    void push(char ch){
        if(isFull()) return;
        arr[++top] = ch;
    }
    void pop(){
        top--;
    }
    char seektop(){
        return arr[top];
    }

    bool isFull(){
        return top+1==size;
    }
    bool isEmpty(){
        return top==-1;
    }
};


int main(){
    string word = "BORROWROB";
    int length = word.length();
    Stack sword(length);
    for(int i=0;i<length;i++){
        sword.push(word[i]);
    }

    bool isPalimdrome = true;
    int i=0;
    while(!sword.isEmpty()){
        if(word[i++] != sword.seektop()){
            isPalimdrome = false;
            break;
        }
        sword.pop();
    }

    if(isPalimdrome) cout<<"String is Palindrome";
    else cout<<"String is not Palindrome";
    
    return 0;
}