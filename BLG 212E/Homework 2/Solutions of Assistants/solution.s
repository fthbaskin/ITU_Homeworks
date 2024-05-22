SIZE			EQU 	20					;ELEMENT SIZE
INT_SIZE		EQU		4					;INTEGER BYTE SIZE
MEM_SIZE		EQU 	SIZE*INT_SIZE		;array memory size

				AREA HW2_SOL, CODE, readonly
				ENTRY
				THUMB
				ALIGN
__main			FUNCTION
				EXPORT __main					
				LDR 	R0, =array			;R0 = &array
				MOVS 	R1, #SIZE			;R1 = SIZE
				BL 		defineNumbers		;defineNumbers(&array, SIZE)				
				LDR 	R0, =array			;R0 = &array; define Numbers changed R0-R3 values, we could also push them before calling defineNumbers and pop them after
				MOVS 	R1, #0				;R1 = 0 						
				MOVS 	R2, #SIZE			;R2 = SIZE
				SUBS 	R2, #1				;R2 = R2 - 1 = SIZE - 1
				BL 		quickSort			;quickSort(&array, 0, SIZE - 1)				
stop			B 		stop											
				ENDFUNC
										
quickSort		FUNCTION					;quickSort(int arr[], int l, int h), quickSort(R0, R1, R2)
				PUSH 	{LR}				;we need to push LR because we use BL instruction inside this function											
				CMP 	R1, R2				;compare l and h
				BGE 	quickReturn			;if l >= h, return
				PUSH 	{R0-R2}				;push R0, R1, R2 because partition function can use R0-R3 freely but after partition return we need them as unchanged to call quickSort recursively
				BL 		partition			;p_index = partition(R0, R1, R2); R0 = p_index 
				MOV 	R3, R0				;R3 = p_index
				POP 	{R0-R2}				;pop R0, R1, R2				
				PUSH	{R0-R3}				;now we also want to store the p_index value
				MOV 	R2, R3				;R2 = p_index
				SUBS 	R2, R2, #1			;R2 = p_index - 1
				BL 		quickSort			;quickSort(arr, l, p_index - 1) = quickSort(R0, R1, R2)
				POP 	{R0-R3}				;pop R0, R1, R2, R3				
				MOV 	R1, R3				;p_index
				ADDS 	R1, R1, #1			;p_index + 1
				BL 		quickSort			;quickSort(arr, p_index + 1, h) = quickSort(R0, R1, R2)
quickReturn		POP 	{PC} 				;at the end we pop LR to PC register because funtion returns				
				ENDFUNC

;&arr = R0, i = R3, p = R4, j = R5, h - 1 = R6				
partition		FUNCTION					;partition(int arr[], int l, int h), partition(R0, R1, R2)->R0
				PUSH 	{LR}				;we need to push LR because of BL instruction 
				PUSH	{R4-R7}				;and R4-R7 for AAPCS
				MOVS 	R3, #4				;R3 = 4
				MULS 	R3, R2, R3			;R3 = 4*h
				MOVS 	R4, R0				;R4 = &arr
				ADDS 	R3, R4				;R3 += R4 (R3 = &arr + 4*h)
				LDR 	R4, [R3]			;R4 = arr[R3], int p = arr[h]				
				MOVS 	R3, R1				;i = l
				SUBS 	R3, R3, #1			;i = l - 1			
				MOVS 	R5, R1				;R5 = j = l
				MOVS 	R6, R2				;h
				SUBS 	R6, R6, #1			;R6 = h - 1
partitionFor	CMP 	R5, R6				;for(R5 < = R6), for(j <= h - 1)
				BGT		endPartitionFor
				MOVS	R7, #4				;R7 = 4
				MULS	R7, R5, R7			;R7 = 4*j
				ADDS	R7, R7, R0			;R7 = &arr + 4*j
				LDR		R1, [R7]			;R1 = arr[j]
				CMP		R1, R4				;arr[j] < p?
				BGE		contPartition		;if not continue
				ADDS	R3, #1				;else increment i and call swap
				PUSH	{R4}				;we will use R0 and R1 to call swapElements
				MOVS	R4, R0				;R4 = &arr
				MOVS	R0, #4				;R0 = 4
				MULS	R0, R3, R0			;R0 = i*4
				ADDS	R0, R4				;R0 = &arr + i*4
				MOVS	R1, #4				;R1 = 4
				MULS	R1, R5, R1			;R1 = j*4
				ADDS	R1, R4				;R1 = &arr + j*4
				PUSH	{R3}				;swapElements uses R3, so we store it first
				BL		swapElements		;swapElements(arr[i], arr[j=h]), swapElements(R0,R1)
				POP		{R3}				;pop R3 = i
				MOVS	R0,	R4				;R0 = &arr
				POP		{R4}				;R4 = p
contPartition	ADDS	R5, #1				;increment i
				B 		partitionFor
endPartitionFor ADDS	R3, #1				;increment i and call swap	
				PUSH	{R4}				;we will use R0 and R1 to call swapElements
				MOVS	R4, R0				;R4 = &arr
				MOVS	R0, #4				;R0 = 4
				MULS	R0, R3, R0			;R0 = i*4
				ADDS	R0, R4				;R0 = &arr + i*4
				MOVS	R1, #4				;R1 = 4
				MULS	R1, R5, R1			;R1 = j*4, (j=h right now)
				ADDS	R1, R4				;R1 = &arr + j*4
				PUSH	{R3}				;swapElements uses R3, so we store it first
				BL		swapElements		;swapElements(arr[i], arr[j=h]), swapElements(R0,R1)
				POP		{R3}				;pop R3 = i
				MOVS	R0,	R3				;return R0 = i+1 = R3
				POP		{R4}				;R4 = p
				POP		{R4-R7}				;pop used registers
				POP		{PC}				;return
				ENDFUNC							
				
defineNumbers	FUNCTION					;defineNumbers(int arr[], int size), defineNumbers(R0, R1)
				PUSH 	{R4}				;we will need an extra regsiter, we can use R4 so we should push it (R0-R3,R12 free to use in AAPCS)
				MOVS 	R2, #0 				;i = 0
				MOVS 	R3, #0 				;temp
defineFor		CMP 	R2, R1				;comparison inside for loop
				BGE 	endFor 				;i >= size -> exit loop		
				MOVS 	R4, R2			    ;R4 = i	;ADDS Rd, Rn, #<imm> works for imm range 0-7, so we use extra register for summation
				ADDS 	R4, R4, #15			;R4 = i + 15
				MOVS 	R3, R4				;temp = i + 15
				LSLS 	R4, R4, #5			;R4 = R4 << 5
				EORS 	R3, R3, R4			;temp ^= R4
				MOVS 	R4, R3				;R4 = temp 
				LSRS 	R4, R4, #4			;R4 = R4 >> 4
				EORS 	R3, R3, R4			;temp ^= R4
				MOVS 	R4, R3				;R4 = temp
				LSLS 	R4, R4, #1			;R4 = R4 << 1
				EORS 	R3, R3, R4			;temp ^= R4
				STR 	R3, [R0]			;arr[i] = temp
				ADDS 	R2, R2, #1			;i++
				ADDS 	R0, R0, #4			;arr = arr+1 (we add 4 because integer is 4 byte)
				B 		defineFor			;continue
endFor			POP 	{R4}				;pop R4 before exit
				BX 		LR					;return
				ENDFUNC

swapElements	FUNCTION					;swapElements(int* first, int* second), swapElements(R0, R1)
				LDR 	R2, [R0]			;temp = *first
				LDR 	R3, [R1]			;temp2 = *second
				STR 	R3, [R0]			;*first = *second
				STR 	R2, [R1]			;*second = temp
				BX  	LR					;return
				ENDFUNC	

				AREA     ARR, DATA, READWRITE		
				ALIGN	
__Array_Start
array			SPACE	MEM_SIZE			;allocate memory (byte)
__Array_End
				END					