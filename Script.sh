for((i = 1; ;++i)); do
	echo $i
	./RandomTestGenerator 1000 10000 $i > in # need to pass Q, N, i
	diff -w <(./Straightforward < in) <(./SolutionSimple < in) || break
done 
