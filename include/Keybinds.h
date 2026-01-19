#ifndef KEYBINDS
#define KEYBINDS

#include <functional>
#include <string>
#include <map>
#include <iostream>
#include "raylib.h"

// const char* GetKeyName(int key)
// {
//     switch (key)
//     {
//         // Lettres
//         case KEY_A: return "A";
//         case KEY_B: return "B";
//         case KEY_C: return "C";
//         case KEY_D: return "D";
//         case KEY_E: return "E";
//         case KEY_F: return "F";
//         case KEY_G: return "G";
//         case KEY_H: return "H";
//         case KEY_I: return "I";
//         case KEY_J: return "J";
//         case KEY_K: return "K";
//         case KEY_L: return "L";
//         case KEY_M: return "M";
//         case KEY_N: return "N";
//         case KEY_O: return "O";
//         case KEY_P: return "P";
//         case KEY_Q: return "Q";
//         case KEY_R: return "R";
//         case KEY_S: return "S";
//         case KEY_T: return "T";
//         case KEY_U: return "U";
//         case KEY_V: return "V";
//         case KEY_W: return "W";
//         case KEY_X: return "X";
//         case KEY_Y: return "Y";
//         case KEY_Z: return "Z";

//         // Chiffres
//         case KEY_ZERO:  return "0";
//         case KEY_ONE:   return "1";
//         case KEY_TWO:   return "2";
//         case KEY_THREE: return "3";
//         case KEY_FOUR:  return "4";
//         case KEY_FIVE:  return "5";
//         case KEY_SIX:   return "6";
//         case KEY_SEVEN: return "7";
//         case KEY_EIGHT: return "8";
//         case KEY_NINE:  return "9";

//         // Touches spéciales
//         case KEY_SPACE: return "SPACE";
//         case KEY_ESCAPE: return "ESC";
//         case KEY_ENTER: return "ENTER";
//         case KEY_TAB: return "TAB";
//         case KEY_BACKSPACE: return "BACKSPACE";
//         case KEY_LEFT: return "LEFT";
//         case KEY_RIGHT: return "RIGHT";
//         case KEY_UP: return "UP";
//         case KEY_DOWN: return "DOWN";
//         case KEY_LEFT_SHIFT: return "LSHIFT";
//         case KEY_RIGHT_SHIFT: return "RSHIFT";
//         case KEY_LEFT_CONTROL: return "LCTRL";
//         case KEY_RIGHT_CONTROL: return "RCTRL";
//         case KEY_LEFT_ALT: return "LALT";
//         case KEY_RIGHT_ALT: return "RALT";

//         // Fonction
//         case KEY_F1: return "F1";
//         case KEY_F2: return "F2";
//         case KEY_F3: return "F3";
//         case KEY_F4: return "F4";
//         case KEY_F5: return "F5";
//         case KEY_F6: return "F6";
//         case KEY_F7: return "F7";
//         case KEY_F8: return "F8";
//         case KEY_F9: return "F9";
//         case KEY_F10: return "F10";
//         case KEY_F11: return "F11";
//         case KEY_F12: return "F12";

//         default:
//             return "UNKNOWN";
//     }
// }

class KeyBinding {
  private:
    int defaultKeys;
    int currentKeys;
    std::function<void()> action;

  public:
    KeyBinding(int defkeys, std::function<void()>func):defaultKeys(defkeys), currentKeys(defkeys), action(func){};
    inline void setKey(int newKey){ currentKeys = newKey;};
    inline int getKey() const { return currentKeys;};
    inline int getDefaultKey() const { return defaultKeys;};
    inline const std::function<void()>& getAction() const { return action;};
    void execute() const {
      if (action) action();
    }
};

class InputManager {
  private:
    std::map<std::string, KeyBinding> bindings;
    std::string waitingForRebind;
    bool isRebinding = false;

  public:
    void add(const std::string& name, int key, std::function<void()> action) {
        bindings.emplace(name, KeyBinding(key, action));
    }
    void startRebind(const std::string& name) {
        waitingForRebind = name;
        isRebinding = true;
    }
    bool rebinding() const { return isRebinding; }
    void handleKey(int key) {
        if (key == 0) return;
        if (isRebinding) {
            bindings.at(waitingForRebind).setKey(key);
            isRebinding = false;
            std::cout << "Rebound " << waitingForRebind << " to " << key << std::endl;
            return;
        }
        for (const auto& [_, binding] : bindings) {
            if (binding.getKey() == key)
                binding.execute();
        }
    }

    const std::map<std::string, KeyBinding>& getBindings() const {
        return bindings;
    }
    void drawKeybindMenu(int startX = 50, int startY = 50) {
        int y = startY + 50;

        DrawText("KEYBINDS", startX, startY, 20, WHITE);

        for (const auto& [name, binding] : bindings) {
            Rectangle rect = {
                (float)startX,
                (float)y,
                300,
                30
            };

            DrawRectangleRec(rect, DARKGRAY);

            DrawText(
                TextFormat("%s : %s", name.c_str(), GetKeyName(binding.getKey())),
                startX + 10,
                y + 5,
                20,
                WHITE
            );

            if (CheckCollisionPointRec(GetMousePosition(), rect) &&
                IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                startRebind(name);
            }

            y += 40;
        }

        if (isRebinding) {
            DrawText("Press a key...", startX, y + 10, 20, RED);
        }
    }
};



#endif 
