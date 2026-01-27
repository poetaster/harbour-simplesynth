#ifndef SYNTHESIZER_H
#define SYNTHESIZER_H

#include <QtCore/QObject>
#include "../libsynth/include/libsynth.hpp"


class SpeedHook : public SoundGeneratorVarHook<float>
{
public:
    SpeedHook() : SoundGeneratorVarHook(&speed, 0, 200, "hook_speed"){};
   atomic<float> speed;  // from 0 to 200

};

class FreqOneHook : public SoundGeneratorVarHook<long>
{
public:
   FreqOneHook() : SoundGeneratorVarHook(&freq, 1, 1000, "freq_one"){};
   atomic<long> freq;  // from 0 to 200

};
class Synthesizer : public QObject
{
    Q_OBJECT
    //Q_PROPERTY(QString voiceDesc READ)
/*QML_ELEMENT*/
    ;

public:
    explicit Synthesizer(QObject *parent = nullptr);
    ~Synthesizer();
    QString getVoiceDesc();
    Q_INVOKABLE void setVoiceDesc(const QString &voiceDesc);
    Q_INVOKABLE void setDuration(long duration);
    Q_INVOKABLE void setFadeIn(long duration);
    Q_INVOKABLE void setFadeOut(long duration);
    Q_INVOKABLE void setSpeedOne(long duration);
    Q_INVOKABLE void setFreqOne(long frequency);
    Q_INVOKABLE void play();

signals:
    void voiceDescChanged();

private:
    QString m_voiceDesc;
    long m_duration;
    long m_fadeIn;
    long m_fadeOut;
    SoundGenerator*  m_g = SoundGenerator::factory(qPrintable(m_voiceDesc));
    SpeedHook* engine_speed;
    FreqOneHook* freq_one;
    uint32_t ech = 48000;
    const int BUF_LENGTH = 1024;
};



//SpeedHook* engine_speed = new SpeedHook();

/*
while(true) {
    ...
    engine_speed.speed = 30;   <- sound will adapt accordingly
    ...
}
*/


#endif // SYNTHESIZER_H
