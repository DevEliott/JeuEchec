QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++2a

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    modele/Cavalier.cpp \
    modele/Dame.cpp \
    modele/Echiquier.cpp \
    modele/Fou.cpp \
    modele/Jeu.cpp \
    modele/Piece.cpp \
    modele/Pion.cpp \
    modele/Roi.cpp \
    modele/Tour.cpp \
    vue/CaseUI.cpp \
    vue/DialogMat.cpp \
    vue/DialogPat.cpp \
    vue/MainWindow.cpp \
    vue/MenuDemarrer.cpp


HEADERS += \
    modele/Cavalier.hpp \
    modele/Dame.hpp \
    modele/Deplacement.hpp \
    modele/Echiquier.hpp \
    modele/Fou.hpp \
    modele/Jeu.hpp \
    modele/Piece.hpp \
    modele/Pion.hpp \
    modele/Roi.hpp \
    modele/Tour.hpp \
    vue/CaseUI.hpp \
    vue/DialogMat.hpp \
    vue/DialogPat.hpp \
    vue/MainWindow.hpp \
    vue/MenuDemarrer.hpp


FORMS += \
    vue/DialogMat.ui \
    vue/DialogPat.ui \
    vue/MainWindow.ui \
    vue/MenuDemarrer.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
