#include "menu.h"

#include "Arduino.h"
#include "encoder.h"
#include "display.h"
#include "PID.h"

typedef struct menuControls{
    void (*onLeft)(void);
    void (*onRight)(void);
    void (*onPress)(void);
} MenuControls;

struct menu{
    void (*displayFunc)(void);
    MenuControls controls;
};

void changeMenu(Menu menu)
{
    changeLeftCalback(menu.controls.onLeft);
    changeRightCalback(menu.controls.onRight);
    changePressCalback(menu.controls.onPress);
    changeScreen(menu.displayFunc);
}


#define P_COLUMN 0
#define I_COLUMN 6
#define D_COLUMN 12

uint8_t cursorColumn = P_COLUMN;

static void mainMenuOnLeft();
static void mainMenuOnRight();
static void mainMenuOnPress();
static void mainMenuDisplay();
Menu mainMenu = {
    .displayFunc = mainMenuDisplay,
    .controls = {
        .onLeft = mainMenuOnLeft,
        .onRight = mainMenuOnRight,
        .onPress = mainMenuOnPress,
    }
};

static void proMenuOnLeft();
static void proMenuOnRight();
static void proMenuOnPress();
static void proMenuDisplay();
Menu proMenu = {
    .displayFunc = proMenuDisplay,
    .controls = {
        .onLeft = proMenuOnLeft,
        .onRight = proMenuOnRight,
        .onPress = proMenuOnPress,
    }
};

static void intMenuOnLeft();
static void intMenuOnRight();
static void intMenuOnPress();
static void intMenuDisplay();
Menu intMenu = {
    .displayFunc = intMenuDisplay,
    .controls = {
        .onLeft = intMenuOnLeft,
        .onRight = intMenuOnRight,
        .onPress = intMenuOnPress,
    }
};

static void derMenuOnLeft();
static void derMenuOnRight();
static void derMenuOnPress();
static void derMenuDisplay();
Menu derMenu = {
    .displayFunc = derMenuDisplay,
    .controls = {
        .onLeft = derMenuOnLeft,
        .onRight = derMenuOnRight,
        .onPress = derMenuOnPress,
    }
};

void mainMenuDisplay()
{
    displaySetCursor(0, 0);
    displayWrite("PRO:  INT:  DER:");

    displaySetCursor(0, 1);
    displayWrite(getPCoef());
    displaySetCursor(6, 1);
    displayWrite(getICoef());
    displaySetCursor(12, 1);
    displayWrite(getDCoef());

    displaySetCursor(cursorColumn, 0);
    displayCursor();
    displayNoBlink();
}

void mainMenuOnLeft()
{
    switch(cursorColumn)
    {
        case P_COLUMN:
            cursorColumn = D_COLUMN;
            break;

        case I_COLUMN:
            cursorColumn = P_COLUMN;
            break;

        case D_COLUMN:
            cursorColumn = I_COLUMN;
            break;

        default:
            break;
    }

    refreshDisplay();
}

void mainMenuOnRight()
{
    switch(cursorColumn)
    {
        case P_COLUMN:
            cursorColumn = I_COLUMN;
            break;

        case I_COLUMN:
            cursorColumn = D_COLUMN;
            break;

        case D_COLUMN:
            cursorColumn = P_COLUMN;
            break;

        default:
            break;
    }

    refreshDisplay();
}

void mainMenuOnPress()
{
    switch(cursorColumn)
    {
        case P_COLUMN:
            changeMenu(proMenu);
            break;

        case I_COLUMN:
            changeMenu(intMenu);
            break;

        case D_COLUMN:
            changeMenu(derMenu);
            break;

        default:
            break;
    }

    refreshDisplay();
}



void proMenuDisplay()
{
    displaySetCursor(0, 0);
    displayWrite("PRO:  INT:  DER:");

    displaySetCursor(0, 1);
    displayWrite(getPCoef());
    displayWrite("   ");
    displaySetCursor(6, 1);
    displayWrite(getICoef());
    displaySetCursor(12, 1);
    displayWrite(getDCoef());

    displaySetCursor(P_COLUMN, 1);
    displayCursor();
    displayNoBlink();
}

void proMenuOnLeft()
{
    decPCoef();
    refreshDisplay();
}

void proMenuOnRight()
{
    incPCoef();
    refreshDisplay();
}

void proMenuOnPress()
{
    changeMenu(mainMenu);
    refreshDisplay();
}



void intMenuDisplay()
{
    displaySetCursor(0, 0);
    displayWrite("PRO:  INT:  DER:");

    displaySetCursor(0, 1);
    displayWrite(getPCoef());
    displaySetCursor(6, 1);
    displayWrite(getICoef());
    displayWrite("   ");
    displaySetCursor(12, 1);
    displayWrite(getDCoef());

    displaySetCursor(I_COLUMN, 1);
    displayCursor();
    displayNoBlink();
}

void intMenuOnLeft()
{
    decICoef();
    refreshDisplay();
}

void intMenuOnRight()
{
    incICoef();
    refreshDisplay();
}

void intMenuOnPress()
{
    changeMenu(mainMenu);
    refreshDisplay();
}



void derMenuDisplay()
{
    displaySetCursor(0, 0);
    displayWrite("PRO:  INT:  DER:");

    displaySetCursor(0, 1);
    displayWrite(getPCoef());
    displaySetCursor(6, 1);
    displayWrite(getICoef());
    displaySetCursor(12, 1);
    displayWrite(getDCoef());
    displayWrite("   ");

    displaySetCursor(D_COLUMN, 1);
    displayCursor();
    displayNoBlink();
}

void derMenuOnLeft()
{
    decDCoef();
    refreshDisplay();
}

void derMenuOnRight()
{
    incDCoef();
    refreshDisplay();
}

void derMenuOnPress()
{
    changeMenu(mainMenu);
    refreshDisplay();
}

void setupMainMenu()
{
    setupLCD();
    setupEncoder();
    
    changeMenu(mainMenu);
}
/////////////////////////////////DEBUG//////////////////////////////////////////

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

    Menu test_menu = {.displayFunc = helloWorldFunc, .controls = testControls};
    
    setupLCD();
    setupEncoder();
    
    changeMenu(test_menu);
}