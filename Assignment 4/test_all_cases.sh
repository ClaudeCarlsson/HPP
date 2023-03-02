STEPS=200

for i in 00010 00100 00500 01000 02000 03000
do
    if [ "$i" = "03000" ]
    then 
        STEPS=100
    fi
    echo -e "\n${i} ------------------------------"
    time ./galsim "${i}" input_data/ellipse_N_"${i}".gal "${STEPS}" 0.00001 0 8
    compare_gal_files/compare_gal_files "${i}" result.gal ref_output_data/ellipse_N_"${i}"_after"${STEPS}"steps.gal
done