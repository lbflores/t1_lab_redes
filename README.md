# t1_lab_redes
Trabalho 1 - Lab Redes

Integrantes: Alessandro Borges de Souza | Leticia Brasil Flores | Lucas Leifheit Nardon 


Para executar o programa é necessário ter o gcc instalado e executar os seguintes comandos:

Para compilar: gcc -o programa recepcao_socket.c
Para executar: sudo ./programa

O número de pacotes que serão capturados está fixado em TOTAL_PACOTES.
Após atingir o TOTAL_PACOTES, o programa irá apresentar a mensagem " FIM DA CAPTURA " e as estatísticas conforme exemplo abaixo:

````
```

<<<<< FIM DA CAPTURA >>>>>


===== Packets Stats =====
Min 42
Max 1514
AVG 76.00



Protocolo                Nro de pacotes  % do total           
ARP Request              16              0.53                 
ARP Reply                16              0.53                 
IPv4                     686             22.87                
ICMP                     3               0.10                 
ICMP Echo Request        1               0.03                 
ICMP Echo Reply          2               7.53                 
IPv6                     782             26.07                
ICMPv6                   226             7.53                 
ICMPv6 Echo Request      0               0.00                 
ICMPv6 Echo Reply        226             7.53                 
UDP                      203             6.77                 
TCP                      673             22.43                
HTTP                     12              0.40                 
HTTPS                    264             8.80                 
DNS                      50              1.67                 
DHCP                     0               0.00                 



- Lista com as 5 portas TCP mais acessadas: 
                        Porta: 443 Quantidade de acessos: 301 
                        Porta: 34634 Quantidade de acessos: 74 
                        Porta: 50630 Quantidade de acessos: 21 
                        Porta: 39290 Quantidade de acessos: 20 
                        Porta: 58460 Quantidade de acessos: 20 
- Lista com as 5 portas UDP mais acessadas: 
                        Porta: 53 Quantidade de acessos: 50 
                        Porta: 1900 Quantidade de acessos: 24 
                        Porta: 5353 Quantidade de acessos: 23 
                        Porta: 57621 Quantidade de acessos: 20 
                        Porta: 443 Quantidade de acessos: 16 

```
````


- Nível de Enlace:

	- ARP Requests e ARP Reply: Protocolo de Resolução de Endereços.

- Nível de Rede:

	- IPv4 e IPv6: Protocolos responsáveis por identificar computadores na Internet e garantir que as informações cheguem ao destino correto. 
    
	- ICMP e ICMPv6: Internet Control Message Protocol. Serve para determinar a disponibilidade da rede e gerenciar o tráfego e o controle de erros na camada de rede.


- Nível de Transporte:

	- UDP - Protocolo não é voltado à conexão, prioriza velocida e não a confiabilidade.

	- TCP - Protocolo voltado à conexão e tem como garantia a integridade e ordem de todos os dados.

- Nível de Aplicação:

	- HTTP e HTTPS: Responsável pela transferência de dados na Internet.

	- DNS: Domain Name System. Responsável por localizar e traduzir para números IP.

	- DHCP: O protocolo de aplicação DHCP serve para configurar as máquinas dos usuários, fornecendo informações como: IP, Máscara, Gateway e servidor DNS. Assim para observar a ocorrência desse protocolo durante a captura pode-se, por exemplo, conectar e desconetar o dispositivo da rede Wi-fi.



Cada protocolo de aplicação tem sua porta específica. Exemplo:

80 - HTTP

443 - HTTPS

53 - DNS

67 e 68 - DHCP


Cada aplicação que precisa se comunicar com a rede, terá uma porta também:

0 até 1023 - portas para protocolos de internet.

1024 até 65535 - portas livres no Sistema Operacional que podem ser utilizadas.
