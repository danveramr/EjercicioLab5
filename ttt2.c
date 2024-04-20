/*
Parte 1:

Deberá ofrecer la posibilidad de jugar humano vs computadora y computadora vs computadora.
La selección de movimientos la hará de forma aleatoria y no se permitirá sobrescribir una jugada previa.
Deberán validarse las combinaciones ganadoras y de empate.

Parte 2:
A partir del programa del gato que desarrollaste al inicio del curso, desarrolla una nueva versión que realice lo siguiente:

Por cada movimiento proporcionado, genere y almacene todos los posibles movimientos restantes.
Diseña una heurística para determinar si el tablero corresponde a un triunfo de la computadora, del humano o un empate. 


*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void tablero(char matriz[][3]);
void jugador(char matriz[][3],int inicio);
void maquina(int *a, int *b, char matriz[][3]);
void maquina2(char matriz[][3]);
int condiciones(char matriz[][3], int *win);
void posiblesJugadas(char matriz[][3],int inicio);

int main(void)
{
	int opcion,flag=0,inicio=0;
	char matriz[3][3];
	printf("\nEjercicio lab no.5");
	printf("\n---------------------");
	printf("\nJuego de gato");
	
	srand(time(NULL));

	//Se inicializan los valores de la matriz 3x3 como '_' para que coincidan con el tablero original
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			matriz[i][j]='_';
		}
	}
	
	//Menú del programa, en donde se podrá jugar las veces que la persona lo desee.
	//Existen dos opciones: Jugador vs. maquina y Maquina vs. maquina

	while(flag==0){
		
		printf("\n\nElige una opcion:\n1.Jugador vs. Maquina\n2.Maquina vs Maquina\n3.Salir\n\nOpcion: ");
		scanf("%d",&opcion);
	
		switch(opcion)
		{
			//Opcion para Jugador vs. maquina
			case 1:
				inicio = rand() % 2;
				if(inicio==0)
				{
					printf("\n\t___|___|___");
					printf("\n\t___|___|___");
					printf("\n\t   |   |   ");
				}
				//printf("\nInicio vale: %d", inicio);
					
				jugador(matriz,inicio);
				break;
			//Opcion para Jugador vs. maquina
			case 2:
				maquina2(matriz);
				break;
			case 3:
				printf("\nFin del programa.");
				exit(0);
			default:
				printf("\nElige una opcion valida");
				break;
		}
	}	
	
	return 0;
}

void tablero(char matriz[][3])
{	
	//Funcion que imprime el tablero con cada jugada realizada tanto 
	//por el jugador como por la maquina

	printf("\n\t_%c_|_%c_|_%c_",matriz[0][0], matriz[0][1], matriz[0][2]);
	printf("\n\t_%c_|_%c_|_%c_",matriz[1][0], matriz[1][1], matriz[1][2]);
	printf("\n\t_%c_|_%c_|_%c_",matriz[2][0], matriz[2][1], matriz[2][2]);
}

void jugador(char matriz[][3], int inicio)
{
	/*Función que permite realizar una jugada a través de los valores 
	introducidos. Asímismo, manda a llamar a otra función que devuelve
	la jugada de la maquina*/
	
	int x,y,c=0,a,b,win=0;
	int ganador=0;

	//Se reinicia el tablero cada vez que se inicia una nueva partida
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			matriz[i][j]='_';
		}
	}

	//La variable inicio puede tomar dos valores: 0 y 1
	//En caso de que sea 0, el jugador inicia la partida
	if(inicio == 0)
	{
		//Mientras que no haya un ganador, se podran realizar hasta un total de 8 jugadas
		while(c<4 && win==0)
		{
			printf("\n\nTu turno!\n");
			printf("\nPosicion en x: ");
			scanf("%d",&x);
			printf("\nPosicion en y: ");
			scanf("%d",&y);
	
			matriz[x][y] = 'x';
			//inicio++;
			printf("\n\nTu jugada:\n");
			tablero(matriz);
			ganador = condiciones(matriz,&win);
			
	
			if(ganador==0)
			{
				posiblesJugadas(matriz,inicio);
				maquina(&a,&b,matriz);
				matriz[a][b] = 'o';
				tablero(matriz);
				ganador = condiciones(matriz,&win);
			}
			c++;
		}
		if(ganador==0)
		{
			printf("\nPosicion en x: ");
			scanf("%d",&x);
			printf("\nPosicion en y: ");
			scanf("%d",&y);	
			tablero(matriz);
			ganador = condiciones(matriz,&win);
		}
	}
	//En caso contrario, la maquina inicia la partida
	else
	{
		while(c<4 && win==0)
		{
			posiblesJugadas(matriz,inicio);
			maquina(&a,&b,matriz);
			matriz[a][b] = 'x';
			tablero(matriz);
			ganador = condiciones(matriz,&win);

			if(ganador==0)
			{
				printf("\n\nTu turno!\n");
				printf("\nPosicion en x: ");
				scanf("%d",&x);
				printf("\nPosicion en y: ");
				scanf("%d",&y);
	
				matriz[x][y] = 'o';
				//inicio++;
		
				printf("\n\nTu jugada:\n");
				tablero(matriz);
				ganador = condiciones(matriz,&win);
			}
			c++;
			
		}
		if(ganador==0)
		{
			maquina(&a,&b,matriz);
			matriz[a][b] = 'x';
			tablero(matriz);
			ganador = condiciones(matriz,&win);
		}
	}

	//Si la bandera win se activa, el estado del juego pasara a ser ganado
	//En caso contrario, resultará en empate
	if(win==0)
	{
		printf("\n\nEstado del juego: Empate");
	}
	else if((inicio==0 && win==1) && ganador==5)
	{
		printf("\n\nGanaste!");
	}
	else if((inicio==0 && win==1) && ganador==10)
	{
		printf("\n\nLa maquina gano");
	}
	else if((inicio==1 && win==1) && ganador==5)
	{
		printf("\n\nLa maquina gano");
	}
	else
		printf("\n\nGanaste!");
}

void maquina(int *a, int *b,char matriz[][3])
{
	/*Función que determina la jugada de la máquina, a partir de 
	valores pseudoaleatorios para a y b, los cuales representan
	las coordenadas de la matriz*/

	int cond = 0;

	/*Mientras el par ordenado elegido no tenga un lugar asignado,
	esos serán los valores correspondientes. En caso contrario,
	se generan nuevamente dichos valores*/
	
	while(cond == 0)
	{	
		*a = rand() % 3;
		*b = rand() % 3;
		if(matriz[*a][*b] != 'o' && matriz[*a][*b] != 'x')
		{
			cond=1;	
		}
	}
	printf("\n\nJugada de la maquina:\n");

}

void maquina2(char matriz[][3])
{
	/*Función que manda a llamar a otra función que devuelve
	la jugada de cada máquina*/
	
	//Se reinicia el tablero cada vez que se inicia una nueva partida
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			matriz[i][j]='_';
		}
	}
	
	int a,b,c=0,win=0;
	printf("\nWin vale: %d",win);

	////Mientras que no haya un ganador, se podrá realizar hasta un total de 8 jugadas
	do
	{
		maquina(&a,&b,matriz);
		matriz[a][b] = 'x';
		tablero(matriz);
		condiciones(matriz,&win);
			
		maquina(&a,&b,matriz);
		matriz[a][b] = 'o';
		tablero(matriz);
		c++;
		condiciones(matriz,&win);
	}
	while(c<4 && win==0);

	//De igual forma, si la bandera win se activa, el estado del juego pasara a ser ganado
	//En caso contrario, resultará en empate
	if(win==0)
	{
		printf("\n\nEstado del juego: Empate");
	}
	else
	{
		printf("\n\nEstado del juego: Ganado");
	}
}
	
int condiciones(char matriz[][3], int *win)
{
	/*Función que contiene todas las combinaciones de victoria para 
	el juego clásico de gato. La misma es llamada en cada turno de
	una partida*/

	int ganador;

	if((matriz[0][0] == 'x' && matriz[1][1] == 'x')&& matriz[2][2] == 'x')
	{
		*win = 1;	
		ganador = 5;
	}
	else if((matriz[0][0] == 'o' && matriz[1][1] == 'o')&& matriz[2][2] == 'o')
	{
		*win = 1;
		ganador = 10;
	}

	else if((matriz[0][2] == 'x' && matriz[1][1] == 'x')&& matriz[2][0] == 'x')
	{
		*win = 1;
		ganador = 5;
	}
	else if((matriz[0][2] == 'o' && matriz[1][1] == 'o')&& matriz[2][0] == 'o')
	{
		*win = 1;
		ganador = 10;
	}

	else if((matriz[0][0] == 'x' && matriz[0][1] == 'x')&& matriz[0][2] == 'x')
	{
		*win = 1;
		ganador = 5;
	}
	else if((matriz[0][0] == 'o' && matriz[0][1] == 'o')&& matriz[0][2] == 'o')
	{
		*win = 1;
		ganador = 10;
	}

	else if((matriz[1][0] == 'x' && matriz[1][1] == 'x')&& matriz[1][2] == 'x')
	{
		*win = 1;
		ganador = 5;
	}
	else if((matriz[1][0] == 'o' && matriz[1][1] == 'o')&& matriz[1][2] == 'o')
	{
		*win = 1;
		ganador = 10;
	}

	else if((matriz[2][0] == 'x' && matriz[2][1] == 'x')&& matriz[2][2] == 'x')
	{
		*win = 1;
		ganador = 5;
	}
	else if((matriz[2][0] == 'o' && matriz[2][1] == 'o')&& matriz[2][2] == 'o')
	{
		*win = 1;
		ganador = 10;
	}

	else if((matriz[0][0] == 'x' && matriz[1][0] == 'x')&& matriz[2][0] == 'x')
	{
		*win = 1;
		ganador = 5;
	}
	else if((matriz[0][0] == 'o' && matriz[1][0] == 'o')&& matriz[2][0] == 'o')
	{
		*win = 1;
		ganador = 10;
	}

	else if((matriz[0][1] == 'x' && matriz[1][1] == 'x')&& matriz[2][1] == 'x')
	{
		*win = 1;
		ganador = 5;
	}
	else if((matriz[0][1] == 'o' && matriz[1][1] == 'o')&& matriz[2][1] == 'o')
	{
		*win = 1;
		ganador = 10;
	}

	else if((matriz[0][2] == 'x' && matriz[1][2] == 'x')&& matriz[2][2] == 'x')
	{
		*win = 1;
		ganador = 5;
	}
	else if((matriz[0][2] == 'o' && matriz[1][2] == 'o')&& matriz[2][2] == 'o')
	{
		*win = 1;
		ganador = 10;
	}
	else 
	{
		win = 0;
		ganador =0;
	}
	return ganador;
}

void posiblesJugadas(char matriz[][3], int inicio)
{
	int i,j;
	char matriz_j[3][3];

	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			matriz_j[i][j] = matriz[i][j];
		}
	}
	printf("\n\nPosibles jugadas:\n\n");
	if(inicio==0)
	{
		for(i=0;i<3;i++)
		{
			for(j=0;j<3;j++)
			{
				if(matriz[i][j]=='_')
				{
					matriz_j[i][j] = 'o';
					tablero(matriz_j);
					matriz_j[i][j] = '_';
					printf("\n");
				}
			}
		}
	}
	else
	{
		for(i=0;i<3;i++)
		{
			for(j=0;j<3;j++)
			{
				if(matriz[i][j]=='_')
				{
					matriz_j[i][j] = 'x';
					tablero(matriz_j);
					matriz_j[i][j] = '_';
					printf("\n");
				}
			}
		}
	}
}