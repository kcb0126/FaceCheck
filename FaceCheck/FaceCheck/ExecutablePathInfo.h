#pragma once
#pragma once
#include "Windows.h"

class CExecutablePathInfo
{
public:
	CExecutablePathInfo(void);
	~CExecutablePathInfo(void);

	//member functions
public:
	bool GetExecutablePath(/*[OUT]*/LPTSTR lpstrExecutablePath, /*[IN]*/int nLength);
	bool GetExecutablePathQuoted(/*[OUT]*/LPTSTR lpstrExecutablePathQuoted, /*[IN]*/int nLength);
	bool GetExecutableDirectory(/*[OUT]*/LPTSTR lpstrExecutableDirectory, /*[IN]*/int nLength);
	bool GetExecutableFilenameWithExt(/*[OUT]*/LPTSTR lpstrExecutableFilenameWithExt, /*[IN]*/int nLength);
	bool GetExecutableNameWithoutExt(/*[OUT]*/LPTSTR lpstrExecutableNameWithoutExt, /*[IN]*/int nLength);
	bool GetExecutableFileExt(/*[OUT]*/LPTSTR lpstrExecutableFileExt, /*[IN]*/int nLength);
	bool GetExecutableDrive(/*[OUT]*/LPTSTR lpstrExecutableDrive, /*[IN]*/int nLength);
};

