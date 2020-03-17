for i in `seq 1 100`;
do
	echo "--- Iteration #$i: $(date) ---"
	./bad_matrix_parallel
done
