#include <iostream>
#include <stack>
using namespace std;

class Cell
{
public:
	//top right left bottom
    bool walls[4];
    bool visited;
	Cell *up;
	Cell *right;
	Cell *down;
	Cell *left;
	Cell()
	{
		for(int i = 0; i < 4; i++) walls[i] = true;
		up = NULL;
		right = NULL;
		down = NULL;
		left = NULL;
		visited = false;
	}


	bool hasUnvisitedNeighbor()
	{
		if(up != NULL) if(!up->visited) return true;
		if(right != NULL) if(!right->visited) return true;
		if(down != NULL) if(!down->visited) return true;
		if(left != NULL) if(!left->visited) return true;
		return false;
	}
};

int size = 10;
Cell cells[10][10];
Cell * current = &cells[0][0];
stack<Cell*> visitedCells;

void printCells()
{
	for(int j = 0; j < size; j++)
	{
		//print tops
		for(int i = 0; i < size; i++)
		{
			if(cells[j][i].walls[0]) cout << " __ ";
			else cout << "    "; // 4 spaces
		}
		cout << endl;
		//print sides & bottoms
		for(int i = 0; i < size; i++)
		{
			//left wall
			if(cells[j][i].walls[3])
			{
				cout << "|";
				if(cells[j][i].walls[2]) cout << "__";
				else cout << "  "; // 2 spaces
			}
			else
			{
				if(cells[j][i].walls[2]) cout << " __";
				else cout << "   "; // 3 spaces
			}
			//right wall
			if(cells[j][i].walls[1]) cout << "|";
			else cout << " ";
		}
		cout << endl;
	}
}

bool unvisitedsExist()
{
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
		{
			if(!cells[i][j].visited) return true;
		}
	}
	return false;
}

int randDir()
{
	return rand() % 4;
}

int chooseCell(Cell *current)
{
	int toCheck = randDir();
	// check toCheck
	// toCheck = (toCheck + 1) % 4
	// if checed 4 times return -1

	int checks = 0;
	while(checks < 4)
	{
		switch(toCheck)
		{
			case 0:
				if(current->up)
					if(!current->up->visited)
						return 0;
			case 1:
				if(current->right)
					if(!current->right->visited)
						return 1;
			case 2:
				if(current->down)
					if(!current->down->visited)
						return 2;
			case 3:
				if(current->left)
					if(!current->left->visited)
						return 3;
		}
		checks++;
		toCheck = (toCheck + 1) % 4;
	}
	return -1;
}

int main()
{
	//setup
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
		{
			if(i > 0) cells[j][i].left = &cells[j][i-1];
			if(i < size - 1) cells[j][i].right = &cells[j][i+1];
			if(j > 0) cells[j][i].up = &cells[j-1][i];
			if(j < size - 1) cells[j][i].down = &cells[j+1][i];
		}
	}
	//display
	printCells();
	cout << endl;
	for(int i = 0; i < size * 4; i++) cout << "*";
	cout << endl << endl;
	int loops = 0;//for debugging
	//begin algorithm
	while(unvisitedsExist())
	{
		current->visited = true;
		int next = chooseCell(current);
		visitedCells.push(current);
		// cout << loops << endl;
		switch(next)
		{
			case 0:
				current->walls[0] = false;
				current->up->walls[2] = false;
				current = current->up;
				break;
			case 1:
				current->walls[1] = false;
				current->right->walls[3] = false;
				current = current->right;
				break;
			case 2:
				current->walls[2] = false;
				current->down->walls[0] = false;
				current = current->down;
				break;
			case 3:
				current->walls[3] = false;
				current->left->walls[1] = false;
				current = current->left;
				break;
			case -1:
				while(!current->hasUnvisitedNeighbor() && !visitedCells.empty())
				{
					current = visitedCells.top();
					visitedCells.pop();
				}
				break;
		}
		// loops++;
	}
	printCells();
}
