for((i = 1; i <= 10;++i)); do
	./StaticGenerator 5000 100000 100 $i > in
	./StaticSolution < in > out
	./StaticNaive < in > out
done 
