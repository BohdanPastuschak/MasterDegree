for((i = 1; ;++i)); do
	echo $i
	./DynamicGenerator 1000 10000 $i > in # need to pass Q N seed
	diff -w <(./DynamicNaive < in) <(./DynamicSolution < in) || break
done 
