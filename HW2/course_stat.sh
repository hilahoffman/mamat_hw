
#!bin/bash

#stage 1: number of arguments check

if [[ $# -ne 1 ]]; then
echo "Wrong number of arguments" >&2
exit
fi

#stage 2: check if a file in the pattern: xxxxxx.txt is exist 
course_num=$1
if [[ ! -e "$course_num".txt ]]; then 
echo "Course not found" >&2
exit
fi

#stage 3: if the doc exist then delete it. create a folder as requsted

if [[ -d "$course_num"_stat ]]; then
rm -r "$course_num"_stat
fi
 # criating a directory as requested
 mkdir "$course_num"_stat

 #stage 4: read *only* grades column and redarection to a file called grades.txt

 tail -n+2 "$course_num".txt |  awk '{print $2}'>"$course_num"_stat/grades.txt

 #stage 5: compile anzd run calc_statistics.c

 gcc -g -Wall calc_statistics.c -o prog.exe 
 ./prog.exe "$course_num"_stat/course_statistics.txt "$course_num"_stat/grades.txt

 #stage 6: print the file course_statistics.txt

 cat "$course_num"_stat/course_statistics.txt


