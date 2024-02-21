#Crypto Speed Test Bench    


| * Project *                      | * Configuration *              | * NOTES *
| -----                            |-----                           | -----
| PIC32MZ\_EF\_c2\_hw.X            | PIC32MZ\_EF\_starterKit\_hw    | works - 296 Verify/Speed Tests 
|                                  |                                | ASSERT hash.out.hash.length
| -----                            |-----                           | -----
| PIC32MZ\_EF\_c2\_sw.X            | pic32mz\_ef\_starterkit\_sw    | works - 303 Verify/Speed Tests 
|ASSERT hash.out.hash.length
| -----                            |-----                           | -----
| pic32\_wifi\_curiosity\_hw.X     | pic32\_mz\_w1\_curiosity\_hw   | builds/runs/FAIL RSA
| -----                            |-----                           | -----
| pic32mz\_wifi\_curiosity\_sw.X   | pic32\_mz\_ef\_wifi\_curiosity |
| -----                            |-----                           | -----
| sam\_9x60\_ek\_sw.X              | sam\_9x60\_ek                  | works - 296 Verify/Speed Tests
|                                  |                                | ASSERT LINE 831 ../src/cryptoST/cryptoSTE_rsa.c (0 == test)
|                                  |                                | ||(test->timer && test->hash && test->name) 
|                                  |                                | Many rsa.c ASSERT
| -----                            |-----                           | -----
| sam\_9x60\_sk\_hw.X              | sam\_9x60\_sk\_hw              |
| -----                            |-----                           | -----
| sam\_a5d2\_xplained\_ultra\_hw.X | sam\_a5d2\_xplained\_ultra\_hw |
| -----                            |-----                           | -----
| sam\_a5d2\_xplained\_ultra\_sw.X | sam\_a5d2\_xplained\_ultra\_sw |
| -----                            |-----                           | -----
| sam\_e54\_xplained\_pro\_hw.X    | sam\_e54\_xplained\_pro\_hw    |
| -----                            |-----                           | -----
| sam\_e54\_xplained\_pro\_hwsw.X  | sam\_e54\_xplained\_pro\_hwsw  |
| -----                            |-----                           | -----
| sam\_e70\_xplained\_ultra\_hw.X  | sam\_e70\_xplained\_ultra\_hw  |
| -----                            |-----                           | -----
| sam\_e70\_xplained\_ultra\_sw.X  | sam\_e70\_xplained\_ultra\_sw  |
| -----                            |-----                           | -----
| sam\_l11\_xplained\_pro\_hw.X    | sam\_l11\_xplained\_pro\_hw    |
| -----                            |-----                           | -----
| sam\_l11\_xplained\_pro\_hwsw.X  | sam\_l11\_xplained\_pro\_hwsw  |
| -----                            |-----                           | -----
| sam\_l21\_xplained\_pro\_hw.X    | sam\_l21\_xplained\_pro\_hw    |
| -----                            |-----                           | -----
| sam\_l21\_xplained\_pro\_sw.X    | sam\_l21\_xplained\_pro\_sw    |
| -----                            |-----                           | -----
| sam\_rh71\_ek\_hw.X              | sam\_rh71\_ek\_hw              | builds/runs/FAIL RSA
| -----                            |-----                           | -----
| sam\_rh71\_ek\_sw.X              | sam\_rh71\_ek\_freertos        | works - 282/282 Verify/Speed Tests
| -----                            |-----                           | -----


##TEST ENVIRONMENT     
MPLAB-X: V5.30    
XC32:    V2.30    
MHC3:     V3.4.1    
CMSIS Packs: 5.6.0    
    
###H3: c:\Microchip\harmony\h3\_V360R3    
Current Time is 11/1/2021 @ 16:32 (AZ)    
    
         crypto: 0b7925c4 Martin Bowman 6 weeks ago: Branch\_v3.7.4    
                 TAG: v3.7.4    
        wolfssl: 3b5135f7c Peter Wright 1 year, 9 months ago: Branch\_v4.7.0    
                 TAG: v4.7.0    
           zlib: cacf7f1 Mark Adler 4 years, 10 months ago:     
                 TAG: v1.2.11    
cryptoApps/crypto\_apps\_speed\_test: c8f1ceb Chuck Lipari 4 hours ago: MH3-52298\_A2D2\_xUlt\_speed\_test\_210426\_CAL    
                 TAG: v3.7.1-25-gc8f1ceb    
            bsp: 7c5f246 Vishal Gandhi 8 weeks ago: Branch\_v3.10.0    
                 TAG: v3.10.0    
           core: dfb8e3059 Vishal Gandhi 7 weeks ago: Branch\_v3.10.0    
                 TAG: v3.10.0    
            csp: 6048f9018 Vishal Gandhi 7 weeks ago: Branch\_v3.10.0    
                 TAG: v3.10.0    
      dev\_packs: 748cfdb99 Vishal Gandhi 6 weeks ago: Branch\_v3.10.0    
                 TAG: v3.10.0    
            mhc: e73c265 Kathirvel K 4 months ago: Branch\_v3.8.0    
                 TAG: v3.8.0    
  mplabx\_plugin: 27043dd Kathirvel K 8 months ago: Branch\_v3.6.4    
                 TAG: v3.6.4    
            usb: 204d5f2d2 Shijas Mayan 4 weeks ago: Branch\_v3.8.1    
                 TAG: v3.8.1    
 CMSIS-FreeRTOS: 677bb7fc Vladimir Umek 1 year, 6 months ago: Branch\_10.3.1    
                 TAG: 10.3.1    
