# compilação automática do programa.

shopt -s globstar

for file in *.*
do
    if [ "${file##*.}" == "c" ];
    then
        var="${var} ${file}"
    fi
done

gcc -O3 ${var} -o main.out -lm
