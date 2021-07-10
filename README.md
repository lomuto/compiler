# Compiler

## Introduction

Tiny compiler, compiles C-syntax based code with pure written data structures.

</br>

## Process

### input

![input](./images/input.PNG)

</br>

### parse variables and its initialized value with delimiters and `return` syntax

![parse](./images/parse.PNG)

</br>

### Set **Non collision** hash table with **key** for _variable's name_ and **value** for _its value_

![hash](./images/hashTable.PNG)

</br>
   
### Set infix return expression to postfix expression, then create expression tree.   
   
![infix](./images/infix.PNG) ![postfix](./images/postfix.PNG)   
   
![tree](./images/exTree.PNG)   
   
</br>
   
### compile to assembly code with assembly generator with expression tree
   
![assembly](./images/assembly.PNG)   
   
</br>
   
### process will return its calculated value to OS
   
![pcbStack](./images/pcbStack.PNG) ![rax](./images/rax.PNG)
   
![os](./images/os.PNG)   
   
</br>
   
### verify return value with `echo $?` command
   
![verify](./images/verify.PNG)
   
</br>
   
## Run
`$ compiler <code> <execute file name>`
