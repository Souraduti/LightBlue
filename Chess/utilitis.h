using namespace std;
struct square{
	int file,rank;
	square(){}
	square(int i,int j){
		rank=i;
		file=j;
	}
};
struct Move{
	square source,dest;
};
class Movelist{
	Move * moves;
	int s;
public:
	Movelist(){
		moves = new Move[100];
		s=0;
	}
	void push_back(const Move & m){
		moves[s] = m;
		++s;
	}
	void pop_back(){
		--s;
	}
	int size(){
		return s;
	}
	Move operator[](int i){
		if(i>=s){
			std::cout<<"Array Index out of Bound"<<std::endl;
			exit(1);
		}
		return moves[i];
	}
	void clear(){
		delete [] moves;
		s=0;
	}
};
inline bool inboard(int i,int j){
	if(i>8||j>8)
		return false;
	if(i<1||j<1)
		return false;
	return true;
}
void display(char board[9][9]){
	std::cout<<"\n\n\n";
	for(int i=0;i<=8;i++){
		std::cout<<"         ";
		for(int j=0;j<=8;j++){
			std::cout<<board[i][j]<<" ";
		}
		std::cout<<std::endl;
	}
}
inline bool opp(char  q,char p){	
	if(('A'<=q&&q<='Z')&&('a'<=p&&p<='z'))
		return true;
	if(('a'<=q&&q<='z')&&('A'<=p&&p<='Z'))
		return true;	
	return false;
}
inline bool sameside(char q,char p){	
	if(('A'<=q&&q<='Z')&&('A'<=p&&p<='Z'))
		return true;
	if(('a'<=q&&q<='z')&&('a'<=p&&p<='z'))
		return true;	
	return false;
}
void promote(char board[9][9],int j,int t){
	char str[]="#QRBN";
	int c=5;
	std::cout<<"Promote to :---"<<std::endl;
	std::cout<<"1 for Queen"<<std::endl;
	std::cout<<"2 for Rook "<<std::endl;
	std::cout<<"3 for Bishop"<<std::endl;
	std::cout<<"4 for Knight"<<std::endl;
	do{
		std::cout<<"Your Choice : ";
		scanf("%d",&c);
		fflush(stdin);
	}while(c<=0||c>4);
	
	if(t==1){
		board[1][j]=str[c];
	}else{
		board[8][j]=str[c]+32;
	}	
}

void set(char board[9][9]){
	
	for(int i=3;i<=6;i++){
		for(int j=1;j<=8;j++){
			board[i][j]='.';
		}
	}
	
	board[1][1]='r';
	board[1][8]='r';
	board[1][2]='n';
	board[1][7]='n';
	board[1][3]='b';
	board[1][6]='b';
	board[1][4]='q';
	board[1][5]='k';
	
	board[8][1]='R';
	board[8][8]='R';
	board[8][2]='N';
	board[8][7]='N';
	board[8][3]='B';
	board[8][6]='B';
	board[8][4]='Q';
	board[8][5]='K';
	
	for(int i=1;i<=8;i++){
		board[2][i]='p';
		board[7][i]='P';
	}
}
int getPieceValue(char p){
	switch(p){
		case 'k':
		case 'K':return 1000000;
		case 'q':
		case 'Q':return 900;
		case 'r':
		case 'R':return 510;
		case 'B':
		case 'b':return 320;
		case 'n':
		case 'N':return 300;
		case 'p':
		case 'P':return 100;
		default :return 0;
	}
}
string getPieceName(char p){
	switch(p){
		case 'k':
		case 'K':return "King";
		case 'q':
		case 'Q':return "Queen";
		case 'r':
		case 'R':return "Rook";
		case 'B':
		case 'b':return "Bishop";
		case 'n':
		case 'N':return "Night";
		case 'p':
		case 'P':return "pawn";
		default :return " ";
	}
}


