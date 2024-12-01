#include <stdio.h>
#include <stdbool.h>


typedef struct 
{
    float elements[3][3];
    bool identiti;
} Matrix3x3;


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


void PrintMatrix(const Matrix3x3* matrix) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%.1f ", matrix->elements[i][j]);
        }
        printf("\n");
    }
    if (matrix->identiti)
        printf("single");
    else
        printf("not single");
}


int main()
{
    printf("1 – create matrix\n"
    "2 – sum of 2 matrices"
    "3 – multiplying 2 matrices\n"
    "4 – multiplying a matrix by a scalar\n" 
    "5 – transpose marix\n"
    "6 – get matrix determinant\n"
    "7 – define inverse matrix\n\n");

    int num = 0;
    do
    {
        printf("Choose function: ");
        scanf("%d", &num);

    } while (num < 1 || num > 7);

    if (num == 1)
    {
        float elements[3][3];
        printf("Input matrix:\n");
        for (int i = 0; i < 3; i++)
        {
            scanf("%f %f %f", &elements[i][0], &elements[i][1], &elements[i][2]);
        }
        Matrix3x3 matrix = CreateMatrix(elements);
        printf("Your matrix:\n");
        PrintMatrix(&matrix);
    } 

    else if (num == 2)
    {
        float elements1[3][3];
        float elements2[3][3];

        printf("Input matrix1:\n");
         for (int i = 0; i < 3; i++)
        {
            scanf("%f %f %f", &elements1[i][0], &elements1[i][1], &elements1[i][2]);
        }
        printf("\n");
        printf("Input matrix2:\n");
         for (int i = 0; i < 3; i++)
        {
            scanf("%f %f %f", &elements2[i][0], &elements2[i][1], &elements2[i][2]);
        }

        Matrix3x3 matrix1 = CreateMatrix(elements1);
        Matrix3x3 matrix2 = CreateMatrix(elements2);

        printf("\n");
        printf("Your matrix1:\n");
        PrintMatrix(&matrix1);
        printf("\n");
        printf("\n");
        printf("Your matrix2:\n");
        PrintMatrix(&matrix2);
        
        Matrix3x3 new_matrix = SumMatrix(matrix1, matrix2);
        printf("\n\nsum of 2 matrices:\n");
        PrintMatrix(&new_matrix);
    }

    else if (num == 3)
    {
       float elements1[3][3];
        float elements2[3][3];

        printf("Input matrix1:\n");
         for (int i = 0; i < 3; i++)
        {
            scanf("%f %f %f", &elements1[i][0], &elements1[i][1], &elements1[i][2]);
        }
        printf("\n");
        printf("Input matrix2:\n");
         for (int i = 0; i < 3; i++)
        {
            scanf("%f %f %f", &elements2[i][0], &elements2[i][1], &elements2[i][2]);
        }

        Matrix3x3 matrix1 = CreateMatrix(elements1);
        Matrix3x3 matrix2 = CreateMatrix(elements2);

        printf("\n");
        printf("Your matrix1:\n");
        PrintMatrix(&matrix1);
        printf("\n");
        printf("\n");
        printf("Your matrix2:\n");
        PrintMatrix(&matrix2); 

        Matrix3x3 new_matrix = MulMatrix(matrix1, matrix2);
        printf("\n\nmultiplying 2 matrices:\n");
        PrintMatrix(&new_matrix);
    }

    else if (num == 4)
    {
        float elements[3][3];
        printf("Input matrix:\n");
        for (int i = 0; i < 3; i++)
        {
            scanf("%f %f %f", &elements[i][0], &elements[i][1], &elements[i][2]);
        }
        Matrix3x3 matrix = CreateMatrix(elements);
        printf("\n");

        printf("Your matrix:\n");
        PrintMatrix(&matrix);
        printf("\n");
  
        float a;
        printf("\nInput a: ");
        scanf("%f", &a);
        printf("\n");

        MulScal(&matrix, a);
        printf("multiplying a matrix by a scala:r\n");
        PrintMatrix(&matrix);
    }
    
    else if (num == 5)
    {
        float elements[3][3];
        printf("Input matrix:\n");
        for (int i = 0; i < 3; i++)
        {
            scanf("%f %f %f", &elements[i][0], &elements[i][1], &elements[i][2]);
        }
        Matrix3x3 matrix = CreateMatrix(elements);
        printf("\n");

        printf("Your matrix:\n");
        PrintMatrix(&matrix);
        printf("\n");

        Transpose(&matrix);
        printf("\ntranspose marix:\n");
        PrintMatrix(&matrix);

    }

    else if (num == 6)
    {
        float elements[3][3];
        printf("Input matrix:\n");
        for (int i = 0; i < 3; i++)
        {
            scanf("%f %f %f", &elements[i][0], &elements[i][1], &elements[i][2]);
        }
        Matrix3x3 matrix = CreateMatrix(elements);
        printf("\n");

        printf("Your matrix:\n");
        PrintMatrix(&matrix);
        printf("\n");

        float det = DetMatrix(&matrix);
        printf("\nmatrix determinant: %f", det);

    }

    else
    {
        float elements[3][3];
        printf("Input matrix:\n");
        for (int i = 0; i < 3; i++)
        {
            scanf("%f %f %f", &elements[i][0], &elements[i][1], &elements[i][2]);
        }
        Matrix3x3 matrix = CreateMatrix(elements);
        printf("\n");

        printf("Your matrix:\n");
        PrintMatrix(&matrix);
        printf("\n");

        InvMatrix(&matrix);
        printf("\ninverse matrix:\n");
        PrintMatrix(&matrix);

    }
    
    return 0;
}