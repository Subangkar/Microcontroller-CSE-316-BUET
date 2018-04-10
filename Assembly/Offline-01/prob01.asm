
.model small


.data

MSG DB ".....$"
MSG1 DB "Input a lowercase character: $"
MSG2 DB "The converted uppercase character is: $"

x DB 0

.code

main proc    
    
    ; initialize Data Segment = AX
    MOV AX,@DATA
    MOV DS,AX

    ; output string
    LEA DX,MSG1
    MOV AH,9
    INT 21h



    
	; take input
    MOV AH,1
    INT 21h
	MOV x,AL
    
    SUB x,32

    ; newline = AX , DX
    MOV AH,2
    MOV DL,0AH
    INT 21h   
    MOV DL,0DH
    INT 21h 


    ; output string
    LEA DX,MSG2
    MOV AH,9
    INT 21h

    MOV DL,x
    MOV AH,2
    INT 21h    
    
    
    
    
    
    mov     ah,4Ch       ;DOS function: Exit program 
    mov     al,0         ;Return exit code value 
    int     21h          ;Call DOS. Terminate program 
       
main endp    

end main


