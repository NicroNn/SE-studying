#include <Windows.h>
#include "lib/UI.h"
#include "lib/config.h"

int main(){
    Config config = loadConfig("../config.ini");

    updateUI(config);
    while (true){
        if (GetKeyState(VK_ESCAPE) & 0x8000){
            return 0;
        }
        if (GetKeyState('N') & 0x8000){
            //next
            config.current_city = (config.current_city + 1) % config.cities.size();
            updateUI(config);
        }
        if (GetKeyState('P') & 0x8000){
            //prev
            config.current_city = config.current_city == 0 ? config.current_city + config.cities.size() - 1 :
                config.current_city - 1;
            updateUI(config);
        }
        if (GetKeyState('I') & 0x8000){  //+
            //increase
            config.days++;
            updateUI(config);
        }
        if (GetKeyState('D') & 0x8000){  //-
            //decrease
            config.days = config.days == 0 ? 0 : config.days - 1;
            updateUI(config);
        }
    }
}