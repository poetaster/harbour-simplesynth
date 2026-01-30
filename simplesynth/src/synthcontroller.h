#ifndef SYNTHCONTROLLER_H
#define SYNTHCONTROLLER_H

#include <QDebug>
#include <QtCore/QObject>
#include "synthesizer.h"

class SynthController : public QObject
{
    Q_OBJECT
    //Q_PROPERTY(QString voiceDesc READ)
/*QML_ELEMENT*/
    ;

public:
    explicit SynthController(QObject *parent = nullptr);
    ~SynthController();
    QString getVoiceDesc();
    Q_INVOKABLE void setVoiceDesc(const QString &voiceDesc);
    Q_INVOKABLE void setDuration(long duration);
    Q_INVOKABLE void setFadeIn(long duration);
    Q_INVOKABLE void setFadeOut(long duration);
    Q_INVOKABLE void setSpeedOne(long duration);
    Q_INVOKABLE void setFreqOne(long freq);
    Q_INVOKABLE void play();

signals:
    void voiceDescChanged();
    void playing();
    void start();
    void done(bool r);

private:
    QString m_voiceDesc;
    long m_duration;
    long m_fadeIn;
    long m_fadeOut;
    QThread * t;
    Synthesizer * w;
};



#endif // SYNTHCONTROLLER_H
