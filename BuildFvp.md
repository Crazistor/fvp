How to build the fvp?

1 download


svn checkout https://fvp.googlecode.com/svn/trunk/ fvp

2 configure:


./configure --host=arm-hismall-linux


3 build

make clean;make


4 run

mount the fvp dir mount -t nfs -o nolock hostipaddr:/home/code/fvp /mnt

cd /mnt/src/test;./meida\_play\_test