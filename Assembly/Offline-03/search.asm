
.model small


.data

MSG DB ".....$"

LIST DW 16 DUP(0)

.code

main proc    
    
    ; initialize Data Segment = AX
    MOV AX,@DATA
    MOV DS,AX
    

    
    
	
	


    
    mov     ah,4Ch       ;DOS function: Exit program 
    mov     al,0         ;Return exit code value 
    int     21h          ;Call DOS. Terminate program 
       

	
main endp    

end main










; if-else

CMP cond
JMP IFC
JMP ELSC

IFC:

JMP END_IF_ELS

ELSC:

END_IF_ELS:











; if - else if - else

CMP cond_if
JMP IFC
CMP cond_els_if
JMP ELS_IFC
JMP ELSC

IFC:

JMP END_IF_ELSIF_ELS

ELS_IFC:

JMP END_IF_ELSIF_ELS

ELSC:

END_IF_ELSIF_ELS:











; LOOP

MOV CX,n

LOOP_LABEL:

LOOP LOOP_LABEL













; REPEAT

LOOP_LABEL:

CMP cond_loop
JMP LOOP_LABEL














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
