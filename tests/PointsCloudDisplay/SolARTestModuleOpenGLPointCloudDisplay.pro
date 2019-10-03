TARGET = SolAROpenGLPointCloudDisplay
VERSION=0.6.0

CONFIG += c++1z
CONFIG += console
CONFIG -= qt

DEFINES += MYVERSION=$${VERSION}

CONFIG(debug,debug|release) {
    DEPENDENCIESCONFIG = shared recurse
    DEFINES += _DEBUG=1
    DEFINES += DEBUG=1
}

CONFIG(release,debug|release) {
    DEPENDENCIESCONFIG = shared install_recurse # install only in release mode
    TARGETDEPLOYDIR = $${PWD}\..\bin
    DEFINES += _NDEBUG=1
    DEFINES += NDEBUG=1
}

DEFINES += BOOST_ALL_NO_LIB
DEFINES += BOOST_ALL_DYN_LINK

win32:CONFIG -= static
win32:CONFIG += shared

## Configuration for Visual Studio to install binaries and dependencies. Work also for QT Creator by replacing QMAKE_INSTALL
PROJECTCONFIG = QTVS

#NOTE : CONFIG as staticlib or sharedlib, DEPENDENCIESCONFIG as staticlib or sharedlib, QMAKE_TARGET.arch and PROJECTDEPLOYDIR MUST BE DEFINED BEFORE templatelibconfig.pri inclusion
include ($$shell_quote($$shell_path($$(REMAKEN_RULES_ROOT)/qmake/templateappconfig.pri))) # Shell_quote & shell_path required for visual on windows

HEADERS += \


SOURCES += \
    main.cpp

unix {
}

linux {
    LIBS += -ldl
}

macx {
    QMAKE_MAC_SDK= macosx
    QMAKE_CXXFLAGS += -fasm-blocks -x objective-c++ -std=c++17
}

win32 {
    QMAKE_LFLAGS += /MACHINE:X64
    DEFINES += WIN64 UNICODE _UNICODE
    QMAKE_COMPILER_DEFINES += _WIN64

    # Windows Kit (msvc2013 64)
    LIBS += -L$$(WINDOWSSDKDIR)lib/winv6.3/um/x64 -lshell32 -lgdi32 -lComdlg32
    INCLUDEPATH += $$(WINDOWSSDKDIR)lib/winv6.3/um/x64
}

configfile.path = $${TARGETDEPLOYDIR}/
configfile.files = $${PWD}/SolAROpenGLPointCloudDisplay_conf.xml
INSTALLS += configfile

#NOTE : Must be placed at the end of the .pro
include ($$shell_quote($$shell_path($$(REMAKEN_RULES_ROOT)/qmake/remaken_install_target.pri))) # Shell_quote & shell_path required for visual on windows
