#define BOLDRED     "\033[1m\033[31m"
#define BOLDYELLOW  "\033[1m\033[33m"
#define RESET   "\033[0m"

#include<vector>

using namespace std;
enum  OP { inicio=0, win=1,lose=2,valid=3,invalid=4,move_pawn=5,setting=6,msj=7,ini_juego=8 };
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
    string name;
    Game(int n,string f)
    {
        restart(n,f);
    }
    Game() {}
    void restart(int n,string f)
    {

        bsize=n;
        ficha =f;
        //enemy=(f=="x")?"o":"x";
        cout<<"iniciando tamaño "<<bsize<<endl;
        cout<<"iniciando board"<<endl;
        resize_board();
        cout<<"iniciando tablero "<<endl;
        initTablero();
    }
    void resize_board()
    {
        board.resize(bsize * bsize);//reservo n*n casilleros
        for(unsigned int  i=0; i<board.size(); i++) //reservo espacios para cada fila
            board[i].resize(bsize);
    }
    void initTablero()
    {
        //espacios para cuadrar el tablero
        for(int i=0; i < bsize; ++i)
        {
            for(int j = 0 ; j < bsize ; ++j)
            {
                board[i][j] = " ";
            }
        }
    }
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
    void printboard()
    {
        for(int i = 0 ; i < bsize ; ++i )
            printf(BOLDRED "%6d",i);
        printf("\n");
        printf("   ");
        for(int i = 0 ; i < bsize ; ++i)
            printf(BOLDYELLOW "------");
        printf("\n");

        for(int i = 0 ; i < bsize ; ++i)
        {
            printf(BOLDRED "%d",i);
            printf(BOLDYELLOW " |");

            for(int j =0 ; j < bsize ; ++j)
            {
                cout << "  " << board[i][j] << "  |";
            }

            printf("\n");
            printf(BOLDYELLOW "  |");

            for(int j = 0 ; j < bsize ; ++j)
            {
                printf("     |");
            }
            printf("\n");
            printf(BOLDYELLOW "  |");

            for(int j = 0 ; j < bsize ; ++j)
                printf("-----|");

            printf("\n");
        }
        printf(RESET);
        printf("\n\n");
    }


    bool is_valid(int x,int y,string fich=" ")
    {
        //cout<<"game::is_valid "<<x<< " "<<y<<" "<<fich<<endl;
        //cout<<board.size()<<endl;
        return is_coord_valid(x,y) && board[x][y]==fich;

    }
    bool is_coord_valid(int x,int y)
    {
        //cout<<"game::is_coord_valid "<<x<<" "<<y<<" "<<endl;
        //cout<<bsize<<endl;
        return x>=0 && x<=bsize && y>=0 && y<=bsize;
    }
};
