; Fatih Baskin
; 150210710
				AREA     syst, CODE, READONLY
				EXPORT 	SysTick_Handler
SysTick_Handler	PROC 				; Custom SysTick_Handler ISR, which would be exported to startup file
				ADDS	R5, R5, #1 	; Incementing the counter
				BX		LR 			; Returning via interrupt exit handler
				ENDP				
				
				AREA main, CODE, READONLY
				ENTRY
				THUMB
				EXPORT	__main
				ALIGN
__main			FUNCTION 				; __main starts here
CTR_Setup		LDR 	R0, =0xE000E010 ; SysTick CSR, control and status register
				MOVS 	R1, #0 			; To clear the current value register, CVR, setting this one to 0 
				STR 	R1, [R0, #8] 	; CVR is located at 0xE000E014
				LDR	 	R1, =11999999 	; Frequency is 1hz, problem is if the system is 48 Mhz, 48e6 can't fit 24 bits, so we can only fit 12e6 , but it counts to 0 so we need 12e6 - 1
				STR 	R1, [R0, #4] 	; SYST_RVR SysTick Reload Value Register, moving 12 x 10^6 here so after each interrput flag counter starts counting down from this value
				MOVS 	R1, #7 			; 0x00000007, CSR bit0: Enable counter (1), bit1: TickInt timer generates interrupt (1), bit2: clock source processor clock (1)
				STR 	R1, [R0] 		; Move the value in R1 to address pointed by R0 to set SYST_CSR accordingly
				MOVS 	R4, #0			; R4 is the number counter, it will count up to 10 and set itself to 0 again
				MOVS 	R5, #0			; R5 is the interrupt counter, we need 4 interrupts to increment our number counter
				LDR 	R6, =LED_Nums	; R6 is used for correct LED lighting
				LDR 	R7, =0x20001000 ; PortB data out register address	
LED_Loop		CMP 	R5, #4 			; Interrupt register, if interrupt register is catched (= 4) then set R5 to 0 and increment R4
				BNE		After_R5_Chk	; If not equal to 4, skip to After_R5_Chk
				ADDS 	R4, R4, #1		; Increment R4, LED number counter 
				MOVS 	R5, #0			; Clear R5, interrupt counter
After_R5_Chk    CMP		R4, #10			; If R4 is 10 (led counter = 10) then set it to 0
				BNE		After_R4_Chk	; If not equal to 10, skip to After_R4_Chk
				MOVS 	R4, #0			; If R4 = 10, set R4 to 0
After_R4_Chk	MOVS 	R0, R4			; R0 will hold the index of the LED number,
				LSLS 	R0, R0, #2		; Shifting R0 two times, effectively multiplying by 4, to adjust index for 4-byte data type	
				ADDS 	R0, R0, R6		; Adding the address of the LED_Nums array, o get i'th element shown by index R4
				LDR		R1, [R0]		; Take the correct pin output from the address shown by R0
				LDR 	R2, [R7]		; Take the current portB data out
				LDR		R3, =0xFFFF80FF ; Mask to clear bits of R2, portB data out
				ANDS	R2, R2, R3		; Apply the clear mask				
				ORRS	R2, R2, R1		; OR with correct pin output so set correct bits.		
				STR		R2, [R7]        ; Store the new pin output.
				B		LED_Loop
				ENDFUNC ; __main ends here
				ALIGN	; Aligning word-size data below accordingly to 2-byte instruction code, below there are the inverses of 7 segment display outputs, because output pins are connected by not gates
LED_Nums		DCD 	0x00004000, 0x00007900, 0x00002400, 0x00003000, 0x00001900, 0x00001200, 0x00000200, 0x00007800, 0x00000000, 0x00001000; inverse of 7 segment numbers 0,1,2,3,4,5,6,7,8,9
				END 	; End of the file
