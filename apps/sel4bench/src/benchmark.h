/*
 * Copyright 2014, NICTA
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(NICTA_GPL)
 */
#ifndef __BENCHMARK_H__
#define __BENCHMARK_H__

#include <sel4bench/sel4bench.h>
#include <simple/simple.h>
#include <sel4utils/process.h>
#include <vka/vka.h>
#include <vspace/vspace.h>

/* Contains information about the test environment. */
struct env {
    /* An initialised vka that may be used by the test. */
    vka_t vka;
    simple_t simple;
    vspace_t vspace;

    /* ep to run benchmark on */
    vka_object_t ep;
    cspacepath_t ep_path;

    /* ep to send results on */
    vka_object_t result_ep;
    cspacepath_t result_ep_path;

    /* elf region containing code segment */
    sel4utils_elf_region_t region;

#ifdef CONFIG_KERNEL_STABLE
    seL4_CPtr asid_pool;
#endif /* CONFIG_KERNEL_STABLE */
};

typedef struct env *env_t;
typedef seL4_Word (*helper_func_t)(int argc, char *argv[]);

typedef struct bench_result {
    double variance;
    double stddev;
    double stddev_pc;
    double mean;
    ccnt_t min;
    ccnt_t max;
} bench_result_t;

void ipc_benchmarks_new(struct env* env);
void run_benchmarks(void);
void irq_benchmarks_new(struct env* env);

#endif /* __BENCHMARK_H__ */
