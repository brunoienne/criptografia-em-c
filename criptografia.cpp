#include <stdio.h>
#include<stdlib.h>
#include<string.h>

//Configuracao da chave
char CHAVE[]="AzBy";
int TAM_CHAVE=strlen(CHAVE);
//---------------------------

//Vetor de entrada de texto
char TEXTO[129];  //por se tratar de uma string deverá ter tamanho de 129 pois o ultimo espaço será '\0'
int TAM_TEXTO=129;
//---------------------------

int TEXTO_CRIPT[129];

//Função Criptografar
bool criptografar(){
	int CHAVE_int;
	for(int i=0; i<strlen(TEXTO); i++){
		TEXTO_CRIPT[i]=TEXTO[i];
	}
	
	
 for(int aux=0; aux< strlen(TEXTO);){
	for(int i=0; i<TAM_CHAVE; i++){
		CHAVE_int=CHAVE[i];
		TEXTO_CRIPT[aux]*=CHAVE_int;	//TEXTO_CRIPT[aux]=TEXTO_CRIPT[aux]*CHAVE_int
		aux++;
	}
}
	return true;
}
//Função Descriptografar
bool descriptografar(){
	FILE *arquivo;
	
	int valor;
	int pos_chave;
	int pos_texto;
	
	arquivo = fopen("c:\\cript\\arquivos_gerados\\criptografado.txt","r");
	
	if (arquivo==NULL){
		return false;
	}
	
	pos_chave=0;
	pos_texto=0;
	while(!feof(arquivo)){       //enquanto o arquivo não terminar de ser lido
		fscanf(arquivo,"%d",&valor); //lendo o valor inteiro criptografado
		
		valor/=CHAVE[pos_chave]; //descriptografando através da divisão pela chave
		
		TEXTO[pos_texto]=(char)valor;
		pos_texto++;
		
		if(pos_chave==TAM_CHAVE-1){
			pos_chave=0;          //voltando para posicao inicial da chave
		}else{
			pos_chave++;          //percorrendo a chave
		}
	}
	fclose(arquivo);
	return true;
}
//Menus-----------------------------------------------------------------------------------------------
void recebe_texto(char tipo[]){
	char aux[TAM_TEXTO];
	char pause;
	bool ok;
	
	FILE *arquivo; 
	char palavra[128];
		if(strcmp(tipo,"msg")==0){
			printf("\n\nReceber texto para criptograr\n\n");
			printf("Digite sua mensagem: ");
			gets(aux);
			fflush(stdin);
		
			if(strlen(aux)<=TAM_TEXTO){
				strcpy(TEXTO,aux);
				printf("\n\nMensagem recebida com sucesso!\n\n");
				printf("\n\nCriptografando texto...\n\n");
			ok=true;
			}else{
			printf("\n\nErro!\nTamanho da mensagem excede o limite de caracteres");
			ok=false;
			system("pause");
			}
		
		
		}else if(strcmp(tipo,"arquivo")==0){
			printf("\n\n Instrucoes para importar um arquivo de texto:");
			printf("\n\n 1 - Renomeie o arquivo para 'original.txt'");
			printf("\n\n 2 - Copie o arquivo para a pasta que sera aberta a seguir");
			printf("\n\n 3 - Feche o explorador e retorne a aplicacao");
		
			printf("\n\n\n Pressione Enter para abrir a pasta...\n");
			scanf("%c",&pause);
			fflush(stdin);
		
			system ("explorer c:\\cript\\arquivos_gerados\\");
		
			printf("\n\n\n Pressione Enter apos colar o arquivo na pasta...\n");
			scanf("%c",&pause);
			fflush(stdin);
			
			printf("\n\nImportando arquivo...\n\n");
		
			arquivo = fopen("c:\\cript\\arquivos_gerados\\original.txt","r"); //abrindo um arquivo para ser lido e depois ser criptografado
			
			if(arquivo==NULL){
				printf("\n\nErro ao abrir o arquivo!\n\n");
			}else{
			while(!feof(arquivo)){
				fscanf(arquivo,"%s",palavra);
				strcat(aux," ");
				strcat(aux,palavra);
			}
			fclose(arquivo);
			if(strlen(aux)<=TAM_TEXTO){	
				strcpy(TEXTO,aux);
				printf("\n\nMensagem recebida com sucesso!\n\n");
				printf("\n\nCriptografando texto...\n\n");
			ok=true;
			}else{
				printf("\n\nErro!\nTamanho da mensagem excede o limite de caracteres");
				ok=false;
				system("pause");
			}	
		}	
		
		}else{
			printf("\n\nErro ao receber arquivo!\n\n");
		}
	
	if(ok){
		if(criptografar()){
			printf("\n\nTexto criptografado com sucesso!");
			
			arquivo =  fopen("c:\\cript\\arquivos_gerados\\criptografado.txt","wt"); //criando um arquivo
			if(arquivo==NULL){
				printf("\n\nErro ao criar o arquivo...\n\n");	
			}else{
				for(int i=0 ; i<strlen(TEXTO);i++){
					fprintf(arquivo,"%d ",TEXTO_CRIPT[i]);
					
				}
				fclose(arquivo);
			}
			printf("\n\nPressione enter para abrir a pasta do arquivo gerado");
			scanf("%c",&pause);
			fflush(stdin);
			system("explorer c:\\cript\\arquivos_gerados\\");
		}else{
		 	printf("\n\nNao foi possivel criptografar o texto!\n\n ");
		}
	 }
		
		
	}
	
//Função receber arquivo
void receber_arq(){
	char pause;
	printf("\n\n Instrucoes para importar um arquivo criptografado:");
			printf("\n\n 1 - Renomeie o arquivo para 'criptografado.txt'");
			printf("\n\n 2 - Copie o arquivo para a pasta que sera aberta a seguir");
			printf("\n\n 3 - Feche o explorador e retorne a aplicacao");
		
			printf("\n\n\n Pressione Enter para abrir a pasta...\n");
			scanf("%c",&pause);
			fflush(stdin);
		
			system ("explorer c:\\cript\\arquivos_gerados\\");
		
			printf("\n\n\n Pressione Enter apos colar o arquivo na pasta...\n");
			scanf("%c",&pause);
			fflush(stdin);
			
			printf("\n\nImportando arquivo...\n\n");
		
			if(descriptografar() ){
				printf("\nArquivo descriptografado com sucesso!");
				system("pause");
				system("cls");
				printf("\n%s\n\n",TEXTO);
				system("pause");
			}else{
				printf("\nNao foi possivel descriptografar o arquivo!\n");
				system("pause");
				
			}
	
}
//Menu de criptografar
void menu_criptografar(){
	int opcao;
		printf("\n\tCriptografia de dados");
		printf("\n\n\ Criptografar mensagem ou arquivo");
		printf("\n\n\n 1 - Digitar mensagem");
		printf("\n\n 2 - Importar aquivo de texto (txt)");
		printf("\n\n 3 - Voltar ao menu");
		printf("\n\n Informe a opcao desejada: ");
		scanf("%d",&opcao);
		fflush(stdin);
	switch(opcao){
		case 1:
			system("cls");
			recebe_texto("msg");
			break;
		case 2:
			system("cls");
			recebe_texto("arquivo");
			break;
		case 3:
			break;
		default:
			printf("Opcao invalida!Digite novamente...");	
	}
	
}

//Menu Principal
void menu(){
	int opcao;
	while(1){
		system("cls");
		printf("\n\tCriptografia de dados");
		printf("\n\n 1 - Criptografar mensagem");
		printf("\n\n 2 - Receber arquivo criptografado");
		printf("\n\n 3 - Sair");
		printf("\n\n Informe a opcao desejada: ");
		scanf("%d",&opcao);
		fflush(stdin);
	switch(opcao){
			case 1:
				system("cls");
				menu_criptografar();
			break;
			case 2:
				system("cls");
				receber_arq();
				break;
			case 3:
				printf("\nFinalizando...\n");
				fflush(stdin);getchar();
				exit(0);
				break;
			default:
				printf("\n\nOpcao invalida! Tente novamente...\n\n");
				system("pause");
		}
	}
}
//-----------------------------------------------------------------------------------------------
main(){
	menu();
}
