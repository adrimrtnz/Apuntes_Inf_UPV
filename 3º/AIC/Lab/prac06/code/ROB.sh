DIR=pruebas_rob

if [ -d "./$DIR" ];
then
    echo "$DIR directory existst."
else
    mkdir $DIR
    echo "$DIR directory created."
fi

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

