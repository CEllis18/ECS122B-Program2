#!/bin/bash
#ex: bash datagather.sh
g++ subset.cpp -o subset -std=c++11
g++ datagenerator.cpp -o datagenerator -std=c++11
g++ ntuple.cpp -o ntuple -std=c++11
g++ mysub.cpp -o mysub -std=c++11

count=1
for j in `seq 3 6`; do
    for k in `seq 1 6`; do
        for i in `seq 1 50`; do 
            ./datagenerator $j $k
		numItems=$(head -n 1 tester.txt)
		maxWeight=$(head -n 2 tester.txt | tail -n 1)


	    	(time ./ntuple) 2> ntupleResult.txt	
			while read -r line
			do
				#echo "$line"
				gline=$(grep "real" $line)
				#echo "$gline"
				fTime=${gline/real	/}
				#echo $fTime
				fTime2=${fTime/[0-9]*m/}
				#echo $fTime2
				nTupleTime=${fTime2/s/}
				#echo $nTupleTime
			done < ntupleResult.txt	
	    	#(time ./subset) 2> subsetResult.txt
		(time ./mysub) 2> mysubResult.txt
			while read -r subLine
			do
				#echo "$subLine"
				gsline=$(grep "real" $subLine)
				#echo "$gsline"
				fsTime=${gsline/real	/}
				#echo "$fsTime"
				fsTime2=${fsTime/[0-9]*m/}
				#echo "$fsTime2"
				subsetTime=${fsTime2/s/}
				#echo $subsetTime
			#done < subsetResult.txt
			done < mysubResult.txt
	    	echo "$count,$numItems,$maxWeight,$j,$k,$subsetTime,$nTupleTime" >> results.csv
		count=$(($count+1))
	    	rm ntupleResult.txt
	    	#rm subsetResult.txt 
		rm mysubResult.txt
            rm tester.txt
        done
    done
done
rm mysub
rm subset
rm ntuple
rm datagenerator
