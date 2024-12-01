#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long comparaciones = 0;
long long intercambios = 0;

void intercambiar(int *a, int *b)
{
    intercambios++;
    int temp = *a;
    *a = *b;
    *b = temp;
}

void seleccion(int arr[], int n)
{
    int i, j, min_idx;

    for (i = 0; i < n - 1; i++)
    {
        min_idx = i;

        for (j = i + 1; j < n; j++)
        {
            comparaciones++;
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }

        if (min_idx != i)
        {
            intercambiar(&arr[min_idx], &arr[i]);
        }
    }
}

void burbujeo(int arr[], int n)
{
    int i, j;
    int swapped;

    for (i = 0; i < n - 1; i++)
    {
        swapped = 0;

        for (j = 0; j < n - i - 1; j++)
        {
            comparaciones++;

            if (arr[j] > arr[j + 1])
            {
                intercambiar(&arr[j], &arr[j + 1]);
                swapped = 1;
            }
        }

        if (!swapped)
            break;
    }
}

void insercion(int arr[], int n)
{
    int i, key, j;

    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;
        comparaciones++;

        while (j >= 0 && arr[j] > key)
        {
            comparaciones++;
            intercambios++;
            arr[j + 1] = arr[j];
            j = j - 1;
        }

        intercambios++;
        arr[j + 1] = key;
    }
}

void shell(int arr[], int n)
{
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i++)
        {
            int temp = arr[i];
            int j;
            comparaciones++;

            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
            {
                comparaciones++;
                intercambios++;
                arr[j] = arr[j - gap];
            }

            intercambios++;
            arr[j] = temp;
        }
    }
}

int medianaDeTres(int arr[], int bajo, int alto)
{
    int medio = (bajo + alto) / 2;

    if (arr[bajo] > arr[medio])
    {
        intercambiar(&arr[bajo], &arr[medio]);
    }

    if (arr[bajo] > arr[alto])
    {
        intercambiar(&arr[bajo], &arr[alto]);
    }

    if (arr[medio] > arr[alto])
    {
        intercambiar(&arr[medio], &arr[alto]);
    }

    intercambiar(&arr[medio], &arr[alto - 1]);

    return arr[alto - 1];
}

int particion(int arr[], int bajo, int alto)
{
    int pivote = medianaDeTres(arr, bajo, alto);
    int i = bajo;
    int j = alto - 1;

    while (1)
    {
        while (arr[++i] < pivote)
        {
            comparaciones++;
        }
        while (arr[--j] > pivote)
        {
            comparaciones++;
        }
        if (i < j)
        {
            intercambiar(&arr[i], &arr[j]);
        }
        else
        {
            break;
        }
    }
    intercambiar(&arr[i], &arr[alto - 1]);
    return i;
}

void insertionSort(int arr[], int inicio, int fin)
{
    for (int i = inicio + 1; i <= fin; i++)
    {
        int key = arr[i];
        int j = i - 1;
        comparaciones++;
        while (j >= inicio && arr[j] > key)
        {
            comparaciones++;
            intercambios++;
            arr[j + 1] = arr[j];
            j--;
        }
        intercambios++;
        arr[j + 1] = key;
    }
}

void quickSort(int arr[], int bajo, int alto)
{
    const int SIZE = alto - bajo + 1;
    int *stack = (int *)malloc(SIZE * sizeof(int));
    int top = -1;

    // Inicializar el stack
    top++;
    stack[top] = bajo;
    top++;
    stack[top] = alto;

    while (top >= 0)
    {
        int h = stack[top--];
        int l = stack[top--];

        if (h - l <= 10)
        {
            insertionSort(arr, l, h);
            continue;
        }

        int p = particion(arr, l, h);

        if (p - 1 > l)
        {
            top++;
            stack[top] = l;
            top++;
            stack[top] = p - 1;
        }

        if (p + 1 < h)
        {
            top++;
            stack[top] = p + 1;
            top++;
            stack[top] = h;
        }
    }

    free(stack);
}

// ----------------------------
// Generacion de Casos
// ----------------------------
void generarMejorCaso(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        arr[i] = i;
}

void generarPeorCaso(int arr[], int n, int algoritmo)
{
    switch (algoritmo)
    {
    case 1: // Selección
    case 2: // Burbujeo
    case 3: // Inserción
        // Peor caso: array ordenado en orden descendente
        for (int i = 0; i < n; i++)
            arr[i] = n - i;
        break;
    case 4: // Shell
        // Peor caso aproximado: array con patrón específico
        for (int i = 0; i < n; i++)
            arr[i] = (i % 2 == 0) ? i : n - i;
        break;
    case 5: // QuickSort
        // Peor caso: array ordenado (ascendente o descendente)
        for (int i = 0; i < n; i++)
            arr[i] = i; // array ordenado de forma ascendente
        break;
    }
}

void generarCasoPromedio(int arr[], int n)
{
    // Inicializar el array con valores ordenados
    for (int i = 0; i < n; i++)
        arr[i] = i;

    // Mezclar el array usando Fisher-Yates
    for (int i = n - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        intercambiar(&arr[i], &arr[j]);
    }
}

int main()
{
    srand(time(NULL)); // Inicializar la seed una vez

    int opcion_algoritmo;
    int tamanios[] = {2000, 2500, 5000, 10000, 35000, 80000, 120000, 150000};
    int num_tamanios = sizeof(tamanios) / sizeof(tamanios[0]);
    int *arr;

    while (1)
    {
        printf("\nAlgoritmos de Ordenamiento\n");
        printf("1. Seleccion\n");
        printf("2. Burbujeo\n");
        printf("3. Insercion\n");
        printf("4. Shell\n");
        printf("5. QuickSort\n");
        printf("6. Salir\n");
        printf("Seleccione el algoritmo que desea usar: ");
        scanf("%d", &opcion_algoritmo);

        if (opcion_algoritmo == 6)
            break;

        for (int s = 0; s < num_tamanios; s++)
        {
            int n = tamanios[s];
            arr = (int *)malloc(n * sizeof(int));

            printf("\nTamanio del array: %d\n", n);

            // Mejor caso
            generarMejorCaso(arr, n);
            comparaciones = intercambios = 0;
            clock_t inicio = clock();

            switch (opcion_algoritmo)
            {
            case 1:
                seleccion(arr, n);
                break;
            case 2:
                burbujeo(arr, n);
                break;
            case 3:
                insercion(arr, n);
                break;
            case 4:
                shell(arr, n);
                break;
            case 5:
                quickSort(arr, 0, n - 1);
                break;
            default:
                printf("Opcion inválida.\n");
                free(arr);
                continue;
            }

            clock_t fin = clock();
            double tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;

            printf("Mejor caso - Tiempo: %f segundos, Comparaciones: %lld, Intercambios: %lld\n", tiempo, comparaciones, intercambios);

            // Caso promedio
            generarCasoPromedio(arr, n);
            comparaciones = intercambios = 0;
            inicio = clock();

            switch (opcion_algoritmo)
            {
            case 1:
                seleccion(arr, n);
                break;
            case 2:
                burbujeo(arr, n);
                break;
            case 3:
                insercion(arr, n);
                break;
            case 4:
                shell(arr, n);
                break;
            case 5:
                quickSort(arr, 0, n - 1);
                break;
            }

            fin = clock();
            tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;

            printf("Caso promedio - Tiempo: %f segundos, Comparaciones: %lld, Intercambios: %lld\n", tiempo, comparaciones, intercambios);

            // Peor caso
            generarPeorCaso(arr, n, opcion_algoritmo);
            comparaciones = intercambios = 0;
            inicio = clock();

            switch (opcion_algoritmo)
            {
            case 1:
                seleccion(arr, n);
                break;
            case 2:
                burbujeo(arr, n);
                break;
            case 3:
                insercion(arr, n);
                break;
            case 4:
                shell(arr, n);
                break;
            case 5:
                quickSort(arr, 0, n - 1);
                break;
            }

            fin = clock();
            tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;

            printf("Peor caso - Tiempo: %f segundos, Comparaciones: %lld, Intercambios: %lld\n", tiempo, comparaciones, intercambios);

            free(arr);
        }
    }

    return 0;
}
