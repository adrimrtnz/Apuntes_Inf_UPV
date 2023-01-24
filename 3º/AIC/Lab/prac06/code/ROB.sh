DIR=pruebas_rob

if [ -d "./$DIR" ];
then
    echo "$DIR directory existst."
else
    mkdir $DIR
    echo "$DIR directory created."
fi

./mips-ooo -f daxpy64.s -s -r 128 -M -p pnt > $DIR/daxpy64-v1-pnt
./mips-ooo -f daxpy64.s -s -r 128 -M -p 1 > $DIR/daxpy64-v1-p1
./mips-ooo -f daxpy64.s -s -r 128 -M -p 2s > $DIR/daxpy64-v1-p2s
./mips-ooo -f daxpy64.s -s -r 128 -M -p p > $DIR/daxpy64-v1-pp

./mips-ooo -f daxpy64.s -s -r 128 -v 2:2:2 -M -p pnt > $DIR/daxpy64-v2-pnt
./mips-ooo -f daxpy64.s -s -r 128 -v 2:2:2 -M -p 1 > $DIR/daxpy64-v2-p1
./mips-ooo -f daxpy64.s -s -r 128 -v 2:2:2 -M -p 2s > $DIR/daxpy64-v2-p2s
./mips-ooo -f daxpy64.s -s -r 128 -v 2:2:2 -M -p p > $DIR/daxpy64-v2-pp

./mips-ooo -f daxpy64.s -s -r 128 -v 4:4:4 -M -p pnt > $DIR/daxpy64-v4-pnt
./mips-ooo -f daxpy64.s -s -r 128 -v 4:4:4 -M -p 1 > $DIR/daxpy64-v4-p1
./mips-ooo -f daxpy64.s -s -r 128 -v 4:4:4 -M -p 2s > $DIR/daxpy64-v4-p2s
./mips-ooo -f daxpy64.s -s -r 128 -v 4:4:4 -M -p p > $DIR/daxpy64-v4-pp

./mips-ooo -f daxpy64.s -s -r 128 -v 8:8:8 -M -p pnt > $DIR/daxpy64-v8-pnt
./mips-ooo -f daxpy64.s -s -r 128 -v 8:8:8 -M -p 1 > $DIR/daxpy64-v8-p1
./mips-ooo -f daxpy64.s -s -r 128 -v 8:8:8 -M -p 2s > $DIR/daxpy64-v8-p2s
./mips-ooo -f daxpy64.s -s -r 128 -v 8:8:8 -M -p p > $DIR/daxpy64-v8-pp

./mips-ooo -f matmul.s -s -r 128 -M -p pnt > $DIR/matmul-v1-pnt
./mips-ooo -f matmul.s -s -r 128 -M -p 1 -b 3 > $DIR/matmul-v1-p1
./mips-ooo -f matmul.s -s -r 128 -M -p 2s -b 3 > $DIR/matmul-v1-p2s
./mips-ooo -f matmul.s -s -r 128 -M -p p > $DIR/matmul-v1-pp

./mips-ooo -f matmul.s -s -r 128 -v 4:4:4 -M -p pnt > $DIR/matmul-v4-pnt
./mips-ooo -f matmul.s -s -r 128 -v 4:4:4 -M -p 1 -b 3 > $DIR/matmul-v4-p1
./mips-ooo -f matmul.s -s -r 128 -v 4:4:4 -M -p 2s -b 3 > $DIR/matmul-v4-p2s
./mips-ooo -f matmul.s -s -r 128 -v 4:4:4 -M -p p > $DIR/matmul-v4-pp

./mips-ooo -f matmul.s -s -r 128 -v 8:8:8 -M -p pnt > $DIR/matmul-v8-pnt
./mips-ooo -f matmul.s -s -r 128 -v 8:8:8 -M -p 1 -b 3 > $DIR/matmul-v8-p1
./mips-ooo -f matmul.s -s -r 128 -v 8:8:8 -M -p 2s -b 3 > $DIR/matmul-v8-p2s
./mips-ooo -f matmul.s -s -r 128 -v 8:8:8 -M -p p > $DIR/matmul-v8-pp


./mips-ooo -f matmul.s -s -r 128 -v 2:2:2 -M -p pnt > $DIR/matmul-v2-pnt
./mips-ooo -f matmul.s -s -r 128 -v 2:2:2 -M -p 1 -b 3 >$DIR/matmul-v2-p1
./mips-ooo -f matmul.s -s -r 128 -v 2:2:2 -M -p 2s -b 3 > $DIR/matmul-v2-p2s
./mips-ooo -f matmul.s -s -r 128 -v 2:2:2 -M -p p > $DIR/matmul-v2-pp

./mips-ooo -f matmul.s -s -r 128 -v 2:2:2 -M -p 1 > $DIR/matmul-v2-r128-p1
./mips-ooo -f matmul.s -s -r 64 -v 2:2:2 -M -p 1 > $DIR/matmul-v2-r64-p1
./mips-ooo -f matmul.s -s -r 32 -v 2:2:2 -M -p 1 > $DIR/matmul-v2-r32-p1
./mips-ooo -f matmul.s -s -r 16 -v 2:2:2 -M -p 1 > $DIR/matmul-v2-r16-p1
./mips-ooo -f matmul.s -s -r 8 -v 2:2:2 -M -p 1 > $DIR/matmul-v2-r8-p1
./mips-ooo -f matmul.s -s -r 4 -v 2:2:2 -M -p 1 > $DIR/matmul-v2-r4-p1

./mips-ooo -f matmul.s -s -r 128 -v 2:2:2 -M -p p > $DIR/matmul-v2-r128-pp
./mips-ooo -f matmul.s -s -r 64 -v 2:2:2 -M -p p > $DIR/matmul-v2-r64-pp
./mips-ooo -f matmul.s -s -r 32 -v 2:2:2 -M -p p > $DIR/matmul-v2-r32-pp
./mips-ooo -f matmul.s -s -r 16 -v 2:2:2 -M -p p > $DIR/matmul-v2-r16-pp
./mips-ooo -f matmul.s -s -r 8 -v 2:2:2 -M -p p > $DIR/matmul-v2-r8-pp
./mips-ooo -f matmul.s -s -r 4 -v 2:2:2 -M -p p > $DIR/matmul-v2-r4-pp

./mips-ooo -f matmul.s -s -r 128 -v 4:4:4 -M -p 1 > $DIR/matmul-v4-r128-p1
./mips-ooo -f matmul.s -s -r 64 -v 4:4:4 -M -p 1 > $DIR/matmul-v4-r64-p1
./mips-ooo -f matmul.s -s -r 32 -v 4:4:4 -M -p 1 > $DIR/matmul-v4-r32-p1
./mips-ooo -f matmul.s -s -r 16 -v 4:4:4 -M -p 1 > $DIR/matmul-v4-r16-p1
./mips-ooo -f matmul.s -s -r 8 -v 4:4:4 -M -p 1 > $DIR/matmul-v4-r8-p1
./mips-ooo -f matmul.s -s -r 4 -v 4:4:4 -M -p 1 > $DIR/matmul-v4-r4-p1

./mips-ooo -f matmul.s -s -r 128 -v 4:4:4 -M -p p > $DIR/matmul-v4-r128-pp
./mips-ooo -f matmul.s -s -r 64 -v 4:4:4 -M -p p > $DIR/matmul-v4-r64-pp
./mips-ooo -f matmul.s -s -r 32 -v 4:4:4 -M -p p > $DIR/matmul-v4-r32-pp
./mips-ooo -f matmul.s -s -r 16 -v 4:4:4 -M -p p > $DIR/matmul-v4-r16-pp
./mips-ooo -f matmul.s -s -r 8 -v 4:4:4 -M -p p > $DIR/matmul-v4-r8-pp
./mips-ooo -f matmul.s -s -r 4 -v 4:4:4 -M -p p > $DIR/matmul-v4-r4-pp

