/***
   t=1 indicates White
   t=0 indicates Black
   
   takes move input from the user 
   checks if valid
   if valid modifies the board and return true else returns false
   
***/
bool usermove(char board[9][9],int t){
	char p;
	char pieces[] = "KQNRBPx";
	Move m;	
	Movelist v;
	if(check(board,t)){
		if(stalemate(board,t)){
			cout<<"Checkmate"<<endl;
			if(t==0)
				cout<<"White won"<<endl;
			else
			    cout<<"Black Won"<<endl;
			return true;
		}
		cout<<"-----CHECK-----"<<endl;
	}
	
	if(stalemate(board,t)){
		cout<<"-----Draw by Stalemate-----"<<endl;
		return true;
	}
	
	if(t==1){
		cout<<"White's turn\n";
	}else{
		cout<<"Black's trun\n";
	}
			
	cout<<"Piece: ";
	cin>>p;
	fflush(stdin);
	
	if(p=='0') exit(1);
		
	for(int i=0;i<=6;i++){
		if(pieces[i]=='x'){
		cout<<"Pice does not exist\n";
		return false;
		}else if(p==pieces[i]||p==pieces[i]+32){
			break;
		} 
	}
	
	if(t==0&&('A'<=p&&p<='Z'))
		p+=32;
	if(t==1&&('a'<=p&&p<='z'))
		p-=32;
		
	cout<<"from :";
	cin>>m.source.rank>>m.source.file;
	
	cout<<"to   :";
	cin>>m.dest.rank>>m.dest.file;
	fflush(stdin);
	
	if(!inboard(m.source.rank,m.source.file)||board[m.source.rank][m.source.file]!=p){
		cout<<"Invalid Move"<<endl;
		return false;
	}
	
	if(!inboard(m.dest.rank,m.dest.file)||sameside(p,board[m.dest.rank][m.dest.file])){
		cout<<"invalid Move"<<endl;
		return false;
	}

	if(p=='K'||p=='k'){
		//castling
		if(m.source.rank==m.dest.rank&&m.source.rank==7*t+1&&abs(m.dest.file-m.source.file)==2){
			if(castle(board,t,(m.dest.file-m.source.file)/2)){
				return true;
			}else{
				cout<<"invalid move";
				return false;
			}
		}
	}
		
	play(board,p,m.source,v);
	
	for(int i=0;i<v.size();i++){
	
		if(m.dest.rank!=v[i].dest.rank||m.dest.file!=v[i].dest.file)
			continue;
		if(!isplayable(board,m,t)){
			cout<<"You Will be in check"<<endl;
			return false;
		}
		
		board[m.source.rank][m.source.file]='.';
		board[m.dest.rank][m.dest.file]=p;
		
		//handeling En Passent
		bool pawn_capture=(m.source.file-m.dest.file)*(m.source.rank-m.dest.rank)!=0;
		if((p=='P'||p=='p')&&pawn_capture&&enpt_flags[1-t]==m.dest.file){
			board[m.source.rank][m.dest.file]='.';
		}
			
		if((p=='p'&&m.dest.rank==8)||(p=='P'&&m.dest.rank==1)){
			promote(board,m.dest.file,t);
		}
		enpt_flags[1-t]=0;
		if(p=='P'&&(m.source.rank-m.dest.rank)==2){
			enpt_flags[t]=m.source.file;
		}
		if(p=='p'&&(m.dest.rank-m.source.rank)==2){
			enpt_flags[t]=m.source.file;
		}
		//updating castling flags
		if(castling_flags[0]){
			
			if(p=='K'){
			castling_flags[0]=false;
			}else if((m.source.rank==8&&m.source.file==8)||(m.dest.rank==8&&m.dest.file==8)){
			castling_flags[1]=false;
			}else if((m.source.rank==8&&m.source.file==1)||(m.dest.rank==8&&m.dest.file==1)){
			castling_flags[2]=false;
			}
		}
		if(castling_flags[3]){
			
			if(p=='k'){
				castling_flags[3]=false;
			}else if((m.source.rank==1&&m.source.file==8)||(m.dest.rank==1&&m.dest.file==8)){
				castling_flags[4]=false;
			}else if((m.source.rank==1&&m.source.file==1)||(m.dest.rank==1&&m.dest.file==1)){
				castling_flags[5]=false;
			}
		}	
		return true;
	}
	cout<<"Invalid Move"<<endl;
	return false;
}
