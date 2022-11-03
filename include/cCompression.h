#ifndef CCOMPRESSION_H
#define CCOMPRESSION_H
#include <cmath>

inline float C(unsigned k) {
    if (k==0) return 1/sqrt(2);
    else return 1;
}

class cCompression {
    unsigned mLargeur;
    unsigned mHauteur;
    unsigned char **mBuffer;
    unsigned mQualite;
public:
    cCompression(unsigned, unsigned, unsigned=50);
    virtual ~cCompression();
    unsigned get_largeur() const;
    unsigned get_hauteur() const;
    unsigned get_qualite() const;
    void set_largeur(const unsigned);
    void set_hauteur(const unsigned);
    void set_qualite(const unsigned);
    void Calcul_DCT_Block(double DCT_Img[][8], int Bloc8x8[][8]);

};

#endif // CCOMPRESSION_H
