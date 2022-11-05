#pragma once

#include "../C/Components.hpp"
#include "../../Game.hpp"

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include <string>

class UILabel : public Component
{
    public:
        UILabel(int x, int y, std::string text, std::string font, SDL_Color &col) : text(text), font(font), color(col)
        {
            pos.x = x;
            pos.y = y;

            this->CreateTexture();
        }

        ~UILabel()
        {}

        void SetFromScore(ScoreComponent &sc)
        {
            Set(sc.AsString());
        }

        void SetFromHealth(HealthComponent &hc)
        {
            Set(hc.AsString());
        }

        void Set(std::string text)
        {
            this->text = text;
            this->CreateTexture();
        }

        void AssociateScore(ScoreComponent *sc)
        {
            scoreComp = sc;
        }

        void AssociateHealth(HealthComponent *hc)
        {
            healthComp = hc;
        }

        void CreateTexture()
        {
            SDL_Surface* surf = TTF_RenderText_Blended(Game::assets->GetFont(font), text.c_str(), color);
            texture = SDL_CreateTextureFromSurface(Game::renderer, surf);
            SDL_FreeSurface(surf);

            SDL_QueryTexture(texture, nullptr, nullptr, &pos.w, &pos.h);
        }

        void draw() override
        {
            SDL_RenderCopy(Game::renderer, texture, nullptr, &pos);
        }

        void update() override
        {
            if (scoreComp)
            {
                this->Set(scoreComp->AsString());
            }

            if (healthComp)
            {
                this->Set(healthComp->AsString());
            }
        }

    private:
        SDL_Rect pos;
        SDL_Color color;
        SDL_Texture* texture;
        
        std::string text;
        std::string font;

        ScoreComponent* scoreComp = nullptr;
        HealthComponent* healthComp = nullptr;
};