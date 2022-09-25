#include "header.h"

char disText(int x, int y, int start, int My, char st) {
	char i;
	i = 32 + rand() % 94;
	attron(COLOR_PAIR(1));
	mvaddch(x, y, i);
	attroff(COLOR_PAIR(1));
	attron(COLOR_PAIR(2));
	mvaddch(x - 1, y, st);
	attroff(COLOR_PAIR(2));
	if (start == My - 1)
	{
		attron(COLOR_PAIR(2));
		mvaddch(x, y, st);
		attroff(COLOR_PAIR(2));
	}
    return i;
}

char *disT(int x, int y, int start, int My, char *st) {
	char *t;
	char *japanese[] = JAPN;
	t = japanese[rand() % 25];
	attron(COLOR_PAIR(1));
	mvaddstr(x, y, t);
	attroff(COLOR_PAIR(1));
	attron(COLOR_PAIR(2));
	mvaddstr(x - 1, y, st);
	attroff(COLOR_PAIR(2));
	if (start == My - 1)
	{
		attron(COLOR_PAIR(2));
		mvaddstr(x, y, st);
		attroff(COLOR_PAIR(2));
	}
    return t;
}

void typeOfText(char* str)
{
    for(unsigned int i = 0; i < mx_strlen(str); i++)
	{
        mvaddch(5, i + 4, str[i] | COLOR_PAIR(1));
        refresh();
        usleep(100000);
    }
    usleep(200000);
    clear();
    refresh();
}

void find(int argc, char *argv[], char *flags)
{
    bool i = false;
    bool a = true;
    if (argc == 2)
	{
		if (mx_strlen(argv[1]) == 2)
		{
			if (argv[1][0] == '-' && argv[1][1] == 'j')
			{
				i = true;
			}
			else if (argv[1][0] == '-' && argv[1][1] == 's')
			{
				a = false;
			}
			else
			{
				write(1, "usage: ./matrix_rain [-s] [-j]\n", mx_strlen("usage: ./matrix_rain [-s] [-j]\n"));
				exit(0);
			}
		}
		else if (mx_strlen(argv[1]) == 3)
		{
			if (argv[1][0] == '-' && ((argv[1][1] == 'j' && argv[1][2] == 's') || (argv[1][1] == 's' && argv[1][2] == 'j'))) 
			{
				a = false;
				i = true;
			}
			else
			{
				write(1, "usage: ./matrix_rain [-s] [-j]\n", mx_strlen("usage: ./matrix_rain [-s] [-j]\n"));
				exit(0);
			}
		}
		else
		{
			write(1, "usage: ./matrix_rain [-s] [-j]\n", mx_strlen("usage: ./matrix_rain [-s] [-j]\n"));
			exit(0);
		}
	}
	else if (argc == 3)
	{
		if (mx_strlen(argv[2]) == 2 && mx_strlen(argv[1]) == 2) 
		{
			if (((argv[1][0] == '-' && argv[1][1] == 'j') && (argv[2][0] == '-' && argv[2][1] == 's')) || ((argv[1][0] == '-' && argv[1][1] == 's') && (argv[2][0] == '-' && argv[2][1] == 'j')))
			{
				a = false;
				i = true;
			}
			else
			{
				write(1, "usage: ./matrix_rain [-s] [-j]\n", mx_strlen("usage: ./matrix_rain [-s] [-j]\n"));
				exit(0);
			}
		}
		else
		{
			write(1, "usage: ./matrix_rain [-s] [-j]\n", mx_strlen("usage: ./matrix_rain [-s] [-j]\n"));
			exit(0);
		}
    }
	else if (argc > 3)
	{
		write(1, "usage: ./matrix_rain [-s] [-j]\n", mx_strlen("usage: ./matrix_rain [-s] [-j]\n"));
		exit(0);
	}              
    if (a)
        flags[0] = '1';
    if (i)
        flags[1] = '1';
}

void CreateRain(bool c) {
	int valOfX;
	int valOfY;
	
	curs_set(0);
	
    	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	time_t  timer;
	
	srand((unsigned) time(&timer));
	
	getmaxyx(stdscr, valOfY, valOfX);
	
	int back[valOfX];
	int end[valOfX];
	int Y[valOfX];
	int flag[valOfX];
	int start[valOfX];
	for (int i = 0; i < valOfX; i++)
	{
		start[i] = -valOfY + rand() % valOfY;
	}
	int mid[valOfX];
	for (int i = 0; i < valOfX; i++)
	{
		mid[i] = rand() % valOfY;
	};
	
	for (int i = 0; i < valOfX; i++)
	{
		 Y[i] = 0;
	}
	int speedOfText = 100;

	int col = 2;
	int typeCol = 1;
	int fontColor = COLOR_GREEN;
	int backColor = COLOR_BLACK;

	char carter[valOfX];
	char *t[valOfX];
	
	while (true) 
	{
		
		for (int i = 0; i < valOfX; i++) 
		{
			if (i % 5 == 0) 
			{
				back[i] = start[i] - mid[i];
				if (flag[i] == 1) 
				{
					if (end[i] == valOfY+1)
					{
						flag[i] = 0;
					}
					move(end[i], i);
					printw(" ");
					end[i]++;
				}
				if (start[i] == valOfY) 
				{
					Y[i] = 0;
					start[i] = 0;
					flag[i] = 1;
					end[i] = valOfY - mid[i];
					mid[i] = rand() % valOfY;
				}
				if(back[i] > -1) 
				{
					printw(" ");
					move(back[i], i);
					printw(" ");
				}
				if (start[i] > -1) 
                		{
					if (c == true)
                        			t[i] = disT(Y[i], i, start[i], valOfY, t[i]);
					else
						carter[i] = disText(Y[i], i, start[i], valOfY, carter[i]);
				}
			}
		}
		for(int i = 0; i < valOfX; i++) {
			if (start[i] >= 0)
				Y[i]++;
		}
		usleep(1000 * speedOfText);
		refresh();
		for(int i = 0; i < valOfX; i++)
		{
			start[i]++;
		}
		char file = getch();
		switch (file) {
			case 'b':
				typeCol = 2;
				break;
				
			case 'f':
				typeCol = 1;
				break;
				
			case 'q':
				echo();
				endwin();
				exit(0);
                		break;
			case '-':
				if (speedOfText < 300) 
				{
					if (speedOfText <= 10)
						speedOfText++;
					else
						speedOfText += 10;
				}
				break;
				
			case '+':
				if (speedOfText > 1) 
				{
					if (speedOfText <= 11)
						speedOfText--;
					else
						speedOfText -= 10;
				}
				break;

			case '1':
				if (typeCol == 1)
					fontColor = COLOR_GREEN;
				else
					backColor = COLOR_GREEN;
				break;

			case '2':
				if (typeCol == 1)
					fontColor = COLOR_BLUE;
				else
					backColor = COLOR_BLUE;
				break;

			case '3':
				if (typeCol == 1)
					fontColor = COLOR_CYAN;
				else
					backColor = COLOR_CYAN;
				break;

			case '4':
				if (typeCol == 1)
					fontColor = COLOR_MAGENTA;
				else
					backColor = COLOR_MAGENTA;
				break;

			case '5':
				if (typeCol == 1)
					fontColor = COLOR_RED;
				else
					backColor = COLOR_RED;
				break;

			case '6':
				if (typeCol == 1)
					fontColor = COLOR_YELLOW;
				else
					backColor = COLOR_YELLOW;
				break;

			case '7':
				if (typeCol == 1)
					fontColor = COLOR_WHITE;
				else
					backColor = COLOR_WHITE;
				break;

			case '8':
				if (typeCol == 1)
					fontColor = COLOR_BLACK;
				else
					backColor = COLOR_BLACK;
       
				break;
			case '.':
				col = 1;
				break;
			case '0':
				col = 2;
				break;
		}
		init_pair(col, fontColor, backColor);
	}
}

void init(){
	initscr();
	noecho();
	start_color();
}
void PrintTypeOfText(){
    refresh();
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
    typeOfText("Wake up , Neo..");
    typeOfText("The Matrix has you..");
    typeOfText("Follow the white rabbit");
    typeOfText("Knock, knock, Neo");
}
int main(int argc, char *argv[]) {
	setlocale(LC_CTYPE, "");
    char *flag = (char*)malloc(sizeof(char));
	find(argc, argv, flag);
	init();
	nodelay(stdscr, 1);
	if (flag[0] == '1')
	{
		PrintTypeOfText();
	}
	CreateRain(flag[1] == '1');
  	endwin();
	return 0;
}


