/*##########################################################################*/
/*                                                                          */
/* HW08_Taha_Atakan_Ipekci_141044011                                        */
/* ­­­­­­­­­                                                                         */
/* Created on 22/04/2016 by Taha Atakan Ipekci                              */
/*                                                                          */
/*                                                                          */
/*Description                                                               */
/* -------------------------------------------------------------------------*/
/* Simulates a game of chess with basic rules.    						    */
/* 																		    */           
/*                                                                          */
/*                                                                          */
/*                                                                	        */
/*                                                                          */
/* ­­­­­­­­­­                                                                         */
/*                                                                          */
/*                                                                          */
/*##########################################################################*/

/*--------------------------------------------------------------------------*/
/*                            Includes                                      */
/*--------------------------------------------------------------------------*/


#include <stdio.h>

/*--------------------------------------------------------------------------*/
/*                             Defines                                      */
/*--------------------------------------------------------------------------*/

#define BOARD_SIZE 8

/*Initialized the classic 8*8 board. Uses a 1D array with a size of 64*/
void initBoard(char board[]);

/*Gets the row and column variables from the player by using scanf*/
void getPosition(char *col, int *row);

/*Checks if a cell is valid according to the variable that are scanned by */
/*getPosition function*/
int isValidCell(char col, int row);

/*Prints the board*/
void printBoard(char *board);

/*Calls the correct function depending on the chess piece which is in source*/
/*cell to find if it can move to the target position*/
int isPieceMovable(char *board, char sc, int sr, char tc, int tr);

/*Checks whether a king is in check or not. */
/*If white king is in check returns 1*/
/*If black king is in check returns 2*/
/*If there is no check returns 0*/ 
int isInCheck(char* board);

/*Moves a piece from source to destination if current player's king is not in */
/*check and piece can move from source to destination.*/
int makeMove(char *board, char sc, int sr, char tc, int tr);

/*Gets the chess piece which is in source cell*/
char getPlayer(char *board, char sc, int sr);

/*If the piece is black returns 1 otherwise 0*/
int isBlack(char currPlayer);

/*If the piece is white returns 1 otherwise 0*/
int isWhite(char currPlayer);

/*Checks if rook can move from the source cell to target considering the basic*/
/*game rules.*/
int isRookMovable(char *board, char sourceCol, int sourceRow, char targetCol,
				  int targetRow);

/*Checks if knight can move from the source cell to target considering the */
/*basic game rules.*/
int isKnightMovable(char *board, char sourceCol, int sourceRow, char targetCol,
				  int targetRow);

/*Checks if bishop can move from the source cell to target considering the */
/*basic game rules.*/
int isBishopMovable(char *board, char sourceCol, int sourceRow, char targetCol,
				  int targetRow);

/*Checks if queen can move from the source cell to target considering the */
/*basic game rules.*/
int isQueenMovable(char *board, char sourceCol, int sourceRow, char targetCol,
				  int targetRow);

/*Checks if king can move from the source cell to target considering the basic*/
/*game rules.*/
int isKingMovable(char *board, char sourceCol, int sourceRow, char targetCol,
				  int targetRow);

/*Checks if pawn can move from the source cell to target considering the basic*/
/*game rules.*/
int isPawnMovable(char *board, char sourceCol, int sourceRow, char targetCol,
				  int targetRow);

int main() {
    char board [BOARD_SIZE*BOARD_SIZE], empty;
    int player = 1; /* 1 white, 0 black */
    char sc,tc; /* source/target cols */
    int sr,tr; /* source/target rows */
    int moveStatus = 0;
    int checkStatus = 0;
    char currPlayer;

    initBoard(board);

    do {
        printBoard(board);
        printf("%s player move > ", player ? "White" : "Black");
        getPosition(&sc,&sr);
        scanf("%c", &empty);
        getPosition(&tc,&tr);
        scanf("%c", &empty);
        currPlayer = getPlayer(board, sc,sr);

        if(!isValidCell(sc,sr)) {
            printf("Source position is invalid\n");
            continue;
        }
        if(!isValidCell(tc,tr)) {
            printf("Target position is invalid\n");
            continue;
        }
        if((isBlack(currPlayer) && player) ||
           (isWhite(currPlayer) && !player)) {
            printf("Illegal piece. \n");
            continue;
        }

        moveStatus = makeMove(board,sc,sr,tc,tr);
        switch(moveStatus) {
            case 0:
                printf("Invalid move!\n");
                break;
            case 1:
                printf("Your king is in check!\n");
                ++checkStatus;
                break;
            case 3:
                printf("Check!\n ");
            case 2:
                player = !player;
                checkStatus = 0;
                break;
        }
    } while(checkStatus < 2);
    printf("%s player WINS!\n", player ? "Black" : "White");
    return 0;
}

int isInCheck(char* board){

/*i stores the position of the king in board. j is used to store the position */
/*of every piece one by one in a loop*/
/*col1 and row1 are the column and row values of the king. col2 and row2 are*/
/*for other pieces*/
int i,j,row1,row2;
char col1,col2;

	/*Finds the king*/
	for(i=0; board[i] != 'k' && i<=63; i++){}
	
	/*converts the cell position to col and row values. Note that a8 is the */
	/*first element of the board array and h1 is the last*/
	/* -96 and int turns the character to its integer value. a=1,b=2,c=3....*/
	col1 = (char)(i%8 + 1 + 96);
	row1 = (63+i%8+1-i)/8;
	
	for(j=0; j<=63; j++)
	{

		col2 = (char)(j%8 + 1 + 96);
		row2 = (63+j%8+1-j)/8;
		
		/*Calls the correct function considering the chess piece. If an enemy*/
		/*piece can move to the kings location that means check*/
		switch(board[j])
		{
			
		case 'R': if(isRookMovable(board,col2,row2,col1,row1)==1)
						return 2; break;
		
		case 'N': if(isKnightMovable(board,col2,row2,col1,row1)==1)
				  		return 2; break;
		
		case 'B': if(isBishopMovable(board,col2,row2,col1,row1)==1)
						return 2; break;
		
		case 'Q': if(isQueenMovable(board,col2,row2,col1,row1)==1)
						return 2; break;

		case 'K': if(isKingMovable(board,col2,row2,col1,row1)==1) 
						return 2; break;

		case 'P': if(isPawnMovable(board,col2,row2,col1,row1)==1)
						return 2; break;

		}
	}
	/*Same algorithm but for white king*/
	for(i=0; board[i] != 'K' && i<=63; i++){}
			
	col1 = (char)(i%8 + 1 + 96);
	row1 = (63+i%8+1-i)/8;

	for(j=0; j<=63; j++)
	{

		col2 = (char)(j%8 + 1 + 96);
		row2 = (63+j%8+1-j)/8;
		
		
		switch(board[j])
		{
			
		case 'r': if(isRookMovable(board,col2,row2,col1,row1)==1)
						return 1; break;
		
		case 'n': if(isKnightMovable(board,col2,row2,col1,row1)==1)
				  		return 1; break;
		
		case 'b': if(isBishopMovable(board,col2,row2,col1,row1)==1)
						return 1; break;
		
		case 'q': if(isQueenMovable(board,col2,row2,col1,row1)==1)
						return 1; break;

		case 'k': if(isKingMovable(board,col2,row2,col1,row1)==1) 
						return 1; break;

		case 'p': if(isPawnMovable(board,col2,row2,col1,row1)==1)
						return 1; break;

		}
	}

return 0;	


}

int isPieceMovable(char *board, char sc, int sr, char tc, int tr){

int cell;

	/* -96 and int turns the character to its integer value. a=1,b=2,c=3....*/	
	cell = 63+((int)sc-96)-(sr*8);
	
	
	switch(board[cell])
		{
		case 'r': return isRookMovable(board,sc,sr,tc,tr); 
		
		case 'R': return isRookMovable(board,sc,sr,tc,tr); 

		case 'n': return isKnightMovable(board,sc,sr,tc,tr); 

		case 'N': return isKnightMovable(board,sc,sr,tc,tr); 

		case 'b': return isBishopMovable(board,sc,sr,tc,tr);

		case 'B': return isBishopMovable(board,sc,sr,tc,tr); 

		case 'q': return isQueenMovable(board,sc,sr,tc,tr); 

		case 'Q': return isQueenMovable(board,sc,sr,tc,tr); 

		case 'K': return isKingMovable(board,sc,sr,tc,tr); 

		case 'k': return isKingMovable(board,sc,sr,tc,tr); 

		case 'p': return isPawnMovable(board,sc,sr,tc,tr); 
		
		case 'P': return isPawnMovable(board,sc,sr,tc,tr); 

		default :  return 0;
		}

}

int makeMove(char *board, char sc, int sr, char tc, int tr){

int cell1,cell2;
char temp1,temp2;
	/* -96 and int turns the character to its integer value. a=1,b=2,c=3....*/
	cell1 = 63+((int)sc-96)-(sr*8);	
	cell2 = 63+((int)tc-96)-(tr*8);

	if(isPieceMovable(board,sc,sr,tc,tr))
	{
		/*If the piece can move makes the move but stores the locations before*/
		/*the move.*/
		temp2 = board[cell2];
		temp1 = board[cell1];
		board[cell2] = board[cell1];
		board[cell1] = ' ';
		
		/*If the player is white and white king is check after the move*/
		/*recalls pieces to their source locations and returns1 */ 
		if(isInCheck(board)==1 && isWhite(temp1)==1){
			board[cell1]=temp1;
			board[cell2]=temp2;
			return 1;
		 }
		
		/*If the player is black and black king is check after the move*/
		/*recalls pieces to their source locations and returns1 */ 
		if(isInCheck(board)==2 && isBlack(temp1)==1){
			board[cell1]=temp1;
			board[cell2]=temp2;
			return 1;
		 }

		/*If the white king is in check and player is black returns 3*/
		if(isInCheck(board)==1 && isWhite(temp1)==0)
			return 3;

		/*If the black king is in check and player is white returns 3*/
		if(isInCheck(board)==2 && isBlack(temp1)==0)
			return 3;	

		/*If there is no check and move is valid, returns 2*/
		return 2;
	 
	}
	/*If move is not valid returns 0*/
	return 0;
}

char getPlayer(char *board, char sc, int sr){

char player;
int cell;

	cell = 63+((int)sc-96)-(sr*8);
	player = board[cell];

return player;
} 

int isBlack(char currPlayer){

	if(currPlayer == 'r' ||
   	   currPlayer == 'n' ||
   	   currPlayer == 'b' ||
   	   currPlayer == 'q' ||
   	   currPlayer == 'k' ||
   	   currPlayer == 'p' )

		return 1;

else 

		return 0;
}

int isWhite(char currPlayer){

	if(currPlayer == 'R' ||
   	   currPlayer == 'N' ||
   	   currPlayer == 'B' ||
   	   currPlayer == 'Q' ||
   	   currPlayer == 'K' ||
   	   currPlayer == 'P' )

		return 1;

else 

		return 0;
}

void initBoard(char board[]){
int i;
board[0] = 'r';
board[1] = 'n';
board[2] = 'b';
board[3] = 'q';
board[4] = 'k';
board[5] = 'b';
board[6] = 'n';
board[7] = 'r';

for(i=8; i<=15; i++)
	board[i]= 'p';

for(i=16; i<=47; i++)
	board[i] = ' ';
for(i=48; i<=55; i++)
	board[i] = 'P';
board[56] = 'R';
board[57] = 'N';
board[58] = 'B';
board[59] = 'Q';
board[60] = 'K';
board[61] = 'B';
board[62] = 'N';
board[63] = 'R';

}

void printBoard(char *board){

int i,j=8;
	/*First row*/
	printf("  a b c d e f g h\n  - - - - - - - -\n");
	
	for(i=0; i<64; i++)   {
		if(i%8 == 0 && j>0){
			printf("%d|",j);
			j--;           }
		
		printf("%c",board[i]);
		
		if(i%8 == 7 && i>0)
			printf("|\n");
		else
			printf(" ");  }		
		/*Last row*/
		printf("  - - - - - - - -\n");

}
void getPosition(char *col, int *row){

	scanf("%c%d", col,row);
	
}
int isValidCell(char col, int row){

int valid=0;

if(col>='a' && col<='h' && row >=1 && row <=8)
valid = 1;

return valid;
}

int isRookMovable(char *board, char sourceCol, int sourceRow, char targetCol,
				  int targetRow){

	int i,col1,col2,cell1,cell2;

	col1= (int)sourceCol-96;
	col2= (int)targetCol-96;
	cell1 = 63+col1-(sourceRow*8);
	cell2 = 63+col2-(targetRow*8);
	
	/*The if statements below checks if a rook changed only row or column. */
	/*Then depending on the situation checks the cells inbetween source and */
	/*target and checks if the target cell has a friendly piece in it.*/
	/*Don't forget that moving 1 row means -8 or +8 in array locations*/
	
	if(sourceCol != targetCol)
	{	
		if(sourceRow != targetRow)
			return 0;
		else{
			if(cell1<cell2)
			for(i=cell1+1; i<cell2; i++){
				if(board[i] != ' ')
					return 0;           }
			if(cell1>cell2)
			for(i=cell1-1; i>cell2; i--){
				if(board[i] != ' ')
					return 0;           }  
			
			if(board[cell1]=='r'){
				if(board[cell2] == 'r' ||
				   board[cell2] == 'n' ||
				   board[cell2] == 'b' ||
				   board[cell2] == 'q' ||
				   board[cell2] == 'k' ||
				   board[cell2] == 'p'
				  )
					return 0;   }
			
			if(board[cell1]== 'R') {	   
				if(board[cell2] == 'R' ||
				   board[cell2] == 'N' ||
				   board[cell2] == 'B' ||
				   board[cell2] == 'Q' ||
				   board[cell2] == 'K' ||
				   board[cell2] == 'P'
				  )
					return 0;      }

			}
	}
    if(sourceRow != targetRow)
	{  
		if(sourceCol != targetCol){ 
			return 0;             }
		
		
			if(cell1>cell2)
			for(i=cell1-8; i>cell2; i=i-8){ 
				if(board[i] != ' ')
					return 0;             }
			if(cell2>cell1)
			for(i=cell1+8; i<cell2; i=i+8){ 
				if(board[i] != ' ')
					return 0;             }
			
			if(board[cell1]=='r'){
				if(board[cell2] == 'r' ||
				   board[cell2] == 'n' ||
				   board[cell2] == 'b' ||
				   board[cell2] == 'q' ||
				   board[cell2] == 'k' ||
				   board[cell2] == 'p'
				  ){
					return 0;   }
				   }
			if(board[cell1]== 'R') {	   
				if(board[cell2] == 'R' ||
				   board[cell2] == 'N' ||
				   board[cell2] == 'B' ||
				   board[cell2] == 'Q' ||
				   board[cell2] == 'K' ||
				   board[cell2] == 'P'
				  ){
					return 0;      }}
			
	}
			
	if(cell1==cell2)
		return 0;

return 1;						}


int isKnightMovable(char *board, char sourceCol, int sourceRow, char targetCol,
				    int targetRow){

	int col1,col2,cell1,cell2;

	col1= (int)sourceCol-96;
	col2= (int)targetCol-96;
	cell1 = 63+col1-(sourceRow*8);
	cell2 = 63+col2-(targetRow*8);
	
			if(cell1 == cell2)
				return 0;			
	
			if(board[cell1]=='n'){
				if(board[cell2] == 'r' ||
				   board[cell2] == 'n' ||
				   board[cell2] == 'b' ||
				   board[cell2] == 'q' ||
				   board[cell2] == 'k' ||
				   board[cell2] == 'p'
				  )
				return 0;   }
			
			if(board[cell1]== 'N') {	   
				if(board[cell2] == 'R' ||
				   board[cell2] == 'N' ||
				   board[cell2] == 'B' ||
				   board[cell2] == 'Q' ||
				   board[cell2] == 'K' ||
				   board[cell2] == 'P'
				  )
				return 0;      }
		
	/*The knight can move up to 8 locations depending on where it is. This */
    /*function checks it one by one.*/
			if(cell2 == 63+col1+2-((sourceRow-1)*8) ||
			   cell2 == 63+col1-2-((sourceRow-1)*8) ||
			   cell2 == 63+col1-2-((sourceRow+1)*8) ||
			   cell2 == 63+col1+2-((sourceRow+1)*8) ||
			   cell2 == 63+col1+1-((sourceRow-2)*8) ||
			   cell2 == 63+col1-1-((sourceRow-2)*8) ||
			   cell2 == 63+col1+1-((sourceRow+2)*8) ||
			   cell2 == 63+col1-1-((sourceRow+2)*8)
			  )
				return 1;

			else
				return 0;
}

int isBishopMovable(char *board, char sourceCol, int sourceRow, char targetCol,
				    int targetRow){

	int i,col1,col2,cell1,cell2,colDiff,rowDiff;

	col1= (int)sourceCol-96;
	col2= (int)targetCol-96;
	cell1 = 63+col1-(sourceRow*8);
	cell2 = 63+col2-(targetRow*8);
	colDiff = abs(col1-col2);
	rowDiff = abs(sourceRow-targetRow);

			/*Since bishops move in a diagonal way the row and column */
            /*difference should be equal. Also it only moves in the multiples*/
            /*of 7, 9, -7 and -9 in our array*/

			if(colDiff != rowDiff)
				return 0;

			if(cell1 == cell2)
				return 0;
	
			if(board[cell1]=='b'){
				if(board[cell2] == 'r' ||
				   board[cell2] == 'n' ||
				   board[cell2] == 'b' ||
				   board[cell2] == 'q' ||
				   board[cell2] == 'k' ||
				   board[cell2] == 'p'
				  )
				return 0;   }
			
			if(board[cell1]== 'B') {	   
				if(board[cell2] == 'R' ||
				   board[cell2] == 'N' ||
				   board[cell2] == 'B' ||
				   board[cell2] == 'Q' ||
				   board[cell2] == 'K' ||
				   board[cell2] == 'P'
				  )
				return 0;      }	

			if(col1<col2 && sourceRow < targetRow)
				for(i=cell1-8+1; i>cell2; i=i-8+1){
					if(board[i] != ' ')
						return 0;                 }

			if(col1<col2 && sourceRow > targetRow)
				for(i=cell1+8+1; i<cell2; i=i+8+1){
					if(board[i] != ' ')
						return 0;                 }

			if(col1>col2 && sourceRow > targetRow)
				for(i=cell1+8-1; i<cell2; i=i+8-1){
					if(board[i] != ' ')
						return 0;                 }

			if(col1>col2 && sourceRow < targetRow)
				for(i=cell1-8-1; i<cell2; i=i-8-1){
					if(board[i] != ' ')
						return 0;                 }


	return 1;

}

int isQueenMovable(char *board, char sourceCol, int sourceRow, char targetCol,
				   int targetRow){

	int col1,col2,cell1,cell2;

	col1= (int)sourceCol-96;
	col2= (int)targetCol-96;
	cell1 = 63+col1-(sourceRow*8);
	cell2 = 63+col2-(targetRow*8);
			
			/*Depending on the move the queen makes it can be considered same */
			/*as rook or bishop. So after checking the target location we call*/
			/*those functions depending on the move queen is making.*/
			
			if(board[cell1]=='q'){
				if(board[cell2] == 'r' ||
				   board[cell2] == 'n' ||
				   board[cell2] == 'b' ||
				   board[cell2] == 'q' ||
				   board[cell2] == 'k' ||
				   board[cell2] == 'p'
				  )
				return 0;   }
			
			if(board[cell1]== 'Q') {	   
				if(board[cell2] == 'R' ||
				   board[cell2] == 'N' ||
				   board[cell2] == 'B' ||
				   board[cell2] == 'Q' ||
				   board[cell2] == 'K' ||
				   board[cell2] == 'P'
				  )
				return 0;      }	

			if(sourceCol != targetCol && sourceRow != targetRow)
				return isBishopMovable(board,sourceCol,sourceRow,targetCol,
									   targetRow); 
			if(sourceCol != targetCol && sourceRow == targetRow)
				return isRookMovable(board,sourceCol,sourceRow,targetCol,
									 targetRow); 
	
			if(sourceCol == targetCol && sourceRow != targetRow)
				return isRookMovable(board,sourceCol,sourceRow,targetCol,
									 targetRow);

			if(sourceCol == targetCol && sourceRow == targetRow)
				return 0;

return 0;
}
			
int isKingMovable(char *board, char sourceCol, int sourceRow, char targetCol,
				  int targetRow){

	int col1,col2,cell1,cell2,colDiff,rowDiff;

	col1= (int)sourceCol-96;
	col2= (int)targetCol-96;
	cell1 = 63+col1-(sourceRow*8);
	cell2 = 63+col2-(targetRow*8);
	colDiff = abs(col1-col2);
	rowDiff = abs(sourceRow-targetRow);
			
			if(cell1 == cell2)
				return 0;

			if(board[cell1]=='k'){
				if(board[cell2] == 'r' ||
				   board[cell2] == 'n' ||
				   board[cell2] == 'b' ||
				   board[cell2] == 'q' ||
				   board[cell2] == 'k' ||
				   board[cell2] == 'p'
				  )
				return 0;   }
			
			if(board[cell1]== 'K') {	   
				if(board[cell2] == 'R' ||
				   board[cell2] == 'N' ||
				   board[cell2] == 'B' ||
				   board[cell2] == 'Q' ||
				   board[cell2] == 'K' ||
				   board[cell2] == 'P'
				  )
				return 0;      }	
			/*King can only move 1 cell*/
			if(colDiff >1 || rowDiff > 1)
				return 0;

	return 1;

}

int isPawnMovable(char *board, char sourceCol, int sourceRow, char targetCol,
				  int targetRow){

	
	int col1,col2,cell1,cell2,colDiff,rowDiff;

	col1= (int)sourceCol-96;
	col2= (int)targetCol-96;
	cell1 = 63+col1-(sourceRow*8);
	cell2 = 63+col2-(targetRow*8);
	colDiff = abs(col2-col1);
	rowDiff = targetRow-sourceRow;


			if(cell1 == cell2)
				return 0;

			/*Pawns can not move backwards and they can only move 1 cell. */
            /*But don't forget that they can move in a diagonal way if there */
            /*is an enemy at its cross*/
			if(colDiff >1 || (rowDiff != 1 && rowDiff != -1))
				return 0;

			if(board[cell1]=='p'){
				if(board[cell2] == 'r' ||
				   board[cell2] == 'n' ||
				   board[cell2] == 'b' ||
				   board[cell2] == 'q' ||
				   board[cell2] == 'k' ||
				   board[cell2] == 'p' ||
				   rowDiff != -1 
				  )
				
				return 0;   }
			
			if(board[cell1]== 'P') {	   
				if(board[cell2] == 'R' ||
				   board[cell2] == 'N' ||
				   board[cell2] == 'B' ||
				   board[cell2] == 'Q' ||
				   board[cell2] == 'K' ||
				   board[cell2] == 'P' ||
				   rowDiff != 1
				  )
				return 0;      }

			
				if(colDiff > 1)
					return 0;				
				if(colDiff == 1 && (rowDiff == 1 && rowDiff == -1)){ 
					if(board[cell1]=='p'){
						if(board[cell2] == 'R' ||
				   		   board[cell2] == 'N' ||
				   		   board[cell2] == 'B' ||
				   		   board[cell2] == 'Q' ||
				   	       board[cell2] == 'K' ||
				   		   board[cell2] == 'P'
				  		  )
						  	return 1;    }
						else 
							return 0;
					if(board[cell1]=='P'){
						if(board[cell2] == 'r' ||
				   		   board[cell2] == 'n' ||
				   		   board[cell2] == 'b' ||
				   		   board[cell2] == 'q' ||
				   		   board[cell2] == 'k' ||
				   		   board[cell2] == 'p'
				  		  )
							return 1;    }
						else 
							return 0;
											   }
		
				
				if(colDiff == 0){
					
					if(board[cell2] != ' ')
						
						return 0; }	


return 1;

}

