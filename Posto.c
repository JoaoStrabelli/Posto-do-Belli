#include <stdio.h>
#include "funcoesPosto.h"

int main(){

    float valorCombustivel, valorTotal = 0, vendaTotal = 0, tanque = 200, litrosTotal = 0;
    char escolha2;
    int maxCarros, quantAbastecida = 0, escolha, carrosFila = 0, carrosAtendidos = 0;
    
    FILE *file;

    hello();

    printf("\n\nInforme o valor do combustivel: ");

    valida(valorCombustivel, "valor do combustivel");

    printf("\nInforme o tamanho maximo da fila: ");

    valida(maxCarros, "tamanho da fila");

    struct TCarro *espera;
    espera = calloc(maxCarros, sizeof(struct TCarro));

    struct TCarro *atendido;
    atendido=calloc(0, sizeof(struct TCarro));

    while(escolha != 5){

        menu(&escolha);

        switch(escolha){

            case 1:

                adicionarCarro(maxCarros, &carrosFila, tanque, espera);

            break;
            
            case 2:

                atendido =(struct TCarro *) realloc (atendido, (carrosAtendidos + 1) * sizeof(struct TCarro)); 

                abastecimento(&tanque, &carrosFila, quantAbastecida, valorTotal, 
                valorCombustivel, &litrosTotal, &vendaTotal, &carrosAtendidos, espera, atendido);

                remover(espera, carrosFila);

            break;

            case 3:

                if(carrosFila == 0){

                    printf(BLU"Nao possuem carros na fila"RESET);

                }else{

                    filaCarros(carrosFila, espera);
                }

            break;

            case 4:

                escolha2 = 'a';

                while(escolha2 != 'f'){

                    relatorio(&escolha2);

                    switch(escolha2){

                        case 'a':

                            printf("Quantidade de litros vendidos: %.2fL", litrosTotal);

                        break;

                        case 'b':

                            printf("Valor total: R$%.2f", vendaTotal);

                        break;

                        case 'c': 

                            printf(GRN"Quantidade de carro(s) atendido(s): %d carro(s)\n"RESET, carrosAtendidos);

                            atendidos(atendido, carrosAtendidos, stdout);

                        break;

                        case 'd':

                            printf(BLU"Quantidade restante no tanque: %.2fL"RESET, tanque);

                        break;

                        case 'e':

                            file = fopen("relatorio.txt", "w");

                            fprintf(file, "Quantidade de litros vendidos: %.2fL", litrosTotal);
                            fprintf(file, "\t\nValor total: R$%.2f", vendaTotal);
                            fprintf(file, "\t\nQuantidade de carros atendida: %d carros\n", carrosAtendidos);
                            atendidos(atendido, carrosAtendidos, file);
                            fprintf(file, "\t\nQuantidade restante no tanque: %.2fL", tanque);
                            fclose(file);

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