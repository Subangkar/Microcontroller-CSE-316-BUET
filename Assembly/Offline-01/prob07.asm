
.model small


.data

MSG DB ".....$"
MSG1 DB "Enter 1st Number: $"
MSG2 DB "Enter 2nd Number: $"
MSG3 DB "Enter 3rd Number: $"
MSG4 DB "Enter 4th Number: $"
MSG5 DB "Sum is: $"

a DB 0
b DB 0
c DB 0
d DB 0
sum DB 0


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
	MOV a,AL

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
	MOV b,AL

    ; newline = AX , DX
    MOV AH,2
    MOV DL,0AH
    INT 21h   
    MOV DL,0DH
    INT 21h 
               
               
               
               
               
               

    ; 3rd num
    ; output string
    LEA DX,MSG3
    MOV AH,9
    INT 21h
    
	; take input
    MOV AH,1
    INT 21h
	MOV c,AL

    ; newline = AX , DX
    MOV AH,2
    MOV DL,0AH
    INT 21h   
    MOV DL,0DH
    INT 21h 
               
               
               
               
               



    
    
    SUB a,030h ; a=a-'0'
    SUB b,030h
    SUB c,030h
    
    MOV CH,0
     
    ADD CH,a
    ADD CH,b
    ADD CH,c
    ADD CH,030h
    
    MOV sum,CH         
             
             
             
             



    
    
    
             
             
             
             
             

    ; newline = AX , DX
    MOV AH,2
    MOV DL,0AH
    INT 21h   
    MOV DL,0DH
    INT 21h 



    ; output string
    LEA DX,MSG5
    MOV AH,9
    INT 21h

    MOV DL,sum
    MOV AH,2
    INT 21h     
    
    
    
    
    
    
    
    
    
    
    mov     ah,4Ch       ;DOS function: Exit program 
    mov     al,0         ;Return exit code value 
    int     21h          ;Call DOS. Terminate program 
       
main endp    

end main


