#include "QPaymentWidget.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include "QPaymentObject.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "PayingOS_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
   // QBluetoothCalculator w;
    QPaymentWidget w;
    w.resize(600,800);
    w.show();

    return a.exec();
}
