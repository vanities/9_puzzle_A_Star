/*=======================================================================================

Programmer: Adam Mischke
Date: Sep 18, 2017
Class: 
	CSCI 4350 Open Lab 1
	Solving Problems By Search
Description:
	This shuffles the board by moving the 0 in a random direction (number argv[2]) by using a 
	random seed (number argv[1])
	s m:
		s set a random seed
		m sets a random number of moves


=======================================================================================*/

#include <iostream> // cout
#include <vector>	// vector
#include <fstream> 	// ifstream, ofstream
#include <string>	// string
#include <stdlib.h>	// srand, rand
#include <cstdlib>	// atoi


#define ROW 3
#define COLUMN 3
	
using namespace std;

struct Node
{
	int x;
	int y;
};

void print_board(vector< vector<int> >);
void move(vector< vector<int> > );
void fs_to_vector(ifstream&, vector< vector<int> >&);
void vector_to_fs(ofstream&, vector< vector<int> >&);
void cin_to_vector(vector< vector<int> >& v);
void find_zero(vector< vector<int> >, Node&);
void move_zero(vector< vector<int> >&, Node&);
bool move_left(vector< vector<int> >&, Node&);
bool move_right(vector< vector<int> >&, Node&);
bool move_up(vector< vector<int> >&, Node&);
bool move_down(vector< vector<int> >&, Node&);


int main(int argc, char ** argv){
	
/*	*ifstream*
	ifstream in;
	string file = "OLA1-input.txt";

	in.open(file);

	if(!in){
		return EXIT_FAILURE;
	}
*/


	vector< vector<int> > v(COLUMN, vector<int>(ROW, 0));

	cin_to_vector(v);
	//fs_to_vector(in,v);
	//print_board(v);

	Node zero = {0,0};
	find_zero(v, zero);

	int moves=atoi(argv[2]);
	srand(atoi(argv[1]));
	//moves = 1000;
	for(int i=0; i<moves; i++){

		move_zero(v,zero);
		//print_board(v);
		find_zero(v,zero);


	}
	/* *ostream*
	ofstream out;
	string file = "OLA1-input2.txt";
	out.open(file);
	vector_to_fs(out,v);
	*/

	print_board(v);

	return EXIT_SUCCESS;
}

void fs_to_vector(ifstream& in, vector< vector<int> >& v){

	Node zero;
	(COLUMN, vector<int>(ROW, 0));

	int num = 0;
	while(!in.eof()){
		for(int i=0; i<COLUMN; i++){
			for(int j=0; j<ROW; j++){
				in >> v[i][j];
			}	
		}
	}

		in.close();
	return;
}

void cin_to_vector(vector< vector<int> >& v){

	for(int i=0; i<COLUMN; i++){
		for(int j=0; j<ROW; j++){
			cin >> v[i][j];
		}	
	}
	return;
}


void print_board(vector< vector<int> > v){
	for(int i=0; i<COLUMN; i++){
		for(int j=0; j<ROW; j++){
			cout << v[i][j] << " ";
		}cout << "\n";
	}
	return;
}


void find_zero(vector< vector<int> > v, Node& zero){

	for(int i=0; i<COLUMN; i++){
		for(int j=0; j<ROW; j++){
			// find zero
			if (zero.y == i && zero.x == j){
				zero.y=i;
				zero.x=j;
				//cout << "the zero is here: [" << zero.x << "," << zero.y << "]"<< "\n";

				return;
			}
		}
	}
}

void move_zero(vector< vector<int> >& v, Node& z){

	bool moved=0;
	string way;
	while(!moved){
		int random = rand() % 4;
		//cout << "random number: " << random << "\n";
	
		switch(random){
			case 0: 
				way = "left";
				moved = move_left(v,z);
				break;
			case 1: 
				way = "up";
				moved = move_up(v,z);
				break;
			case 2: 
				way = "down";
				moved = move_down(v,z);
				break;
			case 3: 
				way = "right";
				moved = move_right(v,z);
				break;
		}
		/*
		if(moved)
			cout << "moved " << way << "\n";
		else
			cout << "can't move " << way << "\n";
			*/

	}
	return;

}

bool move_left(vector< vector<int> >& v, Node& z){
	if(z.x == 0)
		return false;
	else{
		int temp = v[z.y][z.x-1];
		v[z.y][z.x-1] = 0;
		v[z.y][z.x] = temp;
		z.x = z.x-1;

		return true;
	}
}

bool move_right(vector< vector<int> >& v, Node& z){
	if(z.x == COLUMN-1)
		return false;
	else{
		int temp = v[z.y][z.x+1];
		v[z.y][z.x+1] = 0;
		v[z.y][z.x] = temp;
		z.x = z.x+1;

		return true;
	}
}

bool move_up(vector< vector<int> >& v, Node& z){
	if(z.y == 0)
		return false;
	else{
		int temp = v[z.y-1][z.x];
		v[z.y-1][z.x] = 0;
		v[z.y][z.x] = temp;
		z.y = z.y-1;

		return true;
	}
}

bool move_down(vector< vector<int> >& v, Node& z){

	if(z.y == ROW-1)
		return false;
	else{
		int temp = v[z.y+1][z.x];
		v[z.y+1][z.x] = 0;
		v[z.y][z.x] = temp;
		z.y = z.y+1;

		return true;
	}
}

void vector_to_fs(ofstream& out, vector< vector<int> >& v){
	Node zero;
	(COLUMN, vector<int>(ROW, 0));

	int num = 0;
	
	for(int i=0; i<COLUMN; i++){
		for(int j=0; j<ROW; j++){
			out << v[i][j] << " ";
		}	
		out << "\n";
	}

	out.close();
	return;


}
