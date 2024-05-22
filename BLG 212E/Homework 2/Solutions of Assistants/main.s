
SevenSegmentGPIO        EQU     0x20001000

						AREA     SevenSegmentCodesArea, DATA, READONLY
SevenSegmentCodes		DCB		0x3F, 0x06, 0x53, 0x4F, 0x4E, 0x6D, 0x7D, 0x07, 0x7F, 0x6F
END_SevenSegment


						AREA variables, DATA, READWRITE
IntCounter					SPACE 1					; Counts interrupts, change seven segment when it is 4 (250 ms x 1)
SevenSegmentCounter			SPACE 1					; Count seven segment number
End_Counter

				AREA main_area, CODE, READONLY
				ENTRY
				THUMB
				ALIGN


SysTick_Init	FUNCTION
				PUSH {R0-R2}					; Save the modified regiters.
				; CPU 48 MHz, Frequency 4 Hz
				; Period = (ReloadValue +1)/CPUFreq
				; ReloadValue + 1 = CPUFreq/Freq
				; ReloadValue + 1 = 48.000.000 / 4
				; ReloadValue = 11.999.999
				LDR	 R0, =0xE000E014				; Load SYST_RVR Address.
				LDR  R1, =11999999		     		; R1 = 11999999 //Reload Value.	
				STR  R1, [R0]						; Set the Reload Value Register.
				LDR	 R0, =0xE000E018				; Load SYST_CVR Address.
				MOVS R1, #0							; R1 = 0
				STR  R1, [R0]						; Clear the Current Value Register.
				LDR	 R0, =0xE000E010				; Load SYST_CSR Address.
				LDR  R1, [R0]						; Load Control and Status Register to R1.
			    MOVS R2, #7							; MOV #7 to R2.
				ORRS R1, R1, R2						; Set CLKSOURCE, TICKINT, and ENABLE flags.	
				STR  R1, [R0]						; Set the Reload Value Register to enable interrupt and timer.
				POP  {R0-R2}						; Restore saved registers and return with PC.
				BX   LR								; Return with Link Register
				ENDFUNC
				
				
				EXPORT SysTick_Handler
SysTick_Handler	FUNCTION
				LDR  R0, =IntCounter				; Load Int Counter Addresses
				LDRB R1, [R0]						; Get Int Counter Value
				ADDS R1, R1, #1						; Increase Int Counter By One
				CMP  R1, #4							; Check Int Counter is 4 (250 ms period x 4 = 1 Second)
				BLO  SysTick_Finish					; If Int Counter is lower than 4, return.
				LDR  R2, =SevenSegmentCounter		; Get Seven Segment Counter Address
				LDRB R3, [R2]						; Get Seven Segment Counter Value
				ADDS R3, R3, #1						; Increase Seven Segment Counter By One
				CMP	 R3, #10						; Check Seven Segment Reach the 10 
				BNE  SysTick_Cont					; Jump Continue Label if it is not equal to 10
				MOVS R3, #0							; Otherwise set as 0
SysTick_Cont    STRB R3, [R2]						; Store Seven Segment Counter For Next Interrupt
				LDR  R2, =SevenSegmentCodes			; Get Seven SegmentCodes First Value Address
				LDRB R4, [R2, R3]					; Get SevenSegment Code which points the SevenSegmentCounter 
				LDR  R2, =SevenSegmentGPIO			; Get SevenSegment GPIO Output Register Addresses
				STRB R4, [R2, #1]						; Store the seven segment code to Output Register to change number
				MOVS R1, #0							; Clear Int Counter
SysTick_Finish  STRB R1, [R0]						; Store Int Counter
				BX	LR								; Return with link register
				ENDFUNC
				
				
				EXPORT __main
__main			FUNCTION
				MOVS R1, #0							; Clear R1
				LDR  R0, =IntCounter				; Get Int Counter Value
				STRB R1, [R0]						; Clear Int Counter
				LDR  R0, =SevenSegmentCounter		; Get Seven Segment Counter Value
				STRB R1, [R0]						; Clear Seven Segment Counter
				LDR  R2, =SevenSegmentCodes			; Get Seven SegmentCodes First Value Address
				LDRB R1, [R2]						; Get the first seven segment code (0)
				LDR  R2, =SevenSegmentGPIO          ; Get SevenSegment GPIO Output Register Addresses
				STRB  R1, [R2, #1]						; Store the seven segment code to Output Register to set as 0
				BL   SysTick_Init					; Configure System Tick Timer
loop			B    loop							; Creates infinite loop to wait int.
				ALIGN
				ENDFUNC
				END
				
				
				