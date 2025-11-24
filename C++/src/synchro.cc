#include "synchro.hpp"
#include "ensitheora.hpp"

using namespace std;
/* les variables pour la synchro, ici */
mutex mutextex;
mutex allstrm;
mutex mutexhashmap;

condition_variable texprod;
condition_variable texconso;

condition_variable fenetre_et_texture;
condition_variable taillefenetre;

int tex_nbready = 0;
int tex_stockable = NBTEX;
bool windowsdone = false;
bool taille_fini = false;

/* l'implantation des fonctions de synchro ici */
void envoiTailleFenetre([[maybe_unused]] th_ycbcr_buffer buffer) {
    unique_lock<mutex> lock(allstrm);
    windowsx = buffer[0].width;
    windowsy = buffer[0].height;
    taille_fini = true;
    taillefenetre.notify_one();
}

void attendreTailleFenetre() {
    unique_lock<mutex> lock(allstrm);
    while(taille_fini == false){
        taillefenetre.wait(lock);
    }
}

void signalerFenetreEtTexturePrete() {
    unique_lock<mutex> lock(allstrm);
    windowsdone = true;
    fenetre_et_texture.notify_one();
}

void attendreFenetreTexture() {
    unique_lock<mutex> lock(allstrm);
    while(windowsdone == false){
        fenetre_et_texture.wait(lock);
    }
}





void debutConsommerTexture() {
    unique_lock<mutex> lock(mutextex);
    while(tex_nbready <= 0){
       texconso.wait(lock);
    }
    tex_nbready--;
}

void finConsommerTexture() {
    unique_lock<mutex> lock(mutextex);
    tex_stockable++;
    texprod.notify_one();
}

void debutDeposerTexture() {
    unique_lock<mutex> lock(mutextex);
    while(tex_stockable <= 0){
       texprod.wait(lock);
    }
    tex_stockable--;
}

void finDeposerTexture() {
    unique_lock<mutex> lock(mutextex);
    tex_nbready++;
    texconso.notify_one();
}

