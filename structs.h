#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int ID;
    int NIF;
    char NOME[20];
    char CIDADE[20];
    int TELEFONE;
} DONO;

typedef struct {
    int ID;
    char NOME[20];
    char ESPECIE[20];
    char RACA[50];
    char GENERO;
    float PESO;
    int ID_DONO;
} ANIMAL;

typedef struct {
    int ID;
    int NIF;
    char NOME[20];
    char ESPECIALIDADE[20];
    int TELEFONE;
    int HORAS_TRABALHADAS;
} VETERINARIO;


typedef struct {
    int ID;
    int TIPO_INTERVENCAO;
    int ID_VETERINARIO;
    int ID_ANIMAL;
    char DATA[11];
    char HORA[6];
    float CUSTO;
} INTERVENCAO;
