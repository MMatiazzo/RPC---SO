Trabalho de SO RPC

Método de uso:

Na pasta src:

Rode o comando: make

Com isso ele compila

rpcgen  agenda.x
cc -g    -c -o client.o client.c
cc -g    -c -o agenda_clnt.o agenda_clnt.c
cc -g    -c -o agenda_xdr.o agenda_xdr.c
cc -g     -o client client.o agenda_clnt.o agenda_xdr.o -lnsl 
cc -g    -c -o server.o server.c
cc -g    -c -o agenda_svc.o agenda_svc.c
cc -g     -o server server.o agenda_svc.o agenda_xdr.o -lnsl
rm -f core client.o agenda_clnt.o agenda_xdr.o server.o agenda_svc.o agenda_xdr.o

Com o programa compilado rodamos o server:
./server

O server vai ficar rodando esperando o client.

Com o server rodando rodamos agora o client:
./client localhost

Com o client aberto ele mostrará o menu de opções:
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
| 1 - Insere                                  |
| 2 - Consulta                                |
| 3 - Altera                                  |
| 4 - Remove                                  |
| 5 - Sair                                    |
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

[Exemplo de Inserção]:

Client side:
-> 1
DIGITE O NOME: exemplo
DIGITE O TELEFONE: 999
DIGITE O ENDERECO: 999
Cadastrado com sucesso!

Server Side:
Usuario castrado:
 -exemplo
 -999
 -999

[Exemplo Consulta]:

Client side:

(Caso haja o nome procurado no arquivo)
-> 2
DIGITE O NOME: exemplo
Cadastrado:
 nome:exemplo
 telefone:999
 endereco:999
 
Server side:
Usuario encontrado com sucesso:
 nome:exemplo
 telefone:999
 endereco:999
 
(Caso o nome procurado não esteja no arquivo)

Client side:
-> 2
DIGITE O NOME: "teste"
Não encontrado.

Server side:
Usuario "teste" não encontrado!

[Exemplo Alterar]:

(Caso o contato que deseja alterar exista)

Client side:
-> 3
DIGITE O NOME DO CONTATO QUE DESEJA MUDAR: exemplo
DIGITE O NOVO NOME: novo_exemplo
DIGITE O NOVO TELEFONE: 22
DIGITE O NOVO ENDERECO: 22
Alterado com sucesso

Server side:

Alterado com sucesso: novo_exemplo

(Caso o contato que deseja alterar não exista)

Client side:

DIGITE O NOME DO CONTATO QUE DESEJA MUDAR: exemplo1
DIGITE O NOVO NOME: exemplo_novo
DIGITE O NOVO TELEFONE: 22
DIGITE O NOVO ENDERECO: 22
Não encontrado

Server side:

Não encontrado: exemplo1

[Exemplo Remove]:

(Caso exista o contato no banco)

Client side:
-> 4
DIGITE O NOME: remove_exemplo
Deletado com sucesso!

Server side:
Deletado com sucesso: remove_exemplo

(Caso não exista no bando o nome digitado)

Client Side:
-> 4
DIGITE O NOME: nao_existe
Não encontrado!

Server side:
Não encontrado: nao_existe

Em qualquer uma das consultas caso o client não receba confirmação o server envia novamente o resultado até receber a confirmação que chegou.
