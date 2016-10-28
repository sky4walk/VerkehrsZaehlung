# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=dvat - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to dvat - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "dvat - Win32 Release" && "$(CFG)" != "dvat - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "dvat.mak" CFG="dvat - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "dvat - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "dvat - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
# PROP Target_Last_Scanned "dvat - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "dvat - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\dvat.exe"

CLEAN : 
	-@erase "$(INTDIR)\bitmap.obj"
	-@erase "$(INTDIR)\bmpvideo.obj"
	-@erase "$(INTDIR)\ddutil.obj"
	-@erase "$(INTDIR)\dvat.obj"
	-@erase "$(INTDIR)\dvat.res"
	-@erase "$(INTDIR)\dvatDlg.obj"
	-@erase "$(INTDIR)\gauss.obj"
	-@erase "$(INTDIR)\Gauss2.obj"
	-@erase "$(INTDIR)\houghtrafo.obj"
	-@erase "$(INTDIR)\laplace.obj"
	-@erase "$(INTDIR)\motion.obj"
	-@erase "$(INTDIR)\ringpuffer.obj"
	-@erase "$(INTDIR)\schwellwert.obj"
	-@erase "$(INTDIR)\sobel.obj"
	-@erase "$(INTDIR)\spreiz.obj"
	-@erase "$(INTDIR)\Viewer.obj"
	-@erase "$(OUTDIR)\dvat.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /c
# SUBTRACT CPP /YX /Yc /Yu
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/dvat.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/dvat.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/dvat.pdb" /machine:I386 /out:"$(OUTDIR)/dvat.exe" 
LINK32_OBJS= \
	"$(INTDIR)\bitmap.obj" \
	"$(INTDIR)\bmpvideo.obj" \
	"$(INTDIR)\ddutil.obj" \
	"$(INTDIR)\dvat.obj" \
	"$(INTDIR)\dvat.res" \
	"$(INTDIR)\dvatDlg.obj" \
	"$(INTDIR)\gauss.obj" \
	"$(INTDIR)\Gauss2.obj" \
	"$(INTDIR)\houghtrafo.obj" \
	"$(INTDIR)\laplace.obj" \
	"$(INTDIR)\motion.obj" \
	"$(INTDIR)\ringpuffer.obj" \
	"$(INTDIR)\schwellwert.obj" \
	"$(INTDIR)\sobel.obj" \
	"$(INTDIR)\spreiz.obj" \
	"$(INTDIR)\Viewer.obj" \
	".\ddraw.lib" \
	".\dxguid.lib"

"$(OUTDIR)\dvat.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "dvat - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\dvat.exe"

CLEAN : 
	-@erase "$(INTDIR)\bitmap.obj"
	-@erase "$(INTDIR)\bmpvideo.obj"
	-@erase "$(INTDIR)\ddutil.obj"
	-@erase "$(INTDIR)\dvat.obj"
	-@erase "$(INTDIR)\dvat.res"
	-@erase "$(INTDIR)\dvatDlg.obj"
	-@erase "$(INTDIR)\gauss.obj"
	-@erase "$(INTDIR)\Gauss2.obj"
	-@erase "$(INTDIR)\houghtrafo.obj"
	-@erase "$(INTDIR)\laplace.obj"
	-@erase "$(INTDIR)\motion.obj"
	-@erase "$(INTDIR)\ringpuffer.obj"
	-@erase "$(INTDIR)\schwellwert.obj"
	-@erase "$(INTDIR)\sobel.obj"
	-@erase "$(INTDIR)\spreiz.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(INTDIR)\Viewer.obj"
	-@erase "$(OUTDIR)\dvat.exe"
	-@erase "$(OUTDIR)\dvat.ilk"
	-@erase "$(OUTDIR)\dvat.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /c
# SUBTRACT CPP /YX /Yc /Yu
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/dvat.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/dvat.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/dvat.pdb" /debug /machine:I386 /out:"$(OUTDIR)/dvat.exe" 
LINK32_OBJS= \
	"$(INTDIR)\bitmap.obj" \
	"$(INTDIR)\bmpvideo.obj" \
	"$(INTDIR)\ddutil.obj" \
	"$(INTDIR)\dvat.obj" \
	"$(INTDIR)\dvat.res" \
	"$(INTDIR)\dvatDlg.obj" \
	"$(INTDIR)\gauss.obj" \
	"$(INTDIR)\Gauss2.obj" \
	"$(INTDIR)\houghtrafo.obj" \
	"$(INTDIR)\laplace.obj" \
	"$(INTDIR)\motion.obj" \
	"$(INTDIR)\ringpuffer.obj" \
	"$(INTDIR)\schwellwert.obj" \
	"$(INTDIR)\sobel.obj" \
	"$(INTDIR)\spreiz.obj" \
	"$(INTDIR)\Viewer.obj" \
	".\ddraw.lib" \
	".\dxguid.lib"

"$(OUTDIR)\dvat.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Target

# Name "dvat - Win32 Release"
# Name "dvat - Win32 Debug"

!IF  "$(CFG)" == "dvat - Win32 Release"

!ELSEIF  "$(CFG)" == "dvat - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\dvat.cpp
DEP_CPP_DVAT_=\
	".\bitmap.h"\
	".\dvat.h"\
	".\dvatDlg.h"\
	".\Matrix.h"\
	".\MatrixTpl.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\dvat.obj" : $(SOURCE) $(DEP_CPP_DVAT_) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\dvatDlg.cpp
DEP_CPP_DVATD=\
	".\bitmap.h"\
	".\bmpvideo.h"\
	".\ddraw.h"\
	".\dvat.h"\
	".\dvatDlg.h"\
	".\Gauss2.h"\
	".\globals.h"\
	".\houghtrafo.h"\
	".\Matrix.h"\
	".\MatrixTpl.h"\
	".\motion.h"\
	".\ringpuffer.h"\
	".\schwellwert.h"\
	".\sobel.h"\
	".\spreiz.h"\
	".\StdAfx.h"\
	".\Viewer.h"\
	

"$(INTDIR)\dvatDlg.obj" : $(SOURCE) $(DEP_CPP_DVATD) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\dvat.rc
DEP_RSC_DVAT_R=\
	".\dvat.ico"\
	".\dvat.rc2"\
	

"$(INTDIR)\dvat.res" : $(SOURCE) $(DEP_RSC_DVAT_R) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\bitmap.cpp
DEP_CPP_BITMA=\
	".\bitmap.h"\
	".\Matrix.h"\
	".\MatrixTpl.h"\
	

"$(INTDIR)\bitmap.obj" : $(SOURCE) $(DEP_CPP_BITMA) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ddutil.cpp
DEP_CPP_DDUTI=\
	".\ddraw.h"\
	".\ddutil.h"\
	

"$(INTDIR)\ddutil.obj" : $(SOURCE) $(DEP_CPP_DDUTI) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\gauss.cpp
DEP_CPP_GAUSS=\
	".\bitmap.h"\
	".\gauss.h"\
	".\Matrix.h"\
	".\MatrixTpl.h"\
	

"$(INTDIR)\gauss.obj" : $(SOURCE) $(DEP_CPP_GAUSS) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Gauss2.cpp
DEP_CPP_GAUSS2=\
	".\bitmap.h"\
	".\Gauss2.h"\
	".\Matrix.h"\
	".\MatrixTpl.h"\
	

"$(INTDIR)\Gauss2.obj" : $(SOURCE) $(DEP_CPP_GAUSS2) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\laplace.cpp
DEP_CPP_LAPLA=\
	".\bitmap.h"\
	".\laplace.h"\
	".\Matrix.h"\
	".\MatrixTpl.h"\
	

"$(INTDIR)\laplace.obj" : $(SOURCE) $(DEP_CPP_LAPLA) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\motion.cpp
DEP_CPP_MOTIO=\
	".\bitmap.h"\
	".\Matrix.h"\
	".\MatrixTpl.h"\
	".\motion.h"\
	

"$(INTDIR)\motion.obj" : $(SOURCE) $(DEP_CPP_MOTIO) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\schwellwert.cpp
DEP_CPP_SCHWE=\
	".\bitmap.h"\
	".\Matrix.h"\
	".\MatrixTpl.h"\
	".\schwellwert.h"\
	

"$(INTDIR)\schwellwert.obj" : $(SOURCE) $(DEP_CPP_SCHWE) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\sobel.cpp
DEP_CPP_SOBEL=\
	".\bitmap.h"\
	".\globals.h"\
	".\Matrix.h"\
	".\MatrixTpl.h"\
	".\sobel.h"\
	

"$(INTDIR)\sobel.obj" : $(SOURCE) $(DEP_CPP_SOBEL) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\spreiz.cpp
DEP_CPP_SPREI=\
	".\bitmap.h"\
	".\Matrix.h"\
	".\MatrixTpl.h"\
	".\spreiz.h"\
	

"$(INTDIR)\spreiz.obj" : $(SOURCE) $(DEP_CPP_SPREI) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Viewer.cpp
DEP_CPP_VIEWE=\
	".\ddraw.h"\
	".\ddutil.h"\
	".\StdAfx.h"\
	".\Viewer.h"\
	

"$(INTDIR)\Viewer.obj" : $(SOURCE) $(DEP_CPP_VIEWE) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\dxguid.lib

!IF  "$(CFG)" == "dvat - Win32 Release"

!ELSEIF  "$(CFG)" == "dvat - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ddraw.lib

!IF  "$(CFG)" == "dvat - Win32 Release"

!ELSEIF  "$(CFG)" == "dvat - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ringpuffer.cpp
DEP_CPP_RINGP=\
	".\bitmap.h"\
	".\Matrix.h"\
	".\MatrixTpl.h"\
	".\ringpuffer.h"\
	

"$(INTDIR)\ringpuffer.obj" : $(SOURCE) $(DEP_CPP_RINGP) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\bmpvideo.cpp
DEP_CPP_BMPVI=\
	".\bitmap.h"\
	".\bmpvideo.h"\
	".\Matrix.h"\
	".\MatrixTpl.h"\
	

"$(INTDIR)\bmpvideo.obj" : $(SOURCE) $(DEP_CPP_BMPVI) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\houghtrafo.cpp
DEP_CPP_HOUGH=\
	".\bitmap.h"\
	".\globals.h"\
	".\houghtrafo.h"\
	".\Matrix.h"\
	".\MatrixTpl.h"\
	

"$(INTDIR)\houghtrafo.obj" : $(SOURCE) $(DEP_CPP_HOUGH) "$(INTDIR)"


# End Source File
# End Target
# End Project
################################################################################
