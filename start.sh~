echo "Start of Mutation Testing Program"
date
echo 
rm input.out simple_ga_input Mutation_Score mutant*.c mutant*.out all_testcase testcase_result all_score kill_mat population best_members 2> /dev/null

echo "input name of c program"
read name

cp $name input.c 

g++ parse_in_cpp.cpp
./a.out

echo "total mutants generated = `ls mutant*.c | wc -l`"
echo "waiting for compilation of mutants ......."

for i in mutant*.c
do
		gcc $i -lm -o $i.out 2> /dev/null
		if test $? -ne 0
		then
			rm $i
		fi
done
gcc input.c -lm -o input.out

echo "total mutants after filtering = `ls mutant*.c | wc -l`"

echo "how many parameters are in test cases"
read n;

i=1;
while((i<=n))
do
	echo "enter range of $i th parameter"
	read r1 r2
	echo $r1 $r2 >> simple_ga_input
	((i++))
done

g++ EGA.cpp

./a.out 2> /dev/null
g++ setcover.cpp

./a.out 2> /dev/null

#rm mutant*.c mutant*.out mfile p2 p1 real_output simple_ga_input a.out input.c testcase_input input.out Mutation_Score population 2> /dev/null
echo "Normal end of execution"
date
