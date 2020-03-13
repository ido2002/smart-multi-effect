#ifndef TESTGUI_H
#define TESTGUI_H

#include "SoundProcessing/soundprocessor.h"

#include <QBarSet>
#include <QBarSeries>
#include <QChart>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QChartView>
#include <QMainWindow>

namespace TestGui {
    void show_volume_test(sound_processing::SoundProcessor& soundProccessor, int width, int height, double min = 0, double max = 1);
    void show_fft_test(sound_processing::SoundProcessor& soundProccessor, int width, int height, double min = 0, double max = 1, int blockSize = 2);
    void show_notes_test(sound_processing::SoundProcessor& soundProccessor, int width, int height, double min = 0, double max = 1);
    void show_octave_test(sound_processing::SoundProcessor& soundProccessor, int width, int height, double min = 0, double max = 1);

    struct chartData
    {
        QtCharts::QBarSet*          barSet      = nullptr;
        QtCharts::QBarSeries*       barSeries   = nullptr;
        QtCharts::QChart*           chart       = nullptr;
        QStringList*                categories  = nullptr;
        QtCharts::QBarCategoryAxis* axisX       = nullptr;
        QtCharts::QValueAxis*       axisY       = nullptr;
        QtCharts::QChartView*       chartView   = nullptr;
        QMainWindow*                window      = nullptr;
    };
};

#endif // TESTGUI_H
