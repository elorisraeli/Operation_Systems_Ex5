# Operation_Systems_Ex5

## What is the project about:

Usages of Active Objects in pipeline that tranfer infromation between them, in this project we create 4 active objects (we name it AO in shortcut):

- First AO - generate numbers (Number of numbers is given by the user) and pass them to next AO.

- Second AO - Check if the numbers are prime, prints them and the result and pass them to next AO with addition of 11.

- Third AO - Check if the numbers are prime, prints them and the result and pass them to next AO with substruction of 13.

- Forth AO - Get the numbers, prints them and add 2 and print them again.


## How to use the project:

First step is to run all the project using Makefile. To use the Makefile you should enter the command: make

and it will generate a st_pipeline file which you could run using ./st_pipeline and with the instructions below.

Usages (what commands to run in terminal):

NUM := number of numbers to generate. 

SEED := the number of the seed to the random numbers generation (no seed means default seed = take seed from computer time)

./st_pipeline NUM [SEED]

> Examples:
> 
> - ./st_pipeline 2 
> 
> - ./st_pipeline 2 12345


In the end of use you can enter the command: make clean

which clean all the files that created in the folder for run the project.
