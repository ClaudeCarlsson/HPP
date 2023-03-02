for N in 1 2 3 4 5 6 7 8
do
    STEPS=200
    for i in 00500 03000
    do
        if [ "$i" = "03000" ]
        then 
            STEPS=100
        fi
        echo -e "\n${i}-OpenMP-Threads: ${N}--------------------------"
        time ./galsim "${i}" input_data/ellipse_N_"${i}".gal "${STEPS}" 0.00001 0 "${N}"
    done
done