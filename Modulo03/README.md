# Módulo 4

## Simulador de memória virtual paginada

Neste módulo, é implementado um simulador de gerenciamento de memória virtual paginada. O simulador recebe instruções referentes à execução de um programa, onde processos ativos podem solicitar instruções para execução das seguintes operações:
* Criação de um processo (**C**) [link linha 25](https://github.com/RafaelSantosBraz/SSC5723-gpso2/edit/master/Modulo03/README#L25)
* Leitura em memória (**R**)
* Escrita em memória (**W**)
* Execução de instruções armazenadas na memória (**P**)
* Execução de instruções de E/S (**I**)

As instruções ser inseridas antes de executar o sistema, e ficam armazenadas no arquivo [config.txt](/simulador_memoria/config.txt).

As instruções possuem três itens: \[ID do processo\] \[TAG da instrução] \[tamanho do processo / endereço de memória / ID do dispositivo de E/S]

* **ID do processo:** Nome identificador do processo. (ex: P1; P2; P3; ...)
* **TAG da instrução:** Define a instrução a ser executada. Pode ser uma das descritas acima, representada pela TAG **C**, **R**, **W**, **P** ou **I**.
* **tamanho do processo / endereço de memória / ID do dispositivo de E/S:** Quando a TAG **C** é usada, este item indica o tamanho (em Kbytes) da imagem do processo. Se a TAG for **R**, **W** ou **P**, este item indica o valor decimal de um endereço (em binário) lógico de memória na tabela páginas do processo. Com a TAG **I**, este item indica o valor decimal do identificador (em binário) de um dispositivo de E/S. 

Exemplos de instruções aceitas:
* **P1 C 500** - Cria um processo identificado como P1, com 500 Kbytes de tamanho
* **P1 R (1024)2** - Acessa e lê o conteúdo da memória indicado pelo endereço lógico 1024 (em binário)
* **P1 W (4)2** - Escreve na memória no conteúdo indicado pelo endereço lógico 4 (em binário)
* **P1 P (4096)2** - Acessa e executa instrução armazenada na memória indicado pelo endereço 4096 (em binário)
* **P1 I (2)2** - Executa instrução de E/S sobre o dispositivo 2 (em binário)

OBS: A instrução **P** não executa de fato uma outra instrução buscada na memória, mas apenas simboliza a busca por uma instrução armazenada na memória. O simulador possui E/S programada, portanto, a instrução **I** apenas simboliza o processo de espera pelo término de uma instrução de E/S.

## Arquitetura básica do sistema
![](/Arquitetura.png)
