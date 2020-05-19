for((i = 1; i <= 10;++i)); do
	echo $i
	./GeneratorDoubles 1000000 1048576 1000000 50 $i > in # need to pass T, C, M, P, seed
	./SolutionDoubles < in > out
done 
./CalculateTime < out
