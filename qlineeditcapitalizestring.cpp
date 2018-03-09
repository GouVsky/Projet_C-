#include "qlineeditcapitalizestring.h"

QLineEditCapitalizeString::QLineEditCapitalizeString(QObject *parent)
    : QObject(parent)
{
    initialized = false;
}

void QLineEditCapitalizeString::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (initialized)
        return;

    initialized = true;
}

bool QLineEditCapitalizeString::isInitialized() const
{
    return initialized;
}

QWidget *QLineEditCapitalizeString::createWidget(QWidget *parent)
{
    return new QLineEdit(parent);
}

QString QLineEditCapitalizeString::name() const
{
    return QStringLiteral("QLineEditCapitalizeString");
}

QString QLineEditCapitalizeString::group() const
{
    return QStringLiteral("Display Widgets [Examples]");
}

QIcon QLineEditCapitalizeString::icon() const
{
    return QIcon();
}

QString QLineEditCapitalizeString::toolTip() const
{
    return QString();
}

QString QLineEditCapitalizeString::whatsThis() const
{
    return QString();
}

bool QLineEditCapitalizeString::isContainer() const
{
    return false;
}

QString QLineEditCapitalizeString::domXml() const
{
    return "<ui language=\"c++\">\n"
           " <widget class=\"QLineEditCapitalizeString\" name=\"qLineEditCapitalizeString\">\n"
           "  <property name=\"geometry\">\n"
           "   <rect>\n"
           "    <x>0</x>\n"
           "    <y>0</y>\n"
           "    <width>100</width>\n"
           "    <height>100</height>\n"
           "   </rect>\n"
           "  </property>\n"
           "  <property name=\"toolTip\" >\n"
           "   <string> ee </string>\n"
           "  </property>\n"
           "  <property name=\"whatsThis\" >\n"
           "   <string> ee </string>\n"
           "  </property>\n"
           " </widget>\n"
           "</ui>\n";
}

QString QLineEditCapitalizeString::includeFile() const
{
    return QStringLiteral("qlineeditcapitalizestring.h");
}

#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
    Q_EXPORT_PLUGIN2(QLineEditCapitalizeString,QLineEditCapitalizeString)
#endif
