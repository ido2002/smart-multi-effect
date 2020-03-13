#include <QtQml/qqmlprivate.h>
#include <QtCore/qdir.h>
#include <QtCore/qurl.h>

static const unsigned char qt_resource_tree[] = {
0,
0,0,0,0,2,0,0,0,5,0,0,0,1,0,0,1,
52,0,2,0,0,0,4,0,0,0,16,0,0,0,212,0,
2,0,0,0,2,0,0,0,14,0,0,0,8,0,2,0,
0,0,4,0,0,0,10,0,0,1,228,0,0,0,0,0,
1,0,0,0,0,0,0,1,250,0,2,0,0,0,4,0,
0,0,6,0,0,2,68,0,0,0,0,0,1,0,0,0,
0,0,0,2,20,0,0,0,0,0,1,0,0,0,0,0,
0,2,150,0,0,0,0,0,1,0,0,0,0,0,0,2,
102,0,0,0,0,0,1,0,0,0,0,0,0,0,178,0,
0,0,0,0,1,0,0,0,0,0,0,0,90,0,0,0,
0,0,1,0,0,0,0,0,0,0,36,0,0,0,0,0,
1,0,0,0,0,0,0,0,130,0,0,0,0,0,1,0,
0,0,0,0,0,0,230,0,0,0,0,0,1,0,0,0,
0,0,0,1,6,0,0,0,0,0,1,0,0,0,0,0,
0,1,150,0,0,0,0,0,1,0,0,0,0,0,0,1,
116,0,0,0,0,0,1,0,0,0,0,0,0,1,182,0,
0,0,0,0,1,0,0,0,0,0,0,1,68,0,0,0,
0,0,1,0,0,0,0};
static const unsigned char qt_resource_names[] = {
0,
1,0,0,0,47,0,47,0,11,6,196,31,209,0,66,0,
117,0,116,0,116,0,111,0,110,0,115,0,65,0,114,0,
101,0,97,0,24,10,246,116,188,0,67,0,117,0,115,0,
116,0,111,0,109,0,66,0,117,0,111,0,116,0,116,0,
111,0,110,0,70,0,111,0,114,0,109,0,46,0,117,0,
105,0,46,0,113,0,109,0,108,0,17,6,121,243,156,0,
67,0,117,0,115,0,116,0,111,0,109,0,66,0,117,0,
111,0,116,0,116,0,111,0,110,0,46,0,113,0,109,0,
108,0,21,13,220,109,220,0,66,0,117,0,116,0,116,0,
111,0,110,0,65,0,114,0,101,0,97,0,70,0,111,0,
114,0,109,0,46,0,117,0,105,0,46,0,113,0,109,0,
108,0,14,1,198,131,92,0,66,0,117,0,116,0,116,0,
111,0,110,0,65,0,114,0,101,0,97,0,46,0,113,0,
109,0,108,0,6,4,216,131,195,0,70,0,114,0,97,0,
109,0,101,0,115,0,13,5,1,46,92,0,83,0,111,0,
110,0,103,0,70,0,114,0,97,0,109,0,101,0,46,0,
113,0,109,0,108,0,20,11,177,205,28,0,83,0,111,0,
110,0,103,0,70,0,114,0,97,0,109,0,101,0,70,0,
111,0,114,0,109,0,46,0,117,0,105,0,46,0,113,0,
109,0,108,0,5,0,86,125,195,0,80,0,97,0,103,0,
101,0,115,0,21,12,242,100,188,0,80,0,114,0,101,0,
115,0,101,0,116,0,80,0,97,0,103,0,101,0,70,0,
111,0,114,0,109,0,46,0,117,0,105,0,46,0,113,0,
109,0,108,0,14,6,71,211,28,0,80,0,114,0,101,0,
115,0,101,0,116,0,80,0,97,0,103,0,101,0,46,0,
113,0,109,0,108,0,13,3,33,137,156,0,83,0,111,0,
110,0,103,0,115,0,80,0,97,0,103,0,101,0,46,0,
113,0,109,0,108,0,20,7,188,181,124,0,83,0,111,0,
110,0,103,0,115,0,80,0,97,0,103,0,101,0,70,0,
111,0,114,0,109,0,46,0,117,0,105,0,46,0,113,0,
109,0,108,0,8,8,1,90,92,0,109,0,97,0,105,0,
110,0,46,0,113,0,109,0,108,0,10,11,161,194,132,0,
69,0,102,0,102,0,101,0,99,0,116,0,69,0,100,0,
105,0,116,0,21,6,74,249,156,0,69,0,102,0,102,0,
101,0,99,0,116,0,69,0,100,0,105,0,116,0,70,0,
111,0,114,0,109,0,46,0,117,0,105,0,46,0,113,0,
109,0,108,0,14,2,144,23,188,0,69,0,102,0,102,0,
101,0,99,0,116,0,69,0,100,0,105,0,116,0,46,0,
113,0,109,0,108,0,21,7,74,244,124,0,69,0,102,0,
102,0,101,0,99,0,116,0,68,0,105,0,97,0,108,0,
70,0,111,0,114,0,109,0,46,0,117,0,105,0,46,0,
113,0,109,0,108,0,14,6,232,23,156,0,69,0,102,0,
102,0,101,0,99,0,116,0,68,0,105,0,97,0,108,0,
46,0,113,0,109,0,108};
static const unsigned char qt_resource_empty_payout[] = { 0, 0, 0, 0, 0 };
QT_BEGIN_NAMESPACE
extern Q_CORE_EXPORT bool qRegisterResourceData(int, const unsigned char *, const unsigned char *, const unsigned char *);
QT_END_NAMESPACE
namespace QmlCacheGeneratedCode {
namespace _0x5f_EffectEdit_EffectDial_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f_EffectEdit_EffectDialForm_ui_0x2e_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f__main_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f_EffectEdit_EffectEdit_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f_Pages_SongsPageForm_ui_0x2e_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f_Pages_SongsPage_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f_Frames_SongFrameForm_ui_0x2e_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f_Frames_SongFrame_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f_ButtonsArea_ButtonArea_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f_EffectEdit_EffectEditForm_ui_0x2e_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f_ButtonsArea_ButtonAreaForm_ui_0x2e_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f_ButtonsArea_CustomBuotton_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f_ButtonsArea_CustomBuottonForm_ui_0x2e_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f_Pages_PresetPage_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f_Pages_PresetPageForm_ui_0x2e_qml { 
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
        resourcePathToCachedUnit.insert(QStringLiteral("/EffectEdit/EffectDial.qml"), &QmlCacheGeneratedCode::_0x5f_EffectEdit_EffectDial_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/EffectEdit/EffectDialForm.ui.qml"), &QmlCacheGeneratedCode::_0x5f_EffectEdit_EffectDialForm_ui_0x2e_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/main.qml"), &QmlCacheGeneratedCode::_0x5f__main_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/EffectEdit/EffectEdit.qml"), &QmlCacheGeneratedCode::_0x5f_EffectEdit_EffectEdit_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/Pages/SongsPageForm.ui.qml"), &QmlCacheGeneratedCode::_0x5f_Pages_SongsPageForm_ui_0x2e_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/Pages/SongsPage.qml"), &QmlCacheGeneratedCode::_0x5f_Pages_SongsPage_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/Frames/SongFrameForm.ui.qml"), &QmlCacheGeneratedCode::_0x5f_Frames_SongFrameForm_ui_0x2e_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/Frames/SongFrame.qml"), &QmlCacheGeneratedCode::_0x5f_Frames_SongFrame_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/ButtonsArea/ButtonArea.qml"), &QmlCacheGeneratedCode::_0x5f_ButtonsArea_ButtonArea_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/EffectEdit/EffectEditForm.ui.qml"), &QmlCacheGeneratedCode::_0x5f_EffectEdit_EffectEditForm_ui_0x2e_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/ButtonsArea/ButtonAreaForm.ui.qml"), &QmlCacheGeneratedCode::_0x5f_ButtonsArea_ButtonAreaForm_ui_0x2e_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/ButtonsArea/CustomBuotton.qml"), &QmlCacheGeneratedCode::_0x5f_ButtonsArea_CustomBuotton_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/ButtonsArea/CustomBuottonForm.ui.qml"), &QmlCacheGeneratedCode::_0x5f_ButtonsArea_CustomBuottonForm_ui_0x2e_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/Pages/PresetPage.qml"), &QmlCacheGeneratedCode::_0x5f_Pages_PresetPage_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/Pages/PresetPageForm.ui.qml"), &QmlCacheGeneratedCode::_0x5f_Pages_PresetPageForm_ui_0x2e_qml::unit);
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
    Q_INIT_RESOURCE(GUI_qml_qmlcache);
    return 1;
}
Q_CONSTRUCTOR_FUNCTION(QT_MANGLE_NAMESPACE(qInitResources_qml))
int QT_MANGLE_NAMESPACE(qCleanupResources_qml)() {
    Q_CLEANUP_RESOURCE(GUI_qml_qmlcache);
    return 1;
}
