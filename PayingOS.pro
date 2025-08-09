QT       += core gui bluetooth network mqtt

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
INCLUDEPATH += /usr/local/qrencode/include
LIBS += -L/usr/local/qrencode/lib -lqrencode
SOURCES += \
    AliMQTTClient.cpp \
    AliMQTTSettings.cpp \
    QPaymentObject.cpp \
    QWidgetManager.cpp \
    QWidgetPayment.cpp \
    QWidgetReward.cpp \
    QtConstants.cpp \
    main.cpp

HEADERS += \
    AliMQTTClient.h \
    AliMQTTSettings.h \
    QPaymentObject.h \
    QWidgetManager.h \
    QWidgetPayment.h \
    QWidgetReward.h \
    QtConstants.h

TRANSLATIONS += \
    PayingOS_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    README.md

FORMS +=
