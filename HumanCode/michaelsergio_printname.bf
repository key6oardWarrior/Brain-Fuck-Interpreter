Prints out my name in brainfuck.

helpful counter in #0
lowercase buffer 97 to 109 in #1 
uppercase 80 'P' in #2
buffer #3 is for spaces
buffer #4 and #5 is for copy at end

+++++++++           10 in #0 to run 10 times
[                   begin multiply by 10 loop 
>++++++++++         10 in #1
>++++++++            8 in #2
<<-                 dec loop ctr in 0
]                   mult end

i have d and P in 1 and 2

>>                  Capital
---.                M 77
<                   Lower
+++++.              i 105
- -----.            c 99
+ ++++.             h 104
---- ---.           a 97
+++ +.              e 101	
+++++++.            l 108

>>                  Space Buffer (0) #3
>++++++++[<++++>-]< mult 8 4 = 32 ''
.                   32 ' ' space
<                   Upper Buffer #2 77 'M'
+++ +++.            'S' 83

<                   Lower Buffer #2 108 'l'
-------.            101 e




                    sub 13 to get to r
                    13 = 7 mult 2
                    plus 1 in #4

>>>                 Go from #1 to #4 lowercase2
                    We want 114 'r'
                    110 = 10 * 11 plus 4 
                    will work nice

>+++++++++++        11 in #5
[<++++++++++>-]     mult by 10 in #4
<++++               add 4 in #4
.                   104 'r'

<<<                 Using #1 Lowercase 101 'e'
++.                 106 'g'             
++.                 108 'i'

>>>                 #4 lowercase2 114 'r'
---.                111 'o'

                    Have some fun trying to copy #3

                    Copy space buffer to lowercase2 
[-]                 Clear lowercase2 #4
<                   From #3
[>+>+<<-]           mv #3 into #4 and #5    end in #3
>>[<<+>>-]          mv #5 back to #3 (second half of mv #1 to #4) end in #5
                    so we moved $32 into #4

<                   back from #5 to #4
+.                  inc 1 and print 33 '!' 