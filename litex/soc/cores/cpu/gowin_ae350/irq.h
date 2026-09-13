#ifndef __IRQ_H
#define __IRQ_H

#ifdef __cplusplus
extern "C" {
#endif

#include <system.h>
#include <generated/csr.h>
#include <generated/soc.h>

// The SoC IRQs reach it on GP_INT[15:1], which the AE350 maps to
// the contiguous sources IRQ_GP1_SOURCE..IRQ_GP15_SOURCE (11 to 25).
#define PLIC_EXT_IRQ_BASE 11

#define INTERRUPT_PEND 0xe4001000L
#define INTERRUPT_MASK 0xe4002000L

static inline unsigned int irq_getie(void)
{
	return (csrr(mstatus) & CSR_MSTATUS_MIE) != 0;
}

static inline void irq_setie(unsigned int ie)
{
	if(ie) csrs(mstatus,CSR_MSTATUS_MIE); else csrc(mstatus,CSR_MSTATUS_MIE);
}

static inline unsigned int irq_getmask(void)
{
	return *((unsigned int *)INTERRUPT_MASK) >> PLIC_EXT_IRQ_BASE;
}

static inline void irq_setmask(unsigned int mask)
{
	*((unsigned int *)INTERRUPT_MASK) = mask << PLIC_EXT_IRQ_BASE;
}

static inline unsigned int irq_pending(void) {

	return *((unsigned int *)INTERRUPT_PEND) >> PLIC_EXT_IRQ_BASE;
}

#ifdef __cplusplus
}
#endif

#endif /* __IRQ_H */
