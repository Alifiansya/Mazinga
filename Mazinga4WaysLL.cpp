#include <iostream>
#include <string>
using namespace std;

template <typename T>
struct QNode{
    T data;
    QNode<T> *next, *prev;
};

template <typename T>
struct Queue{
    QNode<T> *front, *back;
    void init(){
        front = back = NULL;
    }

    void enqueue(T data){
        QNode<T> *newNode = new QNode<T>;
        newNode -> next = NULL;
        if(front == NULL){
            front = back = newNode;
            newNode -> prev = NULL;
        }
        else{
            newNode -> prev = back;
            back = back -> next = newNode;
        }
        back -> data = data;
    }

    T dequeue(){
        if(!(front == NULL)){
            T data = front -> data;
            if(front == back){
                delete front;
                init();
            }
            else{
                front = front -> next;
                delete front -> prev;
            }
            return data;
        }
        else cerr << "Q kosong tidak dapat di dequeue";
    }
};

struct Node{
    int x,y;
    Node *left, *right, *top, *bot;
    string data;
};

struct Maze{
    Node *first = NULL, *last = NULL;
    int size;
    void init(){
        Node *p, *q, *r;
//        cout << size;
        for(int y = 0; y < size; y++){
            for(int x = 0; x < size; x++){
                if(x == 0){
                    p = new Node;
                    p ->left = p -> bot  = p -> top = p -> right = NULL;
                    if(first == NULL) {
                        q = r = first = p;
                    }
                    else{
                        p ->bot = q;
                        q -> top = p;
                    }
                    r = p;
                }
                else if(x == size -1){
                    p -> right = new Node;
                    p -> right -> left = p;
                    p = p -> right;
                    p -> right = p -> bot = p -> top = NULL;
                    if(y != 0){
                        p ->bot = q;
                        q -> top = p;
                    }
                    if(y == size -1) last = p;
                }
                else{
                    p -> right = new Node;
                    p -> right -> left = p;
                    p = p -> right;
                    p -> right = p -> top = p -> bot = NULL;
                    if(y != 0){
                        p -> bot = q;
                        q -> top = p;
                    }
                }
                p -> x = x;
                p -> y = y;
                if (y != 0) q = q -> right;
            }
            q = r;
        }
        for(first; first -> top != NULL; first = first -> top);
        for(last; last -> bot; last = last -> bot);
    }
    
    void pathInit(string path){
    	for(Node *p = first; p != NULL; p = p -> bot){
    		for(Node *q = p; q != NULL; q = q -> right){
    			q -> data = "[XX]";
			}
		}
	}
    
    void print(){
		for(Node *p = first; p != NULL; p = p -> bot){
			for(Node *q = p; q != NULL; q = q -> right){
//				cout << '[' << q -> x << ',' << p -> y <<']';
				cout << q -> data;
			}
			cout << endl;
		}
	}
};

int main(){
	// string path;
    // Maze mazinga;
    
    // cin >> mazinga.size;
    // cin.ignore(256, '\n');
    // getline(cin, path);
    
    // mazinga.init();
    // mazinga.pathInit(path);
    // mazinga.print();

    Queue<int> test;
    test.init();
    test.enqueue(1);
    test.enqueue(2);
    test.enqueue(3);
    for(int i = 0; i < 3; i++){
        cout << test.dequeue() << endl;
    }
}
