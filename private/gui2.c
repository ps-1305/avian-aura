#include "gui.h"

char* choices[] = {" Profile ", " Flights ", " Trains ", " Buses ", " Wayfarer "};
int n_choices = sizeof(choices) / sizeof(char *);

int handle_mouse_click(int y, int x) {
    // Check if click coordinates fall within button areas
    if (y == 12 && x >= 24 && x < 33) {
        // Handle LOG-IN click
        return 1;
    } else if (y == 12 && x >= 34 && x < 44) {
        // Handle SIGN-UP click
        return 2;
    } else if (y == 13 && x >= 24 && x < 44) {
        // Handle Forgot Password? click
        return 3;
    }
    return 0; // No button clicked
}

int main(void)
{
    WINDOW *win1;
    WINDOW *win2;
    WINDOW *win3;

    initscr();
    clear();
    cbreak();

    curs_set(0);

    win1 = newwin(25, 19, 0, 0);
    win2 = newwin(20, 50, 0, 20);
    win3 = newwin(20, 70, 0 , 0);

    keypad(win3, TRUE);
    keypad(win1, TRUE);
    keypad(win2, TRUE);

    // Enable mouse events
    mousemask(ALL_MOUSE_EVENTS, NULL);

    int h1 = 1;
    int h2 = 1;

    int ch1 = 0;
    int ch2 = 0;

    int c = 0;

    int logged_in = 0;

    while(1)
    {
        if (logged_in == 0)
        {

            start(win3);

            werase(win3);
            delwin(win3);

            logged_in = 1;

            continue;
        }

        print_menu_1(win1, h1);
        print_menu_2(win2, 0, 0);

        noecho();

        wattron(win1, A_BOLD | A_UNDERLINE);
        mvwprintw(win1, 1, 3, "Dashboard");
        wattroff(win1, A_BOLD | A_UNDERLINE);

        while(1)
        {	
            c = wgetch(win1);
            switch(c)
            {	case KEY_UP:
                    if(h1 == 1)
                        h1 = n_choices;
                    else
                        --h1;
                    break;
                case KEY_DOWN:
                    if(h1 == n_choices)
                        h1 = 1;
                    else 
                        ++h1;
                    break;
                case 10:
                    ch1 = h1;
                    break;
            }

            print_menu_1(win1, h1);
            if(ch1 != 0)	/* User did a choice come out of the infinite loop */
                break;
        }

        if(ch1 == 1)
        {
            profile(win2);
        }

        if(ch1 == 2)
        {
            // flights(win2);
        }

        if(ch1 == 3)
        {
            // trains(win2);
        }

        if(ch1 == 4)
        {
            // buses(win2);
        }

        if(ch1 == 5)
        {
            // wayfarer(win2);
        }
    }
}

void print_menu_1(WINDOW *win1, int h1)
{
    int x, y, i;	

	x = 2;
	y = 3;

    box(win1, 0, 0);

    for(i = 0; i < n_choices; ++i)
	{	if(h1 == i + 1) /* High light the present choice */
		{	
            wattron(win1, A_REVERSE); 
			mvwprintw(win1, y, x, "%s", choices[i]);
			wattroff(win1, A_REVERSE);
		}
		else
			mvwprintw(win1, y, x, "%s", choices[i]);
		++y;
	}

    wrefresh(win1);
}

void print_menu_2(WINDOW *win, int x, int y)
{
    box(win, y, x);

    wrefresh(win);
}

void profile(WINDOW *win)
{
    echo();
    wattron(win, A_BOLD | A_UNDERLINE);
    mvwprintw(win, 1, 20, "AVIAN AURA");
    wattroff(win, A_BOLD | A_UNDERLINE);

    char username[100];
    char password[100];

    curs_set(1);

    mvwprintw(win, 7, 11, "Username: ");
    wgetstr(win, username); // Input for username

    mvwprintw(win, 8, 11, "Password: ");
    curs_set(0);
    noecho();

    curs_set(1);
    wgetstr(win, password); // Input for password
    curs_set(0);
    noecho();

    // Do something with username and password here, e.g., validate credentials

    // Display the entered username and password
    mvwprintw(win, 10, 11, "Entered Username: %s", username);
    mvwprintw(win, 11, 11, "Entered Password: %s", password);

    // // Print Log-in, Sign up, and Forgot Password buttons
    // mvwprintw(win, 12, 24, "[ LOG-IN ]");
    // mvwprintw(win, 12, 34, "[ SIGN-UP ]");
    // mvwprintw(win, 13, 24, "[ Forgot Password? ]");

    // refresh();

    // int ch = wgetch(win);
    // if (ch == KEY_MOUSE) {
    //   MEVENT event;
    //   getmouse(&event);
    //   int clicked_button = handle_mouse_click(event.y, event.x);
    //   if (clicked_button == 1) {
    //     // Handle LOG-IN button click
    //   } else if (clicked_button == 2) {
    //     // Handle SIGN-UP button click
    //   } else if (clicked_button == 3) {
    //     // Handle Forgot Password? button click
    //   }
    // }

    // // Refresh the window to display the entered username and password
    // wrefresh(win);
}

void start(WINDOW *win)
{
    echo();
    while(1)
    {
        print_menu_2(win, 0, 0);
        
        mvwprintw(win, 1, 8, "    _        _                  _                   ");
        mvwprintw(win, 2, 8, "   / \\__   _(_) __ _ _ __      / \\  _   _ _ __ __ _ ");
        mvwprintw(win, 3, 8, "  / _ \\ \\ / / |/ _` | '_ \\    / _ \\| | | | '__/ _` |");
        mvwprintw(win, 4, 8, " / ___ \\ V /| | (_| | | | |  / ___ \\ |_| | | | (_| |");
        mvwprintw(win, 5, 8, "/_/   \\_\\_/ |_|\\__,_|_| |_| /_/   \\_\\__,_|_|  \\__,_|");

        char username[100];
        char password[100];

        curs_set(1);

        mvwprintw(win, 8, 25, "Username: ");
        wgetstr(win, username); // Input for username

        mvwprintw(win, 9, 25, "Password: ");
        curs_set(0);
        noecho();

        curs_set(1);
        wgetstr(win, password); // Input for password
        curs_set(0);
        noecho();

        // Do something with username and password here, e.g., validate credentials

        // Display the entered username and password
        mvwprintw(win, 10, 20, "Entered Username: %s", username);
        mvwprintw(win, 11, 20, "Entered Password: %s", password);

    // Print Log-in, Sign up, and Forgot Password buttons
        mvwprintw(win, 12, 24, "[ LOG-IN ]");
        mvwprintw(win, 12, 34, "[ SIGN-UP ]");
        mvwprintw(win, 13, 24, "[ Forgot Password? ]");

    refresh();

    int ch = wgetch(win);
    if (ch == KEY_MOUSE) {
      MEVENT event;
      getmouse(&event);
      int clicked_button = handle_mouse_click(event.y, event.x);
      if (clicked_button == 1) {
        // Handle LOG-IN button click
      } else if (clicked_button == 2) {
        // Handle SIGN-UP button click
      } else if (clicked_button == 3) {
        // Handle Forgot Password? button click
      }
    }

    // Refresh the window to display the entered username and password
    wrefresh(win);

        int ch = wgetch(win);
        if (ch == KEY_MOUSE) {
          MEVENT event;
          getmouse(&event);
          int clicked_button = handle_mouse_click(event.y, event.x);
          if (clicked_button == 1) {
            // Handle LOG-IN button click
          } else if (clicked_button == 2) {
            // Handle SIGN-UP button click
          } else if (clicked_button == 3) {
            // Handle Forgot Password? button click
          }
        }

        char c3 = wgetch(win);

        if (c3 == 10)
        {
            break;
        }
    }
    noecho();
}