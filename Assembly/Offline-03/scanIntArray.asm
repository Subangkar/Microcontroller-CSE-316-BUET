SCAN_INT_DW_ARRAY PROC
; this procedure will input a list of decimal numbers
; input:    SI = array offset address where to store
;           CX = number of elements at most to scan
;           AL = stop instant @ receiving @char
; output :  CX = number of elements scanned
;           SI = array offset address where to store       
; uses : INDEC
    PUSH AX
    PUSH BX
    ;PUSH CX
    PUSH DX
    PUSH SI
    
    MOV BH,AL ; store the exit char
    XOR AX,AX ; set AX=0 to count number of elements

    @PRINT_INT_DW_ARRAY_SCAN:
        
        PUSH AX ; new input will be @AX AX=count=>Stack
        
        CALL INDEC ; input => AX InvalidExitChar/ValidNumLength => DL
        XOR DL,BH ; compare with exit char & exit on matching
        JZ @END_INPUT_PRINT_INT_DW_ARRAY_SCAN
        POP AX

        @SCANNED_INTEGER:
            MOV [SI],AX 
            ;DEC CX
            INC AX

            INC SI
            INC SI
        @SCANNED_WS:            
    ;OR CX,CX
    ;CMP CX,0
    JNZ @PRINT_INT_DW_ARRAY_SCAN

    @END_INPUT_PRINT_INT_DW_ARRAY_SCAN:
        POP AX
        MOV CX,AX

        POP SI
        POP DX
        ;POP CX
        POP BX
        POP AX
    RET
SCAN_INT_DW_ARRAY ENDP




;INDEC PROC
; this procedure will read a number in decimal form
; input : none
; output : store binary number in AX , other READ char in DL
; uses : MAIN
INCLUDE C:/users/subangkar/Desktop/MIC/Assembly/Offline-03/Dec16bitInput.asm

;INCLUDE C:/users/subangkar/Desktop/MIC/Assembly/Offline-03/Dec16bitOutput.asm












