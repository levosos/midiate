#include "midi.h"

#include "../debug/debug.h"

#ifdef ARDUINO
#include <Arduino.h>
#endif // ARDUINO

namespace midier
{
namespace midi
{

#ifdef ARDUINO

namespace
{

void send(byte command, byte data1, byte data2)
{
    constexpr auto channel = 0;

#ifndef DEBUG
    Serial.write((command & 0xF0) | (channel & 0x0F));
    Serial.write(data1 & 0x7F);
    Serial.write(data2 & 0x7F);
#else
    // TRACE_4(F("Sending MIDI command NOTE-"), command == 0x90 ? F("ON") : F("OFF"), " #", (int)data1);
#endif
}

} //

#endif // ARDUINO

Number number(Note note, Octave octave)
{
    return 24 + (12 * (octave - 1)) + (char)note;
}

#ifdef ARDUINO

void on(Number number, Velocity velocity)
{
    send(0x90, number, (char)velocity);
}

void off(Number number)
{
    send(0x80, number, 0);
}

void play(Note note, unsigned duration)
{
    play(note, 3, duration); // playing notes in octave 3 by default
}

void play(Note note, Octave octave, unsigned duration)
{
    const auto no = number(note, octave);

    on(no);
    delay(duration);
    off(no);
}

#endif // ARDUINO

} // midi
} // midier
