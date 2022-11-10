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
    int Q[8][8] = {{16, 11, 10, 16, 24, 40, 51, 61},
                {12, 12, 14, 19, 26, 58, 60, 55},
                {14, 13, 16, 24, 40, 57, 69, 56},
                {14, 17, 22, 29, 51, 87, 80, 62},
                {18, 22, 37, 56, 68, 109, 103, 77},
                {24, 35, 55, 64, 81, 104, 113, 92},
                {49, 64, 78, 87, 103, 121, 120, 101},
                {72, 92, 95, 98, 112, 100, 103, 99}};
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
    void Calcul_iDCT(double DCT_Img[][8], int Bloc8x8[][8]);
    void quant_JPEG(double DCT_Img[][8], int Img_Quant[][8]);
    void dequant_JPEG(int Img_Quant[][8], double img_DCT[][8]);
};
#endif // CCOMPRESSION_H
