.MODEL LARGE
.STACK 1000h
.DATA

ARR DW 1,2,3,4,5
;KEY DW -7900

LIST DW 5,4,-3,2,1,-900,3457,1515,-1515,20,1,-7,0,34
LIST_LEN DW 14
KEY DW 0
POS_KEY DW 0
TERM_CHAR DB 'x'

MSG_ARR_IN DB "Enter Input Array: $"
MSG_KEY_IN DB "Enter n: $"
MSG_FOUND DB " was found in the array$"
MSG_NTFND DB " was not found in the array$"
MSG_END DB "Thank you :)$"



.code

; SCAN_INT_DW_ARRAY PROC
; this procedure will input a list of decimal numbers
; input:    SI = array offset address where to store
;           CX = number of elements at most to scan
;           AL = stop instant @ receiving @char
; output :  CX = number of elements scanned
;           SI = array offset address where to store       
; uses : INDEC
INCLUDE C:/users/subangkar/Desktop/MIC/Assembly/Offline-03/ScanIntArray.asm





; PRINT_INT_DW_ARRAY PROC
; this procedure will display a list of decimal numbers
; input:    SI = array offset address
;           CX = number of elements
; output : none
; uses : OUTDEC
INCLUDE C:/users/subangkar/Desktop/MIC/Assembly/Offline-03/PrintIntArray.asm







; newline
printNewline proc
    PUSH AX
    PUSH DX

    ; newline = AX , DL
    MOV AH,2
    MOV DL,0AH
    INT 21h   
    MOV DL,0DH
    INT 21h 

    POP DX
    POP AX
    RET
printNewline endp

printSpace proc
    PUSH AX
    PUSH DX

	;print a space
    MOV DL, ' '
    MOV AH,2
    INT 21h

    POP DX
    POP AX
    RET
printSpace endp

; LEA DX,string_var
printStringAddrIn_DX proc
    PUSH AX
    MOV AH,9
    INT 21h
    POP AX
    RET
printStringAddrIn_DX endp


returnDOS proc
    mov     ah,4Ch       ;DOS function: Exit program 
    mov     al,0         ;Return exit code value 
    int     21h          ;Call DOS. Terminate program 
    RET
returnDOS endp






main proc

    ; initialize Data Segment = AX
    MOV AX,@DATA
    MOV DS,AX

    LEA DX,MSG_ARR_IN
    call printStringAddrIn_DX

    LEA SI,LIST
    MOV CX,LIST_LEN
    MOV AL,TERM_CHAR

    CALL SCAN_INT_DW_ARRAY
    MOV LIST_LEN,CX

    MOV AX,CX
    CALL OUTDEC

    call printNewline    







    MOV CX,LIST_LEN
    CALL PRINT_INT_DW_ARRAY
    call printNewline



main endp

end main