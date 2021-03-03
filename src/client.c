/* Cliente RPC simples */

#include <stdio.h>
#include "agenda.h"

/* funçao que chama a RPC insert_1 */
int insert (CLIENT *clnt, char *nome, char *telefone, char *endereco)
{
   params pars;
   int *result;

   /* junta os parametros em um struct */
   pars.nome = nome;
   pars.telefone = telefone;
   pars.endereco = endereco;
   /* chama a funcao remota */
   while ((result = insert_1 (&pars,clnt)) == NULL)
   {
	 printf ("Problemas ao chamar a função remota insert\n");
    printf ("Tentando novamente...\n");
   }

   if(*result == 1)
      printf("Cadastrado com sucesso!\n");
   else
      printf("Erro ao cadastrar!\n");

   return (*result);
}

/* funçao que chama a RPC search_1 */
char *search (CLIENT *clnt, char *nome, char *telefone, char *endereco)
{
   params pars;
   char **result;

   /* junta os parametros em um struct */
   pars.nome = nome;

   /* chama a funcao remota */
   while((result = search_1 (&pars,clnt)) == NULL)
   {
	  printf ("Problemas ao chamar a funcao remota search\n");
     printf ("Tentando novamente...\n");
   }
   if( *result[0] == '\0' ) {
	   printf("Não encontrado.\n");
      return *result;
   }
   printf("Cadastrado:\n%s\n", *result); 

   return *result;
}


int update (CLIENT *clnt, char *nome, char *telefone, char *endereco, char* aux)
{
   params pars;
   int *result;

   /* junta os parametros em um struct */
   pars.nome = nome;
   pars.telefone = telefone;
   pars.endereco = endereco;
   pars.aux = aux;
	
   /* chama a fun��o remota */
   result = update_1 (&pars,clnt);
   while ((result = update_1 (&pars,clnt)) == NULL)
   {
	 printf ("Problemas ao chamar a função remota update\n");
    printf ("Tentando novamente...\n");
   }
   if (*result == 1)
      printf("Alterado com sucesso\n");
   else 
      printf("Não encontrado\n");

   return (*result);
}


int delete (CLIENT *clnt, char *nome, char *telefone, char *endereco)
{
   params pars;
   int *result;

   /* junta os parametros em um struct */
   pars.nome = nome;

   /* chama a funcao remota */
   
   while ((result = delete_1 (&pars,clnt)) == NULL)
   {
	 printf ("Problemas ao chamar a função remota delete\n");
    printf ("Tentando novamente...\n");
   }

   if(*result == 1)
      printf("Deletado com sucesso!\n");
   else
      printf("Não encontrado!\n");

   return (*result);
}

int main( int argc, char *argv[])
{
   CLIENT *clnt;

   /* verifica se o cliente foi chamado corretamente */
   if (argc!=2)
   {
	  fprintf (stderr,"Usage: %s hostname \n",argv[0]);
	  exit (1);
   }

   /* cria uma struct CLIENT que referencia uma interface RPC */
   clnt = clnt_create (argv[1], AGENDA_PROG, AGENDA_VERSION, "udp");

   /* verifica se a refer�ncia foi criada */
   if (clnt == (CLIENT *) NULL)
   {
	  clnt_pcreateerror (argv[1]);
	  exit(1);
   }


   //menu
	char nome[30];
	char telefone[30];
	char endereco[30];
   char aux[30];

   while(1){

	   printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
	   printf("| 1 - Insere                                  |\n");
	   printf("| 2 - Consulta                                |\n");
	   printf("| 3 - Altera                                  |\n");
	   printf("| 4 - Remove                                  |\n");
      printf("| 5 - Sair                                    |\n");
	   printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
      printf("-> ");
      int menu_option = 0;
      scanf(" %d", &menu_option);
      switch (menu_option) {
         case 1:
            printf("DIGITE O NOME: ");
            scanf(" %[^\n]", nome);
            printf("DIGITE O TELEFONE: ");
            scanf(" %s", telefone);
            printf("DIGITE O ENDERECO: ");
            scanf(" %[^\n]", endereco);
            insert(clnt, nome, telefone, endereco);
            break;
         case 2:
            printf("DIGITE O NOME: ");
            scanf(" %[^\n]", nome);
            search(clnt, nome, NULL, NULL);
            break;
         case 3:
            printf("DIGITE O NOME DO CONTATO QUE DESEJA MUDAR: ");
            scanf(" %[^\n]", nome);
            printf("DIGITE O NOVO NOME: ");
            scanf(" %[^\n]", aux);
            printf("DIGITE O NOVO TELEFONE: ");
            scanf(" %s", telefone);
            printf("DIGITE O NOVO ENDERECO: ");
            scanf(" %[^\n]", endereco);
            update(clnt, nome, telefone, endereco, aux);
            break;
         case 4:
            printf("DIGITE O NOME: ");
            scanf(" %[^\n]", nome);
            delete(clnt, nome, NULL, NULL);
            break;
         case 5:
            return 0;
            break;
         default:
            printf("Opção invalida\n");
            break;
      }

   }

   return (0);
} 
