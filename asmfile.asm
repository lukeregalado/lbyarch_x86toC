section .data
    const255: dd 255.0                  ; 255.0 as a float

section .text
bits 64
default rel
global imgCvtGrayDoubleToInt

imgCvtGrayDoubleToInt:
    ; Function parameters:
    ; m (number of rows): rcx
    ; n (number of columns): rdx
    ; image (float*): r8
    ; int_image (int*): r9
    
    ; store total size to r10
    mov r10, rcx     

    L1:
        test r10, r10          
        jz L2                           ; if r10 = 0, exit the loop

        ; store float value to xmm0
        movss xmm0, dword [rdx] 

        ; multiply float by 255.0 
        movss xmm1, dword [const255]    ; store const255 in xmm1
        mulss xmm0, xmm1                ; xmm0 = xmm0 * 255.0
        
        roundss xmm0, xmm0, 0           ; round to nearest int

        ; Convert to integer
        cvttss2si eax, xmm0             ; convert float in xmm0 to int in eax
        mov dword [r8], eax             ; store the int value in r8

        ; increment pointers
        add rdx, 4                      ; move to the next float in image
        add r8, 4                       ; move to the next int in int_image

        ; decrement loop counter (total_size)
        dec r10
        jmp L1

    L2:
        ret
