
#include <iostream>
#include <omp.h>
#include <random>

#define N 1000
#define chunk 100
#define mostrar 25
#define PI 3.1415926

void imprimeArreglo(float* d, float* e, float* f);

int main()
{
    float a[N], b[N], c[N];
    int i;
    int pedazos;

    std::random_device rd;

    // Create a random number generator
    std::mt19937 gen(rd());

    // Define a uniform distribution in the range [1, 100]
    std::uniform_int_distribution<> distr(1, 100);


    // Inicialización de los arreglos
    for (i = 0; i < N; i++)
    {
        float random_number;
        random_number = distr(gen);
        a[i] = i * 10 + random_number;
        b[i] = (i + 3) * PI + random_number;
    }

    pedazos = chunk;

    // Suma en paralelo
#pragma omp parallel for shared(a, b, c, pedazos) private(i) schedule(static, pedazos)
    for (i = 0; i < N; i++)
    {
        c[i] = a[i] + b[i];
    }

    // Impresión de los primeros elementos de cada arreglo
    std::cout << "Imprimiendo los primeros " << mostrar << " valores: " << std::endl;
    imprimeArreglo(a, b, c);

    return 0;
}

void imprimeArreglo(float* d, float* e, float* f)
{
    for (int x = 0; x < mostrar; x++)
    {
        std::cout << x << ": " << d[x] << " + " << e[x] << " = " << f[x] << std::endl;
    }
    std::cout << std::endl;
}

