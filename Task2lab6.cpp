#include <iostream>
using namespace std;
#include <cstdlib>
#include <ctime>
#include <string>


class NumStack {
    double arr[50];
    int top;
public:
    NumStack() {top =-1;}

    void push(double val) {
        if(top<49) arr[++top]=val;
    }
    double pop() {
        if (top>=0) return arr[top--];
        return 0; // safety
    }
    bool isEmpty(){ return top==-1; }
};


class Transaction{
    int ID;
    int amount;
    string description;
    bool flag;

    int precedence(char op){
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        return 0;
    }

    string infixToPostfix(const string &expr){
        char opStack[50];
        int top = -1;
        string postfix = "";

        for (size_t i = 0; i < expr.size(); i++){
            char c = expr[i];
            if (isdigit(c) || c =='.'){
                postfix += c;} 
            else if (c ==' '){
                postfix +=' '; } 
            else if (c =='('){
                opStack[++top] = c;} 
            else if (c ==')'){
                postfix += ' ';
                while (top >= 0 && opStack[top] != '(') {
                    postfix += opStack[top--];
                    postfix += ' ';
                }
                top--;
            }
            else if(c == '+' || c == '-' || c == '*' || c == '/'){
                postfix += ' ';
                while (top >= 0 && precedence(opStack[top]) >= precedence(c)) {
                    postfix += opStack[top--];
                    postfix += ' ';
                }
                opStack[++top] = c;
            }
        }

        while(top>=0){
            postfix+= ' ';
            postfix+=opStack[top--];
        }
        return postfix;
    }

    double evalPostfix(const string &postfix){
        NumStack st;
        string token = "";

        for(char c : postfix){
            if(isdigit(c) || c == '.'){
                token += c;} 
            else if(c == ' '){
                if(!token.empty()){
                    st.push(stod(token));
                    token.clear();
                }
            } 
            else if(c == '+' || c == '-' || c == '*' || c == '/'){
                double b = st.pop();
                double a = st.pop();
                double res = 0;
                if (c == '+') res = a + b;
                else if (c == '-') res = a - b;
                else if (c == '*') res = a * b;
                else if (c == '/') res = a / b;
                st.push(res);
            }
        }

        if (!token.empty()) st.push(stod(token));
        return st.pop();
    }
    
    public:
    Transaction(int a, string d){
        ID = 0;
        amount =a;
        description = d;
        if(amount >=0) flag=1;
        else flag=0;
    }
    void setID(int ID){
        this->ID = ID;
    }
    void checkDescription(){
        if(description.length()>20){
            description = description.substr(0, 17) + "...";
        }
    }

    void applyDiscount(){
        if(!flag) return;
        
        if(amount>=1500){
            amount*=0.7;
        }
        else if(amount>=1000){
            amount *=0.85;
        }
        else if(amount>=500){
            amount *=0.95;
        }
    }

    int getAmount(){
        return amount;
    }
    void setAmount(int a){
        amount =a;
    }
    void reverse(){
        if(flag) return;
        flag= true;
        amount *=-1;
        description = description + "[REVERSED]";
    }

    void display(){
        cout<<"ID: "<<ID<<endl;
        cout<<"Amount: "<< amount <<endl;
        cout<<"Description:  "<<description<<endl;
        cout<<"Flag: "<<flag<<endl; 
        
    }
};


class Node{
    public:
    Node* next;
    Transaction *data;
    Node(Transaction *t){
        data = t;
        next = nullptr;
    }
    ~Node(){
        delete data;
    }

};
class Stack{
    static int AllID;

    Node* head;
    Node* tail;

    public:
    Stack(){
        head= tail = nullptr;
    }
    ~Stack(){
        Node*temp = head, *temp2;
        while(temp){
            temp2 = temp->next;
            delete temp;
            temp = temp2;
        }
    }

    void push(Transaction *t){
        t->setID(AllID++);
        t->checkDescription();
        t->applyDiscount();
        Node* newnode = new Node(t);
        if(isEmpty()){
            head = tail = newnode;
        }
        else{
            newnode->next = head;
            head = newnode;
        } 
    }
    void pop(){
        if(isEmpty()) return;
        Node *temp = head;
        head = head->next;
        temp->data->reverse();
        delete temp;
    }
    Transaction* seektop(){
        return head->data;
    }
    void display(){
        Node* temp = head;
        while(temp){
            temp->data->display();
            cout<<endl;
            temp = temp->next;
        }
        cout<<endl;
    }

    bool isEmpty(){
        return head==nullptr;
    }
};
int Stack:: AllID = 1;

int main(){
    int itemPushed[4] = {0};
    srand(time(0));
    int numItemsPushed=0;
    int randomIndex;

    Transaction **Items = new Transaction*[4];
    Items[0] = new Transaction(1200, "Sale: Blue Jacket");
    Items[1] = new Transaction(450, "Sale: Cotton Socks");
    Items[2] = new Transaction(-300, "Refund: Defective Shirt");
    Items[3] = new Transaction(1700, "Sale: Leather Jacket");

    Stack store;
    while(numItemsPushed<4){
        randomIndex = rand() % 4;
        if(itemPushed[randomIndex]==0){
            itemPushed[randomIndex]=1;
            store.push(Items[randomIndex]);
            numItemsPushed++;
        }
    }

    store.display();

    for(int i=0;i<4;i++) delete Items[i];
    delete[] Items;

    return 0;
}
