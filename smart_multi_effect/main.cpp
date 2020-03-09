#define RASPBERRY_PI    0
#define USE_GUI         1
#define USE_SOUNDCARD   0
#define LOAD_NETWORK    0
#define LOAD_DATA       0
#define RECORD_DATA     0
#define LEARN           0
#define SAVE_NETWORK    0
#define SAVE_DATA       0
#define VOLUME_GUI      0
#define FFT_GUI         0
#define NOTES_GUI       0
#define OCTAVE_GUI      0

#define GUI_FFT_FACTOR 0.002
#define GUI_VOLUME_FACTOR 0.08

#include <QQmlApplicationEngine>
#include <QApplication>

#include <QQuickItem>
#include <QQmlComponent>
#include <QDial>
#include <QVariant>

#include <QChartView>
#include <QChart>
#include <QtCharts>
#include <QLineSeries>

#include "SoundProcessing/soundprocessor.h"
#include <iostream>
#include <unistd.h>


#include <limits>

#include "conf.h"
#include "EffectController/effect.h"
#include "EffectController/effectcontroller.h"

#include "GUI/Elements/effect_gui.h"

const QUrl url(QStringLiteral("qrc:/main.qml"));

using namespace QtCharts;
using namespace CONF;
using namespace SOUND_PROCCESSING;
using namespace SOUND_CARD;
using namespace sound_processing;
using namespace hardware_ctrl;

using ms = std::chrono::duration<float, std::milli>;
using namespace std::chrono;

using Note = Stroke::Note;

using namespace std;

using type_element = hardware_ctrl::Effect::EffectControlLayoutEllements;

std::thread* button_thraed = nullptr;

float timerFunc(std::function<void()> func)
{
    auto temp = std::chrono::steady_clock::now();
    func();
    float deltaTime = std::chrono::duration_cast<ms>(std::chrono::steady_clock::now() - temp).count();
    std::cout << "done in " << deltaTime / 1000.0f << " seconds!" << std::endl;
    return deltaTime / 1000.f;
}

void configButtons(hardware_ctrl::EffectController& controller)
{
    controller.AddButton("b1", HARDWARE::BUTTON1);
    controller.AddButton("b2", HARDWARE::BUTTON2);
    controller.AddButton("b3", HARDWARE::BUTTON3);
    controller.AddButton("b4", HARDWARE::BUTTON4);
    controller.AddButton("b5", HARDWARE::BUTTON5);

    controller.AddButtonEvent("b1",[](EffectController* controller){
        for(int i = 0; i <= 100; i++) {
            controller->GetEffect(NAMES::OVERDRIVE)->GetPotentiometer(type_element::Gain)->SetTarget(i);
            controller->GetEffect(NAMES::OVERDRIVE)->GetPotentiometer(type_element::Volume)->SetTarget(100 - i/5);
            controller->GetEffect(NAMES::OVERDRIVE)->GetPotentiometer(type_element::Tone)->SetTarget(80+ i/8);
            controller->GetEffect(NAMES::OVERDRIVE)->On();

            controller->GetEffect(NAMES::DELAY)->GetPotentiometer(type_element::Delay)->SetTarget(30);
            controller->GetEffect(NAMES::DELAY)->GetPotentiometer(type_element::Volume)->SetTarget(50 + i/4);
            controller->GetEffect(NAMES::DELAY)->On();

            controller->GetEffect(NAMES::TREMOLO)->GetPotentiometer(type_element::Speed)->SetTarget(10);
            controller->GetEffect(NAMES::TREMOLO)->Off();

            controller->SetAllToValue();
            usleep(1000 * 10);
        }
    });

    controller.AddButtonEvent("b2",[](EffectController* controller){
        controller->GetEffect(NAMES::OVERDRIVE)->GetPotentiometer(type_element::Gain)->SetTarget(0);
        controller->GetEffect(NAMES::OVERDRIVE)->GetPotentiometer(type_element::Volume)->SetTarget(100);
        controller->GetEffect(NAMES::OVERDRIVE)->GetPotentiometer(type_element::Tone)->SetTarget(80);
        controller->GetEffect(NAMES::OVERDRIVE)->On();

        controller->GetEffect(NAMES::DELAY)->GetPotentiometer(type_element::Delay)->SetTarget(30);
        controller->GetEffect(NAMES::DELAY)->GetPotentiometer(type_element::Volume)->SetTarget(50);
        controller->GetEffect(NAMES::DELAY)->On();

        controller->GetEffect(NAMES::TREMOLO)->GetPotentiometer(type_element::Speed)->SetTarget(10);
        controller->GetEffect(NAMES::TREMOLO)->Off();

        controller->SetAllToValue();
    });

    controller.AddButtonEvent("b3",[](EffectController* controller){
        controller->GetEffect(NAMES::OVERDRIVE)->GetPotentiometer(type_element::Gain)->SetTarget(100);
        controller->GetEffect(NAMES::OVERDRIVE)->GetPotentiometer(type_element::Volume)->SetTarget(70);
        controller->GetEffect(NAMES::OVERDRIVE)->GetPotentiometer(type_element::Tone)->SetTarget(75);
        controller->GetEffect(NAMES::OVERDRIVE)->Off();

        controller->GetEffect(NAMES::DELAY)->GetPotentiometer(type_element::Delay)->SetTarget(50);
        controller->GetEffect(NAMES::DELAY)->GetPotentiometer(type_element::Volume)->SetTarget(30);
        controller->GetEffect(NAMES::DELAY)->On();

        controller->GetEffect(NAMES::TREMOLO)->GetPotentiometer(type_element::Speed)->SetTarget(50);
        controller->GetEffect(NAMES::TREMOLO)->On();

        controller->SetAllToValue();
    });

    controller.AddButtonEvent("b4",[](EffectController* controller){
        controller->GetEffect(NAMES::OVERDRIVE)->GetPotentiometer(type_element::Gain)->SetTarget(100);
        controller->GetEffect(NAMES::OVERDRIVE)->GetPotentiometer(type_element::Volume)->SetTarget(70);
        controller->GetEffect(NAMES::OVERDRIVE)->GetPotentiometer(type_element::Tone)->SetTarget(75);
        controller->GetEffect(NAMES::OVERDRIVE)->Off();

        controller->GetEffect(NAMES::DELAY)->GetPotentiometer(type_element::Delay)->SetTarget(50);
        controller->GetEffect(NAMES::DELAY)->GetPotentiometer(type_element::Volume)->SetTarget(30);
        controller->GetEffect(NAMES::DELAY)->Off();

        controller->GetEffect(NAMES::TREMOLO)->GetPotentiometer(type_element::Speed)->SetTarget(10);
        controller->GetEffect(NAMES::TREMOLO)->Off();

        controller->SetAllToValue();
    });

    controller.AddButtonEvent("b5",[](EffectController* controller){
        controller->GetEffect(NAMES::OVERDRIVE)->GetPotentiometer(type_element::Gain)->SetTarget(100);
        controller->GetEffect(NAMES::OVERDRIVE)->GetPotentiometer(type_element::Volume)->SetTarget(70);
        controller->GetEffect(NAMES::OVERDRIVE)->GetPotentiometer(type_element::Tone)->SetTarget(100);
        controller->GetEffect(NAMES::OVERDRIVE)->On();

        controller->GetEffect(NAMES::DELAY)->GetPotentiometer(type_element::Delay)->SetTarget(25);
        controller->GetEffect(NAMES::DELAY)->GetPotentiometer(type_element::Volume)->SetTarget(10);
        controller->GetEffect(NAMES::DELAY)->On();

        controller->GetEffect(NAMES::TREMOLO)->GetPotentiometer(type_element::Speed)->SetTarget(100);
        controller->GetEffect(NAMES::TREMOLO)->Off();

        controller->SetAllToValue();
    });

    button_thraed = new std::thread([&]() {
        while(true) {
            controller.UpdateButtons();
        }
    });
}

int main(int argc, char *argv[])
{
    //start the application
    QApplication app(argc, argv);

#if RASPBERRY_PI
    hardware_ctrl::EffectController controller(HARDWARE::INC_PIN, HARDWARE::UD_PIN);
    controller.Initialize();
    controller.SetAllToValue_Long();
    configButtons(controller);
#endif

#if USE_GUI
    QQmlApplicationEngine engine;
    engine.load(url);

    //get main window
    qDebug() << engine.rootObjects()[0];
    QQuickItem* parent = engine.rootObjects()[0]->findChild<QQuickItem*>("myRect");

#if RASPBERRY_PI
    Effect* e1 = controller.GetEffect(NAMES::OVERDRIVE);

    GUI_elements::Effect_gui e1G(QString::fromStdString(NAMES::OVERDRIVE), parent, &engine, e1);
#endif

#endif


#if USE_SOUNDCARD
    SoundProcessor soundProccessor;


#if LOAD_DATA
    soundProccessor.getNoteRecognition().LoadNetworkDataSets();
#endif


#if RECORD_DATA
    std::cout << "A..." << std::endl;
    soundProccessor.RecordNoteSample({Note::A});
    std::cout << "A..." << std::endl;
    soundProccessor.RecordNoteSample({Note::A});
    std::cout << "A..." << std::endl;
    soundProccessor.RecordNoteSample({Note::A});

    std::cout << "D..." << std::endl;
    soundProccessor.RecordNoteSample({Note::D});
    std::cout << "D..." << std::endl;
    soundProccessor.RecordNoteSample({Note::D});
    std::cout << "D..." << std::endl;
    soundProccessor.RecordNoteSample({Note::D});

    std::cout << "low..." << std::endl;
    soundProccessor.RecordOctaveSample({1.0f, 0.0f, 0.0f});
    std::cout << "low..." << std::endl;
    soundProccessor.RecordOctaveSample({1.0f, 0.0f, 0.0f});
    std::cout << "low..." << std::endl;
    soundProccessor.RecordOctaveSample({1.0f, 0.0f, 0.0f});

    std::cout << "mid..." << std::endl;
    soundProccessor.RecordOctaveSample({0.0f, 1.0f, 0.0f});
    std::cout << "mid..." << std::endl;
    soundProccessor.RecordOctaveSample({0.0f, 1.0f, 0.0f});
    std::cout << "mid..." << std::endl;
    soundProccessor.RecordOctaveSample({0.0f, 1.0f, 0.0f});

    std::cout << "high..." << std::endl;
    soundProccessor.RecordOctaveSample({0.0f, 0.0f, 1.0f});
    std::cout << "high..." << std::endl;
    soundProccessor.RecordOctaveSample({0.0f, 0.0f, 1.0f});
    std::cout << "high..." << std::endl;
    soundProccessor.RecordOctaveSample({0.0f, 0.0f, 1.0f});
#endif


#if LOAD_NETWORK
    soundProccessor.getNoteRecognition().LoadNetwork();
#endif


#if LEARN
    soundProccessor.Learn();
#endif


#if SAVE_NETWORK
    soundProccessor.getNoteRecognition().SaveNetwork();
#endif


#if SAVE_DATA
    soundProccessor.getNoteRecognition().SaveNetworkDataSets();
#endif


#if VOLUME_GUI
    QBarSet* volume_barSet = new QBarSet("VOLUME");
    QBarSeries* volume_barSeries = new QBarSeries();
    volume_barSeries->append(volume_barSet);
    volume_barSet->setColor(Qt::green);


    QChart *volume_chart = new QChart();
    volume_chart->addSeries(volume_barSeries);
    volume_chart->setTitle("VOLUME");
    volume_chart->setAnimationOptions(QChart::SeriesAnimations);


    QStringList volume_categories;
    volume_categories.insert(0, "Volume");
    volume_barSet->insert(0, 0);

    QBarCategoryAxis *volume_axisX = new QBarCategoryAxis();
    volume_axisX->append(volume_categories);
    volume_chart->addAxis(volume_axisX, Qt::AlignBottom);
    volume_barSeries->attachAxis(volume_axisX);

    QValueAxis *volume_axisY = new QValueAxis();
    volume_axisY->setRange(0, 1 * GUI_VOLUME_FACTOR);
    volume_chart->addAxis(volume_axisY, Qt::AlignLeft);
    volume_barSeries->attachAxis(volume_axisY);

    volume_chart->legend()->setVisible(true);
    volume_chart->legend()->setAlignment(Qt::AlignBottom);

    QChartView *volume_chartView = new QChartView(volume_chart);
    volume_chartView->setRenderHint(QPainter::Antialiasing);

    QMainWindow volume_window;
        volume_window.setCentralWidget(volume_chartView);
        volume_window.resize(400, 500);
        volume_window.show();

    //add logic
    soundProccessor.AddFunctionOnBufferFill([&](int16_t*, size_t, Stroke){
        double vol = soundProccessor.getNoteRecognition().getSumOutput();
        QString volStr = QString::number(vol, 'f', 6);
        QString volLevelStr = QString::fromStdString(soundProccessor.getNoteRecognition().getVolumeLevelStr());
        volume_barSet->replace(0, vol);
        volume_barSet->setLabel(volStr + " ["+ volLevelStr +"]");
    });
#endif

#if FFT_GUI
    int blockSize = 2;

    QBarSet* fft_barSet = new QBarSet("FFT");
    QBarSeries* fft_barSeries = new QBarSeries();
    fft_barSeries->append(fft_barSet);
    fft_barSet->setColor(Qt::red);


    QChart *fft_chart = new QChart();
    fft_chart->addSeries(fft_barSeries);
    fft_chart->setTitle("FFT");
    fft_chart->setAnimationOptions(QChart::SeriesAnimations);


    QStringList fft_categories;
    for(uint i = 0; i < FFT_SIZE / blockSize; i++) {
        QString str = "";
        str = QString::number(i * blockSize * (SAMPLE_RATE / BUFFER_SIZE));
        fft_categories.insert(i, str);
        fft_barSet->insert(i, 0);
    }


    QBarCategoryAxis *fft_axisX = new QBarCategoryAxis();
    fft_axisX->append(fft_categories);
    fft_chart->addAxis(fft_axisX, Qt::AlignBottom);
    fft_barSeries->attachAxis(fft_axisX);

    QValueAxis *fft_axisY = new QValueAxis();
    fft_axisY->setRange(0, 1 * GUI_FFT_FACTOR);
    fft_chart->addAxis(fft_axisY, Qt::AlignLeft);
    fft_barSeries->attachAxis(fft_axisY);

    fft_chart->legend()->setVisible(true);
    fft_chart->legend()->setAlignment(Qt::AlignBottom);

    QChartView *fft_chartView = new QChartView(fft_chart);
    fft_chartView->setRenderHint(QPainter::Antialiasing);

    QMainWindow fft_window;
        fft_window.setCentralWidget(fft_chartView);
        fft_window.resize(800, 500);
        fft_window.show();

    //add logic
    soundProccessor.AddFunctionOnBufferFill([&](int16_t*, size_t, Stroke){
        auto fft = soundProccessor.getNoteRecognition().getFFT();

        fft_chartView->setUpdatesEnabled(false);
        for(size_t i = 0; i < fft.size(); i += blockSize) {
            double sum = fft[i];
            for(int j = 1; j < blockSize; j++){
                sum += fft[i+j];
            }
            sum /= blockSize;
            fft_barSet->replace(i / blockSize, sum);
        }
        fft_chartView->setUpdatesEnabled(true);
    });
#endif


#if NOTES_GUI
    QBarSet* notes_barSet = new QBarSet("NOTES");
    QBarSeries* notes_barSeries = new QBarSeries();
    notes_barSeries->append(notes_barSet);
    notes_barSet->setColor(Qt::blue);


    QChart *notes_chart = new QChart();
    notes_chart->addSeries(notes_barSeries);
    notes_chart->setTitle("NOTES");
    notes_chart->setAnimationOptions(QChart::SeriesAnimations);


    QStringList noets_categories;
    noets_categories.insert(0, "Ab");
    noets_categories.insert(1, "A");
    noets_categories.insert(2, "Bb");
    noets_categories.insert(3, "B");
    noets_categories.insert(4, "C");
    noets_categories.insert(5, "Db");
    noets_categories.insert(6, "D");
    noets_categories.insert(7, "Eb");
    noets_categories.insert(8, "E");
    noets_categories.insert(9, "F");
    noets_categories.insert(10,"Gb");
    noets_categories.insert(11, "G");

    notes_barSet->insert(0, 0);
    notes_barSet->insert(1, 0);
    notes_barSet->insert(2, 0);
    notes_barSet->insert(3, 0);
    notes_barSet->insert(4, 0);
    notes_barSet->insert(5, 0);
    notes_barSet->insert(6, 0);
    notes_barSet->insert(7, 0);
    notes_barSet->insert(8, 0);
    notes_barSet->insert(9, 0);
    notes_barSet->insert(10, 0);
    notes_barSet->insert(11, 0);


    QBarCategoryAxis *notes_axisX = new QBarCategoryAxis();
    notes_axisX->append(noets_categories);
    notes_chart->addAxis(notes_axisX, Qt::AlignBottom);
    notes_barSeries->attachAxis(notes_axisX);

    QValueAxis *notes_axisY = new QValueAxis();
    notes_axisY->setRange(0, 1);
    notes_chart->addAxis(notes_axisY, Qt::AlignLeft);
    notes_barSeries->attachAxis(notes_axisY);

    notes_chart->legend()->setVisible(true);
    notes_chart->legend()->setAlignment(Qt::AlignBottom);

    QChartView *notes_chartView = new QChartView(notes_chart);
    notes_chartView->setRenderHint(QPainter::Antialiasing);

    QMainWindow notes_window;
        notes_window.setCentralWidget(notes_chartView);
        notes_window.resize(600, 500);
        notes_window.show();

    //add logic
    soundProccessor.AddFunctionOnBufferFill([&](int16_t*, size_t, Stroke){
        auto notes = soundProccessor.getNoteRecognition().getNotes();
        for(size_t i = 0; i < notes.size(); i++) {
            notes_barSet->replace(i, notes[i]);
        }
    });
#endif


#if OCTAVE_GUI
    QBarSet* octave_barSet = new QBarSet("OCTAVE");
    QBarSeries* octave_barSeries = new QBarSeries();
    octave_barSeries->append(octave_barSet);
    octave_barSet->setColor(Qt::cyan);


    QChart *octave_chart = new QChart();
    octave_chart->addSeries(octave_barSeries);
    octave_chart->setTitle("OCTAVE");
    octave_chart->setAnimationOptions(QChart::SeriesAnimations);


    QStringList octave_categories;
    octave_categories.insert(0, "Low");
    octave_categories.insert(1, "Mid");
    octave_categories.insert(2, "High");

    octave_barSet->insert(0, 0);
    octave_barSet->insert(1, 0);
    octave_barSet->insert(2, 0);


    QBarCategoryAxis *octave_axisX = new QBarCategoryAxis();
    octave_axisX->append(octave_categories);
    octave_chart->addAxis(octave_axisX, Qt::AlignBottom);
    octave_barSeries->attachAxis(octave_axisX);

    QValueAxis *octave_axisY = new QValueAxis();
    octave_axisY->setRange(0, 1);
    octave_chart->addAxis(octave_axisY, Qt::AlignLeft);
    octave_barSeries->attachAxis(octave_axisY);

    octave_chart->legend()->setVisible(true);
    octave_chart->legend()->setAlignment(Qt::AlignBottom);

    QChartView *octave_chartView = new QChartView(octave_chart);
    octave_chartView->setRenderHint(QPainter::Antialiasing);

    QMainWindow octave_window;
        octave_window.setCentralWidget(octave_chartView);
        octave_window.resize(300, 500);
        octave_window.show();

    //add logic
    soundProccessor.AddFunctionOnBufferFill([&](int16_t* buffer, size_t bufferSize, Stroke){
        auto octaves = soundProccessor.getNoteRecognition().getOctave();
        for(size_t i = 0; i < octaves.size(); i++) {
            octave_barSet->replace(i, octaves[i]);
        }
    });
#endif
    soundProccessor.Start();
#endif

    return app.exec();
}
