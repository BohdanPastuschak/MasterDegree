for((i = 1; i <= 100;++i)); do
	echo $i
	./Generator 1000 1048576 1000 50 $i > in # need to pass T, C, M, P, seed
	diff -w <(./Naive < in) <(./Solution < in) || break
done 
