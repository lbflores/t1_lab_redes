/*-------------------------------------------------------------*/
/* Exemplo Socket Raw - Captura pacotes recebidos na interface */
/*-------------------------------------------------------------*/

/*

IPV6 / ICMPV6 = ping 8.8.8.8
DNS = Acessar qualquer site

*/

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <string.h>
#include <unistd.h>

/* Diretorios: net, netinet, linux contem os includes que descrevem */
/* as estruturas de dados do header dos protocolos   	  	        */

#include <net/if.h>  //estrutura ifr
#include <netinet/ether.h> //header ethernet
#include <netinet/in.h> //definicao de protocolos
#include <arpa/inet.h> //funcoes para manipulacao de enderecos IP

#include <netinet/in_systm.h> //tipos de dados

#define BUFFSIZE 1518
#define TOTAL_PACOTES 500  // numero de pacotes a serem capturados

// Atencao!! Confira no /usr/include do seu sisop o nome correto
// das estruturas de dados dos protocolos.

  unsigned char buff1[BUFFSIZE]; // buffer de recepcao

  int sockd;
  int on;
  struct ifreq ifr;

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
		printf("erro no ioctl!");
	ioctl(sockd, SIOCGIFFLAGS, &ifr);
	ifr.ifr_flags |= IFF_PROMISC;
	ioctl(sockd, SIOCSIFFLAGS, &ifr);

	//Variáveis para estatísticas
	int count = 0;
	int min = 0;
	int max = 0;
	int media = 0;
	int arpRequest = 0;
	int arpReply = 0;
	int ipv4 = 0;
	int ipv4Porcentagem = 0;	
	int icmp = 0;
	int icmpPorcentagem = 0;
	int icmpEchoRequest = 0;
	int icmpEchoReply = 0;
	int ipv6 = 0;
	int ipv6Porcentagem = 0;
	int icmpv6 = 0;
	int icmpv6Porcentagem = 0;
	int icmpv6EchoRequest = 0;
	int icmpv6EchoReply = 0;
	int udp = 0;
	int udpPorcentagem = 0;
	int tcp = 0;
	int tcpPorcentagem = 0;
	int http = 0;
	int httpPorcentagem = 0;
	int dns = 0;
	int dnsPorcentagem = 0;
	int ftp = 0;
	int ftpPorcentagem = 0;
	int dhcp = 0;
	int dhcpPorcentagem = 0;
	int outro = 0;
	int outroPorcentagem = 0;
	int tamPacote = 0;



	// recepcao de pacotes
	while (count < TOTAL_PACOTES) {
   		tamPacote = recv(sockd,(char *) &buff1, sizeof(buff1), 0x0);
		// impress�o do conteudo - exemplo Endereco Destino e Endereco Origem
		printf("0- %x : 1- %x : 2- %x : 3- %x : 4- %x : 5- %x \n", buff1[0],buff1[1],buff1[2],buff1[3],buff1[4],buff1[5]);
		printf("6- %x : 7- %x : 8- %x : 9- %x: 10- %x: 11- %x \n\n", buff1[6],buff1[7],buff1[8],buff1[9],buff1[10],buff1[11]);
		printf("12- %x : 13- %x  \n", buff1[12],buff1[13]);
		printf("se IPV6 20- %x \n", buff1[20]);
		printf("se ARP 21- %x \n", buff1[21]);
		printf("se IPV4 23- %x \n", buff1[23]);
		printf("tamanho pacote- %d\n", tamPacote);

		//lógica de verificação MAC
		//se ARP
		if (buff1[12]== 0x08 && buff1[13]==0x06){
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
			ipv4++;
			//se TCP
			if(buff1[23]== 0x06){
				tcp++;
			}
			//se UDP
			if(buff1[23]== 0x11 || buff1[23]== 0x17){
				udp++;
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
		if(buff1[12]==0x86 && buff1[13]==0xdd){
			ipv6++;
			//se TCP
			if(buff1[20]== 0x06){
				tcp++;
			}
			//se UDP
			if(buff1[20]== 0x11 || buff1[23]== 0x17){
				udp++;
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
		printf("%d\n", count);
		printf("\n<<<<< FIM DA CAPTURA >>>>>\n");
	}

	//limite para impressão da estatística
		
			//calculo de porcentagem
			ipv4Porcentagem = (float)(ipv4*100)/TOTAL_PACOTES;
			icmpPorcentagem = (float)(icmp*100)/TOTAL_PACOTES;

			printf("Geração de estatísticas: \n");

			printf("- Geral: \n");
			printf("	- Apresentar min/max/média do tamanho dos pacotes recebidos: %d / %d/ %d \n", min, max, media);
	
			printf("- Nível de Enlace: \n");
			printf("	- Quantidade e porcentagem de ARP Requests e ARP Reply: %d	%d \n", arpRequest, arpReply);
			
			printf("- Nível de Rede: \n");
			printf("	- Quantidade e porcentagem de pacotes IPv4: %d	%.3f %c \n", ipv4, ipv4Porcentagem, '%');
			printf("	- Quantidade e porcentagem de pacotes ICMP: %d	%.3f %c \n", icmp, icmpPorcentagem, '%');
			printf(" 	- Quantidade e porcentagem de ICMP Echo Request e ICMP Echo Reply: %d  %d \n", icmpEchoRequest, icmpEchoReply);
			printf(" 	- Quantidade e porcentagem de pacotes IPv6: %d %d \n", ipv6, ipv6Porcentagem);
			printf("    - Quantidade e porcentagem de pacotes ICMPv6: %d %d \n", icmpv6, icmpv6Porcentagem);
			printf("    - Quantidade e porcentagem de ICMPv6 Echo Request e ICMPv6 Echo Reply: %d  %d \n", icmpv6EchoRequest, icmpv6EchoReply);
			
			printf("- Nível de Transporte: \n");
			printf("    - Quantidade e porcentagem de pacotes UDP: %d %d \n", udp, udpPorcentagem);
			printf("    - Quantidade e porcentagem de pacotes TCP: %d %d \n", tcp, tcpPorcentagem);
			printf("    - Lista com as 5 portas TCP mais acessadas: \n");
			printf("    - Lista com as 5 portas UDP mais acessadas: \n");

			printf ("- Nível de Aplicação: \n");
			printf("    - Quantidade e porcentagem de pacotes HTTP: %d  %d \n", http, httpPorcentagem);
			printf("    - Quantidade e porcentagem de pacotes DNS: %d  %d \n", dns, dnsPorcentagem);
			printf("    - Quantidade e porcentagem de pacotes DHCP: %d  %d \n", dhcp, dhcpPorcentagem);
			printf("    - Quantidade e porcentagem para outro protocolo de aplicação qualquer: %d  %d \n", outro, outroPorcentagem);
		
}
