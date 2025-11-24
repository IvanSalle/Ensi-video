#ifndef SYNCHRO_H
#define SYNCHRO_H

#include "ensitheora.hpp"

#include <condition_variable>
#include <mutex>
#include <thread>
using namespace std;

/* Les extern des variables pour la synchro ici */

extern mutex allstrm;
extern mutex mutextex;
extern condition_variable texprod;
extern condition_variable texconso;

extern bool taille_fini;
extern int tex_nbready;

extern bool windowsdone; 

extern mutex mutexhashmap;

extern unique_ptr<thread> thread_affichage;

/* Fonctions de synchro à implanter */

void envoiTailleFenetre(th_ycbcr_buffer buffer);
void attendreTailleFenetre();

void attendreFenetreTexture();
void signalerFenetreEtTexturePrete();

void debutConsommerTexture();
void finConsommerTexture();

void debutDeposerTexture();
void finDeposerTexture();

#endif
