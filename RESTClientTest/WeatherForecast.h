#ifndef WEATHERFORECAST_H
#define WEATHERFORECAST_H

#include <QtCore/QDateTime>
#include "QSerializer.h"

class WeatherForecast : public QSerializer
{
    Q_GADGET
    QS_SERIALIZABLE

    QS_FIELD(QDateTime, date);
    QS_FIELD(int, temperatureC);
    QS_FIELD(int, temperatureF);
    QS_FIELD(QString, summary);
};

#endif // WEATHERFORECAST_H
