// PRUSS program to drive a HC-SR04 sensor and store the output in memory
// that can be read by a Linux userspace program when an interrupt is sent
// Writen by Derek Molloy for the book Exploring BeagleBone

.origin 0               // offset of start of program in PRU memory
.entrypoint START       // program entry point used by the debugger

#define TRIGGER_PULSE_US    10
#define INS_PER_US          200
#define INS_PER_LOOP        2
#define TRIGGER_COUNT       (TRIGGER_PULSE_US * INS_PER_US) / INS_PER_LOOP
#define SAMPLE_DELAY_1MS    (1000 * INS_PER_US) / INS_PER_LOOP
#define PRU0_R31_VEC_VALID  32;
#define PRU_EVTOUT_0	    3
#define PRU_EVTOUT_1	    4

// Using register 0 for all temporary storage (reused multiple times)
START:
   // Read number of samples to read and inter-sample delay
   MOV    r0, 0x00000000        //load the memory location, number of samples
   LBBO   r1, r0, 0, 4          //load the value into memory - keep r1
   // Read the sample delay
   MOV    r0, 0x00000004        //the sample delay is in the second 32-bits
   LBBO   r2, r0, 0, 4          //the sample delay is stored in r2
mov r5,0
MAINLOOP:
//   MOV    r0, TRIGGER_COUNT     //store length of the trigger pulse delay
  // SET    r30.t5                //set the trigger high

//TRIGGERING:                     // delay for 10us
  // SUB    r0, r0, 1             // decrement loop counter
   //QBNE   TRIGGERING, r0, 0     // repeat loop unless zero
   //CLR    r30.t5                // 10us over, set the triger low - pulse sent
   // clear the counter and wait until the echo goes high
   MOV    r3, 0                 // r3 will store the echo pulse width
   
   //wait p928 till high
   WBS    r31.t3                // wait until the echo goes high

   // start counting (measuring echo pulse width)  until the echo goes low
	wbc r31.t2
COUNTING:
   wbc 	r31.t2
   ADD    r3, r3, 1             // increment the counter by 1
   QBBS   COUNTING, r31.t3      // loop if the echo is still high
	
	 WBC    r31.t3
	 wbc r31.t2
COUNTINGLOW:
   // at this point the echo is now low - write the value to shared memory
	wbc r31.t2
	ADD R3,R3,1
	QBBC COUNTINGLOW,R31.t3
	///wbs
	/// WBS    r31.t3
	///wbs r31.t2

/*COUNTINGLOWS:
   // at this point the echo is now low - write the value to shared memory
	wbs r31.t2
	ADD R3,R3,1
	QBBC COUNTINGLOWS,R31.t3*/
	///////////////

   MOV    r0, 0x00000008        // going to write the result to this address
   SBBO   r3, r0, 0, 4          // store the count at this address
//////////////////////////////////////////////////////////////////P927
MOV    r3, 0                 // r3 will store the echo pulse width
   WBS    r31.t5                // p927 wait until the echo goes high
  wbc r31.t2
COUNTINGP927:
	wbc r31.t2
   ADD    r3, r3, 1             // increment the counter by 1
   QBBS   COUNTINGP927, r31.t5      // loop if the echo is still high
WBC R31.t5
wbc r31.t2
COUNTINGLOWP927:
   // at this point the echo is now low - write the value to shared memory
	wbc r31.t2
        ADD R3,R3,1
        QBBC COUNTINGLOWP927,R31.t5
 
////////////////////////////////////////////////////////////////////////
	MOV r0, 0x0000000c
	SBBO r3,r0,0,4
/////////////////////////////////////////////////p929
	mov r3,0
	wbc r31.t1
	wbc r31.t2
COUNTINGP929:
	wbc r31.t2
   ADD    r3, r3, 1             // increment the counter by 1
	
   QBBS   COUNTINGP929, r31.t1      // loop if the echo is still high
        wbc r31.t1
	wbc r31.t2
COUNTINGLOWP929:
   // at this point the echo is now low - write the value to shared memory
	wbc r31.t2
        ADD R3,R3,1
        QBBC COUNTINGLOWP929,R31.t1
        ///wbs
       /* 	wbs r31.t2
COUNTINGP929S:
	wbs r31.t2
   ADD    r3, r3, 1             // increment the counter by 1
	
   QBBS   COUNTINGP929S, r31.t1      // loop if the echo is still high
	wbs r31.t2
COUNTINGLOWP929S:
   // at this point the echo is now low - write the value to shared memory
	wbs r31.t2
        ADD R3,R3,1
        QBBC COUNTINGLOWP929S,R31.t1 */
////////////////////////////////////////////////////////////////////////
        MOV r0, 0x00000010
        SBBO r3,r0,0,4
////////////////////////////////////////////////p930
        mov r3,0
	wbc r31.t2
COUNTINGP931:
	wbc r31.t2
   ADD    r3, r3, 1             // increment the counter by 1
   QBBS   COUNTINGP931, r31.t2      // loop if the echo is still high
	wbc r31.t2
COUNTINGLOWP931:
   // at this point the echo is now low - write the value to shared memory
	wbc r31.t2
        ADD R3,R3,1
        QBBC COUNTINGLOWP931,R31.t2
        /////wbs
    /*    wbs r31.t2
COUNTINGP931S:
	wbs r31.t2
   ADD    r3, r3, 1             // increment the counter by 1
   QBBS   COUNTINGP931S, r31.t2      // loop if the echo is still high
	wbs r31.t2
COUNTINGLOWP931S:
   // at this point the echo is now low - write the value to shared memory
	wbs r31.t2
        ADD R3,R3,1
        QBBC COUNTINGLOWP931S,R31.t2*/
////////////////////////////////////////////////////////////////////////
        MOV r0, 0x00000014
        SBBO r3,r0,0,4


////////////////////////////////update sample no into memory
add r5,r5,1
 MOV r0, 24
        SBBO r5,r0,0,4
////////////////////////////////

   // one more sample iteration has taken place
   SUB    r1, r1, 1             // take 1 away from the number of iterations
   MOV    r0, r2                // need a delay between samples

SAMPLEDELAY:			// do this loop r2 times (1ms delay each time)
   SUB    r0, r0, 1             // decrement counter by 1
   MOV	  r4, SAMPLE_DELAY_1MS  // load 1ms delay into r4

DELAY1MS:
   SUB	  r4, r4, 1             
   QBNE   DELAY1MS, r4, 0       // keep going until 1ms has elapsed
   QBNE   SAMPLEDELAY, r0, 0    // repeat loop unless zero
   // generate an interrupt to update the display on the host computer
   MOV R31.b0, PRU0_R31_VEC_VALID | PRU_EVTOUT_1
   QBNE   MAINLOOP, r1, 0       // loop if the no of iterations has not passed

END:
   MOV R31.b0, PRU0_R31_VEC_VALID | PRU_EVTOUT_0
   HALT



