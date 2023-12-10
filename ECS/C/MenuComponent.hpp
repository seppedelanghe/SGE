
#include "ECS.hpp"
#include "Game.hpp"
#include "SDL_pixels.h"
#include "SDL_render.h"
#include "UI/UILabel.h"
#include "Vector2.hpp"
#include <cstdio>
#include <string>
#include <vector>


class MenuComponent : public Component {
    private:
        bool visible = false;
        SDL_Rect dimensions;
        SDL_Color color;
        SDL_Color textColor { 0, 0, 0, 255 };
        std::string textFont = "arial";

        std::vector<UILabel> labels;
        
    public:
        MenuComponent(SDL_Rect dim) {
            dimensions = dim;
            color = SDL_Color{255, 255, 255, 255};
        };

        ~MenuComponent() {};

        void Toggle() {
            visible = !visible;
        }

        void AddLabel(std::string text, int x, int y) {
            UILabel label {x, y, text, textFont, textColor};
            labels.push_back(label);
        };

        void AddButton(std::string text, int x, int y) {

        };

        void draw() override {
            if (!visible) {
                return;
            }

            SDL_SetRenderDrawColor(Game::renderer, color.r, color.g, color.b, color.a);
            SDL_RenderFillRect(Game::renderer, &dimensions);

            for(UILabel label : labels) {
                label.draw();
            }
        }

        void update() override {}
        void init() override {}
};
