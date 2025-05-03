#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->verticalSlider->setMinimum(0);
    ui->verticalSlider->setMaximum(100);
    filesysteminit();
    player = new QMediaPlayer;
    audioOutput = new QAudioOutput;
    player->setAudioOutput(audioOutput);

    //player->setSource(QUrl::fromLocalFile("C:/data/음악/[(팝송) 비틀즈 - 렛잇비].mp3"));

    //qDebug()<<"duration : "<<duration;
    //audioOutput->setVolume(50);
    //connect(verticalSliders, &SlidersGroup::valueChanged, verticalSliders, &SlidersGroup::setValue);//volume
    //connect(verticalSliders, &SlidersGroup::valueChanged, verticalSliders, &QSlider::TickPosition position);//play pos
    connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(setsliderpos(qint64)));//positionChanged(qint64)));
    connect(ui->verticalSlider, SIGNAL(sliderMoved(int)),this, SLOT(applyVolume(int)));
    connect(ui->pushButton, SIGNAL(released()),this, SLOT(startmusic()));
    connect(ui->pushButton_2, SIGNAL(released()),this, SLOT(stopplayer()));
    connect(ui->pushButton_3, SIGNAL(released()),this, SLOT(pauseplayer()));
    //connect(ui->listView, SIGNAL(indexesMoved(const QModelIndexList)),this, SLOT(listveiwindex(const QModelIndexList)));
    //connect(ui->listView, SIGNAL(activated(const QModelIndex)),this, SLOT(listveiwindex(const QModelIndex)));
    connect(ui->listView, SIGNAL(clicked(const QModelIndex)),this, SLOT(listveiwindex(const QModelIndex)));
    connect(ui->pushButton_4, SIGNAL(released()),this, SLOT(addlist()));
    initvolumeslder();
    //connect(ui->pushButton_4, &QPushButton::released, this, &Widget::readslotfunc);

    //ui->horizontalSlider->

}

Widget::~Widget()
{
    delete ui;
}

void Widget::applyVolume(int volumeSliderValue)
{
    // volumeSliderValue is in the range [0..100]

    //qreal linearVolume = QAudio::convertVolume(volumeSliderValue / qreal(100.0),QAudio::LinearVolumeScale, QAudio::LinearVolumeScale);
    //QAudio::convertVolume
    float volume = (float)volumeSliderValue/(float)100;
    audioOutput->setVolume(volume);//0(minimum)~1.0(max)
}
void Widget::startmusic(void)
{
    player->play();
    initvolumeslder();
    //QString albumtitle =player->metaData().metaDataKeyToString(player->metaData().AlbumTitle);
      //  player->metaData().AlbumTitle;toString()
    //QVariant albumtitle = player->metaData().value(player->metaData().AlbumTitle);
    QString albumtitle = player->metaData().stringValue(QMediaMetaData::AlbumTitle);
    //QImage imgaethumnail
    //QVariant tempdata = player->metaData().value(QMediaMetaData::ThumbnailImage);//player->metaData().ThumbnailImage
                               //player->metaData().Title;
    //QByteArray bytedataarray = tempdata.toByteArray();
    //QImage imgaethumnail;
    //imgaethumnail.fromData(bytedataarray);
    //player->metaObject().
    //QVariant variant;
    //...
    //QImage image = tempdata.value<QImage>();
    //ui->graphicsView->setBackgroundBrush(tempdata);
    ui->label_2->setText(albumtitle);//ThumbnailImage
    qDebug()<<albumtitle;

}

void Widget::setsliderpos(qint64 pos)
{
    qDebug()<<"pos : "<<pos;
    duration = player->duration();
    qDebug()<<"duration: "<<duration;
    int temp = (int)((float)100*(float)pos/(float)duration);
    qDebug()<<"setposition: "<<temp;
    ui->horizontalSlider->setSliderPosition(temp);
}
void Widget::initvolumeslder(void)
{
    float volumetemp = 0;
    volumetemp = audioOutput->volume();
    qDebug()<<"volume:"<<volumetemp;
    int intvolumetemp = 0;
    intvolumetemp = (int)(volumetemp*((float)100));
    ui->verticalSlider->setSliderPosition(intvolumetemp);
}
void Widget::stopplayer(void)
{
    player->stop();
}
void Widget::pauseplayer(void)
{
    player->pause();
}
void Widget::filesysteminit(void)
{
    model = new QFileSystemModel;
    model->setRootPath(QDir::currentPath());

    ui->listView->setModel(model);
    ui->listView->setRootIndex(model->index(QDir::currentPath()));
    //ui->listView->
}
void Widget::listveiwindex(const QModelIndex &list)
{
    //qDebug()<<list.data();
    qDebug()<<"list slot";
    int col = 0;
    col = list.column();
    int row = 0;
    row = list.row();
    qDebug()<<"col:"<<col<<",row:"<<row;
    filename = model->fileName(list);
    filepath = model->filePath(list);
    qDebug()<<filename+filepath;
    qDebug()<<filepath;
    player->setSource(QUrl::fromLocalFile(filepath));
    //ui->listView->activated();
    //ui->listView->activated()
    ui->label->setText(filename);
}
/*
void Widget::listgetdata(void)
{
   QModelIndexList data = ui->listView->selectedIndexes();

}
*/
void Widget::addlist(void)
{
    /*
QUrl::fromLocalFile(filepath)
        playlist = new QMediaPlaylist;
    playlist->addMedia(QUrl("http://example.com/movie1.mp4"));
    playlist->addMedia(QUrl("http://example.com/movie2.mp4"));
    playlist->addMedia(QUrl("http://example.com/movie3.mp4"));
    playlist->setCurrentIndex(1);

    player = new QMediaPlayer;
    player->setPlaylist(playlist);

    videoWidget = new QVideoWidget;
    player->setVideoOutput(videoWidget);
    videoWidget->show();

    player->play();
*/
}
