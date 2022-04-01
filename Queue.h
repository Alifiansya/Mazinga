#include <iostream>
using namespace std;

struct QNode{
	int steps;
	string nama;
	string maze;
	QNode *next, *prev;
};

struct Queue{
	QNode *front = NULL, *rear = NULL;
	int size = 0;

	
	bool is_empty(){
		return front == NULL;
	}
	
	void enqueue(int steps, string nama, string maze){
		if(is_empty()){
			front = rear = new QNode;
			front -> next = front -> prev = NULL;
			front -> steps = steps;
			front -> maze = maze;
			front -> nama = nama;
		}
		else{
			rear -> next = new QNode;
			rear -> next -> next = NULL;
			rear -> next -> prev = rear;
			rear -> next -> steps = steps;
			rear -> next -> maze = maze;
			rear -> next -> nama = nama;			
			rear = rear -> next; 
		}
		size++;
	}
	
	void dequeue(){
		if(is_empty()) throw "List kosong, tidak dapat didequeue";
		else{
			if(front == rear){
				delete front;
				front = rear = NULL;
			}
			else{
				front = front -> next;
				delete front -> prev;
				front -> prev = NULL;
			}
			size--;
		}
	}
	
	void make_empty(){
		for(int i = 0; i < size; i++) dequeue();
	}

	int steps_tmp;
	string maze_tmp, nama_tmp;

	void sort(){
		if(!is_empty()){
			for(QNode *i = front; i != NULL; i = i -> next){
				for(QNode *j = i -> next; j != NULL; j = j -> next){
					if(j -> steps < i -> steps){
						steps_tmp = j -> steps;
						j -> steps = i -> steps;
						i -> steps = steps_tmp;
						maze_tmp = j -> maze;
						j -> maze = i -> maze;
						i -> maze = maze_tmp;
						nama_tmp = j -> nama;
						j -> nama = i -> nama;
						i -> nama = nama_tmp;
					}
				}
			}
		}
	}
};
