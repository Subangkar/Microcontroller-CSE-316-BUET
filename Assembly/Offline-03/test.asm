;.MODEL SMALL
.STACK 100h
.DATA

X DB 5
Y DB 7
Z DB 1


LIST1 DB 5,-5,7,3,8,-1
LIST1_LEN DW ($-LIST1)

ARR DW 11,45,46,-55,95
LEN DW ($-ARR)/2
KEY EQU 46
ARR2 DB 35,78,90
MSG1 DB 'KEY IS FOUND AT'
RES DB " POSITION",13,10,"$"
MSG2 DB 'KEY NOT FOUND!!!!!!!!!!!!!. $'

.CODE




;INCLUDE C:/users/subangkar/Desktop/MIC/Assembly/Offline-03/Dec16bitInput.asm

;INCLUDE C:/users/subangkar/Desktop/MIC/Assembly/Offline-03/Dec16bitOutput.asm

INCLUDE C:/users/subangkar/Desktop/MIC/Assembly/Offline-03/SelectionSort.asm

;INCLUDE C:/users/subangkar/Desktop/MIC/Assembly/Offline-03/ProcUtils.asm

INCLUDE C:/users/subangkar/Desktop/MIC/Assembly/Offline-03/scanIntArray.asm

INCLUDE C:/users/subangkar/Desktop/MIC/Assembly/Offline-03/printIntArray.asm






main proc

    ; initialize Data Segment = AX
    MOV AX,@DATA
    MOV DS,AX

    ;MOV AX,WORD PTR Y

    
    ;call SELECT




    MOV CX,5
    LEA SI,ARR
    MOV AL,'x'
    ;CALL SCAN_INT_DW_ARRAY
    

    MOV AH,2
    MOV DL, 0DH
    INT 21H
    MOV DL, 0AH
    INT 21H

    MOV BX,5
    LEA SI,ARR
    CALL SELECT
    
    MOV CX,5
    CALL PRINT_INT_DW_ARRAY


    ;MOV AX,[DI]
    MOV DL,[SI]
    ;call printByteIn_DL


main endp

end main