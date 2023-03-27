#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <limits.h>

/* Diretorios: net, netinet, linux contem os includes que descrevem */
/* as estruturas de dados do header dos protocolos   	  	        */
#include <net/if.h>  //estrutura ifr
#include <netinet/ether.h> //header ethernet
#include <netinet/in.h> //definicao de protocolos
#include <arpa/inet.h> //funcoes para manipulacao de enderecos IP
#include <netinet/in_systm.h> //tipos de dados

#define BUFFSIZE 1518
#define TOTAL_PACOTES 3000  // numero de pacotes a serem capturados

// Atencao!! Confira no /usr/include do seu sisop o nome correto
// das estruturas de dados dos protocolos.
unsigned char buff1[BUFFSIZE]; // buffer de recepcao
int sockd;
int on;
struct ifreq ifr;

//struct para porta e quantidade de acessos
typedef struct {
	char porta[4];
	int quantAcesso;
}portaTCP, portaUDP;

//- Lista com as 5 portas TCP mais acessadas
void adicionaListaTCP(char str[],  portaTCP portasTCP[]){
	int i;
	int adicionou = 0;
	int compara;
	for(i=0; i<TOTAL_PACOTES; i++){
		char aux[512];
		memset(aux, 0, sizeof(aux));
		sprintf(aux, "%d", portasTCP[i].quantAcesso);

		// se lista na posião 0 está vazia, adiciona no inicio
		if(portasTCP[0].quantAcesso == 0){
			strcpy(portasTCP[i].porta, str);
			portasTCP[i].quantAcesso = 1;
			//printf("porta: %s\n", portasTCP[i].porta);
			//printf("quantAcesso: %d\n", portasTCP[i].quantAcesso);
			printf("----------------------\n");
			adicionou = 1;
			break;
		}
		//tentativa de fazer a comparação entre o elemento que já está na lista e o que está sendo adicionado
		char var1[512];
		char var2[512];
		memset(var1, 0, sizeof(var1));
		memset(var2, 0, sizeof(var2));
		strcpy(var1, portasTCP[i].porta);
		strcpy(var2, str);
		//usei o strncmp para comparar apenas os 4 primeiros caracteres
		compara = strncmp(var1, var2, 4);
	
		if (compara == 0){
			portasTCP[i].quantAcesso++;
			printf("----------------------\n");
			adicionou = 1;
			break;
		}
	}

	//se não encontrou na lista, adiciona no final
	if (adicionou == 0){
		for(i=0; i<TOTAL_PACOTES; i++){
			if(portasTCP[i].quantAcesso == 0){
				strcpy(portasTCP[i].porta, str);
				portasTCP[i].quantAcesso = 1;
				//printf("porta: %s\n", portasTCP[i].porta);
				//printf("quantAcesso: %d\n", portasTCP[i].quantAcesso);
				printf("----------------------\n");
				break;
			}
		}		
	}
}

//- Lista com as 5 portas UDP mais acessadas
void adicionaListaUDP(char str[],  portaUDP portasUDP[]){
	int i;
	int adicionou = 0;
	int compara;
	for(i=0; i<TOTAL_PACOTES; i++){
		char aux[512];
		memset(aux, 0, sizeof(aux));	
		//printf("aux: %s\n", aux);
		//printf("portasUDP[i].quantAcesso: %d\n", portasUDP[i].quantAcesso);
		//printf("str: %s\n", str);
		sprintf(aux, "%d", portasUDP[i].quantAcesso);
		//printf("aux: %s\n", aux);

		// se lista na posião 0 está vazia, adiciona no inicio
		if(portasUDP[0].quantAcesso == 0){
			strcpy(portasUDP[i].porta, str);
			portasUDP[i].quantAcesso = 1;
			printf("----------------------\n");
			adicionou = 1;
			break;
		}
		//tentativa de fazer a comparação entre o elemento que já está na lista e o que está sendo adicionado
		char var1[512];
		char var2[512];
		memset(var1, 0, sizeof(var1));
		memset(var2, 0, sizeof(var2));
		strcpy(var1, portasUDP[i].porta);
		strcpy(var2, str);
		//usei o strncmp para comparar apenas os 4 primeiros caracteres
		compara = strncmp(var1, var2, 4);

		if (compara == 0){
			portasUDP[i].quantAcesso++;
			//printf("portasUDP[i].quantAcesso: %d\n", portasUDP[i].quantAcesso);
			printf("----------------------\n");
			adicionou = 1;
			break;			
		}
	}	

	//se não encontrou na lista, adiciona no final
	if (adicionou == 0){
		for(i=0; i<TOTAL_PACOTES; i++){
			if(portasUDP[i].quantAcesso == 0){
				strcpy(portasUDP[i].porta, str);
				portasUDP[i].quantAcesso = 1;
				printf("----------------------\n");
				break;
			}
		}
	}
}

void exibe5maioresTCP(portaTCP portasTCP[], int tamanho){
    for (int i = 0; i < TOTAL_PACOTES; i++){
        for (int j = i; j < TOTAL_PACOTES; j++){
            if (portasTCP[i].quantAcesso < portasTCP[j].quantAcesso){
				portaTCP temp;
				strcpy(temp.porta, portasTCP[i].porta);
				temp.quantAcesso = portasTCP[i].quantAcesso;
				strcpy(portasTCP[i].porta, portasTCP[j].porta);
				portasTCP[i].quantAcesso = portasTCP[j].quantAcesso;
				strcpy(portasTCP[j].porta, temp.porta);
				portasTCP[j].quantAcesso = temp.quantAcesso;
            }
        }
    }
	for(int i = 0; i < 5; i++){
		printf("			Porta: %s Quantidade de acessos: %d \n", portasTCP[i].porta, portasTCP[i].quantAcesso);
	}
}

void exibe5maioresUDP(portaUDP portasUDP[], int tamanho){
    for (int i = 0; i < TOTAL_PACOTES; i++){
        for (int j = i; j < TOTAL_PACOTES; j++){
            if (portasUDP[i].quantAcesso < portasUDP[j].quantAcesso){
				portaUDP temp;
				strcpy(temp.porta, portasUDP[i].porta);
				temp.quantAcesso = portasUDP[i].quantAcesso;
				strcpy(portasUDP[i].porta, portasUDP[j].porta);
				portasUDP[i].quantAcesso = portasUDP[j].quantAcesso;
				strcpy(portasUDP[j].porta, temp.porta);
				portasUDP[j].quantAcesso = temp.quantAcesso;
            }
        }
    }
	for(int i = 0; i < 5; i++){
		printf("			Porta: %s Quantidade de acessos: %d \n", portasUDP[i].porta, portasUDP[i].quantAcesso);
	}
}

float calculatePercentage(float value, int total) {
    float percentage = (value / total) * 100;
    return percentage;
}

int hexToDecimal(char port[4]) {
    int decimalValue;
    sscanf(port, "%x", &decimalValue);
    return decimalValue;
}

int main(int argc,char *argv[])
{
    /* Criacao do socket. Todos os pacotes devem ser construidos a partir do protocolo Ethernet. */
    /* De um "man" para ver os parametros.*/
    /* htons: converte um short (2-byte) integer para standard network byte order. */
    if((sockd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) < 0) {
       printf("Erro na criacao do socket.\n");
       exit(1);
    }

	// O procedimento abaixo eh utilizado para "setar" a interface em modo promiscuo
	strcpy(ifr.ifr_name, "eth0");
	if(ioctl(sockd, SIOCGIFINDEX, &ifr) < 0)
		printf("erro no ioctl!\n");
	ioctl(sockd, SIOCGIFFLAGS, &ifr);
	ifr.ifr_flags |= IFF_PROMISC;
	ioctl(sockd, SIOCSIFFLAGS, &ifr);

	//Variáveis para estatísticas
	int count = 0;
	int smallestPacketSize = INT_MAX;
	int largestPacketSize = 0;
	float averagePacketSize = 0;
	int totalPacketsReceivedSize = 0;
	int arpRequest = 0;
	int arpReply = 0;
	int ipv4 = 0;	
	int icmp = 0;
	int icmpEchoRequest = 0;
	int icmpEchoReply = 0;
	int ipv6 = 0;
	int icmpv6 = 0;
	int icmpv6EchoRequest = 0;
	int icmpv6EchoReply = 0;
	int udp = 0;
	int tcp = 0;
	int http = 0;
	int https = 0;
	int dns = 0;
	int ftp = 0;
	int dhcp = 0;
	int outro = 0;
	int tamPacote = 0;
	portaTCP portasTCP [TOTAL_PACOTES];
	portaUDP portasUDP [TOTAL_PACOTES];

	// inicializa vetor de portas TCP
	for(int i = 0; i < TOTAL_PACOTES; i++){
		strcpy(portasTCP[i].porta, "0");
		portasTCP[i].quantAcesso = 0;
	}
	// inicializa vetor de portas UDP
	for(int i = 0; i < TOTAL_PACOTES; i++){
		strcpy(portasUDP[i].porta, "0");
		portasUDP[i].quantAcesso = 0;
	}

	// recepcao de pacotes
	while (count < TOTAL_PACOTES) {
   		tamPacote = recv(sockd,(char *) &buff1, sizeof(buff1), 0x0);
		totalPacketsReceivedSize += tamPacote;
		count++;

		// Maior e Menor pacote
		if(tamPacote > largestPacketSize){
			largestPacketSize = tamPacote;
		}
		if(tamPacote < smallestPacketSize){
			smallestPacketSize = tamPacote;
		}
		// impress�o do conteudo - exemplo Endereco Destino e Endereco Origem
		//printf("0- %x : 1- %x : 2- %x : 3- %x : 4- %x : 5- %x \n", buff1[0],buff1[1],buff1[2],buff1[3],buff1[4],buff1[5]);
		//printf("6- %x : 7- %x : 8- %x : 9- %x: 10- %x: 11- %x \n\n", buff1[6],buff1[7],buff1[8],buff1[9],buff1[10],buff1[11]);
		printf("Protocolo: %x  %x  \n", buff1[12],buff1[13]);
		//printf("tamanho pacote- %d\n", tamPacote);

		//lógica de verificação MAC
		//se ARP
		if (buff1[12]== 0x08 && buff1[13]==0x06){
			//printf("ARP 21- %x \n", buff1[21]);
			//se ARP Request
			if(buff1[21]== 0x01){
				arpRequest++;
			}
			//se ARP Reply
			if(buff1[21]== 0x02){
				arpReply++;
			}			
		}
		//se IPv4
		if(buff1[12]== 0x08 && buff1[13]==0x00){
			char str [4];
			char aux [4];
			char aux2[4];
			//printf("IPV4 23- %x \n", buff1[23]);
			ipv4++;

			// HTTPS - 443 || (01BB)
			if(buff1[34] == 0x01 && buff1[35] == 0xbb){
				https++;
			}

			//se TCP
			if(buff1[23]== 0x06){		
				memset(str, 0, sizeof(str));
				memset(aux, 0, sizeof(aux));
				memset(aux2, 0, sizeof(aux2));		
				tcp++;
				sprintf(aux, "%x", buff1[34]);
				//printf("TCP 34- %x \n", buff1[34]);
				sprintf(aux2, "%x", buff1[35]);
				//printf("TCP 35- %x \n", buff1[35]);
				strcat(str,  aux);
				strcat(str,  aux2);
				printf("Porta TCP: %s \n", str);
				adicionaListaTCP(str, portasTCP);
			}
			//se UDP
			if(buff1[23]== 0x11 || buff1[23]== 0x17){
				udp++;
				memset(str, 0, sizeof(str));
				memset(aux, 0, sizeof(aux));
				memset(aux2, 0, sizeof(aux2));	
				
				sprintf(aux, "%x", buff1[36]);
				//printf("UDP 36- %x \n", buff1[36]);
				sprintf(aux2, "%x", buff1[37]);
				//printf("UDP 37- %x \n", buff1[37]);
				strcat(str,  aux);
				strcat(str,  aux2);
				printf("Porta UDP: %s \n", str);
				adicionaListaUDP(str, portasUDP);
				
			}

			//se HTTP Porta 80
			if(buff1[34]== 0x00 && buff1[35]== 0x50){
				http++;
			}
			//se DNS Porta 53
			if(buff1[34]== 0x00 && buff1[35]== 0x35){
				dns++;
			}
			//se DHCP Porta 67
			if(buff1[34]== 0x00 && buff1[35]== 0x43){
				dhcp++;
			}
			//se ICMPv4
			if(buff1[23]== 0x01){
				icmp++;
				if (buff1[34] == 0x00){
					icmpEchoRequest++;
				}
				else{
					icmpEchoReply++;
				}
			}
		}

		//se IPv6
		if(buff1[12]==0x86 && buff1[13]==0xdd){
			char str [4];
			char aux [4];
			char aux2[4];
			//printf("IPV6 20- %x \n", buff1[20]);
			ipv6++;

			// HTTPS - 443 || (01BB)
			if(buff1[34] == 0x01 && buff1[35] == 0xbb){
				https++;
			}
			//se TCP
			if(buff1[20]== 0x06){
				memset(str, 0, sizeof(str));
				memset(aux, 0, sizeof(aux));
				memset(aux2, 0, sizeof(aux2));		
				tcp++;
				sprintf(aux, "%x", buff1[54]);
				//printf("TCP 54- %x \n", buff1[54]);
				sprintf(aux2, "%x", buff1[55]);
				//printf("TCP 55- %x \n", buff1[55]);
				strcat(str,  aux);
				strcat(str,  aux2);
				printf("Porta TCP: %s \n", str);
				adicionaListaTCP(str, portasTCP);
			}
			//se UDP
			if(buff1[20]== 0x11 || buff1[23]== 0x17){
				udp++;
				memset(str, 0, sizeof(str));
				memset(aux, 0, sizeof(aux));
				memset(aux2, 0, sizeof(aux2));	
				
				sprintf(aux, "%x", buff1[56]);
				//printf("UDP 56- %x \n", buff1[56]);
				sprintf(aux2, "%x", buff1[57]);
				//printf("UDP 57- %x \n", buff1[57]);
				strcat(str,  aux);
				strcat(str,  aux2);
				printf("Porta UDP: %s \n", str);
				adicionaListaUDP(str, portasUDP);
				
			}
			//se HTTP Porta 80
			if(buff1[54]== 0x00 && buff1[55]== 0x50){
				http++;
			}
			//se DNS Porta 53
			if(buff1[54]== 0x00 && buff1[55]== 0x35){
				dns++;
			}
			//se DHCP Porta 67
			if(buff1[54]== 0x00 && buff1[55]== 0x43){
				dhcp++;
			}
			//se ICMPv6
			if(buff1[20]== 0x3a){
				icmpv6++;
				if (buff1[52] == 0x80){
					icmpv6EchoRequest++;
				}
				else{
					icmpv6EchoReply++;
				}
			}
		}	
	}

	averagePacketSize = totalPacketsReceivedSize / TOTAL_PACOTES;


	printf("\n<<<<< FIM DA CAPTURA >>>>>\n\n\n");
	// Print table
	printf("===== Packets Stats =====\n");
	printf("Min %d\n", smallestPacketSize);
	printf("Max %d\n", largestPacketSize);
	printf("AVG %.2f\n", averagePacketSize);

	printf("\n\n\n");

	printf("%-25s%-16d%-21d\n", "Protocolo", " Nro de pacotes", "  % do total");
	printf("%-25s%-16d%-21.2f\n", "ARP Request", arpRequest, calculatePercentage((float)arpRequest, TOTAL_PACOTES));
	printf("%-25s%-16d%-21.2f\n", "ARP Reply", arpReply, calculatePercentage((float)arpReply, TOTAL_PACOTES));
	printf("%-25s%-16d%-21.2f\n", "IPv4", ipv4, calculatePercentage((float)ipv4, TOTAL_PACOTES));
	printf("%-25s%-16d%-21.2f\n", "ICMP", icmp, calculatePercentage((float)icmp, TOTAL_PACOTES));
	printf("%-25s%-16d%-21.2f\n", "ICMP Echo Request", icmpEchoRequest, calculatePercentage((float)icmpEchoRequest, TOTAL_PACOTES));
	printf("%-25s%-16d%-21.2f\n", "ICMP Echo Reply", icmpEchoReply, calculatePercentage((float)icmpv6EchoReply, TOTAL_PACOTES));
	printf("%-25s%-16d%-21.2f\n", "IPv6", ipv6, calculatePercentage((float)ipv6, TOTAL_PACOTES));
	printf("%-25s%-16d%-21.2f\n", "ICMPv6", icmpv6, calculatePercentage((float)icmpv6, TOTAL_PACOTES));
	printf("%-25s%-16d%-21.2f\n", "ICMPv6 Echo Request", icmpv6EchoRequest, calculatePercentage((float)icmpv6EchoRequest, TOTAL_PACOTES));
	printf("%-25s%-16d%-21.2f\n", "ICMPv6 Echo Reply", icmpv6EchoReply, calculatePercentage((float)icmpv6EchoReply, TOTAL_PACOTES));
	printf("%-25s%-16d%-21.2f\n", "UDP", udp, calculatePercentage((float)udp, TOTAL_PACOTES));
	printf("%-25s%-16d%-21.2f\n", "TCP", tcp, calculatePercentage((float)tcp, TOTAL_PACOTES));
	printf("%-25s%-16d%-21.2f\n", "HTTP", http, calculatePercentage((float)http, TOTAL_PACOTES));
	printf("%-25s%-16d%-21.2f\n", "HTTPS", https, calculatePercentage((float)https, TOTAL_PACOTES));
	printf("%-25s%-16d%-21.2f\n", "DNS", dns, calculatePercentage((float)dns, TOTAL_PACOTES));
	printf("%-25s%-16d%-21.2f\n", "DHCP", dhcp, calculatePercentage((float)dhcp, TOTAL_PACOTES));

	printf("\n\n\n");

	printf("- Lista com as 5 portas TCP mais acessadas: \n");
	exibe5maioresTCP(portasTCP, TOTAL_PACOTES);
	printf("- Lista com as 5 portas UDP mais acessadas: \n");
	exibe5maioresUDP(portasUDP, TOTAL_PACOTES);

	// printf("Geração de estatísticas: \n");
	// printf(" - Nível de Enlace: \n");
	// printf("	- Quantidade e porcentagem de ARP Requests e ARP Reply: \n");
	// printf("	- ARP Requests %d 	%.2f%c \n", arpRequest, (float)(arpRequest*100)/TOTAL_PACOTES, '%');
	// printf("	- ARP Reply %d 	%.2f%c \n\n", arpReply, (float)(arpReply*100)/TOTAL_PACOTES, '%');

	// printf(" - Nível de Rede: \n");
	// printf("	- Quantidade e porcentagem de pacotes IPv4: %d	%.2f%c \n", ipv4, (float)(ipv4*100)/TOTAL_PACOTES, '%');
	// printf("	- Quantidade e porcentagem de pacotes ICMP: %d	%.2f%c \n", icmp, (float)(icmp*100)/TOTAL_PACOTES, '%');
	// printf(" - Quantidade e porcentagem de ICMP Echo Request e ICMP Echo Reply:\n");
	// printf("	- ICMP Echo Request %d 	%.2f%c  \n", icmpEchoRequest, (float)(icmpEchoRequest*100)/TOTAL_PACOTES, '%');
	// printf("	- ICMP Echo Reply %d 	%.2f%c  \n\n", icmpEchoReply, (float)(icmpEchoReply*100)/TOTAL_PACOTES, '%');
	// printf("	- Quantidade e porcentagem de pacotes IPv6: %d 	%.2f%c \n", ipv6, (float)(ipv6*100)/TOTAL_PACOTES, '%');
	// printf("	- Quantidade e porcentagem de pacotes ICMPv6: %d 	%.2f%c \n", icmpv6, (float)(icmpv6*100)/TOTAL_PACOTES,'%')
	// printf("	- Quantidade e porcentagem de ICMPv6 Echo Request e ICMPv6 Echo Reply:\n");
	// printf("	- ICMPv6 Echo Request %d 	%.2f%c  \n", icmpv6EchoRequest, (float)(icmpv6EchoRequest*100)/TOTAL_PACOTES, '%');
	// printf("	- ICMPv6 Echo Reply %d 	%.2f%c  \n\n", icmpv6EchoReply, (float)(icmpv6EchoReply*100)/TOTAL_PACOTES, '%');
		
	// printf("- Nível de Transporte: \n");
	// printf("	- Quantidade e porcentagem de pacotes UDP: %d 	%.2f%c \n", udp, (float)(udp*100)/TOTAL_PACOTES,'%');
	// printf("	- Quantidade e porcentagem de pacotes TCP: %d 	%.2f%c \n", tcp, (float)(tcp*100)/TOTAL_PACOTES,'%');

	// printf ("\n- Nível de Aplicação: \n");
	// printf("	- Quantidade e porcentagem de pacotes HTTP: %d  %.2f%c \n", http, (float)(http*100)/TOTAL_PACOTES,'%');
	// printf("	- Quantidade e porcentagem de pacotes DNS: %d  %.2f%c \n", dns, (float)(dns*100)/TOTAL_PACOTES,'%');
	// printf("	- Quantidade e porcentagem de pacotes DHCP: %d  %.2f%c \n", dhcp, (float)(dhcp*100)/TOTAL_PACOTES,'%');
	// printf("	- Quantidade e porcentagem para outro protocolo de aplicação qualquer: %d  %.2f%c \n", https, (float)(https*100)/TOTAL_PACOTES,'%');
		
}