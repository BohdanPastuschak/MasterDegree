for((i = 1; i <= 10;++i)); do
	echo $i
	./GeneratorDoubles 1000000 1000000000 1000000000 10 $i > in # need to pass T, C, M, P, seed
	./Dynamic < in >> out
done 
./CalculateTime < out
