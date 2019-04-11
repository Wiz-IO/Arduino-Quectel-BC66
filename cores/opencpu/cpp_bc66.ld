MEMORY
{
	ROM (rx) :  ORIGIN = 0x08292040, LENGTH = 0x00032000
	RAM (rwx) : ORIGIN = 0x001E7000, LENGTH = 0x00019000	
	RETSRAM (rwx) : ORIGIN = 0x4301F00, LENGTH = 256
}

SECTIONS
{
    . = 0x08292040;
	.initdata :
	{ 
	. = ALIGN(4);
		KEEP(*(.initdata));
	}AT > ROM	
	
	text : 
	{ 
	. = ALIGN(4);
        PROVIDE_HIDDEN (__preinit_array_start = .);
        KEEP( *(SORT(.preinit_array.*)) )
        KEEP( *(.preinit_init_array*) )
        PROVIDE_HIDDEN (__preinit_array_end = .);
	
        PROVIDE_HIDDEN (__init_array_start = .);
        KEEP( *(SORT(.init_array.*)) )
        KEEP( *(.init_array*) )
        PROVIDE_HIDDEN (__init_array_end = .);
        
        PROVIDE_HIDDEN (__fini_array_start = .);
        KEEP( *(SORT(.fini_array.*)) )
        KEEP( *(.fini_array*) )
        PROVIDE_HIDDEN (__fini_array_end = .);        
        
		. = ALIGN(4);
        *( .text .text.* i.* )
        *( .glue_7t )
        *( .glue_7 )
        *( .ctors )
        *( .dtors )
        *( .gnu.linkonce.t.* )
        *( .gnu.linkonce.r.* )
        *( .gcc_except_table )
        *( .rodata .rodata* .constdata* .conststring*  )
        *(.note.gnu.build-id)
        
	} AT > ROM	
	.ARM.exidx : 
	{ 
	    __exidx_start = .;
	    *(.ARM.exidx* .gnu.linkonce.armexidx.*)
	    __exidx_end = .;
	} AT > ROM	
	
	.rodata :
	{
	. = ALIGN(4);
	    *(.rodata)
	}AT > ROM
	__data_load = LOADADDR(.data);
	.data :
	{
		__data_start = .;
		. = ALIGN(4);
		*(.data.*)
		*(.data)
		_edata = .;
	} > RAM  AT > ROM
	.bss : 
	{
		__bss_start__ = .;
		. = ALIGN(4);
		*(.bss)
		*(.bss.*)
		__bss_end__ = .;
	} > RAM
	
	.sram (NOLOAD) : { *(.sram) } > RETSRAM
}