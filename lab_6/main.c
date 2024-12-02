#include <stdio.h>  
#include <time.h>  
#include <stdlib.h>  
#include <stdbool.h>  
#include <math.h>  
  
  
// Функция для ручного ввода значений матрицы с клавиатуры 
void Input_array1(float* const arr, const int len)  
{  
 printf("Координаты вводятся через пробел\n"); 
  
 float x, y; 
  
 for (int i = 0; i < len; i++ ) 
 { 
    printf("x[%d], y[%d] = ", i, i); 
    scanf("%f %f", &x, &y); 
    *(arr + i * 2) = x; 
    *(arr + i * 2 + 1) = y; 
 } 
}  
 
// Функция для случайного заполнения матрицы 
void Input_array2(float* const arr, const int len)  
{  
 srand(time(0));  
 float l, r; 
 do 
 { 
    printf("Введите диапазон генерации значений через пробел: "); 
    scanf("%f %f", &l, &r); 
 } while (l > r); 
 for (int i = 0; i < len; i++) 
 { 
  *(arr + i * 2) = (float)rand() / RAND_MAX * (r - l) + l; 
  *(arr + i * 2 + 1) = (float)rand() / RAND_MAX * (r - l) + l; 
 } 
} 
 
// Отладочная функция вывода значений матрицы 
void Output_Array(const float* const arr, const int len) 
{ 
 printf("Полученные точки:\n"); 
 for (int i = 0; i < len; i++) 
 { 
  printf("x[%d] = %.2f; y[%d] = %.2f\n", i, *(arr + i * 2), i, *(arr + i * 2 + 1)); 
 } 
} 
  
  
// Функция проверки попадания точки в заданную область 
bool Check_Dot_In_Field(const float x, 
      const float y, 
      const float r) 
{ 
    bool cond_1 = pow((x + r), 2) + pow(y, 2) > pow(r, 2); 
    bool cond_2 = pow((x - r), 2) + pow(y, 2) > pow(r, 2); 
    bool cond_3 = (y < r && y > -r); 
    if (cond_1 && cond_2 && cond_3) 
        return true; 
    else 
        return false; 
} 
   
// Функция проверки массива точек на попадание в заданную область 
void Check_All_Dots(const float* const arr, 
     const int len, 
     const float R) 
{ 
 for (int i = 0; i < len; i++) 
 { 
  printf("x[%d] = %.2f; y[%d] = %.2f", i, *(arr + i * 2), i,  *(arr + i * 2 + 1)); 
   
  if (Check_Dot_In_Field(*(arr + i * 2), *(arr + i * 2 + 1), R)) 
   printf(" — находится в области\n"); 
  else 
   printf(" — не находится в области\n"); 
 } 
} 
  
int main() {  
    printf("Выберите способ заполнения массива:\n" 
       "1) Ручной ввод координат с клавиатуры.\n" 
       "2) Случайным образом в заданном диапозоне.\n"); 
        
    int switch_fill; 
 do{ 
  printf("Введите номер способа: "); 
  scanf("%d", &switch_fill); 
 } while ((switch_fill < 1) || (switch_fill > 2)); 
  
 // Ввод длины массива и его заполнение 
 int len_array; 
 do{ 
  printf("\nВведите количество точек: "); 
  scanf("%d", &len_array); 
 } while (len_array < 1); 
  
 float Dots[len_array][2]; 
  
 void (*inputFunc)(float* const, const int) = NULL; 
  
 if (switch_fill == 1) 
  inputFunc = Input_array1; 
 else 
  inputFunc = Input_array2; 
  
 inputFunc((float*) Dots, len_array); 
  
 Output_Array((float*) Dots, len_array); 
  
 // Определение области для поиска вхождений 
 float radius; 
 printf("\nВведите значения для определения области:\n"); 
  
 do{ 
  printf("- Радиус окружности R = "); 
  scanf("%f", &radius); 
 } while (radius < 0); 
  
     // Проверка вхождений и вывод результатов в консоль 
    Check_All_Dots((float*) Dots, len_array, radius); 
     
    return 0; 
}
