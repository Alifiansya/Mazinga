#include <iostream>
#include <sstream>
#include "DoublyLinkedList.cpp"
#include "StackList.cpp"
using namespace std;

string maze[100][100];
int maze_size;
int startX;
int startY;

int finishX;
int finishY;

Stack mundurX, mundurY;
DoublyLinkedList move_list;	

int ctoi(char c){
	return c - '0';
}

void path(int x[], int y[], string jalur){
	int x_index = 0, y_index = 0;
	for(int i = 0; i < jalur.length(); i++){
		if(i == jalur.length()-1) y[y_index] = ctoi(jalur[i]);
		else if(i == 0) x[x_index++] = ctoi(jalur[i]);
		else{
			if(jalur[i-1] == ',') y[y_index++] = ctoi(jalur[i]);
			else if(jalur[i+1] == ',') x[x_index++] = ctoi(jalur[i]);
			else continue;
		}
	}
}

void tokenize(string str, const char delim, DoublyLinkedList &list){
    stringstream ss(str);
    string s;
    while (getline(ss, s, delim)) {
        list.add_last(s);
    }
}

void maze_init(int maze_size, int x[], int y[], int jalur_size){
	for(int i = 0; i < maze_size; i++){
		for(int j = 0; j < maze_size; j++){
			maze[i][j] = "[XX]";
		}
	}
	
	for(int i = 0; i < jalur_size; i++){
		if(maze[x[i]][y[i]] != "[XX]") continue;
		else maze[x[i]][y[i]] = "[OO]";
	}
}

void maze_print(){
	for(int i = maze_size-1; i >= 0  ; i--){
		for(int j = 0; j < maze_size; j++){
			cout << maze[j][i];
		}
		cout << endl;
	}
}

void move(ListNode *p, int x, int y, int steps){
	// cout << x << y;
	if(p == NULL) cout << " LOL";
	cout << p -> val;
	cout << steps << endl;
	maze_print();
	cout << endl;

	if(x == finishX && y == finishY){
		if(steps < 9) maze[x][y] = "[0" + to_string(++steps) + "]";
		return;
	}

	if(p == NULL){
		cout << 2;
		cout << "tes";
		p = move_list.head;
		if (maze[x][y] == "[OO]"){
			if(steps < 9) maze[x][y] = "[0" + to_string(++steps) + "]";
		}
		
		move(p, mundurX.pop(), mundurY.pop(), steps);
	}

	else if(p -> val == "UP"){
		if(y+1 < maze_size && maze[x][y+1] == "[OO]"){
			if(steps < 9) maze[x][y] = "[0" + to_string(++steps) + "]";
			// cout << maze[x][y];
			mundurX.push(x);
			mundurY.push(y);		
			p = move_list.head;	
			move(p, x, ++y, steps);

		}
		else move(p -> next, x, y, steps);
	}
	else if(p -> val == "DOWN"){
		if(y-1 >= 0 && maze[x][y-1] == "[OO]"){
			if(steps < 9) maze[x][y] = "[0" + to_string(++steps) + "]";
			// cout << maze[x][y];
			mundurX.push(x);
			mundurY.push(y);
			p = move_list.head;
			move(p, x, --y, steps);
		}
		else move(p -> next, x, y, steps);
	}
	else if(p -> val == "LEFT"){
		if(x-1 >= 0 && maze[x-1][y] == "[OO]"){
			if(steps < 9) maze[x][y] = "[0" + to_string(++steps) + "]";
			// cout << maze[x][y];
			mundurX.push(x);
			mundurY.push(y);
			p = move_list.head;
			move(p, --x, y, steps);
		}
		else move(p -> next, x, y, steps);
	}
	else if(p -> val == "RIGHT"){
		if(x+1 < maze_size && maze[x+1][y] == "[OO]"){
			if(steps < 9) maze[x][y] = "[0" + to_string(++steps) + "]";
			// cout << maze[x][y];
			mundurX.push(x);
			mundurY.push(y);
			p = move_list.head;
			move(p, ++x, y, steps);
		}
		else move(p -> next, x, y, steps);
	}
	cout << 20;
}


int main(){
	//input
	int peserta;
	string jalur, gerak;
	

	cin >> maze_size;
	getline(cin >> ws, jalur);

    int jalur_size = jalur.length()/4 + 1;
    int x[jalur_size];
	int y[jalur_size];
    path(x, y, jalur);

	startX = x[0];
	startY = y[0];

	finishX = x[jalur_size-1];
	finishY = y[jalur_size-1];
	maze_init(maze_size, x, y, jalur_size);	

	getline(cin >> ws, gerak);
	tokenize(gerak, ' ', move_list);
	string nama = move_list.head->val;
	move_list.remove_first();

	ListNode *p = move_list.head;
	move(p, startX, startY, 0);

	maze_print();
}
