#pragma once

#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <Windows.h>
#include "Render/D3D11/GLib.h"

namespace FileLoader
{
	void* LoadFile(const char* InFilename, size_t& OutSizeFile);

	GLib::Sprite* CreateSprite(const char* InFilename, unsigned int& OutWidth, unsigned int& OutHeight, unsigned int& OutDepth);

}
