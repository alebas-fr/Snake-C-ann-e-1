//  main.cpp
//  PROJET DU SNAKE
//	
//  Created by Alexandre Lebas & Armand Decobert on 03/01/2017.
//  Copyright © 2017 Alexandre Lebas & Armand Decobert. All rights reserved.

// bibliothéques que l'ont à besoin

#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
//définition des constantes


#define MAX_L 30 //Largeur du terrain équivalent du x
#define MAX_l 50 //Longueur du terrain équivalent du y
#define SIZE_MAX_SNAKE MAX_L*MAX_l // longueur du serpent au maximum

typedef struct{ // évitez de créé des coordonnées pour tous les points
	int x;
	int y;
} Position2D;


void initialiser_terrain(int tab[MAX_L][MAX_l]){ // initialisation du terrain avant de commencer la partie
	int i=0,j=0;
	for (i=0; i<MAX_L; i++) {
		for (j=0; j<MAX_l; j++) {
			// initialisation des bordures et des obstacles

			if (i==0 || j==0 || j==MAX_l-1 || i==MAX_L-1) { 
				tab[i][j]=0;
			}
			else if(i==15 && j==35){
				tab[i][j]=0;
			}
			else if(i==8 && j==39){
				tab[i][j]=0;
			}
			else if(i==25 && j==5){
				tab[i][j]=0;
			}

			// initialisation des fruits rentré en dure au début de la partie

			else if(i==5 && j==5){
				tab[i][j]=2; 
			}
			else if(i==15 && j==10){
				tab[i][j]=2; 
			}

			//initialisation des cases libres

			else{ 
				tab[i][j]=3;
			}
		}
	}
}

int longeur_change(int tab[MAX_L][MAX_l], Position2D serpent[SIZE_MAX_SNAKE]){ // changer la longueur du serpent renvoie un booléen

	if(tab[serpent[0].x][serpent[0].y]==2){// vérifier si les coordonnées du serpent sont égales à celle d'un fruit
		tab[serpent[0].x][serpent[0].y]=1;
		return 1; 
	}
	return 0;

}

void affichage_tableau(int tab[MAX_L][MAX_l], Position2D serpent[SIZE_MAX_SNAKE],int longeur){ // l'affichage du terrain

	int i=0,j=0,k=0;
	char to_display[MAX_L][MAX_l]; // tableau de caractères à afficher

	//affichage du terrain

	for (i=0; i<MAX_L; i++){
		for (j=0; j<MAX_l; j++){
			if (tab[i][j]==0){
				to_display[i][j]='x'; // affichage des bordures
			}
			else if(tab[i][j]==2){
				to_display[i][j]='&'; // affichage du fruit 
			}
			else{
				to_display[i][j]=' '; //affichage des cases libres
			}
		}
	}

	// Affichage du serpent

	to_display[serpent[0].x][serpent[0].y] = 'O'; // affichage de la tête du serpent

	// affichage de la queue du serpent

	for(k=1;k<longeur ;k++) {
		to_display[serpent[k].x][serpent[k].y]='.';
	}
	
	// affichage du caractère

	for (i=0; i<MAX_L; i++) {
		for (j=0; j<MAX_l; j++) {
			printf("%c",to_display[i][j]);
		}
		printf("\n");
	}
}

void deplacement(Position2D serpent[SIZE_MAX_SNAKE], int dd, int longueur){ // déplacement du serpent après la valeur de déplacement demandé et de la longueur
	int i=longueur-1;

	//déplacement du serpent en changeant les valeurs des cases du tableau

	for(i=longueur-1;i>0;i--){
			serpent[i]=serpent[i-1];
	}
	if(dd==1)
		serpent[0].x--; // aller en haut
	else if(dd==2)
		serpent[0].y--; // aller à gauche
	else if(dd==3)
		serpent[0].x++; // aller en bas
	else if(dd==4)
		serpent[0].y++; // aller à droite

}

void lire_clavier_auto(int *dd){ // lire le clavier pour les parties 2 et 3
	
	if(kbhit()){ // si le joueur à appuyé sur une touche

		char c= getch(); // récupérer la valeur du caractère tapée au clavier

		if(c=='z') // deplacemnt haut
			(*dd)=1;
		
		else if(c=='q') //deplacemnt gauche
			(*dd)=2;
		
		else if(c=='s') //deplacement bas
			(*dd)=3;
		
		else if(c=='d') //deplacement droite
			(*dd)=4;

		else // si le joueur n'a pas appuyé sur la bonne touche
			(*dd)=(*dd);
	}
	
	else // si le joueur n'a pas appuyé sur une touche
		(*dd)=(*dd);
	
}

void lire_clavier_manuel(int *dd){ // lire le clavier pour la partie 1

	char c= getch(); // recuperer la valeur du caractère tapée au clavier

	if(c=='z') // haut
		(*dd)=1;
	
	else if(c=='q') //gauche
		(*dd)=2;
	

	else if(c=='s') //bas
		(*dd)=3;
	
	else if(c=='d') //droite
		(*dd)=4;
	
	
	else
		(*dd)=5; // si le joueur n'as pas appuyér sur la bonne touche

}

void fruit_alea(int tab[MAX_L][MAX_l], Position2D fruit[SIZE_MAX_SNAKE],Position2D serpent[SIZE_MAX_SNAKE],int longueur){

	int temps=10,i=0;
	
	int x_alea = (rand() % ((MAX_L-1))) ; //génération d'un nombre entier aléatoire pour le x du fruit
	int y_alea = (rand() % ((MAX_l-1))) ; //géneration d'un nombre entier aléatoire pour le y du fruit

	//vérifier que le fruit n'apparaît ni sur le serpent ni sur le mur

	for(i=0;i<longueur-1;i++){
		if(tab[x_alea][y_alea]==tab[serpent[i].x][serpent[i].y] || tab[x_alea][y_alea]==0 ){ 
			break;
		}
		tab[x_alea][y_alea]=2;
	}
}

int collision_mur(int tab[MAX_L][MAX_l],Position2D serpent[SIZE_MAX_SNAKE]){

	if(tab[serpent[0].x][serpent[0].y]==0){ 
		return 1; 
	}
	return 0;

}

int collision_serpent(Position2D serpent[SIZE_MAX_SNAKE],int longueur){ //pour faire en sorte que la partie soit terminée lorsque le serpent se touche la queue renvoie un booléen 
	
	int i=1;

	//vérifier les coordonnées de la tête par rapport à chaque valeur de la queue du serpent

	for(i=1;i<longueur;i++){ 

		if(serpent[0].x == serpent[i].x && serpent[0].y == serpent[i].y){
			return 1;
		}
	}
	return 0;
}

void game_over(int score){ // affichage de la fin si game Over
		
	system("cls");
	printf("GAME OVER \n");
	printf("SCORE : %d \n",score);
}

void gestion_niveau(int longueur, int *niveau,int *vitesse){

	if(longueur<5){
		(*niveau)=1; // permets de modifier la valeur de ce paramètre pour voir à quel niveau nous somme
		(*vitesse)= (*vitesse); // modifier le temps de pause de la fonction qui gère la gestion des touches
	}

	else if(longueur<8){
		(*niveau)=2;
		(*vitesse)= 300;
	}

	else {
		(*niveau)=3;
		(*vitesse)= 100; 
	}
}

int maximun(int nbr1,int nbr2){ // faire le maximun entre deux nombres passé en paramètre codés en TP
	if(nbr1>nbr2)
		return nbr1;
	else
		return nbr2;
}

void memo_score_2(int score){ // pour le meilleure score prendre la valeur du meilleur score avant cette partie et le comparer à la valeur du score de la partie actuelle pour le 2ème niveau
	FILE* score_save = NULL;
	int score_m_avant=0; // meilleur score de toutes les parties avant

	// lecture du meilleur score avant cette partie

	score_save=fopen("Score_Save_2.txt", "a+");
	fprintf(score_save,"%d ",score);
	fscanf(score_save, "%d",score_m_avant);
	fclose(score_save);

	// regarder si le score de cette partie est supérieur est garde le maximum des deux nombres

	int score_sauvegarde=maximun(score,score_m_avant);
	printf("MEILLEUR SCORE = %d",score_sauvegarde);
	remove("Score_Save_2.txt"); // supprimer l'ancien fichier texte où il y avait le maximum des scores

	// création d'un nouveau fichier pour la sauvegarde et on place la valeur gardée dans la variable

	score_save=fopen("Score_Save_2.txt", "a+");
	fprintf(score_save,"%d ",score_sauvegarde);
	fclose(score_save);
}

void memo_score_3(int score){ // Même chose que la partie 2 mais pour la partie 3
	FILE* score_save = NULL;
	int score_m_avant=0; 

	

	score_save=fopen("Score_Save_3.txt", "a+");
	fprintf(score_save,"%d ",score);
	fscanf(score_save, "%d",score_m_avant);
	fclose(score_save); 



	int score_sauvegarde=maximun(score,score_m_avant);
	printf("MEILLEUR SCORE = %d",score_sauvegarde);
	remove("Score_Save_3.txt"); 


	score_save=fopen("Score_Save_3.txt", "a+");
	fprintf(score_save,"%d ",score_sauvegarde);
	fclose(score_save);
}

void traverse_mur(Position2D serpent[SIZE_MAX_SNAKE]){ // permets de gérer le fait que si le serpent passe à travers la bordure il revient à la bordure opposée
	if(serpent[0].x==MAX_L-1){ // pour la bordure du bas
		serpent[0].x=1;
	}
	if(serpent[0].x==0){
		serpent[0].x=MAX_L-2;
	}
	if(serpent[0].y==MAX_l-1){
		serpent[0].y=1;
	}
	if(serpent[0].y==0){
		serpent[0].y=MAX_l-2;
	}
}
int main(int argc, const char * argv[]) {
	srand(time(NULL)); // permets la génaration de nombres aleatoires
	int dd=1; // déplacement demandé 1=h 2=g 3=b 4=d 1 car pour le deplacement_auto il va directement en haut
	int terrain[MAX_L][MAX_l]; // tableau du terrain 0=obstacle 2=fruit 3=espace libre
	int i=1,j=1,k=1,l=1;
	int horloge=100; // nombre de déplacement que l'on peut faire
	int partie=6; // permets de choisir le mode de jeu
	int niveau_b=1; // permets d'afficher le niveau
	int vitesse=500; // définit le temps que l'on doit mettre en pause la fonction
	int longeur_serpent = 3; // la longueur du serpent
	int vie=3; // nombre de vie pour la partie 3

	// affichage du menu

	while(partie<1 || partie>3){ 
		printf("BIENVENUE DANS LA SNAKE CHOISSISEZ VOTRE NIVEAU \n partie a)=1 \n partie b)=2 \n partie c)=3 \n");
		scanf("%d",&partie);

		system("cls");
	}

	/* Définition des tableaux de structure de point 2D pour faire
	en sorte que le serpent et les fruits soit des tableaux de point 2D
	*/

	Position2D serpent[SIZE_MAX_SNAKE];
	Position2D fruit[SIZE_MAX_SNAKE];// la taille maximale du serpent correspond car cela représente la surface du terrain

	// Position initiale de la tête du serpent

	serpent[0].x = MAX_L/2;
	serpent[0].y = MAX_l/2;

	/*for (i=1;i<SIZE_MAX_SNAKE;i++){ // initialisation des cases du tableau du serpent pour éviter les bugs
		serpent[i].x = serpent[i-1].x;
		serpent[i].y = serpent[i-1].y-1;
	}*/

	// initialisation des cases du tableau du serpent pour les valeurs inferieures à la longueur du serpent initiale

	for (i=1;i<longeur_serpent;i++){ 
		serpent[i].x = serpent[i-1].x;
		serpent[i].y = serpent[i-1].y-1;
	}

	/* initialisation des cases du tableau du serpent si on est supérieur 
	à la longueur du serpent dans un endroit autre que le terrain pour éviter 
	que quand la longueur augmente de 1 le point apparaisent n'importe où sur le terrain
	*/
	for (j=longeur_serpent;j<SIZE_MAX_SNAKE;j++){ 
		for(k=MAX_L;k<MAX_L+30;k++){
			for(l=0;l<MAX_l;l++){
				serpent[j].x=k;
				serpent[j].y=l;
			}
		}
	}

	initialiser_terrain(terrain);

	affichage_tableau(terrain, serpent, longeur_serpent);


	while(1)
	{

		if(partie==1){ // code de la partie a)
			lire_clavier_manuel(&dd);
			deplacement(serpent,dd,longeur_serpent);

			if(longeur_change(terrain,serpent)){ 
				longeur_serpent++; 
			}

			horloge--; // aprés un déplacement, diminuer la valeur de l'horloge
			
			fruit_alea(terrain,fruit,serpent,longeur_serpent);

			 

			if(collision_mur(terrain,serpent) ||collision_serpent(serpent,longeur_serpent) ||horloge==0){
				game_over(longeur_serpent);
				break;
			}


			system("cls"); 
			affichage_tableau(terrain, serpent, longeur_serpent);
			printf("TEMPS = %d \n",horloge);
		}

		if(partie==2){ // code de la partie b)
			Sleep(vitesse); // mettre en pause le programme pour laisser au joueur le temps d'appuyer sur une touche

			lire_clavier_auto(&dd);
			deplacement(serpent, dd,longeur_serpent);

			if(longeur_change(terrain,serpent)){
				longeur_serpent++; //ajouter 1 à la longueur
			}
			gestion_niveau(longeur_serpent,&niveau_b,&vitesse);


			fruit_alea(terrain,fruit,serpent,longeur_serpent); 

			// regarder la case ou le serpent est située et voir si cela est possible qu'il soit la

			if(collision_mur(terrain,serpent) ||collision_serpent(serpent,longeur_serpent)){
				game_over(longeur_serpent);
				memo_score_2(longeur_serpent);
				break;
			}


			system("cls"); 
			affichage_tableau(terrain, serpent, longeur_serpent);
			printf("NIVEAU = %d \n",niveau_b);
		}

		if(partie==3){ //code de la partie c)
			Sleep(vitesse); 

			lire_clavier_auto(&dd);
			deplacement(serpent, dd,longeur_serpent);


			if(longeur_change(terrain,serpent)){
				longeur_serpent++;
			}

			gestion_niveau(longeur_serpent,&niveau_b,&vitesse);
			

			fruit_alea(terrain,fruit,serpent,longeur_serpent);


			if(collision_serpent(serpent,longeur_serpent)){
				game_over(longeur_serpent);
				memo_score_3(longeur_serpent);
				break;
			}
			if(collision_mur(terrain,serpent)){
				vie--;
				if(vie!=0){
					traverse_mur(serpent);
				}
				else{
					game_over(longeur_serpent);
					memo_score_3(longeur_serpent);
					break;
				}
			}

			system("cls"); 
			affichage_tableau(terrain, serpent, longeur_serpent);
			printf("NIVEAU = %d \n",niveau_b); 
			printf("VIE: %d \n", vie); 
		}
		printf("SCORE = %d \n",longeur_serpent);
	}
	getch();
	return 0;
}
