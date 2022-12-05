# empty files, if you wish to keep the content of a file remove it from here
>files.txt
>out.txt
# delete previous sample
rm exemplaires/*.txt -rf

#create 3 times each size
for i in 1 2 3
do
    python gen.py -x 10 -y 20 >> files.txt
    python gen.py -x 36 -y 50 >> files.txt
    python gen.py -x 100 -y 100 >> files.txt
done

# parse and execute
while read line;
do
    filename=*"exemplaires/"$line
    fields=(${line//_/ })
    nb_circ=$((fields[0]*fields[1]/10))
    (timeout 180s ./tp.sh -e $filename -c $nb_circ -p; exit 0) | ./check_sol.py -e $filename -c $nb_circ  >> out.txt
    echo "----------------------------------------------------------">> out.txt
done < "files.txt"