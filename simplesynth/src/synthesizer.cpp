#include "../libsynth/include/libsynth.hpp"
#include "synthesizer.h"
#include <QThread>

Synthesizer::Synthesizer(QObject *parent) : QObject(parent)
{
    // default voice
    m_voiceDesc = "sinus 440";
    // default duration
    m_duration = 1000;
    m_fadeIn = 20;
    m_fadeOut = 20;
    s1 = new SpeedHook();
    f1 = new FreqOneHook();
    s1->speed = 1 ;
    f1->freq = 50;
}

QString Synthesizer::getVoiceDesc()
{
    return m_voiceDesc;
}

void Synthesizer::setVoiceDesc(const QString &voiceDesc)
{
    if (voiceDesc == m_voiceDesc)
        return;
    m_voiceDesc = voiceDesc;
    emit voiceDescChanged();
}

void Synthesizer::play()
{
    //emit playing();
    SoundGenerator::setVolume(0);   // Avoid sound clicks at start
    SoundGenerator::fade_in(10);
    SoundGenerator::setVolume(0.6);   // Avoid sound clicks at start

    QString input = this->getVoiceDesc();

    // remove old instance first
    SoundGenerator::remove(m_g);
    m_g = SoundGenerator::factory(qPrintable(input));
    SoundGenerator::play(m_g);

    const int fade_time=50; //m_fadeIn;
    long duration = m_duration;
    qDebug() << "play dur " << duration ; //<< " for " << m_duration;
    if (duration > fade_time) {
            SDL_Delay(duration-fade_time); // Play for ms
            SoundGenerator::fade_out(fade_time);
            SDL_Delay(fade_time); // Play for 100 ms (while fade out)
    } else {
            SoundGenerator::fade_out(fade_time);
            SDL_Delay(fade_time); // Play for ms (while fading out)
    }
    SDL_Delay(50); // Wait till the end of buffer is played (avoid clicks) TODO this is buffer size dependant
    SoundGenerator::setVolume(0);
    // signal we're finished
    done(true);

}
void Synthesizer::stop()
{
    const int fade_time=50; //m_fadeIn;
    SoundGenerator::fade_out(fade_time);
    SDL_Delay(50); // Wait till the end of buffer is played (avoid clicks) TODO this is buffer size dependant
    SoundGenerator::setVolume(0);
    SoundGenerator::remove(m_g);
    done(true);
}


void Synthesizer::setDuration(long duration)
{
  qDebug() << "dur " << duration ; //<< " for " << m_duration;
  m_duration = duration;
}

void Synthesizer::setFadeIn(long duration)
{
  m_fadeIn = duration;
}

void Synthesizer::setFadeOut(long duration)
{
  m_fadeOut = duration;
}

void Synthesizer::setSpeedOne(long duration) {
   // qDebug() << "s1 " << duration ; //<< " for " << m_duration;
   s1->speed = duration;
}

void Synthesizer::setFreqOne(long frequency) {
    //qDebug() << "f1 " << frequency ; //<< " for " << m_duration;
    f1->freq = frequency;
}
/*
atomic<float> engine_speed;     // Float value that represents the engine speed
class EngineSpeedHook : public SoundGeneratorVarHook<float>
{
        public:
                EngineSpeedHook() : SoundGeneratorVarHook(&engine_speed, 0.0, 100.0, "engine_speed"){}
};
static EngineSpeedHook instance;        // Needed to register the 'engine_speed' hook so it can be used.

*/
