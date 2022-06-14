#include<iostream>
#include<conio.h>

using namespace std;

void printTable (int matrix[10][10],bool isFirstPlayerTurn);
void preloadTable (int matrix[10][10]);
void moveFirstPlayerFile (int matrix[10][10]);
void moveSecondPlayerFile (int matrix[10][10]);
void moveFiles (int matrix[10][10] ,bool isFirstPlayerTurn);
bool validateIfIsValidSelection(bool isFirstPlayerTurn, int i, int j, int matrix[10][10]);
int determinateMovementAcount(bool isFirstPlayerTurn, int i, int j, int matrix[10][10]);
bool determinateIfBeAbleToMoveRight(bool isFirstPlayerTurn, int i, int j, int matrix[10][10]);
bool determinateIfBeAbleToMoveLeft(bool isFirstPlayerTurn, int i, int j, int matrix[10][10]);
int determinatePlayerPoints(int matrix[10][10], bool isFirstPlayerTurn);

int main() {
	int table[10][10] = {0};
	int firstPlayerPoints = 0;
    int secondPlayerPoints = 0;
	bool isFirstPlayerTurn = true;
	bool isWinner = false;
	preloadTable(table);
	do{
	printTable(table, isFirstPlayerTurn);
	moveFiles(table, isFirstPlayerTurn);
	if(isFirstPlayerTurn){
        cout << firstPlayerPoints << endl;
		firstPlayerPoints += determinatePlayerPoints(table, true);
		cout << "Jugador 1: " << firstPlayerPoints << endl;
	}else{
		secondPlayerPoints += determinatePlayerPoints(table, false);
		cout << "Jugador 2: " << secondPlayerPoints << endl;
	}
    if(firstPlayerPoints >= 5||secondPlayerPoints >= 5)isWinner = true;
	isFirstPlayerTurn = !isFirstPlayerTurn;
    system("pause");
	}while(!isWinner);
    if(firstPlayerPoints >= 5) cout << "Felicitaciones jugador 1, has ganado\n";
    else cout << "Felicitaciones jugador 2, has ganado\n";
	return 0;
}

void printTable (int matrix[10][10], bool isFirstPlayerTurn){
	system("cls");
	isFirstPlayerTurn ? cout << "Turno del Jugador N 1 \n" : cout << "Turno del Jugador N 2\n";
	cout << 
	" +-----------------------------------+\n"
	" | \\ X  0  1  2  3  4  5  6  7  8  9 |\n"
	" | Y +-------------------------------+\n";

	for(int i = 0; i < 10; i++){
		for(int j = 0; j <= 10; j++){
			if( j == 0)
			cout << " | " << i << " | ";
			if(j == 10){
			cout << "| ";
			continue;
			}

			if((i + j) % 2 == 0)
				cout << " x " ;
			else
			  cout << " "<< matrix[i][j] << " ";
		}	
		cout << endl;
	}
	cout << " +---+-------------------------------+\n";
}

void preloadTable (int matrix[10][10]){
	
	//LLena las fichas del jugador 1
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 10; j++){
			if((i + j) % 2 == 1)
			  matrix[i][j] = 1;
		}	
	}
	
	//Llena las fichas del jugador 2
	for(int i = 7; i < 10; i++){
		for(int j = 0; j < 10; j++){
			if((i + j) % 2 == 1)
			  matrix[i][j] = 2;
		}	
	}
	
}

void moveFiles (int matrix[10][10] ,bool isFirstPlayerTurn){
	isFirstPlayerTurn ? moveFirstPlayerFile(matrix) : moveSecondPlayerFile(matrix);
}


void moveFirstPlayerFile (int matrix[10][10]){
	// i = y; j = x
	bool isValidSelection = false;
	int i,j;
	char direction;
	do{
	cout << "Que ficha quieres mover? ingrese posicion x, y \n";
	cin >> i >> j;
	isValidSelection = validateIfIsValidSelection(true, j , i, matrix);
	} while (!isValidSelection);
	bool canMoveRight = determinateIfBeAbleToMoveRight(true, j , i, matrix);
	bool canMoveLeft = determinateIfBeAbleToMoveLeft(true, j , i, matrix);
	if(canMoveRight && canMoveLeft){
		cout << "Movera a la derecha <D> o a la Izquierda <I>? \n";
		cin >> direction;
	}else if(canMoveRight && !canMoveLeft){
		direction = 'D';
	}else if(!canMoveRight && canMoveLeft){
		direction = 'I';
	}
	matrix[j][i] = 0;
	if(direction == 'd' || direction == 'D'){
		matrix[j + 1][i + 1] = 1;
		return;
	}else{
		matrix[j + 1][i - 1] = 1;
		return;
	}
	
}

void moveSecondPlayerFile (int matrix[10][10]){
	// i = y; j = x
	int i,j;
	char direction;
	bool isValidSelection = false;
	do{
	cout << "Que ficha quieres mover? ingrese posicion x, y \n";
	cin >> i >> j;
	isValidSelection = validateIfIsValidSelection(false, j,i, matrix);
	} while (!isValidSelection);
	bool canMoveRight = determinateIfBeAbleToMoveRight(false, j , i, matrix);
	bool canMoveleft = determinateIfBeAbleToMoveLeft(false, j , i, matrix);
	if(canMoveRight && canMoveleft){
		cout << "Movera a la derecha <D> o a la Izquierda <I>? \n";
		cin >> direction;
	}else if(canMoveRight && !canMoveleft){
		direction = 'D';
	}else if(!canMoveRight && canMoveleft){
		direction = 'I';
	}
	matrix[j][i] = 0;
	if(direction == 'd' || direction == 'D'){
		matrix[j - 1][i + 1] = 2;
		return;
	}
	else if(direction == 'i' || direction == 'I'){
		matrix[j - 1][i - 1] = 2;
		return;
	}
}

bool validateIfIsValidSelection(bool isFirstPlayerTurn, int i, int j, int matrix[10][10]){
	// Validaciones generales
	if(i < 0 || i > 9) {
		cout << "Posicion \" X \" fuera del rango [0-9]\n";
		return false;
	}

	if(j < 0 || j > 9) {
		cout << "Posicion \" Y \" fuera del rango [0-9]\n";
		return false;
	}

	if((i+j) % 2 == 0) {
		cout << "Esta es una casilla vacia, no puedes seleccionarla \n";
		return false;
	}

	//Validaciones por jugador
	
	if(isFirstPlayerTurn && matrix[i][j] != 1){
		cout << "Esa ficha no te pertenece\n"; 
		return false;
	}else if(!isFirstPlayerTurn && matrix[i][j] != 2){
		cout << "Esa ficha no te pertenece\n"; 
		return false;
	}
	

	//Validacion de posible movimiento
	if(!determinateMovementAcount(isFirstPlayerTurn, i, j, matrix)) {
		cout << "Esta ficha no tiene movimientos posibles \n";
		return false;
	}
	
	return true;
}

int determinateMovementAcount(bool isFirstPlayerTurn, int i, int j, int matrix[10][10]){
	int posibleMovementAcount = 2;
	if(j == 0 || j == 9){
		posibleMovementAcount--;
	}

	if(isFirstPlayerTurn){
		if(matrix[i + 1][j + 1] == 1)
			posibleMovementAcount--;
		if(matrix[i + 1][j - 1] == 1)
			posibleMovementAcount--;
	}

	if(!isFirstPlayerTurn){
		if(matrix[i - 1][j + 1] == 2)
			posibleMovementAcount--;
		if(matrix[i - 1][j - 1] == 2)
			posibleMovementAcount--;
	}
	return posibleMovementAcount;
}

bool determinateIfBeAbleToMoveRight(bool isFirstPlayerTurn, int i, int j, int matrix[10][10]){
	if(isFirstPlayerTurn && matrix[i + 1][j + 1] != 1 && j != 9){
		return true;
	}
	if(!isFirstPlayerTurn && matrix[i - 1][j + 1] != 2 && j != 9){
		return true;
	}
	return false;
}

bool determinateIfBeAbleToMoveLeft(bool isFirstPlayerTurn, int i, int j, int matrix[10][10]){
	if(isFirstPlayerTurn && matrix[i + 1][j - 1] != 1 && j != 0) return true;
	
	if(!isFirstPlayerTurn && matrix[i - 1][j - 1] != 2 && j != 0) return true;
	
	return false;
}

int determinatePlayerPoints(int matrix[10][10], bool isFirstPlayerTurn ){
	int playerNumber = isFirstPlayerTurn ? 1 : 2;
	int points = 0;
	for(int i = 0; i < 10; i++){
		for(int j = 0; j < 10; j++){
			if(matrix[9][j] == 1 && isFirstPlayerTurn){
				matrix[9][j] = 0;
				points ++;
			}else if(matrix[0][j] == 2 && !isFirstPlayerTurn){
				matrix[9][j] = 0;
				points ++;
			}
		}
	}
	return points;
}
