Hi, this project is a Calculator From Infix notation to Postfix notation.
It uses implemented data structures such as, stack, dynamic array and doubly linked list.
It displays Postfix notation, every operation and lastly result.
It has additional features like MINi (takes minimum from i numbers), MAXi (takes maximum from i numbers), N (Negation), IF (a,b,c) (if a > 0 then display b, otherwise display c).
example input:
2 + MIN ( 100 , MAX ( 1 , 6 * 5 + 2 , 2 ) , 80 ,  MIN ( 66 , 36  , 35 , 77 ) , 50 , 60 ) * 3 .
output:
Postfix: 2  100  1  6  5  *  2  +  2  MAX3  80  66  36  35  77  MIN4  50  60  MIN6  3  *  +
1. '*' 5 6 1 100 2
2. '+' 2 30 1 100 2
3. MAX3 2 32 1 100 2
4. MIN4 77 35 36 66 80 32 100 2
5. MIN6 60 50 35 80 32 100 2
6. '*' 3 32 2
7. '+' 96 2
Result: 98
