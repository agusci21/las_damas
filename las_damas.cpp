#include<iostream>
using namespace std;


void printTable (int matrix[10][10]);
void preloadTable (int matrix[10][10]);
void moveFile (int matrix[10][10]);

int main(int argc, char** argv) {
	bool isFirstPlayerTurn = true;
	int table[10][10] = {0};
	
	if(isFirstPlayerTurn)
		cout << "Turno del jugador 1 \n";
	else
		cout << "Turno del jugador 2 \n";
		
	preloadTable(table);
	printTable(table);
	moveFile(table);
	printTable(table);

	return 0;
}

void printTable (int matrix[10][10]){
	system("cls");
	cout << "------------------------------\n";
	cout << " 0  1  2  3  4  5  6  7  8  9 \n";
	cout << "------------------------------\n";
	for(int i = 0; i < 10; i++){
		for(int j = 0; j < 10; j++){
			if((i + j) % 2 == 0)
				cout << " x " ;
			else
			  cout << " "<< matrix[i][j] << " ";
		}	
		cout << endl;
	}
	
}

void preloadTable (int matrix[10][10]){
	
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 10; j++){
			if((i + j) % 2 == 1)
			  matrix[i][j] = 1;
		}	
	}
	
	for(int i = 7; i < 10; i++){
		for(int j = 0; j < 10; j++){
			if((i + j) % 2 == 1)
			  matrix[i][j] = 2;
		}	
	}
	
}

void moveFile (int matrix[10][10]){
	int i,j;
	char direction;
	cout << "Que ficha quieres mover? ingrese posicion x, y \n";
	cin >> i >> j;
	matrix[j][i] = 0;
	cout << "Movera a la derecha <D> o a la Izquierda <I>? \n";
	cin >> direction;
	if(direction == 'D'){
		matrix[i + 1][j + 1] = 1;
	}else if(direction == 'I'){
		matrix[i - 1][j + 1] = 1;
	  }
	}


