#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include "head.h"


ListaDeLetras * InicializaListaDeLetras (ListaDeLetras* ListaIndice)
{
    return NULL;

}

ListaDePalavras * InicializaListaDePalavras (ListaDePalavras* ListaNodo)
{
    return NULL;
}

ListaDeLetras *PreencheListaIndice(ListaDeLetras *ListaIndice)
{
    ListaDeLetras* InsereLetraIndice(ListaDeLetras* ListaIndice, char info) //Insere nó na lista índice
    {
        ListaDeLetras * novo, * ptaux;
        novo = (ListaDeLetras*)malloc(sizeof(ListaDeLetras));
        novo->letra = info;
        novo->prox = NULL;
        novo->Lista_Alfabetica = NULL;

        if(ListaIndice == NULL)
        {
            novo->ant = NULL;
            ListaIndice = novo;

        }
        else
        {
            ptaux = ListaIndice;
            while(ptaux->prox != NULL)
                ptaux = ptaux->prox;
            ptaux->prox = novo;
            novo->ant = ptaux;
        }

        return ListaIndice;
    }

    char alfabeto[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    int ind = 0;

    for(ind=0; ind<26; ind++)
        ListaIndice = InsereLetraIndice(ListaIndice, alfabeto[ind]);
    return ListaIndice;
}

ListaDeLetras *AlocaLista(ListaDeLetras *ListaIndice, ListaDePalavras *ListaNodo, char * ArquivoDasPalavras)
{
    FILE *f;
    char buff[255];
    char delim[] = "\t";
    InfoNodo nodo;
    ListaDeLetras *ptaux;
    char* token;


    f = fopen(ArquivoDasPalavras, "r");
    if(f == NULL)
        printf("\nNão foi possível abrir o arquivo com as palavras.");
    else
    {
        fgets(buff, 255, f);
        while(fgets(buff, 255, f) != NULL)
        {
            token = strtok(buff, delim);
            nodo.peso = strtoll(token, NULL, 10);
            token = strtok(NULL, delim);
            strcpy(nodo.palavra, token);
            int len = strlen(nodo.palavra);
            if (len > 0 && nodo.palavra[len-1] == '\n') nodo.palavra[len-1] = '\0';
            int i;

    for(i = 0; nodo.palavra[i]; i++)
    {
        nodo.palavra[i] = tolower(nodo.palavra[i]);
          }


            for(ptaux = ListaIndice; ptaux != NULL; ptaux = ptaux->prox)
            {

                if(ptaux->letra == nodo.palavra[0])
                {


                    ptaux->Lista_Alfabetica = InsereNodo(ptaux->Lista_Alfabetica, nodo );


                }
            }
        }
    }


    return ListaIndice;
}


ListaDePalavras *InsereNodo(ListaDePalavras *ListaNodo, InfoNodo nodo)
{




    ListaDePalavras *novo, *ptaux;
    novo = (ListaDePalavras*)malloc(sizeof(ListaDePalavras));
    novo->info = nodo;
    novo->prox = NULL;



    if(ListaNodo == NULL) //Se a lista for nula e este for o primeiro nodo...
    {
        ListaNodo = novo;
        novo->ant = NULL;


    }

    else
    {
       ptaux = ListaNodo;
       while(ptaux->prox != NULL)
        ptaux=ptaux->prox;
       ptaux->prox = novo;
       novo->ant = ptaux;
       }



    return ListaNodo;

}


ListaDePalavras * LeEntrada(char * Entrada)
{
    char buff[255];
    ListaDePalavras *ListaDeEntrada;
    InfoNodo temp;

    ListaDeEntrada = InicializaListaDePalavras(ListaDeEntrada);

    FILE *f = fopen(Entrada, "r");
    if(f == NULL)
    {
        printf("Erro ao abrir o arquivo de entrada!");

    }

    else
    {
        while(fgets(buff, 255, f) != NULL)
        {
            strcpy(temp.palavra, buff);
            int len = strlen(temp.palavra);
            if (len > 0 && temp.palavra[len-1] == '\n') temp.palavra[len-1] = '\0';
            temp.peso = 0;
            ListaDeEntrada = InsereNodo(ListaDeEntrada, temp);


        }

        return ListaDeEntrada;

    }




}


bool ChecaPrefixo(const char *pre, const char *str)
{
    return strncmp(pre, str, strlen(pre)) == 0;
}




void EscreveSaida (ListaDeLetras * ListaIndice, ListaDePalavras * ListaDeEntrada, char * ArquivoDeSaida, int NumeroDeConsultas, int TempoAtual)
{

    clock_t start, end, elapsed;
    start=clock();

    void ImprimeSaida(char * Consulta, int NumeroDeConsultas, FILE *f, ListaDeLetras * ListaIndice)
    {
        ListaDeLetras *ptaux;
        ListaDePalavras *ptaux2;
        int contador = 0;


        for(ptaux = ListaIndice; ptaux != NULL; ptaux = ptaux->prox)
        {

            if(Consulta[0] == ptaux->letra)
            {
                for(ptaux2 = ptaux->Lista_Alfabetica; ptaux2->prox != NULL; ptaux2 = ptaux2->prox )
                {

                    if(ChecaPrefixo(Consulta, ptaux2->info.palavra) == true)
                    {



                        if(contador != NumeroDeConsultas)
                        {
                            fprintf(f,"\nPeso = %lli Palavra = %s", ptaux2->info.peso, ptaux2->info.palavra);
                            contador++;
                        }
                    }

                }
            }
        }
        if(contador == 0)
            fprintf(f, "\nNão foi encontrada nenhuma palavra para tal prefixo.\n", contador);
    }

    FILE *f = fopen(ArquivoDeSaida, "w");
    ListaDePalavras * ptaux;


    for(ptaux = ListaDeEntrada; ptaux != NULL; ptaux = ptaux->prox)
    {
        fprintf(f,"\n%s\n", ptaux->info.palavra);
        ImprimeSaida(ptaux->info.palavra, NumeroDeConsultas, f, ListaIndice);
    }

    end=clock();
    elapsed = 1000 * (end - start) / (CLOCKS_PER_SEC);
    elapsed = elapsed + TempoAtual;
    fprintf(f, "\n\nTempo : %ld ms", elapsed);


}









/* DEBUG */ void ImprimeLista (ListaDeLetras *ListaIndice, ListaDePalavras *ListaNodo)
{
    ListaDeLetras * ptauxL = ListaIndice;
    ListaDePalavras * ptauxP = ListaNodo;

    if(ptauxL != NULL)
    {
        while(ptauxL != NULL)
        {
            printf("\nLetra = <%c>", ptauxL->letra);
            ptauxL = ptauxL->prox;
        }


    }
    if(ptauxP != NULL)
    {
        while(ptauxP != NULL)
        {
            printf("\nPeso = %lli Palavra = %s", ptauxP->info.peso, ptauxP->info.palavra);
            ptauxP = ptauxP->prox;
        }


    }



}

/* DEBUG */ void EscreveListaDebugada(ListaDeLetras *ListaIndice)
{
    FILE *f = fopen("debug.txt", "w");


    ListaDeLetras *ptaux;
    ListaDePalavras *ptaux2;

    for(ptaux = ListaIndice; ptaux != NULL; ptaux = ptaux->prox)
        for(ptaux2 = ListaIndice->Lista_Alfabetica; ptaux != NULL; ptaux2 = ptaux2->prox)
        {
            if(ptaux2 != NULL)
          fprintf(f, "Peso = %lli Palavra = %s", ptaux2->info.peso, ptaux2->info.palavra);
        }








}
