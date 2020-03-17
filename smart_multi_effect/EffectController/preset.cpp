#include "preset.h"
#include "conf.h"

#include <iostream>
#include <QVariant>
#include <QVariantList>
#include <QVariantMap>
#include <jsonreader.h>

using namespace hardware_ctrl;


Preset::Preset()
{

}

Preset::Preset(QString path)
{
    Load(path);
}

Preset::Preset(std::list<EffectInfo*> effects, size_t time_ms, size_t resolution)
{
    Set(time_ms, resolution, effects);
}

void Preset::Load(QString path)
{
    QVariantMap map;
    JsonReader::readJsonFile(path, map);
    if(map.size() == 0) {
        std::cout << "error: " << path.toStdString() << std::endl;
        return;
    }
    time_ms = map.find("time")->toInt();
    resolution = map.find("resolution")->toInt();

    effects.clear();
    QVariantMap effectsMap = map.find("effects")->toMap();
    for(auto e : effectsMap.keys()) {
        effects.insert(std::pair<std::string, EffectInfo*>
                       (e.toStdString(), new EffectInfo(effectsMap[e].toMap())));
    }
}

void Preset::Save(QString path)
{
    QVariantMap map;
    map.insert("time", QVariant::fromValue(time_ms));
    map.insert("resolution", QVariant::fromValue(resolution));

    QVariantMap effectsMap;
    for(auto e : effects) {
        effectsMap.insert(QString::fromStdString(e.first), e.second->toQMap());
    }
    map.insert("effects", effectsMap);
    JsonReader::writeJsonFile(map, path);
}

void Preset::Set(size_t time_ms, size_t resolution, std::list<EffectInfo*> effects)
{
    this->time_ms = time_ms;
    this->resolution = resolution;
    for(auto e : effects) {
        this->effects.insert(std::pair<std::string, EffectInfo*>(e->name, e));
    }
}

EffectInfo* Preset::getEffect(std::string name)
{
    return effects.find(name)->second;
}

EffectInfo::EffectInfo(ColorSet colors, std::string name, bool state, std::map<Effect::EffectControlLayoutEllements, int> potentiometers)
 : colors(colors)
{
    this->name = name;
    this->state = state;
    this->potentiometers = potentiometers;
}

EffectInfo::EffectInfo(QVariantMap map) : colors("","","")
{
    using element = Effect::EffectControlLayoutEllements;
    using p_pair = std::pair<element, int>;


    name = map.find("name")->toString().toStdString();
    state = map.find("state")->toBool();

    QVariantMap potentiometersMap = map.find("potentiometers")->toMap();
    for(auto p : potentiometersMap.keys()) {
        potentiometers.insert(p_pair((element)p.toInt(), potentiometersMap[p].toInt()));
    }

    QVariantMap colorsMap = map.find("colors")->toMap();
    colors.fontColor = colorsMap.find("fontColor")->toString();
    colors.dialsColor = colorsMap.find("dialsColor")->toString();
    colors.backGroundColor = colorsMap.find("backGroundColor")->toString();
}

QVariantMap EffectInfo::toQMap()
{
    QVariantMap map;
    map.insert("name", QString::fromStdString(name));
    map.insert("state", state);

    QVariantMap potentiometersMap;
    for(auto p : potentiometers) {
        potentiometersMap.insert(QString::number(p.first), QVariant::fromValue(p.second));
    }
    map.insert("potentiometers", potentiometersMap);

    QVariantMap colorsMap;
    colorsMap.insert("fontColor", colors.fontColor);
    colorsMap.insert("dialsColor", colors.dialsColor);
    colorsMap.insert("backGroundColor", colors.backGroundColor);
    map.insert("colors", colorsMap);

    return map;
}
