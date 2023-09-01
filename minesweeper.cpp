#include<bits/stdc++.h>
#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;

int mines;
int side;
int moves;
int moveCount=1;

bool isValid(int row,int col){
	 return row>=0 && row<side && col>=0 && col<side;
	}

bool isMine(vector<vector<char>> &board, int row,int col){
	if(board[row][col]=='*') return true;
	return false;
	}
	
void printBoard(vector<vector<char>> &board){
	cout<<endl<<endl<<endl;
	cout<<"     MOVES LEFT: "<<moves<<endl<<endl;
	cout<<"     ";
	for(int i=1;i<=side;i++){
		if(i<10) cout<<"0"<<i<<" ";
		else cout<<i<<" ";
		if(i==side) cout<<endl;
		}
	int ind=1;
	for(int row=0;row<side;row++){
		if(row<9) cout<<"   "<<"0"<<ind++<<" ";
        	else cout<<"   "<<ind++<<" ";
        	for(int col=0;col<side;col++){
        		if(col>9) cout<<board[row][col]<<"  ";
        		else cout<<board[row][col]<<"  ";
        			}
       	 cout<<endl;
    		}
    	cout<<endl<<endl<<endl;
	}
					
void setDimensions(int level, vector<vector<char>> &board, vector<vector<char>> &mineBoard){
	if(level==1){
		mines=10;
		side=9;
		}
	else if(level==2){
		mines=40;
		side=16;
		}
	else if(level==3){
		mines=99;
		side=24;
		}
	else{
		cout<<"   INVALID CHOICE\n\n";
		return;
		}
	board=vector<vector<char>>(side,vector<char>(side,'-'));
	mineBoard=vector<vector<char>>(side,vector<char>(side,'-'));
	return;
	}
	
void setMines(vector<vector<char>> &board){
	srand(time(0));
	while(mines!=0){
		int random=rand()%(side*side);
		int row=random/side;
		int col=random%side;
		if(board[row][col]!='*'){
			board[row][col]='*';
			mines--;
			}
		}
	return;
	}

void countAdjacentMines(vector<vector<char>> &board){
	for(int row=0;row<side;row++){
		for(int col=0;col<side;col++){
			if(board[row][col]!='*'){
				int count=0;
				for(int i=-1;i<=1;i++){
					for(int j=-1;j<=1;j++){
						int r=row+i;
						int c=col+j;
						if(isValid(r,c) && board[r][c]=='*') count++;
						}
					}
				board[row][col]=count +'0';
				}
			}
		}
	return;
	}

void replaceMine(vector<vector<char>> &board, vector<vector<char>> &mineBoard,int row,int col){
	mineBoard[row][col]='-';
	board[row][col]='-';
	int r,c;
	do{
		int random=rand()%(side*side);
		r=random/side;
		c=random%side;
		}while(board[r][c]!='*');
	board[r][c]='*';
	mineBoard[r][c]='*';
	countAdjacentMines(board);
	}

bool playMinesweeper(vector<vector<char>> &board,vector<vector<char>> &mineBoard, int row, int col){
	if(mineBoard[row][col]!='-' || mineBoard[row][col]=='*') return false;
	
	if(board[row][col]=='*' && moveCount==1){
		replaceMine(board,mineBoard,row,col);
		return false;
		}
		
	else if(board[row][col]=='*'){
		mineBoard[row][col]='*';
		for(int i=0;i<side;i++){
			for(int j=0;j<side;j++){
				if(board[i][j]=='*') mineBoard[i][j]='*';
				}
			}
		moves--;
		printBoard(mineBoard);
		cout<<"   YOU STEPPED ON A MINE :(\n\n";
		cout<<"   YOU LOST, TRY AGAIN NEXT TIME :)\n\n";
		return true;
		}
	else{
		mineBoard[row][col]=board[row][col];
		moves=moves-1;
		if(board[row][col]=='0'){
			for(int i=-1;i<=1;i++){
				for(int j=-1;j<=1;j++){
					int r=row+i;
					int c=col+j;
					if(isValid(r,c) && !isMine(board,r,c)) mineBoard[r][c]=board[r][c];
					}
				}
			}
		return false;
		}
	}

void play(int level, vector<vector<char>> &board, vector<vector<char>> &mineBoard){
	setDimensions(level,board,mineBoard);
	setMines(board);
	countAdjacentMines(board);
	//moves=(side*side)-mines;
	moves=5;
	printBoard(mineBoard);
	while(true){
		int row,col;
		cout<<"   MAKE YOUR MOVE\n\n";
		cout<<"   ENTER ROW: ";cin>>row;
		cout<<"   ENTER COLUMN: ";cin>>col;
		if(!isValid(row-1,col-1)){
			cout<<"   INVALID MOVE, TRY AGAIN :)\n\n\n";
			continue;
			}
		if(mineBoard[row-1][col-1]!='-' && board[row-1][col-1]!='*'){
			cout<<endl<<endl<<"   ALREADY REVEALED, TRY AGAIN :)\n\n\n";
			continue;
			}
		if(moves==1){
			moves--;
			for(int i=0;i<side;i++){
				for(int j=0;j<side;j++){
					if(board[i][j]=='*') mineBoard[i][j]='*';
					}
				}
			printBoard(mineBoard);
			cout<<"   YOU ARE OUT OF MOVES :(\n\n";
			cout<<"   YOU LOST, TRY AGAIN NEXT TIME :)\n\n";
			return;
			}
		if(playMinesweeper(board,mineBoard,row-1,col-1)){
			return;
			}
		else if(!playMinesweeper(board,mineBoard,row-1,col-1)){
			cout<<endl<<endl<<"   CURRENT BOARD STATUS"<<endl;
			printBoard(mineBoard);
			moveCount++;
			}
		}
	}
	
int main(){
	vector<vector<char>> board(1,vector<char>(1,'-'));
	vector<vector<char>> mineBoard(1,vector<char>(1,'-'));
	cout<<"\t\t\t\t\t<=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=>\n"<<endl;
	cout<<"\t\t\t\t\t|                              MINESWEEPER                              |\n"<<endl;
	cout<<"\t\t\t\t\t|                   Don't step on a mine accidentally :)                |\n"<<endl;
	cout<<"\t\t\t\t\t<=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=>\n"<<endl;
	int level;
	cout<<"   (1)EASY\n";
	cout<<"   (2)INTERMEDIATE\n";
	cout<<"   (3)HARD\n\n";
	cout<<"   CHOOSE DIFFICULTY LEVEL: ";cin>>level;
	play(level,board,mineBoard);	
	
	return 0;
	}
		
		
		
		
		
		
		
		
		
