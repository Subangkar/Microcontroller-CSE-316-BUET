;-------------------------------  INDEC  ----------------------------------;


INDEC PROC
; this procedure will read a number in decimal form
; stops @ receiving x
; input : none
; output : store binary number in AX , other READ char in DL
;           DL = 0 for space
; uses : MAIN

  PUSH BX                        
  PUSH CX                        
  ;PUSH DX                        

  JMP @READ                      

  @SKIP_BACKSPACE:               
    MOV AH, 2                      
    MOV DL, 20H                    ; set DL=\' \'
    INT 21H                        

  @READ:                         
    XOR BX, BX                     
    XOR CX, CX                     
    XOR DX, DX                     

    CALL INDEC_scanByteIn_AL                       

    CMP AL, "-"                    ; negative
    JE @MINUS                      

    CMP AL, "+"                    ; positive
    JE @PLUS                       

    JMP @SKIP_INPUT                

  @MINUS:                        
    MOV CH, 1                  ; CH=1 for - , 2 for - , 0 for nothing   
    INC CL                     ; CL=1    
    JMP @INPUT                     

  @PLUS:                         
    MOV CH, 2                      
    INC CL                         

  @INPUT:                        
    CALL INDEC_scanByteIn_AL                     

  @SKIP_INPUT:                 ; exits or ignores ws

    XOR DL, DL                   ; DL = 0
    CMP AL, ' '                  ; compare AL with CR
    JE @END_INPUT                

    XOR DL, DL                   ; DL = 0
    CMP AL, 10                  ; compare AL with \n
    JE @END_INPUT                

    XOR DL, DL                   ; DL = 0
    CMP AL, 13                  ; compare AL with \r & print new line
    JNE @NOT_PRINT_NEL_LINE
    @PRINT_NEL_LINE :
    CALL INDEC_printNewline
    JMP @END_INPUT                

    @NOT_PRINT_NEL_LINE:


    MOV DL, 'x'
    CMP AL, 'x'                  ; compare AL with CR
    JE @END_INPUT                

    XOR DL, DL                   ; DL = 0
    CMP AL, 08H                   ; compare AL with 8H
    JNE @NOT_BACKSPACE           

    CMP CH, 0                    
    JNE @CHECK_REMOVE_MINUS      

    CMP CL, 0                    
    JE @SKIP_BACKSPACE           
    JMP @MOVE_BACK               

  @CHECK_REMOVE_MINUS:         

    CMP CH, 1                    
    JNE @CHECK_REMOVE_PLUS       

    CMP CL, 1                    
    JE @REMOVE_PLUS_MINUS        

  @CHECK_REMOVE_PLUS:          

    CMP CL, 1                    
    JE @REMOVE_PLUS_MINUS        
    JMP @MOVE_BACK               

  @REMOVE_PLUS_MINUS:          ; removes +/- sign by putting ' ' there & backspace

    CALL INDEC_removeOneChar                  

    JMP @READ                  

  @MOVE_BACK:                  

    MOV AX, BX                   
    MOV BX, 10                   
    DIV BX                       ; set AX=AX/BX

    MOV BX, AX                   

    CALL INDEC_removeOneChar                    

    XOR DX, DX                   ; DX = 0
    DEC CL                       

    JMP @INPUT                   

  @NOT_BACKSPACE:              

    INC CL                       

    CMP AL, 30H                  
    JL @ERROR                    

    CMP AL, 39H                  
    JG @ERROR                    

    AND AX, 000FH                ; convert ascii to decimal code

    PUSH AX                      

    MOV AX, 10                   
    MUL BX                       ; set AX=AX*BX
    MOV BX, AX                   

    POP AX                       

    ADD BX, AX                   
    JMP @INPUT                     

  @ERROR:                        

    MOV AH, 2                      
    MOV DL, 7H                     
    INT 21H                        

    XOR CH, CH                     ; clear CH

;  @CLEAR:                        
;    MOV DL, 8H                   
;    INT 21H                      

;   CALL INDEC_removeOneChar                  
    ;   LOOP @CLEAR                    

    JMP @READ                      

  @END_INPUT:                    

    CMP CH, 1                      ; if neg
    JNE @EXIT                      
    NEG BX                         ; negate BX

  @EXIT:                         

    MOV AX, BX                     

    ;POP DX                         
    POP CX                         
    POP BX                         

  RET                            
INDEC ENDP





; take input in AL affects AX
INDEC_scanByteIn_AL proc
	; take input in AL affects AX
    MOV AH,1
    INT 21h
    RET
INDEC_scanByteIn_AL endp

; Affects AX,DL
INDEC_removeOneChar proc
    MOV AH, 2                    
    MOV DL, ' '                  ; set DL=\' \'
    INT 21H                      

    MOV DL, 8H                   
    INT 21H          
    RET            
INDEC_removeOneChar endp


; newline
INDEC_printNewline proc
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
INDEC_printNewline endp
