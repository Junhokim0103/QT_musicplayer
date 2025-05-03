#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QSlider>
#include <QMediaMetaData>
#include <QFileSystemModel>
#include <QListView>
//#include <QMediaPlaylist>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void initvolumeslder(void);
    void filesysteminit(void);

private:
    Ui::Widget *ui;
    QMediaPlayer *player;
    QAudioOutput *audioOutput;
    qint64 duration;
    QFileSystemModel *model;
    QString filename;
    QString filepath;

private slots:
    void startmusic(void);
    void applyVolume(int volumeSliderValue);
    void setsliderpos(qint64 pos);
    void stopplayer(void);
    void pauseplayer(void);
    void listveiwindex(const QModelIndex &list);
    void addlist(void);
};
#endif // WIDGET_H
