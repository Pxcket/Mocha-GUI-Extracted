#pragma once
#include <Psapi.h>
#include "mem.h"
bool Compare(byte* data, byte* sig, uint64_t size)
{
    for (auto i = 0ull; i < size; i++) { if (data[i] != sig[i] && sig[i] != 0x00) { return false; } }
    return true;
}

byte* FindSignature(byte* start, byte* end, byte* sig, uint64_t size)
{
    for (auto it = start; it < end - size; it++) { if (Compare(it, sig, size)) { return it; }; }
    return nullptr;
}

bool PatchMem(void* address, void* bytes, uint64_t size)
{
    DWORD oldProtection;
    if (!VirtualProtect(address, size, PAGE_EXECUTE_READWRITE, &oldProtection)) { return false; }
    memcpy(address, bytes, size);
    return VirtualProtect(address, size, oldProtection, &oldProtection);
}