#pragma once

#include "../interval/interval.h"

namespace midier
{

enum class Note : char
{
    // the values are the corresponding number of semitones from 'C' in
    // order to easily convert a note to its respective MIDI note number

    C = 0,
    D = 2,
    E = 4,
    F = 5,
    G = 7,
    A = 9,
    B = 11,

    // we might represent other values, in run-time, as notes as well, e.g. 'C = 12', 'G# = 20'
};

enum class Accidental : char
{
    // the values are the number of semitones (and direction)
    // the note should be modified by this accidental

    Flat    = -1,
    Natural =  0,
    Sharp   = +1,
};

#define OPERATOR_ADD(type)                                                          \
    inline Note operator+(Note note, type rhs)                                      \
    {                                                                               \
        return static_cast<Note>(static_cast<char>(note) + static_cast<char>(rhs)); \
    }

OPERATOR_ADD(Interval)
OPERATOR_ADD(Accidental)

#undef OPERATOR_ADD

} // midier
