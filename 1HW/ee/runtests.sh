#!/bin/bash


border=10


for i in $(seq 1 1 ${border})
do
  input="./tests/input/$i.in"
  output="./tests/output/$i.out"
  solution="./tests/solutions/$i.res"


  (./a.out < ${input} ||false)>& ${output}
  if  ! cmp -s ${output} ${solution} ; then
    echo "File $i"
    echo "Input:"
    cat ${input}
    echo "Output:"
    cat ${output}
    echo "Solution:"
    cat ${solution}
    echo ""
  fi
done

