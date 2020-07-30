/* Default linker script, for normal executables */
OUTPUT_ARCH(powerpc)
SEARCH_DIR("=/usr/local/lib"); SEARCH_DIR("=/lib"); SEARCH_DIR("=/usr/lib");
ENTRY (__start)
SECTIONS
{
  .pad 0 : { *(.pad) }
  . = ALIGN (0x10000000 + SIZEOF_HEADERS, 32);
  .text   : {
    PROVIDE (_text = .);
    *(.text)
    *(.pr)
    *(.ro)
    *(.db)
    *(.gl)
    *(.xo)
    *(.ti)
    *(.tb)
    PROVIDE (_etext = .);
  }
  . = ALIGN (ALIGN (0x10000000) + (. & 0xfff), 32);
  .data . : {
    PROVIDE (_data = .);
    *(.data)
    *(.rw)
    *(.sv)
    *(.sv64)
    *(.sv3264)
    *(.ua)
    . = ALIGN(4);
    CONSTRUCTORS
    *(.ds)
    *(.tc0)
    *(.tc)
    *(.td)
    PROVIDE (_edata = .);
  }
  .bss : {
    *(.tocbss)
    *(.bss)
    *(.bs)
    *(.uc)
    *(COMMON)
    PROVIDE (_end = .);
    PROVIDE (end = .);
  }
  .loader : {
    *(.loader)
  }
  .debug : {
    *(.debug)
  }
}
