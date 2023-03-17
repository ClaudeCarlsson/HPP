for k in 1 2 3 4 5 6 7 8 9 10
do 
    echo -e "\nRUN: ${k}------------------------------"
    for i in 45 50 55
    do
        echo -e "\n${i}------------------------------"
        for n in 1 2 3 4 5 6 7 8
        do
            ./soduko 16 input/16x16_${i}.txt ${n} 1
        done
    done
done