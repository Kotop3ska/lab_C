#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f(double x) {
    return 2 * x + log10(2 * x + 3) - 1;
}

double Recursive_solve(double a, double b, double eps) {
    double m = (a + b) / 2;
    if (fabs(f(m)) < eps) {
        return m;
    }
    
    if (f(a) * f(m) < 0) {
        return Recursive_solve(a, m, eps);
    } else {
        return Recursive_solve(m, b, eps);
    }
}

double Iterative_solve(double a, double b, double eps) {
    double m;
    do {
        m = (a + b) / 2;
        if (f(a) * f(m) < 0) {
            b = m;
        } else {
            a = m;
        }
    } while (fabs(f(m)) > eps);
    return m;
}

int main() {
    double eps, a, b;
    
    printf("Введите границы поиска корня:\n");
    do {
        printf("a = ");
        scanf("%lf", &a);
        printf("b = ");
        scanf("%lf", &b);
        if (a > b || a == b) {
            printf("Ошибка: а должно быть меньше b.\n");
        }
        if (a <= -1.5) {
            printf("Ошибка: а не может быть меньше -1.5.\n");
        }
        if (f(a) * f(b) > 0) {
            printf("Нет корня на этом интервале.\n");
        }
    } while (a >= b || a <= -1.5 || f(a) * f(b) > 0);
    
    printf("Введите точность поиска: ");
    scanf("%lf", &eps);
    
    double x1 = Recursive_solve(a, b, eps);
    double x2 = Iterative_solve(a, b, eps);
    
    printf("Корень, найденный рекурсивно: %lf\n", x1);
    printf("Корень, найденный итеративно: %lf\n", x2);
    
    return 0;
}
