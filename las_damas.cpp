#include<iostream>
#include<conio.h>
#include<string>

using namespace std;
struct Player{
	int points = 0;
	string name;
	string color;	
};

void printTable (int matrix[10][10], bool isFirstPlayerTurn, Player firstPlayer, Player secondPlayer);
void preloadTable (int matrix[10][10]);
void moveFirstPlayerFile (int matrix[10][10]);
void moveSecondPlayerFile (int matrix[10][10]);
void moveFiles (int matrix[10][10] ,bool isFirstPlayerTurn);
bool validateIfIsValidSelection(bool isFirstPlayerTurn, int i, int j, int matrix[10][10]);
int determinateMovementAcount(bool isFirstPlayerTurn, int i, int j, int matrix[10][10]);
bool determinateIfBeAbleToMoveRight(bool isFirstPlayerTurn, int i, int j, int matrix[10][10]);
bool determinateIfBeAbleToMoveLeft(bool isFirstPlayerTurn, int i, int j, int matrix[10][10]);
int determinatePlayerPoints(int matrix[10][10], bool isFirstPlayerTurn);
void runGame(string playersNames[10], string playersColors[10], int playersPoints[10], int playerAmounts, int players[2]);
void createUser(string playersNames[10], string playersColors[10], int playersPoints[10], int playerAmounts);
int translateInput();
void printUsers(string playersNames[10], string playersColors[10], int playersPoints[10], int playerAmount);
void getCurrentPlayers(string playersNames[10], string playersColors[10], int playersPoints[10], int playerAmount, int players[2]);
void changeColor(string color);

int main() {
	char option = '0';
	int playersAmount = 0;
	int playersPoints[20];
	string playersNames[20];
	string playersColors[20];
	int players[2];
	cout << "Bienvenido a las Damas" << endl;
	do{
	cout << "1 --- Jugar" << endl;
	cout << "2 --- Crear un usuario" << endl;
	cout << "3 --- Listar partidas ganadas" << endl;
	cout << "Otra tecla --- Salir" << endl;
	option = getche();
	cout << endl;
	switch(option){
		case '1':
		 runGame(playersNames, playersColors, playersPoints, playersAmount, players);
		 break;

		case '2':
			createUser(playersNames, playersColors, playersPoints, playersAmount);
			playersAmount++;
			cout << "Cantidad de jugadores: " << playersAmount << endl;
			break;
		case '3' :
			printUsers(playersNames, playersColors, playersPoints, playersAmount);
			break;
		default:
			option = '0';
			break;
	}
	}while(option != '0');
	return 0;
}

void printTable (int matrix[10][10], bool isFirstPlayerTurn, Player firstPlayer, Player secondPlayer){
	system("cls");
	if(isFirstPlayerTurn){
		cout << "Turno de " << firstPlayer.name << endl;
		changeColor(firstPlayer.color);
	}else {
		cout << "Turno de " << secondPlayer.name << endl;
		changeColor(secondPlayer.color);
	}
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
	i = translateInput();
	j = translateInput();
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
    i =  translateInput();
    j =  translateInput();
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

int translateInput(){
    int aux;
	do{
	aux = getche();
    cout << endl;
    if(aux > 57 || aux < 48) cout << "Seleccione un numero por favor\n-----------------------------\n";
	}while(aux > 57 || aux < 48);
    return aux - 48;
}

void runGame(string playersNames[10], string playersColors[10], int playersPoints[10], int playerAmounts, int players[2]){
		int table[10][10] = {0};
		int firstPlayerPoints = 0;
    	int secondPlayerPoints = 0;
		bool isFirstPlayerTurn = true;
		bool isWinner = false;
		if(playerAmounts < 2){
			cout << "Primero debe crear un minimo de 2 jugadores\n";
			return;
		}
		preloadTable(table);
		getCurrentPlayers(playersNames, playersColors, playersPoints, playerAmounts, players);
		Player firstPlayer, secondPlayer;
		//Nombres de jugadores
		firstPlayer.name = playersNames[players[0]];
		secondPlayer.name = playersNames[players[1]];
		//Puntaje de jugadores
		firstPlayer.points = playersPoints[players[0]];
		secondPlayer.points = playersPoints[players[1]];
		//Color de jugadores
		firstPlayer.color = playersColors[players[0]];
		secondPlayer.color = playersColors[players[1]];
		do{
		printTable(table, isFirstPlayerTurn, firstPlayer, secondPlayer);
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
    	if(firstPlayerPoints >= 5) {
			cout << "Felicitaciones " << firstPlayer.name << " has ganado\n";
			playersPoints[players[0]]++;
		}
    	else {
			cout << "Felicitaciones " << secondPlayer.name << " has ganado\n";
			playersPoints[players[1]]++;
		}
		changeColor("NULL");
		system("pause");
		system("cls");
}

void createUser(string playersNames[10], string playersColors[10], int playersPoints[10], int playersAmount){
	string validSelections = "1234567";
	Player player;
	string name;
	string color = "COLOR 0x";
	char colorChar;
	int points = 0;
	system("cls");
	cout << "Crea tu usuario\nIngrese su nombre\n";
	cin >> name;
	system("cls");
	do{
		cout << "Ingrese su color de preferencia \n";
		cout << 
    	"1 = Azul\n"
    	"2 = Verde\n"
    	"3 = Aguamarina\n"
    	"4 = Rojo \n"
    	"5 = Purpura\n"
    	"6 = Amarillo\n"
    	"7 = Blanco\n";
		colorChar = getche();
		cout << endl;
		if(validSelections.find(colorChar) == string::npos){
			cout << "Por favor, selecione una opcion valida\n";
			system("pause");
			system("cls");
		}
	}while(validSelections.find(colorChar) == string::npos);
	color[7] = colorChar;
	player.name = name;
	player.color = color;
	player.points = 0;
	playersPoints[playersAmount] = player.points;
	playersNames[playersAmount] = player.name;
	playersColors[playersAmount] = player.color;
	system("cls");
}

void printUsers(string playersNames[10], string playersColors[10], int playersPoints[10], int playerAmounts){
	Player player;
	cout << "-----------------------\n";
	for(int i = 0; i < playerAmounts; i++){
		player.name = playersNames[i];
		player.points = playersPoints[i];
		player.color = playersColors[i];
		cout << "Jugador N: " << i+1 << endl;
		cout << "Nombre: " << player.name << endl;
		cout << "Puntaje: " <<player.points << endl;
		cout << "-----------------------\n";
	}
}

void getCurrentPlayers(string playersNames[10], string playersColors[10], int playersPoints[10], int playerAmount, int players[2]){
	int firstPlayer, secondPlayer;
	system("cls");
	do{
		cout << "Seleccione el Jugador 1: \n";
		printUsers(playersNames, playersColors, playersPoints, playerAmount);
		firstPlayer = translateInput() - 1;
		if(firstPlayer > playerAmount || firstPlayer == -1){
			cout << "Por favor, seleccione una opcion valida\n";
			system("pause");
			system("cls");
		}
	}while(firstPlayer > playerAmount || firstPlayer == -1);
	system("cls");
	cout << "Seleccione el Jugador 2: \n";
	printUsers(playersNames, playersColors, playersPoints, playerAmount);
	secondPlayer = translateInput() - 1;
	players[0] = firstPlayer;
	players[1] = secondPlayer;
}

void changeColor(string color){

	switch(color[7]){
		case '1':
			system("COLOR 01");
			break;

		case '2':
			system("COLOR 02");
			break;

		case '3':
			system("COLOR 03");
			break;

		case '4':
			system("COLOR 04");
			break;

		case '5':
			system("COLOR 05");
			break;

		case '6':
			system("COLOR 06");
			break;

		default:
			system("COLOR 07");
			break;
	}
}