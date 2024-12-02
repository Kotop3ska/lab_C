#ifndef LAB11_H
#define LAB11_H

typedef struct 
{
    float elements[3][3];
    bool identiti;
} Matrix3x3;


Matrix3x3 CreateMatrix(float const elements[3][3]);
Matrix3x3 SumMatrix(const Matrix3x3 matrix1, const Matrix3x3 matrix2);
Matrix3x3 MulMatrix(const Matrix3x3 matrix1, const Matrix3x3 matrix2);
void MulScal(Matrix3x3* matrix, float a);
void Transpose(Matrix3x3* matrix);
float DetMatrix(Matrix3x3* matrix);
void InvMatrix(Matrix3x3* matrix);
#endif