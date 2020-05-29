# Módulo 3

## Simulador de memória virtual paginada

Neste módulo, é implementado um simulador de gerenciamento de memória virtual paginada. O simulador recebe instruções referentes à execução de um programa, onde processos ativos podem solicitar instruções para execução das seguintes operações:
* Criação de um processo (**C**)
* Leitura em memória (**R**)
* Escrita em memória (**W**)
* Execução de instruções armazenadas na memória (**P**)
* Execução de instruções de E/S (**I**)

As instruções ser inseridas antes de executar o sistema, e ficam armazenadas no arquivo [config.txt](https://github.com/RafaelSantosBraz/SSC5723-gpso2/blob/master/Modulo03/simulador_memoria/config.txt).

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

## Configurações do simulador

Algumas configurações do simulador podem ser definidos manualmente antes da execução por meio de modificações no arquivo [config.h](https://github.com/RafaelSantosBraz/SSC5723-gpso2/blob/master/Modulo03/simulador_memoria/config.h).

O tamanho em Kbytes da **página virtual** e do **quadro de página** da memória devem ser iguais, e são definidos na linha 29:
  ```
  #define VIRTUAL_PAGE_SIZE 4
  ```
O tamanho da **memória principal (RAM)** é colocado como uma quantidade de quadros de página, que são multiplicados pelo tamanho em Kbytes do quadro de página.
  ```
  #define RAM_SIZE (FRAME_SIZE * 6)
  ```
O tamanho da **área de troca (swap)** da memória secundária é colocado como uma quantidade de quadros de página, que são multiplicados pelo tamanho em Kbytes do quadro de página.
  ```
  #define SECUNDARY_MEM_MAX_SIZE (FRAME_SIZE * 10000)
  ```
O tamanho da **memória virtual** é colocado como uma quantidade de páginas virtuais, que são multiplicados pelo tamanho em Kbytes de uma página.
  ```
  #define VIRTUAL_MEM_SIZE (VIRTUAL_PAGE_SIZE * 2000)
  ```
Para definir o algoritmo de substituição de páginas usado (LRU ou CLOCK), basta inserir o nome na linha
  ```
  #define CURRENT_METHOD LRU
  ```

## Arquitetura básica do simulador

<img src="https://github.com/RafaelSantosBraz/SSC5723-gpso2/blob/master/Modulo03/Arquitetura.png" height="400" width="500">

## Políticas adotadas

Algumas políticas foram adotadas para garantir o correto funcionamento do simulador e, em especial, minimizar ao máximo a ocorrência de faltas de página.

#### Política de substituição global

Páginas de qualquer processo podem ser substituídas a qualquer momento.

Implicação: quantidade de páginas por processo é dinamicamente gerenciada.

#### Substituição de página

Se uma página for solicitada e existir ao menos 1 quadro de página disponível, a falta de página ocorrerá, mas não será necessária a substituição de uma já mapeada.

Se uma página for solicitada e não houver nenhuma página disponível, então um dos algoritmos de substituição de página é usado para selecionar a página a ser substituída.

Algoritmos: LRU e CLOCK.

#### Alocação Inicial e Wake Up de Processos

Todo processo deve possuir ao menos 15% de suas páginas (calculado a partir da imagem do processo) na RAM em sua criação e/ou em seu retorno da suspensão.

* Não pode exceder 50% do número total de quadros de páginas;
* Se 15% das páginas do processo exceder os 50% total, então são alocadas o máximo possível de páginas sem que extrapole este limite;
* Ao menos 1 quadro de página deve ser atribuído.

Se a imagem do processo for maior do que o limite do espaço de endereçamento virtual, o processo não é criado.

Se não existir espaço disponível na RAM para suprir a política de alocação inicial, processos atualmente mapeados devem ser suspensos para liberar espaço.
**Regra:** processos com a maior quantidade de páginas mapeadas devem ser suspensos. Em caso de empate, o processo mais antigo é escolhido.

OBS: a regra de alocação inicial é apenas garantida no momento de alocação, não durante a execução do processo.

**Quais páginas do processo serão mapeadas?**

**Na criação:** Alocação sequencial da primeira página até o limite estabelecido. Páginas 0 a <valor limite de alocação inicial> - 1.

**Wake up:**

Páginas que estavam mapeadas no momento em que o processo foi suspenso.

* Se o número de páginas ultrapassar o limite de alocação inicial, as n primeiras páginas mapeadas anteriormente até o valor máximo serão trazidas;
* Se o número de páginas for menor que o limite de alocação inicial, todas as páginas mapeadas + as n páginas a partir da última mapeada até o valor limite serão trazidas.

#### Políticas para a área de troca (SWAP)

Quando um processo é criado, um espaço de tamanho igual ao de sua imagem deve ser alocado na área de troca em disco e sua imagem copiada para esta área.

Se a imagem for maior do que o disponível na SWAP, o processo não será criado.

## Execução

Uma vez que as configurações do simulador estejam definidas no arquivo [config.h](https://github.com/RafaelSantosBraz/SSC5723-gpso2/blob/master/Modulo03/simulador_memoria/config.h) e as instruções inseridas no arquivo [config.txt](https://github.com/RafaelSantosBraz/SSC5723-gpso2/blob/master/Modulo03/simulador_memoria/config.txt), o sistema pode ser executado.

Para compilar os arquivos basta executar o arquivo [comp.sh](https://github.com/RafaelSantosBraz/SSC5723-gpso2/blob/master/Modulo03/simulador_memoria/comp.sh) e então executar o arquivo main.out.
  ```
  $ ./comp.sh
  $ ./main.out
  ```
  
 **Exemplos de execução**
 
 Em todos os exemplos a seguir, a seguinte configuração foi utilizada:
 
 * Tamanho das páginas/quadros: 4 Kbytes;
 * Tamanho da memória principal (RAM): 6 quadros;
 * Tamanho da área de troca (SWAP): 10000 molduras de página;
 * Tamanho da memória virtual: 2000 páginas;
 
 A sequência de instruçõe a seguir é um exemplo que aborda quase todas as políticas adotadas. Sua saída foi copiadas para o arquivo [ex1.txt](https://github.com/RafaelSantosBraz/SSC5723-gpso2/blob/master/Modulo03/examples/ex1.txt). Neste exemplo, o algoritmo LRU foi usado para tratar a substituição de página.
 
  ```
  P1 C 100
  P2 C 100
  P1 W (0)2
  P1 I (1)2
  P1 R (4096)2
  P1 R (8192)2
  P2 W (0)2
  P2 R (4096)2
  P2 R (8192)2
  P1 W (0)2 
  P2 P (12288)2
  P3 C 500
  P4 C 9000
  P3 R 6000000
  ```
 
O próximo exemplo foi executado com os dois algoritmos de substituição. Em ambos, a página substituída foi a mesma, apesar dos métodos serem distintos ([resultado da execução](https://github.com/RafaelSantosBraz/SSC5723-gpso2/blob/master/Modulo03/examples/ex2.txt)).
  ```
  P1 C 100
  P2 C 100
  P1 W (0)2
  P1 R (4096)2
  P2 W (0)2
  P2 R (4096)2
  P2 R (8192)2
  P2 P (12288)2
  ```
  
Já no exemplo abaixo, a execução com os algoritmos LRU e CLOCK resultaram na remoção de páginas diferentes da memória ([resultado com LRU](https://github.com/RafaelSantosBraz/SSC5723-gpso2/blob/master/Modulo03/examples/ex3_LRU.txt), [resultado com CLOCK](https://github.com/RafaelSantosBraz/SSC5723-gpso2/blob/master/Modulo03/examples/ex3_CLOCK.txt)).
  ```
  P1 C 100
  P2 C 100
  P1 W (0)2
  P1 R (4096)2
  P1 R (8192)2
  P2  W (0)2
  P2 R (4096)2
  P2 R (8192)2
  P1 W (0)2 
  P2 P (12288)2
  ```
