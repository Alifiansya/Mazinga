#include <iostream>
using namespace std;

struct ListNode{
	string val;
	ListNode *next;
	ListNode *prev;
};

struct DoublyLinkedList{
	ListNode *head = NULL, *tail = NULL;
	
	bool is_empty(){
		return head == NULL;
	}
	
	//SIZE
	int get_size(){
		int size = 0;
		for(ListNode *p = head; p != NULL; p = p -> next){
			size++;
		}
		return size;
	}
	
	//ADDING
	void add_first(string val){
		if(is_empty()){
			head = tail = new ListNode;
			head -> val = val;
			head -> next = head -> prev = NULL;
		}
		else{
			ListNode *tmp = new ListNode;
			tmp -> next = head;
			tmp -> prev = NULL;
			tmp -> val = val;
			head -> prev = tmp;
			head = tmp;
			tmp = NULL; 
		}
	}
	
	void add_last(string val){
		if(is_empty()){
			head = tail = new ListNode;
			head -> val = val;
			head -> next = head -> prev = NULL;
		}
		else{
			tail -> next = new ListNode;
			tail -> next -> next = NULL;
			tail -> next -> prev = tail;
			tail -> next -> val = val;
			tail = tail -> next;
		}
	}
	
	//REMOVE
	void remove_first(){
		if(is_empty()){
			return;
		}
		else if(head == tail){
			delete head;
			head = tail = NULL;
		}
		else{
			head = head -> next;
			delete head -> prev;
			head -> prev = NULL;
		}
	}
	
	void remove_last(){
		if(is_empty()){
			return;
		}
		else if(head == tail){
			delete tail;
			head = tail = NULL;
		}
		else{
			tail = tail -> prev;
			delete tail -> next;
			tail -> next = NULL;
		}
	}
	
	void print_to_last(){
		if(is_empty()){
			return;
		}
		for(ListNode *p = head; p != NULL; p = p -> next){
			if(p == tail){
				cout << p -> val << endl;
			}
			else{
				cout << p -> val << " <--> ";
			}
		}
	}
	
	void print_to_first(){
		if(is_empty()){
			return;
		}
		for(ListNode *p = tail; p != NULL; p = p -> prev){
			if(p == head){
				cout << p -> val << endl;
			}
			else{
				cout << p -> val << " <--> ";
			}
		}
	}
	
	void make_empty(){
		for(ListNode *i = head; i != NULL; i = head){
			head = head -> next;
			delete i;
		}
		head = tail = NULL;
	}
	
	void insert(int index, string data){
		ListNode *p;
		if(index < 0){
			for(p = tail; p != NULL; p = p -> prev){
				if(index == -1) break;
				index++;
			}
			if(p==head) add_first(data);
			else if(p == tail) add_last(data);
			else{
				ListNode *tmp = new ListNode;
				tmp -> val = data;
				tmp -> next = p -> next;
				tmp -> prev = p;  
				p -> next -> prev = tmp;
				p -> next = tmp;
			}
		}
		else{
			int i = 0;
			for(p = head; p != NULL; p = p -> next){
				if(i == index) break;
				i++;
			}
			if(p==head) add_first(data);
			else if(p == tail) add_last(data);
			else{
				ListNode *tmp = new ListNode;
				tmp -> val = data;
				tmp -> next = p;
				tmp -> prev = p -> prev;  
				p -> prev -> next = tmp;
				p -> prev = tmp;
			}
		}
	}
	void remove(int index){
		ListNode *p;
		if(index < 0){
			for(p = tail; p != NULL; p = p -> prev){
				if(index == -1) break;
				index++;
			}
			if(p==head) remove_first();
			else if(p == tail) remove_last();
			else{
				p -> prev -> next = p -> next;
				p -> next -> prev = p -> prev;
				delete p;
			}
		}
		else{
			int i = 0;
			for(p = head; p != NULL; p -> next){
				if(i == index) break;
				i++;
			}
			if(p==head) remove_first();
			else if(p == tail) remove_last();
			else{
				p -> prev -> next = p -> next;
				p -> next -> prev = p -> prev;
				delete p;
			}
		}
	}
 
	void print(){
		ListNode *p = head;
		while(p != NULL){
			cout << p -> val << " -- ";
			p = p -> next;
		}
		cout << endl;
	}
};

