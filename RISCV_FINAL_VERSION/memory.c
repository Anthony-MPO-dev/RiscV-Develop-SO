#include "types.h"
#include "defs_SOS.h"
#include "memlayout.h"
#include "proc.h"
#include "riscv.h"
#include "console.h"

TrapFrame trap_frame[4]; // Um para cada processador

/* 
  O extern declara  uma coisa (ela já existe em outro lugar)
  stack_end foi criado pelo linker (kernel.ld)
*/
extern char stack_end[]; 
extern char stack_start[];
extern char text_end[]; 

#define HEAP_START stack_end
#define HEAP_END (uint8*)(KERNEL_START + MEMORY_LENGTH)
#define HEAP_SIZE ((uint64)HEAP_END - (uint64)HEAP_START)
#define TEXT_SIZE (uint64)text_end - KERNEL_START
#define FREE_PAGE 0x01
#define LAST_PAGE 0x02

long total_pages; // Número total de páginas do heap
uint64 alloc_start; // Início da região aloçavel do heap

// Verificar se a página apontada por desc está livre
int
free_page(uint8 desc) {
    if(desc & FREE_PAGE) 
        return 1; // pág. livre
    return 0; //pág. ocupada
}

/* Marcar página como ocupada/desocupada. 
    Se bit 0 de desc = 1 (página livre)
    se bit 0 de desc = 0 (página ocupada)
*/
void 
set_free_page_flag(uint8 *desc, uint8 freedom){
    if(freedom) // marca pág. como livre
        *desc = *desc | FREE_PAGE;
    else
        *desc = *desc & (0xFF << 1); //marca pág. como ocupada
}

/* 
    Verificar se é a última página do bloco
    se bit 1 = 1 (última página)
*/
int 
last_page(uint8 desc) {
    if ( (desc & LAST_PAGE) != 0)
        return 1; //última página
    return 0; //não é última página
}

// Modifica flag de última página para 0 ou 1
void 
set_last_page_flag(uint8 *desc, uint8 last){
    if(last) {  
        *desc = *desc | (1 << 1);
    }
    else {
        *desc  = *desc & ( (0xFF << 2) | 1);
    }                            
}

/* 
    Arredonda o endereço para o próximo endereço múltiplo de PAGE_SIZE:
     page_round_up(4095) -> 4096
     page_round_up(5000) -> 8192   
*/
uint64 
page_round_up(uint64 addr) {
    if( (addr % PAGE_SIZE) != 0) {
        // O endereço não é múltiplo de PAGE_SIZE porque o resto da divisão não é zero
         addr = addr - (addr % PAGE_SIZE) + PAGE_SIZE;
    }
    return addr; //endereço já é múltiplo de PAGE_SIZE
}

/* 
    Arredonda o endereço para o endereço anterior múltiplo de PAGE_SIZE:
     page_round_up(4095) -> 0
     page_round_up(5000) -> 4096   
*/
uint64 
page_round_down(uint64 addr) {
    return addr - (addr % PAGE_SIZE);
}

void pages_init() {
    // Cria e inicializa descritores de páginas
    uint8 *desc = (uint8 *) HEAP_START;
    int reserved_pages;  //páginas não alocáveis (destinada aos descritores)
    total_pages = HEAP_SIZE / PAGE_SIZE; 
    reserved_pages = total_pages / PAGE_SIZE;
    if (total_pages % PAGE_SIZE) {
        reserved_pages++;
    }
    total_pages -= reserved_pages; //Total de páginas alocáveis
    // Marcar todas as páginas alocáveis como livres
    for (int i = 0; i < total_pages; i++) {
        *desc++ = FREE_PAGE;
    }
    printf("Páginas reservadas para os descritores:%d\n", reserved_pages);
    // É preciso arredondar o alloc_start para um múltiplo de PAGE_SIZE por conta
    // do subsistema de memória virtual
    alloc_start = page_round_up( (uint64)HEAP_START + reserved_pages * PAGE_SIZE ); 
}

void 
memory_init() {

    //move cursor para cima
    printf(CURSOR_TOP_LEFT);
    //limpa a tela
    printf(CLEAR_SCREEN);
    //Configuração inicial do dispositivo UART

    printf("\nCódigo:\n");
    printf("\tInício:\t %p\n", (void*)KERNEL_START);
    printf("\tFim:\t %p\n", text_end);
    printf("\tTamanho: %d bytes\n", TEXT_SIZE);

    printf("Dados: ...\n");
    printf("Pilha:\n");
    printf("\tInício:\t %p\n", stack_start);

    printf("Heap:\n");
    printf("\tInício:\t %p\n", HEAP_START);
    printf("\tFim:\t %p\n", HEAP_END);
    printf("\tTamanho: %d bytes (~%d MiB)\n", HEAP_SIZE, HEAP_SIZE/1024/1024);
    
    pages_init();
    printf("Início da região 'alocável':\t%p\n", (uint64 *) alloc_start);

  

    printf("Alocando pilha para atendimento de exceções (traps) ...\n");
    trap_frame[0].trap_stack = kalloc(1);
    trap_frame[0].trap_stack += 4096;
    trap_frame[0].hartid = 0;
    // armazenar o endereço de trap_frame no registrador mscratch
    w_mscratch((uint64)&trap_frame);

    printf("Teste de arredondamento para cima (múltiplos de PAGE_SIZE)\n");
    int n = 4096;
    printf("%d -> %d (%d) \n", n, page_round_up(n), 4096);
    n = 4095;
    printf("%d -> %d (%d) \n", n, page_round_up(n), 4096);
    n = 5000;
    printf("%d -> %d (%d)\n\n", n, page_round_up(n), 8192);

    //Testar alocação dinâmica
    int *p1 = (int*) kalloc(2);
    *p1 = 500;
    printf("p1 aponta para a posição de memória %p\n\n", p1);
    char *p2 = (char*) kalloc(1);
    printf("p2 aponta para a posição de memória %p\n\n", p2);
    *p2 = 'U';

    char *p3 = "Roncador";
     printf("p3 aponta para a posição de memória %p\n\n", p3);

    kfree(p1);
    kfree(p2);
    //kfree(p3);

   
}

void*
kalloc(int pages) {
    uint8 *ptr;
    uint8 * fp_desc = 0; //descritor da página livre encontrada
    int count = 0; // contador de páginas livres em sequência
    int i =0;
    if (pages  == 0)
        return 0; //null
    for(i = 0; i < total_pages; i++) {
        ptr = (uint8 *) HEAP_START + i;
        if(free_page(*ptr)) {
            if(count == 0) // 1ª pag. livre
                fp_desc = ptr; 

            count++;            
        }
        else {
            count = 0;
            fp_desc = 0;
        }

        if (count == pages) break;
    }

    if (count < pages) fp_desc = 0;

    
    if (fp_desc != 0) {
        //encontrou bloco solicitado
        for(i = 0; i < pages; i++){
            //Marca página como ocupada e não ultima
            set_free_page_flag(fp_desc + i, !FREE_PAGE);
            set_last_page_flag(fp_desc + i, !LAST_PAGE);
        }
        set_last_page_flag(fp_desc + (i-1), LAST_PAGE);
        //converter descritor para endereço da página que ele aponta
        int pos_desc = (uint64) fp_desc - (uint64) HEAP_START;
        printf("Páginas alocadas: %d\n", i);
        return (uint64*) (alloc_start + pos_desc * PAGE_SIZE);
    }
    return 0; // não foi possivel alocar bloco solicitado
}

void kfree(void *block){
    uint32 desc_id = (((uint64) block) - ((uint64) alloc_start))/PAGE_SIZE; // indice do descritor
    uint8 *desc = ((uint8*) (HEAP_START + desc_id)); //posição inicial do bloco
    int count = 0; // contador de páginas liberadas
    
    if (free_page(*desc)){
        printf("Block vazio");
        return;
    }
    while(!last_page(*desc)){
        set_free_page_flag(desc, FREE_PAGE);
        desc++;
        count++;
    }
    set_free_page_flag(desc, FREE_PAGE);
    set_last_page_flag(desc, !LAST_PAGE);
    count++;

    printf("\nPaginas liberadas %d\n", count);
    
}