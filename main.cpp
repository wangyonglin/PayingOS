#include "QWidgetPayment.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include "QWidgetManager.h"

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

    QWidgetManager qWidgetManager;
    qWidgetManager.resize(600,800);
    qWidgetManager.show();

    return a.exec();
}
