for i in `seq 1 100`;
do
	echo "--- Iteration #$i: $(date) ---"
	./good_matrix_parallel
done
