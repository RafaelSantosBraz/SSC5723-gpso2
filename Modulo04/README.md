# Módulo 4

# Desempenho dos sistemas de arquivos

Neste módulo foi desenvolvido um estudo onde 3 dos mais conhecidos e utilizados sistemas de arquivos foram analisados:
* Ext4
* FAT32
* NTFS

A análise levou em consideração 3 operações:
* Criação de arquivos
* Leitura de arquivos
* Destruição de arquivos

Cada uma das operações foram executadas 10 vezes sobre cada arquivo. Foram considerados arquivos de:
* 5Kb
* 10Kb
* 100Kb
* 1Mb
* 10Mb
* 100Mb
* 500Mb

### Ambiente de execução

O experimento foi executado sobre o seguinte ambiente:
* Sistema operacional Ubuntu  versão 18.04.4 LTS instalado sobre um HD
* Pendrive Kingston 8Gb
* Processador Intel Core I5 - 2.5Gh

As operações são executadas por meio do código [run.sh](https://github.com/RafaelSantosBraz/SSC5723-gpso2/blob/master/Modulo04/run.sh) em bash (shell) para execução das operações (criação, leitura e remoção).

Para a escrita, é criado um arquivo de texto com 0kb que é incrementado em blocos de 5kb até o valor desejado.

Para leitura, o arquivo é lido linha a linha.

O tempo das operações é coletado em segundos por meio do comando *time*.

### Execução do experimento 

Basta colar o arquivo [run.sh](https://github.com/RafaelSantosBraz/SSC5723-gpso2/blob/master/Modulo04/run.sh) dentro do dispositivo de armazenamento desejado, acessar o dispositivo pelo terminal e executar o comando
  ```
  $ ./run.sh
  ```
Em seguida, deve-se informar o tamanho (em Kb) do arquivo de texto a ser criado, considerando o tamanho mínimo de 5Kb.

Ao fim da execução, os resultados ficam armazenados na pasta *result*, que é criada no mesmo local onde o arquivo *run.sh* foi copiado.

Os resultados das 10 operações de criação, leitura e destruição dos arquivos são registrados, respectivamente, no arquivos:
*make_output.txt
*read_output.txt
*remove_output.txt

## Empacotamento

Os dados coletados para cada sistema de arquivo neste experimento podem ser encontrados nas pastas [Ext4](https://github.com/RafaelSantosBraz/SSC5723-gpso2/tree/master/Modulo04/Ext4), [FAT32](https://github.com/RafaelSantosBraz/SSC5723-gpso2/tree/master/Modulo04/FAT32) e [NTFS](https://github.com/RafaelSantosBraz/SSC5723-gpso2/tree/master/Modulo04/NTFS) deste repositório.

Os dados brutos e as tabelas estão disponíveis neste [link do Google Sheets](https://docs.google.com/spreadsheets/d/14_hjFr-qH5X3917sVOhHBvbvRBKm8kXy5HDCoObJY3c/edit#gid=1747600645&range=G31) 
