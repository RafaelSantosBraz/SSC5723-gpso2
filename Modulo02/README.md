# Módulo 02

Este módulo objetiva-se em exemplificar a solução do problema do produtor/consumidor por meio de mutexes e threads em C. O código comentado está disponível [aqui](https://github.com/RafaelSantosBraz/SSC5723-gpso2/blob/master/Modulo02/produtor_consumidor/main.c).

O programa é subdividido em duas partes principais:

* Produtor: responsável por gerar aleatoriamente números inteiros (entre 1 e 100) e armazená-los em um buffer compartilhado, sendo bloqueado se o tamanho máximo do buffer for atingido.
* Consumidor: responsável com retirar os números armazenados no buffer compartilhado e os imprimir no terminal, sendo bloquado se o buffer estiver vazio.

Obs: o código do programa é totalmente estático, se desejar alterar a quantidade de números a serem gerados ou o tamanho do buffer compartilhado, é preciso alterar as duas macros correspondentes no arquivo "main.c".

* Exemplo de execução:
   ```sh 
    //Para compilar deve ser adicionado o parâmetro -pthread
    $ gcc main.c -o main.out -pthread
    $ ./main.out
    34 100 69 89 
    27 70 50 76 
    4 25 
   ```   
* Às macros MAX_NUMBERS e BUFFER_MAX foram atribuídos os valores 10 e 4, respectivamente. MAX_NUMBERS indica a quantidade total de números que serão produzidos/consumidos, e BUFFER_MAX define o tamanho do buffer utilizado para armazenar os números.
Portando, na saída acima foram exibidos 10 números, agrupados em até 4 por linha,devido ao tamanho definido para o buffer.
