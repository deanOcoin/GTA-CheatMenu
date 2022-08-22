#pragma once
#include "Windows.h"
#include <vector>
#include <string>
#include <sstream>
#include "structs.h"

namespace Mem
{
	void Patch(void* addr, const std::vector<std::uint8_t>& bytes, DWORD oldProtect);
	void NOP(void* addr, uint8_t bytes, DWORD oldProtect);
}
