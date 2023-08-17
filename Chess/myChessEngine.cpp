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
					{'.','1','2','3','4','5','6','7','8'},
					{'1','r','n','b','q','k','b','n','r'},
					{'2','p','p','p','p','p','p','p','p'},
					{'3','.','.','.','.','.','.','.','.'},
					{'4','.','.','.','.','.','.','.','.'},
					{'5','.','.','.','.','.','.','.','.'},
					{'6','.','.','.','.','.','.','.','.'},
					{'7','P','P','P','P','P','P','P','P'},
					{'8','R','N','B','Q','K','B','N','R'}
				};
		
	
	set(board);
	display(board);
	while(true){
		cout<<"Play as \n"<<"1.White\n"<<"2.Black\n";
		cin>>choice;
		if(choice==1||choice==2) break;
	}
	
	while(c!=0){
		
		if(isGameEnded(board,1)) break;
		if(choice==1){
			while(!usermove(board,1));
		}else{
			computer(board,1);
			cout<<"\n"<<getMoveByComputer()<<"\n";
		}
		system("cls");
		display(board);
		
		if(isGameEnded(board,-1)) break;
		if(choice==1){
			computer(board,-1);
			cout<<"\n"<<getMoveByComputer()<<"\n";
		}else{
			while(!usermove(board,0));
		}
		
		system("cls");
		display(board);
		
		c--;
	}
	display(board);
	return 0;
}




	
	


	
	
	
	
	
	

	
	
	
	
	
	
	



