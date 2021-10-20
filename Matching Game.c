#include<stdio.h>
#include<locale.h>
#include<time.h>
#include<windows.h>
#include<math.h>
#include<conio.c>
void posicao(int x,int y){ //FUNÇÃO RESPONSÁVEL POR NAVEGAR NAS LINHAS E COLUNAS DA TELA	
	COORD p={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),p);
}
void mostrabotao(){ //FUNÇÃO RESPONSÁVEL POR MOSTRAR AS BORDAS DOS BOTÕES
	int i;
	for(i=0;i<17;i++){printf("-");}	
}
void mostracolunas(int tam){ //FUNÇÃO RESPONSÁVEL POR MOSTRAR O NÚMERO DAS COLUNAS DAS TABELAS
	if(tam==4){printf("   0   1   2   3\n");}
	if(tam==6){printf("    0     1     2     3     4     5\n");}
	if(tam==8){printf("    0     1     2     3     4     5     6     7\n");}
}
int dificuldade(){ //FUNÇÃO RESPONSÁVEL POR MOSTRAR O MENU DAS DIFICULDADES
	int i,x,y,tam=0;
	while(tam != 1 && tam != 2 && tam != 3){ //ENQUANTO A ESCOLHA DO USUÁRIO FOR DIFERENTE DAS OPÇÕES DISPONÍVEIS NADA OCORRERÁ E ELE SERÁ OBRIGADO A INSERIR UMA OPÇÃO VÁLIDA	
		system("cls");
		x=36;
		y=0;
		for(i=1;i<=3;i++){ //PRINTA OS BOTÕES DA TELA		
			y+=3;				
			posicao(x,y);	
			mostrabotao();		
			y++;
			posicao(x,y);
			printf("|");			
			if(i==1){
				textcolor(10);
				printf("     Fácil     ");
			}
			else{
				if(i==2){
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
			if(i==1){
				textcolor(10);
				printf("  Pressione 1  ");
			}
			else{
				if(i==2){
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
		scanf("%d",&tam);
		if(tam == 1){ //CASO O USUÁRIO ESCOLHA A OPÇÃO 1 "FÁCIL" SERÁ RETORNADO O TAMANHO 4
			return 4;
		}
		else{
			if(tam == 2){ //CASO O USUÁRIO ESCOLHA A OPÇÃO 2 "MÉDIO" SERÁ RETORNADO O TAMANHO 6
				return 6;
			}
			else{
				if(tam == 3){ //CASO O USUÁRIO ESCOLHA A OPÇÃO 3 "DIFÍCIL" SERÁ RETORNADO O TAMANHO 8
					return 8;
				}				
			}
		}
	}
}
void mostratabela(char nome1[80], char nome2[80], int j1, int j2, int auxj, int tam, int tabela[][tam], int espelho[][tam], int l1, int c1, int l2, int c2, int auxtabela, int auxcerto){ //FUNÇÃO RESPONSÁVEL POR ATUALIZAR E PRINTAR TODOS ELEMENTOS DA TABELA E DA TELA DURANTE O JOGO
	int i,j,x,y;
	system("cls");
	x=3;
	y=0;
	posicao(x,y);
	printf("%s: %d pontos", nome1, j1); //MOSTRA EM TELA OS JOGADORES E SEUS RESPECTIVOS PONTOS
	y=2;
	posicao(x,y);
	printf("%s: %d pontos", nome2, j2);
	x=35;
	y=6;
	posicao(x,y);
	printf("Turno do jogador %d",auxj);	//MOSTRA QUEM DEVE JOGAR
	y=9;	
	if(tam==4){			
		x=35;}
	else{
		if(tam==6){			
			x=26;	
		}
		else{			
			x=20;			
		}		
	}	
	posicao(x,y);		
	mostracolunas(tam);
	for(i=0;i<tam;i++){ //PERCORRE AS LINHAS DA TABELA
		y++;
		posicao(x,y);
		printf("%d ",i);
		for(j=0;j<tam;j++){ //PERCORRE AS COLUNAS DA TABELA
			if((tabela[i][j] == tabela[l1][c1] || tabela[i][j] == tabela[l2][c2]) && auxcerto>0){ //CASO OS ELEMENTOS ESCOLHIDOS PELO USUÁRIO FOREM OS CERTOS, ARMAZENA ELES NA TABELA "ESPELHO" AUXILIAR 
				espelho[i][j]=tabela[i][j];						
				auxcerto--;}
			if((i==l1 && j==c1 && auxtabela>0) || (i==l2 && j==c2 && auxtabela==2)){ //REVELA O ELEMENTO ESCOLHIDO PELO USUÁRIO
				if(tam==4){																				
					printf("[%d] ",tabela[i][j]);					
				}
				else{
				printf("[%3d] ",tabela[i][j]);				
				}
			}
			else{
				if(espelho[i][j] != 0){ //REVELA OS ELEMENTOS JÁ ACERTADOS
					if(tam==4){
						printf("[");
						textcolor(10);							
						printf("%d",espelho[i][j]);
						textcolor(15);
						printf("] ");
					}
					else{
						printf("[");
						textcolor(10);
						printf("%3d",espelho[i][j]);
						textcolor(15);
						printf("] ");				
					}
				}
				else{ //MOSTRA # PARA OS ELEMENTOS NÃO ACERTADOS E NÃO ESCOLHIDOS
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
int jogo(int tam, int tabela[][tam], char nome1[80], char nome2[80]){ // FUNÇÃO EM QUE O JOGO IRÁ ACONTECER
	int i, j, selecao[3], j1=0, j2=0, auxj=1, escolha=1, auxtabela=0, auxcerto=0, espelho[tam][tam], x=0, y=0, retorna=0;
	char ordem, linha_coluna;		
	for(i=0;i<tam;i++){ //CRIA A TABELA "ESPELHO" AUXILIAR DA TABELA PRINCIPAL COM TODOS OS ELEMENTOS IGUAL A 0		
		for(j=0;j<tam;j++){			
			espelho[i][j]=0;												
		}
	}						
	while(j1+j2<(pow(tam,2)/2)){	//ENQUANTO OS JOGADORES NÃO PONTUAREM A QUANTIDADE MÁXIMA DE ELEMENTOS O JOGO CONTINUA											
		mostratabela(nome1, nome2, j1, j2, auxj, tam, tabela, espelho, l1, c1, l2, c2, auxtabela, auxcerto); //CHAMA A FUNÇÃO RESPONSÁVEL POR ATUALIZAR E PRINTAR TODOS ELEMENTOS DA TABELA E DA TELA DURANTE O JOGO 
		auxcerto=0; //ZERAR O VALOR DE AUXCERTO, POIS ELA SÓ SUBTRAI NA FUNÇÃO MOSTRATABELA, NESSA FUNÇÃO ELA PERMANECE COMO 2
		for(i=0;i<4;i++){						
			while(escolha==1){ //ENQUANTO A VARIÁVEL ESCOLHA FOR IGUAL A 1, SERÁ SOLICITADO AO USUÁRIO PARA INSERIR A LINHA E COLUNA DO PRIMEIRO ELEMENTO		
				if(i == 0 || i == 1){
					ordem = "primeiro";				
					linha_coluna = "linha";
					if(i == 1){
						linha_coluna = "coluna";
					}
				}
				else{							
					ordem = "segundo";
					linha_coluna = "linha";
					if(i == 3){
						linha_coluna = "coluna";
					}
				}		
				printf("Insira a %s do %s elemento: ", linha_coluna, ordem);
				scanf("%d",&selecao[i]);			
			while(selecao[i] > tam-1 || selecao[i] < 0){ //CASO O VALOR DA LINHA DO PRIMEIRO ELEMENTO ULTRAPASSE O LIMITE DE TAMANHO DA TABELA OU SEJA MENOR QUE ZERO, SERÁ SOLICITADO AO USUÁRIO QUE INSIRA UM VALOR VÁLIDO
				mostratabela(nome1, nome2, j1, j2, auxj, tam, tabela, espelho, l1, c1, l2, c2, auxtabela, auxcerto);
				printf("Insira uma linha válida: ");
				scanf("%d",&selecao[i]);		
			}
			//mostratabela(nome1, nome2, j1, j2, auxj, tam, tabela, espelho, l1, c1, l2, c2, auxtabela, auxcerto);
			//printf("Insira a %s do %s elemento: ", linha_coluna, ordem);
			//scanf("%d",&selecao[i]);		
			//while(c1 > tam-1 || c1 < 0){ //CASO O VALOR DA COLUNA DO PRIMEIRO ELEMENTO ULTRAPASSE O LIMITE DE TAMANHO DA TABELA OU SEJA MENOR QUE ZERO, SERÁ SOLICITADO AO USUÁRIO QUE INSIRA UM VALOR VÁLIDO
			//	mostratabela(nome1, nome2, j1, j2, auxj, tam, tabela, espelho, l1, c1, l2, c2, auxtabela, auxcerto);
		//		printf("Insira uma coluna válida: ");
			//	scanf("%d",&c1);		
			//}
			if(espelho[selecao[0]][selecao[1]] != 0 || espelho[selecao[2]][selecao[3]] != 0 || (selecao[2]==selecao[0] && selecao[3]==selecao[1])){ //SE O ELEMENTO QUE O USUÁRIO ESCOLHER JÁ ESTIVER REVELADO SERÁ INFORMADO QUE O ELEMENTO É REPETIDO E ELE TERÁ QUE SELECIONAR OUTRO ELEMENTO			
				mostratabela(nome1, nome2, j1, j2, auxj, tam, tabela, espelho, l1, c1, l2, c2, auxtabela, auxcerto);
				textcolor(4);		 
				printf("Elemento repetido\n"); //MOSTRA MENSAGEM DIZENDO QUE O ELEMENTO ESCOLHIDO FOI REPETIDO
				textcolor(15);
			}
			else{ //CASO O USUÁRIO ESCOLHER UM ELEMENTO QUE NÃO SEJA REPETIDO, A VARIÁVEL ESCOLHA SE TORNA 0 E SAI DO LOOP			
				escolha--;
			}		
			}
		}
		escolha++; //ESCOLHA SE TORNA 1 NOVAMENTE PARA A ESCOLHA DO SEGUNDO ELEMENTO				
		auxtabela++; //SOMA UM NA VARIÁVEL AUXTABELA PARA ARMAZENAR O MOMENTO QUE O PRIMEIRO ELEMENTO JÁ FOI ESCOLHIDO
		mostratabela(nome1, nome2, j1, j2, auxj, tam, tabela, espelho, l1, c1, l2, c2, auxtabela, auxcerto);
		while(escolha==1){ //ENQUANTO A VARIÁVEL ESCOLHA FOR 1, SERÁ SOLICITADO AO USUÁRIO PARA INSERIR UMA LINHA E COLUNA DO SEGUNDO ELEMENTO						
		printf("Insira a linha do segundo elemento: ");
		scanf("%d",&l2);
		while(l2 > tam-1 || l2 < 0){ //CASO O VALOR DA LINHA DO SEGUNDO ELEMENTO ULTRAPASSE O LIMITE DE TAMANHO DA TABELA OU SEJA MENOR QUE ZERO, SERÁ SOLICITADO AO USUÁRIO QUE INSIRA UM VALOR VÁLIDO
			mostratabela(nome1, nome2, j1, j2, auxj, tam, tabela, espelho, l1, c1, l2, c2, auxtabela, auxcerto);
			printf("Insira uma linha válida: ");
			scanf("%d",&l2);		
		}
		mostratabela(nome1, nome2, j1, j2, auxj, tam, tabela, espelho, l1, c1, l2, c2, auxtabela, auxcerto);
		printf("Insira a coluna do segundo elemento: ");
		scanf("%d",&c2);
		while(c2 > tam-1 || c2 < 0){ //CASO O VALOR DA COLUNA DO SEGUNDO ELEMENTO ULTRAPASSE O LIMITE DE TAMANHO DA TABELA OU SEJA MENOR QUE ZERO, SERÁ SOLICITADO AO USUÁRIO QUE INSIRA UM VALOR VÁLIDO
			mostratabela(nome1, nome2, j1, j2, auxj, tam, tabela, espelho, l1, c1, l2, c2, auxtabela, auxcerto);
			printf("Insira uma coluna válida: ");
			scanf("%d",&c2);		
		}
		if((espelho[l2][c2] != 0) || l2==l1 && c2==c1){ //SE O ELEMENTO QUE O USUÁRIO ESCOLHER JÁ ESTIVER REVELADO OU FOR IGUAL AO PRIMEIRO ELEMENTO ESCOLHIDO, SERÁ INFORMADO QUE O ELEMENTO É REPETIDO E ELE TERÁ QUE SELECIONAR OUTRO ELEMENTO			
			mostratabela(nome1, nome2, j1, j2, auxj, tam, tabela, espelho, l1, c1, l2, c2, auxtabela, auxcerto);
			textcolor(4);			 
			printf("Elemento repetido\n"); 
			textcolor(15);
		}
		else{ //CASO O USUÁRIO ESCOLHER UM ELEMENTO QUE NÃO SEJA REPETIDO, A VARIÁVEL ESCOLHA SE TORNA 0 E SAI DO LOOP			
			escolha--;
		}
		}
		escolha++; //VARIÁVEL ESCOLHA SE TORNA 1 NOVAMENTE PARA QUANDO O LOOP SE REPETIR		
		auxtabela++; //SOMA MAIS UM NA VARIÁVEL AUXTABELA PARA ARMAZENAR O MOMENTO QUE O SEGUNDO ELEMENTO FOI ESCOLHIDO
		mostratabela(nome1, nome2, j1, j2, auxj, tam, tabela, espelho, l1, c1, l2, c2, auxtabela, auxcerto); 
		auxtabela=0; //AUXTABELA VOLTA A 0 PARA ARMAZENAR O MOMENTO QUE OS DOIS ELEMENTOS JÁ FORAM ESCOLHIDOS E ASSIM RESETAR O LOOP		
		Sleep(1500); //TEMPO DE 1 SEGUNDO E MEIO PARA A VISUALIZAÇÃO E MEMORIZAÇÃO DOS ELEMENTOS ESCOLHIDOS			
		if((tabela[l1][c1] == tabela[l2][c2]) && auxj == 1){ //CASO OS ELEMENTOS ESCOLHIDOS FOREM IGUAIS O USUÁRIO ACERTOU. VARIÁVEL AUXJ INDICA QUEM ESTÁ JOGANDO, CASO FOR 1 O JOGADOR 1 RECEBE PONTO.		
			j1++;
			auxcerto+=2;		
		}
		else{			
		if((tabela[l1][c1] == tabela[l2][c2]) && auxj == 2){ //CASO AUXJ FOR 2, JOGADOR 2 ESTÁ JOGANDO E RECEBE PONTO
			j2++;
			auxcerto+=2;		
		}
		else{ //CASO ERRAREM PASSA A VEZ
			if(auxj == 1){ //SE ESTIVER NA VEZ DO JOGADOR 1 PASSA PARA O JOGADOR 2
				auxj++;
			}
			else{ //SE ESTIVER NA VEZ DO JOGADOR 2 PASSA PARA O JOGADOR 1
				auxj--;
			}
		}
	}					
	}
	while(retorna != 1 && retorna != 2){ //ENQUANTO A OPÇÃO INSERIDA PELO USUÁRIO FOR DIFERENTE DAS OPÇÕES DISPONÍVEIS NÃO ACONTECERÁ NADA E O USUÁRIO SERÁ OBRIGADO A INSERIR UMA DAS OPÇÕES MOSTRADAS
	system("cls");
	if(j1 > j2){ //SE A PONTUAÇÃO DO JOGADOR 1 FOR MAIOR QUE A DO JOGADOR 2, É MOSTRADO NO FINAL DO JOGO QUE ELE VENCEU E A QUANTIDADE DE PONTOS
		x=29;
		y=3;
		posicao(x,y);
		printf("Jogador 1 venceu com %d pontos!",j1);
	}
	else{
		if(j2 > j1){ //SE A PONTUAÇÃO DO JOGADOR 2 FOR MAIOR QUE A DO JOGADOR 1, É MOSTRADO NO FINAL DO JOGO QUE ELE VENCEU E A QUANTIDADE DE PONTOS
		x=29;
		y=3;
		posicao(x,y);		
		printf("Jogador 2 venceu com %d pontos!",j2);
	}
		else{ //CASO A PONTUAÇÃO DOS DOIS JOGADORES AO FINAL DO JOGO FOREM IGUAIS, É MOSTRADO NA TELA QUE OCORREU UM EMPATE
		x=41;
		y=3;
		posicao(x,y);
		printf("Empate");
		}
	}
	x=36;	
	for(i=1;i<=2;i++){ //PRINTA OS BOTÕES DA TELA		
		y+=3;				
		posicao(x,y);	
		mostrabotao();		
		y++;
		posicao(x,y);					
		if(i==1){printf("|Jogar novamente|");}
		else{printf("|     Sair      |");}			
		textcolor(15);		
		y++;
		posicao(x,y);					
		if(i==1){printf("|  Pressione 1  |");}
		else{printf("|  Pressione 2  |");}
		textcolor(15);		
		y++;
		posicao(x,y);
		mostrabotao();			
	}	
	printf("\n");
	scanf("%d", &retorna);
	}
	return retorna; //RETORNA A OPÇÃO DE CONTINUAR JOGANDO OU NÃO PARA A FUNÇÃO "TABELA" 
}
int tabela(int tam){ //CRIAÇÃO DA TABELA PRINCIPAL
	int linha, coluna, tabela[tam][tam], aux, i, j, cont=1, x, y, escolha;	
	char nome1[80], nome2[80], lixo[2];	
	system("cls");		
	for(i=0;i<tam;i++){ // CRIA A TABELA EM ORDEM CRESCENTE 
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
	y=9;	
	x=9;
	posicao(x,y);					
	printf("Insira o nome do primeiro jogador: "); //SOLICITA O NOME DOS JOGADORES PARA SER MOSTRADO EM TELA NO MOMENTO DO JOGO COM SUAS RESPECTIVAS PONTUAÇÕES
	gets(nome1);
	system("cls");
	y=9;	
	x=9;
	posicao(x,y);
	printf("Insira o nome do segundo jogador: ");
	gets(nome2);
	system("cls");		
	srand(time(NULL));		
	for(i=0;i<tam;i++){ //RANDOMIZA OS ELEMENTOS DA TABELA		
		for(j=0;j<tam;j++){						
			linha = rand() % tam;			
			coluna = rand() % tam;			
			aux = tabela[i][j];
			tabela[i][j] = tabela[linha][coluna];
			tabela[linha][coluna] = aux;						
		}		
	}	
	if(tam==4){x=35;}
	else{
		if(tam==6){x=26;}
		else{x=20;}		
	}	
	posicao(x,y);	
	mostracolunas(tam);	
	for(i=0;i<tam;i++){ //PRINTA EM TELA A TABELA PARA O USUÁRIO MEMORIZAR
		y++;		
		posicao(x,y);
		printf("%d ",i);
		for(j=0;j<tam;j++){
			if(tam == 4){			
				printf("[%d] ",tabela[i][j]);
			}
			else{
				printf("[%3d] ",tabela[i][j]);				
			}
		}
		printf("\n");		
	}	
	Sleep(3000);	
	return jogo(tam, tabela, nome1, nome2); //CHAMA A FUNÇÃO ONDE O JOGO IRÁ ACONTECER E RETORNA DESSA FUNÇÃO A ESCOLHA DO JOGADOR SE DESEJA OU NÃO CONTINUAR JOGANDO QUANDO A PARTIDA FINALIZAR		
}
int main(){ //MENU	
	setlocale(LC_ALL,"Portuguese");
	int i, x, y, tam=4, selecione, escolha=1;		
	while(escolha == 1){ //ENQUANTO A VARIÁVEL ESCOLHA FOR IGUAL A 1 O JOGO NÃO TERMINARÁ
		x=37;
		y=3;
		system("cls");
		posicao(x,y);
		textcolor(9);				
		printf("JOGO DA MEMÓRIA");
		textcolor(15);
		x=36;
		for(i=1;i<=3;i++){ //PRINTA OS BOTÕES DA TELA		
			y+=3;				
			posicao(x,y);	
			mostrabotao();		
			y++;
			posicao(x,y);											
			if(i==1){printf("|     Jogar     |");}
			else{												
				if(i==2){printf("|  Dificuldade  |");}
				else{printf("|     Sair      |");}
			}							
			y++;
			posicao(x,y);								
			if(i==1){printf("|  Pressione 1  |");}
			else{
				if(i==2){printf("|  Pressione 2  |");}
				else{printf("|  Pressione 3  |");}
			}					
			y++;
			posicao(x,y);
			mostrabotao();			
		}			
		printf("\n");		
		scanf("%d",&selecione);
		if(selecione == 1){ //CASO O USUÁRIO SELECIONAR A OPÇÃO 1 O JOGO INICIA			
			escolha = tabela(tam); //CHAMA A FUNÇÃO RESPONSÁVEL PELA CRIAÇÃO DA TABELA/MATRIZ PRINCIPAL E RECEBE AO FINAL A ESCOLHA DO JOGADOR SE DESEJA OU NÃO CONTINUAR JOGANDO				
		}
		else{
			if(selecione == 2){ //CASO O USUÁRIO SELECIONAR A OPÇÃO 2 SERÁ MOSTRADO O MENU DAS DIFICULDADES
				tam=dificuldade(); //CHAMA A FUNÇÃO DO MENU DAS DIFICULDADES E RECEBE A DIFICULDADE ESCOLHIDA PELO USUÁRIO				
			}
			else{
				if(selecione == 3){ //CASO O USUÁRIO SELECIONAR A OPÇÃO 3 O JOGO SERÁ ENCERRADO
					escolha--;
				}
			}			
		}				
	}
	system("cls");
	y=9;
	x=36;
	posicao(x,y);
	textcolor(12);
	printf("Finalizando....");
	textcolor(3);
	Sleep(1500);
	y=11;
	x=37;
	posicao(x,y);
	printf("Volte Sempre!\n\n");
	textcolor(15);
	return 0;	
}
