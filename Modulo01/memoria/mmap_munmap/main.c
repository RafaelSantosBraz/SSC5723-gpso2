#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
* arquivo para teste das chamadas de sistema mmap e munmap.
*/

int main(int argc, char *argv[])
{
    /*
    * estrutura do tipo stat (stat.h) que serve como buffer para armazenar informações sober os arquivos.
    */
    struct stat sb;
    /*
    * caminho para o arquivo que será lido.
    */
    const char *file_path = "./file.txt";
    /*
    * o arquivo especificado é aberto para leitura para que as informações sejam coletadas.
    */
    int fd = open(file_path, O_RDONLY);
    /*
    * verifica se o arquivo foi aberto e as informaçõe coletadas.
    */
    if (fd == -1 || fstat(fd, &sb) == -1)
    {
        printf("Erro ao abrir ou ler informações sobre o arquivo! :(\n");
        return EXIT_FAILURE;
    }
    /*
    * ponto de início de leitura do arquivo real.
    * Colocou-se 0 para que todo o texto do arquivo seja lido.
    */
    off_t offset = 0;
    /*
    * operações bit a bit (bitwise) são aplicadas, apenas por facilitar o cálculo, 
    * para mapear o offset informado para o tamanho da página do sistema 
    * - obtida pela variável _SC_PAGE_SIZE do sistema.
    */
    off_t pa_offset = offset & ~(sysconf(_SC_PAGE_SIZE) - 1);
    /*
    * o tamanho do arquivo (tamanho real - o offset de início).
    */
    size_t length = sb.st_size - offset;
    /*
    * a syscall mmap é chamada para mapear o arquivo especificado para memória.
    * Após sua execução, um endereço de memória do local em que o arquivo foi mapeado é retornado,
    * ou um erro.
    * Parâmetro 1: o endereço de preferência (hint) para guiar, mas não necessariamente definir, 
    * onde será mapeado o arquivo. Se NULL, o sistema escolherá sem restrições de posicionamento.
    * Parâmetro 2: tamanho do mapa e não necessariamente do arquivo.
    * Parâmetro 3: especificador de modificação da página como, por exemplo, para leitura (PROT_READ) 
    * ou para escrita (PROT_WRITE).
    * Parâmetro 4: flags que estabelecem modificadores de acesso/visibilidade do mapa para outros 
    * processos como, por exemplo, apenas o processo dono (MAP_PRIVATE) ou compartilhado (MAP_SHARED).
    * Parâmetro 5: arquivo que será mapeado.
    * Parâmetro 6: posição do início do mapeamento.
    */
    char *addr = mmap(NULL, length + offset - pa_offset, PROT_READ, MAP_PRIVATE, fd, pa_offset);
    /*
    * verifica se o mapa foi alocado corretamente.
    */
    if (addr == MAP_FAILED)
    {
        printf("Não foi possível mapear o arquivo! :(\n");
        return EXIT_FAILURE;
    }
    /*
    * escreve na saída padrão (STDOUT) o conteúdo do mapa de memória, o qual remete ao conteúdo do arquivo.
    */
    write(STDOUT_FILENO, addr + offset - pa_offset, length);
    /*
    * após a utilização do mapa, a primitiva contrária a mmap deve ser chamada para liberar o mapa da memória.
    * Parâmetro 1: endereço de memória para a página que será apagada.
    * Parâmetro 2: o tamanho do mapa que será liberado.
    */
    int resp = munmap(addr, length + offset - pa_offset);
    /*
    * verifica se o mapa foi realmente liberado.
    */
    if (resp != 0)
    {
        printf("Erro ao liberar o mapa da memória! :(\n");
    }
    /*
    * o arquivo é fechado.
    */
    close(fd);
    return 0;
}