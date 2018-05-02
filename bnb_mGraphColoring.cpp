#include<stdio.h>
#include<iostream>

// Jumlah vertex maksimal
#define M 100

void printSolution(int color[], int V);

/* Fungsi untuk pengecekan apakah vertex v dapat diberikan warna*/
bool isSafe (int v, bool graph[][M], int color[], int c, int V)
{
    for (int i = 0; i < V; i++)
        if (graph[v][i] && c == color[i])
            return false;
    return true;
}

/* Fungsi untuk menghitung jumlah tetangga dari vertex v*/
int countAdjacent(bool graph[][M], int v, int i, int V)
{
    if(i == V)
        return 0;
    else{
        if(graph[v][i])
            return 1 + countAdjacent(graph, v, i+1, V);
        else
            return countAdjacent(graph, v, i+1, V);
    }
}

/* Fungsi untuk menentukan vertex yang memiliki tetangga paling banyak dan belum diberi warna */
int maxAdjacent (bool graph[][M], int color[], int V)
{
    int m = 0;int midx = 0;
    for(int i = 0; i < V; i++){
        if(color[i] == 0){
           int temp = countAdjacent(graph, i, 0, V);
           if(m < temp){
              m = temp;
              midx = i;
           }
        }

    }

    return midx;
}

/* Fungsi recursive untuk penyelesaian masalah m-coloring graph*/
bool graphColoringUtil(bool graph[][M], int m, int color[], int colored, int V)
{
    /* base case: Jika semua vertex telah diberi warna maka akan return true*/
    if (colored == V)
        return true;

    /* Memasukkan warna ke vertex yang memiliki jumlah tetangga maksimal*/
    for (int c = 1; c <= m; c++)
    {
        /* Mengambil vertex dengan jumlah tetangga paling banyak*/
        int v = maxAdjacent(graph, color, V);

        /* Pengecekan apakah vertex v dapat diberi warna*/
        if (isSafe(v, graph, color, c, V))
        {
           color[v] = c;

           if (graphColoringUtil (graph, m, color, colored+1, V) == true)
             return true;

           color[v] = 0;
        }

    }

    /* Jika tidak ada warna yang dapat diberikan ke vertex ini maka akan return false */
    return false;
}


bool graphColoring(bool graph[][M], int m, int V)
{
    // Menginisialisasi seluruh warna dengan 0
    int *color = new int[V];
    for (int i = 0; i < V; i++)
       color[i] = 0;

    // Pemanggilan graphColoringUtil() untuk vertex pertama
    if (graphColoringUtil(graph, m, color, 0, V) == false)
    {
      printf("Solution does not exist");
      return false;
    }

    // Menampilkan hasil
    printSolution(color, V);
    return true;
}

/* Fungsi untuk menampilkan solusi setelah graph diberi warna */
void printSolution(int color[], int V)
{
    printf("\nSolution Exists:"
            " Following are the assigned colors \n");
    for (int i = 0; i < V; i++)
      printf(" %d ", color[i]);
    printf("\n");
}

int main()
{
    int V, m;
    /* Create following graph and test whether it is 3 colorable
      (3)---(2)
       |   / |
       |  /  |
       | /   |
      (0)---(1)
    */
   /* bool graph[V][V] = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 1, 0},
        {1, 1, 0, 1, 1},
        {0, 1, 1, 0, 1},
        {0, 0, 1, 1, 0}
    };
    int m = 4; // Number of colors*/

    //masukkan jumlah vertex yang diinginkan
    printf("Jumlah vertex: ");
    scanf("%d", &V);
    printf("\n---Masukkan status ketetanggan dari setiap vertex---\n'0' jika tidak bertetangga, '1' sebaliknya\n\n");

    bool graph[V][100];

    //Masukkan status ketetanggan dari setiap vertex
    //Jika tidak bertetangga diisi '0', sebaliknya diisi '1'
    for(int i = 0; i < V; i++){
        printf("=>Vertex %d:\n", i+1);
        for(int j = 0; j < V; j++){
            printf("Vertex-%d dengan Vertex-%d: ", i+1, j+1);
            std::cin >> graph[i][j];
        }
    }

    //Masukkan jumlah warna yang tersedia
    printf("\n\nJumlah warna yang tersedia: ");
    scanf("%d", &m);

    graphColoring (graph, m, V);

    return 0;
}
