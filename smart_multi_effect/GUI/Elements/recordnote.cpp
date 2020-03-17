#include "recordnote.h"
#include "conf.h"
#include <iostream>
#include <QFile>

using namespace CONF::GUI_PARAMETERS::NOTE_RECORDING_PAGE;
using namespace CONF::GUI_PARAMETERS::GENERAL_GUI_PROPERTIES_NAMES;
using namespace sound_processing;

RecordNotePage::RecordNotePage(QQmlApplicationEngine *engine, QQuickItem *parent)
{
    //create component
    QQmlComponent comp(engine, parent);
    comp.loadUrl(NOTE_RECORDING_PAGE_URL);

    //add element
    window = qobject_cast<QQuickItem *>(comp.create());
    engine->setObjectOwnership(window, QQmlEngine::JavaScriptOwnership);
    window->setParentItem(parent);
    window->setVisible(false);

    busyIndicator = window->findChild<QQuickItem*>(BUSY_INDICATOR);
    busyIndicator->setVisible(false);
    notesLabel = window->findChild<QQuickItem*>(NOTES_LABEL);
    noteLabel = window->findChild<QQuickItem*>(NOTE_LABEL);
}

void RecordNotePage::Show()
{
    window->setVisible(true);
}

void RecordNotePage::Hide()
{
    window->setVisible(false);
}

int RecordNotePage_counter = 0;
void RecordNotePage::update()
{
    if(recordingThread == nullptr) {
        busyIndicator->setVisible(false);
    } else {
        if(RecordNotePage_counter < 2){
            RecordNotePage_counter++;
            return;
        }
        RecordNotePage_counter = 0;
        recordingThread->join();
        recordingThread = nullptr;
        //notes.clear();
        UpdateList();
    }
}

void RecordNotePage::UpdateList()
{
    QString str = NOTES_LABEL_BASE_TEXT;
    for(auto n : notes) {
        str += "\n" + QString::fromStdString(Stroke::NoteToString(n));
    }
    notesLabel->setProperty(LABEL_TEXT, str);
}

void RecordNotePage::up()
{
    if(currentNote == Stroke::Note::G) {
        currentNote = Stroke::Note::Ab;
    } else {
        currentNote = (Stroke::Note)((int)currentNote + 1);
    }
    noteLabel->setProperty(LABEL_TEXT, NOTE_LABEL_BASE_TEXT +
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
