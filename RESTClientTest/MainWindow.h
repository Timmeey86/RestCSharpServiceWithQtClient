#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>

#include <QtNetwork/QNetworkAccessManager>
#include <QtGui/QStandardItemModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    std::shared_ptr<QNetworkAccessManager> _networkAccessManager = std::make_shared<QNetworkAccessManager>();
    std::unique_ptr<QStandardItemModel> _itemModel = std::make_unique<QStandardItemModel>();
};
#endif // MAINWINDOW_H
