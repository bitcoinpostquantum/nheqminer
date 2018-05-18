// Equihash solver
// Copyright (c) 2016-2016 John Tromp
#ifndef EQUI_H_
#define EQUI_H_

#include "blake/blake2.h"
#ifdef __APPLE__
#include "osx_barrier.h"
#include <machine/endian.h>
#include <libkern/OSByteOrder.h>
#define htole32(x) OSSwapHostToLittleInt32(x)
#else
#include <endian.h>
#endif
#include <stdint.h> // for types uint32_t,uint64_t
#include <string.h> // for functions memset
#include <stdlib.h> // for function qsort

typedef uint32_t u32;
typedef unsigned char uchar;

// algorithm parameters, prefixed with W (for Wagner) to reduce include file conflicts

#ifndef WN
#define WN	96
#endif

#ifndef WK
#define WK	5
#endif

#ifndef RESTBITS
#define RESTBITS  4
#endif


#ifndef HEADERNONCELEN
#define HEADERNONCELEN 140
#endif

#define NDIGITS		(WK+1)
#define DIGITBITS	(WN/(NDIGITS))

static const u32 PROOFSIZE = 1<<WK;
static const u32 BASE = 1<<DIGITBITS;
static const u32 NHASHES = 2*BASE;
static const u32 HASHESPERBLAKE = 512/WN;
static const u32 HASHOUT = HASHESPERBLAKE*WN/8;

typedef u32 proof[PROOFSIZE];

void setheader(blake2b_state *ctx, const char *headernonce);
bool duped(proof prf);


#endif