[org 0x0100]

       ;**********  INSERTION SORT  **********

   mov bx , 0               
   mov cx , [size]
   add cx , [size]
        
   mov si , 0
   mov di , 0
  
   outerLoop:
      cmp si , cx
      jnl binarySearch
      mov di , si
      add word di  ,2
      mov bx , si

      innerLoop:
         mov ax , [arr+di]
         mov dx , [arr+bx]
            
         cmp ax , dx
         jl replaceIndex
            
         return:
             add di , 2
             cmp di , cx
             jl innerLoop
             jnl swap

replaceIndex:
   mov bx , di
   jmp return
     
swap:

   mov ax , [arr+si]
   mov dx , [arr+bx]
  
   mov [arr+si] , dx
   mov [arr+bx] , ax
     
   add word si  ,2
   jmp outerLoop

         ;**********   BINARY SEARCH **********      
     
binarySearch:
     
   mov cx , [key]        ;place key in CX
   mov dx , [size]       ;place total no. of elements in AX
   add dx , [size]
   sub dx , 2
   mov [iMax] , dx
  
   mov ax , 0            ;place 0 in DX
     
main:
   mov ax , [iMin]
   mov dx , [iMax]
   cmp ax , dx
   jg exit
   jmp getMid

   search:
      mov bx , [mid]
      cmp cx , [arr+bx]
      jz positiveExit
      jg iMinIncrement
      jl iMaxDecrement

iMaxDecrement:
   mov ax , [mid]
   dec ax
   dec ax
   mov [iMax] , ax
   jmp main

iMinIncrement:
   mov ax , [mid]
   inc ax
   inc ax
   mov [iMin] , ax
   jmp main

getMid:
     
   mov ax , [iMin]
   add ax , [iMax]
     
   mov dx , 0
   cmp ax , 0
   jz midReturn
     
   division:
         
      sub ax , 4
      add dx , 2
         
      cmp ax , 1
      jz midReturn
         
      cmp ax , 2
      jz midReturn
      cmp ax , 3
      jz midReturn
     
      cmp ax , 0
      jnz division
     
   midReturn:
      mov [mid] , dx
      jmp search

positiveExit:
   mov ax , 1
   jmp exit
     
exit:
   mov ax , 0x4c00
   int 0x21

mid: dw 0
iMin: dw 0
iMax: dw 0
key: dw 1
size: dw 9                      ;size of the array
arr: dw 3,2,9,5,6,8,1,4,7       ;array