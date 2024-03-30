#include "dependencies.h>

void print_menu_1(WINDOW *win1, int h1);
void print_menu_2(WINDOW *win2, int h2);

void profile(WINDOW *win);
void flights(WINDOW *win);
void trains(WINDOW *win);
void buses(WINDOW *win);
void wayfares(WINDOW *win);

char* choices[] = {" Profile ", " Flights ", " Buses ", " Wayfares "};
int n_choices = sizeof(choices) / sizeof(char *);

int main(void)
{
    WINDOW *win1;
    WINDOW *win2;


    initscr();
    clear();
    cbreak();

    curs_set(0);

    win1 = newwin(20, 15, 0, 0);
    win2 = newwin(20, 50, 0, 16);
    keypad(win1, TRUE);
    keypad(win2, TRUE);

    int h1 = 1;
    int h2 = 1;

    int ch1 = 0;
    int ch2 = 0;

    int c = 0;

    while(1)
    {
        print_menu_1(win1, h1);
        print_menu_2(win2, h2);
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
            // profile(win2);
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
            // wayfares(win2);
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

void print_menu_2(WINDOW *win2, int h2)
{
    box(win2, 0, 0);

    wrefresh(win2);
}

void profile(WINDOW *win)
{
    // login and signup data will be stored from here
}
