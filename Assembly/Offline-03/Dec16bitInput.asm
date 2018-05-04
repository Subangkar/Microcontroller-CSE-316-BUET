;-------------------------------  INDEC  ----------------------------------;


INDEC PROC
; this procedure will read a number in decimal form
; input : none
; output : store binary number in AX
; uses : MAIN

  PUSH BX                        
  PUSH CX                        
  PUSH DX                        

  JMP @READ                      

  @SKIP_BACKSPACE:               
    MOV AH, 2                      
    MOV DL, 20H                    ; set DL=\' \'
    INT 21H                        

  @READ:                         
    XOR BX, BX                     
    XOR CX, CX                     
    XOR DX, DX                     

    CALL scanByteIn_AL                       

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
    CALL scanByteIn_AL                     

  @SKIP_INPUT:                 ; exits or ignores ws

    CMP AL, 0DH                  ; compare AL with CR
    JE @END_INPUT                

    CMP AL, 8H                   ; compare AL with 8H
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

    CALL removeOneChar                  

    JMP @READ                  

  @MOVE_BACK:                  

    MOV AX, BX                   
    MOV BX, 10                   
    DIV BX                       ; set AX=AX/BX

    MOV BX, AX                   

    CALL removeOneChar                    

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

  @CLEAR:                        
    MOV DL, 8H                   
    INT 21H                      

    CALL removeOneChar                  
    LOOP @CLEAR                    

    JMP @READ                      

  @END_INPUT:                    

    CMP CH, 1                      ; if neg
    JNE @EXIT                      
    NEG BX                         ; negate BX

  @EXIT:                         

    MOV AX, BX                     

    POP DX                         
    POP CX                         
    POP BX                         

  RET                            
INDEC ENDP





; take input in AL affects AX
scanByteIn_AL proc
	; take input in AL affects AX
    MOV AH,1
    INT 21h
    RET
scanByteIn_AL endp

; Affects AX,DL
removeOneChar proc
    MOV AH, 2                    
    MOV DL, ' '                  ; set DL=\' \'
    INT 21H                      

    MOV DL, 8H                   
    INT 21H          
    RET            
removeOneChar endp