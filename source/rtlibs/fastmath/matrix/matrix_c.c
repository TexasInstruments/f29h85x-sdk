//=============================================================================
// File:    Library Of Matrix Operations In C
//=============================================================================
// Contents:
//  32-bit Floating-Point Functions:
//      void  matrix_mpy_f32_4by4(float Ma_f32[][4], float Mb_f32[][4], float Mc_f32[][4])
//      float matrix_invert_determinant_f32_4by4(float Ma_f32[][4], float Mb_f32[][4])
//      float matrix_determinant_f32_4by4(float Ma_f32[][4])
//      void  matrix_invert_f32_4by4(float Ma_f32[][4], float Mb_f32[][4], float Det)
//
//  64-bit Floating-Point Functions:
//      void  matrix_mpy_f64_4by4(float Ma_f32[][4], float Mb_f32[][4], float Mc_f32[][4])
//

#include "float.h"
#include "matrix.h"
#include "stdint.h"

typedef struct {
    float   f0;
    float   f1;
    float   f2;
    float   f3;
} QUAD_F32;

#if 1
void    matrix_mpy_f32_4by4(float Ma_f32[][4], float Mb_f32[][4], float Mc_f32[][4])
{
    QUAD_F32    Ma;
    QUAD_F32    Mb;
    QUAD_F32    Mc;

//    Mc_f32[0][0] = (Mb_f32[0][0] * Ma_f32[0][0]) + (Mb_f32[0][1] * Ma_f32[1][0]) + (Mb_f32[0][2] * Ma_f32[2][0]) + (Mb_f32[0][3] * Ma_f32[3][0]);
//    Mc_f32[0][1] = (Mb_f32[0][0] * Ma_f32[0][1]) + (Mb_f32[0][1] * Ma_f32[1][1]) + (Mb_f32[0][2] * Ma_f32[2][1]) + (Mb_f32[0][3] * Ma_f32[3][1]);
//    Mc_f32[0][2] = (Mb_f32[0][0] * Ma_f32[0][2]) + (Mb_f32[0][1] * Ma_f32[1][2]) + (Mb_f32[0][2] * Ma_f32[2][2]) + (Mb_f32[0][3] * Ma_f32[3][2]);
//    Mc_f32[0][3] = (Mb_f32[0][0] * Ma_f32[0][3]) + (Mb_f32[0][1] * Ma_f32[1][3]) + (Mb_f32[0][2] * Ma_f32[2][3]) + (Mb_f32[0][3] * Ma_f32[3][3]);

    Mb.f0 = Mb_f32[0][0];
    Mb.f1 = Mb_f32[0][1];
    Ma.f0 = Ma_f32[0][0];
    Ma.f1 = Ma_f32[0][1];
    Mc.f0 = (Mb.f0 * Ma.f0);
    Mc.f1 = (Mb.f0 * Ma.f1);
    Ma.f2 = Ma_f32[0][2];
    Ma.f3 = Ma_f32[0][3];
    Mc.f2 = (Mb.f0 * Ma.f2);
    Mc.f3 = (Mb.f0 * Ma.f3);

    Ma.f0 = Ma_f32[1][0];
    Ma.f1 = Ma_f32[1][1];
    Mc.f0 += (Mb.f1 * Ma.f0);
    Mc.f1 += (Mb.f1 * Ma.f1);
    Ma.f2 = Ma_f32[1][2];
    Ma.f3 = Ma_f32[1][3];
    Mc.f2 += (Mb.f1 * Ma.f2);
    Mc.f3 += (Mb.f1 * Ma.f3);

    Mb.f2 = Mb_f32[0][2];
    Mb.f3 = Mb_f32[0][3];
    Ma.f0 = Ma_f32[2][0];
    Ma.f1 = Ma_f32[2][1];
    Mc.f0 += (Mb.f2 * Ma.f0);
    Mc.f1 += (Mb.f2 * Ma.f1);
    Ma.f2 = Ma_f32[2][2];
    Ma.f3 = Ma_f32[2][3];
    Mc.f2 += (Mb.f2 * Ma.f2);
    Mc.f3 += (Mb.f2 * Ma.f3);

    Ma.f0 = Ma_f32[3][0];
    Ma.f1 = Ma_f32[3][1];
    Mc.f0 += (Mb.f3 * Ma.f0);
    Mc.f1 += (Mb.f3 * Ma.f1);
    Ma.f2 = Ma_f32[3][2];
    Ma.f3 = Ma_f32[3][3];
    Mc.f2 += (Mb.f3 * Ma.f2);
    Mc.f3 += (Mb.f3 * Ma.f3);

    Mc_f32[0][0] = Mc.f0;
    Mc_f32[0][1] = Mc.f1;
    Mc_f32[0][2] = Mc.f2;
    Mc_f32[0][3] = Mc.f3;


//    Mc_f32[1][0] = (Mb_f32[1][0] * Ma_f32[0][0]) + (Mb_f32[1][1] * Ma_f32[1][0]) + (Mb_f32[1][2] * Ma_f32[2][0]) + (Mb_f32[1][3] * Ma_f32[3][0]);
//    Mc_f32[1][1] = (Mb_f32[1][0] * Ma_f32[0][1]) + (Mb_f32[1][1] * Ma_f32[1][1]) + (Mb_f32[1][2] * Ma_f32[2][1]) + (Mb_f32[1][3] * Ma_f32[3][1]);
//    Mc_f32[1][2] = (Mb_f32[1][0] * Ma_f32[0][2]) + (Mb_f32[1][1] * Ma_f32[1][2]) + (Mb_f32[1][2] * Ma_f32[2][2]) + (Mb_f32[1][3] * Ma_f32[3][2]);
//    Mc_f32[1][3] = (Mb_f32[1][0] * Ma_f32[0][3]) + (Mb_f32[1][1] * Ma_f32[1][3]) + (Mb_f32[1][2] * Ma_f32[2][3]) + (Mb_f32[1][3] * Ma_f32[3][3]);

    Mb.f0 = Mb_f32[1][0];
    Mb.f1 = Mb_f32[1][1];
    Ma.f0 = Ma_f32[0][0];
    Ma.f1 = Ma_f32[0][1];
    Mc.f0 = (Mb.f0 * Ma.f0);
    Mc.f1 = (Mb.f0 * Ma.f1);
    Ma.f2 = Ma_f32[0][2];
    Ma.f3 = Ma_f32[0][3];
    Mc.f2 = (Mb.f0 * Ma.f2);
    Mc.f3 = (Mb.f0 * Ma.f3);

    Ma.f0 = Ma_f32[1][0];
    Ma.f1 = Ma_f32[1][1];
    Mc.f0 += (Mb.f1 * Ma.f0);
    Mc.f1 += (Mb.f1 * Ma.f1);
    Ma.f2 = Ma_f32[1][2];
    Ma.f3 = Ma_f32[1][3];
    Mc.f2 += (Mb.f1 * Ma.f2);
    Mc.f3 += (Mb.f1 * Ma.f3);

    Mb.f2 = Mb_f32[1][2];
    Mb.f3 = Mb_f32[1][3];
    Ma.f0 = Ma_f32[2][0];
    Ma.f1 = Ma_f32[2][1];
    Mc.f0 += (Mb.f2 * Ma.f0);
    Mc.f1 += (Mb.f2 * Ma.f1);
    Ma.f2 = Ma_f32[2][2];
    Ma.f3 = Ma_f32[2][3];
    Mc.f2 += (Mb.f2 * Ma.f2);
    Mc.f3 += (Mb.f2 * Ma.f3);

    Ma.f0 = Ma_f32[3][0];
    Ma.f1 = Ma_f32[3][1];
    Mc.f0 += (Mb.f3 * Ma.f0);
    Mc.f1 += (Mb.f3 * Ma.f1);
    Ma.f2 = Ma_f32[3][2];
    Ma.f3 = Ma_f32[3][3];
    Mc.f2 += (Mb.f3 * Ma.f2);
    Mc.f3 += (Mb.f3 * Ma.f3);

    Mc_f32[1][0] = Mc.f0;
    Mc_f32[1][1] = Mc.f1;
    Mc_f32[1][2] = Mc.f2;
    Mc_f32[1][3] = Mc.f3;


//    Mc_f32[2][0] = (Mb_f32[2][0] * Ma_f32[0][0]) + (Mb_f32[2][1] * Ma_f32[1][0]) + (Mb_f32[2][2] * Ma_f32[2][0]) + (Mb_f32[2][3] * Ma_f32[3][0]);
//    Mc_f32[2][1] = (Mb_f32[2][0] * Ma_f32[0][1]) + (Mb_f32[2][1] * Ma_f32[1][1]) + (Mb_f32[2][2] * Ma_f32[2][1]) + (Mb_f32[2][3] * Ma_f32[3][1]);
//    Mc_f32[2][2] = (Mb_f32[2][0] * Ma_f32[0][2]) + (Mb_f32[2][1] * Ma_f32[1][2]) + (Mb_f32[2][2] * Ma_f32[2][2]) + (Mb_f32[2][3] * Ma_f32[3][2]);
//    Mc_f32[2][3] = (Mb_f32[2][0] * Ma_f32[0][3]) + (Mb_f32[2][1] * Ma_f32[1][3]) + (Mb_f32[2][2] * Ma_f32[2][3]) + (Mb_f32[2][3] * Ma_f32[3][3]);

    Mb.f0 = Mb_f32[2][0];
    Mb.f1 = Mb_f32[2][1];
    Ma.f0 = Ma_f32[0][0];
    Ma.f1 = Ma_f32[0][1];
    Mc.f0 = (Mb.f0 * Ma.f0);
    Mc.f1 = (Mb.f0 * Ma.f1);
    Ma.f2 = Ma_f32[0][2];
    Ma.f3 = Ma_f32[0][3];
    Mc.f2 = (Mb.f0 * Ma.f2);
    Mc.f3 = (Mb.f0 * Ma.f3);

    Ma.f0 = Ma_f32[1][0];
    Ma.f1 = Ma_f32[1][1];
    Mc.f0 += (Mb.f1 * Ma.f0);
    Mc.f1 += (Mb.f1 * Ma.f1);
    Ma.f2 = Ma_f32[1][2];
    Ma.f3 = Ma_f32[1][3];
    Mc.f2 += (Mb.f1 * Ma.f2);
    Mc.f3 += (Mb.f1 * Ma.f3);

    Mb.f2 = Mb_f32[2][2];
    Mb.f3 = Mb_f32[2][3];
    Ma.f0 = Ma_f32[2][0];
    Ma.f1 = Ma_f32[2][1];
    Mc.f0 += (Mb.f2 * Ma.f0);
    Mc.f1 += (Mb.f2 * Ma.f1);
    Ma.f2 = Ma_f32[2][2];
    Ma.f3 = Ma_f32[2][3];
    Mc.f2 += (Mb.f2 * Ma.f2);
    Mc.f3 += (Mb.f2 * Ma.f3);

    Ma.f0 = Ma_f32[3][0];
    Ma.f1 = Ma_f32[3][1];
    Mc.f0 += (Mb.f3 * Ma.f0);
    Mc.f1 += (Mb.f3 * Ma.f1);
    Ma.f2 = Ma_f32[3][2];
    Ma.f3 = Ma_f32[3][3];
    Mc.f2 += (Mb.f3 * Ma.f2);
    Mc.f3 += (Mb.f3 * Ma.f3);

    Mc_f32[2][0] = Mc.f0;
    Mc_f32[2][1] = Mc.f1;
    Mc_f32[2][2] = Mc.f2;
    Mc_f32[2][3] = Mc.f3;

//    Mc_f32[3][0] = (Mb_f32[3][0] * Ma_f32[0][0]) + (Mb_f32[3][1] * Ma_f32[1][0]) + (Mb_f32[3][2] * Ma_f32[2][0]) + (Mb_f32[3][3] * Ma_f32[3][0]);
//    Mc_f32[3][1] = (Mb_f32[3][0] * Ma_f32[0][1]) + (Mb_f32[3][1] * Ma_f32[1][1]) + (Mb_f32[3][2] * Ma_f32[2][1]) + (Mb_f32[3][3] * Ma_f32[3][1]);
//    Mc_f32[3][2] = (Mb_f32[3][0] * Ma_f32[0][2]) + (Mb_f32[3][1] * Ma_f32[1][2]) + (Mb_f32[3][2] * Ma_f32[2][2]) + (Mb_f32[3][3] * Ma_f32[3][2]);
//    Mc_f32[3][3] = (Mb_f32[3][0] * Ma_f32[0][3]) + (Mb_f32[3][1] * Ma_f32[1][3]) + (Mb_f32[3][2] * Ma_f32[2][3]) + (Mb_f32[3][3] * Ma_f32[3][3]);

    Mb.f0 = Mb_f32[3][0];
    Mb.f1 = Mb_f32[3][1];
    Ma.f0 = Ma_f32[0][0];
    Ma.f1 = Ma_f32[0][1];
    Mc.f0 = (Mb.f0 * Ma.f0);
    Mc.f1 = (Mb.f0 * Ma.f1);
    Ma.f2 = Ma_f32[0][2];
    Ma.f3 = Ma_f32[0][3];
    Mc.f2 = (Mb.f0 * Ma.f2);
    Mc.f3 = (Mb.f0 * Ma.f3);

    Ma.f0 = Ma_f32[1][0];
    Ma.f1 = Ma_f32[1][1];
    Mc.f0 += (Mb.f1 * Ma.f0);
    Mc.f1 += (Mb.f1 * Ma.f1);
    Ma.f2 = Ma_f32[1][2];
    Ma.f3 = Ma_f32[1][3];
    Mc.f2 += (Mb.f1 * Ma.f2);
    Mc.f3 += (Mb.f1 * Ma.f3);

    Mb.f2 = Mb_f32[3][2];
    Mb.f3 = Mb_f32[3][3];
    Ma.f0 = Ma_f32[2][0];
    Ma.f1 = Ma_f32[2][1];
    Mc.f0 += (Mb.f2 * Ma.f0);
    Mc.f1 += (Mb.f2 * Ma.f1);
    Ma.f2 = Ma_f32[2][2];
    Ma.f3 = Ma_f32[2][3];
    Mc.f2 += (Mb.f2 * Ma.f2);
    Mc.f3 += (Mb.f2 * Ma.f3);

    Ma.f0 = Ma_f32[3][0];
    Ma.f1 = Ma_f32[3][1];
    Mc.f0 += (Mb.f3 * Ma.f0);
    Mc.f1 += (Mb.f3 * Ma.f1);
    Ma.f2 = Ma_f32[3][2];
    Ma.f3 = Ma_f32[3][3];
    Mc.f2 += (Mb.f3 * Ma.f2);
    Mc.f3 += (Mb.f3 * Ma.f3);

    Mc_f32[3][0] = Mc.f0;
    Mc_f32[3][1] = Mc.f1;
    Mc_f32[3][2] = Mc.f2;
    Mc_f32[3][3] = Mc.f3;
}
#else
void    matrix_mpy_f32_4by4(float Ma_f32[][4], float Mb_f32[][4], float Mc_f32[][4])
{
    int32_t i,j,k;
    for (i=0; i<4; i++) 
    {
        for (j=0; j<4; j++) 
        {
            float32_t temp = 0;
            for(k=0;k<4;k++)
            {
                temp += Ma_f32[i][k] * Mb_f32[k][j];
            }
            Mc_f32[i][j] = temp;
        }
    }
}

#endif

void    matrix_mpy_f64_4by4(double Ma_f64[][4], double Mb_f64[][4], double Mc_f64[][4])
{
    double Ma;
    double Mb;
    double Mc_f0;
    double Mc_f1;
    double Mc_f2;
    double Mc_f3;

//    Mc_f64[0][0] = (Mb_f64[0][0] * Ma_f64[0][0]) + (Mb_f64[0][1] * Ma_f64[1][0]) + (Mb_f64[0][2] * Ma_f64[2][0]) + (Mb_f64[0][3] * Ma_f64[3][0]);
//    Mc_f64[0][1] = (Mb_f64[0][0] * Ma_f64[0][1]) + (Mb_f64[0][1] * Ma_f64[1][1]) + (Mb_f64[0][2] * Ma_f64[2][1]) + (Mb_f64[0][3] * Ma_f64[3][1]);
//    Mc_f64[0][2] = (Mb_f64[0][0] * Ma_f64[0][2]) + (Mb_f64[0][1] * Ma_f64[1][2]) + (Mb_f64[0][2] * Ma_f64[2][2]) + (Mb_f64[0][3] * Ma_f64[3][2]);
//    Mc_f64[0][3] = (Mb_f64[0][0] * Ma_f64[0][3]) + (Mb_f64[0][1] * Ma_f64[1][3]) + (Mb_f64[0][2] * Ma_f64[2][3]) + (Mb_f64[0][3] * Ma_f64[3][3]);

    Mb     = Mb_f64[0][0];
    Ma     = Ma_f64[0][0];
    Mc_f0  = Mb * Ma;
    Ma     = Ma_f64[0][1];
    Mc_f1  = Mb * Ma;
    Ma     = Ma_f64[0][2];
    Mc_f2  = Mb * Ma;
    Ma     = Ma_f64[0][3];
    Mc_f3  = Mb * Ma;

    Mb     = Mb_f64[0][1];
    Ma     = Ma_f64[1][0];
    Mc_f0 += Mb * Ma;
    Ma     = Ma_f64[1][1];
    Mc_f1 += Mb * Ma;
    Ma     = Ma_f64[1][2];
    Mc_f2 += Mb * Ma;
    Ma     = Ma_f64[1][3];
    Mc_f3 += Mb * Ma;

    Mb     = Mb_f64[0][2];
    Ma     = Ma_f64[2][0];
    Mc_f0 += Mb * Ma;
    Ma     = Ma_f64[2][1];
    Mc_f1 += Mb * Ma;
    Ma     = Ma_f64[2][2];
    Mc_f2 += Mb * Ma;
    Ma     = Ma_f64[2][3];
    Mc_f3 += Mb * Ma;

    Mb     = Mb_f64[0][3];
    Ma     = Ma_f64[3][0];
    Mc_f0 += Mb * Ma;
    Ma     = Ma_f64[3][1];
    Mc_f1 += Mb * Ma;
    Ma     = Ma_f64[3][2];
    Mc_f2 += Mb * Ma;
    Ma     = Ma_f64[3][3];
    Mc_f3 += Mb * Ma;

    Mc_f64[0][0] = Mc_f0;
    Mc_f64[0][1] = Mc_f1;
    Mc_f64[0][2] = Mc_f2;
    Mc_f64[0][3] = Mc_f3;

//    Mc_f64[1][0] = (Mb_f64[1][0] * Ma_f64[0][0]) + (Mb_f64[1][1] * Ma_f64[1][0]) + (Mb_f64[1][2] * Ma_f64[2][0]) + (Mb_f64[1][3] * Ma_f64[3][0]);
//    Mc_f64[1][1] = (Mb_f64[1][0] * Ma_f64[0][1]) + (Mb_f64[1][1] * Ma_f64[1][1]) + (Mb_f64[1][2] * Ma_f64[2][1]) + (Mb_f64[1][3] * Ma_f64[3][1]);
//    Mc_f64[1][2] = (Mb_f64[1][0] * Ma_f64[0][2]) + (Mb_f64[1][1] * Ma_f64[1][2]) + (Mb_f64[1][2] * Ma_f64[2][2]) + (Mb_f64[1][3] * Ma_f64[3][2]);
//    Mc_f64[1][3] = (Mb_f64[1][0] * Ma_f64[0][3]) + (Mb_f64[1][1] * Ma_f64[1][3]) + (Mb_f64[1][2] * Ma_f64[2][3]) + (Mb_f64[1][3] * Ma_f64[3][3]);

    Mb     = Mb_f64[1][0];
    Ma     = Ma_f64[0][0];
    Mc_f0  = Mb * Ma;
    Ma     = Ma_f64[0][1];
    Mc_f1  = Mb * Ma;
    Ma     = Ma_f64[0][2];
    Mc_f2  = Mb * Ma;
    Ma     = Ma_f64[0][3];
    Mc_f3  = Mb * Ma;

    Mb     = Mb_f64[1][1];
    Ma     = Ma_f64[1][0];
    Mc_f0 += Mb * Ma;
    Ma     = Ma_f64[1][1];
    Mc_f1 += Mb * Ma;
    Ma     = Ma_f64[1][2];
    Mc_f2 += Mb * Ma;
    Ma     = Ma_f64[1][3];
    Mc_f3 += Mb * Ma;

    Mb     = Mb_f64[1][2];
    Ma     = Ma_f64[2][0];
    Mc_f0 += Mb * Ma;
    Ma     = Ma_f64[2][1];
    Mc_f1 += Mb * Ma;
    Ma     = Ma_f64[2][2];
    Mc_f2 += Mb * Ma;
    Ma     = Ma_f64[2][3];
    Mc_f3 += Mb * Ma;

    Mb     = Mb_f64[1][3];
    Ma     = Ma_f64[3][0];
    Mc_f0 += Mb * Ma;
    Ma     = Ma_f64[3][1];
    Mc_f1 += Mb * Ma;
    Ma     = Ma_f64[3][2];
    Mc_f2 += Mb * Ma;
    Ma     = Ma_f64[3][3];
    Mc_f3 += Mb * Ma;

    Mc_f64[1][0] = Mc_f0;
    Mc_f64[1][1] = Mc_f1;
    Mc_f64[1][2] = Mc_f2;
    Mc_f64[1][3] = Mc_f3;

//    Mc_f64[2][0] = (Mb_f64[2][0] * Ma_f64[0][0]) + (Mb_f64[2][1] * Ma_f64[1][0]) + (Mb_f64[2][2] * Ma_f64[2][0]) + (Mb_f64[2][3] * Ma_f64[3][0]);
//    Mc_f64[2][1] = (Mb_f64[2][0] * Ma_f64[0][1]) + (Mb_f64[2][1] * Ma_f64[1][1]) + (Mb_f64[2][2] * Ma_f64[2][1]) + (Mb_f64[2][3] * Ma_f64[3][1]);
//    Mc_f64[2][2] = (Mb_f64[2][0] * Ma_f64[0][2]) + (Mb_f64[2][1] * Ma_f64[1][2]) + (Mb_f64[2][2] * Ma_f64[2][2]) + (Mb_f64[2][3] * Ma_f64[3][2]);
//    Mc_f64[2][3] = (Mb_f64[2][0] * Ma_f64[0][3]) + (Mb_f64[2][1] * Ma_f64[1][3]) + (Mb_f64[2][2] * Ma_f64[2][3]) + (Mb_f64[2][3] * Ma_f64[3][3]);

    Mb     = Mb_f64[2][0];
    Ma     = Ma_f64[0][0];
    Mc_f0  = Mb * Ma;
    Ma     = Ma_f64[0][1];
    Mc_f1  = Mb * Ma;
    Ma     = Ma_f64[0][2];
    Mc_f2  = Mb * Ma;
    Ma     = Ma_f64[0][3];
    Mc_f3  = Mb * Ma;

    Mb     = Mb_f64[2][1];
    Ma     = Ma_f64[1][0];
    Mc_f0 += Mb * Ma;
    Ma     = Ma_f64[1][1];
    Mc_f1 += Mb * Ma;
    Ma     = Ma_f64[1][2];
    Mc_f2 += Mb * Ma;
    Ma     = Ma_f64[1][3];
    Mc_f3 += Mb * Ma;

    Mb     = Mb_f64[2][2];
    Ma     = Ma_f64[2][0];
    Mc_f0 += Mb * Ma;
    Ma     = Ma_f64[2][1];
    Mc_f1 += Mb * Ma;
    Ma     = Ma_f64[2][2];
    Mc_f2 += Mb * Ma;
    Ma     = Ma_f64[2][3];
    Mc_f3 += Mb * Ma;

    Mb     = Mb_f64[2][3];
    Ma     = Ma_f64[3][0];
    Mc_f0 += Mb * Ma;
    Ma     = Ma_f64[3][1];
    Mc_f1 += Mb * Ma;
    Ma     = Ma_f64[3][2];
    Mc_f2 += Mb * Ma;
    Ma     = Ma_f64[3][3];
    Mc_f3 += Mb * Ma;

    Mc_f64[2][0] = Mc_f0;
    Mc_f64[2][1] = Mc_f1;
    Mc_f64[2][2] = Mc_f2;
    Mc_f64[2][3] = Mc_f3;

//    Mc_f64[3][0] = (Mb_f64[3][0] * Ma_f64[0][0]) + (Mb_f64[3][1] * Ma_f64[1][0]) + (Mb_f64[3][2] * Ma_f64[2][0]) + (Mb_f64[3][3] * Ma_f64[3][0]);
//    Mc_f64[3][1] = (Mb_f64[3][0] * Ma_f64[0][1]) + (Mb_f64[3][1] * Ma_f64[1][1]) + (Mb_f64[3][2] * Ma_f64[2][1]) + (Mb_f64[3][3] * Ma_f64[3][1]);
//    Mc_f64[3][2] = (Mb_f64[3][0] * Ma_f64[0][2]) + (Mb_f64[3][1] * Ma_f64[1][2]) + (Mb_f64[3][2] * Ma_f64[2][2]) + (Mb_f64[3][3] * Ma_f64[3][2]);
//    Mc_f64[3][3] = (Mb_f64[3][0] * Ma_f64[0][3]) + (Mb_f64[3][1] * Ma_f64[1][3]) + (Mb_f64[3][2] * Ma_f64[2][3]) + (Mb_f64[3][3] * Ma_f64[3][3]);

    Mb     = Mb_f64[3][0];
    Ma     = Ma_f64[0][0];
    Mc_f0  = Mb * Ma;
    Ma     = Ma_f64[0][1];
    Mc_f1  = Mb * Ma;
    Ma     = Ma_f64[0][2];
    Mc_f2  = Mb * Ma;
    Ma     = Ma_f64[0][3];
    Mc_f3  = Mb * Ma;

    Mb     = Mb_f64[3][1];
    Ma     = Ma_f64[1][0];
    Mc_f0 += Mb * Ma;
    Ma     = Ma_f64[1][1];
    Mc_f1 += Mb * Ma;
    Ma     = Ma_f64[1][2];
    Mc_f2 += Mb * Ma;
    Ma     = Ma_f64[1][3];
    Mc_f3 += Mb * Ma;

    Mb     = Mb_f64[3][2];
    Ma     = Ma_f64[2][0];
    Mc_f0 += Mb * Ma;
    Ma     = Ma_f64[2][1];
    Mc_f1 += Mb * Ma;
    Ma     = Ma_f64[2][2];
    Mc_f2 += Mb * Ma;
    Ma     = Ma_f64[2][3];
    Mc_f3 += Mb * Ma;

    Mb     = Mb_f64[3][3];
    Ma     = Ma_f64[3][0];
    Mc_f0 += Mb * Ma;
    Ma     = Ma_f64[3][1];
    Mc_f1 += Mb * Ma;
    Ma     = Ma_f64[3][2];
    Mc_f2 += Mb * Ma;
    Ma     = Ma_f64[3][3];
    Mc_f3 += Mb * Ma;

    Mc_f64[3][0] = Mc_f0;
    Mc_f64[3][1] = Mc_f1;
    Mc_f64[3][2] = Mc_f2;
    Mc_f64[3][3] = Mc_f3;
}


#define M11     Ma_f32[0][0]
#define M12     Ma_f32[0][1]
#define M13     Ma_f32[0][2]
#define M14     Ma_f32[0][3]

#define M21     Ma_f32[1][0]
#define M22     Ma_f32[1][1]
#define M23     Ma_f32[1][2]
#define M24     Ma_f32[1][3]

#define M31     Ma_f32[2][0]
#define M32     Ma_f32[2][1]
#define M33     Ma_f32[2][2]
#define M34     Ma_f32[2][3]

#define M41     Ma_f32[3][0]
#define M42     Ma_f32[3][1]
#define M43     Ma_f32[3][2]
#define M44     Ma_f32[3][3]

#define ans11   Mb_f32[0][0]
#define ans12   Mb_f32[0][1]
#define ans13   Mb_f32[0][2]
#define ans14   Mb_f32[0][3]

#define ans21   Mb_f32[1][0]
#define ans22   Mb_f32[1][1]
#define ans23   Mb_f32[1][2]
#define ans24   Mb_f32[1][3]

#define ans31   Mb_f32[2][0]
#define ans32   Mb_f32[2][1]
#define ans33   Mb_f32[2][2]
#define ans34   Mb_f32[2][3]

#define ans41   Mb_f32[3][0]
#define ans42   Mb_f32[3][1]
#define ans43   Mb_f32[3][2]
#define ans44   Mb_f32[3][3]

float   matrix_determinant_f32_4by4(float Ma_f32[][4])
{
    float   Det;

    Det =   (M11 * M22 * M33 * M44 ) + (M11 * M23 * M34 * M42 ) + (M11 * M24 * M32 * M43 )
          - (M11 * M24 * M33 * M42 ) - (M11 * M23 * M32 * M44 ) - (M11 * M22 * M34 * M43 )
          - (M12 * M21 * M33 * M44 ) - (M13 * M21 * M34 * M42 ) - (M14 * M21 * M32 * M43 )
          + (M14 * M21 * M33 * M42 ) + (M13 * M21 * M32 * M44 ) + (M12 * M21 * M34 * M43 )
          + (M12 * M23 * M31 * M44 ) + (M13 * M24 * M31 * M42 ) + (M14 * M22 * M31 * M43 )
          - (M14 * M23 * M31 * M42 ) - (M13 * M22 * M31 * M44 ) - (M12 * M24 * M31 * M43 )
          - (M12 * M23 * M34 * M41 ) - (M13 * M24 * M32 * M41 ) - (M14 * M22 * M33 * M41 )
          + (M14 * M23 * M32 * M41 ) + (M13 * M22 * M34 * M41 ) + (M12 * M24 * M33 * M41 );

    return Det;
}

void    matrix_invert_f32_4by4(float Ma_f32[][4], float Mb_f32[][4], float Det)
{
    float   Inv_Det = 1.0/Det;

    ans11 = ( M22*M33*M44 + M23*M34*M42 + M24*M32*M43 - M24*M33*M42 - M23*M32*M44 - M22*M34*M43) * Inv_Det;
    ans12 = (-M12*M33*M44 - M13*M34*M42 - M14*M32*M43 + M14*M33*M42 + M13*M32*M44 + M12*M34*M43) * Inv_Det;
    ans13 = ( M12*M23*M44 + M13*M24*M42 + M14*M22*M43 - M14*M23*M42 - M13*M22*M44 - M12*M24*M43) * Inv_Det;
    ans14 = (-M12*M23*M34 - M13*M24*M32 - M14*M22*M33 + M14*M23*M32 + M13*M22*M34 + M12*M24*M33) * Inv_Det;

    ans21 = (-M21*M33*M44 - M23*M34*M41 - M24*M31*M43 + M24*M33*M41 + M23*M31*M44 + M21*M34*M43) * Inv_Det;
    ans22 = ( M11*M33*M44 + M13*M34*M41 + M14*M31*M43 - M14*M33*M41 - M13*M31*M44 - M11*M34*M43) * Inv_Det;
    ans23 = (-M11*M23*M44 - M13*M24*M41 - M14*M21*M43 + M14*M23*M41 + M13*M21*M44 + M11*M24*M43) * Inv_Det;
    ans24 = ( M11*M23*M34 + M13*M24*M31 + M14*M21*M33 - M14*M23*M31 - M13*M21*M34 - M11*M24*M33) * Inv_Det;

    ans31 = ( M21*M32*M44 + M22*M34*M41 + M24*M31*M42 - M24*M32*M41 - M22*M31*M44 - M21*M34*M42) * Inv_Det;
    ans32 = (-M11*M32*M44 - M12*M34*M41 - M14*M31*M42 + M14*M32*M41 + M12*M31*M44 + M11*M34*M42) * Inv_Det;
    ans33 = ( M11*M22*M44 + M12*M24*M41 + M14*M21*M42 - M14*M22*M41 - M12*M21*M44 - M11*M24*M42) * Inv_Det;
    ans34 = (-M11*M22*M34 - M12*M24*M31 - M14*M21*M32 + M14*M22*M31 + M12*M21*M34 + M11*M24*M32) * Inv_Det;

    ans41 = (-M21*M32*M43 - M22*M33*M41 - M23*M31*M42 + M23*M32*M41 + M22*M31*M43 + M21*M33*M42) * Inv_Det;
    ans42 = ( M11*M32*M43 + M12*M33*M41 + M13*M31*M42 - M13*M32*M41 - M12*M31*M43 - M11*M33*M42) * Inv_Det;
    ans43 = (-M11*M22*M43 - M12*M23*M41 - M13*M21*M42 + M13*M22*M41 + M12*M21*M43 + M11*M23*M42) * Inv_Det;
    ans44 = ( M11*M22*M33 + M12*M23*M31 + M13*M21*M32 - M13*M22*M31 - M12*M21*M33 - M11*M23*M32) * Inv_Det;
}

float    matrix_invert_determinant_f32_4by4(float Ma_f32[][4], float Mb_f32[][4])
{
    float   M_31mpy44 = (M31 * M44);
    float   M_32mpy44 = (M32 * M44);
    float   M_33mpy44 = (M33 * M44);

    float   M_31mpy43 = (M31 * M43);
    float   M_32mpy43 = (M32 * M43);
    float   M_34mpy43 = (M34 * M43);

    float   M_31mpy42 = (M31 * M42);
    float   M_33mpy42 = (M33 * M42);
    float   M_34mpy42 = (M34 * M42);

    float   M_32mpy41 = (M32 * M41);
    float   M_33mpy41 = (M33 * M41);
    float   M_34mpy41 = (M34 * M41);

    float   M_11mpy22 = (M11 * M22);
    float   M_11mpy23 = (M11 * M23);
    float   M_11mpy24 = (M11 * M24);

    float   M_12mpy21 = (M12 * M21);
    float   M_12mpy23 = (M12 * M23);
    float   M_12mpy24 = (M12 * M24);

    float   M_13mpy21 = (M13 * M21);
    float   M_13mpy22 = (M13 * M22);
    float   M_13mpy24 = (M13 * M24);

    float   M_14mpy21 = (M14 * M21);
    float   M_14mpy22 = (M14 * M22);
    float   M_14mpy23 = (M14 * M23);

    float   temp11 = ( M22*M_33mpy44 + M23*M_34mpy42 + M24*M_32mpy43 - M24*M_33mpy42 - M23*M_32mpy44 - M22*M_34mpy43);
    float   temp12 = (-M12*M_33mpy44 - M13*M_34mpy42 - M14*M_32mpy43 + M14*M_33mpy42 + M13*M_32mpy44 + M12*M_34mpy43);
    float   temp13 = ( M_12mpy23*M44 + M_13mpy24*M42 + M_14mpy22*M43 - M_14mpy23*M42 - M_13mpy22*M44 - M_12mpy24*M43);
    float   temp14 = (-M_12mpy23*M34 - M_13mpy24*M32 - M_14mpy22*M33 + M_14mpy23*M32 + M_13mpy22*M34 + M_12mpy24*M33);

    float   temp21 = (-M21*M_33mpy44 - M23*M_34mpy41 - M24*M_31mpy43 + M24*M_33mpy41 + M23*M_31mpy44 + M21*M_34mpy43);
    float   temp22 = ( M11*M_33mpy44 + M13*M_34mpy41 + M14*M_31mpy43 - M14*M_33mpy41 - M13*M_31mpy44 - M11*M_34mpy43);
    float   temp23 = (-M_11mpy23*M44 - M_13mpy24*M41 - M_14mpy21*M43 + M_14mpy23*M41 + M_13mpy21*M44 + M_11mpy24*M43);
    float   temp24 = ( M_11mpy23*M34 + M_13mpy24*M31 + M_14mpy21*M33 - M_14mpy23*M31 - M_13mpy21*M34 - M_11mpy24*M33);

    float   temp31 = ( M21*M_32mpy44 + M22*M_34mpy41 + M24*M_31mpy42 - M24*M_32mpy41 - M22*M_31mpy44 - M21*M_34mpy42);
    float   temp32 = (-M11*M_32mpy44 - M12*M_34mpy41 - M14*M_31mpy42 + M14*M_32mpy41 + M12*M_31mpy44 + M11*M_34mpy42);
    float   temp33 = ( M_11mpy22*M44 + M_12mpy24*M41 + M_14mpy21*M42 - M_14mpy22*M41 - M_12mpy21*M44 - M_11mpy24*M42);
    float   temp34 = (-M_11mpy22*M34 - M_12mpy24*M31 - M_14mpy21*M32 + M_14mpy22*M31 + M_12mpy21*M34 + M_11mpy24*M32);

    float   temp41 = (-M21*M_32mpy43 - M22*M_33mpy41 - M23*M_31mpy42 + M23*M_32mpy41 + M22*M_31mpy43 + M21*M_33mpy42);
    float   temp42 = ( M11*M_32mpy43 + M12*M_33mpy41 + M13*M_31mpy42 - M13*M_32mpy41 - M12*M_31mpy43 - M11*M_33mpy42);
    float   temp43 = (-M_11mpy22*M43 - M_12mpy23*M41 - M_13mpy21*M42 + M_13mpy22*M41 + M_12mpy21*M43 + M_11mpy23*M42);
    float   temp44 = ( M_11mpy22*M33 + M_12mpy23*M31 + M_13mpy21*M32 - M_13mpy22*M31 - M_12mpy21*M33 - M_11mpy23*M32);

    float   Det =   (M_11mpy22 * M_33mpy44 ) + (M_11mpy23 * M_34mpy42 ) + (M_11mpy24 * M_32mpy43 )
                  - (M_11mpy24 * M_33mpy42 ) - (M_11mpy23 * M_32mpy44 ) - (M_11mpy22 * M_34mpy43 )
                  - (M_12mpy21 * M_33mpy44 ) - (M_13mpy21 * M_34mpy42 ) - (M_14mpy21 * M_32mpy43 )
                  + (M_14mpy21 * M_33mpy42 ) + (M_13mpy21 * M_32mpy44 ) + (M_12mpy21 * M_34mpy43 )
                  + (M_12mpy23 * M_31mpy44 ) + (M_13mpy24 * M_31mpy42 ) + (M_14mpy22 * M_31mpy43 )
                  - (M_14mpy23 * M_31mpy42 ) - (M_13mpy22 * M_31mpy44 ) - (M_12mpy24 * M_31mpy43 )
                  - (M_12mpy23 * M_34mpy41 ) - (M_13mpy24 * M_32mpy41 ) - (M_14mpy22 * M_33mpy41 )
                  + (M_14mpy23 * M_32mpy41 ) + (M_13mpy22 * M_34mpy41 ) + (M_12mpy24 * M_33mpy41 );

    float   Inv_Det = 1.0/Det;

    ans11 = temp11 * Inv_Det;
    ans12 = temp12 * Inv_Det;
    ans13 = temp13 * Inv_Det;
    ans14 = temp14 * Inv_Det;
    ans21 = temp21 * Inv_Det;
    ans22 = temp22 * Inv_Det;
    ans23 = temp23 * Inv_Det;
    ans24 = temp24 * Inv_Det;
    ans31 = temp31 * Inv_Det;
    ans32 = temp32 * Inv_Det;
    ans33 = temp33 * Inv_Det;
    ans34 = temp34 * Inv_Det;
    ans41 = temp41 * Inv_Det;
    ans42 = temp42 * Inv_Det;
    ans43 = temp43 * Inv_Det;
    ans44 = temp44 * Inv_Det;

    return  Det;
}



//
// End of file.
//

