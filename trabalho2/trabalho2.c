#include <stdio.h>
#include <stdlib.h>
#define TAM 10

#include "trabalho2.h"

//int vetorPrincipal[TAM];


int *ponteirosAuxiliares[TAM];
int tamanhosAuxiliares[TAM];
int quantidadesAuxiliares[TAM];

int ehPosicaoValida(int posicao);
/*
Objetivo: criar estrutura auxiliar na posição 'posicao'.
com tamanho 'tamanho'

Rertono (int)
    SUCESSO - criado com sucesso
    JA_TEM_ESTRUTURA_AUXILIAR - já tem estrutura na posição
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    SEM_ESPACO_DE_MEMORIA - Sem espaço de memória
    TAMANHO_INVALIDO - o tamanho deve ser maior ou igual a 1
*/
int criarEstruturaAuxiliar(int posicao, int tamanho)
{
    if(ehPosicaoValida(posicao) == POSICAO_INVALIDA)
        return POSICAO_INVALIDA;

    if(tamanho < 1)
        return TAMANHO_INVALIDO;

    int idx = posicao - 1;

    if (quantidadesAuxiliares[idx] != -1)
        return JA_TEM_ESTRUTURA_AUXILIAR;

    int *novo = (int *)malloc(tamanho * sizeof(int));
    if(novo == NULL)
        return SEM_ESPACO_DE_MEMORIA;

    ponteirosAuxiliares[idx] = novo;
    tamanhosAuxiliares[idx] = tamanho;
    quantidadesAuxiliares[idx] = 0;

    return SUCESSO;
}

/*
Objetivo: inserir número 'valor' em estrutura auxiliar da posição 'posicao'
Rertono (int)
    SUCESSO - inserido com sucesso
    SEM_ESPACO - não tem espaço
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
CONSTANTES
*/
int inserirNumeroEmEstrutura(int posicao, int valor)
{
    if(ehPosicaoValida(posicao) == POSICAO_INVALIDA)
        return POSICAO_INVALIDA;

    int idx = posicao  - 1;

    if(quantidadesAuxiliares[idx] == -1)
        return SEM_ESTRUTURA_AUXILIAR;

    if(quantidadesAuxiliares[idx] >= tamanhosAuxiliares[idx])
        return SEM_ESPACO;

    ponteirosAuxiliares[idx][quantidadesAuxiliares[idx]] = valor;
    quantidadesAuxiliares[idx]++;

    return SUCESSO;
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar no final da estrutura.
ex: suponha os valores [3, 8, 7, 9,  ,  ]. Após excluir, a estrutura deve ficar da seguinte forma [3, 8, 7,  ,  ,  ].
Obs. Esta é uma exclusão lógica

Rertono (int)
    SUCESSO - excluido com sucesso
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int excluirNumeroDoFinaldaEstrutura(int posicao)
{
    if(ehPosicaoValida(posicao) == POSICAO_INVALIDA)
        return POSICAO_INVALIDA;
    
    int idx = posicao  - 1;

    if(quantidadesAuxiliares[idx] == -1)
        return SEM_ESTRUTURA_AUXILIAR;
    
    if(quantidadesAuxiliares[idx] == 0)
        return ESTRUTURA_AUXILIAR_VAZIA;

    quantidadesAuxiliares[idx]--;

    return SUCESSO;
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar da posição 'posicao'.
Caso seja excluido, os números posteriores devem ser movidos para as posições anteriores
ex: suponha os valores [3, 8, 7, 9,  ,  ] onde deve ser excluido o valor 8. A estrutura deve ficar da seguinte forma [3, 7, 9,  ,  ,  ]
Obs. Esta é uma exclusão lógica
Rertono (int)
    SUCESSO - excluido com sucesso 'valor' da estrutura na posição 'posicao'
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    NUMERO_INEXISTENTE - Número não existe
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar

*/
int excluirNumeroEspecificoDeEstrutura(int posicao, int valor)
{
    if(ehPosicaoValida(posicao) == POSICAO_INVALIDA)
        return POSICAO_INVALIDA;

    int idx = posicao  - 1;

    if(quantidadesAuxiliares[idx] == -1)
        return SEM_ESTRUTURA_AUXILIAR;
    
    if(quantidadesAuxiliares[idx] == 0)
        return ESTRUTURA_AUXILIAR_VAZIA;

    int posicaoEncontrada = -1;
    int i;
    for(i = 0; i < quantidadesAuxiliares[idx]; i++){
        if(ponteirosAuxiliares[idx][i] == valor){
            posicaoEncontrada = i;
            break;
        }
    }

    if (posicaoEncontrada == -1)
        return NUMERO_INEXISTENTE;

    for (i = posicaoEncontrada; i < quantidadesAuxiliares[idx] - 1; i++)
    {
        ponteirosAuxiliares[idx][i] = ponteirosAuxiliares[idx][i + 1];
    }
    quantidadesAuxiliares[idx]--;

    return SUCESSO;
}

// se posição é um valor válido {entre 1 e 10}
int ehPosicaoValida(int posicao)
{
    int retorno = 0;
    if (posicao < 1 || posicao > 10)
    {
        retorno = POSICAO_INVALIDA;
    }
    else
        retorno = SUCESSO;

    return retorno;
}
/*
Objetivo: retorna os números da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Retorno (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosEstruturaAuxiliar(int posicao, int vetorAux[])
{
    if (ehPosicaoValida(posicao) == POSICAO_INVALIDA)
        return POSICAO_INVALIDA;

    int idx = posicao - 1;

    if (quantidadesAuxiliares[idx] == -1)
        return SEM_ESTRUTURA_AUXILIAR;

    int i;
    for (i = 0; i < quantidadesAuxiliares[idx]; i++)
        vetorAux[i] = ponteirosAuxiliares[idx][i];

    return SUCESSO;
}

/*
Objetivo: retorna os números ordenados da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao (1..10)'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[])
{
    int retorno = getDadosEstruturaAuxiliar(posicao, vetorAux);

    if (retorno != SUCESSO)
        return retorno;

    int idx = posicao - 1;
    int i, j, temp;
    // bubble sort simples (ordem crescente)
    for (i = 0; i < quantidadesAuxiliares[idx] - 1; i++)
    {
        for (j = 0; j < quantidadesAuxiliares[idx] - 1 - i; j++)
        {
            if (vetorAux[j] > vetorAux[j + 1])
            {
                temp = vetorAux[j];
                vetorAux[j] = vetorAux[j + 1];
                vetorAux[j + 1] = temp;
            }
        }
    }

    return SUCESSO;
}

/*
Objetivo: retorna os números de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosDeTodasEstruturasAuxiliares(int vetorAux[])
{
    int total = 0;
    int i, j;

    for (i = 0; i < TAM; i++)
    {
        if (quantidadesAuxiliares[i] > 0)
        {
            for (j = 0; j < quantidadesAuxiliares[i]; j++)
            {
                vetorAux[total] = ponteirosAuxiliares[i][j];
                total++;
            }
        }
    }

    if (total == 0)
        return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;

    return SUCESSO;
}

/*
Objetivo: retorna os números ordenados de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[])
{

    int retorno = getDadosDeTodasEstruturasAuxiliares(vetorAux);

    if (retorno != SUCESSO)
        return retorno;

    int total = 0;
    int i, j;
    for (i = 0; i < TAM; i++)
        if (quantidadesAuxiliares[i] > 0)
            total += quantidadesAuxiliares[i];

    int tmp;
    for (i = 0; i < total - 1; i++)
    {
        for (j = 0; j < total - 1 - i; j++)
        {
            if (vetorAux[j] > vetorAux[j + 1])
            {
                tmp = vetorAux[j];
                vetorAux[j] = vetorAux[j + 1];
                vetorAux[j + 1] = tmp;
            }
        }
    }

    return SUCESSO;
}

/*
Objetivo: modificar o tamanho da estrutura auxiliar da posição 'posicao' para o novo tamanho 'novoTamanho' + tamanho atual
Suponha o tamanho inicial = x, e novo tamanho = n. O tamanho resultante deve ser x + n. Sendo que x + n deve ser sempre >= 1

Rertono (int)
    SUCESSO - foi modificado corretamente o tamanho da estrutura auxiliar
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    NOVO_TAMANHO_INVALIDO - novo tamanho não pode ser negativo
    SEM_ESPACO_DE_MEMORIA - erro na alocação do novo valor
*/
int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho)
{

    if (ehPosicaoValida(posicao) == POSICAO_INVALIDA)
        return POSICAO_INVALIDA;

    int idx = posicao - 1;

    if (quantidadesAuxiliares[idx] == -1)
        return SEM_ESTRUTURA_AUXILIAR;

    int tamanhoResultante = tamanhosAuxiliares[idx] + novoTamanho;

    if (tamanhoResultante < 1)
        return NOVO_TAMANHO_INVALIDO;

    int *novoPonteiro = (int *)realloc(ponteirosAuxiliares[idx], tamanhoResultante * sizeof(int));
    if (novoPonteiro == NULL)
        return SEM_ESPACO_DE_MEMORIA;

    ponteirosAuxiliares[idx] = novoPonteiro;
    tamanhosAuxiliares[idx] = tamanhoResultante;

    if (quantidadesAuxiliares[idx] > tamanhoResultante)
        quantidadesAuxiliares[idx] = tamanhoResultante;

    return SUCESSO;
}

/*
Objetivo: retorna a quantidade de elementos preenchidos da estrutura auxiliar da posição 'posicao'.

Retorno (int)
    POSICAO_INVALIDA - posição inválida
    SEM_ESTRUTURA_AUXILIAR - sem estrutura auxiliar
    ESTRUTURA_AUXILIAR_VAZIA - estrutura auxiliar vazia
    Um número int > 0 correpondente a quantidade de elementos preenchidos da estrutura
*/
int getQuantidadeElementosEstruturaAuxiliar(int posicao)
{
    if (ehPosicaoValida(posicao) == POSICAO_INVALIDA)
        return POSICAO_INVALIDA;

    int idx = posicao - 1;

    if (quantidadesAuxiliares[idx] == -1)
        return SEM_ESTRUTURA_AUXILIAR;

    if (quantidadesAuxiliares[idx] == 0)
        return ESTRUTURA_AUXILIAR_VAZIA;

    return quantidadesAuxiliares[idx];
}

/*
Objetivo: montar a lista encadeada com cabeçote com todos os números presentes em todas as estruturas.

Retorno (No*)
    NULL, caso não tenha nenhum número nas listas
    No*, ponteiro para o início da lista com cabeçote
*/
No *montarListaEncadeadaComCabecote()
{
    int i, j;
    int existeAlgumNumero = 0;
    for (i = 0; i < TAM; i++)
        if (quantidadesAuxiliares[i] > 0)
            existeAlgumNumero = 1;

    if (!existeAlgumNumero)
        return NULL;

     No *cabecote = (No *)malloc(sizeof(No));
    cabecote->conteudo = 0;
    cabecote->prox = NULL;

    No *ultimo = cabecote;

    for (i = 0; i < TAM; i++)
    {
        if (quantidadesAuxiliares[i] > 0)
        {
            for (j = 0; j < quantidadesAuxiliares[i]; j++)
            {
                No *novo = (No *)malloc(sizeof(No));
                novo->conteudo = ponteirosAuxiliares[i][j];
                novo->prox = NULL;

                ultimo->prox = novo;
                ultimo = novo;
            }
        }
    }

    return cabecote;
}

/*
Objetivo: retorna os números da lista enceada com cabeçote armazenando em vetorAux.
Retorno void
*/
void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[])
{
     if (inicio == NULL)
        return;

    int i = 0;
    No *atual = inicio->prox; 

    while (atual != NULL)
    {
        vetorAux[i] = atual->conteudo;
        i++;
        atual = atual->prox;
    }
}

/*
Objetivo: Destruir a lista encadeada com cabeçote a partir de início.
O ponteiro inicio deve ficar com NULL.

Retorno 
    void.
*/
void destruirListaEncadeadaComCabecote(No **inicio)
{
    No *atual = *inicio;

    while (atual != NULL)
    {
        No *proximo = atual->prox;
        free(atual);
        atual = proximo;
    }

    *inicio = NULL;
}

/*
Objetivo: inicializa o programa. deve ser chamado ao inicio do programa 

*/

void inicializar()
{
    int i;
    for (i = 0; i < TAM; i++)
    {
        ponteirosAuxiliares[i] = NULL;
        tamanhosAuxiliares[i] = 0;
        quantidadesAuxiliares[i] = -1;
    }
}

/*
Objetivo: finaliza o programa. deve ser chamado ao final do programa 
para poder liberar todos os espaços de memória das estruturas auxiliares.

*/

void finalizar()
{
    int i;
    for (i = 0; i < TAM; i++)
    {
        if (quantidadesAuxiliares[i] != -1)
        {
            free(ponteirosAuxiliares[i]);
            ponteirosAuxiliares[i] = NULL;
        }
        quantidadesAuxiliares[i] = -1;
        tamanhosAuxiliares[i] = 0;
    }
}

void dobrar(int *x)
{
    *x = (*x) * 2;
}