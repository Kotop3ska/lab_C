#include <stdio.h>
#include <locale.h>
#include <stdbool.h>
#include "11.h"

Matrix3x3 CreateMatrix(float const elements[3][3])
{
    Matrix3x3 matrix;
    matrix.identiti = true;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            matrix.elements[i][j] = elements[i][j];
            if ((i == j && elements[i][j] != 1) || (i != j & elements[i][j] != 0))
            {
                matrix.identiti = false;
            }
        }
    }
    return matrix;
}


Matrix3x3 SumMatrix(const Matrix3x3 matrix1, const Matrix3x3 matrix2)
{
    Matrix3x3 new_matrix;
    new_matrix.identiti = true;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            new_matrix.elements[i][j] = matrix1.elements[i][j] + matrix2.elements[i][j];

            if ((i == j && new_matrix.elements[i][j] != 1) || (i != j && new_matrix.elements[i][j] != 0))
            {
                new_matrix.identiti = false;
            }
        }
    }
    return new_matrix;
}


Matrix3x3 MulMatrix(const Matrix3x3 matrix1, const Matrix3x3 matrix2)
{
    Matrix3x3 new_matrix;
    new_matrix.identiti = true;
    
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                new_matrix.elements[i][j] += matrix1.elements[i][k] * matrix2.elements[k][j];
            }

            if ((i == j && new_matrix.elements[i][j] != 1) || (i != j && new_matrix.elements[i][j] != 0))
            {
                new_matrix.identiti = false;
            }
        }
    }
    return new_matrix;
}


void MulScal(Matrix3x3* matrix, float a)
{
    matrix->identiti = true;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            matrix->elements[i][j] = matrix->elements[i][j] * a;

            if ((i == j && matrix->elements[i][j] != 1) || (i != j && matrix->elements[i][j] != 0))
            {
                matrix->identiti = false;
            }
        }
    }
}


void Transpose(Matrix3x3* matrix)
{
    if (!matrix->identiti)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = i + 1; j < 3; j++)
            {
                float temp = matrix->elements[i][j];
                matrix->elements[i][j] = matrix->elements[j][i];
                matrix->elements[j][i] = temp;
            }
        }
    }
}


float DetMatrix(Matrix3x3* matrix)
{
    if (!matrix->identiti)
    {
    float det;
    det = matrix->elements[0][0] * (matrix->elements[1][1] * matrix->elements[2][2] - matrix->elements[1][2] * matrix->elements[2][1]) -
        matrix->elements[0][1] * (matrix->elements[1][0] * matrix->elements[2][2] - matrix->elements[1][2] * matrix->elements[2][0]) +
        matrix->elements[0][2] * (matrix->elements[1][0] * matrix->elements[2][1] - matrix->elements[1][1] * matrix->elements[2][0]);

    return det;
    }

    else
        return 1;
}


void InvMatrix(Matrix3x3* matrix)
{
    if (!matrix->identiti)
    {
        float det = DetMatrix(matrix);

        if (det == 0)
        {
            printf("Error: Nul Det");
            return;
        }

        float cofactors[3][3] = 
        {{
            (matrix->elements[1][1] * matrix->elements[2][2] - matrix->elements[1][2] * matrix->elements[2][1]),
            -(matrix->elements[1][0] * matrix->elements[2][2] - matrix->elements[1][2] * matrix->elements[2][0]),
            (matrix->elements[1][0] * matrix->elements[2][1] - matrix->elements[1][1] * matrix->elements[2][0]) 
        },

        {
            -(matrix->elements[0][1] * matrix->elements[2][2] - matrix->elements[0][2] * matrix->elements[2][1]), 
            (matrix->elements[0][0] * matrix->elements[2][2] - matrix->elements[0][2] * matrix->elements[2][0]),
            -(matrix->elements[0][0] * matrix->elements[2][1] - matrix->elements[0][1] * matrix->elements[2][0])
        },

        {
            (matrix->elements[0][1] * matrix->elements[1][2] - matrix->elements[0][2] * matrix->elements[1][1]), 
            -(matrix->elements[0][0] * matrix->elements[1][2] - matrix->elements[0][2] * matrix->elements[1][0]),
            (matrix->elements[0][0] * matrix->elements[1][1] - matrix->elements[0][1] * matrix->elements[1][0])  
        }};
        
        Matrix3x3 cof = CreateMatrix(cofactors);


        Transpose(&cof);
        
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                matrix->elements[i][j] = cof.elements[i][j] / det;
            }
        }

    }
}
