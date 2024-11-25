# lbyarch_x86toC
In partial accomplishment of the LBYARCH course. 


TO COMPILE and RUN (using cmd with cd to root folder of the project):
nasm -f win64 asmfile.asm
gcc -c cfile.c -o cfile.obj -m64
gcc cfile.obj asmfile.obj -o cfile.exe -m64
cfile.exe


Execution Time and Analysis:



Program output (w/ correctness check):
