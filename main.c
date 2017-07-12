#include "head.h"
#include <stdio.h>
#include <time.h>
#include <locale.H>

int main(int argc, char * argv[])
{
    setlocale(LC_ALL, "");
    clock_t start, end, elapsed; //para contar o tempo
    ListaDeLetras * ListaIndice;
    ListaDeLetras * ListaNodo;
    ListaDePalavras *Consultas;
    ListaDeLetras *ptaux;







    if(argc != 5)
    {
        printf("Número incorreto de parâmetros.\n O esperado era 4 : \n(Arquivo com palavras) \n(Arquivo de entrada) \n(Arquivo de saída) \n(Número de consultas)");
        return 1;
    }
    else
    {
        start=clock(); //inicia a contagem do tempo;
        argv[4] = atoi(argv[4]); // Para virar string

        ListaIndice = InicializaListaDeLetras(ListaIndice); // Inicializa a lista com nulo
        ListaNodo = InicializaListaDePalavras(ListaNodo);  //  Inicializa a lista com nulo
        ListaIndice = PreencheListaIndice(ListaIndice); // Preenche a lista com a até z



        ListaIndice = AlocaLista(ListaIndice, ListaNodo, argv[1]); //Aloca a lista de cada letra com suas palavras correspondentes



        Consultas = LeEntrada(argv[2]); // Lê o arquivo de entrada e armazena as consultas





        end=clock();
         elapsed = 1000 * (end - start) / (CLOCKS_PER_SEC);

        EscreveSaida(ListaIndice, Consultas, argv[3], argv[4], elapsed);












    }


}
