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

enum CURSORPOSITION {P, I, D, P_I, I_D, D_P, P_I_D};
CURSORPOSITION cursorPosition = P;

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

static void proIntMenuOnLeft();
static void proIntMenuOnRight();
static void proIntMenuOnPress();
static void proIntMenuDisplay();
Menu proIntMenu = {
    .displayFunc = proIntMenuDisplay,
    .controls = {
        .onLeft = proIntMenuOnLeft,
        .onRight = proIntMenuOnRight,
        .onPress = proIntMenuOnPress,
    }
};

static void intDerMenuOnLeft();
static void intDerMenuOnRight();
static void intDerMenuOnPress();
static void intDerMenuDisplay();
Menu intDerMenu = {
    .displayFunc = intDerMenuDisplay,
    .controls = {
        .onLeft = intDerMenuOnLeft,
        .onRight = intDerMenuOnRight,
        .onPress = intDerMenuOnPress,
    }
};

static void derProMenuOnLeft();
static void derProMenuOnRight();
static void derProMenuOnPress();
static void derProMenuDisplay();
Menu derProMenu = {
    .displayFunc = derProMenuDisplay,
    .controls = {
        .onLeft = derProMenuOnLeft,
        .onRight = derProMenuOnRight,
        .onPress = derProMenuOnPress,
    }
};

static void proIntDerMenuOnLeft();
static void proIntDerMenuOnRight();
static void proIntDerMenuOnPress();
static void proIntDerMenuDisplay();
Menu proIntDerMenu = {
    .displayFunc = proIntDerMenuDisplay,
    .controls = {
        .onLeft = proIntDerMenuOnLeft,
        .onRight = proIntDerMenuOnRight,
        .onPress = proIntDerMenuOnPress,
    }
};

void mainMenuDisplay()
{
    displaySetCursor(0, 1);
    displayWrite(getPCoef());
    displaySetCursor(6, 1);
    displayWrite(getICoef());
    displaySetCursor(12, 1);
    displayWrite(getDCoef());
    
    displaySetCursor(0, 0);
    switch (cursorPosition)
    {
    case P_I:
        displayWrite("PRO:<>INT:  DER:");
        displayNoCursor();
        break;
    
    case I_D:
        displayWrite("PRO:  INT:<>DER:");
        displayNoCursor();
        break;

    case D_P:
        displayWrite("PRO:< INT: >DER:");
        displayNoCursor();
        break;

    case P_I_D:
        displayWrite("PRO:<>INT:<>DER:");
        displayNoCursor();
    
    case P:
        displayWrite("PRO:  INT:  DER:");
        displaySetCursor(P_COLUMN, 0);
        displayCursor();
        break;

    case I:
        displayWrite("PRO:  INT:  DER:");
        displaySetCursor(I_COLUMN, 0);
        displayCursor();
        break;

    case D:
        displayWrite("PRO:  INT:  DER:");
        displaySetCursor(D_COLUMN, 0);
        displayCursor();
        break;

    default:
        break;
    }

    displayNoBlink();
}

void mainMenuOnLeft()
{
    switch(cursorPosition)
    {
        case P:
            cursorPosition = P_I_D;
            break;

        case I:
            cursorPosition = P;
            break;

        case D:
            cursorPosition = I;
            break;

        case P_I:
            cursorPosition = D;
            break;

        case I_D:
            cursorPosition = P_I;
            break;

        case P_I_D:
            cursorPosition = I_D;
            break;

        default:
            break;
    }

    refreshDisplay();
}

void mainMenuOnRight()
{
    switch(cursorPosition)
    {
        case P:
            cursorPosition = I;
            break;

        case I:
            cursorPosition = D;
            break;

        case D:
            cursorPosition = P_I;
            break;

        case P_I:
            cursorPosition = I_D;
            break;

        case I_D:
            cursorPosition = P_I_D;
            break;

        case P_I_D:
            cursorPosition = P;
            break;

        default:
            break;
    }

    refreshDisplay();
}

void mainMenuOnPress()
{
    switch(cursorPosition)
    {
        case P:
            changeMenu(proMenu);
            break;

        case I:
            changeMenu(intMenu);
            break;

        case D:
            changeMenu(derMenu);
            break;
        
        case P_I:
            changeMenu(proIntMenu);
            break;

        case I_D:
            changeMenu(intDerMenu);
            break;

        case D_P:
            changeMenu(derProMenu);
            break;

        case P_I_D:
            changeMenu(proIntDerMenu);
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

    displaySetCursor(P_COLUMN, 1);
    displayWrite(getPCoef());
    displayWrite("   ");
    displaySetCursor(I_COLUMN, 1);
    displayWrite(getICoef());
    displaySetCursor(D_COLUMN, 1);
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

    displaySetCursor(P_COLUMN, 1);
    displayWrite(getPCoef());
    displaySetCursor(I_COLUMN, 1);
    displayWrite(getICoef());
    displayWrite("   ");
    displaySetCursor(D_COLUMN, 1);
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

    displaySetCursor(P_COLUMN, 1);
    displayWrite(getPCoef());
    displaySetCursor(I_COLUMN, 1);
    displayWrite(getICoef());
    displaySetCursor(D_COLUMN, 1);
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



void proIntMenuDisplay()
{
    displaySetCursor(0, 0);
    displayWrite("PRO:  INT:  DER:");

    displaySetCursor(P_COLUMN, 1);
    displayWrite(getPCoef());
    displayWrite("   ");
    displaySetCursor(I_COLUMN-2, 1);
    displayWrite("<>");
    displayWrite(getICoef());
    displayWrite("   ");
    displaySetCursor(D_COLUMN, 1);
    displayWrite(getDCoef());

    displayNoCursor();
    displayNoBlink();
}

void proIntMenuOnLeft()
{
    decPCoef();
    decICoef();
    refreshDisplay();
}

void proIntMenuOnRight()
{
    incPCoef();
    incICoef();
    refreshDisplay();
}

void proIntMenuOnPress()
{
    changeMenu(mainMenu);
    refreshDisplay();
}



void intDerMenuDisplay()
{
    displaySetCursor(0, 0);
    displayWrite("PRO:  INT:  DER:");

    displaySetCursor(P_COLUMN, 1);
    displayWrite(getPCoef());
    displaySetCursor(I_COLUMN, 1);
    displayWrite(getICoef());
    displayWrite("   ");
    displaySetCursor(D_COLUMN-2, 1);
    displayWrite("<>");
    displayWrite(getDCoef());
    displayWrite("   ");

    displayNoCursor();
    displayNoBlink();
}

void intDerMenuOnLeft()
{
    decICoef();
    decDCoef();
    refreshDisplay();
}

void intDerMenuOnRight()
{
    incICoef();
    incDCoef();
    refreshDisplay();
}

void intDerMenuOnPress()
{
    changeMenu(mainMenu);
    refreshDisplay();
}



void derProMenuDisplay()
{
    displaySetCursor(0, 0);
    displayWrite("PRO:  INT:  DER:");

    displaySetCursor(P_COLUMN, 1);
    displayWrite(getPCoef());
    displayWrite("   ");
    displaySetCursor(I_COLUMN-2, 1);
    displayWrite("< ");
    displayWrite(getICoef());
    displaySetCursor(D_COLUMN-2, 1);
    displayWrite(" >");
    displayWrite(getDCoef());
    displayWrite("   ");

    displayNoCursor();
    displayNoBlink();
}

void derProMenuOnLeft()
{
    decDCoef();
    decPCoef();
    refreshDisplay();
}

void derProMenuOnRight()
{
    incDCoef();
    incPCoef();
    refreshDisplay();
}

void derProMenuOnPress()
{
    changeMenu(mainMenu);
    refreshDisplay();
}



void proIntDerMenuDisplay()
{
    displaySetCursor(0, 0);
    displayWrite("PRO:  INT:  DER:");

    displaySetCursor(P_COLUMN, 1);
    displayWrite(getPCoef());
    displayWrite("   ");
    displaySetCursor(I_COLUMN-2, 1);
    displayWrite("<>");
    displayWrite(getICoef());
    displayWrite("   ");
    displaySetCursor(D_COLUMN-2, 1);
    displayWrite("<>");
    displayWrite(getDCoef());
    displayWrite("   ");

    displayNoCursor();
    displayNoBlink();
}

void proIntDerMenuOnLeft()
{
    decDCoef();
    decICoef();
    decPCoef();
    refreshDisplay();
}

void proIntDerMenuOnRight()
{
    incDCoef();
    incICoef();
    incPCoef();
    refreshDisplay();
}

void proIntDerMenuOnPress()
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