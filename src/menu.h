#ifndef MENU_H
#define MENU_H

struct menu;
typedef struct menu Menu;

void changeMenu(Menu menu);

void setupMainMenu();
void setupTestMenu();

#endif