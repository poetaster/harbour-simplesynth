#ifndef SYNTHESIZER_H
#define SYNTHESIZER_H

#include <QDebug>
#include <QtCore/QObject>
#include "../libsynth/include/libsynth.hpp"


class SpeedHook : public SoundGeneratorVarHook<float>
{
public:
    SpeedHook() : SoundGeneratorVarHook(&speed, 0, 200, "n_speed"){};
   atomic<float> speed;  // from 0 to 200

};

class FreqOneHook : public SoundGeneratorVarHook<long>
{
public:
   FreqOneHook() : SoundGeneratorVarHook(&freq, 1, 1000, "freq_one"){};
   atomic<long> freq;  // from 1 to 1000

};
/* Player class for running the audio play function in a separate thread
 */

class Player : public QObject {
    Q_OBJECT
  public slots:
    void setGenerator(QString generator) {
        m_voiceDesc = generator;
        qDebug() << "generator " << m_voiceDesc ; //<< " for " << m_duration;
    }
    void setDuration(long time) {
        m_duration  = time;
        qDebug() << "duration " << m_duration ; //<< " for " << m_duration;
    }
    void setSpeedOne(long duration) {
        n_speed->speed = duration;
    }
    void setFreqOne(long frequency) {
        freq_one->freq = frequency;
    }
    void play() {
        SoundGenerator::setVolume(0);   // Avoid sound clicks at start
        SoundGenerator::fade_in(10);
        SoundGenerator::setVolume(0.6);   // Avoid sound clicks at start
        // remove old instance first
        SoundGenerator::remove(this->mg);
        this->mg = SoundGenerator::factory(qPrintable(m_voiceDesc));
        SoundGenerator::play(this->mg);
        const int fade_time=10; //m_fadeIn;
        long duration = m_duration;
        if (duration > fade_time) {
                SDL_Delay(duration-fade_time); // Play for ms
                SoundGenerator::fade_out(fade_time);
                SDL_Delay(fade_time); // Play for 100 ms (while fade out)
        } else {
                SoundGenerator::fade_out(fade_time);
                SDL_Delay(fade_time); // Play for ms (while fading out)
        }
        SDL_Delay(10); // Wait till the end of buffer is played (avoid clicks) TODO this is buffer size dependant
     result(true);
    }
  signals:
    void result(bool r);
  private:
    SoundGenerator*  mg;
    QString m_voiceDesc;
    long m_duration;
    SpeedHook* n_speed = new SpeedHook();
    FreqOneHook* freq_one = new FreqOneHook();
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
    Q_INVOKABLE void setFreqOne(long freq);
    Q_INVOKABLE void play();
    Q_INVOKABLE void playNonBlocking();

signals:
    void voiceDescChanged();
    void playing();
    void start();
    void result(bool r);

private:
    QString m_voiceDesc;
    long m_duration;
    long m_fadeIn;
    long m_fadeOut;
    SoundGenerator*  m_g; // = SoundGenerator::factory(qPrintable(m_voiceDesc));
    SpeedHook* n_speed = new SpeedHook();
    FreqOneHook* freq_one = new FreqOneHook();
    uint32_t ech = 48000;
    const int BUF_LENGTH = 1024;
    QThread * t;
    Player * w;
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
