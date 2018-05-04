.model small

.stack 100h

.data

MSG DB ".....$"


.code

main proc    
    
    ; initialize Data Segment = AX
    MOV AX,@DATA
    MOV DS,AX
    
	; take input in AL affects AX
    MOV AH,1
    INT 21h
	;MOV CL,AL
    
    

    ; newline = AX , DL
    MOV AH,2
    MOV DL,0AH
    INT 21h   
    MOV DL,0DH
    INT 21h 
    
    
    ; output string affects AX,DX
    LEA DX,MSG
    MOV AH,9
    INT 21h


    ; newline = AX , DL
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






; take input of multiple digit decimal number<255 affects AX,DX output in DH	
MOV AL,'0'
MOV DH,0  ; DH holds all digit number	
SCAN_DIGITS:

MOV DL,AL ; DL holds last digit char
SUB DL,'0'; DL holds last digit value

MOV AL,DH
MOV AH,10
MUL AH
MOV DH,AL
ADD DH,DL
 
MOV AH,1
INT 21h

CMP AL,0DH
JNE SCAN_DIGITS