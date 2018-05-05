;.MODEL SMALL
.STACK 100h
.DATA

X DB 5
Y DB 7
Z DB 1


LIST1 DB 5,-5,7,3,8,-1
LIST1_LEN DW ($-LIST1)

ARR DW 11,45,46,55,95
LEN DW ($-ARR)/2
KEY EQU 46
ARR2 DB 35,78,90
MSG1 DB 'KEY IS FOUND AT'
RES DB " POSITION",13,10,"$"
MSG2 DB 'KEY NOT FOUND!!!!!!!!!!!!!. $'

.CODE




;INCLUDE C:/users/subangkar/Desktop/Microprocessor/Assembly/Offline-03/Dec16bitInput.asm

;INCLUDE C:/users/subangkar/Desktop/Microprocessor/Assembly/Offline-03/Dec16bitOutput.asm

INCLUDE C:/users/subangkar/Desktop/Microprocessor/Assembly/Offline-03/SelectionSort.asm

;INCLUDE C:/users/subangkar/Desktop/Microprocessor/Assembly/Offline-03/ProcUtils.asm




OUTDEC PROC
; this procedure will display a decimal number
; input : AX
; output : none
; uses : MAIN

  PUSH BX                        
  PUSH CX                        
  PUSH DX                        

  CMP AX, 0                      ; compare AX with 0
  JGE @START                     ; jump to label @START if AX>=0

  MOV DL, "-"                    ; set DL=\'-\'
  CALL printByteIn_DL

  NEG AX                         ; take 2\'s complement of AX

  @START:                        ; jump label

    XOR CX, CX                     ; CX counts number of digits
    MOV BX, 10                     ; set BX=10

  @OUTPUT:                       
    XOR DX, DX                   ; clear DX
    DIV BX                       ; divide AX by BX
    PUSH DX                      ; push DX onto the STACK
    INC CX                       
    OR AX, AX                    ; take OR of Ax with AX
    JNE @OUTPUT                    ; jump to label @OUTPUT if ZF=0

  MOV AH, 2                      ; set output function

  @DISPLAY:                      
    POP DX                       
    OR DL, 30H                   ; convert decimal to ascii code
    INT 21H                      
    LOOP @DISPLAY                  ; jump to label @DISPLAY if CX!=0

  POP DX                         
  POP CX                         
  POP BX                         

  RET                           
OUTDEC ENDP









PRINT_INT_DW_ARRAY PROC
; this procedure will display a list of decimal numbers
;input: SI = array offset address
;       CX = number of elements
; output : none
; uses : OUTDEC

    PUSH AX
    PUSH CX
    PUSH DX
    PUSH SI
    
    @PRINT_INT_DW_ARRAY_PRINT:
        MOV AX,[SI]
        CALL OUTDEC
        INC SI
        INC SI

        ;print a space
        MOV DL, ' '
        MOV AH,2
        INT 21h
    LOOP @PRINT_INT_DW_ARRAY_PRINT

    POP SI
    POP DX
    POP CX
    POP AX
PRINT_INT_DW_ARRAY ENDP






; prints the Byte in DL
printByteIn_DL proc
    PUSH AX

    MOV AH,2
    INT 21h

    POP AX    
    RET
printByteIn_DL endp


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

    MOV CX,5
    LEA SI,ARR
    CALL PRINT_INT_DW_ARRAY


    ;MOV AX,[DI]
    MOV DL,[SI]
    call printByteIn_DL


main endp

end main