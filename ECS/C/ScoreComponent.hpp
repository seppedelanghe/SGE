#pragma once

#include <string>
#include <sstream>
#include "Components.hpp"

class ScoreComponent : public Component
{
    private:
        int score;
        std::string name;

    public:
        ScoreComponent()
        {
            score = 0;
            name = "Score";
        }
        
        ScoreComponent(std::string n)
        {
            score = 0;
            name = n;
        }

        ScoreComponent(std::string n, int scr)
        {
            score = scr;
            name = n;
        }

        void Increase(int value = 1)
        {
            score += value;
        }

        void Decrease(int value = 1)
        {
            score -= value;
        }

        int Value()
        {
            return score;
        }

        bool Zero()
        {
            return score == 0;
        }

        void Reset()
        {
            score = 0;
        }

        std::string AsString()
        {
            std::stringstream ss;
            ss << name << ": " << score;
            return ss.str();
        }

        void init() override
        {
            score = 0;
        }
};
