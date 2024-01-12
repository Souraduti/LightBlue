/***
   Runs mini-max algorithm with alpha beta pruning.
   future improvement : Transposition(Zobrist Hashing) ,Iterative deepining,
   arranging moves by liklihood 
   
   Computer can not play En-passant,Castling and unaware of draw by Repition
   
***/
#define MAXDEPTH 4
#define INF 1000000
string lastmove = "";
int evaluation(char board[9][9],int t,int depth,int alpha,int beta){
	
	if(depth==0){
		return  staticEvaluation(board);
	}
	if(checkmate(board,t)) return -t*(INF+depth*1000);
	if(stalemate(board,t)) return 0;	
	
	int eval,maxi=-INF,mini=INF;
	Movelist all;
	Move x;
	char c = (t==1)?'K':'k';
	
	generate(board,t,all);
	
	for(int i=0;i<all.size();i++){
		
		char was = board[all[i].dest.rank][all[i].dest.file];
		redo(board,all[i]);
		
		int eval = evaluation(board,-t,depth-1,alpha,beta);
		
		undo(board,all[i],was);
			
		if(t==1){
			maxi=max(eval,maxi);
			alpha=max(alpha,eval);
			if(beta<=alpha) break;
		}else{
			mini=min(mini,eval);
			beta=min(eval,beta);
			if(beta<=alpha) break;
		}
	}
	all.clear();
	return t==1?maxi:mini;
}
void computer(char board[9][9],int t){
	
	int index=0;
	char c= (t==1)?'K':'k';
	Move x;
	Movelist all;
	int maxi=-INF,mini = INF;
	
	if(checkmate(board,1)||checkmate(board,-1)||stalemate(board,t)){
	  return ;	
	}
	
	generate(board,t,all);
			
	for(int i=0;i<all.size();i++){
		char was= board[all[i].dest.rank][all[i].dest.file];
		redo(board,all[i]);
		
		double eval=evaluation(board,-t,MAXDEPTH,-INF,INF);
		
		undo(board,all[i],was);
	
		if(t==1&&eval>maxi){
			index=i;
			maxi = eval;
		}else if(t==-1&&eval<mini){
			index =i;
			mini = eval;
		}		
	}
	
	lastmove+= getPieceName(board[all[index].source.rank][all[index].source.file]);
	lastmove+=" from ";
	lastmove+=char(all[index].source.file+'a'-1);
	lastmove+=char('9'-all[index].source.rank);
	lastmove+=" to ";
	lastmove+=char(all[index].dest.file+'a'-1);
	lastmove+=char('9'-all[index].dest.rank);
	lastmove+="\n";
	
	redo(board,all[index]);
	all.clear();
	return ;	
}
string getMoveByComputer(){
	string str = lastmove;
	lastmove = "";
	return str;
}

