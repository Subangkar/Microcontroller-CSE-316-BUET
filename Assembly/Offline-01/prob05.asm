
.model small


.data




.code

main proc    
    
    MOV CL, 075         
             


    MOV AH,2
    MOV DL,CL
    INT 21h   
    
    
    
    mov     ah,4Ch       ;DOS function: Exit program 
    mov     al,0         ;Return exit code value 
    int     21h          ;Call DOS. Terminate program 
       
main endp    

end main


