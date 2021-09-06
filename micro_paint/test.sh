gcc micro_paint.c -o micro_paint 

max=10
for (( i=0; i <= $max; ++i ))
do
./micro_paint examples/$i > output/$i.eric
./our_micro_paint examples/$i > output/$i.ia
diff output/$i.eric output/$i.ia
done