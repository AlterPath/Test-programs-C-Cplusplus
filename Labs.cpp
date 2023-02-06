
/*
 #include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS
#include <locale.h>
 
long int factNumber = 1;
 
 int main() {
    int n; 
    printf("N = ");
    scanf("%d", &n);
        if (n >= 0)
        {
            for (int i = 1; i < n + 1; i++) {
                    factNumber = factNumber * i;
            }
        }
        else
        {
            printf("Error: N < 0.");
        }
    printf("%d", factNumber);
    return 0;
};
*/

/*
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
void func(int *a, int srarif, int n) {
    printf("\n\nСреднее арифметическое всех положительных чисел: %i \n", srarif);
    printf("\nМассив после преобразования: \n");
    for (int i = 0; i < n; i++) {
        if (a[i] < 0) {
            a[i] = srarif;
        }
        printf("%d ", a[i]);
    }
}
int main()
{
    setlocale(LC_ALL, "Rus");
    int arr[100];
    int kolvo = 0;
    int srarif = 0;
    srand(time(NULL));
    printf("Сгенерированный массив: \n");
    for (int i = 0; i < 100; i++) {
        arr[i] = -100 + rand() % (201);
        printf("%d ", arr[i]);
        if (arr[i] > 0) {
            kolvo = kolvo + 1;
            srarif = srarif + arr[i];
        }
    }
    srarif = srarif / kolvo;
    func(arr, srarif, 100);

}
*/

 //ВОСЬМАЯ ЛАБА
/*
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int **ar;
    int i, j, n, * mas;
    printf("Введите количество строк матрицы: ");
    scanf("%d", &n);
    ar = (int**)malloc(n * sizeof(int*));
    mas = (int*)malloc(n * sizeof(int)); // массив кол-ва
    for (i = 0; i < n; i++) {
        printf("Введите количество столбцов строки %d: ",i);
        scanf("%d", &mas[i]);//для i строки м.б.разные
        ar[i] = (int*)malloc(mas[i] * sizeof(int));
        for (j = 0; j < mas[i]; j++) {
            printf("ar[%d][%d]= ", i, j);
            scanf("%d", &ar[i][j]);
        }
    }
    for (i = 0; i < n; i++) { // цикл по строкам
        for (j = 0; j < m; j++) { // цикл по столбцам
            printf("%5d ", ar[i][j]); // 5 знакомест под элемент массива
        }
        printf("\n");
        free(ar[i]); // освобождение памяти под строку
    }
    free(ar);
    return 0;
}
*/



//ВТОРАЯ ЛАБА
/*
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>


int main() {
    setlocale(LC_ALL, "Rus");

    float a, b, c, ha, hb, hc, p;
    int answ;

    printf("Введите длину первой стороны треугольника: ");
    scanf("%f", &a);
    printf("Введите длину второй стороны треугольника: ");
    scanf("%f", &b);
    printf("Введите длину третьей стороны треугольника: ");
    scanf("%f", &c);

    printf("Высоту к какой стороне вы хотите просчитать?\n ");
    scanf("%i", &answ);

    p = (a + b + c) / 2;

    switch (answ) {
    case(1):
        ha = 2 * (sqrt(p * (p - a) * (p - b) * (p - c))) / a;
        printf("Значение высоты треугольника, проведенный к стороне а: %f", ha);
        break;

    case(2):
        hb = 2 * (sqrt(p * (p - a) * (p - b) * (p - c))) / b;
        printf("\nЗначение высоты треугольника, проведенный к стороне b: %f", hb);
        break;

    case(3):
        hc = 2 * (sqrt(p * (p - a) * (p - b) * (p - c))) / c;
        printf("\nЗначение высоты треугольника, проведенный к стороне c: %f", hc);
        break;
    }
}
*/

/*
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <time.h>

int main()
{

    setlocale(LC_ALL, "Rus");
    int** ar;
    int i, j, n, * mas;
    int* A;
    int* B;

    srand(time(NULL));
    n = rand() % (21);
    printf("количество строк матрицы: %d", n);

    ar = (int**)malloc(n * sizeof(int*));
    mas = (int*)malloc(n * sizeof(int)); // массив кол-ва
    A = (int*)calloc(100, sizeof(int));
    B = (int*)malloc(100 * sizeof(int));



    for (i = 0; i < n; i++) {
        printf("\nколичество столбцов строки %d: ", i);
        mas[i] = rand() % (11);
        ar[i] = (int*)malloc(mas[i] * sizeof(int));
        for (j = 0; j < mas[i]; j++) {
            //ar[i][j] = rand() % (21);
            printf("\nar[%d][%d]= %d", i, j, ar[i][j]);

        }

        }
        for (i = 0; i < n; i++) { // цикл по строкам
            for (j = 0; j < mas[i]; j++) { // цикл по столбцам
                printf("%5d ", ar[i][j]); // 5 знакомест под элемент массива
            }
            printf("\n");
            free(ar[i]); // освобождение памяти под строку
        }

        printf("\nМассив A:\n");
        for (int i = 0; i < 100; i++) {
            //A[i] = rand() % 9 + 1;
            printf("%3d", A[i]);
        }
        printf("\nМассив B:\n");
        for (int i = 0; i < 100; i++) {
            //B[i] = rand() % 9 + 1;
            printf("%3d", B[i]);
        }
        printf("\n");
        printf("Исходный адрес\n");
        printf("Адрес A: %d\n", A);
        printf("Адрес B: %d\n", B);
        printf("\n");

        A = (int*)realloc(A, (200) * sizeof(int));
        B = (int*)realloc(B, (50) * sizeof(int));

        printf("\nМассив A:\n");
        for (int i = 0; i < 200; i++) {
            //A[i] = rand() % 9 + 1;
            printf("%3d", A[i]);
        }
        printf("\nМассив B:\n");
        for (int i = 0; i < 50; i++) {
            //B[i] = rand() % 9 + 1;
            printf("%3d", B[i]);
        }

        printf("Адрес при А = 200 и B = 50\n");
        printf("Адрес A: %d\n", A);
        printf("Адрес B: %d\n", B);
        printf("\n");

        A = (int*)realloc(A, (50) * sizeof(int));
        B = (int*)realloc(B, (200) * sizeof(int));

        printf("Адрес при А = 50 и B = 200\n");
        printf("Адрес A: %d\n", A);
        printf("Адрес B: %d\n", B);


        free(A); free(B);
        free(ar);
        return 0;
}
*/

//ТРЕТЬЯ ЛАБА. Даны n натуральных чисел. Вывести те числа, значения которых
//являются степенями двойки(1, 2, 4, 8, 16, ...).

//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <math.h>
//
//int main() {
//	int n = 0, k = 1;
//	printf("Enter n: ");
//	scanf("%d", &n);
//	while (k <= n) {
//		int x = 0;
//		printf("Enter x: ");
//		scanf("%d", &x);
//		int tempx = log2(x);
//		if (pow(2, tempx) == x)
//			printf("%d\n", x);
//		k++;
//	}
//}

//ЧЕТВЕРТАЯ ЛАБА. Заменить
//все
//элементы
//отрицательными
//значениями
//средним арифметическим значением
//всех положительных элементов

//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <math.h>
//#include <locale.h>
//#include <time.h>;
//
//int main() {
//    setlocale(LC_ALL, "Rus");
//    int a[30];
//    int kolvo = 0;
//    int sraf = 0;
//    
//
//    srand(time(NULL));
//
//    for (int i = 0; i < 30; i++) {
//        a[i] = rand() % (21) - 10 ;
//        printf("\na[%d]= %d", i, a[i]);
//        if (a[i] > 0){
//            sraf = sraf + a[i];
//            kolvo = kolvo + 1;
//        }
//    }
//    sraf = sraf / kolvo;
//    printf("\n");
//    printf("\nсреднее арифметическое: %d", sraf);
//
//    for (int i = 0; i < 30; i++) {
//        if (a[i] < 0)
//            a[i] = sraf;
//        printf("\na[%d]= %d", i, a[i]);
//    }
//    
//}

//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <locale.h>
//#include <math.h>
//#include <time.h>
//
//int main() {
//    setlocale(LC_ALL, "Rus");
//    int n, m;
//    int** a;
//    int* x;
//
//    srand(time(NULL));
//    n = rand() % (21);
//    m = rand() % (21);
//    printf("\nколичество столбцов массива %i: ", n);
//    printf("\nколичество строк массива %i: ", m);
//
//    a = (int**)calloc(n * m, sizeof(int*));
//    x = (int*)calloc(n*m, sizeof(int));
//    
//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < m; j++) {
//            a[i][j] = rand() % (21);
//            printf("\nar[%d][%d]= %d", i, j, a[i][j]);
//        }
//    }
//    for (int j = 0; j < m; j++) {
//        x[j] = rand() % (21);
//        printf("\nx[%d]= %d", j, x[j]);
//    }
//
//    for (int i = 0; i < 2; i++) {
//        for (int j = 0; j < m; j++) {
//            a[n-i][j] = x[j];
//        }
//    }
//
//    printf("\nМассив A:\n");
//    for (int i = 0; i < n; i++) {
//        printf("\n");
//        for (int j = 0; j < m; j++) {
//            printf("%i", a[i][j]);
//        }
//        
//    }
//}


//ДЕВЯТАЯ ЛАБА
//Дан двумерный массив a, размером(nm) и одномерный
//массив х(m).Нечетные строки матрицы заменить массивами х. (не
//	использовать%, использовать for).

 
 //ДЕСЯТАЯ ЛАБА
  
// Первое задание. Дан двумерный массив a, размером (nm) и одномерный
//массив х(m).Нечетные строки матрицы заменить массивами х. (не
//	использовать%, использовать for).

//#include <stdio.h>
//#include <stdlib.h>
//#include <locale.h>
//#include <math.h>
//#include <time.h>
//
//int main() {
//    setlocale(LC_ALL, "Rus");
//    int** a;
//    int n, m;
//    int* x;
//    srand(time(NULL));
//    n = 5;
//    m = rand() % (11);
//
//    printf("количество строк матрицы: %d", n);
//    printf("количество стобцов матрицы: %d", m);
//
//    a = (int**)malloc(n * m * sizeof(int*));
//    x = (int*)calloc(m, sizeof(int));
//
//
//    for (int i = 0; i < n; i++) {
//        a[i] = (int*)malloc(m * sizeof(int));
//        for (int j = 0; j < m; j++) {
//            a[i][j] = rand() % (21);
//            printf("\na[%d][%d]= %d", i, j, a[i][j]);
//        }
//    }
//
//    for (int i = 0; i < m; i++) {
//        x[i] = rand() % (21);
//        printf("\nx[%d]= %d", i, x[i]);
//    }
//
//    for (int i = 0; i < n; i++) {
//        if (i % 2 != 0) {
//            for (int j = 0; j < m; j++) {
//                a[i][j] = x[j];
//
//            }
//        }
//    }
//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < m; j++) {
//            printf("\na[%d][%d]= %d", i, j, a[i][j]);
//        }
//    }
//
//}

// Второе задание. Дан двумерный массив A, размером (nn) (или квадратная
//матрица A).Найти среднее арифметическое положительных элементов
//параллели главной диагонали, расположенной выше над диагональю.

//#include <stdio.h>
//#include <stdlib.h>
//#include <locale.h>
//#include <math.h>
//#include <time.h>
//
//int main() {
//    setlocale(LC_ALL, "Rus");
//    int** a;
//    int n, kolvo = 0;
//    double sraf = 0;
//    int* x;
//    srand(time(NULL));
//    n = rand() % (11);
//
//    printf("количество строк и столбцов матрицы: %d", n);
//
//
//    a = (int**)malloc(n * n * sizeof(int*));
//
//
//    for (int i = 0; i < n; i++) {
//        a[i] = (int*)malloc(n * sizeof(int));
//        for (int j = 0; j < n; j++) {
//            a[i][j] = rand() % (21);
//            printf("\na[%d][%d]= %d", i, j, a[i][j]);
//        }
//    }
//
//    for (int i = 1; i < n; i++) {
//        if (a[i - 1][i] > 0) {
//            printf("\n%d", a[i - 1][i]);
//            sraf = sraf + a[i - 1][i];
//            kolvo = kolvo + 1;
//        }
//    }
//    printf("\n%f %d", sraf, kolvo);
//    sraf = sraf / kolvo;
//    printf("\n%f %d", sraf, kolvo);
//}

//Третье задание. Дан двумерный массив А, размером (nn) (или квадратная
//матрица А).Найти среднее геометрическое отрицательных элементов,
//нижней треугольной матрицы, расположенной ниже побочной диагонали,
//исключая саму побочную диагональ.

//#include <stdio.h>
//#include <stdlib.h>
//#include <locale.h>
//#include <math.h>
//#include <time.h>
//
//int main() {
//    setlocale(LC_ALL, "Rus");
//    int** a;
//    int n;
//    int kolvo = 1;
//    srand(time(NULL));
//    n = rand() % (11);
//
//    printf("количество строк и столбцов матрицы: %d", n);
//
//    a = (int**)malloc(n * sizeof(int*));
//
//
//    for (int i = 0; i < n; i++) {
//        a[i] = (int*)malloc(n * sizeof(int));
//        for (int j = 0; j < n; j++) {
//            a[i][j] = rand() % (101) - 50;
//            printf("\na[%d][%d]= %d", i, j, a[i][j]);
//
//        }
//    }
//    double srgeom = 1.0;
//
//    for (int i = 1; i < n; i++) {
//        for (int j = 0; j < i; j++) {
//            if (a[i][j] < 0) {
//                srgeom = srgeom * abs(a[i][j]);
//                kolvo = kolvo + 1;
//
//            }
//
//        }
//    }
//
//
//
//    printf("\n%f ", srgeom);
//}

//Четвертое задание. Дано два двумерных массива х(n1m1) ,y(n2m2).
//Cформировать массив z((n1 + n2)(m1 + m2)), таким образом, чтобы
//массивы x и y располагались по диагонали, а остальные элементы были бы
//заполнены нулями.

//#include <stdio.h>
//#include <stdlib.h>
//#include <locale.h>
//#include <math.h>
//#include <time.h>
//
//int main() {
//    setlocale(LC_ALL, "Rus");
//    int** x;
//    int** y;
//    int n1, n2, m1, m2;
//    int kolvo = 1;     
//    srand(time(NULL));
//    n1 = rand() % (5) + 1;
//    n2 = rand() % (5) + 1;
//    m1 = rand() % (5) + 1;
//    m2 = rand() % (5) + 1;
//
//    printf("n1 = %d \n n2 = %d \n m1 = %d \n m2 = %d", n1, n2, m1, m2);
//
//    x = (int**)malloc(n1 * sizeof(int*));
//
//    for (int i = 0; i < n1; i++) {
//        x[i] = (int*)malloc(m1 * sizeof(int));
//        for (int j = 0; j < m1; j++) {
//            x[i][j] = rand() % (101) - 50;
//            printf("\nx[%d][%d]= %d", i, j, x[i][j]);
//
//        }
//    }
//
//    y = (int**)malloc(n2 * sizeof(int*));
//
//    for (int i = 0; i < n2; i++) {
//        y[i] = (int*)malloc(m2 * sizeof(int));
//        for (int j = 0; j < m2; j++) {
//            y[i][j] = rand() % (101) - 50;
//            printf("\ny[%d][%d]= %d", i, j, y[i][j]);
//
//        }
//    }
//
//    int** z;
//    int n3 = n1 + n2;
//    int m3 = m1 + m2;
//    z = (int**)malloc(n3 * sizeof(int*));
//    for (int i = 0; i < n3; i++) {
//        y[i] = (int*)malloc(m3 * sizeof(int));
//        int j = i;
//        if (i < n1) {
//            z[i][j] = x[i][j];
//        }
//        printf("\nz[%d][%d]= %d", i, j, z[i][j]);
//
//        }
//    
//}



//ОДИННАДЦАТАЯ ЛАБА. Дана матрица Р размером m*n . Найти сумму минимальных
//элементов каждого столбца матрицы.
 
//#include <stdio.h>
//#include <stdlib.h>
//#include <locale.h>
//#include <math.h>
//#include <time.h>
//
//int main() {
//    setlocale(LC_ALL, "Rus");
//    int** a;
//    int n, m;
//    int smin = 0;
//    srand(time(NULL));
//    n = rand() % (5);
//    m = rand() % (5);
//
//    printf("количество строк матрицы: %d", n);
//    printf("количество стобцов матрицы: %d", m);
//
//    a = (int**)malloc(n * m * sizeof(int*));
//
//
//    for (int i = 0; i < n; i++) {
//        a[i] = (int*)malloc(m * sizeof(int));
//        for (int j = 0; j < m; j++) {
//            a[i][j] = rand() % (30);
//            printf("\na[%d][%d]= %d", i, j, a[i][j]);
//        }
//    }
//    for (int i = 0; i < m; i++) {
//        int min = 100;
//        for (int j = 0; j < n; j++) {
//            if (a[j][i] < min) {
//                min = a[j][i];
//            }
//        }
//        smin = smin + min;
//    }
//    printf("\n%d", smin);
//}

//ДВЕННАДЦАЯ ЛАБА. Функция выравнивает строку по правому краю до заданной длины.

/*#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <locale.h>

void strright(int length, char str[256]) {
    int strlength = 0;
    while (str[strlength] != '\0') {
        strlength++;
    }
    strlength = strlength - 1;

    for (int i = 0; i < strlength; i++) {
        str[length - strlength + i] = str[i];
        str[i] = '.';

    }


    for (int j = strlength; j < length - strlength; j++) {
        str[j] = '.';

    }
    printf("%s \n", str);


}
int main() {
    setlocale(LC_ALL, "Rus");
    int length = 0;
    char str[256];

    printf("Введите строку:");
    fgets(str, 256, stdin);

    printf("Введите длину до которой нужно выровнять строку:");
    scanf("%i", &length);

    printf("Строка:");
    strright(length, str);
    return 0;
}
*/


/*
#include <stdio.h>
#include <math.h>
#include <locale.h>

int main()
{
    setlocale(LC_ALL, "Russian");
    float x, y, t;
    double z;
    printf("Введите длину стороны треугольника");
    printf("\n");
    scanf_s("%f", &t);
    printf("Введите величину угла");
    printf("\n");
    scanf_s("%f", &z);
    printf("\n");
    y = t + 2 * (cos(z) / sin(z));
    x = (3 * pow(y, 2)) / (4 * tan(z) - 2 * pow(t, 2));
    printf("%f", x);
    return 0;


}
*/


