#ifndef MENU_MODE_H_INCLUDED
#define MENU_MODE_H_INCLUDED

void menu_Init();
void menu_Start();
void menu_DeInit();
void menu_Render();
BOOL menu_TouchEvent(BOOL down);
void menu_Heartbeat();
MODE menu_IsDone();

#endif /* MENU_MODE_H_INCLUDED */
