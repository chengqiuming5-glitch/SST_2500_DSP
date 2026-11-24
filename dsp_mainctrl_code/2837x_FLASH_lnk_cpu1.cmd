
#ifdef CLA_C
// Define a size for the CLA scratchpad area that will be used
// by the CLA compiler for local symbols and temps
// Also force references to the special symbols that mark the
// scratchpad are.
CLA_SCRATCHPAD_SIZE = 0x100;
--undef_sym=__cla_scratchpad_end
--undef_sym=__cla_scratchpad_start
#endif //CLA_C

MEMORY
{
PAGE 0 :  /* Program Memory */
          /* Memory (RAM/FLASH) blocks can be moved to PAGE1 for data allocation */
          /* BEGIN is used for the "boot to Flash" bootloader mode   */

   BEGIN           	: origin = 0x080000, length = 0x000002
 //  BEGIN           	: origin = 0x084100, length = 0x000002
   RAMD0           	: origin = 0x00B000, length = 0x000800
   RAMLS234    	    : origin = 0x008000, length = 0x002800
   RAMGS36      	: origin = 0x00F000, length = 0x004000
   RESET           	: origin = 0x3FFFC0, length = 0x000002
   
   /* Flash sectors */
   FLASH_PROG_HEAD 	: origin = 0x084000, length = 0x100
   FILE_CHECK      	: origin = 0x084102, length = 0x00100	/* For file MD5 check */
   FLASH           	: origin = 0x084202, length = 0x23DFE	/* on-chip Flash C~H */

PAGE 1 : /* Data Memory */
         /* Memory (RAM/FLASH) blocks can be moved to PAGE0 for program allocation */

   BOOT_RSVD       : origin = 0x000002, length = 0x000120     /* Part of M0, BOOT rom will use this for stack */
   RAMM1           : origin = 0x000400, length = 0x000400     /* on-chip RAM block M1 */
   RAMD1           : origin = 0x00B800, length = 0x000800

   RAMLS5      : origin = 0x00A800, length = 0x000800

   RAMGS710      : origin = 0x013000, length = 0x004000
   RAMGS11      : origin = 0x017000, length = 0x001000
   RAMGS1215     : origin = 0x018000, length = 0x004000

   SRAM_BUF		: origin = 0x100000, length = 0x8000
   
   CPU2TOCPU1RAM   : origin = 0x03F800, length = 0x000400
   CPU1TOCPU2RAM   : origin = 0x03FC00, length = 0x000400

   CLA1_MSGRAMLOW   : origin = 0x001480, length = 0x000080
   CLA1_MSGRAMHIGH  : origin = 0x001500, length = 0x000080

   EMIF2_CS0n      : origin = 0x90000000, length = 0x10000000
}


SECTIONS
{
   /* Allocate program areas: */
   .cinit              : > FLASH      PAGE = 0, ALIGN(4)
   .pinit              : > FLASH,     PAGE = 0, ALIGN(4)
   .text               : > FLASH      PAGE = 0, ALIGN(4)
   codestart           : > BEGIN       PAGE = 0, ALIGN(4)

#ifdef __TI_COMPILER_VERSION__
   #if __TI_COMPILER_VERSION__ >= 15009000
    GROUP
    {
        .TI.ramfunc
        { -l F021_API_F2837xD_FPU32.lib}

    }                    LOAD = FLASH,
                         RUN = RAMGS36,
                         LOAD_START(_RamfuncsLoadStart),
                         LOAD_SIZE(_RamfuncsLoadSize),
                         LOAD_END(_RamfuncsLoadEnd),
                         RUN_START(_RamfuncsRunStart),
                         RUN_SIZE(_RamfuncsRunSize),
                         RUN_END(_RamfuncsRunEnd),
                         PAGE = 0, ALIGN(4)
   #else
    GROUP
    {
        ramfuncs
        { -l F021_API_F2837xD_FPU32.lib}

    }                    LOAD = FLASH,
                         RUN = RAMGS36,
                         LOAD_START(_RamfuncsLoadStart),
                         LOAD_SIZE(_RamfuncsLoadSize),
                         LOAD_END(_RamfuncsLoadEnd),
                         RUN_START(_RamfuncsRunStart),
                         RUN_SIZE(_RamfuncsRunSize),
                         RUN_END(_RamfuncsRunEnd),
                         PAGE = 0, ALIGN(4)   
   #endif
#endif
						 
   /* Allocate uninitalized data sections: */
   .stack              : > RAMM1       PAGE = 1
//   .ebss               : >> RAMD1 | RAMGS710     PAGE = 1
   .ebss               : >> SRAM_BUF     PAGE = 1
   .esysmem            : >> RAMD1 | RAMGS710     PAGE = 1
   .farbss             : > EMIF2_CS0n,  PAGE = 1

   /* Initalized sections go in Flash */
   .econst             : > FLASH      PAGE = 0, ALIGN(4)
   .switch             : > FLASH      PAGE = 0, ALIGN(4)
   .farconst           : > EMIF2_CS0n, PAGE = 1
   
   .reset              : > RESET,     PAGE = 0, TYPE = DSECT /* not used, */

   Filter_RegsFile     : > RAMGS710,	   PAGE = 1

   DATA_RAM				: > RAMGS11,	PAGE = 1

	CLADataLS5		: > RAMLS5, PAGE = 1
//	SramBuf			: > SRAM_BUF, PAGE = 1

    /* CLA specific sections */
    Cla1Prog         : LOAD = FLASH,
                      RUN = RAMLS234,
                      LOAD_START(_Cla1funcsLoadStart),
                      LOAD_END(_Cla1funcsLoadEnd),
                      RUN_START(_Cla1funcsRunStart),
                      LOAD_SIZE(_Cla1funcsLoadSize),
                      PAGE = 0, ALIGN(4)

    Cla1ToCpuMsgRAM  	: > CLA1_MSGRAMLOW,   PAGE = 1
    CpuToCla1MsgRAM  	: > CLA1_MSGRAMHIGH,  PAGE = 1

#ifdef CLA_C
   /* CLA C compiler sections */
   //
   // Must be allocated to memory the CLA has write access to
   //
   CLAscratch       :
                     { *.obj(CLAscratch)
                     . += CLA_SCRATCHPAD_SIZE;
                     *.obj(CLAscratch_end) } >  RAMLS5,  PAGE = 1

   .scratchpad      : > RAMLS5,       PAGE = 1
   .bss_cla		    : > RAMLS5,       PAGE = 1
   .const_cla	    :  LOAD = FLASH,
                       RUN = RAMLS5,
                       RUN_START(_Cla1ConstRunStart),
                       LOAD_START(_Cla1ConstLoadStart),
                       LOAD_SIZE(_Cla1ConstLoadSize),
                       PAGE = 1
#endif //CLA_C
    
}

/*
//===========================================================================
// End of file.
//===========================================================================
*/
