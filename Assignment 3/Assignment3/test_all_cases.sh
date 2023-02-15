STEPS=200

for i in {00010, 00100, 00500, 01000, 02000}
do
    echo -e '------------------------------\n'
    ./galsim ${i} input_data/ellipse_N_${i}.gal ${STEPS} 0.00001 0
    sleep 0.5
    compare_gal_files/compare_gal_files ${i} result.gal ref_output_data/ellipse_N_${i}_after${STEPS}steps.gal
    sleep 0.5
done

i=03000
STEPS=100
./galsim ${i} input_data/ellipse_N_${i}.gal ${STEPS} 0.00001 0
sleep 0.5
compare_gal_files/compare_gal_files ${i} result.gal ref_output_data/ellipse_N_${i}_after${STEPS}steps.gal