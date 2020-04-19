#ifndef BUTTONTIMER_H
#define BUTTONTIMER_H

#include <QString>
#include <QTimer>

class buttontimer : public QTimer
{

public:
    buttontimer();

    QString button_name;

    QString get_buttonname();
    void set_buttonname(QString value);
};

#endif // BUTTONTIMER_H
