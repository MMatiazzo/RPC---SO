#include <stdio.h>
#include <string.h>
#include "agenda.h"



/* implementa��o da funçao add */
int * insert_1_svc (params *argp, struct svc_req *rqstp)
{  
	int i, j, k;
	static int result;
	FILE *fp = fopen("agenda.bin", "ab");

	fwrite(argp->nome, 30, 1, fp);
	fwrite(argp->telefone, 30, 1, fp);
	result = !!fwrite(argp->endereco, 30, 1, fp);

	printf ("Usuario castrado:\n -%s\n -%s\n -%s\n\n", argp->nome, argp->telefone, argp->endereco);
	fclose(fp);
	return (&result);
}

/* implementaçao da funçao search */
char ** search_1_svc (params *argp, struct svc_req *rqstp)
{
	static char* res;

	char aux_nome[30],
		aux_tel[30],
		aux_ende[30];


	aux_nome[0] = aux_tel[0] = aux_ende[0] = '\0';
    FILE *fp = fopen("agenda.bin", "rb");


    while(0 < fread(aux_nome, 30, 1, fp)){
		if(!strcmp(aux_nome, argp->nome)){
			fread(aux_tel, 30, 1, fp);
			fread(aux_ende, 30, 1, fp);
			res = malloc(sizeof(char)*150);
			sprintf(res, " nome:%s\n telefone:%s\n endereco:%s\n", aux_nome, aux_tel, aux_ende);
			printf("Usuario encontrado com sucesso:\n%s\n", res);
			fclose(fp);
			return &res;
		}
		fseek(fp, 60, SEEK_CUR);
	}
	fclose(fp); 

    res = malloc(sizeof(char)*2);
    aux_nome[0] = '\0';
    sprintf(res, "%s", aux_nome);
    printf ("Usuario %s não encontrado!\n\n", argp->nome);
    return &res;
} 


int * update_1_svc (params *argp, struct svc_req *rqstp){
	static int result = 0;
	result = 0;
	FILE * fp = fopen("agenda.bin", "r+b");
	char buf[30];

	while(0 < fread(buf, 30, 1, fp)){
		if(!strcmp(buf, argp->nome)){
			fseek(fp, -30, SEEK_CUR);
			fwrite(argp->aux, 30, 1, fp);
			fwrite(argp->telefone, 30, 1, fp);
			fwrite(argp->endereco, 30, 1, fp);
			result = 1;
			printf("Alterado com sucesso: %s\n", argp->aux);
			break;
		}
		fseek(fp, 60, SEEK_CUR);
	}

	fclose(fp);
	if(result)
		printf("Alterado com sucesso: %s\n", argp->aux);
	else
		printf("Não encontrado: %s\n", argp->aux);

	return (&result);
}


int * delete_1_svc (params *argp, struct svc_req *rqstp){
	static int result = 0;
	result = 0;
	FILE * fp = fopen("agenda.bin", "r+b");
	char buf[30];

	while(0 < fread(buf, 30, 1, fp)){
		if(!strcmp(buf, argp->nome)){
			fseek(fp, -30, SEEK_CUR);
			buf[0] = '\0';
			fwrite(buf, 30, 1, fp);
			fwrite(buf, 30, 1, fp);
			fwrite(buf, 30, 1, fp);
			result = 1;
			break;
		}
		fseek(fp, 60, SEEK_CUR);
	}
	
	fclose(fp);
	if(result)
		printf("Deletado com sucesso: %s\n\n", argp->nome);
	else
		printf("Não encontrado: %s\n\n", argp->nome);
		
	return &result;
}