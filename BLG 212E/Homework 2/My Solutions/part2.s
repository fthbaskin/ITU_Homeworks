; Fatih Baskin
; 150210710
SIZE			EQU 0x00000032 ; 50 items
				AREA ARRAY, data, readwrite
				ALIGN
array			SPACE SIZE * 4 ; since each word is 4 byte, multiplying it by 4 to create a 50 * 4 = 200 byte space
	
				AREA main, CODE, READONLY
				ENTRY
				THUMB
				EXPORT	__main
				ALIGN
__main			FUNCTION 				; __main starts here
				LDR 	R0, =array		; Load the address of array into R0 
				MOVS 	R1, #SIZE		; Load the size of array into R1;
				BL 		defineNumbers	; Calling the function to define numbers
				LDR		R0, =array		; Load the address of array into R0 
				MOVS	R1, #0			; Load R1 such that l = 0 for function parameter
				MOVS	R2, #SIZE		; Load SIZE to r2 for function parameter
				SUBS	R2, R2, #1		; Subtracting 1 from SIZE, effectively SIZE - 1
				BL		quickSort		; Calling the quickSort function
deadLoop		B		deadLoop 		; Infinite loop (while(1)) at the en of the program 

quickSort		PUSH	{LR}			; Push link register into stack
				CMP		R1, R2			; Compare l with h 	
				BHS		qS_return		; If l >= h, don't execute the program and return directly
				PUSH	{R0-R2}			; Since we are going to call partition function with same parameters, we need to save them because they might change inside the function
				BL		partition		; Calling partition function
				MOVS	R3, R0			; Store return value into R3, p_index
				POP		{R0-R2}			; Restore values
				PUSH	{R0-R3}			; Will call this function for (int*, l, p_index - 1), so saving current variables beforegand
				MOVS	R2, R3			; h = p_index
				SUBS    R2, R2, #1		; h = h - 1; effectively h = p_index - 1;
				BL		quickSort		; Calling the function with parameters quickSort(array, l, p_index - 1)
				POP		{R0-R3}			; After function call, restoring variables from stack
				MOVS	R1, R3			; l = p_index
				ADDS 	R1, R1, #1		; l = l + 1; effectively l = p_index + 1
				BL 		quickSort		; Calling the function with parameters quickSort(array, p_index + 1, h)
qS_return		POP 	{R3}			; Pop LR into R3 to return
				BX		R3				; Return from the function


partition		PUSH	{LR}			; Firstly, storing the return address for the current function
				PUSH 	{R4}			; R4 is used for storing i 
				PUSH	{R5}			; R5 is used for storing p
				PUSH	{R6}			; R6 is used for immediate operations and int j
				PUSH	{R7}			; R7 is used for immediate operations
				LSLS	R6, R2, #2		; R6 will be used for accessing arr[h], and since each word is 4 bytes, we need to multiply h by 4 (shift left by 2), h held in R2
				ADDS	R6, R6, R0		; Adding the address of array to access right address for the arr[h]
				LDR		R5, [R6]		; The value held in arr[h] is taken into R5, effectively int p = arr[h]
				MOVS 	R4, R1			; R4 is for int i, taking l value held in R1 for int i
				SUBS	R4, R4, #1		; Subtracting 1 from i, effectively int i = l - 1;
				MOVS	R6, R1			; R6 will be used for int j, effectively int j = l
				B		prt_forLp_cmp	; Jump to comparison stage of the for loop
prt_forLp_bdy	LSLS	R3, R6, #2		; For calculating arr[j], first find 4*j (shift left by 2) because each word is 4 bytes
				ADDS	R3, R3, R0		; For calculating arr[j], adding the pointer value, effectively finding the pointer for arr[j]
				LDR		R7,	[R3]		; Taking the value of arr[j] into R7
				CMP		R7, R5			; Comparing arr[j] and R5
				BHS		prt_forLp_inc	; If arr[j] >= p, don't do the operation below, jump to increment portion of for loop, effectively if(arr[j] < p)
				ADDS 	R4, R4, #1		; Incrementing i,
				PUSH	{R0}			; For function call, we sould restore our previous calculations, so sttoring R0
				PUSH	{R1}			; Store R1
				PUSH	{R2}			; Store R2
				MOVS	R3, R0			; Taking array address into R3, because we will call swapElements function and will use R0 and R1 for passing parameters
				LSLS	R0, R6, #2		; For taking the address of arr[j], firstly 4*j (2 times left shift) must be found since each word is 4 bytes 
				ADDS	R0, R0, R3		; Adding the address of array to R0, effectively &arr[j]
				LSLS	R1, R4, #2		; For taking the address of arr[i], firstly 4*i (2 times left shift) must be found since each word is 4 bytes 
				ADDS	R1, R1, R3		; Adding the address of array to R1, effectively &arr[i]
				BL		swapElements	; Calling the function with (&arr[j], &arr[i])
				POP		{R2}			; Restore R2
				POP		{R1}			; Restore R1
				POP		{R0}			; Restore R0
prt_forLp_inc	ADDS	R6, R6, #1		; Increment j after the body of for loop
prt_forLp_cmp	cmp 	R6, R2			; Compare j and h
				BLO		prt_forLp_bdy	; If j < h, jump to body of for loop
				ADDS	R4, R4, #1		; !!! Since the function swaps with i + 1 and returning i + 1, instead of calculating them again and again, calculating i + 1 beforehand !!!
				MOVS	R3, R0			; Storing the address of array in R3 because R0 and R1 will be used for passing parameter to swapElements
				LSLS	R0, R2, #2		; For calculating the address of &arr[h], we need to calculate 4*h (left shift by 2) since each word is 4 bytes
				ADDS	R0, R0, R3		; Adding the array's address to get &arr[h]
				LSLS	R1, R4, #2		; For calculating the address of &arr[i], we need to calculate 4*h (left shift by 2) since each word is 4 bytes
				ADDS	R1, R1, R3		; Adding the array's address to get &arr[i]				
				BL 		swapElements	; calling the function with (&arr[i], &arr[h])
				MOVS	R0, R4			; For returning i (i + 1), store R4 in R0
				POP 	{R7}			; Restore R7
				POP 	{R6}			; Restore R6
				POP 	{R5}			; Restore R5
				POP 	{R4}			; Restore R4
				POP		{R3}			; Restore LR into R3
				BX 		R3				; Return from the function	

defineNumbers	PUSH 	{R4}			; This will be used for pointer arithmetic and immediate operations
				MOVS 	R2, #0			; Will use this as variable i inside for loop
				B		dN_forLp_cmp 	; After initializing i, jump to comparison part
dN_forLp_bdy	MOVS	R3, #15			; For both clearing the temp and due to limitations of instruction (3 bit immediate), first moving 15 to R3
				ADDS	R3, R3, R2		; And adding i to temp, effectively temp = i + 15
				LSLS	R4, R3, #5		; Shift temp (R3) left by 5 times then write immediate result to R4
				EORS	R3, R3, R4		; XOR immediate result with temp (R3), effectively temp ^= temp << 5
				ASRS 	R4, R3, #4		; Shift temp (R3) right by 4 times then write immediate result to R4				
				EORS 	R3, R3, R4		; XOR immediate result with temp (R3), effectively temp ^= temp >> 4
				LSLS	R4, R3, #1		; Shift temp (R3) left by 1 times then write immediate result to R4
				EORS	R3, R3, R4		; XOR immediate result with temp (R3), effectively temp ^= temp << 1						
				MOVS	R4, R2			; For pointer arithmetic, each word is 4 bytes long, each index of array corresponds to 4 bytes of incrementation
				LSLS	R4, R4, #2		; 2 times left shift means multiplying by 4, wtich is necessary for turning index into pointer	
				ADDS 	R4, R4, R0		; Adding the array pointer to calculate correct pointer, effectively arr[i]
				STR		R3, [R4]		; Storing the temp value into arr[i], effectively arr[i] = temp
				ADDS	R2, R2, #1		; Incrementing i
dN_forLp_cmp	CMP		R2, R1			; Comparing current i and size
				BLO 	dN_forLp_bdy	; If i < SIZE then jump back to body of for loop
				POP {R4}				; Restore old R4 from stack
				BX LR					; Return from the function			
				
swapElements	LDR	R2, [R0]			; Taking the value that has been stored in pointer R0
				LDR R3, [R1]			; Taking the value that has been stored in pointer R1
				STR R3, [R0]			; Storing the R1's pointed value into R0
				STR R2, [R1]			; Storing the R0's pointed value into R1
				BX LR					; Return from the function
				
				ENDFUNC ; __main ends here
				END 	; End of the file

