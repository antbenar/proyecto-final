#include "Tablero.h"
#include "Lista.h"
#include "Lista.cpp"

using namespace std;

//Constructor de Tablero en blanco
Tablero::Tablero()
{
	playerInTurn = 1;
	for(int i=0; i<6; i++){
		for(int j=0; j<7; j++){
					map[i][j]=0;
		}
}
}


int Tablero::getPlayer()
{
	return playerInTurn;
}


//Revisa si queda espacio en la columna
bool Tablero::columnFull(int columna)
{
    if(map[0][columna]!=0)
        return true;
    return false;

}

//Buscar el primer espacio disponible
int Tablero::searchFila(int columna)
{
	for(int fila=6; fila>=0; fila--)
	{
		if(map[fila][columna]==0)
			return fila;
	}
	return 0;
}


//Insertar la ficha del jugador
void Tablero::addFicha(int columna)
{
	    map[searchFila(columna-1)][columna-1]= playerInTurn;
	    changePlayer();
}


//Es el turno del otro jugador
void Tablero::changePlayer()
{
	if(playerInTurn==1)
		playerInTurn=2;
	else
		playerInTurn=1;
}

//Función auxiliar que busca en todas las direcciones
bool Tablero::searchLine(int direction, int i, int j){
    int posy = i;
	int posx = j;
	bool Vali1 = true;
	bool Vali2 = true;
	Lista<int> path;
	path.add_head(posy*10+posx);
	while(Vali1 || Vali2){
        switch (direction){
            case 1://En vertical
                Vali2=false;
                posy++;
            case 2://En horizontal
                if (Vali1)
                    posx ++;
                else if(Vali2)
                    i--;
            case 3://En diagonal derecha
                if(Vali1){
                    posx++;
                    posy--;}
                else if (Vali2){
                    j--;
                    i++;}
            case 4://En diagonal izquierda
                if(Vali1){
                        posx++;
                        posy++;}
                else if (Vali2){
                        j--;
                        i--;}
        }

        if(posy > 0 && posy < 7 && posx > 0 && posx < 8&& i > 0 && i < 7 && j > 0 && j < 8){
            if (Vali1)
                Vali1=false;
            else if(Vali2)
                Vali2=false;
        }
		else if(map[posx][posy]==playerInTurn){
			path.add_end(posx*10+posy);//Guardamos las posición x,y en un solo número
			path.print();
		}
		else{
			if(Vali1)
                Vali1=false;
            else if (Vali2)
                Vali2=false;}
		if(path.getNum()==4){
			for(int m=0; m<4; m++)
			{
				int a=path.pop();
				map[a/10][a%10]=3;
			}
			return true;
		}
	}
	path.del_all();
	return false;
}

bool Tablero::win(int posx){
    for(int i=1 ;i <=4; i++){
        if (searchLine(i, searchFila(posx-1),posx-1)){
            return true;
        }
    }
}


void Tablero::printTablero(){
    cout<<" 1  2  3  4  5  6  7"<<"\n";
	for(int i=0; i<6; i++)
	{
		for(int j=0; j<7; j++)
		{
		    if (map[i][j]==0)
                cout<< "[ ]";
            else
                cout<< "["<< map[i][j]<<"]";
		}
		cout<< "\n";
	}
}
