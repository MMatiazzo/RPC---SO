

/*#define PROGRAM_NUMBER 12345678
#define VERSION_NUMBER 1*/

#define PROGRAM_NUMBER 1111111
#define VERSION_NUMBER 1

/* tipo de dado que ser� passado aos procedimentos remotos */

struct params
{
    string nome<30>;
    string telefone<30>;
    string endereco<30>;
    string aux<30>;
};

/* Defini��o da interface que ser� oferecida aos clientes */

program AGENDA_PROG
{
   version AGENDA_VERSION
   {
     int INSERT (params) = 1;
     string SEARCH (params) = 2;
     int UPDATE (params) = 3;
     int DELETE (params) = 4;
   }
   = VERSION_NUMBER;
}
= PROGRAM_NUMBER;

 
