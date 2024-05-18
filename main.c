#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

#define TAM_TEX_MAXIMO 400

typedef struct _personagem
	{
	char nome[50];
	int hp;
	int defesa;
	int ataque;
	int dano;
	int posicao;
	} PERSONAGEM;
	
	void imprimir_atual(int pagina);
	void imprimir_menu();
	void limpar_tela();
	int dado_aleatorio(int faces);
	void menu_inicial();
	void olhar(int posicao);
	int imprimir_status(PERSONAGEM jogador);
	void mover(int posicao, PERSONAGEM *jogador);
	
	int main()
		{
		int combate_atual = 0;
		char comando;
		int parar = 1;
		srand(time(NULL));
		menu_inicial(); //criacao de personagem, lista autores, recorde, etc...
		
		//cria��o do personagem feita de forma direta - deveria ser dentro do menu inicial com op��es
			PERSONAGEM jogador;
			strcpy(jogador.nome, "Daniel");
			jogador.hp = 100;
			jogador.defesa = 10;
			jogador.ataque = 5;
			jogador.dano = 3;
			jogador.posicao = 0;
		
		//grava��o inicial da p�gina 0 e p�gina 1 do livro jogo (deveria ser feito antes por outro programa)
		//antes de rodar esse programa, todas as p�ginas j� deveriam estar gravadas em historia.dat
			FILE *gravar;
			gravar=fopen("historia.dat", "wb");
			char texto[TAM_TEX_MAXIMO];
			fgets(texto, TAM_TEX_MAXIMO, stdin);
			fwrite(texto, sizeof(texto), 1, gravar);
			fgets(texto, TAM_TEX_MAXIMO, stdin);
			fwrite(texto, sizeof(texto), 1, gravar);

			fclose(gravar);


		while(parar)
			{
			imprimir_atual(jogador.posicao);
			imprimir_menu();

			scanf(" %c", &comando);
			limpar_tela();
			switch(comando)
				{
				case 'O':	olhar(jogador.posicao);
							break;
				case 'S':	imprimir_status(jogador);
							break;
				case 'M':	scanf("%d", &jogador.posicao);
							mover(jogador.posicao, &jogador);
							break;
				case 'C': 	if(combate_atual ==1)
								;
								//combate(&jogador, &inimigo);
							break;
				case 'Q': 	parar = 0;
							break;
				}
			}
		return 0;
		}
		
	void imprimir_atual(int pagina)
		{
		FILE *fp;
		char texto[TAM_TEX_MAXIMO];
		fp = fopen("historia.dat", "rb");
		fseek(fp, pagina * TAM_TEX_MAXIMO * sizeof(char), SEEK_SET);
		fread(texto, sizeof(texto), 1, fp);
		printf("%s\n", texto);
		fclose(fp);
		}
		
	void olhar(int pagina)
		{
		FILE *fp;
		char texto[TAM_TEX_MAXIMO];
		fp = fopen("olhar.dat", "rb");
		fseek(fp, pagina * TAM_TEX_MAXIMO * sizeof(char), SEEK_SET);
		fread(texto, sizeof(texto), 1, fp);
		printf("%s", texto);
		fclose(fp);
		}

	
	void imprimir_menu()	
		{
		printf("%10s %10s %10s %10s %10s\n", "[O] Olhar", "[S] Status", "[M numero] Mover", "[C] combate", "[Q] Sair");
		}
		
	void limpar_tela()
		{
		system("cls"); //no windows
		//syste("clear"); //no linux
		}
		
	int dado_aleatorio(int faces)
		{
		int resultado;
		resultado = rand() % faces + 1;
		return resultado;
		}
	
	void menu_inicial()
		{
		}
		
	int imprimir_status(PERSONAGEM jogador)
		{
		printf("Nome:%s Posicao: %d\n", jogador.nome, jogador.posicao);
		printf("HP: %d Dano: %d\n", jogador.hp, jogador.dano);
		printf("Ataque: %d Defesa: %d\n", jogador.ataque, jogador.defesa);
		}
		
	void mover(int posicao, PERSONAGEM *jogador)
		{
		jogador->posicao = posicao;
		}