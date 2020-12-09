for((i = 1; ;++i)); do
	echo $i
	./StaticGenerator 1000 1000 100 $i > in # need to pass Q1 Q2 N seed
	diff -w <(./StaticNaive < in) <(./StaticSolution < in) || break
done 
