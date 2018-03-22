/*=======================================================================================

MORE INFO ON HEURISTICS:
	https://heuristicswiki.wikispaces.com/N+-+Puzzle

Programmer: Adam Mischke
Date: Sep 18, 2017
Class: 
	CSCI 4350 Open Lab 1
	Solving Problems By Search
Description:
	This program solves the n-puzzle by using A* with the following heuristics argv:
	0:
		0 - h(n) = 0 (Uniform Cost Search) AKA no heuristic :o) AKA BAD
        3^20  = 3.4 x 10^9 = 3.4 Billion game states.
    1:
    	1 - h(n) = Number of tiles displaced from the goal
    2:
    	2 - h(n) = Sum of Manhattan (city-block) distances of all tiles from the goal
    3:
    	3 - h(n) = A novel heuristic of your own design
=======================================================================================*/


#include <iostream> // cout
#include <queue>	// priority_queue
#include <vector>	// vector
#include <fstream> 	// ifstream, ofstream (not used)
#include <map>		// map
#include <set>		// set
#include <cstdlib>	// atoi
#include <cmath>	// hypot

#define ROW 3
#define COLUMN 3
#define ROOT 0		// used to keep track of depth from parent to CHILDREN

using namespace std;
// The total number of nodes visited/expanded (VISITED)
// The maximum number of nodes stored in memory (closed list + open list size) (ID)
// The depth of the optimal solution (DEPTH)
// The -approximate- effective branching factor (b) where N = b^d
int HEURISITC=0, VISITED=0,DEPTH=0,ID=0;
long double BRANCHING=0;
// A Node on a graph: (x,y)
struct Node
{
	int x;
	int y;
};

// A state on the 2-d board v, vector
// it's unique ID
// the cost associated with the action
typedef struct
{	
	std::vector< std::vector<int> > v;		// the 2-d board
	int id;									// ID to resolve cost issues
	int cost;								// this is the first thing we compare between, then we go to ID
	int depth;								// depth of the state

} State;

// the comparision for our frontier (priority queue)
struct Compare
{
	bool operator() (State *&lhs, State *&rhs)
	{	
		// if we can't resolve the costs,
		if (lhs->cost == rhs->cost)
			// return the lesser id
			return lhs->id > rhs->id;
		// return the lesser cost
        return lhs->cost > rhs->cost;
	}
};



// a mapping of the board to a boolean of visited or not
//map<vector<vector<int> >,bool> visited;
set<vector<vector<int> > > visited;
// a mapping of the board to it's parent
map<vector<vector<int> > , vector<vector<int> > > parent;

// setting this here so we don't have to continually pass as a parameter
vector< vector<int> > GOAL_STATE(COLUMN, vector<int>(ROW, 0));

// initializes the goal state
// INPUT:  NONE (the global goal vector is used)
// OUTPUT: NONE (sets the goal state)
void set_goal_state();

// prints a board using cout
// input:  the reference to a board
// output: 2-d vector to stdout
void print_board(vector< vector<int> >&);

// filestream to vector
// input:	reference to input fs, reference to a board
// output:	sets the initial state and closes the filestream 
void fs_to_vector(ifstream&, vector< vector<int> >&);

// performs the a* algorithm
// input:	an initial state
// output:	finds the solution
void a_star(State*);

// USED FOR HEURISITC 1
// finds the number of correct positions of a state
// input:	a state
// output:	the number of correct positions (ROW vs COLUMN)
int correct_states(State*);

// finds the (x,y) coordinates of the 0 on the board
// input:	the board
// output:	the Node pair (x,y) of the 0 on this board
Node find_zero(vector< vector<int> >);

// the possibilites of moving the zero either left, right, up, or down
// input:	a board
// output:	a vector of successful moves of the zero
vector<vector<vector<int> > > move_zero(vector< vector<int> >);

// helper function for move zero, moves left
// input:	a reference to the vector of boards and where the zero is as a (x,y) pair
// output:  none, updates the vector of moves through reference
void move_left(vector<vector<vector<int> > >&, vector< vector<int> >, Node);

// helper function for move zero, moves right
// input:	a reference to the vector of boards and where the zero is as a (x,y) pair
// output:  none, updates the vector of moves through reference
void move_right(vector<vector<vector<int> > >&, vector< vector<int> >, Node);

// helper function for move zero, moves up
// input:	a reference to the vector of boards and where the zero is as a (x,y) pair
// output:  none, updates the vector of moves through reference
void move_up(vector<vector<vector<int> > >&, vector< vector<int> >, Node);

// helper function for move zero, moves down
// input:	a reference to the vector of boards and where the zero is as a (x,y) pair
// output:  none, updates the vector of moves through reference
void move_down(vector<vector<vector<int> > >&, vector< vector<int> >, Node);

// the heuristic function: returns the heurisitcs determined by the argv
//	input:	a state
//	output:	returns the calculation
int h(State*);

//  USED FOR HEURISTIC 2
//  the manhattan function:
//  The distance between two points in a grid based on a strictly horizontal and/or vertical path (that is,
//  along the grid lines), as opposed to the diagonal or "as the crow flies" distance. The Manhattan distance
//  is the simple sum of the horizontal and vertical components, whereas the diagonal distance might be computed by
//  applying the Pythagorean theorem.
// 	input:		a board
//	outputs:	returns the distance	
int manhattan(vector<vector<int> >);


// 	recursively calls each others parents until finding an empty 2-d vector
// 	input:	the goal as a vector
//	output:	none, but updates the DEPTH counter
void trace_path(vector<vector<int> >);

// cin to 2-d board
void cin_to_vector(vector< vector<int> >&);

// USED FOR HEURISTIC 3
// the euclidean distance:
// basically, i took the manhattan and changed it to fit the distance formula
// inp
int euclidean(vector<vector<int> >);


int main(int argc, char ** argv){

	// initialization of goal state
	set_goal_state();
	//cout << "GOAL STATE:\n";
	//print_board(GOAL_STATE);

	// initialization of begin state
	vector< vector<int> > BEGIN_STATE(COLUMN, vector<int>(ROW, 0));
	
	/*	*IFSTREAM*
	ifstream in;
	string file = "OLA1-input2.txt";

	in.open(file);

	if(!in){
		return EXIT_FAILURE;
	}
	

	fs_to_vector(in,BEGIN_STATE);
	*/

	//cout << "BEGIN STATE:\n";
	//print_board(BEGIN_STATE);
	cin_to_vector(BEGIN_STATE);

	// handle argv1
	HEURISITC =  atoi(argv[1]);
	//HEURISITC = 2;

	// setting root state on the tree
	State *tree;
	tree = new State;
	
	//cout << tree;
	tree->v = BEGIN_STATE;
	tree->id = ID;		// ID = 0
	ID++;				// for the next id
	tree->depth = ROOT;	// ROOT = 0

	// null vector for parent
	vector<vector<int> > empty;

	// add child (temp) to parent pair (current)
	parent.insert(pair<vector<vector<int> > , vector<vector<int> > >(tree->v,empty));

	//cout << "starting heuristic #" << HEURISITC << "..\n";
	//auto t1 = std::chrono::high_resolution_clock::now();
	// solve using a*
	a_star(tree);
	//auto t2 = std::chrono::high_resolution_clock::now();

	// The -approximate- effective branching factor (b) where N = b^d
	// therefore: b = exp(N, - d)

		/*			PRINTING			*/

		BRANCHING = pow(double(ID),(1 / double(DEPTH)));

		cout << "V=" << VISITED << "\nN=" << ID << "\nd=" << DEPTH  << "\nb=" << BRANCHING << "\n\n";
    	trace_path(GOAL_STATE);

    	//cout << "\b..took "
        // 	 << std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count()
        // 	 << " milliseconds\n";

	return EXIT_SUCCESS;
}

// iterate through the board and set the board to:
void set_goal_state(){
	/*	0 1 2
		3 4 5
		6 7 8	*/  
	int init = 0;
	for(int i=0; i<COLUMN; i++){
		for(int j=0; j<ROW; j++){
			GOAL_STATE[i][j] = init;
			init++;
		}
	}
}
// cin to board
void cin_to_vector(vector< vector<int> >& v){

	for(int i=0; i<COLUMN; i++){
		for(int j=0; j<ROW; j++){
			cin >> v[i][j];
		}	
	}
	return;
}

// iterate through the board and print
void print_board(vector< vector<int> > &v){
	for(int i=0; i<COLUMN; i++){
		for(int j=0; j<ROW; j++){
			cout << v[i][j] << " ";
		}cout << "\n";
	}
	return;
}

// iterate through the board and compare the goal board the the current state
// int returns a 0-9
int correct_states(State *s){
	int correct = 0;
	for(int i=0; i<COLUMN; i++){
		for(int j=0; j<ROW; j++){
			if(GOAL_STATE[i][j] == s->v[i][j])
				correct++;	
		}
	}
	return correct;
}

// while char seperated by ws, iterate through the board and assign
// close the fs
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

// perform a* on a state,
// uses a priority queue as a frontier,
void a_star(State *s){

	// the correct states
	int cor;

	// create the frontier
	priority_queue<State*,vector<State*>,Compare> frontier;
	// push the state onto the world
	frontier.push(s);

	while(!frontier.empty()){

		// top, pop, and add to the visited vector
		State *current = new State;
		current = frontier.top();
		frontier.pop();
		visited.insert(current->v);
		VISITED++;


		// find the number of correct states
		cor = correct_states(current);
		//cout << "CURRENT STATE (" << cor << "):\n";
		//print_board(current->v);
		// if goal, quit
		if (cor == COLUMN * ROW){
			//cout << "GOAL!!\n";
			DEPTH = current->depth;
			return;
		}

		//cout << "CHILDREN: \n";
		//	create a vector of board moves from the current board (next states)
		vector<vector<vector<int> > > ns = move_zero(current->v);

		// iterate over the vector of moves
		vector<vector<vector<int> > >::iterator it;
		for(it=ns.begin();it!=ns.end();it++){

			//print_board(*it);
			vector<vector<int> > temp = *it;

			// if we haven't visited the state yet,
			//!has_visited(temp)
			if(visited.find(temp) == visited.end()){

				// add child (temp) to parent pair (current)
				parent.insert(pair<vector<vector<int> > , vector<vector<int> > >(temp,current->v));

				// create a temp state and assign
				State *temp_s = new State;
				temp_s->v = temp;
				temp_s->id = ID;
				temp_s->depth = current->depth+1;
				ID++;
				// calculate the cost with a heurisitc function based on argv
				temp_s->cost = temp_s->depth + h(temp_s);
				//cout << "\ndeep: " << temp_s->depth << " h: " <<  h(temp_s) << "\n";

				// push onto the frontier
				frontier.push(temp_s);
			}
		}
		//return;
		/*TESTING CHILDREN
		current = frontier.top();
		print_board(current.v);
		cout << "id: "<<current.id << "cost: " << current.cost << "depth: "<< current.depth << "\n";
		frontier.pop();
		current = frontier.top();
		print_board(current.v);
		cout << "id: "<<current.id << "cost: " << current.cost <<"depth: "<< current.depth << "\n";
		frontier.pop();
		//current = frontier.top();
		//print_board(current.v);
		//cout << "id: "<<current.id << "cost: " << current.cost << "\n";
		//frontier.pop();
		return;*/
		
	}
	
	// free the frontier! 
	while(!frontier.empty()){
		State* i = frontier.top();
		delete(i);
		frontier.pop();
	}

	return;
}

// returns a vector of boards that are the theoretical adj moves of the board parameter
 vector<vector<vector<int> > > move_zero(vector< vector<int> > v){

	vector<vector<vector<int> > > adj;
	Node z = find_zero(v);


	move_left(adj,v,z);
	move_up(adj,v,z);
	move_down(adj,v,z);
	move_right(adj,v,z);


	return adj;

}

// moves left on the 2-d board
void move_left(vector<vector<vector<int> > > &adj, vector< vector<int> > v, Node z){
	if(z.x == 0)
		return;
	else{
		int temp = v[z.y][z.x-1];
		v[z.y][z.x-1] = 0;
		v[z.y][z.x] = temp;
		z.x = z.x-1;
		adj.push_back(v);
		return;
	}
}

// moves right on the 2-d board
void move_right(vector<vector<vector<int> > > &adj, vector< vector<int> > v, Node z){
	if(z.x == COLUMN-1)
		return;
	else{
		int temp = v[z.y][z.x+1];
		v[z.y][z.x+1] = 0;
		v[z.y][z.x] = temp;
		z.x = z.x+1;
		adj.push_back(v);

		return;
	}
}

// moves up on the 2-d board
void move_up(vector<vector<vector<int> > > &adj, vector< vector<int> > v, Node z){
	if(z.y == 0)
		return;
	else{
		int temp = v[z.y-1][z.x];
		v[z.y-1][z.x] = 0;
		v[z.y][z.x] = temp;
		z.y = z.y-1;
		adj.push_back(v);


		return;
	}
}

// moves down on the 2-d board
void move_down(vector<vector<vector<int> > > &adj, vector< vector<int> > v, Node z){

	if(z.y == ROW-1)
		return;
	else{
		int temp = v[z.y+1][z.x];
		v[z.y+1][z.x] = 0;
		v[z.y][z.x] = temp;
		z.y = z.y+1;
		adj.push_back(v);

		return;
	}
}

// finds and returns a (x,y) node of where the zero is on a vector
Node find_zero(vector< vector<int> > v){

	Node z;
	for(int i=0; i<COLUMN; i++){
		for(int j=0; j<ROW; j++){
			// find zero
			if (v[i][j] == 0){
				z.y=i;
				z.x=j;
				//cout << "the zero is here: [" << z.x << "," << z.y << "]"<< "\n";
			}
		}
	}
	return z;
}

// returns the manhattan value for a given vector
int manhattan(vector<vector<int> > v){
	// or ID 
	int dist=0;
	// iterate through the board
	for(int i=0;i<COLUMN;i++){
		for(int j=0;j<ROW;j++){

			// DONT COUNT THE 0!
			if(v[i][j]!=0){

				// iterate through a 2nd copy of a vector
				for(int k=0;k<COLUMN;k++){
					for(int l=0;l<ROW;l++){

						if(v[i][j]==GOAL_STATE[k][l]){
							// calculate the absolute value of the distances
							dist+=abs(i-k)+abs(j-l);
						}
					}
				}
			}
		}
	}
	return dist;
}

// returns the manhattan value for a given vector
int euclidean(vector<vector<int> > v){
	// or ID 
	int dist=0;
	// iterate through the board
	for(int i=0;i<COLUMN;i++){
		for(int j=0;j<ROW;j++){

			// DONT COUNT THE 0!
			if(v[i][j]!=0){

				// iterate through a 2nd copy of a vector
				for(int k=0;k<COLUMN;k++){
					for(int l=0;l<ROW;l++){

						if(v[i][j]==GOAL_STATE[k][l]){
							// calculate the absolute value of the distances
							dist+=hypot((i-k),(j-l));
						}
					}
				}
			}
		}
	}
	return dist;
}

// heuristic function, handles the argv option
int h(State *s){
	int correct, displaced, sum;
	switch(HEURISITC){
		// 		 	0 - h(n) = 0 (Uniform Cost Search)
        //       	3^20  = 3.4 x 10^9 = 3.4 Billion game states.
		case 0: 
			//cout << "0 (Uniform Cost Search)\n\n";
			return HEURISITC;


		// 		  	1 - h(n) = Number of tiles displaced from the goal
		case 1:
			correct = correct_states(s);
			displaced = (ROW * COLUMN) - correct;
			//cout << "Number of tiles correct/displaced from the goal: " << correct << "/" << displaced << "\n\n";
			return displaced;

		// 		  	2 - h(n) = Sum of Manhattan (city-block) distances of all tiles from the goal
		case 2:
			sum = manhattan(s->v);
			//cout << "Sum of Manhattan (city-block) distances of all tiles from the goal: " << sum << "\n\n";
			return sum;

		// 			3 - h(n) = A novel heuristic of your own design
		case 3:
			sum = euclidean(s->v);
			return sum;

	}
	return 0;

}

void trace_path(vector<vector<int> > v){

	if(!parent[v].empty())
   	 	trace_path(parent[v]);

   	print_board(v);
   	cout << "\n";
   	return;
}
