#include "synthesizer.h"
#include "../libsynth/include/libsynth.hpp"
#include <QtConcurrent/QtConcurrent>

Synthesizer::Synthesizer(QObject *parent) : QObject(parent)
{
}

Synthesizer::~Synthesizer(){
    // default voice
    m_voiceDesc = "sinus 440";
    // default duration
    m_duration = 1000;
    m_fadeIn = 20;
    m_fadeOut = 20;
    //n_speed->speed = 1 ;
    //freq_one->freq = 50;
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

void Synthesizer::playNonBlocking(){
    w = new Player;
    w->setDuration(m_duration);
    w->setGenerator(m_voiceDesc);
    t = new QThread;
    w->moveToThread(t);
    connect(this, SIGNAL(start()), w, SLOT(play()));
    connect(w, SIGNAL(result(bool)), this, SIGNAL(result(bool)));
    this->start();
    t->start();
    //w->play();
}

void Synthesizer::play()
{
    emit playing();
    SoundGenerator::setVolume(0);   // Avoid sound clicks at start
    SoundGenerator::fade_in(10);
    SoundGenerator::setVolume(0.6);   // Avoid sound clicks at start

    QString input = this->getVoiceDesc();

    // remove old instance first
    SoundGenerator::remove(m_g);
    m_g = SoundGenerator::factory(qPrintable(input));
    SoundGenerator::play(m_g);

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

}

void Synthesizer::setDuration(long duration)
{
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
   n_speed->speed = duration;
   //w->setSpeedOne( duration);
}
void Synthesizer::setFreqOne(long frequency) {
    freq_one->freq = frequency;
    //w->setFreqOne( frequency);
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
