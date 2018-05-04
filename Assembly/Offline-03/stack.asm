.stack 2h

.data

main proc

    MOV AX, 0f80h

    PUSH AX
    PUSH AX
    PUSH AX

    POP DX
    POP CX

    MOV AH,2
    INT 21h


main endp

end main