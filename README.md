#LBYARCH_x86toC
In partial accomplishment of the LBYARCH course. 


TO COMPILE and RUN (using cmd with cd to root folder of the project):
nasm -f win64 asmfile.asm

gcc -c cfile.c -o cfile.obj -m64

gcc cfile.obj asmfile.obj -o cfile.exe -m64

cfile.exe


Execution Time and Analysis:
## Observations
All ran 30 times.
1. **(10x10) :**
   - Execution time is negligible, reported as `0.000000` seconds.
   - Indicates the operation completes instantaneously.
     
2. **(100x100) :**
   - Execution time is `0.000033` seconds.
   - Minimal increase compared to smaller matrices.

3. **(1000x1000) :**
   - Execution time rises to `0.001033` seconds.
   - Growth in execution time aligns with the increased computational workload.
  ## Analysis

 1. Execution time increases as matrix size grows but remains manageable, suggesting good scalability.
 2. For a 100x increase in size (from 10x10 to 1000x1000), execution time grows significantly but not exponentially.
 3. Operations on smaller matrices complete almost instantaneously.


Program output (w/ correctness check):
1. **(10x10) :**
   
![image](https://github.com/user-attachments/assets/3e0d486c-6c1c-452e-b6ec-8d42434ab45d)

2. **(100x100) :**

![image](https://github.com/user-attachments/assets/7a086fe4-7c80-4a6b-96df-06c8208fd689)

3. **(1000x1000) :**

![image](https://github.com/user-attachments/assets/5a2fa27b-5fe4-4761-b838-c7ec90bb635c)


