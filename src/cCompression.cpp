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
            double somme_x = 0;
            for (unsigned x=0; x<8; x++) {
                double somme_y = 0;
                for (unsigned y=0; y<8; y++) {
                    somme_y += (Bloc8x8[x][y]-128)*cos(((2*x+1)*pi*u)/16)*cos(((2*y+1)*pi*v)/16);
                }
                somme_x += somme_y;
            }
            DCT_Img[u][v] = C(u)*C(v)*somme_x/4;
        }
    }
}

void cCompression::Calcul_iDCT(double DCT_Img[][8], int Bloc8x8[][8]) {
    for (unsigned x=0; x<8; x++) {
        for (unsigned y=0; y<8; y++) {
            double somme_u = 0;
            for (unsigned u=0; u<8; u++) {
                double somme_v = 0;
                for (unsigned v=0; v<8; v++) {
                    somme_v += C(u)*C(v)*DCT_Img[u][v]*cos(((2*x+1)*pi*u)/16)*cos(((2*y+1)*pi*v)/16);
                }
                somme_u += somme_v;
            }
            Bloc8x8[x][y] = 128 + ceil(somme_u/4);
        }
    }
}

void cCompression::quant_JPEG(double DCT_Img[][8], int Img_Quant[][8]) {
    double lambda = (mQualite < 50 ? 5000 / mQualite : 200 - 2 * mQualite);
    int Q_tab[8][8];
    for (unsigned i=0; i<8; i++) {
        for (unsigned j=0; j<8; j++) {
            int val = floor((Q[i][j] * lambda + 50) / 100);
            if (val < 1) Q_tab[i][j] = 1;
            else if (val > 255) Q_tab[i][j] = 255;
            else Q_tab[i][j] = val;
        }
    }
    for (unsigned u=0; u<8; u++) {
        for (unsigned v=0; v<8; v++) {
            Img_Quant[u][v] = round(DCT_Img[u][v] / Q_tab[u][v]);
        }
    }
}

void cCompression::dequant_JPEG(int Img_Quant[][8], double img_DCT[][8]) {
    double lambda = (mQualite < 50 ? 5000 / mQualite : 200 - 2 * mQualite);
    int Q_tab[8][8];
    for (unsigned i=0; i<8; i++) {
        for (unsigned j=0; j<8; j++) {
            int val = floor((Q[i][j] * lambda + 50) / 100);
            if (val < 1) Q_tab[i][j] = 1;
            else if (val > 255) Q_tab[i][j] = 255;
            else Q_tab[i][j] = val;
        }
    }
    for (unsigned u=0; u<8; u++) {
        for (unsigned v=0; v<8; v++) {
            img_DCT[u][v] = (double)(Q_tab[u][v] * Img_Quant[u][v]);
        }
    }
}
double cCompression::EQM(int Bloc8x8[][8]) {
    double DCT_img[8][8];
    int quantif_img[8][8];
    double dequantif_img[8][8];
    int iDCT_img[8][8];
    Calcul_DCT_Block(DCT_img, Bloc8x8);
    quant_JPEG(DCT_img, quantif_img);
    dequant_JPEG(quantif_img, dequantif_img);
    Calcul_iDCT(dequantif_img, iDCT_img);

    double eqm = 0;
    for (unsigned u=0; u<8; u++) {
        for (unsigned v=0; v<8; v++) {
            eqm += (Bloc8x8[u][v] - iDCT_img[u][v]) * (Bloc8x8[u][v] - iDCT_img[u][v]);
        }
    }
    return eqm / (8 * 8);
}

double cCompression::Taux_Compression(int Bloc8x8[][8]) {
    double DCT_img[8][8];
    int quantif_img[8][8];
    double dequantif_img[8][8];
    Calcul_DCT_Block(DCT_img, Bloc8x8);
    quant_JPEG(DCT_img, quantif_img);
    dequant_JPEG(quantif_img, dequantif_img);
    double taux = 0;
    for (unsigned u=0; u<8; u++) {
        for (unsigned v=0; v<8; v++) {
            if (dequantif_img[u][v] != 0) taux ++;
        }
    }
    return 1 - (taux / (8 * 8));
}
