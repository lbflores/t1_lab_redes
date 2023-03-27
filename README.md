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
AVG 442.00


Protocolo                -743927531      -743927544           
ARP Request              4               0.13                 
ARP Reply                3               0.10                 
IPv4                     1349            44.97                
ICMP                     0               0.00                 
ICMP Echo Request        0               0.00                 
ICMP Echo Reply          0               1.20                 
IPv6                     1640            54.67                
ICMPv6                   36              1.20                 
ICMPv6 Echo Request      0               0.00                 
ICMPv6 Echo Reply        36              1.20                 
UDP                      1529            50.97                
TCP                      1380            46.00                
HTTP                     24              0.80                 
HTTPS                    214             7.13                 
DNS                      351             11.70                
DHCP                     1               0.03          


- Lista com as 5 portas TCP mais acessadas: 
                        Porta: 1bb Quantidade de acessos: 714 
                        Porta: d882� Quantidade de acessos: 199 
                        Porta: ae9a, Quantidade de acessos: 44 
                        Porta: c4c8 Quantidade de acessos: 31 
                        Porta: 050 Quantidade de acessos: 24 
- Lista com as 5 portas UDP mais acessadas: 
                        Porta: 035 Quantidade de acessos: 357 
                        Porta: 1bb Quantidade de acessos: 312 
                        Porta: 9ba1] Quantidade de acessos: 93 
                        Porta: 14e9K Quantidade de acessos: 75 
                        Porta: 9ff1. Quantidade de acessos: 46 

```
````

Observações:

- DHCP: O protocolo de aplicação DHCP serve para configurar as máquinas dos usuários, fornecendo informações como: IP, Máscara, Gateway e servidor DNS. Assim para observar a ocorrência desse protocolo durante a captura pode-se, por exemplo, conectar e desconetar o dispositivo da rede Wi-fi.

- IPV6 / ICMPV6: Fazer ping 8.8.8.8

- A lista de portas TCP e UDP mais utilizadas está sendo apresentada em hexadecimal. Exemplo: Porta dffa em hexadecimal = Porta 57338 em decimal

Cada protocolo de aplicação tem sua porta específica. Exemplo:
80 - HTTP
443 - HTTPS
53 - DNS
67 e 68 - DHCP


Cada aplicação que precisa se comunicar com a rede, terá uma porta também:

0 até 1023 - portas para protocolos de internet.
1024 até 65535 - portas livres no Sistema Operacional que podem ser utilizadas.
