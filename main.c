#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define TAM_TEX_MAXIMO 2048

typedef struct _personagem {
    char nome[50];
    int hp;
    int defesa;
    int ataque;
    int carisma;
    int posicao;
} PERSONAGEM;

void imprimir_atual(int pagina);
void imprimir_menu();
void limpar_tela();
int dado_aleatorio(int faces);
void menu_inicial(PERSONAGEM *jogador);
void criar_personagem(PERSONAGEM *jogador);
void gravar_jogo(PERSONAGEM jogador);
int continuar_jogo();
void criar_personagem(PERSONAGEM *jogador);
void teste_carisma(PERSONAGEM *jogador);
int combate(PERSONAGEM *jogador);

int main() {
    int combate_atual = 0;
    char comando;
    int parar = 1;
    PERSONAGEM jogador;
    srand(time(NULL));
    menu_inicial(&jogador); // criação de personagem, lista autores, recorde, etc...

    while (parar) {
        imprimir_atual(jogador.posicao);
        imprimir_menu();
        scanf(" %c", &comando);
        // limpar_tela();
        switch (comando) {
            case 'A':
                if(jogador.posicao == 1){
                    jogador.posicao = 2;
                    break;
                } else if(jogador.posicao == 2){
                    jogador.posicao = 3;
                    break;
                } else if(jogador.posicao == 3){
                    if(combate(&jogador) == 1){
                        jogador.posicao = 4;
                    } else{
                        printf("Você morreu!\n");
                        printf("Voltando ao último jogo salvo...\n");
                        jogador.posicao = continuar_jogo();
                    }
                    break;
                } else if(jogador.posicao == 4){
                    jogador.posicao = 5;
                    break;
                } else if(jogador.posicao == 5){
                    jogador.posicao = 6;
                    break;
                } else if(jogador.posicao == 7){
                    jogador.posicao = 12;
                    break;
                } else if(jogador.posicao == 9){
                    jogador.posicao = 10;
                    break;
                } else if(jogador.posicao == 10){
                    jogador.posicao = 11;
                    break;
                } else if(jogador.posicao == 11){
                    jogador.posicao = 7;
                    break;
                } else if(jogador.posicao == 10){
                    jogador.posicao = 19;
                    break;
                }
                break;
            case 'B':
                if(jogador.posicao == 1){
                    jogador.posicao = 9;
                    break;
                } else if(jogador.posicao == 2){
                    jogador.posicao = 3;
                    break;
                } else if(jogador.posicao == 3){
                    teste_carisma(&jogador);
                    jogador.posicao = 4;
                    break;
                } else if(jogador.posicao == 4){
                    jogador.posicao = 13;
                    break;
                } else if(jogador.posicao == 7){
                    jogador.posicao = 8;
                    break;
                } else if(jogador.posicao == 9){
                    jogador.posicao = 14;
                    break;
                } else if(jogador.posicao == 10){
                    jogador.posicao = 2;
                    break;
                } else if(jogador.posicao == 11){
                    jogador.posicao = 14;
                    break;
                }
                break;
            case 'Q':   
                parar = 0;
                break;
            case 'G':   
                gravar_jogo(jogador);
                printf("Jogo salvo com sucesso!\n");
                break;
        }
        if(jogador.posicao == 6){
            imprimir_atual(jogador.posicao);
            jogador.posicao = 7;
        } else if(jogador.posicao == 12){
            imprimir_atual(jogador.posicao);
            parar = 0;
        } else if(jogador.posicao == 13){
            imprimir_atual(jogador.posicao);
            jogador.posicao = 7;
        } else if(jogador.posicao == 8){
            imprimir_atual(jogador.posicao);
            parar = 0;
        } else if(jogador.posicao == 14){
            imprimir_atual(jogador.posicao);
            jogador.posicao = 2;
        }
    }
    return 0;
}

void imprimir_atual(int pagina) {
    FILE *fp;
    char texto[TAM_TEX_MAXIMO];
    memset(texto, 0, sizeof(texto));
    switch (pagina) {
        case 1:
            fp = fopen("pag1.dat", "rb");
            break;
        case 2:
            fp = fopen("pag2.dat", "rb");
            break;
        case 3:
            fp = fopen("pag3.dat", "rb");
            break;
        case 4:
            fp = fopen("pag4.dat", "rb");
            break;
        case 5:
            fp = fopen("pag5.dat", "rb");
            break;
        case 6:
            fp = fopen("pag6.dat", "rb");
            break;
        case 7:
            fp = fopen("pag7.dat", "rb");
            break;
        case 8:
            fp = fopen("pag8.dat", "rb");
            break;
        case 9:
            fp = fopen("pag9.dat", "rb");
            break;
        case 10:
            fp = fopen("pag10.dat", "rb");
            break;
        case 11:
            fp = fopen("pag11.dat", "rb");
            break;
        case 12:
            fp = fopen("pag12.dat", "rb");
            break;
        case 13:
            fp = fopen("pag13.dat", "rb");
            break;
        case 14:
            fp = fopen("pag14.dat", "rb");
            break;
    }
    size_t bytesRead = fread(texto, sizeof(char), TAM_TEX_MAXIMO - 1, fp);
    texto[bytesRead] = '\0';
    printf("%s\n", texto);
    fclose(fp);
}

void imprimir_menu() {
    printf("%10s %10s %10s %10s\n", "[A] Escolher", "[B] Escolher", "[G] Gravar progresso", "[Q] Sair");
}

void limpar_tela() {
    //system("cls"); // no Windows
    system("clear"); // no Linux
}

int dado_aleatorio(int faces) {
    int resultado;
    resultado = rand() % faces + 1;
    return resultado;
}

void menu_inicial(PERSONAGEM *jogador) {
    int opcao;
    printf("\nBem vindo(a)!!!\n");
    printf("\n");
    printf("(1) Iniciar um novo jogo\n");
    printf("(2) Continuar jogo salvo\n");
    printf("(3) Listar membros do grupo\n");
    printf("Digite a opcao: ");
    scanf("%d", &opcao);
    switch (opcao) {
        case 1: 
            criar_personagem(jogador);
            break;
        case 2:
            printf("Continuando o jogo...\n");
            jogador->posicao = continuar_jogo();
            break;
        case 3: 
            printf("Pedro Henrique de Oliveira Duarte\n");
            break;
        default:
            printf("Opcao invalida!\n");
            break;
    }
}

void criar_personagem(PERSONAGEM *jogador) {
    int PONTOS_TOTAIS = 100;
    int pontos_distribuidos = 0;
    int pontos_restantes = PONTOS_TOTAIS;

    printf("Digite o nome do seu personagem: ");
    scanf("%s", jogador->nome);

    while (pontos_distribuidos < PONTOS_TOTAIS) {
        printf("\nVoce tem %d pontos restantes para distribuir.\n", pontos_restantes);

        printf("Digite a vida maxima do seu personagem (pontos restantes: %d): ", pontos_restantes);
        scanf("%d", &jogador->hp);
        if (jogador->hp > pontos_restantes) {
            printf("Voce nao tem pontos suficientes para essa distribuicao. Tente novamente.\n");
            continue;
        }
        pontos_distribuidos += jogador->hp;
        pontos_restantes -= jogador->hp;

        printf("Digite o valor de defesa do seu personagem (pontos restantes: %d): ", pontos_restantes);
        scanf("%d", &jogador->defesa);
        if (jogador->defesa > pontos_restantes) {
            printf("Voce nao tem pontos suficientes para essa distribuicao. Tente novamente.\n");
            pontos_distribuidos -= jogador->hp;
            pontos_restantes += jogador->hp;
            continue;
        }
        pontos_distribuidos += jogador->defesa;
        pontos_restantes -= jogador->defesa;

        printf("Digite o valor de ataque do seu personagem (pontos restantes: %d): ", pontos_restantes);
        scanf("%d", &jogador->ataque);
        if (jogador->ataque > pontos_restantes) {
            printf("Voce nao tem pontos suficientes para essa distribuicao. Tente novamente.\n");
            pontos_distribuidos -= jogador->defesa;
            pontos_restantes += jogador->defesa;
            continue;
        }
        pontos_distribuidos += jogador->ataque;
        pontos_restantes -= jogador->ataque;

        printf("Digite o valor de carisma do seu personagem (pontos restantes: %d): ", pontos_restantes);
        scanf("%d", &jogador->carisma);
        if (jogador->carisma > pontos_restantes) {
            printf("Voce nao tem pontos suficientes para essa distribuicao. Tente novamente.\n");
            pontos_distribuidos -= jogador->ataque;
            pontos_restantes += jogador->ataque;
            continue;
        }
        pontos_distribuidos += jogador->carisma;
        pontos_restantes -= jogador->carisma;

        if (pontos_restantes < 0) {
            printf("Voce distribuiu mais pontos do que o permitido. Tente novamente.\n");
            pontos_distribuidos = 0;
            pontos_restantes = PONTOS_TOTAIS;
        } else {
            break;
        }
    }

    jogador->posicao = 1;
    printf("\nPersonagem criado com sucesso!\n");
    printf("\n");
}

void gravar_jogo(PERSONAGEM jogador){
    FILE *fs;
    fs = fopen("save.txt", "w");
    fprintf(fs, "%d", jogador.posicao);
    fclose(fs);
}

int continuar_jogo(){
    FILE *fs;
    int posicao;
    fs = fopen("save.txt", "r");
    while(!feof(fs)){
        fscanf(fs, "%d", &posicao);
    }
    fclose(fs);
    return posicao;
}

void teste_carisma(PERSONAGEM *jogador){
    int resistencia_npc = dado_aleatorio(50);
    int teste_carisma = dado_aleatorio(50) + jogador->carisma;
    if(teste_carisma > resistencia_npc){
        printf("Com seu charme impecavel e oratoria invejavel, voce convenceu o capanga a se render!\n");
    } else{
        printf("Voce falhou em convencer o capanga a se render\n");
        combate(jogador);
    }
}

int combate(PERSONAGEM *jogador){
    int vida_npc = 70;
    int turno = 1;
    int resistencia_npc = dado_aleatorio(100);
    int teste_ataque;
    int teste_npc;
    char input;
    printf("Voce entrou em combate!\n");
    while(jogador->hp > 0 && vida_npc > 0){
        if(turno % 2 != 0){
            printf("Sua vez! Digite A para atacar!\n");
            scanf(" %c", &input);
            if(input == 'A'){
                printf("Rolando seu ataque...\n");
                teste_ataque = dado_aleatorio(100) + jogador->ataque;
                if(teste_ataque > resistencia_npc){
                    printf("Voce acertou!\n");
                    vida_npc-=30;
                    printf("HP do inimigo: %d\n", vida_npc);
                } else{
                    printf("Voce errou!\n");
                }
                turno++;
            }
        } else{
            printf("Vez do inimigo!\n");
            printf("O inimigo esta rolando o ataque...\n");
            teste_npc = dado_aleatorio(80);
            if(teste_npc > jogador->defesa){
                printf("O inimigo te acertou!\n");
                jogador->hp-=10;
                printf("Seu HP: %d\n", jogador->hp);
            } else{
                printf("O inimigo errou!\n");
            }
            turno++;
        }
    }
    if(jogador->hp <= 0){
        return 0;
    } else{
        printf("Com suas habilidades de combate afiadas, voce foi capaz de subjulgar o inimigo.\n");
        return 1;
    }
}