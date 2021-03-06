/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

int contador_id=0;
int contaassinatura=0; //contador de assinaturas


#include "trabalho_EduP_CLB.h"



struct infos conta[100];

int *
deposito_100_svc(infos *argp, struct svc_req *rqstp)
{
	static int  result;

	/*
	 * insert server code here
	 */
	 
	 result = 0;
	 printf("Requisição de depósito\n");
	 if (argp->num_assinatura == contaassinatura){
		 for(int i=0; i<100; i++){
			if(conta[i].id == argp->id){
				conta[i].valor = conta[i].valor + argp->valor;
				result = 1;
				break;
			}
		 }
	} else printf("Assinatura com falha!");

	return &result;
}

int *
saque_100_svc(infos *argp, struct svc_req *rqstp)
{
	static int  result;

	/*
	 * insert server code here
	 */
	 result=0;
	 if (argp->num_assinatura == contaassinatura){
		 for(int i=0; i<100; i++){
			if(conta[i].id == argp->id){
				conta[i].valor = conta[i].valor - argp->valor;
				result = 1;
				break;
			}
		 }
	 } else printf("Assinatura com falha!");

	return &result;
}

int *
saldo_100_svc(infos *argp, struct svc_req *rqstp)
{
	static int  result;

	/*
	 * insert server code here
	 */
	 result=0;
	 for(int i=0; i<100; i++){
		if(conta[i].id == argp->id){
			result = conta[i].valor;
			break;
		}
	 }

	return &result;
}

int *
aberturaconta_100_svc(infos *argp, struct svc_req *rqstp)
{
	static int  result=0;

	/** FUNÇÃO NÂO-IDEMPOTENTE */
	/* 1. A abertura de conta não pode ser executada mais de uma vez 
	 * 2. É testado se o valor de "argp->num_assinatura" é igual ao valor do contador GLOBAL de Assinatura "contaassinatura"
	 * 3. O código só é executado se for igual
	 * */
	 printf("Requisição para abertura de conta\n");
	 result=0;
	 if (argp->num_assinatura == contaassinatura){
		contador_id++; // começa em '1' (Não queremos conta n '0')
		conta[contador_id].id = contador_id;
		conta[contador_id].valor = 0;
		result = conta[contador_id].id ;
	} else printf("Assinatura com falha!\n");
	return &result;
}

int *
fechamentoconta_100_svc(infos *argp, struct svc_req *rqstp)
{
	static int  result=0;

	/*
	 * insert server code here
	 */
	 printf("Requisição para fechamento da conta %d\n",argp->id);
	 if (argp->num_assinatura == contaassinatura){
		 for(int i=0; i<100; i++){
			if(conta[i].id == argp->id){
				conta[i].id = 0;
				result = 1;
				break;
			}
		 }
	 } else printf("Assinatura com falha!\n");
	 
	return &result;
}

int *
autenticaconta_100_svc(infos *argp, struct svc_req *rqstp)
{
	static int  result;

	printf("Requisição para autenticação da conta %d\n",argp->id);	
	/*
	 * insert server code here
	 */
	 result=0;
	 for(int i=0; i<=contador_id; i++){
	//	 printf("DEBUG Autentica: i=%d / conta[i].id=%d argp->id=%d\n",i,conta[i].id,argp->id);
		if(conta[i].id == argp->id){
			result = 1;
			break;
		}
	 }
	
	return &result;
}

int *
retornaproxassinatura_100_svc(void *argp, struct svc_req *rqstp)
{
	static int  result;

	/*
	 * insert server code here
	 */
	 /** RESPOSTA A REQUISICAO DO CLIENTE **/
	contaassinatura++;
	result=contaassinatura;
	printf("Requisição de chave número %d\n",result);
	
	//Responde ao cliente com o próximo valor do Contador
	return &result;
}

int *
deposito_comfalha_100_svc(infos *argp, struct svc_req *rqstp)
{
	static int  result;

	/*
	 * insert server code here
	 */

	return &result;
}
