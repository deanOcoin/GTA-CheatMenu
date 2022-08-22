#include "memory.h"

namespace Mem
{
	void Patch(void* addr, const std::vector<std::uint8_t>& bytes, DWORD oldProtect)
	{
		VirtualProtect(addr, bytes.size(), PAGE_EXECUTE_READWRITE, &oldProtect);
		std::memcpy(addr, bytes.data(), bytes.size());
		VirtualProtect(addr, bytes.size(), oldProtect, &oldProtect);
	}

	void NOP(void* addr, uint8_t bytes, DWORD oldProtect)
	{
		std::vector<uint8_t> nopv;
		for (int i = 0; i < bytes; i++) nopv.push_back(0x90);
		Patch(addr, nopv, oldProtect);
	}

}