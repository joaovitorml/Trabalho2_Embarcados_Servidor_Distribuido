#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "servidor_tcp.h"
#include "reading_temp_umi.h"
#include "gpio.h"

void TrataClienteTCP(int socketCliente) {
	char buffer[50];
	char dispo[50];
	char buffer_temper[50];

	while (1) {
		recv(socketCliente, buffer, 16, 0);
		printf("%c\n",buffer[0]);
		switch(buffer[0]){
			case '1':
				recv(socketCliente, dispo, 16, 0);
				config_gpio_proj(buffer[0], dispo[0]);
				memset(buffer, 0, sizeof buffer);
				memset(dispo, 0, sizeof dispo);
				break;
			case '2':
				recv(socketCliente, dispo, 16, 0);
				config_gpio_proj(buffer[0], dispo[0]);
				memset(buffer, 0, sizeof buffer);
				memset(dispo, 0, sizeof dispo);
				break;
			case '3':
				gpio_check();
				memset(buffer, 0, sizeof buffer);
				break;
			case '4':
				memset(buffer, 0, sizeof buffer);
				if(send(socketCliente, buffer, strlen(buffer)+1, 0) == 1)
					printf("Erro no envio - send()\n");
				memset(buffer, 0, sizeof buffer);
				break;
			case '5':
				recv(socketCliente, buffer_temper, 16, 0);
				printf("%s\n",buffer_temper);
				memset(buffer, 0, sizeof buffer);
				memset(buffer_temper, 0, sizeof buffer_temper);
				break;
			default:
				break;
		}
        sleep(1);
	}
}

void* Servidor(void *args) {

	int servidorSocket;
	int socketCliente;
	struct sockaddr_in servidorAddr;
	struct sockaddr_in clienteAddr;
	unsigned short servidorPorta;
	unsigned int clienteLength;

	servidorPorta = 5000;

	// Abrir Socket
	if((servidorSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		printf("falha no socker do Servidor\n");

	// Montar a estrutura sockaddr_in
	memset(&servidorAddr, 0, sizeof(servidorAddr)); // Zerando a estrutura de dados
	servidorAddr.sin_family = AF_INET;
	servidorAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servidorAddr.sin_port = htons(servidorPorta);

	// Bind
	if(bind(servidorSocket, (struct sockaddr *) &servidorAddr, sizeof(servidorAddr)) < 0)
		printf("Falha no Bind\n");

	// Listen
	if(listen(servidorSocket, 10) < 0)
		printf("Falha no Listen\n");		

	while(1) {
		clienteLength = sizeof(clienteAddr);
		if((socketCliente = accept(servidorSocket, 
			                      (struct sockaddr *) &clienteAddr, 
			                      &clienteLength)) < 0)
			printf("Falha no Accept\n");
		
		printf("Conexão do Cliente %s\n", inet_ntoa(clienteAddr.sin_addr));
		
		TrataClienteTCP(socketCliente);
		close(socketCliente);

	}
	close(servidorSocket);

}
