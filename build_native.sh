set -e

gcc -o cc.o -c src/7.1/cc/cc.c -g -I include/ -I include/indy_stubs -D NATIVE_BUILD -D_LANGUAGE_C -DPERMUTER -w 2> errors.txt

gcc -o sex.o -c src/7.1/mld/sex.c -g -I include/ -I include/indy_stubs -I include/indy -D NATIVE_BUILD -D_LANGUAGE_C -DPERMUTER -w 2>> errors.txt

gcc -o cc_native.elf cc.o sex.o -g 2>> errors.txt
