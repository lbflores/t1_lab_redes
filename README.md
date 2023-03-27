# t1_lab_redes
Trabalho 1 - Lab Redes
Integrantes: Alessandro Borges de Souza | Leticia Brasil Flores | Lucas Leifheit Nardon 


Para executar o programa é necessário ter o gcc instalado e executar os seguintes comandos:

Para compilar: gcc -o programa recepcao_socket.c
Para executar: sudo ./programa

O número de pacotes que serão capturados está fixado em TOTAL_PACOTES.
Após atingir o TOTAL_PACOTES, o programa irá apresentar a mensagem " FIM DA CAPTURA " e as estatísticas conforme exemplo abaixo:



(adicionar imagem aqui)


Observações:

- DHCP: O protocolo de aplicação DHCP serve para configurar as máquinas dos usuários, fornecendo informações como: IP, Máscara, Gateway e servidor DNS. Assim para observar a ocorrência desse protocolo durante a captura pode-se, por exmeplo, conectar e desconetar o dispopsitivo da rede Wi-fi.

- HTTP: Acessar a página http://www.pudim.com.br

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