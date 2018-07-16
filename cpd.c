#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include <string.h>
#include "arvore_b.h"
#define NUM_DADOS 10000
#define MAX_AUX_VALOR 10

struct s_dado {
    int ano;
    int mes;
    int codigo;
    char nome[250];
    char UF[2];
    int T_prest_int_f; //Nº total de prestadores (autorizadas) de acessos de internet fixa (SCM)
    int T_acesso_int_f; //Nº total de acessos de internet fixa (SCM) em serviço
    int Ass_TV_ass;
    int Cobert_3g;
    int posicao;
};


void salto(FILE* entrada, int n_saltos)
{
    char c;
    int i;

    for (i=0; i<= n_saltos; i++)
        while (c != ';')
            c = fgetc(entrada);
}

void inicializa_dado(struct s_dado* dado){
    int i;
    dado->ano = 0;
    dado->mes = 0;
    dado->codigo = 0;
    for (i=0;i<250;i++)
        dado->nome[i] = 0;
    dado->UF[0] = dado->UF[1] = 0;
    dado->T_prest_int_f = 0;
    dado->T_acesso_int_f = 0;
    dado->Ass_TV_ass = 0;
    dado->Cobert_3g = 0;
}

void conv_txt_bin (FILE* database){  //recebe um arquivo txt e transforma em binario
    struct s_dado dado;
    char carac;
    FILE *entrada;

    char nArqEntrada[16];
    int cont =0;
    int j=0;
    char aux_mes[2]= {};
    char ano_aux[5]={0};
    char aux_cod[7] = {0};
    char aux_valor[MAX_AUX_VALOR] = {0};
    int c_max, k;



    printf("\nConversão de Arquivo texto para arquivo binario\nInsira o nome do arquivo texto: ");
    gets(nArqEntrada);

    if ((entrada = fopen(nArqEntrada, "r")) == NULL)
        printf("Erro ao abrir arquivo");
    printf("ASSEMBLYING DATA\n");


    while (!feof(entrada) && cont<NUM_DADOS)
    {
        //inicializando struct
        inicializa_dado(&dado);

//==================ANO===================
        j=0;
        carac = fgetc(entrada);
        while (carac != ';')
        {
            ano_aux[j] = carac;
            j++;
            carac = fgetc(entrada);
        }
        ano_aux[4] = '\0';
        dado.ano = atoi(ano_aux);
        //printf("Ano %d\n", dado.ano);
//==================MES===================
        aux_mes[0] = fgetc(entrada);
        if( (carac = fgetc(entrada)) == ';')
            dado.mes = aux_mes[0] - 48;
        else
        {
            printf("teste");
            aux_mes[1] = carac;
            dado.mes = atoi(aux_mes);
        }
        //printf("Mes %d\n", dado.mes);

//==================CODIGO===================
        j=0;
        carac = fgetc(entrada);
        while (carac != ';') //
        {
            aux_cod[j] = carac;
            j++;
            carac = fgetc(entrada);
        }
        aux_cod[7] = '\0';
        dado.codigo = atoi(aux_cod);
        //printf("codigo %d\n", dado.codigo);

//==================NOME===================
        j=0;
        carac = fgetc(entrada);
        while (carac != ';') //
        {
            dado.nome[j] = carac;
            j++;
            carac = fgetc(entrada);
        }
        dado.nome[j] = '\0';
        //printf("Nome %s\n", dado.nome);

//==================salto codigo UF===================
        salto(entrada,1);


//==================UF===================
        j=0;
        carac = fgetc(entrada);
        while (carac != ';')
        {
            dado.UF[j] = carac;
            j++;
            carac = fgetc(entrada);
        }

        //printf("UF %s\n", dado.UF);

//==============================================================
//===Nº total de prestadores (autorizadas) de acessos de internet fixa (SCM)===
//==============================================================
        j=0; c_max =1;
        for (k=0; k<MAX_AUX_VALOR;k++)
            aux_valor[k]=0;

        carac = fgetc(entrada);
        while (carac != ';')
        {
            aux_valor[j] = carac;
            j++;
            carac = fgetc(entrada);
        }
        j--;
        while(j+1) //ajustar vetor para conversao
        {
            aux_valor[MAX_AUX_VALOR-c_max] = aux_valor[j];
            aux_valor[j] =0;
            j--; c_max++;
        }
        dado.T_prest_int_f = atoi(aux_valor); //transferir valor para o campo
       // printf("Numero de fornecedores de internet fixa %d\n", dado.T_prest_int_f);

//==============================================================
//===Nº total de acessos de internet fixa (SCM) em serviço======
//==============================================================
        j=0; c_max =1;
        for (k=0; k<MAX_AUX_VALOR;k++)
            aux_valor[k]=0;

        carac = fgetc(entrada);
        while (carac != ';')
        {
            aux_valor[j] = carac;
            j++;
            carac = fgetc(entrada);
        }
        j--;
        while(j+1) //ajustar vetor para conversao
        {
            aux_valor[MAX_AUX_VALOR-c_max] = aux_valor[j];
            aux_valor[j] =0;
            j--; c_max++;
        }
        dado.T_acesso_int_f = atoi(aux_valor); //transferir valor para o campo
        //printf("Numero de acesso a internet fixa %d\n", dado.T_acesso_int_f);

//==============================================================
//==============================================================
        //salto Município já atendido pelo PNBL;
        //salto Nº de telefones de uso público (TUP) em serviço;
        //salto  Nº de assinantes de TV por assinatura (TVC, MMDS e TVA)
        salto(entrada,3);
//==============================================================
//==============================================================


//==================================================================================
        //Nº total de assinantes de TV por assinatura (TVC, MMDS, TVA e DTH)
//==================================================================================
        j=0; c_max =1;
        for (k=0; k<MAX_AUX_VALOR;k++)
            aux_valor[k]=0;

        carac = fgetc(entrada);
        while (carac != ';')
        {
            aux_valor[j] = carac;
            j++;
            carac = fgetc(entrada);
        }
        j--;
        while(j+1) //ajustar vetor para conversao
        {
            aux_valor[MAX_AUX_VALOR-c_max] = aux_valor[j];
            aux_valor[j] =0;
            j--; c_max++;
        }
        dado.Ass_TV_ass = atoi(aux_valor); //transferir valor para o campo
        //printf("Numero total de assinantes de TV por assinatura %d\n", dado.Ass_TV_ass);

//==============================================================
//==============================================================
        //salto Nº de assinantes de TV por assinatura via satélite (DTH);
        //salto Nº de prestadores de serviço de TV por assinatura (TVC, MMDS e TVA);
        salto(entrada,2);
//==============================================================
//==============================================================

//==============================================================
//Município coberto por internet banda larga móvel (SMP tecnologia 3G)
//==============================================================
        carac = fgetc(entrada);

        if (carac == '1' )
            dado.Cobert_3g = 1;
        else
            dado.Cobert_3g = 0;

       // if (dado.Cobert_3g)
           // printf("3G: sim\n");
        //else
            //printf("3G: nao\n");


        //SALTAR TODOS OS OUTROS 52
        //salto(entrada,51);
        //ultimo registro
        do
        {
            carac = fgetc(entrada);
        }while (carac != '\n');

        cont++;
        dado.posicao = busca_posicao(database);
        fwrite(&dado, sizeof(struct s_dado), 1, database);


    }
    printf("\nConversao Finalizada\n");

}

int escreve_tela(int posicao, FILE* database){ //printa na tela o registro da posicao recebida
    struct s_dado buffer;


    fseek(database,sizeof(struct s_dado)*posicao, SEEK_SET);
    fread(&buffer,sizeof(struct s_dado),1,database);

    printf(
        "Ano %d\nMes %d\ncodigo %d\nNome %s\nUF %s\nNumero de fornecedores de internet fixa %d\nNumero de acesso a internet fixa %d\nNumero de assinantes de TV por assinatura: %d\n "
        ,buffer.ano,buffer.mes,buffer.codigo,buffer.nome,buffer.UF,buffer.T_prest_int_f, buffer.T_acesso_int_f, buffer.Ass_TV_ass);


    if (buffer.Cobert_3g)
        printf("3G: sim\n");
    else
        printf("3G: nao\n");
return 0;


}

void insere_registro(FILE* database, TipoPagina* raiz){ //insere novo registro manualmente

    struct TipoRegistro reg;
    struct s_dado new_dado, buffer;

    inicializa_dado(&new_dado);
    printf("Insira os dados: \n");
    printf("Ano: ");
    scanf("%d", &new_dado.ano);
    printf("Mes(codigo): ");
    scanf("%d", &new_dado.mes);
    printf("Codigo da cidade: ");
    scanf("%d", &new_dado.codigo);
    printf("Nome da Cidade: ");
    fflush(stdin);
    gets(new_dado.nome);
    printf("UF: ");
    fflush(stdin);
    gets(new_dado.UF);
    printf("N de prestadores de acessos de internet fixa: ");
    scanf("%d", &new_dado.T_prest_int_f);
    printf("N de acessos de internet: ");
    scanf("%d", &new_dado.T_acesso_int_f);
    printf("N de assinantes de TV por assinatura: ");
    scanf("%d", &new_dado.Ass_TV_ass);
    printf("Cobertura 3g (0/1): ");
    scanf("%d", &new_dado.Cobert_3g);
    new_dado.posicao = busca_posicao(database);
    printf("%d", new_dado.posicao);
    fseek(database,0, SEEK_END);

   // if ((database = fopen("database.bin", "a+b")) == NULL)
    //    printf("Erro ao abrir arquivo: database");
    fwrite(&new_dado,sizeof(struct s_dado),1,database);
    reg.Chave = new_dado.codigo;
    reg.posicao = new_dado.posicao;
    Insere(reg, &raiz);
}


int busca_posicao (FILE* database)
{
    struct s_dado dado_temp;
    if (ftell(database) == 0)
        return 0;

    fseek (database, sizeof(struct s_dado)*(-1), SEEK_END );
    fread(&dado_temp, sizeof(struct s_dado), 1, database);
    return (dado_temp.posicao +1);
}




int main()
{
    FILE* database;
    TipoPagina* raiz;
    inicializa_raiz(&raiz);
    if ((database = fopen("database.bin", "a+b")) == NULL)
        printf("Erro ao abrir database");

    conv_txt_bin(database);
    //insere_registro(database, raiz);
    escreve_tela(0,database);
    escreve_tela(1,database);
    escreve_tela(2,database);
    escreve_tela(3,database);

    fclose(database);
    return 0;
}


