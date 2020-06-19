#Tamanho do arquivo em Kb
#>/dev/null 2>&1  -> hide de output 

main() 
{
    echo "Tamanho do arquivo em Kb: "
    read file_size;
    bytes=$(expr $file_size \* 1024)

    result_folder=result
    mkdir -p $result_folder
    file_path=./$result_folder/file.txt
    make_out_path=./$result_folder/make_output.txt
    read_out_path=./$result_folder/read_output.txt
    remove_out_path=./$result_folder/remove_output.txt

    make_record
    read_record
    remove_record
}

#Função para criar o arquivo do tamanho informado
make_file()
{
    n_bytes=$(expr $bytes / 2) #assim já conta o \n como byte 
    for (( i=0; i < $n_bytes; i++ ))
    do
        echo "a" >> $file_path
    done
}

#Função para gravar o tempo das operações de criação no arquivo make_output.txt
make_record()
{
    for i in {1..10}
    do
        echo "---Execução $i---" >> $make_out_path
        exec 3>&1 4>&2
        var=$( { time make_file 1>&3 2>&4; } 2>&1 )
        exec 3>&- 4>&- 
        echo -e "${var}\n\n" >> $make_out_path
        rm $file_path        
    done 
}

#Função para gravar o tempo de leitura no arquivo read_output.txt
read_record()
{
    make_file
    for i in {1..10}
    do
        echo "---Execução $i---" >> $read_out_path
        exec 3>&1 4>&2
        var=$( { time read_file 1>&3 2>&4; } 2>&1 )
        exec 3>&- 4>&- 
        echo -e "${var}\n\n" >> $read_out_path      
    done
    rm $file_path
}

#Função para ler o arquivo
read_file()
{
    while IFS= read -r line
    do 
        true
    done < "$file_path"
}

#Função para remover e gravar o tempo de remoção do arquivo
remove_record()
{
    make_file
    for i in {1..10}
    do
        echo "---Execução $i---" >> $remove_out_path
        exec 3>&1 4>&2
        var=$( { time rm $file_path 1>&3 2>&4; } 2>&1 )
        exec 3>&- 4>&- 
        echo -e "${var}\n\n" >> $remove_out_path
        make_file     
    done
    rm $file_path
}
main