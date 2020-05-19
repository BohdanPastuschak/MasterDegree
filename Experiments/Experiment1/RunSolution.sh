for((i = 1; i <= 100;++i)); do
	echo $i
	./Generator 10000 1048576 1000 50 $i > in # need to pass T, C, M, P, seed
	./Solution < in > out
done 
./CalculateTime < out
