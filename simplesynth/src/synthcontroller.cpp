#include "../libsynth/include/libsynth.hpp"
#include "synthesizer.h"
#include <QThread>

Synthcontroller::Synthcontroller(QObject *parent) : QObject(parent)
{
}

Synthcontroller::~Synthcontroller(){
    // default voice
    m_voiceDesc = "sinus 440";
    // default duration
    m_duration = 2000;
    m_fadeIn = 20;
    m_fadeOut = 20;
}

QString Synthcontroller::getVoiceDesc()
{
    return m_voiceDesc;
}

void Synthcontroller::setVoiceDesc(const QString &voiceDesc)
{
    if (voiceDesc == m_voiceDesc)
        return;
    m_voiceDesc = voiceDesc;
    emit voiceDescChanged();
}

void Synthcontroller::playNonBlocking(){

    w = new Player;

    // setup before playing new iteration
    w->setDuration(m_duration);
    w->setGenerator(m_voiceDesc);
    w->remove();
    t = new QThread;
    w->moveToThread(t);
    connect(this, SIGNAL(start()), w, SLOT(play()));
    connect(w, SIGNAL(result(bool)), this, SIGNAL(result(bool)));
    this->start();
    t->start();

    //w->play();
}

void Synthcontroller::play()
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

void Synthcontroller::setDuration(long duration)
{
  m_duration = duration;
}

void Synthcontroller::setFadeIn(long duration)
{
  m_fadeIn = duration;
}

void Synthcontroller::setFadeOut(long duration)
{
  m_fadeOut = duration;
}

void Synthcontroller::setSpeedOne(long duration) {
   //n_speed->speed = duration;
   w->setSpeedOne( duration);
}
void Synthcontroller::setFreqOne(long frequency) {
    //freq_one->freq = frequency;
    w->setFreqOne( frequency);
}
