// The user must define CLA_C in the project linker settings if using the
// CLA C compiler
// Project Properties -> C2000 Linker -> Advanced Options -> Command File
// Preprocessing -> --define
#ifdef CLA_C
// Define a size for the CLA scratchpad area that will be used
// by the CLA compiler for local symbols and temps
// Also force references to the special symbols that mark the
// scratchpad are.
CLA_SCRATCHPAD_SIZE = 0x100;
--undef_sym=__cla_scratchpad_end
--undef_sym=__cla_scratchpad_start
#endif //CLA_C

#define Bootloader_En	0
#define UNIT_TEST_EN    0

MEMORY
{
PAGE 0 :
   /* BEGIN is used for the "boot to SARAM" bootloader mode   */
   RAMM0           	: origin = 0x000123,   length = 0x0002DD
   RAMD0           	: origin = 0x00B000,   length = 0x000800
   RAMLS0          	: origin = 0x008000,   length = 0x000800
   RAMLS1_5         : origin = 0x008800,   length = 0x002800
#if 0U == UNIT_TEST_EN
   RAMGS8_11        : origin = 0x014000,   length = 0x004000
#else
   RAMGS8_11        : origin = 0x01B000,   length = 0x001000     /* GS15 RAM */
#endif

   RESET           	: origin = 0x3FFFC0,   length = 0x000002
   /* Flash sectors */
#if 0U == UNIT_TEST_EN
#if Bootloader_En == 0
   /* BEGIN is used for the "boot to SARAM" bootloader mode   */
   FLASH_BOOTAPP	 : origin = 0x080000, length = 0x004000	/* FLASH_BANK0_SEC0~BANK0_SEC3,16K*16 */
   BEGIN             : origin = 0x084000, length = 0x000002
   FLASH_RUNAPP  	 : origin = 0x084002, length = 0x01BFFB	/* FLASH_BANK0_SEC4~BANK1_SEC1,56K*16 */
   ProdMdl           : origin = 0x09FFFD, length = 0x000001
   AppProperty       : origin = 0x09FFFE, length = 0x000002	/* App Property,  BANK1_SEC1, 2*16*/
   FLASH_BOOTRSVD	 : origin = 0x0A0000, length = 0x01C000	/* FLASH_BANK1_SEC2~BANK1_SEC15,56K*16 */
#else
   BEGIN             : origin = 0x080000, length = 0x000002
   FLASH_BOOTAPP	 : origin = 0x080002, length = 0x003FFE	/* FLASH_BANK0_SEC0~BANK0_SEC1,16K*16 */
   FLASH_RUNAPP  	 : origin = 0x084002, length = 0x01BFFC	/* FLASH_BANK0_SEC2~BANK0_SEC7,144K*16 */
   AppProperty       : origin = 0x09FFFE, length = 0x000002	/* App Property,  BANK0_SEC7,  2*16*/
   FLASH_BOOTRSVD	 : origin = 0x0A0000, length = 0x01C000	/* FLASH_BANK0_SEC8~BANK1_SEC4,160K*16 */
#endif
#else
   BEGIN             : origin = 0x080000, length = 0x000002
   FLASH_RUNAPP  	 : origin = 0x080002, length = 0x03FFFB
   ProdMdl           : origin = 0x0BFFFD, length = 0x000001
   AppProperty       : origin = 0x0BFFFE, length = 0x000002
#endif

PAGE 1 :

   BOOT_RSVD        : origin = 0x000002, length = 0x000121     /* Part of M0, BOOT rom will use this for stack */
   RAMM1            : origin = 0x000400, length = 0x0003F8     /* on-chip RAM block M1 */
#if 0U == UNIT_TEST_EN
   RAMGS0_7         : origin = 0x00C000, length = 0x008000
#else
   RAMGS0_7         : origin = 0x00C000, length = 0x00F000     /* GS0~14 RAM */
#endif

   RAMGS12          : origin = 0x018000,   length = 0x001000

   EMIF1_CS0n       : origin = 0x80000000, length = 0x10000000
   EMIF1_CS2n       : origin = 0x00100000, length = 0x00200000
   EMIF1_CS3n       : origin = 0x00300000, length = 0x00080000
   EMIF1_CS4n       : origin = 0x00380000, length = 0x00060000
   EMIF2_CS0n       : origin = 0x90000000, length = 0x10000000
   EMIF2_CS2n       : origin = 0x00002000, length = 0x00001000

   CLA1_MSGRAMLOW   : origin = 0x001480,   length = 0x000080
   CLA1_MSGRAMHIGH  : origin = 0x001500,   length = 0x000080

   CPU2TOCPU1RAM    : origin = 0x03F800,   length = 0x000400
   CPU1TOCPU2RAM    : origin = 0x03FC00,   length = 0x000400

}


SECTIONS
{
   /* Allocate program areas: */
   .cinit           : > FLASH_RUNAPP      PAGE = 0, ALIGN(8)
   .text            : > FLASH_RUNAPP      PAGE = 0, ALIGN(8)
   codestart        : > BEGIN       PAGE = 0, ALIGN(8)
   .stack           : > RAMM1       PAGE = 1
   .switch          : > FLASH_RUNAPP      PAGE = 0, ALIGN(8)

   /* Allocate uninitalized data sections: */
   Cpu1ToCpu2MsgRAM    : > CPU1TOCPU2RAM PAGE = 1
   Cpu2ToCpu1MsgRAM    : > CPU2TOCPU1RAM PAGE = 1

#if defined(__TI_EABI__)
   .init_array         : > FLASH_RUNAPP,   PAGE = 0, ALIGN(8)
   .bss                : > RAMGS0_7,       PAGE = 1
   .bss:output         : > RAMGS0_7,       PAGE = 1
   .data               : > RAMGS0_7,       PAGE = 1
   .sysmem             : > RAMGS0_7,       PAGE = 1
   .const              : > FLASH_RUNAPP,   PAGE = 0, ALIGN(8)
#else
   .pinit              : > FLASH_RUNAPP,   PAGE = 0, ALIGN(8)
   .ebss               : > RAMGS0_7,	   PAGE = 1
   .esysmem            : > RAMGS0_7,       PAGE = 1
   .econst             : > FLASH_RUNAPP    PAGE = 0, ALIGN(8)
#endif

   .reset           : > RESET,     PAGE = 0, TYPE = DSECT /* not used, */

   Filter_RegsFile  : > RAMGS0_7,	   PAGE = 1
   
   .em2_cs0         : > EMIF2_CS0n, PAGE = 1
   .em2_cs2         : > EMIF2_CS2n, PAGE = 1

    /* CLA specific sections */
   #if defined(__TI_EABI__)
   		Cla1Prog    : LOAD = FLASH_RUNAPP,
                      RUN = RAMLS1_5,
                      LOAD_START(Cla1funcsLoadStart),
                      LOAD_END(Cla1funcsLoadEnd),
                      RUN_START(Cla1funcsRunStart),
                      LOAD_SIZE(Cla1funcsLoadSize),
                      PAGE = 0, ALIGN(8)
   #else
      	Cla1Prog    : LOAD = FLASH_RUNAPP,
                      RUN = RAMLS1_5,
                      LOAD_START(_Cla1funcsLoadStart),
                      LOAD_END(_Cla1funcsLoadEnd),
                      RUN_START(_Cla1funcsRunStart),
                      LOAD_SIZE(_Cla1funcsLoadSize),
                      PAGE = 0, ALIGN(8)
   #endif

   CLADataLS0		: > RAMLS0, PAGE=0
//   CLADataLS1		: > RAMLS1, PAGE=0

   Cla1ToCpuMsgRAM  : > CLA1_MSGRAMLOW,   PAGE = 1
   CpuToCla1MsgRAM  : > CLA1_MSGRAMHIGH,  PAGE = 1

   CMADataRam		: > RAMGS12,	PAGE = 1

#ifdef __TI_COMPILER_VERSION__
   #if __TI_COMPILER_VERSION__ >= 15009000
        #if defined(__TI_EABI__)
		    .TI.ramfunc : {} LOAD = FLASH_RUNAPP,
							 RUN = RAMGS8_11,
                	         LOAD_START(RamfuncsLoadStart),
                 	         LOAD_SIZE(RamfuncsLoadSize),
                 	         LOAD_END(RamfuncsLoadEnd),
                  	         RUN_START(RamfuncsRunStart),
                  	         RUN_SIZE(RamfuncsRunSize),
                   	         RUN_END(RamfuncsRunEnd),
							 PAGE = 0, ALIGN(8)
		#else
			.TI.ramfunc : {} LOAD = FLASH_RUNAPP,
							 RUN = RAMGS8_11,
                	         LOAD_START(_RamfuncsLoadStart),
                 	         LOAD_SIZE(_RamfuncsLoadSize),
                 	         LOAD_END(_RamfuncsLoadEnd),
                  	         RUN_START(_RamfuncsRunStart),
                  	         RUN_SIZE(_RamfuncsRunSize),
                   	         RUN_END(_RamfuncsRunEnd),
							 PAGE = 0, ALIGN(8)
		#endif
   #else
   ramfuncs         : LOAD = FLASH_RUNAPP,
                      RUN = RAMGS8_11,
                      LOAD_START(_RamfuncsLoadStart),
                      LOAD_SIZE(_RamfuncsLoadSize),
                      LOAD_END(_RamfuncsLoadEnd),
                      RUN_START(_RamfuncsRunStart),
                      RUN_SIZE(_RamfuncsRunSize),
                      RUN_END(_RamfuncsRunEnd),
                      PAGE = 0, ALIGN(8)
   #endif
#endif

#ifdef CLA_C
   /* CLA C compiler sections */
   //
   // Must be allocated to memory the CLA has write access to
   //
   CLAscratch       :
                     { *.obj(CLAscratch)
                     . += CLA_SCRATCHPAD_SIZE;
                     *.obj(CLAscratch_end) } >  RAMLS0,  PAGE = 0

   .scratchpad      : > RAMLS0,       PAGE = 0
   .bss_cla		    : > RAMLS0,       PAGE = 0
   .const_cla	    :  LOAD = FLASH_RUNAPP,
                       RUN = RAMLS0,
                       RUN_START(_Cla1ConstRunStart),
                       LOAD_START(_Cla1ConstLoadStart),
                       LOAD_SIZE(_Cla1ConstLoadSize),
                       PAGE = 0
#endif //CLA_C

   /* Allocate FPU math areas: */
   FPUmathTables       : > FLASH_RUNAPP,     PAGE = 0, ALIGN(8)
       /* User: */
   ProdMdl_sect     : > ProdMdl,           PAGE = 0
   AppProperty_sect : > AppProperty,       PAGE = 0

   /* The following section definitions are required when using the IPC API Drivers */
    GROUP : > CPU1TOCPU2RAM, PAGE = 1
    {
        PUTBUFFER
        PUTWRITEIDX
        GETREADIDX
    }

    GROUP : > CPU2TOCPU1RAM, PAGE = 1
    {
        GETBUFFER :    TYPE = DSECT
        GETWRITEIDX :  TYPE = DSECT
        PUTREADIDX :   TYPE = DSECT
    }
}

/*
//===========================================================================
// End of file.
//===========================================================================
*/
