#include "stdafx.h"
#include <windows.h>
#include "MiniDump.h"
#include "DBGHELP.H"
//http://dblab.co.kr/294
typedef BOOL (WINAPI *MINIDUMPWRITEDUMP)( // Callback 함수의 원형
    HANDLE hProcess,
    DWORD dwPid,
    HANDLE hFile,
    MINIDUMP_TYPE DumpType,
    CONST PMINIDUMP_EXCEPTION_INFORMATION ExceptionParam,
    CONST PMINIDUMP_USER_STREAM_INFORMATION UserStreamParam,
    CONST PMINIDUMP_CALLBACK_INFORMATION CallbackParam);

LPTOP_LEVEL_EXCEPTION_FILTER PreviousExceptionFilter = NULL;

LONG WINAPI UnHandledExceptionFilter(struct _EXCEPTION_POINTERS *exceptionInfo)
{
    HMODULE    DllHandle        = NULL;

    // Windows 2000 이전에는 따로 DBGHELP를 배포해서 설정해 주어야 한다.
    DllHandle                = LoadLibrary(_T("DBGHELP.DLL"));

    if (DllHandle)
    {
        MINIDUMPWRITEDUMP Dump = (MINIDUMPWRITEDUMP) GetProcAddress(DllHandle, "MiniDumpWriteDump");

        if (Dump)
        {
            TCHAR        DumpPath[MAX_PATH] = {0,};
            SYSTEMTIME    SystemTime;

            GetLocalTime(&SystemTime);

            _sntprintf(DumpPath, MAX_PATH, _T("%d-%d-%d_%dh%dm%ds.dmp"),
                SystemTime.wYear,
                SystemTime.wMonth,
                SystemTime.wDay,
                SystemTime.wHour,
                SystemTime.wMinute,
                SystemTime.wSecond);
           
            HANDLE FileHandle = CreateFile(
                DumpPath,
                GENERIC_WRITE,
                FILE_SHARE_WRITE,
                NULL, CREATE_ALWAYS,
                FILE_ATTRIBUTE_NORMAL,
                NULL);

            if (FileHandle != INVALID_HANDLE_VALUE)
            {
                _MINIDUMP_EXCEPTION_INFORMATION MiniDumpExceptionInfo;
               
                MiniDumpExceptionInfo.ThreadId            = GetCurrentThreadId();
                MiniDumpExceptionInfo.ExceptionPointers    = exceptionInfo;
                MiniDumpExceptionInfo.ClientPointers    = NULL;

                BOOL Success = Dump(
                    GetCurrentProcess(),
                    GetCurrentProcessId(),
                    FileHandle,
                    (_MINIDUMP_TYPE)(MiniDumpWithUnloadedModules+
					MiniDumpWithHandleData+
					MiniDumpWithFullMemory), //webzen...
                    &MiniDumpExceptionInfo,
                    NULL,
                    NULL);

                if (Success)
                {
                    CloseHandle(FileHandle);

                    return EXCEPTION_EXECUTE_HANDLER;
                }
            }

            CloseHandle(FileHandle);
        }
    }

    return EXCEPTION_CONTINUE_SEARCH;
}

//////////////////////////////////////////////////////////////////////
// 1. 디버그모드로 생성된 exe를 실행시 dmp 파일이 생성된다.!!
// 2. 2007-11-7 23_22_39.dmp ( Crash Dump File ) 이 생성된다.
// 3. vc80.pdb ( Program Debug Database ) 가 같은 폴더내에 있어야 에러위치를 볼수 있다.
// 4. dmp 파일을 실행시킨후 디버깅 해주면 에러난곳에 멈춘다.
//////////////////////////////////////////////////////////////////////

BOOL CMiniDump::Begin(VOID)
{
    SetErrorMode(SEM_FAILCRITICALERRORS);

    PreviousExceptionFilter = SetUnhandledExceptionFilter(UnHandledExceptionFilter);

    return true;
}

BOOL CMiniDump::End(VOID)
{
    SetUnhandledExceptionFilter(PreviousExceptionFilter);

    return true;
}