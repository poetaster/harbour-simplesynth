#ifndef SYNTHESIZER_H
#define SYNTHESIZER_H

#include <QDebug>
#include <QtCore/QObject>
#include "../libsynth/include/libsynth.hpp"

class SpeedHook : public SoundGeneratorVarHook<float>
{
public:
    SpeedHook() : SoundGeneratorVarHook(&speed, 0, 200, "s1"){};
   atomic<float> speed;  // from 0 to 200

};

class FreqOneHook : public SoundGeneratorVarHook<long>
{
public:
   FreqOneHook() : SoundGeneratorVarHook(&freq, 1, 1000, "f1"){};
   atomic<long> freq;  // from 1 to 1000

};

//atomic<float> engine_speed;	// Float value that represents the engine speed

class EngineSpeedHook : public SoundGeneratorVarHook<float>
{
    public:
        atomic<float> engine_speed;	// Float value that represents the engine speed
        EngineSpeedHook() : SoundGeneratorVarHook(&engine_speed, 0.0, 100.0, "engine_speed"){}
        void setSpeed(float v)
        {
            engine_speed = v;
        }
};

//static EngineSpeedHook instance;	// Needed to register the 'engine_speed' hook so it can be used.a



class Synthesizer : public QObject
{
    Q_OBJECT
    //Q_PROPERTY(QString voiceDesc READ)
/*QML_ELEMENT*/
    ;

public:
    explicit Synthesizer(QObject *parent = nullptr);
    ~Synthesizer(){
      delete m_g;
      delete s1;
      delete f1;
    }

    Q_INVOKABLE QString getVoiceDesc();
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
    void done(bool r);

private:
    QString m_voiceDesc;
    long m_duration = 3000;
    long m_fadeIn = 50;
    long m_fadeOut = 50;
    SoundGenerator*  m_g; // = SoundGenerator::factory(qPrintable(m_voiceDesc));
    SpeedHook* s1 ;   //= new SpeedHook();
    FreqOneHook* f1 ; //= new FreqOneHook();
    EngineSpeedHook* s2;
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
