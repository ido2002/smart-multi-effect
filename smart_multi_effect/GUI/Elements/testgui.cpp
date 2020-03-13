#include "testgui.h"

#include "conf.h"
#include "SoundProcessing/soundprocessor.h"


using namespace QtCharts;
using namespace CONF::SOUND_CARD;
using namespace CONF::SOUND_PROCCESSING;
using namespace sound_processing;

TestGui::chartData volumeChart;
TestGui::chartData fftChart;
TestGui::chartData noteChart;
TestGui::chartData octaveChart;

void TestGui::show_volume_test(SoundProcessor &soundProccessor, int width, int height, double min, double max)
{
    volumeChart.barSet = new QBarSet("VOLUME");
    volumeChart.barSeries = new QBarSeries();
    volumeChart.barSeries->append(volumeChart.barSet);
    volumeChart.barSet->setColor(Qt::green);


    volumeChart.chart = new QChart();
    volumeChart.chart->addSeries(volumeChart.barSeries);
    volumeChart.chart->setTitle("VOLUME");
    volumeChart.chart->setAnimationOptions(QChart::SeriesAnimations);


    volumeChart.categories = new QStringList;
    volumeChart.categories->insert(0, "Volume");
    volumeChart.barSet->insert(0, 0);

    volumeChart.axisX = new QBarCategoryAxis();
    volumeChart.axisX->append(*volumeChart.categories);
    volumeChart.chart->addAxis(volumeChart.axisX, Qt::AlignBottom);
    volumeChart.barSeries->attachAxis(volumeChart.axisX);

    volumeChart.axisY = new QValueAxis();
    volumeChart.axisY->setRange(min, max);
    volumeChart.chart->addAxis(volumeChart.axisY, Qt::AlignLeft);
    volumeChart.barSeries->attachAxis(volumeChart.axisY);

    volumeChart.chart->legend()->setVisible(true);
    volumeChart.chart->legend()->setAlignment(Qt::AlignBottom);

    volumeChart.chartView = new QChartView(volumeChart.chart);
    volumeChart.chartView->setRenderHint(QPainter::Antialiasing);

    volumeChart.window = new QMainWindow();
    volumeChart.window->setCentralWidget(volumeChart.chartView);
    volumeChart.window->resize(width, height);
    volumeChart.window->show();

    //add logic
    soundProccessor.AddFunctionOnBufferFill([&](int16_t*, size_t, Stroke){
        double vol = soundProccessor.getNoteRecognition().getSumOutput();
        QString volStr = QString::number(vol, 'f', 6);
        QString volLevelStr = QString::fromStdString(soundProccessor.getNoteRecognition().getVolumeLevelStr());
        volumeChart.barSet->replace(0, vol);
        volumeChart.barSet->setLabel(volStr + " ["+ volLevelStr +"]");
    });
}

int fftBlockSize = 0;

void TestGui::show_fft_test(sound_processing::SoundProcessor& soundProccessor, int width, int height, double min, double max, int blockSize)
{
    fftBlockSize = blockSize;

    fftChart.barSet = new QBarSet("FFT");
    fftChart.barSeries = new QBarSeries();
    fftChart.barSeries->append(fftChart.barSet);
    fftChart.barSet->setColor(Qt::red);


    fftChart.chart = new QChart();
    fftChart.chart->addSeries(fftChart.barSeries);
    fftChart.chart->setTitle("FFT");
    fftChart.chart->setAnimationOptions(QChart::SeriesAnimations);


    fftChart.categories = new QStringList;
    for(uint i = 0; i < FFT_SIZE / blockSize; i++) {
        QString str = "";
        str = QString::number(i * blockSize * (SAMPLE_RATE / BUFFER_SIZE));
        fftChart.categories->insert(i, str);
        fftChart.barSet->insert(i, 0);
    }


    fftChart.axisX = new QBarCategoryAxis();
    fftChart.axisX->append(*fftChart.categories);
    fftChart.chart->addAxis(fftChart.axisX, Qt::AlignBottom);
    fftChart.barSeries->attachAxis(fftChart.axisX);

    fftChart.axisY = new QValueAxis();
    fftChart.axisY->setRange(min, max);
    fftChart.chart->addAxis(fftChart.axisY, Qt::AlignLeft);
    fftChart.barSeries->attachAxis(fftChart.axisY);

    fftChart.chart->legend()->setVisible(true);
    fftChart.chart->legend()->setAlignment(Qt::AlignBottom);

    fftChart.chartView = new QChartView(fftChart.chart);
    fftChart.chartView->setRenderHint(QPainter::Antialiasing);

    fftChart.window = new QMainWindow;
    fftChart.window->setCentralWidget(fftChart.chartView);
    fftChart.window->resize(width, height);
    fftChart.window->show();

    //add logic
    soundProccessor.AddFunctionOnBufferFill([&](int16_t*, size_t, Stroke){
        auto fft = soundProccessor.getNoteRecognition().getFFT();

        fftChart.chartView->setUpdatesEnabled(false);
        for(size_t i = 0; i < fft.size(); i += fftBlockSize) {
            double sum = fft[i];
            for(int j = 1; j < fftBlockSize; j++){
                sum += fft[i+j];
            }
            sum /= fftBlockSize;
            fftChart.barSet->replace(i / fftBlockSize, sum);
        }
        fftChart.chartView->setUpdatesEnabled(true);
    });
}

void TestGui::show_notes_test(SoundProcessor &soundProccessor, int width, int height, double min, double max)
{
    noteChart.barSet = new QBarSet("NOTES");
    noteChart.barSeries = new QBarSeries();
    noteChart.barSeries->append(noteChart.barSet);
    noteChart.barSet->setColor(Qt::blue);


    noteChart.chart = new QChart();
    noteChart.chart->addSeries(noteChart.barSeries);
    noteChart.chart->setTitle("NOTES");
    noteChart.chart->setAnimationOptions(QChart::SeriesAnimations);


    noteChart.categories = new QStringList;
    noteChart.categories->insert(0, "Ab");
    noteChart.categories->insert(1, "A");
    noteChart.categories->insert(2, "Bb");
    noteChart.categories->insert(3, "B");
    noteChart.categories->insert(4, "C");
    noteChart.categories->insert(5, "Db");
    noteChart.categories->insert(6, "D");
    noteChart.categories->insert(7, "Eb");
    noteChart.categories->insert(8, "E");
    noteChart.categories->insert(9, "F");
    noteChart.categories->insert(10,"Gb");
    noteChart.categories->insert(11, "G");

    noteChart.barSet->insert(0, 0);
    noteChart.barSet->insert(1, 0);
    noteChart.barSet->insert(2, 0);
    noteChart.barSet->insert(3, 0);
    noteChart.barSet->insert(4, 0);
    noteChart.barSet->insert(5, 0);
    noteChart.barSet->insert(6, 0);
    noteChart.barSet->insert(7, 0);
    noteChart.barSet->insert(8, 0);
    noteChart.barSet->insert(9, 0);
    noteChart.barSet->insert(10, 0);
    noteChart.barSet->insert(11, 0);


    noteChart.axisX = new QBarCategoryAxis();
    noteChart.axisX->append(*noteChart.categories);
    noteChart.chart->addAxis(noteChart.axisX, Qt::AlignBottom);
    noteChart.barSeries->attachAxis(noteChart.axisX);

    noteChart.axisY = new QValueAxis();
    noteChart.axisY->setRange(min, max);
    noteChart.chart->addAxis(noteChart.axisY, Qt::AlignLeft);
    noteChart.barSeries->attachAxis(noteChart.axisY);

    noteChart.chart->legend()->setVisible(true);
    noteChart.chart->legend()->setAlignment(Qt::AlignBottom);

    noteChart.chartView = new QChartView(noteChart.chart);
    noteChart.chartView->setRenderHint(QPainter::Antialiasing);

    noteChart.window = new QMainWindow;
    noteChart.window->setCentralWidget(noteChart.chartView);
    noteChart.window->resize(width, height);
    noteChart.window->show();

    //add logic
    soundProccessor.AddFunctionOnBufferFill([&](int16_t*, size_t, Stroke){
        auto notes = soundProccessor.getNoteRecognition().getNotes();
        for(size_t i = 0; i < notes.size(); i++) {
            noteChart.barSet->replace(i, notes[i]);
        }
    });
}

void TestGui::show_octave_test(SoundProcessor &soundProccessor, int width, int height, double min, double max)
{
    octaveChart.barSet = new QBarSet("OCTAVE");
    octaveChart.barSeries = new QBarSeries();
    octaveChart.barSeries->append(octaveChart.barSet);
    octaveChart.barSet->setColor(Qt::cyan);


    octaveChart.chart = new QChart();
    octaveChart.chart->addSeries(octaveChart.barSeries);
    octaveChart.chart->setTitle("OCTAVE");
    octaveChart.chart->setAnimationOptions(QChart::SeriesAnimations);


    octaveChart.categories = new QStringList;
    octaveChart.categories->insert(0, "Low");
    octaveChart.categories->insert(1, "Mid");
    octaveChart.categories->insert(2, "High");

    octaveChart.barSet->insert(0, 0);
    octaveChart.barSet->insert(1, 0);
    octaveChart.barSet->insert(2, 0);


    octaveChart.axisX = new QBarCategoryAxis();
    octaveChart.axisX->append(*octaveChart.categories);
    octaveChart.chart->addAxis(octaveChart.axisX, Qt::AlignBottom);
    octaveChart.barSeries->attachAxis(octaveChart.axisX);

    octaveChart.axisY = new QValueAxis();
    octaveChart.axisY->setRange(min, max);
    octaveChart.chart->addAxis(octaveChart.axisY, Qt::AlignLeft);
    octaveChart.barSeries->attachAxis(octaveChart.axisY);

    octaveChart.chart->legend()->setVisible(true);
    octaveChart.chart->legend()->setAlignment(Qt::AlignBottom);

    octaveChart.chartView = new QChartView(octaveChart.chart);
    octaveChart.chartView->setRenderHint(QPainter::Antialiasing);

    octaveChart.window = new QMainWindow;
        octaveChart.window->setCentralWidget(octaveChart.chartView);
        octaveChart.window->resize(width, height);
        octaveChart.window->show();

    //add logic
    soundProccessor.AddFunctionOnBufferFill([&](int16_t*, size_t, Stroke){
        auto octaves = soundProccessor.getNoteRecognition().getOctave();
        for(size_t i = 0; i < octaves.size(); i++) {
            octaveChart.barSet->replace(i, octaves[i]);
        }
    });
}
