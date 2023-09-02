/***
 t=1 represents white , t= -1 represents black
 play function return all possible legal moves with a given piece with starting square
 check,chekmate,stalemate function returns bool-ian result with respect to invoking 
 player colour
 
***/

///// Git 
const int offset[8][2]={{0,1},{0,-1},{1,0,},{-1,0},{1,1},{1,-1},{-1,1},{-1,-1}};
const int knoffset[8][2]={{2,1},{2,-1},{-2,1},{-2,-1},{1,2},{1,-2},{-1,2},{-1,-2}};
bool castling_flags[6] = {true,true,true,true,true,true};
int enpt_flags[2] = {0,0};

bool check(char board[9][9],int t){
	
	int r,f;
	char king=(t==1)?'K':'k';
	
	for(r=1;r<=8;r++){
		for(f=1;f<=8;f++){
			if(board[r][f]==king)
				goto out;	
		}
	}
	out:	
	for(int c=0;c<8;c++){
		int i=r,j=f,count=0;
		do{
			++count;
			i+=offset[c][0];
			j+=offset[c][1];	
		}while(inboard(i,j)&&board[i][j]=='.');
			
		if(!inboard(i,j)||sameside(king,board[i][j])) continue;
		
		char p=board[i][j];
		if(count==1&&(p=='K'||p=='k')) return true;
			
		if(p=='q'||p=='Q'){
			return true;
		}else if((p=='R'||p=='r')&&c<4){
			return true;
		}else if((p=='B'||p=='b')&&c>=4){
			return true;
		}	
	}
	
	for(int c=0;c<8;c++){
		int i,j;
		i=r+knoffset[c][0];
		j=f+knoffset[c][1];
		char kn=(t==1)?'n':'N';
		if(inboard(i,j)&&board[i][j]==kn)
			return true;	
	}		
	if(t==1){
		if(inboard(r-1,f-1)&&board[r-1][f-1]=='p')
			return true;
		if(inboard(r-1,f+1)&&board[r-1][f+1]=='p')
			return true;	
	}else{
		if(inboard(r+1,f-1)&&board[r+1][f-1]=='P')
			return true;
		if(inboard(r+1,f+1)&&board[r+1][f+1]=='P')
			return true;	
	}
	return false;
}
bool isplayable(char board[9][9],Move & x,int t){
	bool flag;
	char was = board[x.dest.rank][x.dest.file];
	board[x.dest.rank][x.dest.file]=board[x.source.rank][x.source.file];
	board[x.source.rank][x.source.file] = '.';
	
	flag = check(board,t);
	
	board[x.source.rank][x.source.file] = board[x.dest.rank][x.dest.file];
	board[x.dest.rank][x.dest.file] = was;
	
	return !flag;		
}

void knight(char board[9][9],char p,square & s,Movelist & v){
	square x;
	Move m;
	m.source=s;
	int t= (p=='N') ?1:0;	
	for(int c=0;c<8;c++){
		x.rank=s.rank+knoffset[c][0];
		x.file=s.file+knoffset[c][1];
		m.dest=x;
	if(inboard(x.rank,x.file)&&(!sameside(board[x.rank][x.file],p))&&(isplayable(board,m,t)))
		v.push_back(m);	
	}	
}
void king(char board[9][9],char p,square & s,Movelist & v){
	Move m;
	m.source=s;
	int t=(p=='K')?1:0;
	for(int c=0;c<8;c++){
		m.dest.rank=s.rank+offset[c][0];
		m.dest.file=s.file+offset[c][1];
	if(inboard(m.dest.rank,m.dest.file)&&(!sameside(board[m.dest.rank][m.dest.file],p))&&(isplayable(board,m,t)))
		v.push_back(m);				
	}	
}
void pawn(char board[9][9],char p,square & s,Movelist & v){
	int t;
	Move m;
	m.source=s;
	int k,home,last;
	if(p=='p'){
		k=1;home=2;t=0,last=8;
	}else{
		k=-1;home=7;t=1,last=1;
	}
		
	if(board[s.rank+k][s.file]=='.'){    
		m.dest.rank=s.rank+k;m.dest.file=s.file;
		if(isplayable(board,m,t)){
			v.push_back(m);
			if(m.dest.rank==last){
				v.pop_back();
				Move m1;
				m1=m;
				m1.prm='q'-t*32;v.push_back(m1);
				m1.prm='r'-t*32;v.push_back(m1);
				m1.prm='b'-t*32;v.push_back(m1);
				m1.prm='n'-t*32;v.push_back(m1);
			}
		}
	}
		
	if(s.rank==home&&board[s.rank+2*k][s.file]=='.'&&board[s.rank+k][s.file]=='.'){   
		m.dest.rank=s.rank+2*k;m.dest.file=s.file;
		if(isplayable(board,m,t)){
			v.push_back(m);
		}
	}
		
	if(inboard(s.rank+k,s.file+1)&&(opp(p,board[s.rank+k][s.file+1]))){	
		m.dest.rank=s.rank+k;m.dest.file=s.file+1;
		if(isplayable(board,m,t)){
			v.push_back(m);
			if(m.dest.rank==last){
				v.pop_back();
				Move m1;
				m1=m;
				m1.prm='q'-t*32;v.push_back(m1);
				m1.prm='r'-t*32;v.push_back(m1);
				m1.prm='b'-t*32;v.push_back(m1);
				m1.prm='n'-t*32;v.push_back(m1);
			}
		}
	}	
		
	if(inboard(s.rank+k,s.file-1)&&(opp(p,board[s.rank+k][s.file-1]))){ 
		m.dest.rank=s.rank+k;m.dest.file=s.file-1;
		if(isplayable(board,m,t)){
			v.push_back(m);
			if(m.dest.rank==last){
				v.pop_back();
				Move m1;
				m1=m;
				m1.prm='q'-t*32;v.push_back(m1);
				m1.prm='r'-t*32;v.push_back(m1);
				m1.prm='b'-t*32;v.push_back(m1);
				m1.prm='n'-t*32;v.push_back(m1);
			}
		}
	}	
}
bool castle(char board[9][9],int t,int side){
	char King,Rook;
	int edge,i;
	if(check(board,t)){
		return false;
	}
	if(t==1){
		if(!castling_flags[0]){	return false;}	
		King='K';Rook='R';
		edge=8;i=0;
	}else{
		if(!castling_flags[3]){return false;}		
		King='k';Rook='r';
		edge=1;i=3;
	}
					
	if(side==1){
		//short castle
		if(!castling_flags[i]||board[edge][8]!=Rook){
			return false;
		}
		
		if(board[edge][6]!='.'||board[edge][7]!='.'){
			return false;
		}
			
		board[edge][6]=King;
		board[edge][5]='.';
		if(check(board,t)){
			board[edge][6]='.';
			board[edge][5]=King;
			return false;
		}
		board[edge][7]=King;
		board[edge][6]='.';
		if(check(board,t)){
			board[edge][7]='.';
			board[edge][5]=King;
			return false;
		}
		board[edge][6]=Rook;
		board[edge][8]='.';
		castling_flags[i]=false;
		castling_flags[i+1]=false;
		return true;
	}else if(side==-1){
		//long castle
		if(!castling_flags[i+2]||board[edge][1]!=Rook)
			return false;
		if(board[edge][4]!='.'||board[edge][3]!='.')
			return false;
			
		board[edge][4]=King;
		board[edge][5]='.';
		if(check(board,t)){
			board[edge][4]='.';
			board[edge][5]=King;
			return false;
		}
		board[edge][3]=King;
		board[edge][6]='.';
		if(check(board,t)){
			board[edge][3]='.';
			board[edge][5]=King;
			return false;
		}
		
		board[edge][4]=Rook;
		board[edge][1]='.';
		castling_flags[i]=false;
		castling_flags[i+2]=false;
		return true;	
	}
	return false;
}
void play(char board[9][9],char p,square & s,Movelist & v){
	
	int l,h,i,j,t;
	Move m;
	m.source=s;
	t=('A'<=p&&p<='Z')?1:-1;
		
	if(p=='K'||p=='k'){
		king(board,p,s,v);
		return;	
	}
	if(p=='N'||p=='n'){	
		knight(board,p,s,v);
		return;
	}
	if(p=='P'||p=='p'){
		pawn(board,p,s,v);
		return;
	}else if(p=='R'||p=='r'){
		l=0;h=4;
	}else if(p=='B'||p=='b'){
		l=4;h=8;
	}else if(p=='Q'||p=='q'){
		l=0;h=8;
	}
	
	for(int c=l;c<h;c++){
		i=s.rank;j=s.file;
		while(true){
			i+=offset[c][0];
			j+=offset[c][1];
			if(!inboard(i,j))
				break;
			
			if(board[i][j]=='.'){
				m.dest.rank=i;m.dest.file=j;
				if(isplayable(board,m,t))
				v.push_back(m);
			}else if(opp(p,board[i][j])){			
				m.dest.rank=i;m.dest.file=j;
				if(isplayable(board,m,t))
				v.push_back(m);
				break;	
			}else {
				break;
			}
		}	
	}	
}

bool stalemate(char board[9][9],int t){

	char ch = (t==1)?'K':'k';
	Movelist v;
	square x;
	bool flag =true;	
	for(int i=1;i<=8;i++){
		for(int j=1;j<=8;j++){
			if(sameside(ch,board[i][j])){
				x.rank=i;x.file=j;
				play(board,board[i][j],x,v);
			
			for(int c=0;c<v.size();c++){
				
				x.rank=v[c].dest.rank;x.file=v[c].dest.file;
				
				char p=board[i][j],was=board[x.rank][x.file];
				board[x.rank][x.file]=p;
				board[i][j]='.';
				
				if(!check(board,t)){
					flag=false;
				}
				
				board[i][j] = p;
				board[x.rank][x.file] = was;
	
				if(!flag) return false;	
			}					
			}
		}	
	}
	return true;	
}
bool checkmate(char board[9][9],int t){
	return check(board,t)&&stalemate(board,t);	
}
void generate(char board[9][9],int t,Movelist & all){
	Move x;
	char c=(t==1)?'K':'k';
	for(int in =1;in<=8;in++){
		for(int j=1;j<=8;j++){
			int i = (t==1)?in:9-in;
			if(sameside(c,board[i][j])){
				x.source.rank=i;x.source.file=j;
				play(board,board[i][j],x.source,all);
			}
		}
	}
}
bool isGameEnded(char board [9][9],int t){
	if(checkmate(board,1)){
	  cout<<"Black Won"<<endl;
	  return true;	
	}
	if(checkmate(board,-1)){
	  cout<<"White Won"<<endl;
	  return true;	
	}
	if(stalemate(board,t)){
		cout<<"Draw By Stalemate";
		return true;
	}	
	return false;
}
void redo(char board [9][9],const Move & m){
	
	board[m.dest.rank][m.dest.file] = board[m.source.rank][m.source.file];
	board[m.source.rank][m.source.file] = '.';
	if(m.prm!='.'){
		board[m.dest.rank][m.dest.file] = m.prm;
	}
}
void undo(char board [9][9],const Move & m,char capt){
	
	board[m.source.rank][m.source.file] = board[m.dest.rank][m.dest.file];
	board[m.dest.rank][m.dest.file] = capt;
	if(sameside(m.prm,'K')){
		board[m.source.rank][m.source.file] = 'P';
	}else if(sameside(m.prm,'k')){
		board[m.source.rank][m.source.file] = 'p';
	}
}
