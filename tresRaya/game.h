#define RESET   "\033[0m"

#include<vector>

using namespace std;
enum  OP { inicio=0, win,lose,valid,invalid,move_pawn  };
enum dir {up=0,down,left,right,up_left,down_left,up_right,down_right};

//up down left right up-left down-right up-right down-left;

int direction[][2]= {{-1,0},{1,0},{0,-1},{0,1},{-1,-1},{1,1},{-1,1},{1,-1}};

class Game
{
public:
    int bsize;
    vector< vector< string > > board; // Matriz de posiciones de Comida.
    string ficha,enemy;
    int x,y;
    Game(int n,string f)
    {
        bsize=n;
        ficha =f;
        enemy=(f=="x")?"o":"x";
        board.resize(bsize * bsize);//reservo n*n casilleros
        for(unsigned int  i=0; i<board.size(); i++) //reservo espacios para cada fila
            board[i].resize(bsize);
        for(int i=0; i < bsize; ++i)
        {
            for(int j = 0 ; j < bsize ; ++j)
            {
                board[i][j] = " ";
            }
        }
    }
    Game() {}

    bool is_win(int t_x,int t_y)
    {
        int j=1;
        x=t_x;
        y=t_y;
        cout<<"mi ficha "<<ficha<<endl;

        for(int k=0; k<8; k++)
        {
            j=1;
            bool res =verify(direction[k][0],direction[k][1],j);
            if(res) return true;

        }
        
        return false;
    }
    bool verify(/*int caso,*/int xx,int yy,int & cont)
    {
        if(cont==3) return true;

        if(is_valid(x+xx,y+yy,ficha))//arriba
        {
            x=x+xx;
            y=y+yy;
            cont =cont+1;
            verify(xx,yy,cont);
        }
        else
            return false;
    }
    void print()
    {
        for(int i = 0 ; i < bsize ; ++i )
            printf( "%6d",i);
        printf("\n");
        printf("   ");
        for(int i = 0 ; i < bsize ; ++i)
            printf( "------");
        printf("\n");

        for(int i = 0 ; i < bsize ; ++i)
        {
            printf( "%d",i);
            printf( " |");

            for(int j =0 ; j < bsize ; ++j)
            {
                cout << "  " << board[i][j] << "  |";
            }

            printf("\n");
            printf( "  |");

            for(int j = 0 ; j < bsize ; ++j)
            {
                printf("     |");
            }
            printf("\n");
            printf( "  |");

            for(int j = 0 ; j < bsize ; ++j)
                printf("-----|");

            printf("\n");
        }
        printf(RESET);
        printf("\n\n");
    }


    bool is_valid(int x,int y,string fich=" ")
    {
        return is_coord_valid(x,y) && board[x][y]==fich;

    }
    bool is_coord_valid(int x,int y)
    {
        return x>=0 && x<=bsize && y>=0 && y<=bsize;
    }
};
