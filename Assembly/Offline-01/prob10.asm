
.model small


.data




.code

main proc    
             
    MOV AX,250
    MOV BX,20         
    
    MOV CX, 0
    
    ADD CX,AX
    ADD CX,BX         
             
    
    
    mov     ah,4Ch       ;DOS function: Exit program 
    mov     al,0         ;Return exit code value 
    int     21h          ;Call DOS. Terminate program 
       
main endp    

end main


