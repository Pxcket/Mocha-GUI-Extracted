#pragma once
#include <Windows.h>
#include <MinHook.h>
#include "xorstr.hpp"
#include <string.h>
#include <string>
#include "vector"
#include "natives.h"
#include "../includes.h"
#include "../logger.h"


void Hooks()
{
    Log::log("Hooks Are Working Please Wait :D");
    MH_Initialize();





    Log::log("Hooks Are Done");
}