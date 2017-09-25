/* ==========================================================================
Class :			CExecutablePathInfo

Author :		IRDS: Satish

Creation Date :	5 March, 2015

Updated Date:   16 March, 2015

Purpose :		The class is help to retrieve executable file's path,
its diretory, name with ext, name without ext and also
extention of executable file.

========================================================================*/

#include "StdAfx.h"
#include "ExecutablePathInfo.h"

CExecutablePathInfo::CExecutablePathInfo(void)
{
}

CExecutablePathInfo::~CExecutablePathInfo(void)
{
}

bool CExecutablePathInfo::GetExecutablePath(/*[OUT]*/LPTSTR lptstrExecutablePath, /*[IN]*/int nLength)
/* ================================================================================================================
NAME OF FUNCTION:	CExecutablePathInfo::GetExecutablePath
CREDIT:				IRDS: Satish
PURPOSE:			This function returns executable file path.
PARAMETERS:			[OUT] 1) LPTSTR lptstrExecutablePath: This output string parameter receives
executable file path.
[IN]  2) int nLength: User need to supply minimum length to store string in output string.
RETURN VALUE:		Returns true on success.
CALLS TO: 			None
CALLED FROM: 		1) GetExecutablePathQuoted
2) GetExecutableDirectory
3) GetExecutableFilenameWithExt
4) GetExecutableNameWithoutExt
5) GetExecutableFileExt
Added date: 		5 March, 2015
Updated date: 		16 March, 2015
===================================================================================================================*/
{
	// This path is longer than MAX_PATH, do not use it with
	// windows api functions as you might get buffer overflows.

	TCHAR strShortPath[1024] = { 0 };
	TCHAR strLongPath[1024] = { 0 };
	bool bSucceed = false;

	if (GetModuleFileName(NULL, strShortPath, 1024) != 0)
	{
		GetLongPathName(strShortPath, strLongPath, 1024);
		_stprintf_s(lptstrExecutablePath, nLength, _T("%s"), strLongPath);

		bSucceed = true;
	}
	else
	{
		bSucceed = false;
	}

	return bSucceed;
}

bool CExecutablePathInfo::GetExecutablePathQuoted(/*[OUT]*/LPTSTR lptstrQuotedExecutablePath, /*[IN]*/int nLength)
/* ================================================================================================================
NAME OF FUNCTION:	CExecutablePathInfo::GetExecutablePathQuoted
CREDIT:				IRDS: Satish
PURPOSE:			This function returns executable file path in quotes.
PARAMETERS:			[OUT] 1) LPTSTR lptstrQuotedExecutablePath: This output string parameter receives executable file path in quotes.
[IN]  2) int nLength: User need to supply minimum length to store string in output string.
RETURN VALUE:		Returns true on success.
CALLS TO: 			1) GetExecutablePath
CALLED FROM:
Added date: 		5 March, 2015
Updated date: 		16 March, 2015
===================================================================================================================*/
{
	LPTSTR lptstrTempPath = new TCHAR[nLength];
	bool bSucceed = false;

	if (GetExecutablePath(lptstrTempPath, nLength))
	{
		_stprintf_s(lptstrQuotedExecutablePath, nLength, _T("\"%s\""), lptstrTempPath);
		bSucceed = true;
	}
	else
	{
		bSucceed = false;
	}

	delete[] lptstrTempPath;
	lptstrTempPath = NULL;

	return bSucceed;
}

bool CExecutablePathInfo::GetExecutableDirectory(/*[OUT]*/LPTSTR lptstrExecutableFileDirectory, /*[IN]*/int nLength)
/* ================================================================================================================
NAME OF FUNCTION:	CExecutablePathInfo::GetExecutableDirectory
CREDIT:				IRDS: Satish
PURPOSE:			This function returns directory containing executable file.
PARAMETERS:			[OUT] 1) LPTSTR lptstrExecutableFileDirectory: This output string parameter receives directory
containing executable file.
[IN]  2) int nLength: User need to supply minimum length to store string in output string.
RETURN VALUE:		Returns true on success
CALLS TO: 			1) GetExecutablePath
CALLED FROM:
Added date: 		5 March, 2015
Updated date: 		16 March, 2015
===================================================================================================================*/
{
	// Without slash at end.
	// This path is longer than MAX_PATH, do not use it with windows api functions as you might get buffer overflows.

	TCHAR strLongPath[1024] = { 0 };
	bool bSucceed = false;

	if (GetExecutablePath(strLongPath, _countof(strLongPath)))
	{
		TCHAR strDrive[3] = { 0 };
		TCHAR strDirectory[768] = { 0 };
		TCHAR strFileName[256] = { 0 };
		TCHAR strExtension[32] = { 0 };

		errno_t errResult = _tsplitpath_s(strLongPath, strDrive, _countof(strDrive), strDirectory, _countof(strDirectory),
			strFileName, _countof(strFileName), strExtension, _countof(strExtension));

		if (errResult == 0)
		{
			_stprintf_s(lptstrExecutableFileDirectory, nLength, _T("%s%s"), strDrive, strDirectory);

			// remove slash at end
			int nLengthTemp = lstrlen(lptstrExecutableFileDirectory);
			if ((lptstrExecutableFileDirectory[nLengthTemp - 1] == '\\') || (lptstrExecutableFileDirectory[nLengthTemp - 1] == '/'))
			{
				lptstrExecutableFileDirectory[nLengthTemp - 1] = 0;
			}

			bSucceed = true;
		}
		else
		{
			bSucceed = false;
		}
	}
	else
	{
		bSucceed = false;
	}

	return bSucceed;
}

bool CExecutablePathInfo::GetExecutableFilenameWithExt(/*[OUT]*/LPTSTR lpstrExecutableFilenameWithExt, /*[IN]*/int nLength)
/* ================================================================================================================
NAME OF FUNCTION:	CExecutablePathInfo::GetExecutableNameWithExt
CREDIT:				IRDS: Satish
PURPOSE:			This function returns executable file name with extension.
PARAMETERS:			[OUT] 1) LPTSTR lpstrExecutableFilenameWithExt: This output string parameter receives executable
file name with extension.
[IN]  2) int nLength: User need to supply minimum length to store string in output string.
RETURN VALUE:		Returns true on success
CALLS TO: 			1) GetExecutablePath
CALLED FROM:
Added date: 		5 March, 2015
Updated date:		16 March, 2015
===================================================================================================================*/
{
	// Filename with extension.

	TCHAR strLongPath[1024] = { 0 };
	bool bSucceed = false;

	if (GetExecutablePath(strLongPath, _countof(strLongPath)))
	{
		TCHAR strDrive[3] = { 0 };
		TCHAR strDirectory[768] = { 0 };
		TCHAR strFileName[256] = { 0 };
		TCHAR strExtension[32] = { 0 };

		errno_t errResult = _tsplitpath_s(strLongPath, strDrive, _countof(strDrive), strDirectory, _countof(strDirectory),
			strFileName, _countof(strFileName), strExtension, _countof(strExtension));

		if (errResult == 0)
		{
			_stprintf_s(lpstrExecutableFilenameWithExt, nLength, _T("%s%s"), strFileName, strExtension);
			bSucceed = true;
		}
		else
		{
			bSucceed = false;
		}
	}
	else
	{
		bSucceed = false;
	}

	return bSucceed;
}

bool CExecutablePathInfo::GetExecutableNameWithoutExt(/*[OUT]*/LPTSTR lpstrExecutableFilenameWithoutExt, /*[IN]*/int nLength)
/* ================================================================================================================
NAME OF FUNCTION:	CExecutablePathInfo::GetExecutableNameWithoutExt
CREDIT:				IRDS: Satish
PURPOSE:			This function returns executable file name without extension.
PARAMETERS:			[OUT] 1) LPTSTR lpstrExecutableFilenameWithoutExt: This output string parameter receives
executable file name without extension.
[IN]  2) int nLength: User need to supply minimum length to store string in output string.
RETURN VALUE:		Returns true on success
CALLS TO: 			1) GetExecutablePath
CALLED FROM:
Added date: 		5 March, 2015
Updated date: 		16 March, 2015
===================================================================================================================*/
{
	// Filename without extension.

	TCHAR strLongPath[1024] = { 0 };
	bool bSucceed = false;

	if (GetExecutablePath(strLongPath, _countof(strLongPath)))
	{
		TCHAR strDrive[3] = { 0 };
		TCHAR strDirectory[768] = { 0 };
		TCHAR strFileName[256] = { 0 };
		TCHAR strExtension[32] = { 0 };

		errno_t errResult = _tsplitpath_s(strLongPath, strDrive, _countof(strDrive), strDirectory, _countof(strDirectory),
			strFileName, _countof(strFileName), strExtension, _countof(strExtension));

		if (errResult == 0)
		{
			_stprintf_s(lpstrExecutableFilenameWithoutExt, nLength, _T("%s"), strFileName);
			bSucceed = true;
		}
		else
		{
			bSucceed = false;
		}
	}
	else
	{
		bSucceed = false;
	}

	return bSucceed;
}

bool CExecutablePathInfo::GetExecutableFileExt(/*[OUT]*/LPTSTR lpstrExecutableFileExt, /*[IN]*/int nLength)
/* ================================================================================================================
NAME OF FUNCTION:	CExecutablePathInfo::GetExecutableFileExt
CREDIT:				IRDS: Satish
PURPOSE:			This function returns extension of file.
PARAMETERS:			[OUT] 1) LPTSTR lpstrExecutableFileExt: This output string parameter receives extension of file
[IN]  2) int nLength: User need to supply minimum length to store string in output string.
RETURN VALUE:		Returns true on success
CALLS TO: 			None
CALLED FROM:
Added date: 		5 March, 2015
Updated date: 		16 March, 2015
===================================================================================================================*/
{
	TCHAR strLongPath[1024] = { 0 };
	bool bSucceed = false;

	if (GetExecutablePath(strLongPath, _countof(strLongPath)))
	{
		TCHAR strDrive[3] = { 0 };
		TCHAR strDirectory[768] = { 0 };
		TCHAR strFileName[256] = { 0 };
		TCHAR strExtension[32] = { 0 };

		errno_t errResult = _tsplitpath_s(strLongPath, strDrive, _countof(strDrive), strDirectory, _countof(strDirectory),
			strFileName, _countof(strFileName), strExtension, _countof(strExtension));

		if (errResult == 0)
		{
			_stprintf_s(lpstrExecutableFileExt, nLength, _T("%s"), strExtension);
			bSucceed = true;
		}
		else
		{
			bSucceed = false;
		}
	}
	else
	{
		bSucceed = false;
	}

	return bSucceed;
}

bool CExecutablePathInfo::GetExecutableDrive(/*[OUT]*/LPTSTR lpstrExecutableDrive, /*[IN]*/int nLength)
/* ================================================================================================================
NAME OF FUNCTION:	CExecutablePathInfo::GetExecutableFileExt
CREDIT:				IRDS: Satish
PURPOSE:			This function returns extension of file.
PARAMETERS:			[OUT] 1) LPTSTR lpstrExecutableFileExt: This output string parameter receives extension of file
[IN]  2) int nLength: User need to supply minimum length to store string in output string.
RETURN VALUE:		Returns true on success
CALLS TO: 			None
CALLED FROM:
Added date: 		5 March, 2015
Updated date: 		16 March, 2015
===================================================================================================================*/
{
	TCHAR strLongPath[1024] = { 0 };
	bool bSucceed = false;

	if (GetExecutablePath(strLongPath, _countof(strLongPath)))
	{
		TCHAR strDrive[3] = { 0 };
		TCHAR strDirectory[768] = { 0 };
		TCHAR strFileName[256] = { 0 };
		TCHAR strExtension[32] = { 0 };

		errno_t errResult = _tsplitpath_s(strLongPath, strDrive, _countof(strDrive), strDirectory, _countof(strDirectory),
			strFileName, _countof(strFileName), strExtension, _countof(strExtension));

		if (errResult == 0)
		{
			_stprintf_s(lpstrExecutableDrive, nLength, _T("%s"), strDrive);
			bSucceed = true;
		}
		else
		{
			bSucceed = false;
		}
	}
	else
	{
		bSucceed = false;
	}

	return bSucceed;
}