#include<stdio.h>
#include<locale.h>
#include<string.h>
#include<time.h>
#include<windows.h>
#include<math.h>
#include<conio.c>

// Função responsável por navegar nas linhas e colunas da tela
void posicao(int x,int y){ 	
	COORD p={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),p);
}

// Função responsável por printar as bordas dos botões
void mostrabotao(){ 
	int i;
	for(i=0;i<17;i++){printf("-");}	
}

// Função responsável por printar os números das colunas da tabela
void mostracolunas(int tam){ 
	if(tam == 4){printf("   0   1   2   3\n");}
	if(tam == 6){printf("    0     1     2     3     4     5\n");}
	if(tam == 8){printf("    0     1     2     3     4     5     6     7\n");}
}

// Função responsável por printar o menu das dificuldades
int dificuldade(){ 
	int i,x,y,tam=0;
	
	// Enquanto a seleção do usuário for diferente das opções disponíveis, nada ocorrerá e ele será obrigado a inserir uma opção válida
	while(tam != 1 && tam != 2 && tam != 3){ 	
		system("cls");
		x = 36;
		y = 0;
		
		// Printa os botões da tela
		for(i=1;i<=3;i++){ 		
			y += 3;				
			posicao(x,y);	
			mostrabotao();		
			y++;
			posicao(x,y);
			printf("|");			
			if(i == 1){
				textcolor(10);
				printf("     Fácil     ");
			}
			else{
				if(i == 2){
					textcolor(14);
					printf("     Médio     ");
				}
				else{
					textcolor(4);
					printf("    Difícil    ");
				}
			}			
			textcolor(15);
			printf("|");
			y++;
			posicao(x,y);
			printf("|");			
			if(i == 1){
				textcolor(10);
				printf("  Pressione 1  ");
			}
			else{
				if(i == 2){
					textcolor(14);
					printf("  Pressione 2  ");
				}
				else{
					textcolor(4);
					printf("  Pressione 3  ");
				}
			}
			textcolor(15);
			printf("|");
			y++;
			posicao(x,y);
			mostrabotao();			
		}		
		printf("\n");
		scanf("%d", &tam);
		
		// De acordo com a seleção do usuário, será retornado o valor do tamanho em que a tabela será criada
		if(tam == 1){ 
			return 4;
		}
		else{
			if(tam == 2){ 
				return 6;
			}
			else{
				if(tam == 3){ 
					return 8;
				}				
			}
		}
	}
}

// Função responsável por atualizar e printar todos elementos da tabela e da tela durante o jogo
void mostratabela(char nome1[80], char nome2[80], int jogador1, int jogador2, int turno, int tam, int tabela[][tam], int espelho[][tam], int *selecao, int escolha, int acerto){ 
	int i,j,x,y;
	system("cls");
	x = 3;
	y = 0;
	posicao(x,y);
	
	// Mostra em tela os jogadores e seus respectivos pontos
	printf("%s: %d pontos", nome1, jogador1); 
	y = 2;
	posicao(x,y);
	printf("%s: %d pontos", nome2, jogador2);	
	x = 35;
	y = 6;
	posicao(x,y);
	
	// Mostra o turno de quem está jogando
	printf("Turno do jogador %d", turno);	
	y = 9;	
	if(tam == 4){			
		x = 35;}
	else{
		if(tam == 6){			
			x = 26;	
		}
		else{			
			x = 20;			
		}		
	}	
	posicao(x,y);		
	mostracolunas(tam);
	
	// Percorre as linhas da tabela
	for(i=0;i<tam;i++){ 
		y++;
		posicao(x,y);
		printf("%d ", i);
		
		// Percorre as colunas da tabela
		for(j=0;j<tam;j++){
			
			// Compara se os elementos escolhidos pelo usuário são correspondentes e se for armazena-os na tabela "espelho" auxiliar
			if((tabela[i][j] == tabela[selecao[0]][selecao[1]] || tabela[i][j] == tabela[selecao[2]][selecao[3]]) && acerto > 0){ 
				espelho[i][j]=tabela[i][j];						
				acerto--;}
				
			// Printa os elementos selecionado pelo usuário
			if((i == selecao[0] && j == selecao[1] && escolha > 0) || (i == selecao[2] && j == selecao[3] && escolha == 2)){
				if(tam == 4){																				
					printf("[%d] ", tabela[i][j]);					
				}
				else{
					if(tabela[i][j] < 10){
						printf("[ %d ] ", tabela[i][j]);
					}
					else{
						printf("[%3d] ", tabela[i][j]);						
					}								
				}
			}
			
			// Printa os elementos já acertados
			else{
				if(espelho[i][j] != 0){ 
					printf("[");
					textcolor(10);					
					if(tam==4){													
						printf("%d", espelho[i][j]);						
					}
					else{
						if(espelho[i][j] < 10){
							printf(" %d ", espelho[i][j]);							
						}
						else{
							printf("%3d", espelho[i][j]);							
						}																
					}
					textcolor(15);
					printf("] ");
				}
				
				// Printa # para os elementos não acertados e não selecionados
				else{ 
					if(tam==4){ 
						printf("[#] ");
					}
					else{
						printf("[ # ] ");
					}
				}					
			}							
		}
		printf("\n\n");		
	}			
}

// Função onde toda lógica do jogo ocorrerá
int jogo(int tam, int tabela[][tam], char nome1[80], char nome2[80]){ 
	int i, j, repetido=0, selecao[3], jogador1=0, jogador2=0, turno=1, escolha=0, acerto=0, espelho[tam][tam], x=0, y=0, retorna=0;
	char mensagens[][10] = {"primeiro", "segundo", "linha", "coluna"}, ordem[8], linha_coluna[6];
	
	// Atribui o valor 0 a todas as posições do vetor "selecao", o vetor responsável por armazenar as escolhas do usuário durante cada rodada
	for(i=0;i<4;i++){
		selecao[i] = 0;
	}
	
	// Cria a tabela "espelho" auxiliar da tabela principal atribuindo a todos os elementos o valor 0		
	for(i=0;i<tam;i++){ 	
		for(j=0;j<tam;j++){			
			espelho[i][j] = 0;												
		}
	}
	
	// Condição de parada do jogo. Enquanto os jogadores não pontuarem a quantidade máxima de elementos o jogo irá ocorrer						
	while(jogador1 + jogador2 < (pow(tam,2)/2)){													
		mostratabela(nome1, nome2, jogador1, jogador2, turno, tam, tabela, espelho, selecao, escolha, acerto); 
		
		// Variável responsável por armazenar a informação se houve acerto ou não na rodada. 
		acerto=0;
		
		// Loop que permite ao usuário realizar a seleção dos dois elementos 
		for(i=0;i<4;i++){					
			
			// Atribui as mensagens de acordo com qual elemento e qual etapa está sendo escolhida		
			if(i == 0 || i == 1){					
				strcpy(ordem, mensagens[0]);										
			}
			else{							
				strcpy(ordem, mensagens[1]);					
			}
			
			if(i == 0 || i == 2){									
				strcpy(linha_coluna, mensagens[2]);
			}					
			else{
				strcpy(linha_coluna, mensagens[3]);
			}
			
			// Caso ocorra a seleção de algum elemento repetido, será alertado em tela a escolha inválida
			if(repetido == 1){
				textcolor(4);		 
				printf("Elemento repetido\n"); 
				textcolor(15);
				repetido = 0;	
			}						
			printf("Insira a %s do %s elemento: ", linha_coluna, ordem);			
			scanf("%d",&selecao[i]);
			
			// Caso a seleção do usuário seja um numero inválido, será solicitado que insira um outro valor válido			
			while(selecao[i] > tam-1 || selecao[i] < 0){ 
				mostratabela(nome1, nome2, jogador1, jogador2, turno, tam, tabela, espelho, selecao, escolha, acerto);
				printf("Insira uma %s válida: ", linha_coluna);
				scanf("%d",&selecao[i]);		
			}
			
			// Confere se o elemento selecionado pelo usuário é repetido, caso seja, essa condição é registrada atribuindo o valor 1 a variável "repetido" e será solicitado que o usuário selecione novamente o elemento
			if(i == 1 || i == 3){			
				if(espelho[selecao[0]][selecao[1]] != 0 || (espelho[selecao[2]][selecao[3]] != 0 && escolha > 0) || (selecao[2]==selecao[0] && selecao[3]==selecao[1] && escolha > 0)){ 			
					repetido = 1;										
					if(i == 1){
						i = -1;												
					}
					else{
						i = 1;
					}
				}
				
				// Caso o elemento não seja repetido, é registrado que uma escolha foi realizada
				else{
					escolha++;
				}							
			}			
			mostratabela(nome1, nome2, jogador1, jogador2, turno, tam, tabela, espelho, selecao, escolha, acerto);			
		}
		
		// Escolha se torna 0 para armazenar o momento que os dois elementos já foram escolhidos		
		escolha = 0;		
		Sleep(1500);
		
		// Caso os elementos escolhidos pelo usuário correspondam, ele acertou e irá receber 1 ponto.
		// A variável turno define quem está jogando e quem ganhará o ponto. Caso ela seja 1, o turno é do jogador 1, caso 2, turno do jogador 2		   			
		if(tabela[selecao[0]][selecao[1]] == tabela[selecao[2]][selecao[3]]){ 		
			if(turno == 1){
				jogador1++;				
			}
			else{
				jogador2++;
			}			
			acerto += 2;		
		}
		
		// No caso do jogador errar, a sua vez é passada		
		else{ 
			if(turno == 1){ 
				turno++;
			}
			else{ 
				turno--;
			}
		}						
	}
	
	// Após finalização do jogo será solicitado ao usuário se deseja jogar novamente ou sair
	// Enquanto a opção inserida pelo usuário for inválida, nada ocorrerá e ele será obrigado a inserir uma opção válida
	while(retorna != 1 && retorna != 2){ 
	system("cls");
	
	// Printa qual jogador venceu a partida de acordo com sua pontuação ou se houve empate
	if(jogador1 > jogador2){ 
		x = 29;
		y = 3;
		posicao(x,y);
		printf("Jogador 1 venceu com %d pontos!", jogador1);
	}
	else{
		if(jogador2 > jogador1){ 
		x = 29;
		y = 3;
		posicao(x,y);		
		printf("Jogador 2 venceu com %d pontos!", jogador2);
	}	
		else{ 
		x = 41;
		y = 3;
		posicao(x,y);
		printf("Empate");
		}
	}
	x = 36;
	
	// Printa os botões da tela de finalização do jogo	
	for(i=1;i<=2;i++){ 		
		y += 3;				
		posicao(x,y);	
		mostrabotao();		
		y++;
		posicao(x,y);					
		if(i == 1){
			printf("|Jogar novamente|");
		}
		else{
			printf("|     Sair      |");
		}			
		textcolor(15);		
		y++;
		posicao(x,y);					
		if(i == 1){
			printf("|  Pressione 1  |");
		}
		else{
			printf("|  Pressione 2  |");
		}
		textcolor(15);		
		y++;
		posicao(x,y);
		mostrabotao();			
	}	
	printf("\n");
	scanf("%d", &retorna);
	}
	
	// Retorna a opção do usuário de continuar jogando ou não para a função "tabela"
	return retorna; 
}

// Função responsável por realizar a criação da tabela principal do jogo
int tabela(int tam){ 
	int linha, coluna, tabela[tam][tam], aux, i, j, cont=1, x, y, escolha;	
	char nome1[80], nome2[80], lixo[2];	
	system("cls");
	
	// Atribui os valores dos elementos da tabela em ordem crescente 		
	for(i=0;i<tam;i++){
		if(i > 0){
			cont++;			
		}
		for(j=0;j<tam;j++){
			if(j % 2 == 0 && j != 0){
				cont++;
			}
			tabela[i][j]=cont;						
		}
	}
	
	gets(lixo);	
	y = 9;	
	x = 9;
	posicao(x,y);
	
	// Solicita o nome dos jogadores para ser mostrado em tela no momento do jogo com suas respectivas pontuações					
	printf("Insira o nome do primeiro jogador: "); 
	gets(nome1);
	system("cls");
	y = 9;	
	x = 9;
	posicao(x,y);
	printf("Insira o nome do segundo jogador: ");
	gets(nome2);
	system("cls");
	
	// Randomiza os elementos da tabela 		
	srand(time(NULL));		
	for(i=0;i<tam;i++){ 		
		for(j=0;j<tam;j++){						
			linha = rand() % tam;			
			coluna = rand() % tam;			
			aux = tabela[i][j];
			tabela[i][j] = tabela[linha][coluna];
			tabela[linha][coluna] = aux;						
		}		
	}
	
		
	if(tam == 4){
		x = 35;
	}
	else{
		if(tam == 6){
			x = 26;
		}
		else{
			x = 20;
		}		
	}	
	posicao(x,y);	
	mostracolunas(tam);
	
	// Printa inicialmente em tela a tabela para o usuário memorizar 	
	for(i=0;i<tam;i++){ 
		y++;		
		posicao(x,y);
		printf("%d ", i);
		for(j=0;j<tam;j++){
			if(tam == 4){			
				printf("[%d] ", tabela[i][j]);
			}
			else{
				printf("[%3d] ", tabela[i][j]);				
			}
		}
		printf("\n");		
	}	
	Sleep(3000);
	
	// Chama a função onde a lógica do jogo será executada e retorna dessa função a escolha do jogador se desja ou não continuar jogando quando a partida finalizar	
	return jogo(tam, tabela, nome1, nome2); 		
}

// Função onde está o menu do jogo
int main(){ 	
	setlocale(LC_ALL,"Portuguese");
	int i, x, y, tam=4, selecione, parada=1;
	
	// Enquanto a variável parada for igual a 1 o jogo não terminará 		
	while(parada == 1){ 
		x = 37;
		y = 3;
		system("cls");
		posicao(x,y);
		textcolor(9);				
		printf("JOGO DA MEMÓRIA");
		textcolor(15);
		x = 36;
		
		// Printa os botões da tela
		for(i=1;i<=3;i++){ 		
			y += 3;				
			posicao(x,y);	
			mostrabotao();		
			y++;
			posicao(x,y);											
			if(i == 1){
				printf("|     Jogar     |");
			}
			else{												
				if(i == 2){
					printf("|  Dificuldade  |");
				}
				else{
					printf("|     Sair      |");
				}
			}							
			y++;
			posicao(x,y);								
			if(i == 1){
				printf("|  Pressione 1  |");
			}
			else{
				if(i == 2){
					printf("|  Pressione 2  |");
				}
				else{
					printf("|  Pressione 3  |");
				}
			}					
			y++;
			posicao(x,y);
			mostrabotao();			
		}			
		printf("\n");		
		scanf("%d",&selecione);
		
		// Será armazenada a seleção do usuário e de acordo com sua escolha ele será encaminhado para alguma das telas
		
		// Jogar
		if(selecione == 1){ 		
			parada = tabela(tam); 				
		}
		else{
			// Dificuldade
			if(selecione == 2){ 
				tam = dificuldade();				
			}
			else{
				// Sair
				if(selecione == 3){ 
					parada--;
				}
			}			
		}				
	}
	
	// Printa a tela de finalização no encerramento do jogo
	system("cls");
	y = 9;
	x = 36;
	posicao(x,y);
	textcolor(12);
	printf("Finalizando....");
	textcolor(3);
	Sleep(1500);
	y = 11;
	x = 37;
	posicao(x,y);
	printf("Volte Sempre!\n\n");
	textcolor(15);
	return 0;	
}
