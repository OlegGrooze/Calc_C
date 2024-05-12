#include <QApplication>
#include <QIcon>
#include <QLocale>
#include <QTranslator>

#include "smartcalc_v1.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  QTranslator translator;
  const QStringList uiLanguages = QLocale::system().uiLanguages();
  for (const QString &locale : uiLanguages) {
    const QString baseName = "calculator_" + QLocale(locale).name();
    if (translator.load(":/i18n/" + baseName)) {
      a.installTranslator(&translator);
      break;
    }
  }
  SmartCalc_v1 w;
  w.show();
  return a.exec();
}
