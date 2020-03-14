#include "recordnote.h"
#include "conf.h"

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
    notesLable = window->findChild<QQuickItem*>(NOTES_LABLE);
    noteLable = window->findChild<QQuickItem*>(NOTE_LABLE);
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
    if(recordingThread == nullptr && notes.size() > 0) {
        busyIndicator->setVisible(true);
        recordingThread = new std::thread([&]() {
            soundProcessor->RecordNoteSample(notes);
        });
    }
}
