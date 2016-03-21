#define PRSET1__ t1 = CPUCycleCounter();
#define PRSET2__ t2 = CPUCycleCounter();
#define PRDIFF__ t2 - t1
unsigned long long t1 =0, t2 =0;
 
static inline unsigned long long CPUCycleCounter(void) {
    unsigned long long int x;
    __asm__ volatile (".byte 0x0F, 0x31" : "=A" (x));
    return x;
}
