#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "laberinto.h"
#include "copa.h"

#define DERECHA 'd'
#define ABAJO 's'
#define IZQUIERDA 'a'
#define ARRIBA 'w'

#define JUGADOR 'J'
#define RIVAL 'G'
#define COPA 'C'
#define POCION 'P'
#define IMPEDIMENTA 'I'
#define RIDDIKULUS 'R'
#define ESCREGUTO 'E'
#define ACROMANTULA 'A'
#define BOGGART 'B'
#define ESFINGE 'F'

#define VIDA_IMPEDIMENTA 0
#define VIDA_RIDDIKULUS 0
#define VIDA_POCION 15
#define VIDA_ESFINGE 0
#define VIDA_MINIMA_COPA 15
#define VIDA_JUGADOR 50

#define DANIO_TURNO 3
#define DANIO_ESCREGUTO 20
#define DANIO_ACROMANTULA 10
#define DANIO_BOGGART 15

#define RIVAL_PASOS_INICIALES 0
#define RIVAL_PASOS_MAXIMOS 4

#define DISTANCIA_JUGADORES_COPA 10

#define ESTADO_GANADO 1
#define ESTADO_PERDIDO (-1)
#define ESTADO_EN_CURSO 0

#define VECTOR_OBSTACULO 0
#define VECTOR_AYUDA 1

#define VECTOR_JUEGO 0
#define VECTOR_JUGADOR 1

/* 
 * Pre: Recibe 2 registros de tipo coordenada_t, que en este caso representan al jugador o rival y la copa.
 * Post: Devuelve true en caso de que la distancia manhattan entre dichos registros sea la deseada, por el contraio devuelve false.
 */
bool validar_distancia_manhattan(coordenada_t entidad_1, coordenada_t entidad_2){

	int distancia = abs(entidad_1.fil - entidad_2.fil) + abs(entidad_1.col - entidad_2.col);

	if (distancia > DISTANCIA_JUGADORES_COPA)
		return true;
	else
		return false;

}

/*
 * Pre: Recibe una variable de tipo coordenada_t la cual representa una posicion, ademas una matriz la cual en este caso representa el laberinto.
 * Post: Devuelve true si en la matriz en la posicion dada hay un caracter vacio.
*/
bool validar_posicion(coordenada_t posicion, char laberinto[TAMANIO][TAMANIO]){

	return (laberinto[posicion.fil][posicion.col] == VACIO);

}

/*
 * Pre: Recibe una variable de tipo juego_t que representa al juego y ademas una matriz la cual en este caso representa el laberinto temporal.
 * Post: Inicializa la copa validando su posicion en un espacio vacio del laberinto y sus propiedades correspondientes.
*/
void inicializar_copa(juego_t* juego, char laberinto[TAMANIO][TAMANIO]){

	do{
		(*juego).copa.posicion = posicion_aleatoria();
	}while(!(validar_posicion((*juego).copa.posicion, laberinto)));
	(*juego).copa.codigo = COPA;
	laberinto[(*juego).copa.posicion.fil][(*juego).copa.posicion.col] = (*juego).copa.codigo;

}

/*
 * Pre: Recibe una variable de tipo juego_t que representa al juego y ademas una matriz la cual en este caso representa el laberinto temporal.
 * Post: Inicializa al escreguto validando su posicion en un espacio vacio del laberinto y sus propiedades correspondientes.
*/
void inicializar_escreguto(juego_t* juego, char laberinto[TAMANIO][TAMANIO]){

	do{
		(*juego).obstaculos[0].posicion = posicion_aleatoria();
	}while(!(validar_posicion((*juego).obstaculos[0].posicion, laberinto)));
	(*juego).obstaculos[0].codigo = ESCREGUTO;
	(*juego).obstaculos[0].danio = DANIO_ESCREGUTO;
	laberinto[(*juego).obstaculos[0].posicion.fil][(*juego).obstaculos[0].posicion.col] = (*juego).obstaculos[0].codigo;
	(*juego).tope_obstaculos += 1;

}

/*
 * Pre: Recibe una variable de tipo juego_t que representa al juego y ademas una matriz la cual en este caso representa el laberinto temporal.
 * Post: Inicializa a la acromantula validando su posicion en un espacio vacio del laberinto y sus propiedades correspondientes.
*/
void inicializar_acromantula(juego_t* juego, char laberinto[TAMANIO][TAMANIO]){

	do{
		(*juego).obstaculos[1].posicion = posicion_aleatoria();
	}while(!(validar_posicion((*juego).obstaculos[1].posicion, laberinto)));
	(*juego).obstaculos[1].codigo = ACROMANTULA;
	(*juego).obstaculos[1].danio = DANIO_ACROMANTULA;
	laberinto[(*juego).obstaculos[1].posicion.fil][(*juego).obstaculos[1].posicion.col] = (*juego).obstaculos[1].codigo;
	(*juego).tope_obstaculos += 1;

}

/*
 * Pre: Recibe una variable de tipo juego_t que representa al juego y ademas una matriz la cual en este caso representa el laberinto temporal.
 * Post: Inicializa al boggart validando su posicion en un espacio vacio del laberinto y sus propiedades correspondientes.
*/
void inicializar_boggart(juego_t* juego, char laberinto[TAMANIO][TAMANIO]){

	do{
		(*juego).obstaculos[2].posicion = posicion_aleatoria();
	}while(!(validar_posicion((*juego).obstaculos[2].posicion, laberinto)));
	(*juego).obstaculos[2].codigo = BOGGART;
	(*juego).obstaculos[2].danio = DANIO_BOGGART;
	laberinto[(*juego).obstaculos[2].posicion.fil][(*juego).obstaculos[2].posicion.col] = (*juego).obstaculos[2].codigo;
	(*juego).tope_obstaculos += 1;

}

/*
 * Pre: Recibe una variable de tipo juego_t que representa al juego y ademas una matriz la cual en este caso representa el laberinto temporal.
 * Post: Inicializa impedimenta validando su posicion en un espacio vacio del laberinto y sus propiedades correspondientes.
*/
void inicializar_impedimenta(juego_t* juego, char laberinto[TAMANIO][TAMANIO]){

	do{
		(*juego).ayudas[0].posicion = posicion_aleatoria();
	}while(!(validar_posicion((*juego).ayudas[0].posicion, laberinto)));
	(*juego).ayudas[0].codigo = IMPEDIMENTA;
	(*juego).ayudas[0].vida_a_recuperar = VIDA_IMPEDIMENTA;
	laberinto[(*juego).ayudas[0].posicion.fil][(*juego).ayudas[0].posicion.col] = (*juego).ayudas[0].codigo;
	(*juego).tope_ayudas += 1;

}

/*
 * Pre: Recibe una variable de tipo juego_t que representa al juego y ademas una matriz la cual en este caso representa el laberinto temporal.
 * Post: Inicializa riddikulus validando su posicion en un espacio vacio del laberinto y sus propiedades correspondientes.
*/
void inicializar_riddikulus(juego_t* juego, char laberinto[TAMANIO][TAMANIO]){

	do{
		(*juego).ayudas[1].posicion = posicion_aleatoria();
	}while(!(validar_posicion((*juego).ayudas[1].posicion, laberinto)));
	(*juego).ayudas[1].codigo = RIDDIKULUS;
	(*juego).ayudas[1].vida_a_recuperar = VIDA_RIDDIKULUS;
	laberinto[(*juego).ayudas[1].posicion.fil][(*juego).ayudas[1].posicion.col] = (*juego).ayudas[1].codigo;
	(*juego).tope_ayudas += 1;

}

/*
 * Pre: Recibe una variable de tipo juego_t que representa al juego y ademas una matriz la cual en este caso representa el laberinto temporal.
 * Post: Inicializa las pociones validando su posicion en un espacio vacio del laberinto y sus propiedades correspondientes.
*/
void inicializar_pociones(juego_t* juego, char laberinto[TAMANIO][TAMANIO]){

	for(int i = 2; i < 5; i++){	
		do{
			(*juego).ayudas[i].posicion = posicion_aleatoria();
		}while(!(validar_posicion((*juego).ayudas[i].posicion, laberinto)));
		(*juego).ayudas[i].codigo = POCION;
		(*juego).ayudas[i].vida_a_recuperar = VIDA_POCION;
		laberinto[(*juego).ayudas[i].posicion.fil][(*juego).ayudas[i].posicion.col] = (*juego).ayudas[i].codigo;
		(*juego).tope_ayudas += 1;
	}

}

/*
 * Pre: Recibe una variable de tipo juego_t que representa al juego y ademas una matriz la cual en este caso representa el laberinto temporal.
 * Post: Inicializa la esfinge validando su posicion en un espacio vacio del laberinto y sus propiedades correspondientes.
*/
void inicializar_esfinge(juego_t* juego, char laberinto[TAMANIO][TAMANIO]){

	do{
		(*juego).ayudas[5].posicion = posicion_aleatoria();
	}while(!(validar_posicion((*juego).ayudas[5].posicion, laberinto)));
	(*juego).ayudas[5].codigo = ESFINGE;
	(*juego).ayudas[5].vida_a_recuperar = VIDA_ESFINGE;
	laberinto[(*juego).ayudas[5].posicion.fil][(*juego).ayudas[5].posicion.col] = (*juego).ayudas[5].codigo;
	(*juego).tope_ayudas += 1;

}

/*
 * Pre: Recibe una variable de tipo juego_t que representa al juego y ademas una matriz la cual en este caso representa el laberinto temporal.
 * Post: Inicializa al rival validando su posicion en un espacio vacio del laberinto, la distancia manhattan y sus propiedades correspondientes.
*/
void inicializar_rival(juego_t* juego, char laberinto[TAMANIO][TAMANIO]){

	do{
		(*juego).rival.posicion = posicion_aleatoria();
	}while(!((validar_posicion((*juego).rival.posicion, laberinto)) && (validar_distancia_manhattan((*juego).rival.posicion, (*juego).copa.posicion))));
	(*juego).rival.codigo = RIVAL;
	(*juego).rival.direccion = DERECHA;
	(*juego).rival.cantidad_pasos = RIVAL_PASOS_INICIALES;
	laberinto[(*juego).rival.posicion.fil][(*juego).rival.posicion.col] = (*juego).rival.codigo;

}

/*
 * Pre: Recibe una variable de tipo juego_t que representa al juego y ademas una matriz la cual en este caso representa el laberinto temporal.
 * Post: Inicializa al jugador validando su posicion en un espacio vacio del laberinto, la distancia manhattan y sus propiedades correspondientes.
*/
void inicializar_jugador(juego_t* juego, char laberinto[TAMANIO][TAMANIO]){

	do{
		(*juego).jugador.posicion = posicion_aleatoria();
	}while(!((validar_posicion((*juego).jugador.posicion, laberinto)) && (validar_distancia_manhattan((*juego).jugador.posicion, (*juego).copa.posicion))));
	(*juego).jugador.codigo = JUGADOR;
	(*juego).jugador.vida = VIDA_JUGADOR;
	(*juego).jugador.tope_ayudas = 0; 
	laberinto[(*juego).jugador.posicion.fil][(*juego).jugador.posicion.col] = (*juego).jugador.codigo;

}

void inicializar_laberinto(juego_t* juego){

	inicializar_paredes_laberinto((*juego).laberinto_original);

	char laberinto_temporal[TAMANIO][TAMANIO];
	for (int x = 0; x < TAMANIO; x++){
		for (int y = 0; y < TAMANIO; y++){
			laberinto_temporal[x][y] = (*juego).laberinto_original[x][y];
		}
	}

	(*juego).tope_obstaculos = 0;
	(*juego).tope_ayudas = 0;

	inicializar_copa(&(*juego), laberinto_temporal);
	inicializar_escreguto(&(*juego), laberinto_temporal);
	inicializar_acromantula(&(*juego), laberinto_temporal);
	inicializar_boggart(&(*juego), laberinto_temporal);
	inicializar_impedimenta(&(*juego), laberinto_temporal);
	inicializar_riddikulus(&(*juego), laberinto_temporal);
	inicializar_pociones(&(*juego), laberinto_temporal);
	inicializar_esfinge(&(*juego), laberinto_temporal);
	inicializar_rival(&(*juego), laberinto_temporal);
	inicializar_jugador(&(*juego), laberinto_temporal);

}

/*
 * Pre: Reciben 2 variables enteras que representan fila y columna de una matriz.
 * Post: Si los valores dados estan dentro del rango de la matriz (laberinto) devuelve true, caso contrario devuelve false.
*/
bool validar_entidad_rango(int fila, int columna){

	if ((fila >= 0) && (fila <= 14) && (columna >= 0) && (columna <= 14))
		return true;
	else 
		return false;

}

bool es_movimiento_valido(juego_t* juego, char tecla){

	int fila = (*juego).jugador.posicion.fil;
	int columna = (*juego).jugador.posicion.col;

	switch(tecla){

		case ARRIBA:
			if ((((*juego).laberinto_original[fila-1][columna]) != PARED) && validar_entidad_rango(fila-1, columna))
				return true;
			break;
		case ABAJO:
			if ((((*juego).laberinto_original[fila+1][columna]) != PARED) && validar_entidad_rango(fila+1, columna))
				return true;
			break;
		case DERECHA:
			if ((((*juego).laberinto_original[fila][columna+1]) != PARED) && validar_entidad_rango(fila, columna+1))
				return true;
			break;
		case IZQUIERDA:
			if ((((*juego).laberinto_original[fila][columna-1]) != PARED) && validar_entidad_rango(fila, columna-1))
				return true;
			break;
		default:
			return false;
			break;
	
	}

	return false;

}

void mover_jugador(jugador_t* jugador, char direccion){

	switch(direccion){

		case ARRIBA:
			((*jugador).posicion.fil)--;
		break;
		case ABAJO:
			((*jugador).posicion.fil)++;
		break;
		case DERECHA:
			((*jugador).posicion.col)++;
		break;
		case IZQUIERDA:
			((*jugador).posicion.col)--;
		break;

	}

}

/*
 * Pre: Recibe un puntero a una variable de tipo juego_t, el juego, y 2 numeros enteros los cuales representan la posicion actual de en este caso el rival.
 * Post: En caso de que la posicion recibida y la posicion actual del rival difieran, se devuelve true, es decir se movio, por el contrario false.
*/
bool se_movio_rival(juego_t *juego, int pos_actual_fil, int pos_actual_col){

	if (((*juego).rival.posicion.fil != pos_actual_fil) || ((*juego).rival.posicion.col != pos_actual_col))
		return true;
	else
		return false;

}

/*
 * Pre: Recibe un puntero a una variable de tipo juego_t que representa el juego y un char que representa la direccion a validar.
 * Post: En caso de que la direccion a la que el rival se quiere desplazar sea valida se devuelve true, caso contrario, false.
*/
bool validar_mov_rival(juego_t* juego, char direccion){

	int fila = (*juego).rival.posicion.fil;
	int columna = (*juego).rival.posicion.col;

	switch(direccion){

		case ARRIBA:
			if ((((*juego).laberinto_original[fila-1][columna]) != PARED) && validar_entidad_rango(fila-1, columna))
				return true;
			break;
		case ABAJO:
			if ((((*juego).laberinto_original[fila+1][columna]) != PARED) && validar_entidad_rango(fila+1, columna))
				return true;
			break;
		case DERECHA:
			if ((((*juego).laberinto_original[fila][columna+1]) != PARED) && validar_entidad_rango(fila, columna+1))
				return true;
			break;
		case IZQUIERDA:
			if ((((*juego).laberinto_original[fila][columna-1]) != PARED) && validar_entidad_rango(fila, columna-1))
				return true;
			break;
		default:
			return false;
			break;

	}

	return false;

}

/*
 * Pre: Recibe un puntero a una variable de tipo juego_t, representando al juego en si.
 * Post: Si el rival tiene pasos disponibles, valida, y dependiendo el resultado se mueve a la derecha o no, sino, se cambia la direccion por la siguiente y se reestablecen los pasos.
*/
void rival_derecha(juego_t* juego){

	if (((*juego).rival.cantidad_pasos) == RIVAL_PASOS_MAXIMOS){
		(*juego).rival.direccion = ABAJO;
		(*juego).rival.cantidad_pasos = RIVAL_PASOS_INICIALES;
	}
	else if (validar_mov_rival(juego, (*juego).rival.direccion)){
		((*juego).rival.posicion.col)++;
		((*juego).rival.cantidad_pasos)++;
	}
	else{
		((*juego).rival.cantidad_pasos)++;
	}

}

/*
 * Pre: Recibe un puntero a una variable de tipo juego_t, representando al juego en si.
 * Post: Si el rival tiene pasos disponibles, valida, y dependiendo el resultado se mueve abajo o no, sino, se cambia la direccion por la siguiente y se reestablecen los pasos.
*/
void rival_abajo(juego_t* juego){

	if (((*juego).rival.cantidad_pasos) == RIVAL_PASOS_MAXIMOS){
		(*juego).rival.direccion = IZQUIERDA;
		(*juego).rival.cantidad_pasos = RIVAL_PASOS_INICIALES;
	}
	else if (validar_mov_rival(juego, (*juego).rival.direccion)){
		((*juego).rival.posicion.fil)++;
		((*juego).rival.cantidad_pasos)++;
	}
	else{
		((*juego).rival.cantidad_pasos)++;
	}

}

/*
 * Pre: Recibe un puntero a una variable de tipo juego_t, representando al juego en si.
 * Post: Si el rival tiene pasos disponibles, valida, y dependiendo el resultado se mueve a la izquierda o no, sino, se cambia la direccion por la siguiente y se reestablecen los pasos.
*/
void rival_izquierda(juego_t* juego){

	if (((*juego).rival.cantidad_pasos) == RIVAL_PASOS_MAXIMOS){
		(*juego).rival.direccion = ARRIBA;
		(*juego).rival.cantidad_pasos = RIVAL_PASOS_INICIALES;
	}
	else if (validar_mov_rival(juego, (*juego).rival.direccion)){
		((*juego).rival.posicion.col)--;
		((*juego).rival.cantidad_pasos)++;
	}
	else{
		((*juego).rival.cantidad_pasos)++;
	}

}

/*
 * Pre: Recibe un puntero a una variable de tipo juego_t, representando al juego en si.
 * Post: Si el rival tiene pasos disponibles, valida, y dependiendo el resultado se mueve arriba o no, sino, se cambia la direccion por la siguiente y se reestablecen los pasos.
*/
void rival_arriba(juego_t* juego){

	if (((*juego).rival.cantidad_pasos) == RIVAL_PASOS_MAXIMOS){
		(*juego).rival.direccion = DERECHA;
		(*juego).rival.cantidad_pasos = RIVAL_PASOS_INICIALES;
	}
	else if (validar_mov_rival(juego, (*juego).rival.direccion)){
		((*juego).rival.posicion.fil)--;
		((*juego).rival.cantidad_pasos)++;
	}
	else{
		((*juego).rival.cantidad_pasos)++;
	}

}

void mover_rival(juego_t* juego){

	int pos_actual_fil = (*juego).rival.posicion.fil;
	int pos_actual_col = (*juego).rival.posicion.col;

	while(!(se_movio_rival(juego, pos_actual_fil, pos_actual_col))){

		if ((*juego).rival.direccion == DERECHA){
			rival_derecha(juego);
		}
		else if ((*juego).rival.direccion == ABAJO){
			rival_abajo(juego);
		}
		else if ((*juego).rival.direccion == IZQUIERDA){
			rival_izquierda(juego);
		}
		else{
			rival_arriba(juego);
		}

	}

}

/*
 * Pre: Recibe un puntero a una variable de tipo juego_t que representa el juego y 3 numeros enteros, representando una posicion, un tope, y el caso a evaluar.
 * Post: Borrara el elemento en la posicion recibida en el registro elegido segun el caso.
*/
void eliminar_elem_vector_pos(juego_t *juego, int posicion, int *tope, int caso){

	if (caso == VECTOR_OBSTACULO){
		for (int i = posicion; i < ((*tope) - 1); i++){
			(*juego).obstaculos[i] = (*juego).obstaculos[i+1];
		}
		(*tope)--;
	}
	else{
		for (int i = posicion; i < ((*tope) - 1); i++){
			(*juego).ayudas[i] = (*juego).ayudas[i+1];
		}
		(*tope)--;
	}

}

/*
 * Pre: Recibe una variable de tipo juego_t representando al juego.
 * Post: Devuelve un caracter dentro del registro ayudas o obstaculos dependiendo de si la posicion del jugador es igual a la de un elemento, sino, se devuelve 0.
*/
char obtener_caracter(juego_t juego){

	for (int i = 0; i < juego.tope_obstaculos; i++){
		if ((juego.jugador.posicion.fil == juego.obstaculos[i].posicion.fil) && (juego.jugador.posicion.col == juego.obstaculos[i].posicion.col))
			return (juego.obstaculos[i].codigo);
	}

	for (int i = 0; i < juego.tope_ayudas; i++){
		if ((juego.jugador.posicion.fil == juego.ayudas[i].posicion.fil) && (juego.jugador.posicion.col == juego.ayudas[i].posicion.col))
			return (juego.ayudas[i].codigo);
	}

	return 'x';

}

/*
 * Pre: Recibe una variable de tipo juego_t representando al juego.
 * Post: Devuelve una posicion dentro del registro ayudas o obstaculos dependiendo de si la posicion del jugador es igual a la de un elemento, sino, se devuelve 0.
*/
int obtener_posicion(juego_t juego){

	for (int i = 0; i < juego.tope_obstaculos; i++){
		if ((juego.jugador.posicion.fil == juego.obstaculos[i].posicion.fil) && (juego.jugador.posicion.col == juego.obstaculos[i].posicion.col))
			return i;
	}

	for (int i = 0; i < juego.tope_ayudas; i++){
		if ((juego.jugador.posicion.fil == juego.ayudas[i].posicion.fil) && (juego.jugador.posicion.col == juego.ayudas[i].posicion.col))
			return i;
	}

	return 0;

}

/*
 * Pre: Recibe una variable de tipo juego_t que representa el juego y 2 numeros enteros, representando una codigo y el caso a evaluar.
 * Post: Devuelve true si el caracter se encuentre en el vector, de lo contrario, false.
*/
bool busqueda_caracter(juego_t juego, char codigo, int caso){

    bool esta = false;
    int i = 0;

	if (caso == VECTOR_JUEGO){
		while ((i < juego.tope_ayudas) && (!esta)){
			if (juego.ayudas[i].codigo == codigo){
				esta = true;
			}
			i++;
		}
	}
	else{
		while ((i < juego.jugador.tope_ayudas) && (!esta)){
			if (juego.jugador.ayudas[i].codigo == codigo){
				esta = true;
			}
			i++;
		}
	}

    return esta;

}

void actualizar_juego(juego_t* juego){

	(*juego).jugador.vida -= DANIO_TURNO;

	switch (obtener_caracter(*juego)){

		case POCION:
			if ((*juego).jugador.vida >= 4){
				(*juego).jugador.vida += (*juego).ayudas[obtener_posicion(*juego)].vida_a_recuperar;
			}
			if((*juego).jugador.vida > 50){
				(*juego).jugador.vida = 50;
			}
			eliminar_elem_vector_pos((juego), obtener_posicion(*juego), &((*juego).tope_ayudas), VECTOR_AYUDA);
			break;
		case ESFINGE:
			eliminar_elem_vector_pos((juego), obtener_posicion(*juego), &((*juego).tope_ayudas), VECTOR_AYUDA);
			break;
		case RIDDIKULUS:
			for (int i = 0; i < (*juego).tope_ayudas; i++){
				if ((*juego).ayudas[i].codigo == RIDDIKULUS){
					(*juego).jugador.ayudas[(*juego).jugador.tope_ayudas] = (*juego).ayudas[i];
					((*juego).jugador.tope_ayudas)++;
				}
			}
			eliminar_elem_vector_pos((juego), obtener_posicion(*juego), &((*juego).tope_ayudas), VECTOR_AYUDA);
			break;
		case IMPEDIMENTA:
			for (int i = 0; i < (*juego).tope_ayudas; i++){
				if ((*juego).ayudas[i].codigo == IMPEDIMENTA){
					(*juego).jugador.ayudas[(*juego).jugador.tope_ayudas] = (*juego).ayudas[i];
					((*juego).jugador.tope_ayudas)++;
				}
			}
			eliminar_elem_vector_pos((juego), obtener_posicion(*juego), &((*juego).tope_ayudas), VECTOR_AYUDA);
			break;
		case ACROMANTULA:
			(*juego).jugador.vida -= (*juego).obstaculos[obtener_posicion(*juego)].danio;
			eliminar_elem_vector_pos((juego), obtener_posicion(*juego), &((*juego).tope_obstaculos), VECTOR_OBSTACULO);
			break;
		case ESCREGUTO:
			if (!(busqueda_caracter(*juego, IMPEDIMENTA, VECTOR_JUGADOR))){
				(*juego).jugador.vida -= (*juego).obstaculos[obtener_posicion(*juego)].danio;
			}
			eliminar_elem_vector_pos((juego), obtener_posicion(*juego), &((*juego).tope_obstaculos), VECTOR_OBSTACULO);
			break;
		case BOGGART:
			if (!(busqueda_caracter(*juego, RIDDIKULUS, VECTOR_JUGADOR))){
				(*juego).jugador.vida -= (*juego).obstaculos[obtener_posicion(*juego)].danio;
			}
			eliminar_elem_vector_pos((juego), obtener_posicion(*juego), &((*juego).tope_obstaculos), VECTOR_OBSTACULO);
			break;

	}

}

int estado_juego(juego_t juego){

	if ((juego.jugador.posicion.fil == juego.copa.posicion.fil) && (juego.jugador.posicion.col == juego.copa.posicion.col))
		return ESTADO_GANADO;
	else if ((juego.rival.posicion.fil == juego.copa.posicion.fil) && (juego.rival.posicion.col == juego.copa.posicion.col))
		return ESTADO_PERDIDO;
	else if (juego.jugador.vida <= 0)
		return ESTADO_PERDIDO;
	else
		return ESTADO_EN_CURSO;

}

coordenada_t posicion_aleatoria(){

	coordenada_t posicion_aleatoria;
    posicion_aleatoria.fil = rand()%15;
    posicion_aleatoria.col = rand()%15;
    return posicion_aleatoria;

}

void actualizar_laberinto(juego_t juego, char laberinto[TAMANIO][TAMANIO]){

	for (int x = 0; x < TAMANIO; x++){
		for (int y = 0; y < TAMANIO; y++){
			laberinto[x][y] = juego.laberinto_original[x][y];
		}
	}

	if ((!(busqueda_caracter(juego, 'F', VECTOR_JUEGO))) || juego.jugador.vida <= VIDA_MINIMA_COPA){
	laberinto[juego.copa.posicion.fil][juego.copa.posicion.col] = juego.copa.codigo;
	}

	for (int i = 0; i < (juego.tope_obstaculos); i++){
		laberinto[juego.obstaculos[i].posicion.fil][juego.obstaculos[i].posicion.col] = juego.obstaculos[i].codigo;
	}

	for (int i = 0; i < (juego.tope_ayudas); i++){
		laberinto[juego.ayudas[i].posicion.fil][juego.ayudas[i].posicion.col] = juego.ayudas[i].codigo;
	}

	laberinto[juego.rival.posicion.fil][juego.rival.posicion.col] = juego.rival.codigo;

	laberinto[juego.jugador.posicion.fil][juego.jugador.posicion.col] = juego.jugador.codigo;

}

void mostrar_laberinto(char laberinto[TAMANIO][TAMANIO]){

	for (int x = 0; x < TAMANIO; x++){
		for (int y = 0; y < TAMANIO; y++)
			printf("%c ", laberinto[x][y]);
		printf("\n");
	}

}