# Microsoft Developer Studio Project File - Name="Dataserver" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Dataserver - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Dataserver.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Dataserver.mak" CFG="Dataserver - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Dataserver - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Dataserver - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Dataserver - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /ZI /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /ZI /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x412 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 ws2_32.lib /nologo /subsystem:windows /profile /map /debug /machine:I386

!ELSEIF  "$(CFG)" == "Dataserver - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ws2_32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Dataserver - Win32 Release"
# Name "Dataserver - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ActiveMng.cpp
# End Source File
# Begin Source File

SOURCE=.\BadSyntaxChk.cpp
# End Source File
# Begin Source File

SOURCE=.\BaseDAO.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildView.cpp
# End Source File
# Begin Source File

SOURCE=.\CQuery.cpp
# End Source File
# Begin Source File

SOURCE=.\Dataserver.cpp
# End Source File
# Begin Source File

SOURCE=.\DelayHandler.cpp
# End Source File
# Begin Source File

SOURCE=.\DirPath.cpp
# End Source File
# Begin Source File

SOURCE=.\giocp.cpp
# End Source File
# Begin Source File

SOURCE=.\LogToFile.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MiniDump.cpp
# End Source File
# Begin Source File

SOURCE=..\common\MuNameCheck.cpp
# End Source File
# Begin Source File

SOURCE=.\wsJoinServer.cpp
# End Source File
# Begin Source File

SOURCE=.\WZIPCheck.cpp
# End Source File
# Begin Source File

SOURCE=.\WzItemSerial.cpp
# End Source File
# Begin Source File

SOURCE=.\WZQueue.cpp
# End Source File
# Begin Source File

SOURCE=..\common\WZScriptEncode.cpp
# End Source File
# Begin Source File

SOURCE=..\common\classdef.cpp
# End Source File
# Begin Source File

SOURCE=..\common\logproc.cpp
# End Source File
# Begin Source File

SOURCE=..\common\MyWinsockBase.cpp
# End Source File
# Begin Source File

SOURCE=..\common\SetItemOption.cpp
# End Source File
# Begin Source File

SOURCE=..\common\winutil.cpp
# End Source File
# Begin Source File

SOURCE=..\common\WzMemScript.cpp
# End Source File
# Begin Source File

SOURCE=..\common\zzzitem.cpp
# End Source File
# Begin Source File

SOURCE=.\DbSet\AccountCharDBSet.cpp
# End Source File
# Begin Source File

SOURCE=.\DbSet\CastleDBSet.cpp
# End Source File
# Begin Source File

SOURCE=.\DbSet\CharDBSet.cpp
# End Source File
# Begin Source File

SOURCE=.\DbSet\CharPreviewDBSet.cpp
# End Source File
# Begin Source File

SOURCE=.\DbSet\CrywolfDBSet.cpp
# End Source File
# Begin Source File

SOURCE=.\DbSet\DBConBase.cpp
# End Source File
# Begin Source File

SOURCE=.\DbSet\GSDBSet.cpp
# End Source File
# Begin Source File

SOURCE=.\DbSet\ItemExtDbSet.cpp
# End Source File
# Begin Source File

SOURCE=.\DbSet\MasterLevelSystemDBSet.cpp
# End Source File
# Begin Source File

SOURCE=.\DbSet\OptionDbSet.cpp
# End Source File
# Begin Source File

SOURCE=.\DbSet\PeriodItemExDBSet.cpp
# End Source File
# Begin Source File

SOURCE=.\DbSet\PetDBSet.cpp
# End Source File
# Begin Source File

SOURCE=.\DbSet\QuestExpDBSet.cpp
# End Source File
# Begin Source File

SOURCE=.\DbSet\QuestMonKillDBSet.cpp
# End Source File
# Begin Source File

SOURCE=.\ServerPrc.cpp
# End Source File
# Begin Source File

SOURCE=.\DbSet\WarehouseDBSet.cpp
# End Source File
# Begin Source File

SOURCE=.\DbSet\ZenEvenDb.cpp
# End Source File
# Begin Source File

SOURCE=.\protocol.cpp
# End Source File
# Begin Source File

SOURCE=.\MapServerManager_DS.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ActiveMng.h
# End Source File
# Begin Source File

SOURCE=.\BadSyntaxChk.h
# End Source File
# Begin Source File

SOURCE=.\BaseDAO.h
# End Source File
# Begin Source File

SOURCE=.\ChildView.h
# End Source File
# Begin Source File

SOURCE=.\CQuery.h
# End Source File
# Begin Source File

SOURCE=.\Dataserver.h
# End Source File
# Begin Source File

SOURCE=.\DelayHandler.h
# End Source File
# Begin Source File

SOURCE=.\DirPath.h
# End Source File
# Begin Source File

SOURCE=.\giocp.h
# End Source File
# Begin Source File

SOURCE=.\LogToFile.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MiniDump.h
# End Source File
# Begin Source File

SOURCE=..\common\MuNameCheck.h
# End Source File
# Begin Source File

SOURCE=.\wsJoinServer.h
# End Source File
# Begin Source File

SOURCE=.\WZIPCheck.h
# End Source File
# Begin Source File

SOURCE=.\WzItemSerial.h
# End Source File
# Begin Source File

SOURCE=.\WZQueue.h
# End Source File
# Begin Source File

SOURCE=..\common\WZScriptEncode.h
# End Source File
# Begin Source File

SOURCE=..\common\classdef.h
# End Source File
# Begin Source File

SOURCE=..\common\logproc.h
# End Source File
# Begin Source File

SOURCE=..\common\MyWinsockBase.h
# End Source File
# Begin Source File

SOURCE=..\common\SetItemOption.h
# End Source File
# Begin Source File

SOURCE=..\common\winutil.h
# End Source File
# Begin Source File

SOURCE=..\common\WzMemScript.h
# End Source File
# Begin Source File

SOURCE=..\common\zzzitem.h
# End Source File
# Begin Source File

SOURCE=.\DbSet\AccountCharDBSet.h
# End Source File
# Begin Source File

SOURCE=.\DbSet\CastleDBSet.h
# End Source File
# Begin Source File

SOURCE=.\DbSet\CharDBSet.h
# End Source File
# Begin Source File

SOURCE=.\DbSet\CharPreviewDBSet.h
# End Source File
# Begin Source File

SOURCE=.\DbSet\CrywolfDBSet.h
# End Source File
# Begin Source File

SOURCE=.\DbSet\DBConBase.h
# End Source File
# Begin Source File

SOURCE=.\DbSet\GSDBSet.h
# End Source File
# Begin Source File

SOURCE=.\DbSet\ItemExtDbSet.h
# End Source File
# Begin Source File

SOURCE=.\DbSet\MasterLevelSystemDBSet.h
# End Source File
# Begin Source File

SOURCE=.\DbSet\OptionDbSet.h
# End Source File
# Begin Source File

SOURCE=.\DbSet\PeriodItemExDBSet.h
# End Source File
# Begin Source File

SOURCE=.\DbSet\PetDBSet.h
# End Source File
# Begin Source File

SOURCE=.\DbSet\QuestExpDBSet.h
# End Source File
# Begin Source File

SOURCE=.\DbSet\QuestMonKillDBSet.h
# End Source File
# Begin Source File

SOURCE=.\ServerPrc.h
# End Source File
# Begin Source File

SOURCE=.\DbSet\WarehouseDBSet.h
# End Source File
# Begin Source File

SOURCE=.\DbSet\ZenEvenDb.h
# End Source File
# Begin Source File

SOURCE=.\protocol.h
# End Source File
# Begin Source File

SOURCE=.\MapServerManager_DS.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\Dataserver.ico
# End Source File
# Begin Source File

SOURCE=.\res\Dataserver.rc2
# End Source File
# Begin Source File

SOURCE=.\res\DataserverDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\Dataserver.rc
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
