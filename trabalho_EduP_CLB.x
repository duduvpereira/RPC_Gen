struct infos {
	int id;
	int valor;
	int num_assinatura;
	};
program PROG {
   version VERSAO {
        int deposito(infos) = 1;
        int saque(infos) = 2;
		int saldo(infos) = 3;
		int aberturaConta(infos) = 4;
		int fechamentoConta(infos) = 5;		
		int autenticaConta(infos) = 6;		
		int retornaProxAssinatura() = 7;
		int deposito_comFalha(infos) = 8;
   } = 100;
} = 55555555;
