#include "sc.h"
#include "msr.h"
#include "fbconsole.h"
#include "string.h"
#include "mm.h"
#include "cpu.h"
#include "scheduler.h"
#include "pic.h"
#include "config.h"

#define GDT_ACCESSED   0x01
#define GDT_RW         0x02
#define GDT_CONFORMING 0x04
#define GDT_EXECUTE    0x08
#define GDT_SYSTEM     0x10
#define GDT_RING1      0x20
#define GDT_RING2      0x40
#define GDT_RING3      0x60
#define GDT_PRESENT    0x80

extern const char* LAST_INIT_STEP;

typedef struct {
    uint16_t baseLow;
    uint16_t selector;
    uint8_t  ist;
    uint8_t  flags;
    uint16_t baseMid;
    uint32_t baseHigh;
    uint32_t _reserved;
}__attribute__((packed)) idt_entry_t;

typedef struct {
    uint16_t   limitLow;
    uint16_t   baseLow;
    uint8_t    baseMid;
    uint8_t    type;
    uint8_t    size;
    uint8_t    baseHigh;
}__attribute__((packed)) gdt_entry_t;

typedef struct {
    uint16_t limit;
    uint64_t base;
}__attribute__((packed)) table_pointer;

idt_entry_t _idt[256];
gdt_entry_t _gdt[5];

void _setup_idt();
void _setup_gdt();
extern void _syscall_handler();
extern void reload_cs();

extern void idt_entry_0();
extern void idt_entry_1();
extern void idt_entry_2();
extern void idt_entry_3();
extern void idt_entry_4();
extern void idt_entry_5();
extern void idt_entry_6();
extern void idt_entry_7();
extern void idt_entry_8();
extern void idt_entry_9();
extern void idt_entry_10();
extern void idt_entry_11();
extern void idt_entry_12();
extern void idt_entry_13();
extern void idt_entry_14();
extern void idt_entry_15();
extern void idt_entry_16();
extern void idt_entry_17();
extern void idt_entry_18();
extern void idt_entry_19();
extern void idt_entry_20();
extern void idt_entry_21();
extern void idt_entry_22();
extern void idt_entry_23();
extern void idt_entry_24();
extern void idt_entry_25();
extern void idt_entry_26();
extern void idt_entry_27();
extern void idt_entry_28();
extern void idt_entry_29();
extern void idt_entry_30();
extern void idt_entry_31();
extern void idt_entry_32();
extern void idt_entry_33();
extern void idt_entry_34();
extern void idt_entry_35();
extern void idt_entry_36();
extern void idt_entry_37();
extern void idt_entry_38();
extern void idt_entry_39();
extern void idt_entry_40();
extern void idt_entry_41();
extern void idt_entry_42();
extern void idt_entry_43();
extern void idt_entry_44();
extern void idt_entry_45();
extern void idt_entry_46();
extern void idt_entry_47();

void init_sc() {
    _setup_idt();

    asm("mov $0xC0000080, %rcx\n"
        "rdmsr\n"
        "or $1, %rax\n"
        "wrmsr");

    write_msr(0xC0000081, 0x0018000800000000);
    write_msr(0xC0000082, (ptr_t)_syscall_handler);
}

void _set_idt_entry(int index, ptr_t base) {
    _idt[index].baseLow  = base         & 0xFFFF;
    _idt[index].baseMid  = (base >> 16) & 0xFFFF;
    _idt[index].baseHigh = base  >> 32;
    _idt[index].selector = 0x08;
    _idt[index].flags    = 0xEF;
}

void _setup_idt() {
    memset((uint8_t*)_idt, 0, sizeof(_idt));

    _set_idt_entry( 0, (ptr_t) idt_entry_0);
    _set_idt_entry( 1, (ptr_t) idt_entry_1);
    _set_idt_entry( 2, (ptr_t) idt_entry_2);
    _set_idt_entry( 3, (ptr_t) idt_entry_3);
    _set_idt_entry( 4, (ptr_t) idt_entry_4);
    _set_idt_entry( 5, (ptr_t) idt_entry_5);
    _set_idt_entry( 6, (ptr_t) idt_entry_6);
    _set_idt_entry( 7, (ptr_t) idt_entry_7);
    _set_idt_entry( 8, (ptr_t) idt_entry_8);
    _set_idt_entry( 9, (ptr_t) idt_entry_9);
    _set_idt_entry(10, (ptr_t)idt_entry_10);
    _set_idt_entry(11, (ptr_t)idt_entry_11);
    _set_idt_entry(12, (ptr_t)idt_entry_12);
    _set_idt_entry(13, (ptr_t)idt_entry_13);
    _set_idt_entry(14, (ptr_t)idt_entry_14);
    _set_idt_entry(15, (ptr_t)idt_entry_15);
    _set_idt_entry(16, (ptr_t)idt_entry_16);
    _set_idt_entry(17, (ptr_t)idt_entry_17);
    _set_idt_entry(18, (ptr_t)idt_entry_18);
    _set_idt_entry(19, (ptr_t)idt_entry_19);
    _set_idt_entry(20, (ptr_t)idt_entry_20);
    _set_idt_entry(21, (ptr_t)idt_entry_21);
    _set_idt_entry(22, (ptr_t)idt_entry_22);
    _set_idt_entry(23, (ptr_t)idt_entry_23);
    _set_idt_entry(24, (ptr_t)idt_entry_24);
    _set_idt_entry(25, (ptr_t)idt_entry_25);
    _set_idt_entry(26, (ptr_t)idt_entry_26);
    _set_idt_entry(27, (ptr_t)idt_entry_27);
    _set_idt_entry(28, (ptr_t)idt_entry_28);
    _set_idt_entry(29, (ptr_t)idt_entry_29);
    _set_idt_entry(30, (ptr_t)idt_entry_30);
    _set_idt_entry(31, (ptr_t)idt_entry_31);
    _set_idt_entry(32, (ptr_t)idt_entry_32);
    _set_idt_entry(33, (ptr_t)idt_entry_33);
    _set_idt_entry(34, (ptr_t)idt_entry_34);
    _set_idt_entry(35, (ptr_t)idt_entry_35);
    _set_idt_entry(36, (ptr_t)idt_entry_36);
    _set_idt_entry(37, (ptr_t)idt_entry_37);
    _set_idt_entry(38, (ptr_t)idt_entry_38);
    _set_idt_entry(39, (ptr_t)idt_entry_39);
    _set_idt_entry(40, (ptr_t)idt_entry_40);
    _set_idt_entry(41, (ptr_t)idt_entry_41);
    _set_idt_entry(42, (ptr_t)idt_entry_42);
    _set_idt_entry(43, (ptr_t)idt_entry_43);
    _set_idt_entry(44, (ptr_t)idt_entry_44);
    _set_idt_entry(45, (ptr_t)idt_entry_45);
    _set_idt_entry(46, (ptr_t)idt_entry_46);
    _set_idt_entry(47, (ptr_t)idt_entry_47);

    table_pointer idtp = {
        .limit = sizeof(_idt) - 1,
        .base  = (ptr_t)_idt,
    };
    asm("lidt %0"::"m"(idtp));
}

void init_gdt() {
    memset((uint8_t*)_gdt, 0, sizeof(_gdt));

    _gdt[1].type = GDT_SYSTEM | GDT_PRESENT | GDT_RW | GDT_EXECUTE;
    _gdt[1].size = 0xa0;

    _gdt[2].type = GDT_SYSTEM | GDT_PRESENT | GDT_RW;
    _gdt[2].size = 0xa0;

    _gdt[3].type = GDT_SYSTEM | GDT_PRESENT | GDT_RW | GDT_EXECUTE | GDT_RING3;
    _gdt[3].size = 0xa0;

    _gdt[4].type = GDT_SYSTEM | GDT_PRESENT | GDT_RW | GDT_EXECUTE | GDT_RING3;
    _gdt[4].size = 0xa0;

    table_pointer gdtp = {
        .limit = sizeof(_gdt) -1,
        .base  = (ptr_t)_gdt,
    };

    asm("lgdt %0"::"m"(gdtp));
    reload_cs();
}

cpu_state* interrupt_handler(cpu_state* cpu) {
    if(cpu->interrupt < 32) {
        const char* exceptions[] = {
            "Division by zero",
            "Debug",
            "NMI",
            "Breakpoint",
            "Overflow",
            "Bound range exceeded",
            "Invalid Opcode",
            "Device not available",
            "Double fault",
            "Coprocessor segment overrun",
            "Invalid TSS",
            "Segment not present",
            "Stack-segment fault",
            "General protection fault",
            "Page fault",
            "reserved",
            "x87 floating point exception",
            "Alignment check",
            "Machine check",
            "SIMD floating point exception",
            "Virtualization exception",
            "reserved",
            "reserved",
            "reserved",
            "reserved",
            "reserved",
            "reserved",
            "reserved",
            "reserved",
            "Security exception",
            "reserved"
        };

        fbconsole_clear(0, 0, 127);
        fbconsole_write("\e[38;5;15m\e[48;5;4m");
        fbconsole_write("An error occured and LF OS has to be halted.\n"
                        "Below you can find more information:\n\n");

        fbconsole_write("LF OS build:    %s\n",   BUILD_ID);
        fbconsole_write("Last init step: %s\n\n", LAST_INIT_STEP);
        fbconsole_write("Interrupt: 0x%02x (%s), error: 0x%04x\n\n", cpu->interrupt, exceptions[cpu->interrupt], cpu->error_code);

        DUMP_CPU(cpu);

        while(1);
    }
    else if(cpu->interrupt >= 32 && cpu->interrupt < 48) {
        pic_set_handled(cpu->interrupt);
    }

    cpu_state*  new_cpu = cpu;
    vm_table_t* new_context;
    schedule_next(&new_cpu, &new_context);

    if(new_cpu->rip < 4096) {
        DUMP_CPU(new_cpu);
        while(1);
    }

    vm_context_activate(new_context);

    return new_cpu;
//      return cpu;
}

cpu_state* syscall_handler(cpu_state* cpu) {
    switch(cpu->rdx) {
        case 42:
            fbconsole_write("%c", (int)cpu->rax);
            break;
        default:
            DUMP_CPU(cpu);
            break;
    }

    return cpu;
}