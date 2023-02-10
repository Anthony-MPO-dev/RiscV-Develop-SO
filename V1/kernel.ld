/*  
Coloca a seção de texto no endereço 0x80000000 como espera
a VM `virt` (RISC-V) do Qemu
*/
 
OUTPUT_ARCH( "riscv" )
ENTRY( _start )
 
SECTIONS
{
    . = 0x80000000; /* contador de localização */

    /* seção de código */
    .text :
    {
    *(.text)
    }
    /* seção de dados */
    .data :
    {
    *(.data)
    }
}