#include <iostream>
#include <string>
#include <sstream>
using namespace std;

template <typename T>
struct QNode{
    T data;
    QNode<T> *next, *prev;
};

template <typename T>
struct Queue{
    QNode<T> *front = NULL, *back = NULL;
    int size = 0;
    
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
        size++;
    }

    T dequeue(){
        if(!(front == NULL)){
            T data = front -> data;
            if(front == back){
                delete front;
                front = back = NULL;
            }
            else{
                front = front -> next;
                delete front -> prev;
                front -> prev = NULL;
            }
            size--;
            return data;
        }
        else cerr << "Q kosong tidak dapat di dequeue";
        return "\0";
    }
    T dequeueBack(){
        if(!(front == NULL)){
            T data = back -> data;
            if(front == back){
                delete back;
                front = back = NULL;
            }
            else{
                back = back -> prev;
                delete back -> next;
                back -> next = NULL;
            }
            size--;
            return data;
        }
        else cerr << "Q kosong tidak dapat di dequeue";
        return "\0";
    }

    void print(){
        for(QNode<T> *p = front; p != NULL; p = p -> next){
            cout << p -> data;
            if(p != back) cout << " -- ";
        }
        cout << endl;
    }
};

void tokenize(string str, const char delim, Queue<string> &q){
    stringstream ss(str);
    string s;
    while (getline(ss, s, delim)) {
        q.enqueue(s);
    }
}

struct Node{
    int x,y;
    Node *left, *right, *top, *bot;
    string data;
};

struct Maze{
    Node *first = NULL, *last = NULL;
    int size;
    Node *start, *finish;
    void init(){
        Node *p, *q, *r;
        if(size == 1){
            first = last = new Node;
            first -> x = first -> y = 0;
            first -> top = first -> bot = first -> right = first -> left = NULL;
            return;
        }
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
        Queue<string> q, x, y;
        tokenize(path, ' ', q);
        int itt = 0;

        for(int i = q.size; i > 0 ; i--){
            tokenize(q.dequeue(), ',', x);
            y.enqueue(x.dequeueBack());
        }
        int xcoor = stoi(x.dequeue());
        int ycoor = stoi(y.dequeue());

    	for(Node *p = first; p != NULL; p = p -> bot){
    		for(Node *q = p; q != NULL; q = q -> right){
    			q -> data = "[XX]";
			}
		}
        while (true)
        {
            for(Node *p = first; p != NULL; p = p -> bot){
                for(Node *q = p; q != NULL; q = q -> right){
                    if((q -> x == xcoor) && (q -> y == ycoor)){
                        q -> data = "[OO]";
                        if(itt == 0) start = q;
                        if(!(x.back == NULL)){
                            xcoor = stoi(x.dequeue());
                            ycoor = stoi(y.dequeue());
                            break; break;
                        }
                        else {
                            finish = q;
                            return;
                        }
                        itt++;
                    }
                }
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

    void printCoor(){
		for(Node *p = first; p != NULL; p = p -> bot){
			for(Node *q = p; q != NULL; q = q -> right){
				cout << '[' << q -> x << ',' << p -> y <<']';
				// cout << q -> data;
			}
			cout << endl;
		}
	}
};

int main(){
	string path;
    Maze mazinga;
    
    cin >> mazinga.size;
    cin.ignore(256, '\n');
    getline(cin, path);
    
    mazinga.init();
    mazinga.pathInit(path);
    mazinga.print();
    mazinga.printCoor();
}
