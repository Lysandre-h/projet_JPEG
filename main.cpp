#include <iostream>
#include "cCompression.h"

int main() {
    const unsigned taille = 8;
    int bloc[taille][taille]= {139, 144, 149, 153, 155, 155, 155, 155,
                                            144, 151, 153, 156, 159, 156, 156, 156,
                                            150, 155, 160, 163, 158, 156, 156, 156,
                                            159, 161, 162, 160, 160, 159, 159, 159,
                                            159, 160, 161, 162, 162, 155, 155, 155,
                                            161, 161, 161, 161, 160, 157, 157, 157,
                                            162, 162, 161, 163, 162, 157, 157, 157,
                                            162, 162, 161, 161, 163, 158, 158, 158};


    cCompression c = cCompression(100, 100);
    double DCT_img[taille][taille];//[taille][taille];
    //unsigned char* pbloc = &bloc;
    c.Calcul_DCT_Block(DCT_img, bloc);
    for (unsigned i=0; i<taille; i++) {
        for (unsigned j=0; j<taille; j++) {
            std::cout << DCT_img[i][j] << ", ";
        }
    std::cout << std::endl;
    }
return 0;
}
