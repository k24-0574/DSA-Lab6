/*
Task 3: As a software developer, you have been assigned the task of developing an application for a busy restaurant that can handle a large volume of orders. To ensure that orders are processed in the order they were received, what type of data structure would you choose to store the orders?
ANS: queues using linked lists

Please describe the necessary operations that would be required to add and remove orders from this data structure, including the quantity of each item. 
ANS: each node would have object of "order" which would have array of item name and quantities. to add Order, nodes would be inserted from rear and to remove they would be removed from front

Additionally, how would you prevent the data structure from becoming full or empty to avoid overflow or underflow?
ANS: isEmpty function would return weather front node is pointing to null or not. if there if limited capacity, a "isFull" function will be used

Finally, explain your approach for printing out all the processed orders in the order they were received to ensure that the restaurant staff can efficiently fulfill the orders.
ANS: Once printed the orders can be added to a new Queue and dequeued from the original so that pending orders can be dealt with.
*/
#include <iostream>
using namespace std;

class Order{
    int numItems;
    string *itemName;
    int *amount;
    public:
    Order(int numItems, string items[], int amounts[]){
        this->numItems = numItems;
        itemName = new string[numItems];
        amount = new int[numItems];

        for(int i =0;i<numItems;i++){
            amount[i] = amounts[i];
            itemName[i] = items[i];
        }
    }
    ~Order(){
        delete[] itemName;
        delete[] amount;
    }
};

class Node{
    public:
    Node*next;
    Order* data;
    Node(Order* o){
        data = o;
        next = nullptr;
    }
};

class Queue{
    Node* front, *rear;
    int curr, cap;
    public:
    Queue(int cap){
        front = rear = nullptr;
        this->cap = cap;
        curr=0;
    }

    void enqueue(Order* o){
        if(isFull) return;
        Node* newnode = new Node(o);
        if(front == nullptr){
            front = rear = newnode;
        }
        else{
            //add order to rear
            rear->next = newnode;
            rear = newnode;
        }
        curr++;
    }

    void dequeue(){
        if(isEmpty()) return;
        //remove order from front
        Node* temp = front;
        front = front->next;
        delete temp;
        curr--;
    }

    bool isEmpty(){
        return front==nullptr;
    }

    bool isFull(){
        return curr = cap;
    }
};

int main(){
    return 0;
}   
