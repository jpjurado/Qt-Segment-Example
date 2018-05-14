#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkAccessManager>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    API_KEY = "API_KEY";

    QString json_data = "{\"userId\": \"507f191e810c19729de860ea\",\"event\": \"Home\",\"properties\": {\"name\": \"Test\"}}";
    sendData(json_data);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sendData(QString data)
{
    QString SYNC_URL = "https://api.segment.io/v1/track";
        QUrl url(SYNC_URL);
        QNetworkRequest request(url);

        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        request.setRawHeader("Authorization",API_KEY.toUtf8());


        QNetworkAccessManager *manager = new QNetworkAccessManager(this);

        connect(manager, SIGNAL(finished(QNetworkReply*)),
                this, SLOT(syncRequestFinished(QNetworkReply*)));

        //QByteArray data = QtJson::Json::serialize(collectSyncData());
        //QString json_data = "{\"userId\": \"507f191e810c19729de860ea\",\"event\": \"Home\",\"properties\": {\"name\": \"Test\"}}";
        // FIXME for debug
        //qDebug() << "Sync" << QString::fromUtf8(data.data(), data.size());

        manager->post(request, data.toUtf8());
}

void MainWindow::syncRequestFinished(QNetworkReply *)
{
    qDebug() << "Termino";
}

void MainWindow::on_pushButton_clicked()
{
    qDebug() << "Clicked";
    QString json_data = "{\"userId\": \"507f191e810c19729de860ea\",\"event\": \"Clicked\",\"properties\": {\"name\": \"Test\"}}";
    sendData(json_data);
}
