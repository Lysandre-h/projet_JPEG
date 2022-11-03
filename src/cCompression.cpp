#include "cCompression.h"
#include <cmath>

double pi = 4*atan(1);

cCompression::cCompression(unsigned largeur, unsigned hauteur, unsigned qualite) {
    mLargeur = largeur;
    mHauteur = hauteur;
    mQualite = qualite;
}

cCompression::~cCompression() {

}

unsigned cCompression::get_largeur() const { return mLargeur; }

unsigned cCompression::get_hauteur() const { return mHauteur; }

unsigned cCompression::get_qualite() const { return mQualite; }

void cCompression::set_largeur(const unsigned largeur) { mLargeur = largeur; }

void cCompression::set_hauteur(const unsigned hauteur) { mHauteur = hauteur; }

void cCompression::set_qualite(const unsigned qualite) { mQualite = qualite; }

void cCompression::Calcul_DCT_Block(double DCT_Img[][8], int Bloc8x8[][8]) {

    for (unsigned u=0; u<8; u++) {
        for (unsigned v=0; v<8; v++) {
            double somme_u = 0;
            for (unsigned x=0; x<8; x++) {
                double somme_v = 0;
                for (unsigned y=0; y<8; y++) {
                    somme_v += (Bloc8x8[x][y]-128)*cos(((2*x+1)*pi*u)/16)*cos(((2*y+1)*pi*v)/16);
                }
                somme_u += somme_v;
            }
            DCT_Img[u][v] = C(u)*C(v)*somme_u/4;
        }
    }
}
