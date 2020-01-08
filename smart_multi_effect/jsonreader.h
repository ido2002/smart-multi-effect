#ifndef JSONREADER_H
#define JSONREADER_H

#include <QString>
#include <QVariant>
#include <QVariantMap>
#include <QVariantList>


class JsonReader
{
public:
    JsonReader();

    static bool readJsonFile(QString file_path, QVariantMap& result);

    static bool writeJsonFile(QVariantMap point_map, QString file_path);

};


#endif // JSONREADER_H
