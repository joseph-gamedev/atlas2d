#include <stdarg.h>		// for va_<xxx>
#include <stdio.h>		// for _snprintf_s(), _vsnprintf_s()
#include <Windows.h>	// for OutputDebugStringA(). Uggh.. this pulls in a lot of Windows specific stuff

#include "JobSystem/Syncronization/Mutex.h"
#include "JobSystem/Syncronization/ScopeLock.h"

namespace Engine
{
	Engine::Mutex ConsolePrintMutex;

	void ConsolePrint(const char* i_pFmt, const char* i_pFile, unsigned int i_Line, ...)
	{
		ScopeLock Lock(ConsolePrintMutex);

		if (!i_pFmt)
			return;

		const size_t		lenOutput = 256;
		char				strOutput[lenOutput] = {};
		const char*			pFile = i_pFile ? i_pFile : "<unknown>";
		int					prefixLen = _snprintf_s(strOutput, lenOutput, _TRUNCATE, "DEBUG: %s %u: ", pFile, i_Line);
		if (prefixLen < 0)
			prefixLen = static_cast<int>(lenOutput - 1);

		// define a variable argument list variable 
		va_list				args;

		// initialize it. second parameter is variable immediately
		// preceding variable arguments
		va_start(args, i_Line);

		// (safely) print our formatted string to a char buffer
		if (static_cast<size_t>(prefixLen) < lenOutput)
		{
			_vsnprintf_s(strOutput + prefixLen, lenOutput - static_cast<size_t>(prefixLen), _TRUNCATE, i_pFmt, args);
		}

		va_end(args);

		OutputDebugStringA(strOutput);
		OutputDebugStringA("\n");
	}
} // namespace Engine
