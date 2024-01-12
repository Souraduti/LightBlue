#include<iostream>
#include<string>
#include<stdlib.h>

#include "utilitis.h"
#include "Evaluation.h"
#include "moves.h"
#include "machine.h"
#include "usermoveinput.h"

using namespace std;

int main(){
	int c=1000,choice=0;
	char board[9][9]={
					{'.','a','b','c','d','e','f','g','h'},
					{'8','.','r','b','.','k','b','.','r'},
					{'7','.','.','.','.','.','p','p','.'},
					{'6','p','.','.','p','.','.','.','p'},
					{'5','.','.','.','n','P','R','.','.'},
					{'4','.','.','.','.','P','.','.','.'},
					{'3','.','.','.','.','.','.','.','.'},
					{'2','P','q','P','.','N','.','P','P'},
					{'1','R','.','.','Q','.','.','.','K'}
				};
		
	display(board);
	while(true){
		cout<<"Play as \n"<<"1.White\n"<<"2.Black\n";
		cin>>choice;
		if(choice==1||choice==2) break;
	}
	system("cls");
	set(board);
	display(board);
	
	
	while(c!=0){
		
		if(isGameEnded(board,1)) break;
		if(choice==1){
			while(!usermove(board,1));
			system("cls");
			display(board);
		}else{
			computer(board,1);
			system("cls");
			display(board);
			cout<<"\n"<<getMoveByComputer()<<"\n";
		}
		
		if(isGameEnded(board,-1)) break;
		if(choice==1){
			computer(board,-1);
			system("cls");
			display(board);
			cout<<"\n"<<getMoveByComputer()<<"\n";
		}else{
			while(!usermove(board,0));
			system("cls");
			display(board);
		}
		
		c--;
	}
	display(board);
	getchar();
	return 0;
}