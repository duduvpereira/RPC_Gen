/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "trabalho_EduP_CLB.h"


void
prog_100(char *host, int operacao, infos *rec)
{
	CLIENT *clnt;
	int  *result_1;
	infos  deposito_100_arg;
	int  *result_2;
	infos  saque_100_arg;
	int  *result_3;
	infos  saldo_100_arg;
	int  *result_4;
	infos  aberturaconta_100_arg;
	int  *result_5;
	infos  fechamentoconta_100_arg;
	int  *result_6;
	infos  autenticaconta_100_arg;
	int  *result_7;
	char *retornaproxassinatura_100_arg;
	int  *result_8;
	infos  deposito_comfalha_100_arg;

#ifndef	DEBUG
	clnt = clnt_create (host, PROG, VERSAO, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

		result_7 = retornaproxassinatura_100((void*)&retornaproxassinatura_100_arg, clnt);
		if (result_7 == (int *) NULL) {
			clnt_perror (clnt, "call failed");
		}
		
		autenticaconta_100_arg.id=rec->id;
		result_6 = autenticaconta_100(&autenticaconta_100_arg, clnt);
		if (result_6 == (int *) NULL) {
			clnt_perror (clnt, "call failed");
		}

	if (operacao==4){
		aberturaconta_100_arg.num_assinatura = *result_7;
		result_4 = aberturaconta_100(&aberturaconta_100_arg, clnt);
		if (result_4 == (int *) NULL) {
			clnt_perror (clnt, "call failed");
		} else if (*result_4==0){
			printf("Não foi possível abrir a conta\n");
		} else {
			printf("A conta de id=%d foi criada\n", *result_4);		
		}
	} else if (operacao==5){
		if (*result_6==0) printf("A conta id=%d não existe\n",rec->id);
		else{
			fechamentoconta_100_arg.id = rec->id;
			fechamentoconta_100_arg.num_assinatura = *result_7;
			result_5 = fechamentoconta_100(&fechamentoconta_100_arg, clnt);
			if (result_5 == (int *) NULL) {
				clnt_perror (clnt, "call failed");
			} else if(*result_5==0){
				printf("Alerta! A conta de id=%d falhou no fechamento\n", rec->id);		
			} else {
				printf("A conta de id=%d foi Fechada\n", rec->id);		
			}
		}
	}
	
	else if (operacao==1 || operacao==6){
		if (*result_6==0) printf("A conta id=%d não existe\n",rec->id);
		else{
			deposito_100_arg.id = rec->id;
			deposito_100_arg.valor = rec->valor;
			deposito_100_arg.num_assinatura = *result_7;
			if (operacao==6) deposito_100_arg.num_assinatura = 0; //caso do depósito com falha
			result_1 = deposito_100(&deposito_100_arg, clnt);
			if (result_1 == (int *) NULL) {
				clnt_perror (clnt, "call failed");
			} else if (*result_1==0) {
				printf("Alerta! O deposito de %d na conta %d falhou. \n", rec->valor, rec->id);		
			}
			else printf("Foi depositado R$ %d na conta %d \n", rec->valor, rec->id);					
		}
	}

	 else if (operacao==2){
		if (*result_6==0) printf("A conta id=%d não existe\n",rec->id);
		else{
			saque_100_arg.id = rec->id;
			saque_100_arg.valor = rec->valor;
			saque_100_arg.num_assinatura = *result_7;
			result_2 = saque_100(&saque_100_arg, clnt);
			if (result_2 == (int *) NULL) {
				clnt_perror (clnt, "call failed");
			} else if(*result_2==0){
				printf("Alerta! O saque de R$ %d da conta %d falhou. \n", rec->valor, rec->id);		
			} else printf("Foi saque de R$ %d na conta %d \n", rec->valor, rec->id);	
		}
	}
	
	 else if (operacao==3){
		if (*result_6==0) printf("A conta id=%d não existe\n",rec->id);
		else{
			saldo_100_arg.id = rec->id;
			//saldo_100_arg.valor = rec->valor;
			//saldo_100_arg.num_assinatura = *result_7;
			result_3 = saldo_100(&saldo_100_arg, clnt);
			if (result_3 == (int *) NULL) {
				clnt_perror (clnt, "call failed");
			} else printf("A conta %d possui Saldo de R$ %d \n", rec->id,*result_3);	
		}
	}
	
	else printf("Opção Inválida!\n");


	


	
	result_8 = deposito_comfalha_100(&deposito_comfalha_100_arg, clnt);
	if (result_8 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{
	char *host;
	
	infos *rec = (infos *) malloc(sizeof(infos));
	

	/*if (argc!=6) {
    fprintf(stderr,"Uso correto: %s perfil operação Valor1 numConta\n",argv[0]);
    printf("argc=>%d\n",argc);
    printf("Perfil:\n");
    printf("	1->caixa\n");
    printf("	2->agencia\n");
    printf("	3->adm\n");
    
    printf("Operação:\n");
    printf("	CAIXA:\n");
    printf("		1-> depósito\n");
    printf("		2-> saque\n");
    printf("		3-> saldo\n");
    printf("	AGENCIA e ADM:\n");
    printf("		4-> abertura\n");
    printf("		5-> fechamento\n");

    exit(0); }*/
    
    
    if (argc != 3) {
		printf ("usage: %s server_host\n", argv[0]);
		fprintf(stderr,"Uso correto: %s perfil operação Valor1 numConta\n",argv[0]);
		printf("argc=>%d\n",argc);
		printf("Perfil:\n");
		printf("	1->caixa\n");
		printf("	2->agencia\n");
		printf("	3->adm\n");
		exit (0);
	}
	
	host = argv[1];
	
	printf ("arg123 %s %s \n",argv[1],argv[2]);
	
	int clt;
	clt = atoi(argv[2]);
	
	int op;
	if(clt == 1){
		printf("		1-> depósito\n");
		printf("		2-> saque\n");
		printf("		3-> saldo\n");
		printf("Qual opercao deseja realizar? ");
		scanf("%d", &op);
	}
	if(clt == 2){
		printf("		4-> abertura\n");
		printf("		5-> fechamento\n");
		printf("Qual opercao deseja realizar? ");
		scanf("%d", &op);
	}
	if(clt == 3){
		printf("		4-> abertura\n");
		printf("		5-> fechamento\n");
		printf("Qual opercao deseja realizar? ");
		scanf("%d", &op);
	}
	
	  int x,y,i,id;
	  int valor,operacao,perfil,assinatura;
	
	 /* Recupera os 2 operandos passados como argumento */
	//x = atoi(argv[1]);   y = atoi(argv[2]); id = atoi(argv[5]);	
	//perfil=atoi(argv[2]);
	
	operacao=op;
	//valor=atoi(argv[4]);
	
	
	
	
	/*if ((perfil==1) && ((operacao < 1) || (operacao >3))) {
		printf("Operação incompatível com o Perfil de Caixa\n");
		return(0);
	}
	if ((perfil==2 || perfil==3) && ((operacao < 1) || (operacao >5))) {
		printf("Operação incompatível com o Perfil de Caixa ou ADM\n");
		return(0);
	}
	if (perfil<1 || perfil>3) printf("perfil inexistente!\n");
	*/

	
	if(operacao==1){
		printf("Digite o id da conta: ");
		scanf("%d", &id);
		printf("Digite o valor a ser depositado: ");
		scanf("%d", &valor);
	}
	
	if(operacao==2){
		printf("Digite o id da conta: ");
		scanf("%d", &id);
		printf("Digite o valor a ser sacado: ");
		scanf("%d", &valor);
	}
	
	if(operacao==3){
		printf("Digite o id da conta: ");
		scanf("%d", &id);
	}
	
	if(operacao==4){
		
	}
	
	if(operacao==5){
		printf("Digite o id da conta que sera fechada: ");
		scanf("%d", &id);
	}
	
	rec->id = id;
	rec->valor = valor;
	rec->num_assinatura = 0;
	
	
	prog_100 (host, operacao, rec);
	exit (0);


}
