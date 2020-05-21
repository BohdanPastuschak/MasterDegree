for((i = 1; i <= 10;++i)); do
	echo $i
	./GeneratorDoubles 1000000 1073741824 1000000000 90 $i > in # need to pass T, C, M, P, seed
	./DynamicSegmentTree < in >> out
done 
./CalculateTime < out
