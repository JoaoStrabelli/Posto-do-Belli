#include <stdio.h>
#include <stdlib.h>

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

struct TCarro{

    char modelo[20], cor[20];
    int ano;

};

void hello(){

    printf("--------------------------------------");
    printf("\n  Bem vindo ao Posto de gasolina!!!");
    printf("\n  Autor: Joao Pedro Dezan Strabelli");
    printf("\n--------------------------------------");
}

void flush_in(){

    int ch;

    do{

        ch = fgetc(stdin);

    }while(ch != EOF && ch != '\n');
}

void valida(float *valor, char *s){

    while(!scanf("%f", &*valor) || *valor <= 0){

            printf(RED"Valor invalido"RESET);
            printf("\n\nInforme o %s novamente: ", s);
            flush_in();
    }
}

void menu(int *opcao){

    printf(GRN"\n--------------MENU-----------------"RESET);
            printf("\n  1 - Adicionar um carro a fila");
            printf("\n  2 - Abastecimento");
            printf("\n  3 - Exibir carros na fila de espera");
            printf("\n  4 - Relatorio");
            printf("\n  5 - Encerrar");
            printf(GRN"\n-----------------------------------\n"RESET);
            printf("\nEscolha uma opcao: ");
            
            while(!scanf("%d", &*opcao)){

                printf(RED"Valor invalido!\n Informe novamente: "RESET);
                flush_in();
            }

            system("cls");
}

void remover(struct TCarro espera[], int carrosFila){

    for(int j = 0; j < carrosFila; j++){

        espera[j] = espera[j + 1];
    }
}

void adicionarCarro(float totalCarros, int *carrosFila, float tanque, struct TCarro espera[]){

    if(tanque > 0){

        if(totalCarros > *carrosFila){

            flush_in();

            printf("Informe o modelo do carro: ");
            fgets(espera[*carrosFila].modelo, 20, stdin);

            printf("Informe a cor do carro: ");
            fgets(espera[*carrosFila].cor, 20, stdin);

            printf("Informe o ano do carro: ");
            
            while(!scanf("%d", &espera[*carrosFila].ano) || espera[*carrosFila].ano <= 0){

                printf(RED"Valor invalido!"RESET);
                printf("\n\nInforme o ano novamente: ");
                fflush(stdin);
            }

            printf(GRN"\nCarro adicionado a fila!"RESET);

            *carrosFila = *carrosFila + 1;

        }else
            printf(RED"\nLotacao maxima atingida!"RESET);

    }else
        printf(RED"\nEstamos sem combustivel no momento"RESET);

    
}

void abastecimento(float *qntComb, int *carrosFila, float qntAbastecida, float valorTot, 
float valorComb, float *litrosTot, float *vendaTotal, int *carrosAtend, struct TCarro espera[], 
struct TCarro atend[]){

    if(*carrosFila > 0){
        
        if(*qntComb != 0){

            printf(BLU"Quantidade disponivel no tanque: %.2f L\n"RESET, *qntComb);
            printf("Informe a quantidade a ser abastecida(L): ");

            scanf("%f", &qntAbastecida);
            
            while((qntAbastecida <= 0) || (qntAbastecida > *qntComb)){

                flush_in();

                printf(RED"\n\nValor invalido!"RESET);
                printf("\n\nInforme novamente a quantidade a ser abastecida(L): ");
                scanf("%f", &qntAbastecida);
            }

                        valorTot = qntAbastecida * valorComb;

                        printf("Valor total: R$%.2f", valorTot);

                        *litrosTot += qntAbastecida;

                        *vendaTotal += valorTot;

                        *carrosFila = *carrosFila - 1; 

                        *qntComb -= qntAbastecida;

                        atend[*carrosAtend] = espera[0];

                        *carrosAtend = *carrosAtend + 1;

        }else{
            printf(BLU"Estamos sem combustivel no momento! Tente novamente mais tarde ;("RESET);
    
            *carrosFila = *carrosFila - 1;

        }
    }else
        printf(RED"Nao possuem carros na fila!"RESET);

}

void filaCarros(int carrosFila, struct TCarro espera[]){

        for(int i = 0; carrosFila > i; i++){
            printf(BLU"------------------------------------"RESET);
            printf("\nModelo: %s", espera[i].modelo);
            printf("Cor: %s", espera[i].cor);
            printf("Ano: %d\n\n", espera[i].ano);
        }
            
}

void relatorio(char *opcao2){

    printf("\n\n---------------------------------MENU--------------------------------------");
    printf("\na - Quantidade de litros vendida");
    printf("\nb - Valor total arrecadado com as vendas");
    printf("\nc - Quantidade de carros atendidos");
    printf("\nd - Quantidade de combustivel restante no tanque");
    printf("\ne - Gerar arquivo para impressao (com todas as informacoes de A, B, C e D)");
    printf("\nf - Voltar ao menu anterior");
    printf("\n----------------------------------------------------------------------------\n\n");
    printf("Escolha uma opcao: ");

    fflush(stdin);

    while(!scanf("%c", &*opcao2)){

                printf(RED"Valor invalido!\n Informe novamente: "RESET);
                flush_in();
    }

    system("cls");
}

void atendidos(struct TCarro atend[], int carrosAtend, FILE *file){

    for(int i = 0; carrosAtend > i; i++){

            fprintf(file, "------------------------------------");
            fprintf(file, "\nModelo: %s", atend[i].modelo);
            fprintf(file, "Cor: %s", atend[i].cor);
            fprintf(file, "Ano: %d\n\n", atend[i].ano);
        }
}