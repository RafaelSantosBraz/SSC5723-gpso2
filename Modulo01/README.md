# Módulo 01

Este módulo foi dividido em 2 grandes categorias:

* Demonstração de chamadas de sistema; e
* Demonstração de tipos de processo (CPU e I/O-bound).

Algumas subdivisões foram criadas dentro dessas grandes categorias (clique no nome para ver o código):

* Chamadas de Sistema:
    * Arquivos:
        * [Chmod](https://github.com/RafaelSantosBraz/SSC5723-gpso2/tree/master/Modulo01/arquivos/chmod/main.c)
        * [Open e Write](https://github.com/RafaelSantosBraz/SSC5723-gpso2/tree/master/Modulo01/arquivos/open_write/main.c)
    * Memória:
        * [Brk](https://github.com/RafaelSantosBraz/SSC5723-gpso2/tree/master/Modulo01/memoria/brk/main.c)
        * [Mmap e Munmap](https://github.com/RafaelSantosBraz/SSC5723-gpso2/tree/master/Modulo01/memoria/mmap_munmap/main.c)
    * Processos:
        * [Execve](https://github.com/RafaelSantosBraz/SSC5723-gpso2/tree/master/Modulo01/processos/execve/main.c)
        * [Fork](https://github.com/RafaelSantosBraz/SSC5723-gpso2/tree/master/Modulo01/processos/fork/main.c)
        * [Kill](https://github.com/RafaelSantosBraz/SSC5723-gpso2/tree/master/Modulo01/processos/kill/main.c)
* Tipos de Processos:
    * [CPU-Bound](https://github.com/RafaelSantosBraz/SSC5723-gpso2/tree/master/Modulo01/cpu_bound/main.c)
    * [I/O-Bound](https://github.com/RafaelSantosBraz/SSC5723-gpso2/tree/master/Modulo01/IO_bound/main.c)
    
* Commandos para uso da ferramenta strace:
   * O programa main.c precisa ser primeiramente compilado: ```$ gcc main.c -o main.out```
   * Comandos no strace para os programa fork.c e kill.c:
      * Obs: Usar o parâmetro -f para que o strace rastreie também a execução dos procesos filhos.
   ```sh 
      $ strace -f ./main.out
      $ strace -c -f ./main.out > /dev/null
   ```
   * Comandos no strace para os demais programas:
   ```sh 
      $ strace ./main.out
      $ strace -c ./main.out > /dev/null
   ```   
* A ferramenta time permite que a string com as saídas seja formatada:
   ```sh 
      $ /usr/bin/time -f "Tempo total: %e \n
        Porcentagem de uso do CPU: %P \n
        Tempo em modo usuário: %U \n
        Tempo em modo Kernel: %S \n
        Troca de contexto voluntária: %w \n
        Troca de contexto involuntária: %c \n
        Entradas no sistema de arquivos: %I \n
        Saídas no sistema de arquivos: %O \n\n" ./main.out
   ```  
****

**Documentação dos Programas Desenvolvidos**

* **Chmod** 
    * Descrição: o programa altera as permissões de um arquivo chamado "file.txt", apresentando suas permissões antigas e as atuais para comparação.
    * Como Utilizar: Por referenciar um arquivo fixo, não é necessário passar qualquer parâmetro. Apenas executar o programa.
    * Exemplo de Utilização:
        ```sh
        $ ./main.out

        Permissões ANTES do chmod:
        -rwxr-xr-x 1 gpos02 allusers 0 Apr  2 10:20 file.txt
        Permissões DEPOIS do chmod:
        -rwx---rw- 1 gpos02 allusers 0 Apr  2 10:20 file.txt
        ```
* **Open e Write** 
    * Descrição: o programa abre um arquivo de texto "arq.txt", carrega um buffer com caracteres e escreve o conteúdo do buffer no arquivo.
    * Como Utilizar: o buffer é carregado no código do programa, portanto, basta executá-lo. O resultado pode ser visualizado abrindo o arquivo arq.txt após a execução.
    * Exemplo de Utilização:
        ```sh
        $ ./main.out
        
        Conteúdo do buffer inserido no arquivo
        
        //O  conteúdo do arquivo pode ser visualizado pelo nano
        $ nano arq.txt
        Conteúdo do buffer inserido no arquivo
        
        ```
* **Brk** 
    * Descrição: o programa utiliza a primitiva brk para alocar 3 espaços de memória. O programa pede ao uuário para informar dois números que são armazenados nos dois primeiros espaços alocados. Depois os números informados são somados e o resultado é aramazenado no último espaço alocado. Por fim, o resultado é apresentado ao usuário.
    * Como Utilizar: Apenas execute o programa e, quando solicitado, informe dois números inteiros para serem somados.
    * Exemplo de Utilização:
        ```sh
        $ ./main.out
        
        Informe o primeiro número: 40
        Informe o segundo número: 2
        A soma dos dois número é: 42
        ```
* **Mmap e Munmap** 
    * Descrição: o programa realiza o mapeamento para a memória, em modo de leitura, do conteúdo do arquivo "file.txt" e realiza a leitura do mapa em memória para exibição do conteúdo do arquivo no terminal. Logo após, o mapa em memória e liberado. Desta forma, as duas primitivas são utilizadas.
    * Como Utilizar: como o programa utiliza um arquivo fixo, apenas é necessário executar o programa.
    * Exemplo de Utilização:
        ```sh
        $ ./main.out

        Essa linha deveria aparecer na tela!
        ```
        * Obs: a linha exibida é o conteudo de "file.txt".
* **Execve** 
    * Descrição: o programa começa a executar pelo código do arquivo "main" que apenas exibe uma mensagem e depois troca o processo em execução pela chamada dessa diretiva para o código do arquivo "novo", o qual informa uma mensagem e exibe o valor recebido por parâmetro pelo processo "main".
    * Como Utilizar: o programa foi construído de forma fixa para simplicá-lo e, portanto, é necessário apenas executá-lo.
    * Exemplo de Utilização:
        ```sh
        $ ./main.out

        Processo original :)
        Processo novo :O
        Valor recebido: 42
        ```
* **Fork** 
    * Descrição: o programa cria um processo filho e executa o código dos processos pai e filho. Por meio de um caractere char que é declarado antes da chamada fork e alterado posteriormente no processo pai, é possível verificar que seu valor e o mapeamento do caractere na memória continuam o mesmo para o processo filho.
    * Como Utilizar: os parâmetros já são fornecidos no código do programa, portando, basta executá-lo.
    * Exemplo de Utilização:
        ```sh
        $ ./main.out
        pid = 29769

        Executando o processo pai...
        Caractere e Endereço: b - 0x7ffea8a77053
        PID do Pai: 29769
        Região comum

        $ 
        Executando o processo filho...
        Caractere e endereço: a - 0x7ffea8a77053
        PID do Filho: 29770
        Região comum
      
        ```
* **Kill** 
    * Descrição: O programa cria um processo filho por meio da chamada fork. O código do processo filho é executado por completo, enquanto que a execução do código do processo pai é interrompida pela chamada de sistema kill, que envia um sinal para matar o processo.
    * Como Utilizar: Todos os parâmetros já estão inclusos no código do programa, portanto, basta executá-lo.
    * Exemplo de Utilização:
        ```sh
        $ ./main.out
        pid = 29862

        Executando o processo pai:
        Killed
        $ 
        Executando o processo filho...
        PID do Filho: 29863
        Região comum
        
        ```
* **CPU-Bound** 
    * Descrição: o programa recebe um número inteiro como parâmetro e realiza o cálculo da soma de todos os números inteiros no intervalo entre 0 e o número informado, apresentando o resultado no final.
    * Como Utilizar: é preciso informar um número inteiro como parâmetro ao programa.
    * Exemplo de Utilização:
        ```sh
        $ ./main.out 9

        Calculando a soma de todos os inteiros entre 0 e 9
        Soma: 45
        ```
* **I/O-Bound** 
    * Descrição: o programa abre o arquivo "arq.txt" e realiza uma ou mais leituras de um buffer. A cada leitura, o conteúdo do buffer é escrito no arquivo.
    * Como Utilizar: Quando o programa solicitar o texto a ser escrito no buffer, basta digitar um texto com até 127 caracteres e pressionar a tecla enter. Para continuar escrevendo, digite 's', ou, para encerrar o programa, digite 'n' ou qualquer outro caractere, e, por fim, tecle enter. O resultado pode ser conferido ao abrir o arquivo arq.txt.
    * Exemplo de Utilização:
        ```sh
        $ ./main.out
        
        Digite uma linha de texto:linha 1

        Continuar escrevendo? (s / n) s

        Digite uma linha de texto:linha 2

        Continuar escrevendo? (s / n) s

        Digite uma linha de texto:linha 3

        Continuar escrevendo? (s / n) n

        $

        //Texto escrito no arquivo arq.txt
        $ nano arq.txt
        linha 1
        linha 2
        linha 3

        ```
                
