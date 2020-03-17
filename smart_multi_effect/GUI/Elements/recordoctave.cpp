#include "recordoctave.h"

#include "conf.h"

using namespace CONF::GUI_PARAMETERS::OCTAVE_RECORDING_PAGE;
using namespace CONF::GUI_PARAMETERS::GENERAL_GUI_PROPERTIES_NAMES;
using namespace sound_processing;

RecordOctavePage::RecordOctavePage(QQmlApplicationEngine *engine, QQuickItem *parent)
{
    //create component
    QQmlComponent comp(engine, parent);
    comp.loadUrl(OCTAVE_RECORDING_PAGE_URL);

    //add element
    window = qobject_cast<QQuickItem *>(comp.create());
    engine->setObjectOwnership(window, QQmlEngine::JavaScriptOwnership);
    window->setParentItem(parent);
    window->setVisible(false);

    busyIndicator = window->findChild<QQuickItem*>(BUSY_INDICATOR);
    busyIndicator->setVisible(false);
    octavesLabel = window->findChild<QQuickItem*>(OCTAVES_LABEL);
    octaveLabel = window->findChild<QQuickItem*>(OCTAVE_LABEL);
}

void RecordOctavePage::Show()
{
    window->setVisible(true);
}

void RecordOctavePage::Hide()
{
    window->setVisible(false);
}

int RecordOctavePage_counter = 0;

void RecordOctavePage::update()
{
    if(recordingThread == nullptr) {
        busyIndicator->setVisible(false);
    } else {
        if(RecordOctavePage_counter < 2){
            RecordOctavePage_counter++;
            return;
        }
        RecordOctavePage_counter = 0;
        recordingThread->join();
        recordingThread = nullptr;
        //octaves.clear();
        UpdateList();
    }
}

void RecordOctavePage::UpdateList()
{
    QString str = OCTAVES_LABEL_BASE_TEXT;
    for(auto o : octaves) {
        str += "\n" + QString::fromStdString(Stroke::NoteOctaveToString(o));
    }
    octavesLabel->setProperty(LABEL_TEXT, str);
}

void RecordOctavePage::up()
{
    if(currentOctave == Stroke::NoteOctave::High) {
        currentOctave = Stroke::NoteOctave::Low;
    } else {
        currentOctave = (Stroke::NoteOctave)((int)currentOctave + 1);
    }
    octaveLabel->setProperty(LABEL_TEXT, OCTAVE_LABEL_BASE_TEXT +
                           QString::fromStdString(Stroke::NoteOctaveToString(currentOctave)));
}

void RecordOctavePage::add()
{
    if(std::find(octaves.begin(), octaves.end(), currentOctave) == octaves.end()) {
        octaves.push_back(currentOctave);
        std::sort(octaves.begin(), octaves.end());
        UpdateList();
    }
}

void RecordOctavePage::remove()
{
    auto it = std::find(octaves.begin(), octaves.end(), currentOctave);
    if(it != octaves.end()) {
        octaves.erase(it);
        UpdateList();
    }
}

void RecordOctavePage::record(SoundProcessor *soundProcessor)
{
    if(recordingThread == nullptr && octaves.size() > 0) {
        busyIndicator->setVisible(true);
        octavesVector = new std::vector<float>(3, 0);
        if(std::find(octaves.begin(), octaves.end(), Stroke::NoteOctave::Low) == octaves.end()) {
            (*octavesVector)[0] = 1;
        }
        if(std::find(octaves.begin(), octaves.end(), Stroke::NoteOctave::Mid) == octaves.end()) {
            (*octavesVector)[1] = 1;
        }
        if(std::find(octaves.begin(), octaves.end(), Stroke::NoteOctave::High) == octaves.end()) {
            (*octavesVector)[2] = 1;
        }
        this->soundProcessor = soundProcessor;
        recordingThread = new std::thread([&]() {
            this->soundProcessor->RecordOctaveSample(*octavesVector);
            delete octavesVector;
        });
    }
}
