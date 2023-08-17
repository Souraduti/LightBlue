/***
   statically evaluates a position
   using matrial,piece activity,pawn structure
   return evaluation as a Double
   futur improvement : king safty,End game play 
   
***/
int s = 0;
int Queenmap[8][8]={{-1,0,0,0,0,0,0,-1},
					{-1,1,1,1,1,1,1,-1},
					{1,3,2,2,2,2,3,1},
					{1,2,4,5,5,4,2,1},
					{1,2,4,5,5,4,2,1},
					{1,3,2,2,2,2,3,1},
					{-1,1,1,1,1,1,1,-1},
					{-1,0,0,1,1,0,0,-1}
					};
int Kingmap[8][8]={
					{-2,-3,-3,-5,-5,-3,-3,-2},
					{-1,-2,-2,-4,-4,-2,-2,-1},
					{0,-1,-1,-2,-2,-1,-1,0},
					{0,0,0,-1,-1,0,0,0},
					{1,0,0,0,0,0,0,1},
					{1,0,0,0,0,0,0,1},
					{2,1,1,0,0,1,1,2},
					{3,4,2,1,1,2,4,3}
				};
					
int Rookmap[8][8]={
					{3,3,3,3,3,3,3,3},
					{4,4,4,5,5,4,4,4},
					{2,2,3,4,4,3,2,2},
					{1,2,2,2,2,2,2,1},
					{1,1,1,1,1,1,1,1},
					{0,1,1,1,1,1,1,0},
					{0,0,1,1,1,1,0,0},
					{0,0,1,2,2,1,0,0}
					};
int Bishopmap[8][8]={{-1,0,1,1,0,0,0,-1},
					{1,1,1,2,2,1,1,1},
					{3,1,2,1,1,2,1,3},
					{1,3,2,2,2,2,3,1},
					{1,2,4,5,5,4,2,1},
					{1,3,2,1,1,2,3,1},
					{-1,4,1,1,1,1,4,-1},
				{-1,-2,1,-1,-1,1,-2,-1}};
				
int Nightmap[8][8]={{0,0,0,0,0,0,0,0},
					{0,-1,1,1,1,1,-1,0},
					{1,2,4,4,4,4,2,1},
					{1,3,4,5,5,4,3,1},
					{1,2,3,5,5,3,3,1},
					{1,2,3,2,2,3,2,1},
					{0,0,1,2,2,1,0,0},
					{-3,-1,-1,-1,-1,-1,-1,-3}};
int Pawnmap[8][8]={ 
                    {10,10,10,10,10,10,10,10},
				    {2,2,2,2,2,2,2,2},
					{2,0,2,3,3,2,0,2},
					{0,0,2,4,4,2,0,0},
					{1,0,2,4,4,2,0,1},
					{2,2,0,0,0,0,2,2},
					{0,0,0,0,0,0,0,0},
					{0,0,0,0,0,0,0,0}
				};

					
inline int min(int i ,int j){
	return i<j?i:j;
}

double W_material(char board[9][9]){
	double e=0;
	for(int i = 1;i<=8;i++){
		for(int j=1;j<=8;j++){
			char p = board[i][j];
			switch(p){
				case 'K':e+=10000;break;
				case 'Q':e+=900;break;
				case 'R':e+=500;break;
				case 'B':e+=328;break;
				case 'N':e+=315;break;
				case 'P':e+=100;break;
			}
		}
	}
	return e;	
}
double B_material(char board[9][9]){
	double e=0;
	for(int i = 1;i<=8;i++){
		for(int j=1;j<=8;j++){
			char p = board[i][j];
			switch(p){	
				case 'k':e-=10000;break;
				case 'q':e-=900;break;
				case 'r':e-=500;break;
				case 'b':e-=328;break;
				case 'n':e-=315;break;
				case 'p':e-=100;break;
			}
		}
	}
	return e;	
}
double material(char board[9][9]){
	return W_material(board)+B_material(board);
}

double pawnStructure(char  board[9][9]){
	
	double e=0;
	for(int i=1;i<=8;i++ ){
		for(int j=1;j<=8;j++){
			if(board[i][j]=='P'){
				e+=(7-i)*4+min(j,8-j)*4*min(i,8-i);
			}else if(board[i][j]=='p'){
				e-=(i-2)*4+min(j,8-j)*4*min(i,8-i);
			}	
		}
	}
	int c1=0,c2=0;
	for(int j= 1;j<=8;j++){
		c1=0;c2=0;
		for(int i=1;i<=8;i++){
			if(board[i][j]=='P'){
				c1++;
			}else if(board[i][j]=='p'){
				c2++;
			}	
		}
	}
	if(c1>0) e-=(c1-1)*20;
	if(c2>0) e+=(c2-1)*20;
	return e;
}
double activity(char board[9][9]){
	
	double e=0;		
	for(int i=1;i<=8;i++){
		for(int j=1;j<=8;j++){
			char p=board[i][j];
			switch(p){	
				case 'K':e+=Kingmap[i-1][j-1]*10;break;
				case 'Q':e+=Queenmap[i-1][j-1]*3;break;
				case 'R':e+=Rookmap[i-1][j-1]*7;break;
				case 'B':e+=Bishopmap[i-1][j-1]*8;break;
				case 'N':e+=Nightmap[i-1][j-1]*10;break;
				case 'P':e+=Pawnmap[i-1][j-1]*7;break;
				
				case 'k':e-=Kingmap[8-i][j-1]*10;break;
				case 'q':e-=Queenmap[8-i][j-1]*3;break;
				case 'r':e-=Rookmap[8-i][j-1]*7;break;
				case 'b':e-=Bishopmap[8-i][j-1]*8;break;
				case 'n':e-=Nightmap[8-i][j-1]*10;break;
				case 'p':e-=Pawnmap[8-i][j-1]*7;break;
			}
		}
	}
	return e;
}
double staticEvaluation(char  board[9][9]){
	s++;	
	return 5*material(board)+2*activity(board)+pawnStructure(board);	
}
/*void serchedPosition(){
	cout<<s;
}*/


