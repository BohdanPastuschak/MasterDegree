for((i = 1; i <= 10;++i)); do
	echo $i
	./GeneratorDoubles 10000 1073741824 1000000000 50 $i > in # need to pass T, C, M, P, seed
	./NaiveDoubles < in > out
done 
./CalculateTime < out
