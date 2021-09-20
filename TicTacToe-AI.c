#include<stdio.h>
#include<limits.h>

int update(int board[3][3]);
int minimax(int board[3][3], int depth, int isMaximizing);
int checkWinner(int board[3][3]);
void choicePosition(int board[3][3]);
void displayBoard(int board[3][3]);

int main(){
	
	int board[3][3] = {0}; // X->1  O->-1  Empty->0
	
	update(board);														// call Game Loop function
	return 0;
}


int update(int board[3][3]){
	
	int winner = -2;													// if winner is -2 it's not game over 
	int i;
	int x,y;
	
	i = 0;																//turn control
	while(winner == -2){												//game loop
		
		if(i % 2 == 1){													//Human turn
			do{
				printf("Coordinates:");
				scanf("%d %d",&x,&y);
				
			}while(board[x-1][y-1] != 0 || x<1 || x>3 || y<1 || y>3);
			
			board[x-1][y-1] = -1;										//'O' is placed at the given coordinates
			
			displayBoard(board);										//call displayBoard
			
			winner = checkWinner(board);								//Winner control
		}
		
		else{															//AI Turn
			
			choicePosition(board);										//AI choices best move
			
			displayBoard(board);										//Call displayBoard
			
			winner = checkWinner(board);								//Winner control
		}
		
		i++;
	}
	
	if(winner == 1){													
		printf("X WIN");
	}
	else if(winner == -1){
		printf("O WIN");
	}
	else{
		printf("TIE");
	}
}


int checkWinner(int board[3][3]){										//function winner control
	
	int i,j;
	int countX,countO;
	int count;
	
	count = 0;
	for(i = 0 ; i < 3 ; i++){											//Check for free space on the board
		for(j = 0 ; j < 3 ; j++){
			if(board[i][j] == 0){
				count++;
			}	
		}
	}
	
	if(count == 0){											//if there is no space on the board the game is over
		return 0;
	}
	
	//Horizontal Check
	
	count = 0;
	for(i = 0 ; i < 3 ; i++){
		countX = 0;
		countO = 0;
		for(j = 0 ; j < 3 ; j++){
			
			if(board[i][j] == 1){
				countX++;
			}
			else if(board[i][j] == -1){
				countO++;
			}
		}
		
		
		if(countX == 3){
			return 1;
		}
		else if(countO == 3){
			return -1;
		}
		
	}
	
	// Vertical Check
	
	for(i = 0 ; i < 3 ; i++){
		countX = 0;
		countO = 0;
		for(j = 0 ; j < 3 ; j++){
			if(board[j][i] == 1){
				countX++;
			}
			else if(board[j][i] == -1){
				countO++;
			}
		}
		
		if(countX == 3){
			return 1;
		}
		else if(countO == 3){
			return -1;
		}
	}
	
	//Diagonal Check
	
	countX = 0;
	countO = 0;
	for(j = 0 ; j < 3 ; j++){
		if(board[j][j] == 1){
			countX++;
		}
		else if(board[j][j] == -1){
			countO++;
		}
	}
		
	if(countX == 3){
		return 1;
	}
	else if(countO == 3){
		return -1;
	}
	
	
	countX = 0;
	countO = 0;
	i = 0;
	for(j = 2 ; j >= 0 ; j--){
		if(board[i][j] == 1){
			countX++;
		}
		else if(board[i][j] == -1){
			countO++;
		}
		i++;
	}
		
	if(countX == 3){
		return 1;
	}
	else if(countO == 3){
		return -1;
	}
	
	
	return -2;
	
}

int minimax(int board[3][3],int depth, int isMaximizing){						//function choosing the best move for AI using minimax algorithm
	
	int winner = 0;
	int score;
	int bestScore;
	int i,j;
	
	
	winner = checkWinner(board);									//winner control
	if(winner != -2){
		return winner;
	}
	
	
	if(isMaximizing == 1){									 		// if it's AI's turn
		
		bestScore = INT_MIN;
		
		for(i = 0 ; i < 3 ; i++){
			for(j = 0 ; j < 3 ; j++){
				if(board[i][j] == 0){
					board[i][j] = 1;
					score = minimax(board,depth+1,0);
					board[i][j] = 0;
					if(score > bestScore){
						bestScore = score;
					}
				}
			}
		}
		return bestScore;
	}
	
	else{															// if it's human's turn
		bestScore = INT_MAX;
		
		for(i = 0 ; i < 3 ; i++){
			for(j = 0 ; j < 3 ; j++){
				if(board[i][j] == 0){
					board[i][j] = -1;
					score = minimax(board,depth+1,1);						// recursively call minimax function
					board[i][j] = 0;
					if(score < bestScore){
						bestScore = score;
					}
				}
			}
		}
		return bestScore;
	}
	
	
}

void choicePosition(int board[3][3]){								//function choosing best move using minimax algorithm
	
	int i,j;
	int score,bestScore;
	int x,y;
	bestScore = INT_MIN;
	for(i = 0 ; i < 3 ; i++){
		for(j = 0 ; j < 3 ; j++){
			if(board[i][j] == 0){
				board[i][j] = 1;
				score = minimax(board,0,0);							// call minimax algorithm
				board[i][j] = 0;
				if(score > bestScore){
					bestScore = score;
					x = i;
					y = j;
				}
			}
		}
	}
	board[x][y] = 1;
}


void displayBoard(int board[3][3]){									// function that display the board
	
	int i,j;
	
	system("cls");
	printf("\n  Developed by Engin Memis\n\n");
	printf("\n X -> AI   O -> You\n");
	printf("\n       1   2   3\n\n");
	for(i = 0 ; i < 3 ; i++){
		printf(" %d   |",i+1);
		for(j = 0 ; j < 3 ; j++){
			if(board[i][j] == 1){
				printf(" %c |",'X');
			}
			else if(board[i][j] == -1){
				printf(" %c |",'O');
			}
			else{
				printf("  %c |",0);
			}
		}
		printf("\n");
	}	
	printf("\n\n");
}
