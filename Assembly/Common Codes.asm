
.model small


.data

MSG DB ".....$"


.code

main proc    
    
    ; initialize Data Segment = AX
    MOV AX,@DATA
    MOV DS,AX
    
	; take input
    MOV AH,1
    INT 21h
	;MOV CL,AL
    

    ; newline = AX , DX
    MOV AH,2
    MOV DL,0AH
    INT 21h   
    MOV DL,0DH
    INT 21h 
    
    
    ; output string
    LEA DX,MSG
    MOV AH,9
    INT 21h


    ; newline = AX , DX
    MOV AH,2
    MOV DL,0AH
    INT 21h   
    MOV DL,0DH
    INT 21h 
    

	
	;print a space
    MOV DL, 032
    MOV AH,2
    INT 21h
    

	
	




    
    mov     ah,4Ch       ;DOS function: Exit program 
    mov     al,0         ;Return exit code value 
    int     21h          ;Call DOS. Terminate program 
       
	
main endp    

end main


