#include "equi_miner.h"

// convenience function

// size (in bytes) of hash in round 0 <= r < WK
u32 hashSize(const u32 r) {
  const u32 hashbits = WN - (r+1) * DIGITBITS + RESTBITS;
  return (hashbits + 7) / 8;
}

// convert bytes into words,rounding up
u32 hashWords(u32 bytes) {
  return (bytes + TREEBYTES-1) / TREEBYTES;
}

void barrier(pthread_barrier_t *barry) {
  const int rc = pthread_barrier_wait(barry);
  if (rc != 0 && rc != PTHREAD_BARRIER_SERIAL_THREAD) {
    printf("Could not wait on barrier\n");
    pthread_exit(NULL);
  }
}


// do all rounds for each thread
void *worker(void *vp) {
  thread_ctx *tp = (thread_ctx *)vp;
  equi *eq = tp->eq;

  if (tp->id == 0) printf("Digit 0");
  eq->digit0(tp->id);
  barrier(&eq->barry);
  if (tp->id == 0) eq->showbsizes(0);
  barrier(&eq->barry);
#if WN == 200 && WK == 9 && RESTBITS == 10
  eq->digit1(tp->id);
  barrier(&eq->barry);
  if (tp->id == 0) eq->showbsizes(1);
  barrier(&eq->barry);
  eq->digit2(tp->id);
  barrier(&eq->barry);
  if (tp->id == 0) eq->showbsizes(2);
  barrier(&eq->barry);
  eq->digit3(tp->id);
  barrier(&eq->barry);
  if (tp->id == 0) eq->showbsizes(3);
  barrier(&eq->barry);
  eq->digit4(tp->id);
  barrier(&eq->barry);
  if (tp->id == 0) eq->showbsizes(4);
  barrier(&eq->barry);
  eq->digit5(tp->id);
  barrier(&eq->barry);
  if (tp->id == 0) eq->showbsizes(5);
  barrier(&eq->barry);
  eq->digit6(tp->id);
  barrier(&eq->barry);
  if (tp->id == 0) eq->showbsizes(6);
  barrier(&eq->barry);
  eq->digit7(tp->id);
  barrier(&eq->barry);
  if (tp->id == 0) eq->showbsizes(7);
  barrier(&eq->barry);
  eq->digit8(tp->id);
  barrier(&eq->barry);
  if (tp->id == 0) eq->showbsizes(8);
  barrier(&eq->barry);
#else
  for (u32 r = 1; r < WK; r++) {
    r&1 ? eq->digitodd(r, tp->id) : eq->digiteven(r, tp->id);
    barrier(&eq->barry);
    if (tp->id == 0) eq->showbsizes(r);
    barrier(&eq->barry);
  }
#endif
  eq->digitK(tp->id);
  pthread_exit(NULL);
  return 0;
}
