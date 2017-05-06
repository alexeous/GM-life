#ifndef REGRAPH_H
#define REGRAPH_H

///////////// EMPTY LIB //////////////////

enum colors {
    BLACK = 0,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    LIGHTGRAY,
    DARKGRAY,
    LIGHTBLUE,
    LIGHTGREEN,
    LIGHTCYAN,
    LIGHTRED,
    LIGHTMAGENTA,
    YELLOW,
    WHITE
};

enum line_styles { SOLID_LINE, DOTTED_LINE,
    CENTER_LINE,
    DASHED_LINE,
    USERBIT_LINE
};

enum fill_styles {
    EMPTY_FILL, SOLID_FILL, LINE_FILL, STICK_FILL, LTSLASH_FILL, SLASH_FILL, BKSLASH_FILL, LTBKSLASH_FILL,
    HATCH_FILL, XHATCH_FILL, INTERLEAVE_FILL, WIDE_DOT_FILL, CLOSE_DOT_FILL, USER_FILL
};

enum horiz { LEFT_TEXT, CENTER_TEXT, RIGHT_TEXT };
enum vertical { BOTTOM_TEXT, VCENTER_TEXT, TOP_TEXT };

enum font_names {
    DEFAULT_FONT, TRIPLEX_FONT, SMALL_FONT, SANS_SERIF_FONT, GOTHIC_FONT, SCRIPT_FONT,
    SIMPLEX_FONT, TRIPLEX_SCR_FONT, COMPLEX_FONT, EUROPEAN_FONT, BOLD_FONT
};

enum putimage_ops { COPY_PUT, XOR_PUT, OR_PUT, AND_PUT, NOT_PUT };

enum font_attributes { BOLD = 1, ITALIC = 2, UNDERLINE = 4, STRIKEOUT = 8, ANTIALIASED = 16 };

enum keys { KEY_LEFT, KEY_UP, KEY_RIGHT, KEY_DOWN,
            KEY_END, KEY_HOME, KEY_INSERT, KEY_DELETE,
            KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6,
            KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_F11, KEY_F12, VK_RETURN, VK_ESCAPE };

#define CURRENT_WINDOW -1   // константы для
#define ALL_WINDOWS -2      // initwindow

#define HORIZ_DIR       0   // для settextjustify
#define VERT_DIR        1

#define DEG2RAD 0.0174532
#define TAN_30DEG  0.5773502

#define MAX_KQ_SIZE 100     // макс. кол-во элементов в очереди нажатых клавиш клавиатуры
#define MAX_MV_SIZE 100     // макс. кол-во элементов в списке событий мыши
#define CLOSE_FROM_CLOSEGRAPH 0xCC0

int COLOR(int r, int g, int b);
int initwindow(int width, int height, const char *title = "Graphic Window",
                      int /*(unused) left*/ = 0, int /*(unused) top*/ = 0, bool /*(unused) dbflag*/ = false,
                      bool closeflag = true);

void closegraph(int windowID = ALL_WINDOWS);
void setcurrentwindow(int window);
int getcurrentwindow();

void delay(int ms);

void sector(int x, int y, int stangle, int endangle, int xrad, int yrad);
void pieslice(int x, int y, int stangle, int endangle, int radius);
void ellipse(int x, int y, int stangle, int endangle, int xrad, int yrad);
void arc(int x, int y, int stangle, int endangle, int radius);
void circle(int x, int y, int radius);
void rectangle(int left, int top, int right, int bottom);
void bar(int left, int top, int right, int bottom);
void bar3d(int left, int top, int right, int bottom, int depth, int topflag);
void drawpoly(int n_points, int *points);
void fillpoly(int n_points, int *points);
void fillellipse(int x, int y, int xradius, int yradius);
void floodfill(int x, int y, int border);

void outtext(const char *textstring);
void outtextxy(int x, int y, const char *textstring);
void settextjustify(int horiz, int vert);
void settextstyle(int font, int direction, int charsize);
void settextstyle(const char *fontface, int attr, int angle, int charsize);
int textheight(const char *textstring);
int textwidth(const char *textstring);

void cleardevice();
void moveto(int x, int y);
void moverel(int dx, int dy);
void lineto(int x, int y);
void linerel(int dx, int dy);
void line(int startx, int starty, int endx, int endy);

void putpixel(int x, int y, int color);
int getpixel(int x, int y);
void setcolor(int color);
int getcolor();
void setbkcolor(int bkcolor);
int getbkcolor();

void setbktransparent(bool transparent);
bool getbktransparent();
void setlinestyle(int linestyle, unsigned upattern, int thickness);
void setfillstyle(int pattern, int color, bool transparentBk = true);
void setfillpattern(char *upattern, int color, bool transparentBk = true);
void getfillpattern(char *pattern);

unsigned imagesize(int left, int top, int right, int bottom);
void getimage(int left, int top, int right, int bottom, void *bitmap);
void putimage(int left, int top, void *bitmap, int op);

int mousex();
int mousey();
int ismouseclick(int kind);
void clearmouseclick(int kind);
void getmouseclick(int kind, int &x, int &y);

int getx();
int gety();
int getmaxheight();
int getmaxwidth();
int getwindowwidth();
int getwindowheight();
int getmaxx();
int getmaxy();

int getch();
int kbhit();

#endif // REGRAPH_H
