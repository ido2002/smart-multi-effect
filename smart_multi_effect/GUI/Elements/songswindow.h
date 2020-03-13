#ifndef SONGSWINDOW_H
#define SONGSWINDOW_H

#include <QQuickItem>
#include <QQmlApplicationEngine>
#include "songframe.h"
#include <vector>

class SongsWindow
{
public:
    SongsWindow(QQmlApplicationEngine* engine, QQuickItem* parent);

    void Show();
    void Hide();

    void choose();
    void left();
    void right();

    void AddFrame(SongFrame* frame);

    SongFrame* getCurrentSong();

private:
    QQuickItem* window = nullptr;
    std::vector<SongFrame*> frames;
    int index = 0;
};

#endif // SONGSWINDOW_H
