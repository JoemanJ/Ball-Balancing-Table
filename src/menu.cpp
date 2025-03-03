#include "menu.h"

#include "Arduino.h"
#include "encoder.h"
#include "nop.h"

struct menuControls{
    void (*onLeft)(void);
    void (*onRight)(void);
    void (*onPress)(void);
};

struct menu{
    void (*displayFunc)(void);
    MenuControls controls;
};

void changeMenu(Menu menu)
{
    changeLeftCalback(menu.controls.onLeft);
    changeRightCalback(menu.controls.onRight);
    changePressCalback(menu.controls.onPress);
}

static void testOnLeft()
{
    Serial.println("LEFT!");
}

static void testOnRight()
{
    Serial.println("RIGHT!");
}

static void testOnPress()
{
    Serial.println("PRESSED!");
}

MenuControls testControls =
{
    .onLeft = testOnLeft,
    .onRight = testOnRight,
    .onPress = testOnPress
};

void setupTestMenu()
{
    MenuControls testControls =
    {
        .onLeft = testOnLeft,
        .onRight = testOnRight,
        .onPress = testOnPress
    };

    Menu test_menu = {.displayFunc = doNothing, .controls = testControls};
    changeMenu(test_menu);
    setupEncoder();
}