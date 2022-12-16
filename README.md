# arbitrary-precision-calculator
This is one of my first projects as a computer science student, hence could be a
bit buggy. It does need a postfix converter for more diverse range of operations
and I am working on the same.
## Why arbitrary precision calculator?
A normal calculator allows operations over numbers having a limited range. It
would use the basic data types such as int, float, etc. The maximum size varies
depending on the machine in use, but what if we wish to expand these boundaries
and look calculations beyond these traditional sizes? 
BC to the rescue!
It allows us to perform basic operations over numbers of infinite lengths.
It uses doubly linked lists to store each digit of the number at a node. The
program takes the input for the equation in the form fo a string. The string is
processed iteratively until we encounter an end of string character. 
One major drawback of the technique that I have employed in this project would
be the issue caused by operator precedence. The program looks for numeric
characters and a token denoting the operation ot be performed, performs the
desired operation and stores the result in a variable. The vlaue in the variable
is then reused to perform the operation next in line. Hence, operator precednece
would not be considered for the evaluation.

## How to use this calculator?
Clone the project onto your machine and just execute ./bc on your command line
once you are present in the directory containing this code. 
```shell
./bc
```

Once you are done doing that, you can now enter your input in the usual way.
```
>>> 150000000*258945802349842+36582975025097093825
>>> 38878453327501397093825
>>> 4565.65/8
>>> 570
```


