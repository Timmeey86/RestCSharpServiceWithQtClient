#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "WeatherForecast.h"

#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>

#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonValue>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _itemModel->setColumnCount(4);
    _itemModel->setHeaderData(0, Qt::Horizontal, "Date");
    _itemModel->setHeaderData(1, Qt::Horizontal, "Temperature (°C)");
    _itemModel->setHeaderData(2, Qt::Horizontal, "Tempareture (°F)");
    _itemModel->setHeaderData(3, Qt::Horizontal, "Summary");

    ui->tableView->setModel(_itemModel.get());

    QObject::connect(_networkAccessManager.get(), &QNetworkAccessManager::finished, [this](QNetworkReply* reply){

        _itemModel->removeRows(0, _itemModel->rowCount());
        if(reply->error())
        {
            _itemModel->appendRow(
                        {
                            new QStandardItem( "Error" ),
                            new QStandardItem( "0" ),
                            new QStandardItem( "0" ),
                            new QStandardItem( reply->errorString() )
                        });
        }
        else
        {
            QString replyText = reply->readAll();
            auto doc = QJsonDocument::fromJson(replyText.toUtf8());
            auto array = doc.array();
            for(auto element : array)
            {
                auto jsonObj = element.toObject();
                WeatherForecast forecast;
                forecast.fromJson(jsonObj);
                _itemModel->appendRow(
                            {
                               new QStandardItem( forecast.date.toString() ),
                               new QStandardItem( QString::number( forecast.temperatureC ) ),
                                new QStandardItem( QString::number( forecast.temperatureF ) ),
                                new QStandardItem( forecast.summary )
                            });
            }
        }
        reply->deleteLater();
    });

    QNetworkRequest request;
    QSslConfiguration config = QSslConfiguration::defaultConfiguration();
    config.setProtocol(QSsl::TlsV1_2);
    request.setSslConfiguration(config);
    request.setUrl({"https://localhost:44308/weatherforecast/"});
    request.setHeader(QNetworkRequest::ServerHeader, "application/json");
    _networkAccessManager->get(request);
}

MainWindow::~MainWindow()
{
    delete ui;
}

