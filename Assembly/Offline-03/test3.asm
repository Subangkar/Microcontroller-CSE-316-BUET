;.MODEL SMALL
.STACK 100h
.DATA

ARR DW 11,45,46,55,95
KEY DW 94

.CODE




; BIN_SEARCH PROC
;search in a sorted array by the binary search method
;input: SI = array offset address
;       BX = number of elements
;       CX = key
;output: SI = offset of sorted array
;        AX = pos @where key has been found
;uses:  
INCLUDE C:/users/subangkar/Desktop/MIC/Assembly/Offline-03/BinarySearch.asm





; OUTDEC PROC
; this procedure will display a decimal number
; input : AX
; output : none
; uses : MAIN
INCLUDE C:/users/subangkar/Desktop/MIC/Assembly/Offline-03/Dec16bitOutput.asm




main proc

    ; initialize Data Segment = AX
    MOV AX,@DATA
    MOV DS,AX

    LEA SI,ARR
    MOV BX,5
    MOV CX,KEY

    CALL BIN_SEARCH

    CALL OUTDEC


main endp

end main