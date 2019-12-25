#include <QtQml/qqmlprivate.h>
#include <QtCore/qdir.h>
#include <QtCore/qurl.h>

static const unsigned char qt_resource_tree[] = {
0,
0,0,0,0,2,0,0,0,8,0,0,0,1,0,0,0,
182,0,0,0,0,0,1,0,0,0,0,0,0,0,218,0,
0,0,0,0,1,0,0,0,0,0,0,0,134,0,0,0,
0,0,1,0,0,0,0,0,0,0,8,0,0,0,0,0,
1,0,0,0,0,0,0,0,86,0,0,0,0,0,1,0,
0,0,0,0,0,1,38,0,0,0,0,0,1,0,0,0,
0,0,0,0,252,0,0,0,0,0,1,0,0,0,0,0,
0,0,42,0,0,0,0,0,1,0,0,0,0};
static const unsigned char qt_resource_names[] = {
0,
1,0,0,0,47,0,47,0,14,6,232,23,156,0,69,0,
102,0,102,0,101,0,99,0,116,0,68,0,105,0,97,0,
108,0,46,0,113,0,109,0,108,0,19,14,112,70,92,0,
83,0,101,0,116,0,116,0,105,0,110,0,103,0,115,0,
70,0,111,0,114,0,109,0,46,0,117,0,105,0,46,0,
113,0,109,0,108,0,21,7,74,244,124,0,69,0,102,0,
102,0,101,0,99,0,116,0,68,0,105,0,97,0,108,0,
70,0,111,0,114,0,109,0,46,0,117,0,105,0,46,0,
113,0,109,0,108,0,21,6,74,249,156,0,69,0,102,0,
102,0,101,0,99,0,116,0,69,0,100,0,105,0,116,0,
70,0,111,0,114,0,109,0,46,0,117,0,105,0,46,0,
113,0,109,0,108,0,15,2,131,188,188,0,72,0,111,0,
109,0,101,0,70,0,111,0,114,0,109,0,46,0,117,0,
105,0,46,0,113,0,109,0,108,0,14,2,144,23,188,0,
69,0,102,0,102,0,101,0,99,0,116,0,69,0,100,0,
105,0,116,0,46,0,113,0,109,0,108,0,18,14,46,170,
28,0,69,0,100,0,105,0,116,0,105,0,110,0,103,0,
70,0,111,0,114,0,109,0,46,0,117,0,105,0,46,0,
113,0,109,0,108,0,8,8,1,90,92,0,109,0,97,0,
105,0,110,0,46,0,113,0,109,0,108};
static const unsigned char qt_resource_empty_payout[] = { 0, 0, 0, 0, 0 };
QT_BEGIN_NAMESPACE
extern Q_CORE_EXPORT bool qRegisterResourceData(int, const unsigned char *, const unsigned char *, const unsigned char *);
QT_END_NAMESPACE
namespace QmlCacheGeneratedCode {
namespace _0x5f__main_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f__EditingForm_ui_0x2e_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f__EffectEdit_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f__HomeForm_ui_0x2e_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f__EffectEditForm_ui_0x2e_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f__EffectDialForm_ui_0x2e_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f__SettingsForm_ui_0x2e_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f__EffectDial_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}

}
namespace {
struct Registry {
    Registry();
    ~Registry();
    QHash<QString, const QQmlPrivate::CachedQmlUnit*> resourcePathToCachedUnit;
    static const QQmlPrivate::CachedQmlUnit *lookupCachedUnit(const QUrl &url);
};

Q_GLOBAL_STATIC(Registry, unitRegistry)


Registry::Registry() {
        resourcePathToCachedUnit.insert(QStringLiteral("/main.qml"), &QmlCacheGeneratedCode::_0x5f__main_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/EditingForm.ui.qml"), &QmlCacheGeneratedCode::_0x5f__EditingForm_ui_0x2e_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/EffectEdit.qml"), &QmlCacheGeneratedCode::_0x5f__EffectEdit_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/HomeForm.ui.qml"), &QmlCacheGeneratedCode::_0x5f__HomeForm_ui_0x2e_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/EffectEditForm.ui.qml"), &QmlCacheGeneratedCode::_0x5f__EffectEditForm_ui_0x2e_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/EffectDialForm.ui.qml"), &QmlCacheGeneratedCode::_0x5f__EffectDialForm_ui_0x2e_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/SettingsForm.ui.qml"), &QmlCacheGeneratedCode::_0x5f__SettingsForm_ui_0x2e_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/EffectDial.qml"), &QmlCacheGeneratedCode::_0x5f__EffectDial_qml::unit);
    QQmlPrivate::RegisterQmlUnitCacheHook registration;
    registration.version = 0;
    registration.lookupCachedQmlUnit = &lookupCachedUnit;
    QQmlPrivate::qmlregister(QQmlPrivate::QmlUnitCacheHookRegistration, &registration);
QT_PREPEND_NAMESPACE(qRegisterResourceData)(/*version*/0x01, qt_resource_tree, qt_resource_names, qt_resource_empty_payout);
}

Registry::~Registry() {
    QQmlPrivate::qmlunregister(QQmlPrivate::QmlUnitCacheHookRegistration, quintptr(&lookupCachedUnit));
}

const QQmlPrivate::CachedQmlUnit *Registry::lookupCachedUnit(const QUrl &url) {
    if (url.scheme() != QLatin1String("qrc"))
        return nullptr;
    QString resourcePath = QDir::cleanPath(url.path());
    if (resourcePath.isEmpty())
        return nullptr;
    if (!resourcePath.startsWith(QLatin1Char('/')))
        resourcePath.prepend(QLatin1Char('/'));
    return unitRegistry()->resourcePathToCachedUnit.value(resourcePath, nullptr);
}
}
int QT_MANGLE_NAMESPACE(qInitResources_qml)() {
    ::unitRegistry();
    Q_INIT_RESOURCE(qml_qmlcache);
    return 1;
}
Q_CONSTRUCTOR_FUNCTION(QT_MANGLE_NAMESPACE(qInitResources_qml))
int QT_MANGLE_NAMESPACE(qCleanupResources_qml)() {
    Q_CLEANUP_RESOURCE(qml_qmlcache);
    return 1;
}
