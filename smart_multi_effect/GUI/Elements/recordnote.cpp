#include "recordnote.h"
#include "conf.h"
#include <iostream>
#include <QFile>

using namespace CONF::GUI_PARAMETERS::NOTE_RECORDING_PAGE;
using namespace CONF::GUI_PARAMETERS::GENERAL_GUI_PROPERTIES_NAMES;
using namespace sound_processing;

RecordNotePage::RecordNotePage(QQmlApplicationEngine *engine, QQuickItem *parent)
{
    std::cout << "1" << std::endl;
    //create component
    QQmlComponent comp(engine, parent);
    std::cout << "2" << std::endl;
    comp.loadUrl(NOTE_RECORDING_PAGE_URL);
    std::cout << "3" << std::endl;

    //add element
    window = qobject_cast<QQuickItem *>(comp.create());
    std::cout << "4" << std::endl;
    engine->setObjectOwnership(window, QQmlEngine::JavaScriptOwnership);
    std::cout << "5" << std::endl;
    window->setParentItem(parent);
    std::cout << "6" << std::endl;
    window->setVisible(false);
    std::cout << "7" << std::endl;

    busyIndicator = window->findChild<QQuickItem*>(BUSY_INDICATOR);
    std::cout << "8" << std::endl;
    busyIndicator->setVisible(false);
    std::cout << "9" << std::endl;
    notesLable = window->findChild<QQuickItem*>(NOTES_LABLE);
    std::cout << "10" << std::endl;
    noteLable = window->findChild<QQuickItem*>(NOTE_LABLE);
    std::cout << "11" << std::endl;
}

void RecordNotePage::Show()
{
    window->setVisible(true);
}

void RecordNotePage::Hide()
{
    window->setVisible(false);
}

void RecordNotePage::update()
{
    if(recordingThread == nullptr) {
        busyIndicator->setVisible(false);
    } else {
       recordingThread->join();
       recordingThread = nullptr;
       notes.clear();
       UpdateList();
    }
}

void RecordNotePage::UpdateList()
{
    QString str = NOTES_LABLE_BASE_TEXT;
    for(auto n : notes) {
        str += "\n" + QString::fromStdString(Stroke::NoteToString(n));
    }
    notesLable->setProperty(LABLE_TEXT, str);
}

void RecordNotePage::up()
{
    if(currentNote == Stroke::Note::G) {
        currentNote = Stroke::Note::Ab;
    } else {
        currentNote = (Stroke::Note)((int)currentNote + 1);
    }
    noteLable->setProperty(LABLE_TEXT, NOTE_LABLE_BASE_TEXT +
                           QString::fromStdString(Stroke::NoteToString(currentNote)));
}

void RecordNotePage::add()
{
    if(std::find(notes.begin(), notes.end(), currentNote) == notes.end()) {
        notes.push_back(currentNote);
        std::sort(notes.begin(), notes.end());
        UpdateList();
    }
}

void RecordNotePage::remove()
{
    auto it = std::find(notes.begin(), notes.end(), currentNote);
    if(it != notes.end()) {
        notes.erase(it);
        UpdateList();
    }
}

void RecordNotePage::record(SoundProcessor *soundProcessor)
{
    this->soundProcessor = soundProcessor;
    if(recordingThread == nullptr && notes.size() > 0) {
        busyIndicator->setVisible(true);
        recordingThread = new std::thread([&]() {
            this->soundProcessor->RecordNoteSample(notes);
        });
    }
}
