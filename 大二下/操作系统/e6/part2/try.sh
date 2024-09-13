#! /bin/bash

gcc chat.c -o chat
gcc clean.c -o clean
for i in {1..5};do
./chat&
./chat&
done

wait
./clean
rm chat clean