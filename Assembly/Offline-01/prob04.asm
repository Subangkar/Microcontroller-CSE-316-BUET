
.model small


.data

MSG DB ".....$"
MSG1 DB "Enter 1st Number: $"
MSG2 DB "Enter 2nd Number: $"
MSG3 DB "You have entered: $"
MSG4 DB "After swapping: $"

.code

main proc    
    
    ; initialize Data Segment = AX
    MOV AX,@DATA
    MOV DS,AX


    ; 1st num
    ; output string
    LEA DX,MSG1
    MOV AH,9
    INT 21h
    
	; take input
    MOV AH,1
    INT 21h
	MOV CH,AL

    ; newline = AX , DX
    MOV AH,2
    MOV DL,0AH
    INT 21h   
    MOV DL,0DH
    INT 21h 


    ; 2nd num
    ; output string
    LEA DX,MSG2
    MOV AH,9
    INT 21h

	; take input
    MOV AH,1
    INT 21h
	MOV CL,AL

    ; newline = AX , DX
    MOV AH,2
    MOV DL,0AH
    INT 21h   
    MOV DL,0DH
    INT 21h 



    
    
    ; output string
    LEA DX,MSG3
    MOV AH,9
    INT 21h

    MOV DL,CH
    MOV AH,2
    INT 21h    
    
    ;print a space
    MOV DL, 032
    MOV AH,2
    INT 21h
    
    MOV DL,CL
    MOV AH,2
    INT 21h     
    
    
    
    
    MOV BH,CH
    MOV BL,CL
    
    
    ADD CH,CL ; CH=x=x+y
    
    MOV BH,CH ; BH  =x
    SUB BH,CL ; BH  =x-y
    MOV CL,BH ; CL=y=x-y
    SUB CH,CL ; CH=x=x-y
    
    
    
             
             
             
             
             

    ; newline = AX , DX
    MOV AH,2
    MOV DL,0AH
    INT 21h   
    MOV DL,0DH
    INT 21h 



    ; output string
    LEA DX,MSG4
    MOV AH,9
    INT 21h

    MOV DL,CH
    MOV AH,2
    INT 21h    
    
    ;print a space
    MOV DL, 032
    MOV AH,2
    INT 21h
    
    MOV DL,CL
    MOV AH,2
    INT 21h     
    
    
    
    
    
    
    
    
    
    
    mov     ah,4Ch       ;DOS function: Exit program 
    mov     al,0         ;Return exit code value 
    int     21h          ;Call DOS. Terminate program 
       
main endp    

end main


