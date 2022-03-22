#!/bin/bash

# Check if we have enough arguments
usage="Usage: ./grade.sh <filename>"

if [[ $# -eq 0 ]]; then
  echo $usage
elif [[ $# -gt 1 ]]; then
  echo $usage
fi
# Delete temporary files
rm ./ref/*.out
echo "all files removed"
# Compile the reference program
gcc ./ref/*.c -o ./ref/$1
# Generate reference output files
max=0
for f in ./ref/*.in
do
    ./ref/$1 < $f > $f.out
    let max=max+1
done
# Now mark submissions

#
# Note: See Lab02Qn.pdf for format of output file. Marks will be deducted for missing elements.
#

# Iterate over every submission directory
processed=0
echo -e "Test date and time: $(date +"%A, %e %B %Y, %T") \n" > results.out

for folder in ./subs/*
do  
    name="$(basename $folder)"
    score=0
    let entries=entries+1
    # Compile C code
    gcc $folder/*.c -o $folder/$1 2> compile_errors.out
    # Print compile error message to output file
    if [[ $? -ne 0 ]]; then
      echo "Directory $name has a compile error." >> results.out
    else
    # Generate output from C code using *.in files in ref
      for f in ./ref/*.in
      do
        $folder/$1 < $f > $f.student.out
    # Compare with reference output files  and award 1 mark if they are identical
        if [[ $(diff $f.student.out $f.out) == "" ]]; then #no difference
          let score=score+1
        fi
      done
    fi
# print score for student
    echo "Directory $name score $score / $max" >> results.out
    let processed=processed+1
done
# print total files marked.
echo -e "\nProcessed $processed files." >> results.out
   
