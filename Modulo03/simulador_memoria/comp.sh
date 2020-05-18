shopt -s globstar

for file in *.*
do
    if [ "${file##*.}" == "c" ];
    then
        var="${var} ${file}"
    fi
done

gcc ${var} -o main.out
