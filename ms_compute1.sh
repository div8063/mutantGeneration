rm Mutation_Score;
tm=`ls mutant*.out | wc -l`

#	for ((i=1;i<=tm;i++))
#	do
#		if((j>=15))
#			then break
#		else 
#			((j++));
#		fi
#		printf '%3d ' "$i"  >> kill_mat
#	done	
#	printf '\n' >> kill_mat
#	((tm=j));

	while read line
	do
		echo $line > p2
		./input.out < p2 > real_output
		km=0;
		echo $line >p1
		((j=0))
	
		for i in mutant*.out
		do
#			if((j>=15))
#				then break
#			else 
#				((j++));
#			fi
			./$i < p1 > mfile
			cmp mfile real_output > /dev/null
			if test $? -ne 0
			then
				printf '%d ' "1"  >> kill_mat
				km=$((km=km+1))
			else
				printf '%d ' "0"  >> kill_mat
			fi
		done
		echo >> kill_mat
		echo "scale=5; $km * 100 / $tm" | bc >> Mutation_Score
		echo -n "  $line             $km              $tm            "
		echo $(bc <<< "scale = 5; $km / $tm * 100")
done < population 2> /dev/null
