#include <stdio.h>

struct Peso_E_Palavra
{
    long long int peso;
    char palavra[35];
};
typedef struct Peso_E_Palavra InfoNodo; // É a informação que a lista guarda.

struct Lista1
{
    InfoNodo info;
    struct Lista1 *prox;
    struct Lista1 *ant;
};
typedef struct Lista1 ListaDePalavras; //É a lista que armazena as palavras.

struct Lista2
{
    char letra; // Vai de a até z.
    ListaDePalavras *Lista_Alfabetica; //Lista com as palavras que começam com a letra do nodo.
    struct Lista2 *prox;
    struct Lista2 *ant;
};
typedef struct Lista2 ListaDeLetras; //É o índice.


//Funções

ListaDeLetras * InicializaListaDeLetras (ListaDeLetras* ListaIndice);
ListaDePalavras * InicializaListaDePalavras (ListaDePalavras* ListaNodo);
ListaDeLetras *PreencheListaIndice(ListaDeLetras *ListaIndice);
ListaDePalavras *InsereNodo(ListaDePalavras *ListaNodo, InfoNodo nodo);
ListaDeLetras *AlocaLista(ListaDeLetras *ListaIndice, ListaDePalavras *ListaNodo, char * ArquivoDasPalavras);
ListaDePalavras * LeEntrada(char * Entrada);


//Debug
/* DEBUG */ void ImprimeLista (ListaDeLetras *ListaIndice, ListaDePalavras *ListaNodo);
