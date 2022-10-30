#include <stdio.h>
#include "funcoesPosto.h"

int main(){

    float valorCombustivel, valorTotal = 0, vendaTotal = 0;
    char escolha2;
    int maxCarros, quantAbastecida, escolha, carrosFila = 0, litrosTotal = 0, carrosAtendidos = 0;
    int tanque = 200;

    #define RED   "\x1B[31m"
    #define GRN   "\x1B[32m"
    #define YEL   "\x1B[33m"
    #define BLU   "\x1B[34m"
    #define MAG   "\x1B[35m"
    #define CYN   "\x1B[36m"
    #define WHT   "\x1B[37m"
    #define RESET "\x1B[0m"

    hello();

    printf("\n\nInforme o valor do combustivel: ");

    validComb(&valorCombustivel);

    printf("\nInforme o tamanho maximo da fila: ");

    validMaxCarros(&maxCarros);

    struct TCarro espera[maxCarros], atendido[maxCarros*2];

    while(escolha != 5){

        menu(&escolha);

        switch(escolha){

            case 1:

                adicionarCarro(maxCarros, &carrosFila, tanque, espera);

            break;
            
            case 2:

                abastecimento(&tanque, &carrosFila, quantAbastecida, valorTotal, 
                valorCombustivel, &litrosTotal, &vendaTotal, &carrosAtendidos, espera, atendido);

            break;

            case 3:

                if(carrosFila == 0){

                    printf(BLU"Nao possuem carros na fila"RESET);

                }else{

                    filaCarros(&carrosFila, espera);

                }

            break;

            case 4:

                escolha2 = 'a';

                while(escolha2 != 'f'){

                    relatorio(&escolha2);

                    switch(escolha2){

                        case 'a':

                            printf("Quantidade de litros vendidos: %dL", litrosTotal);

                        break;

                        case 'b':

                            printf("Valor total: R$%.2f", vendaTotal);

                        break;

                        case 'c': 

                            printf("Quantidade de carros atendidos: %d carros", carrosAtendidos);

                        break;

                        case 'd':

                            printf("Quantidade restante no tanque: %dL", tanque);

                        break;

                        case 'e':

                            arquivo(&litrosTotal, &vendaTotal, &carrosAtendidos, &tanque);

                        break;

                        case 'f':

                            printf(BLU"Voltando..."RESET);

                        break;

                        default:

                            printf(RED"Escolha invalida!"RESET);

                        break;
                    }
                }

            break;

            case 5:

                printf(BLU"Muito obrigado e volte sempre!!!"RESET);

            break;

            default:

                printf(RED"Escolha invalida! Tente novamente"RESET);
            
            break;
        }
    }

    return 0;
}