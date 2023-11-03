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
					{'1','.','r','b','.','k','b','.','r'},
					{'2','.','.','.','.','.','p','p','.'},
					{'3','p','.','.','p','.','.','.','p'},
					{'4','.','.','.','n','P','R','.','.'},
					{'5','.','.','.','.','P','.','.','.'},
					{'6','.','.','.','.','.','.','.','.'},
					{'7','P','q','P','.','N','.','P','P'},
					{'8','R','.','.','Q','.','.','.','K'}
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
	getchar();
	return 0;
}




	
	


	
	
	
	
	
	

	
	
	
	
	
	
	



