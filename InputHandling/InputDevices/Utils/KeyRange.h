#pragma once

#include <algorithm>
#include <SDL.h>

struct KeyRange
{
    KeyRange(SDL_Scancode key, float polarity) :
        Key(key),
        Polarity(polarity)
    {}

    bool operator==(const KeyRange& other) const
    {
        return (this == &other);
    }

    SDL_Scancode Key;
    float Polarity;
};

namespace std
{
    template<>
    struct std::hash<KeyRange>
    {
        std::size_t operator()(const KeyRange& keyRange) const
        {
            return std::hash<int>()(keyRange.Key);
        }
    };
}