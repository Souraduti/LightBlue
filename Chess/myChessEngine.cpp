#include<iostream>
#include<string>
#include<stdlib.h>
#include<time.h>

#include "utilitis.h"
#include "Evaluation.h"
#include "moves.h"
#include "machine.h"
#include "usermoveinput.h"

using namespace std;

int main(){
	int c=1000;
	char board[9][9]={
				{'.','1','2','3','4','5','6','7','8'},
				{'1','.','.','.','.','.','.','k','.'},
				{'2','.','.','.','.','.','.','.','.'},
				{'3','.','.','.','.','.','.','.','P'},
				{'4','.','.','.','.','.','.','.','.'},
				{'5','.','.','.','.','N','.','.','.'},
				{'6','.','.','.','.','.','.','.','.'},
				{'7','r','q','.','.','.','.','.','.'},
				{'8','Q','.','.','.','.','.','.','K'}};
		
	
	/*set(board);
	display(board);
	clock_t start=clock();
	computer(board,1);
	clock_t end=clock();
	display(board);
	double elapsed=(end-start)*1000/CLOCKS_PER_SEC;
	cout<<elapsed<<" ms"<<endl;
	*/
	
	set(board);
	//usermove(board,1);
	//usermove(board,0);
	display(board);
	//computer(board,1);
	while(c!=0&&!isGameEnded(board)){
		while(!usermove(board,1));
		//computer(board,1);
		system("cls");
		display(board);
		computer(board,-1);
		system("cls");
		display(board);
		string last = getMoveByComputer();
		cout<<"\n"<<last<<"\n"<<endl;
		c--;
		//cin>>c;	
	}
	display(board);
	return 0;
}




	
	


	
	
	
	
	
	

	
	
	
	
	
	
	



