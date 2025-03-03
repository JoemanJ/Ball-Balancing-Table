#ifndef MENU_H
#define MENU_H

struct menu;
typedef struct menu Menu;
struct menuControls;
typedef struct menuControls MenuControls;

void changeMenu(Menu menu);

void setupTestMenu();

#endif