#include "../libsynth/include/libsynth.hpp"
#include "synthesizer.h"
#include "synthcontroller.h"
#include <QThread>

SynthController::SynthController(QObject *parent) : QObject(parent)
{
    // create a synth instance
    w = new Synthesizer;
    // create a thread to run it in
    t = new QThread;
    w->setDuration(m_duration);
    w->setVoiceDesc(m_voiceDesc);
    w->moveToThread(t);
    connect(this, SIGNAL(start()), w, SLOT(play()));
    connect(w, SIGNAL(done(bool)), this, SIGNAL(done(bool)));
    // default voice
    m_voiceDesc = "sinus 440";
    // default duration
    m_duration = 2000;
    m_fadeIn = 20;
    m_fadeOut = 20;
}

SynthController::~SynthController(){
  delete w;
  delete t;
}

QString SynthController::getVoiceDesc()
{
    return m_voiceDesc;
}

void SynthController::setVoiceDesc(const QString &voiceDesc)
{
    if (voiceDesc == m_voiceDesc)
        return;
    m_voiceDesc = voiceDesc;
    emit voiceDescChanged();
}

void SynthController::play(){

    // create a synth instance
    //w = new Synthesizer;
    // create a thread to run it in
    //t = new QThread;
    // setup before playing new iteration
    w->setDuration(m_duration);
    w->setVoiceDesc(m_voiceDesc);
    //w->moveToThread(t);
    t->start();
    this->start();
}
void SynthController::stop(){
    w->stop();
}

void SynthController::setDuration(long duration)
{
  m_duration = duration;
}

void SynthController::setFadeIn(long duration)
{
  m_fadeIn = duration;
}

void SynthController::setFadeOut(long duration)
{
  m_fadeOut = duration;
}

void SynthController::setSpeedOne(long duration) {
   //n_speed->speed = duration;
   w->setSpeedOne( duration);
}
void SynthController::setFreqOne(long frequency) {
    //freq_one->freq = frequency;
    w->setFreqOne( frequency);
}
