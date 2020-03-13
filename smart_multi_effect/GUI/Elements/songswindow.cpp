#include "songswindow.h"
#include "conf.h"

using namespace CONF::GUI_PARAMETERS::SONGS_PAGE;


SongsWindow::SongsWindow(QQmlApplicationEngine *engine, QQuickItem *parent)
{
    //create component
    QQmlComponent comp(engine, parent);
    comp.loadUrl(SONGS_URL);

    //add element
    window = qobject_cast<QQuickItem *>(comp.create());
    engine->setObjectOwnership(window, QQmlEngine::JavaScriptOwnership);
    window->setParentItem(parent);
    window->setVisible(false);
}

void SongsWindow::Show()
{
    window->setVisible(true);
}

void SongsWindow::Hide()
{
    window->setVisible(false);
}

void SongsWindow::choose()
{

}

void SongsWindow::left()
{
    index--;
    if(index < 0) index = frames.size() - 1;
}

void SongsWindow::right()
{
    index++;
    if(index >= (int)frames.size()) index = 0;
}

void SongsWindow::AddFrame(SongFrame *frame)
{
    frames.push_back(frame);
}

SongFrame *SongsWindow::getCurrentSong()
{
    if(frames.size() == 0) {
        return nullptr;
    }
    return frames[index];
}
