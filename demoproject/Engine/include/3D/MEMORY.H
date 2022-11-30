/*
 *  Memory.H
 *
 *  Created on: Oct 23, 2022
 *  Author: SAK-007
 *
 *
 *  Contains:RAM Functions
 *
 */

#ifndef MEMORY_H
#define MEMORY_H
unsigned long __ramsize =   0x00200000; // 2 Megabytes of RAM
unsigned long __stacksize = 0x00004000; // 16 Kilobytes of Stack


#include <STDLIB.H>
#include <STDIO.H>
#include <LIBGTE.H>
#include <LIBGPU.H>
#include <LIBGS.H>
#include <LIBETC.H>
#include <LIBSPU.H>
#include <SYS/TYPES.H>



void clearVRAM() {
    RECT rectTL;
    setRECT(&rectTL, 0, 0, 1024, 512);
    ClearImage2(&rectTL, 0, 0, 0);
    DrawSync(0);
    return;
}

void ClearVRAM() {
    RECT rectTL;
    setRECT(&rectTL, 0, 0, 1024, 512);
    ClearImage2(&rectTL, 0, 0, 0);
    DrawSync(0);
    return;
}

void clearRAM() {
    RECT rectTL;
    setRECT(&rectTL, 0, 0, 1024, 512);
    ClearImage2(&rectTL, 0, 0, 0);
    DrawSync(0);
    return;
}

void ClearRAM() {
    RECT rectTL;
    setRECT(&rectTL, 0, 0, 1024, 512);
    ClearImage2(&rectTL, 0, 0, 0);
    DrawSync(0);
    return;
}


void initialize_heap() {
    InitHeap3((void*)0x800F8000, 0x00100000);
}


void initializeHeap() {
    InitHeap3((void*)0x800F8000, 0x00100000);
}

void initializeMemory() {
    InitHeap3((void*)0x800F8000, 0x00100000);
}



#endif
