#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include<stdbool.h>


#define JAPN {"ア", "イ", "ウ", "エ", "オ", "カ", "キ", "ク", "ケ", "コ", "サ", "シ", "ス", "セ", "ソ", "ガ", "ギ", "グ", "ゲ", "ゴ", "パ", "ピ", "プ", "ペ", "ポ"}

unsigned int mx_strlen(const char *s);
