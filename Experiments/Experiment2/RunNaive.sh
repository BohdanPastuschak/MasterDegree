for((i = 1; i <= 10;++i)); do
	echo $i
	./GeneratorDoubles 100000 1048576 1000 90 $i > in # need to pass T, C, M, P, seed
	./NaiveDoubles < in >> out
done 
./CalculateTime < out
