#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main (int argc, char *argv[])
{
    int fd1;//irá armazenar o descritor do arquivo a ser aberto
    char arq[] = "./arq.txt";//diretório do arquivo
    /*
	O retorno da função open é o descritor do arquivo, que é um identificador dos arquivos abertos no sistema
	Argumentos da função open
	arq -> diretório do arquivo a ser aberto
	flags -> O_RDWR indica que o arquivo a ser aberto tem permissão para ser lido e escrito durante a execução do programa
		 O_CREAT se o diretório descrito no primeiro argumento não existe, então ele é criado
		 O_TRUNC se já houver um arquivo com o mesmo nome descrito no diretório do primeiro argumento, então seu conteúdo é apagado
	mode -> O terceiro argumento é o campo mode, que indica a configuração de permissão que arquivo assumirá após a execução do programa.
		Seu valor é um inteiro, que pode ser representado também por TAGS pré-definidas.
		00777 -> permissão para leitura, escrita e execução por qualquer usuário.
    */
    fd1 = open(arq, O_RDWR | O_CREAT | O_TRUNC, 00777);
    if (fd1 == -1) { //em caso de erro, a função open retorna o valor -1
        perror(arq);
        return EXIT_FAILURE;
    }

    char buf[] = "Conteúdo do buffer inserido no arquivo";

    write(fd1, buf, strlen(buf));
    /*
	Argumentos da função write:
	fd1 -> descritor do arquivo no qual o conteúdo do buffer é será escrito
	buf -> buffer usado para armazenar os dados a serem escritos, que neste caso é um array de caracteres.
	strlen(buf) -> o terceiro argumento determina quantos bytes devem ser lido após o endereço do buffer, que neste caso, equivale ao tamanho do array retornado pela função strlen()
     */

     printf("\n %s \n", buf);

    close(fd1); //fecha o arquivo

    return 0;
}
