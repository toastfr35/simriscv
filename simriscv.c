#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <capstone/capstone.h>
#include <unicorn/unicorn.h>

#define BASE_ADDRESS 0x0 // Where to load the binary
#define STOP_ADDRESS 0xc // Where to stop the emulator

// Code + Data binary
unsigned char* code_buffer;
int code_size;

uc_engine *uc; // emulator
csh handle;    // disassembler


static void show_registers_change() 
{
#define REG(_X) \
    static uint64_t _X; \
    static uint64_t p##_X; \
    uc_reg_read(uc, UC_RISCV_REG_##_X, &_X); \
    if (_X != p##_X) {printf("                                                                     " #_X " = 0x%x -> 0x%x\n", p##_X, _X);} \
    p##_X=_X;
REG(RA) REG(SP) REG(GP) REG(TP) REG(T0) REG(T1) REG(T2) REG(FP)
REG(A0) REG(A1) REG(A2) REG(A3) REG(A4) REG(A5) REG(A6) REG(A7)
REG(S0) REG(S1) REG(S2) REG(S3) REG(S4) REG(S5) REG(S6) REG(S7) REG(S8) REG(S9) REG(S10) REG(S11)
REG(T3) REG(T4) REG(T5) REG(T6)
REG(FA0) REG(FA1) REG(FA2) REG(FA3) REG(FA4) REG(FA5) REG(FA6) REG(FA7)
REG(FS2) REG(FS3) REG(FS4) REG(FS5) REG(FS6) REG(FS7) REG(FS8) REG(FS9) REG(FS10) REG(FS11) 
REG(FT8) REG(FT9) REG(FT10) REG(FT11) 
}


static void hook_instruction (uc_engine *uc, uint64_t address, uint32_t size, void *user_data)
{
    cs_insn *insn;
    show_registers_change();
    int count = cs_disasm(handle, code_buffer+address, size, address, 1, &insn);
    if (count == 1> 0) {
        printf("0x%08"PRIx64":\t%s\t\t%s\n", insn[0].address, insn[0].mnemonic, insn[0].op_str);
        cs_free(insn, count);
    }
}


static void hook_memread (uc_engine *uc, uc_mem_type type, uint64_t address, int size, int64_t value, void *user_data)
{
    uint64_t data = 0;
    uc_mem_read(uc, address, &data, size);
    printf("                                                                     ");
    printf("READ  %u bytes (0x%" PRIx64 ") @ 0x%" PRIx64 "\n", size, data, address);
}


static void hook_memwrite (uc_engine *uc, uc_mem_type type, uint64_t address, int size, int64_t value, void *user_data)
{
    printf("                                                                     ");
    printf("WRITE %u bytes (0x%" PRIx64 ") @ 0x%" PRIx64 "\n", size, value, address);
}


static void run_binary(char * filename)
{
    uc_hook trace;
    uc_open(UC_ARCH_RISCV, UC_MODE_RISCV64, &uc); // create emulator 
    uc_mem_map(uc, BASE_ADDRESS, 2 * 1024 * 1024, UC_PROT_ALL); // map 2MB memory for this emulation
    uc_mem_write(uc, BASE_ADDRESS, code_buffer, code_size); // write machine code to be emulated to memory
    uc_hook_add(uc, &trace, UC_HOOK_CODE, hook_instruction, NULL, 1, 0); // tracing all instruction
    uc_hook_add(uc, &trace, UC_HOOK_MEM_WRITE, hook_memwrite, NULL, 1, 0);  // tracing memory write
    uc_hook_add(uc, &trace, UC_HOOK_MEM_READ, hook_memread, NULL, 1, 0);   // tracing memory read
    uint64_t mstatus = 1 << 13; // for enabling floating point instructions
    uc_reg_write(uc, UC_RISCV_REG_MSTATUS, &mstatus);
    uc_err err = uc_emu_start(uc, BASE_ADDRESS, STOP_ADDRESS, 0, 0); // run
    printf ("%d\n", err);
    uc_close(uc);
}


static void load_binary(char * filename)
{
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {printf("Error opening file\n"); return;}
    fseek(file, 0, SEEK_END);
    code_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    code_buffer = (unsigned char*)malloc(code_size);
    fread(code_buffer, 1, code_size, file);
    fclose(file);
}


int main(int argc, char **argv, char **envp)
{
    cs_open(CS_ARCH_RISCV, CS_MODE_RISCVC, &handle); // open capstone disassembler
    load_binary(argv[1]);
    run_binary(argv[1]); 
    return 0;
}