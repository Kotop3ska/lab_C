#include <stdio.h> 
#include <time.h> 
#include <stdlib.h> 
#include <stdbool.h> 
#include <math.h> 
 
void Input_array1(float arr[][2], const int sizeX, const int sizeY) 
{ 
 float elem; 
 int i, j; 
 for (i = 0; i < sizeX; i++) 
 { 
  for (j = 0; j < sizeY; j++) 
  { 
   printf("array[%d][%d] = ", i, j); 
   scanf("%f", &elem); 
   arr[i][j] = elem; 
  } 
 } 
} 
 
void Input_array2(float arr[][2], const int sizeX, const int sizeY, const float r) 
{ 
 srand(time(0)); 
 int i, j; 
 float elem; 
 for (i = 0; i < sizeX; i++) 
 { 
  for (j = 0; j < sizeY; j++) 
  { 
   elem = (float)rand() / RAND_MAX * (2 * r) - r; 
   if (j == 0) 
   { 
       printf("x[%d] = %.2f\n", i, elem); 
   } 
   else 
   { 
       printf("y[%d] = %.2f\n", i, elem); 
   } 
   arr[i][j] = elem; 
  } 
 } 
} 
 
 
bool Hit_point(const float x, const float y, const float r) 
{ 
 float dist = x * x + y * y; 
 bool flag = false; 
  
 if (y < r && y > -r) 
 { 
     if ((pow((x + r), 2) + pow((y), 2)) > pow(r, 2) && (pow((x - r), 2) + pow(y, 2)) > pow(r, 2)) 
     { 
         flag = true; 
     } 
 } 
 return flag; 
}  
 
 
void PrintPoints(const float arr[][2], const int sizeX, const float rad) 
{ 
 int i; 
 for (i = 0; i < sizeX; i++) 
 { 
  if(Hit_point(arr[i][0], arr[i][1], rad)) 
  { 
   printf("Точка x = %.2f, y = %.2f попала в заданную область\n", arr[i][0], arr[i][1]); 
  } 
  else 
  { 
   printf("точка x = %.2f, y = %.2f не попала в заданную область\n", arr[i][0], arr[i][1]); 
  } 
 } 
} 
 
int main() { 
 float array[100][2]; 
 int coords;  
 float rad;  
 
 do{ 
  printf("Введите количество точек: "); 
  scanf("%d", &coords);  
 }while(coords <= 0); 
  
 do{ 
  printf("Введите радиус окружностей: "); 
  scanf( "%f", &rad); 
   
 }while(rad <= 0); 
  
  
 int choice;  
 do 
 { 
  printf("\n1. Задание точек с клавиатуры\n"); 
  printf("2. Задание точек с помощью генератора псевдослучайных чисел\n"); 
  printf("Выберете способ задания точек: "); 
  scanf("%d", &choice); 
 } while(choice > 2 || choice < 1); 
  
 if (choice  == 1) 
 { 
  Input_array1(array, coords, 2); 
 } 
 else 
 { 
  Input_array2(array, coords, 2, rad); 
 } 
 PrintPoints(array, coords, rad); 
 return 0; 
}
