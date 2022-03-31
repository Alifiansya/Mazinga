#include <iostream>
#include <string>
using namespace std;
 
struct Node{
    int data;
    Node *next, *prev;
};
 
struct Stack{
    Node *top = NULL, *bottom = NULL;
    
    bool is_empty() {
        return top == NULL;
    }
    
    void push(int data){
        if(is_empty()){
            top = bottom = new Node;
            top -> next = top -> prev = NULL;
        }
        else{
            top -> next = new Node;
            top -> next -> prev = top;
            top -> next -> next = NULL;
            top = top -> next;
        }
        top -> data = data;
    }
    
    int pop(){
        if(is_empty()) throw "Tidak Valid";
        else{
            int data = top -> data;
            if(top == bottom){
                delete top;
                top = bottom = NULL;
            }
            else{
                top = top -> prev;
                delete top -> next;
                top -> next = NULL;
            }
            return data;
        }
    }

    void clear(){
        while(!is_empty()) pop();
    }
};
