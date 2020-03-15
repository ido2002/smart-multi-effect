#include "loadingpage.h"
#include "conf.h"
#include <iostream>

using namespace CONF::GUI_PARAMETERS::LOADING_PAGE;

LoadingPage::LoadingPage(QQmlApplicationEngine *engine, QQuickItem *parent)
{
    //create component
    QQmlComponent comp(engine, parent);
    comp.loadUrl(LOADING_PAGE_URL);

    //add element
    window = qobject_cast<QQuickItem *>(comp.create());
    engine->setObjectOwnership(window, QQmlEngine::JavaScriptOwnership);
    window->setParentItem(parent);
    window->setVisible(false);
}

void LoadingPage::Show()
{
    window->setVisible(true);
}

void LoadingPage::Hide()
{
    window->setVisible(false);
}
