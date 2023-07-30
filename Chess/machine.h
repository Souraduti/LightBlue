/***
   Runs mini-max algorithm with alpha beta pruning.
   future improvement : Transposition(Zobrist Hashing) ,Iterative deepining,
   arranging moves by liklihood 
   
   Computer can not play En-passant,Castling and unaware of draw by Repition
   
***/
const int MAXDEPTH = 4;
const int INF = 10000000;
string lastmove = "";
double evaluation(char board[9][9],int t,int depth,double alpha,double beta){
	
	if(depth==0){
		return  staticEvaluation(board);
	}
	if(checkmate(board,t)) return -t*INF;
	if(stalemate(board,t)) return 0;	
	
	double eval,maxi=-INF,mini=INF;
	Movelist all;
	Move x;
	char c = (t==1)?'K':'k';
	
	generate(board,t,all);
	
	for(int i=0;i<all.size();i++){
		
		char was = board[all[i].dest.rank][all[i].dest.file];
		board[all[i].dest.rank][all[i].dest.file] =board[all[i].source.rank][all[i].source.file];
		board[all[i].source.rank][all[i].source.file] = '.';
		
		double eval = evaluation(board,-t,depth-1,alpha,beta);
		
		board[all[i].source.rank][all[i].source.file] = board[all[i].dest.rank][all[i].dest.file];
		board[all[i].dest.rank][all[i].dest.file] = was;
			
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
	double maxi=-INF,mini = INF;
	
	if(checkmate(board,1)||checkmate(board,-1)||stalemate(board,t)){
	  return ;	
	}
	
	generate(board,t,all);
			
	for(int i=0;i<all.size();i++){
		char was= board[all[i].dest.rank][all[i].dest.file];
		board[all[i].dest.rank][all[i].dest.file] = board[all[i].source.rank][all[i].source.file];
		board[all[i].source.rank][all[i].source.file] = '.';
		
		double eval=evaluation(board,-t,MAXDEPTH,-INF,INF);
		
		board[all[i].source.rank][all[i].source.file] = board[all[i].dest.rank][all[i].dest.file];
		board[all[i].dest.rank][all[i].dest.file] = was;
	
		if(t==1&&eval>maxi){
			index=i;
			maxi = eval;
		}else if(t==-1&&eval<mini){
			index =i;
			mini =eval;
		}		
	}
	
	lastmove+= getPieceName(board[all[index].source.rank][all[index].source.file]);
	lastmove+=" from ";
	lastmove+=char(48+all[index].source.rank);
	lastmove+=",";
	lastmove+=char(48+all[index].source.file);
	lastmove+=" to ";
	lastmove+=char(48+all[index].dest.rank);
	lastmove+=",";
	lastmove+=char(48+all[index].dest.file);
	
	board[all[index].dest.rank][all[index].dest.file]=board[all[index].source.rank][all[index].source.file];
	board[all[index].source.rank][all[index].source.file] = '.';
	
	// Auto promoting to Queen
	if(board[all[index].dest.rank][all[index].dest.file]=='p'&&all[index].dest.rank==8){
		board[all[index].dest.rank][all[index].dest.file]='q';
	}
	if(board[all[index].dest.rank][all[index].dest.file]=='P'&&all[index].dest.rank==1){
		board[all[index].dest.rank][all[index].dest.file]='Q';
	}
	all.clear();
	return ;	
}
string getMoveByComputer(){
	string str = lastmove;
	lastmove = "";
	return str;
}

