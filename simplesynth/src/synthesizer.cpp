#include "synthesizer.h"
#include "../libsynth/include/libsynth.hpp"

Synthesizer::Synthesizer(QObject *parent) :
    QObject(parent)
{
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
    makeAsound();
    emit voiceDescChanged();
}

void Synthesizer::makeAsound() {

    // initial instrument definition for testing
    //string input = "fm 100 150 am 0 100 square 100:20 square 39 adsr 1:0 1000:0 2000:100 5001:100 6000:-100 8000:0 loop level 1";

    QString input = getVoiceDesc();
    string blah = qPrintable(input);
    std::cout << blah << std::endl;
    long duration = 1000;
    uint32_t ech = 48000;
    const int BUF_LENGTH = 1024;

    //SoundGenerator::play(SoundGenerator::factory("fm 50 150 sinus 440 hook_speed"));

    SoundGenerator* g = SoundGenerator::factory(blah);

    SoundGenerator::play(g);

    SoundGenerator::setVolume(0);   // Avoid sound clicks at start
    SoundGenerator::fade_in(10);
    SoundGenerator::setVolume(0);   // Avoid sound clicks at start
    SoundGenerator::fade_in(10);

    const int fade_time=50;

    if (duration > fade_time) {
            SDL_Delay(duration-fade_time); // Play for ms
            SoundGenerator::fade_out(fade_time);
            SDL_Delay(fade_time); // Play for 100 ms (while fade out)
    } else {
            SoundGenerator::fade_out(fade_time);
            SDL_Delay(fade_time); // Play for ms (while fading out)
    }
    SDL_Delay(1000); // Wait till the end of buffer is played (avoid clicks) TODO this is buffer size dependant

}
