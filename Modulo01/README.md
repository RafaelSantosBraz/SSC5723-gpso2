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
    * Descrição:
    * Como Utilizar:
    * Exemplo de Utilização:
        ```sh
        $ comandos e 
        $ saídas
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
    * Descrição:
    * Como Utilizar:
    * Exemplo de Utilização:
        ```sh
        $ comandos e 
        $ saídas
        ```
* **Kill** 
    * Descrição:
    * Como Utilizar:
    * Exemplo de Utilização:
        ```sh
        $ comandos e 
        $ saídas
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
    * Descrição:
    * Como Utilizar:
    * Exemplo de Utilização:
        ```sh
        $ comandos e 
        $ saídas
        ```
                