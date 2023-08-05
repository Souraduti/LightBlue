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
					{'1','r','n','b','q','k','b','n','r'},
					{'2','p','p','p','p','p','p','p','p'},
					{'3','.','.','.','.','.','.','.','P'},
					{'4','.','.','.','.','.','.','.','.'},
					{'5','.','.','.','.','.','.','.','.'},
					{'6','.','.','.','.','.','.','.','.'},
					{'7','P','P','P','P','P','P','P','P'},
					{'8','R','N','B','Q','K','B','N','R'}
				};
		
	
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
	display(board);
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
	}
	display(board);
	return 0;
}




	
	


	
	
	
	
	
	

	
	
	
	
	
	
	



