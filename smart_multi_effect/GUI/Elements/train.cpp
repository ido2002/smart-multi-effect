#include "train.h"
#include "conf.h"

using namespace CONF::GUI_PARAMETERS::TRAINING_PAGE;
using namespace CONF::GUI_PARAMETERS::GENERAL_GUI_PROPERTIES_NAMES;
using namespace sound_processing;

TrainingPage::TrainingPage(QQmlApplicationEngine *engine, QQuickItem *parent)
{
    //create component
    QQmlComponent comp(engine, parent);
    comp.loadUrl(TRAINING_PAGE_URL);

    //add element
    window = qobject_cast<QQuickItem *>(comp.create());
    engine->setObjectOwnership(window, QQmlEngine::JavaScriptOwnership);
    window->setParentItem(parent);
    window->setVisible(false);

    busyIndicator = window->findChild<QQuickItem*>(BUSY_INDICATOR);
    busyIndicator->setVisible(false);
    repeatsLable = window->findChild<QQuickItem*>(REPEATS_LABLE);
    UpdateLable();
}

void TrainingPage::Show()
{
    window->setVisible(true);
}

void TrainingPage::Hide()
{
    window->setVisible(false);
}

void TrainingPage::update()
{
    if(learningThread == nullptr) {
        busyIndicator->setVisible(false);
    } else {
       learningThread->join();
       learningThread = nullptr;
    }
}

void TrainingPage::UpdateLable()
{
    QString str = REPEATS_LABLE_BASE_TEXT + QString::number(repeats);
    repeatsLable->setProperty(LABLE_TEXT, str);
}

void TrainingPage::up()
{
    if(repeats < 100) {
        repeats += 10;
    } else if(repeats < 500) {
        repeats += 50;
    } else if(repeats < 1000) {
        repeats += 100;
    } else if(repeats < 5000) {
        repeats += 250;
    } else if(repeats < 10000) {
        repeats += 1000;
    } else if(repeats < 50000) {
        repeats += 5000;
    }
    UpdateLable();
}

void TrainingPage::down()
{
    if(repeats <= 0) {
        repeats = 0;
    } else if(repeats <= 100) {
        repeats -= 10;
    } else if(repeats <= 500) {
        repeats -= 50;
    } else if(repeats <= 1000) {
        repeats -= 100;
    } else if(repeats <= 5000) {
        repeats -= 250;
    } else if(repeats <= 10000) {
        repeats -= 1000;
    } else if(repeats <= 50000) {
        repeats -= 5000;
    }
    UpdateLable();
}

void TrainingPage::learn(SoundProcessor *soundProcessor)
{
    if(learningThread == nullptr && repeats > 0) {
        busyIndicator->setVisible(true);
        learningThread = new std::thread([&]() {
            soundProcessor->Learn(repeats, repeats);
        });
    }
}
