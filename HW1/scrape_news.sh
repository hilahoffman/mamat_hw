
#!bin/bash

wget https://www.ynetnews.com/category/3082
cat 3082 | grep -E -o "https://www.ynetnews.com/article/[0-9a-zA-Z]{9}" | sort | uniq > links.txt #makes a file with 60 links
count=$(cat links.txt | wc -l) # the number of linkes
echo $count >> results.csv
for (( i=1; i<=count; i++ )); do
curr_link=$(cat links.txt | head -n $i | tail -n 1)
wget -O curr $curr_link
Bennett_count=$(cat curr | grep -E -o Bennett | wc -l)
Netanyahu_count=$(cat curr | grep -E -o Netanyahu | wc -l)
if (( Bennett_count==0 && Netanyahu_count==0 )); then
echo $curr_link, - >> results.csv
else
echo $curr_link, Bennett, $Bennett_count, Netanyahu, $Netanyahu_count >> results.csv
fi
done


