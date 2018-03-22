#!/bin/bash

#for ((x=1;x<=10;x++)); do cat OLA1-input.txt | ./random_board $x 100 | ./a-star 2 ; done | grep "d="

echo "starting a-star-3:"

echo "N:"
for ((x=1;x<=100;x++)); do cat OLA1-input.txt | ./random_board $x 100 | ./a-star 3 ; done | grep "N=" | cut -f2 -d'=' > a-star-3-N
echo "V:"
for ((x=1;x<=100;x++)); do cat OLA1-input.txt | ./random_board $x 100 | ./a-star 3 ; done | grep "V=" | cut -f2 -d'=' > a-star-3-V
echo "d:"
for ((x=1;x<=100;x++)); do cat OLA1-input.txt | ./random_board $x 100 | ./a-star 3 ; done | grep "d=" | cut -f2 -d'=' > a-star-3-d
echo "b:"
for ((x=1;x<=100;x++)); do cat OLA1-input.txt | ./random_board $x 100 | ./a-star 3 ; done | grep "b=" | cut -f2 -d'=' > a-star-3-b 
			
echo "finished a-star-3"

echo "starting a-star-2:"
echo "N:"
for ((x=1;x<=100;x++)); do cat OLA1-input.txt | ./random_board $x 100 | ./a-star 2 ; done | grep "N=" | cut -f2 -d'=' > a-star-2-N
echo "V:"
for ((x=1;x<=100;x++)); do cat OLA1-input.txt | ./random_board $x 100 | ./a-star 2 ; done | grep "V=" | cut -f2 -d'=' > a-star-2-V
echo "d:"
for ((x=1;x<=100;x++)); do cat OLA1-input.txt | ./random_board $x 100 | ./a-star 2 ; done | grep "d=" | cut -f2 -d'=' > a-star-2-d
echo "b:"
for ((x=1;x<=100;x++)); do cat OLA1-input.txt | ./random_board $x 100 | ./a-star 2 ; done | grep "b=" | cut -f2 -d'=' > a-star-2-b 
			
echo "finished a-star-2"

echo "starting a-star-1:"

echo "N:"
for ((x=1;x<=100;x++)); do cat OLA1-input.txt | ./random_board $x 100 | ./a-star 1 ; done | grep "N" | cut -f2 -d'=' > a-star-1-N
echo "V:"
for ((x=1;x<=100;x++)); do cat OLA1-input.txt | ./random_board $x 100 | ./a-star 1 ; done | grep "V" | cut -f2 -d'=' > a-star-1-V
echo "d:"
for ((x=1;x<=100;x++)); do cat OLA1-input.txt | ./random_board $x 100 | ./a-star 1 ; done | grep "d" | cut -f2 -d'=' > a-star-1-d
echo "b:"
for ((x=1;x<=100;x++)); do cat OLA1-input.txt | ./random_board $x 100 | ./a-star 1 ; done | grep "b=" | cut -f2 -d'=' > a-star-1-b 

echo "finished a-star-1"

echo "starting a-star-0:"

echo "N:"
for ((x=1;x<=100;x++)); do cat OLA1-input.txt | ./random_board $x 100 | ./a-star 0 ; done | grep "N" | cut -f2 -d'=' > a-star-0-N
echo "V:"
for ((x=1;x<=100;x++)); do cat OLA1-input.txt | ./random_board $x 100 | ./a-star 0 ; done | grep "V" | cut -f2 -d'=' > a-star-0-V
echo "d:"
for ((x=1;x<=100;x++)); do cat OLA1-input.txt | ./random_board $x 100 | ./a-star 0 ; done | grep "d" | cut -f2 -d'=' > a-star-0-d
echo "b:"
for ((x=1;x<=100;x++)); do cat OLA1-input.txt | ./random_board $x 100 | ./a-star 0 ; done | grep "b=" | cut -f2 -d'=' > a-star-0-b 

echo "finished a-star-0"

echo "pasting.."
paste a-star-0-N a-star-0-V a-star-0-b a-star-0-d > a-star-0-NVbd
paste a-star-1-N a-star-1-V a-star-1-b a-star-1-d > a-star-1-NVbd
paste a-star-2-N a-star-2-V a-star-2-b a-star-2-d > a-star-2-NVbd
paste a-star-3-N a-star-3-V a-star-3-b a-star-3-d > a-star-3-NVbd

echo "done!!"