# Add more folders to ship with the application, here
folder_01.source = qml/CrossSolver
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =



CONFIG += c++14
#CXXFLAGS += -std=c++0x
#QMAKE_CXXFLAGS += -std=c++11


# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    wordlist.cpp \
    solver.cpp \
    asyncsolver.cpp \
    anagramsolver.cpp \
    exsolver.cpp

# Installation path
# target.path =

# Please do not modify the following two lines. Required for deployment.
include(qtquick2applicationviewer/qtquick2applicationviewer.pri)
qtcAddDeployment()

HEADERS += \
    wordlist.h \
    solver.h \
    asyncsolver.h \
    anagramsolver.h \
    exsolver.h

RESOURCES += \
    resources/resources.qrc
