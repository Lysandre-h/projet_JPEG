#include <iostream>
#include "cCompression.h"

const unsigned taille = 8;
template <typename T> void display_bloc(T bloc[][8]) {
    for (unsigned i=0; i<taille; i++) {
        for (unsigned j=0; j<taille; j++) {
            std::cout << bloc[i][j] << ", ";
        }
    std::cout << std::endl;
    }
    std::cout << "________________________________________________\n\n";
}

int main() {
    // Test de la DCT
    int bloc[taille][taille]= {139, 144, 149, 153, 155, 155, 155, 155,
                                144, 151, 153, 156, 159, 156, 156, 156,
                                150, 155, 160, 163, 158, 156, 156, 156,
                                159, 161, 162, 160, 160, 159, 159, 159,
                                159, 160, 161, 162, 162, 155, 155, 155,
                                161, 161, 161, 161, 160, 157, 157, 157,
                                162, 162, 161, 163, 162, 157, 157, 157,
                                162, 162, 161, 161, 163, 158, 158, 158};
    cCompression c = cCompression(100, 100);
    double DCT_img[taille][taille];
    c.Calcul_DCT_Block(DCT_img, bloc);
    display_bloc(DCT_img);
    // Test de la DCT inverse
    int bloc_inverse[taille][taille];
    c.Calcul_iDCT(DCT_img, bloc_inverse);
    display_bloc(bloc_inverse);
    //Test de la quantification
    int bloc_quantif[taille][taille];
    c.quant_JPEG(DCT_img, bloc_quantif);
    display_bloc(bloc_quantif);
    // Test de la déquantification
    double bloc_dequantif[taille][taille];
    c.dequant_JPEG(bloc_quantif, bloc_dequantif);
    display_bloc(bloc_dequantif);
    double eqm = c.EQM(bloc);
    std::cout << eqm << std::endl;
    double taux = c.Taux_Compression(bloc);
    std::cout << taux << std::endl;
return 0;
}
