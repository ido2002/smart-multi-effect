#include "jsonreader.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QVariant>
#include <QVariantList>
#include <QVariantMap>
#include <QFile>
#include <QDir>
#include <qdebug.h>

JsonReader::JsonReader()
{

}

bool JsonReader::readJsonFile(QString file_path, QVariantMap& result)
{
    // step 1
    QFile file_obj(file_path);
    if (!file_obj.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open " << file_path;
        return false;
    }

    // step 2
    QTextStream file_text(&file_obj);
    QString json_string;
    json_string = file_text.readAll();
    file_obj.close();
    QByteArray json_bytes = json_string.toLocal8Bit();

    // step 3
    auto json_doc = QJsonDocument::fromJson(json_bytes);


    if (json_doc.isNull()) {
        qDebug() << "Failed to create JSON doc.";
        return false;
    }
    if (!json_doc.isObject()) {
        qDebug() << "JSON is not an object.";
        return false;
    }

    QJsonObject json_obj = json_doc.object();


    if (json_obj.isEmpty()) {
        qDebug() << "JSON object is empty.";
        return false;
    }

    // step 4
    result = json_obj.toVariantMap();
    return true;
}

bool JsonReader::writeJsonFile(QVariantMap point_map, QString file_path)
{
    QJsonObject json_obj = QJsonObject::fromVariantMap(point_map);
    QJsonDocument json_doc(json_obj);
    QString json_string = json_doc.toJson();



    QFile save_file(file_path);
    if (!save_file.open(QIODevice::WriteOnly)) {
        QDir dir;
            dir.mkpath(file_path + "dir-to_delete");
        if (!save_file.open(QIODevice::WriteOnly)) {
            qDebug() << "failed to open save file";
            return false;
        }
    }
    save_file.write(json_string.toUtf8());
    save_file.close();
    return true;
}
