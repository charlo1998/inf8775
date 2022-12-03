> test.txt
>out.txt
rm exemplaires/*.txt -rf
for i in 1 2 3
do
    python gen.py -x 10 -y 20 >> test.txt
    python gen.py -x 36 -y 50 >> test.txt
    python gen.py -x 100 -y 100 >> test.txt
done
while read line;
do
    filename=*"exemplaires/"$line
    fields=(${line//_/ })
    nb_circ=$((fields[0]*fields[1]/10))
    (timeout 180s ./tp.sh -e $filename -c $nb_circ -p; exit 0) | ./check_sol.py -e $filename -c $nb_circ  >> out.txt
    echo "----------------------------------------------------------">> out.txt
done < "test.txt"