//
// Created by Acer on 2024-05-24.
//

#include "Menu.h"

void Menu::show_menu(SDL_Rect dest)
{
// Load the black and white buttons sprite sheet
auto menu_BnW_ss = texture_manager::LoadTexture("assets/Menu/Menu Buttons sprite (BnW).png");

// Load the colored buttons sprite sheet
auto menu_color_ss = texture_manager::LoadTexture("assets/Menu/Menu Buttons sprite (Colored).png");

// Calculate the x-coordinate of the center of the screen
int centerX = dest.x + (dest.w / 2);

// Calculate the y-coordinate of the center of the screen
int centerY = dest.y + (dest.h / 2);

// Define rectangles for the start and quit buttons
SDL_Rect start_button = { centerX - 300, centerY - 112, 600, 225 }; // Centered start button
SDL_Rect quit_button = { centerX - 300, centerY + 138, 600, 225 }; // Centered quit button (250px below the start button)

// Get the current mouse state
int mouseX, mouseY;
SDL_GetMouseState(&mouseX, &mouseY);

// Check if the mouse is hovered over the start button
bool isMouseOverStartButton = isMouseOverButton(start_button, mouseX, mouseY);

// Draw the start button
drawButton(start_button, isMouseOverStartButton, menu_BnW_ss, menu_color_ss, dest);

// Check if the mouse is hovered over the quit button
bool isMouseOverQuitButton = isMouseOverButton(quit_button, mouseX, mouseY);

// Draw the quit button
drawButton(quit_button, isMouseOverQuitButton, menu_BnW_ss, menu_color_ss, dest);

}
void Menu::drawButton(SDL_Rect button, bool isMouseOver, SDL_Texture* bwTexture, SDL_Texture* colorTexture, SDL_Rect dest) {
    if (isMouseOver) {
        texture_manager::Draw(colorTexture, button, dest,SDL_FLIP_NONE);
    } else {
        texture_manager::Draw(bwTexture, button, dest,SDL_FLIP_NONE);
    }
}
bool Menu::isMouseOverButton(SDL_Rect button, int mouseX, int mouseY) {
    return (mouseX >= button.x && mouseX <= button.x + button.w &&
            mouseY >= button.y && mouseY <= button.y + button.h);
}

