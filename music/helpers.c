// Helper functions for music
#include <cs50.h>
#include <string.h>
#include <math.h>
#include "helpers.h"

// Standard length of notes
#define STDLEN 8

// Position of note "A" in array NOTEX
#define APOS 9

// Base frequency for note "A4"
#define BASEFREQ 440

// Default octave
#define OCTAVE 4

// Notes in an octave
const string NOTEX[] = {"C", "C#", "D", "D#", "E", "F",
                        "F#", "G", "G#", "A", "A#", "B"};

// Convert a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    int num = fraction[0] - '0';
    int denom = fraction[2] - '0';
    return num * STDLEN / denom;
}

// Calculate frequency (in Hz) of a note
int frequency(string note)
{
    char letter = note[0];

    int mod = 0, oct = 0;

    // Check for modifiers "#" and "b" and save octave of note
    if (note[1] == 35)
    {
        mod = 1;
        oct = note[2] - '0';
    }
    else if (note[1] == 98)
    {
        mod = -1;
        oct = note[2] - '0';
    }
    else
        oct = note[1] - '0';

    // Setting up index relative to A
    int index = 0;

    for (int i = 0; (NOTEX[i][0]) != '\0'; i++)
    {
        if (letter == NOTEX[i][0])
        {
            index = i - APOS;
            break;
        }
    }

    // Final conversion into frequency
    float exponent = (oct - OCTAVE) + (mod + index) / 12.0;
    return round(BASEFREQ * pow(2, exponent));
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    if (s[0] == '\0')
        return true;
    else
        return false;
}
