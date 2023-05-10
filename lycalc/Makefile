calc: y.tab.o lex.yy.o
        gcc -g -o calc y.tab.o lex.yy.o -ly -ll

matrix.o: matrix.c
		gcc -g -c matrix.c

y.tab.o: y.tab.c
        gcc -g -c y.tab.c

lex.yy.o: lex.yy.c
        gcc -g -c lex.yy.c

y.tab.c: calc.y
        yacc -dv calc.y

lex.yy.c: calc.l
        lex -l calc.l

clean:
        rm -rf lex.yy.* y.tab.* *.o calc