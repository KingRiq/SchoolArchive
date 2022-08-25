touch touched.txt
ln -sf /usr/share/dict/words
cat words > words.txt
sort -r words.txt | cat > output.txt
sort -r words.txt | head -5 | sort -R > output2.txt
head -5 words > first5words.txt
cat /proc/self/status | grep nonvol > nonvoluntaryswitches.txt
sort -R < words | head -5 > rand5words.txt
sort -R < words | head -5 | sort -d > randsort5words.txt
sort -R < words | grep -i ab | head -5 | sort -d > threepipes.txt
sort -R < words | grep -i ab | grep -i zz | head -5 | sort -d > fourpipes.txt
sort -R < words | grep -i ab | grep -i zz | grep ab | head -5 | sort -d > fivepipes.txt
head -5 <(sort -R words) | sort -d > randsort5wordsprocsub.txt
ls
echo Process Complete
