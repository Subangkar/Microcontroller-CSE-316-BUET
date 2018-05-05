.MODEL BIG
.STACK 100h
.DATA

ARR DW 11,45,46,55,95
LEN DW ($-ARR)/2

L DB 5,4,3,2,1

.CODE




INCLUDE C:/users/subangkar/Desktop/Microprocessor/Assembly/Offline-03/Dec16bitInput.asm

INCLUDE C:/users/subangkar/Desktop/Microprocessor/Assembly/Offline-03/Dec16bitOutput.asm

;INCLUDE C:/users/subangkar/Desktop/Microprocessor/Assembly/Offline-03/SelectionSort.asm

;INCLUDE C:/users/subangkar/Desktop/Microprocessor/Assembly/Offline-03/ProcUtils.asm

;INCLUDE C:/users/subangkar/Desktop/Microprocessor/Assembly/Offline-03/PRINTIntArray.asm

;INCLUDE C:/users/subangkar/Desktop/Microprocessor/Assembly/Offline-03/scanIntArray.asm








INCLUDE C:/users/subangkar/Desktop/Microprocessor/Assembly/Offline-03/printIntArray.asm





ABC PROC
   RET
ABC ENDP


main proc

    ; initialize Data Segment = AX
    MOV AX,@DATA
    MOV DS,AX

    ;MOV AX,WORD PTR Y

    ;LEA DI,LIST1

    ;INC DI
    ;INC DI
    ;INC DI

    ;LEA SI,LIST1
    ;MOV BX,6
    
    ;call SELECT




    call INDEC

    call OUTDEC


end main

