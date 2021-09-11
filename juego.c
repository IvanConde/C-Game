#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "laberinto.h"
#include "copa.h"

#define IMPEDIMENTA 'I'
#define RIDDIKULUS 'R'

#define MAX_MOCHILA 2
#define MOCHILA_VACIO '-'

/* 
 * Pre: Recibe una variable de tipo jugador_t representando al mismo.
 * Post: Imprime por consola la vida y la mochila, o inventario, del jugador.
 */
void interfaz_grafica(jugador_t jugador){

	printf("Vida: %i", jugador.vida);

	char mochila[MAX_MOCHILA];
	for (int i = 0; i < MAX_MOCHILA; i++){
		mochila[i] = MOCHILA_VACIO;
	}
	for(int i = 0; i < jugador.tope_ayudas; i++){
		if ((jugador.ayudas[i].codigo == RIDDIKULUS) || (jugador.ayudas[i].codigo == IMPEDIMENTA)){
			mochila[i] = jugador.ayudas[i].codigo;
		}
	}
	printf("        Mochila: [%c,%c]\n", mochila[0], mochila[1]);

}

int main(){

	system("clear");

	srand((unsigned int)time(NULL));

	juego_t juego;
	char laberinto[TAMANIO][TAMANIO];
	char direccion;

	inicializar_laberinto(&juego);
	actualizar_laberinto(juego, laberinto);
	mostrar_laberinto(laberinto);
	interfaz_grafica(juego.jugador);

	do{

		printf("Presiona (w,a,s,d) para moverte: \n");
		scanf(" %c",&direccion);
		while (!es_movimiento_valido(&juego, direccion)){
			printf("Por favor, ingrese un caracter correcto: \n");
			scanf(" %c",&direccion);
		}

		mover_jugador(&juego.jugador, direccion);

		mover_rival(&juego);

		actualizar_juego(&juego);

		actualizar_laberinto(juego, laberinto);

		system("clear");

		mostrar_laberinto(laberinto);
		interfaz_grafica(juego.jugador);

	}while(estado_juego(juego) == 0);

	if (estado_juego(juego) == 1){
		printf("Ganaste!\n");
	}
	else{
		printf("Perdiste!\n");
	}

	return 0;

}