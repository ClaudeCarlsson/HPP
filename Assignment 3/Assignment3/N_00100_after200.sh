N=00100
STEPS=200

./galsim ${N} input_data/ellipse_N_${N}.gal ${STEPS} 0.00001 0

compare_gal_files/compare_gal_files ${N} result.gal ref_output_data/ellipse_N_${N}_after${STEPS}steps.gal