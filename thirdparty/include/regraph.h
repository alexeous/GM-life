#ifndef REGRAPH_H
#define REGRAPH_H

#include <math.h>         // sin, cos
#include <windows.h>
#include <windowsx.h>     // GET_X_LPARAM, GET_Y_LPARAM
#include <vector>
#include <queue>
#include <stdio.h>        // sprintf
#include <conio.h>        // _getch()

enum colors {
    BLACK = 0,
    BLUE = RGB(0, 0, 127),
    GREEN = RGB(0, 127, 0),
    CYAN = RGB(0, 127, 127),
    RED = RGB(127, 0, 0),
    MAGENTA = RGB(127, 0, 127),
    BROWN = RGB(90, 60, 0),
    LIGHTGRAY = RGB(200, 200, 200),
    DARKGRAY = RGB(100, 100, 100),
    LIGHTBLUE = RGB(0, 0, 255),
    LIGHTGREEN = RGB(0, 255, 0),
    LIGHTCYAN = RGB(0, 255, 255),
    LIGHTRED = RGB(255, 0, 0),
    LIGHTMAGENTA = RGB(255, 0, 255),
    YELLOW = RGB(255, 255, 0),
    WHITE = RGB(255, 255, 255)
};

enum line_styles { SOLID_LINE = PS_SOLID, DOTTED_LINE = PS_DOT,
    CENTER_LINE = PS_DASHDOT,
    DASHED_LINE = PS_DASH,
    USERBIT_LINE = PS_USERSTYLE
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

enum keys { KEY_LEFT = VK_LEFT, KEY_UP = VK_UP, KEY_RIGHT = VK_RIGHT, KEY_DOWN = VK_DOWN,
            KEY_END = VK_END, KEY_HOME = VK_HOME, KEY_INSERT = VK_INSERT, KEY_DELETE = VK_DELETE,
            KEY_F1 = VK_F1, KEY_F2 = VK_F2, KEY_F3 = VK_F3, KEY_F4 = VK_F4, KEY_F5 = VK_F5, KEY_F6 = VK_F6,
            KEY_F7 = VK_F7, KEY_F8 = VK_F8, KEY_F9 = VK_F9, KEY_F10 = VK_F10, KEY_F11 = VK_F11, KEY_F12 = VK_F12 };

#define CURRENT_WINDOW -1   // константы для
#define ALL_WINDOWS -2      // initwindow

#define HORIZ_DIR       0   // для settextjustify
#define VERT_DIR        1

#define DEG2RAD 0.0174532
#define TAN_30DEG  0.5773502

#define MAX_KQ_SIZE 100     // макс. кол-во элементов в очереди нажатых клавиш клавиатуры
#define MAX_MV_SIZE 100     // макс. кол-во элементов в списке событий мыши


class RegraphWindow {
private:
    typedef struct { int kind, x, y; } mouseEvent;
private:
    static void showLastError(const char *prefixMessage);
    static LRESULT CALLBACK windowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
    static void createAndProcess(RegraphWindow *window);
    static bool isServiceKey(WPARAM key);
    static bool isMouseEvent(UINT msg);
    void recreatePen();
    void recreateFont();
    void refreshWindow();
    void refreshWindow(RECT rect);

    typedef void (*putFunction)(HDC dc, int x, int y, int color);                           // тип функции вывода для putImage
    static void putCopy(HDC dc, int x, int y, int color);
    static void putXor(HDC dc, int x, int y, int color);
    static void putOr(HDC dc, int x, int y, int color);
    static void putAnd(HDC dc, int x, int y, int color);
    static void putNot(HDC dc, int x, int y, int color);

public:
    RECT getWindowRect();
    HWND getWindowHandle();
    HDC& getDeviceContext();
    int getID();

    bool initialize(int id, int width, int height, const char *title, bool closeflag, void (*onDestroyedFunc)(int));
    void cleanup();
    void clearDevice();

    void sector(int x, int y, int stangle, int endangle, int xradius, int yradius);
    void circle(int x, int y, int radius);
    void ellipse(int x, int y, int stangle, int endangle, int xradius, int yradius);
    void fillEllipse(int x, int y, int xrad, int yrad);
    void rectangle(int left, int top, int right, int bottom);
    void bar(int left, int top, int right, int bottom);
    void bar3d(int left, int top, int right, int bottom, int depth, int topflag);
    void drawPoly(int numpoints, int *points);
    void fillPoly(int numpoints, int *points);
    void floodFill(int x, int y, int borderColor);
    void lineTo(int x, int y);
    void lineRel(int dx, int dy);
    void line(int startx, int starty, int endx, int endy);
    void moveTo(int x, int y);
    void moveRel(int dx, int dy);

    void setPixel(int x, int y, int color);
    int getPixel(int x, int y);
    void setColor(int color);
    int getColor();
    void setBkColor(int backgroundColor);
    int getBkColor();

    void outText(const char *textstring);
    void outTextXY(int x, int y, const char *textstring);
    void setLineStyle(int linestyle, unsigned upattern, int thickness);
    void setFillStyle(int style, int color, bool transparentBk);
    void setFillPattern(char *pattern, int color, bool transparentBk);
    void getFillPattern(char* pattern);

    void getImage(int left, int top, int right, int bottom, void *bitmap);
    void putImage(int left, int top, void *bitmap, int op);

    void setTextStyle(int font, int direction, int charsize);
    void setTextStyle(const char *face, int attr, int angle, int charsize);
    void setTextJustify(int horiz, int vert);
    int textHeight(const char *textstring);
    int textWidth(const char *textstring);

    int getMouseX();
    int getMouseY();
    bool isMouseClick(int kind);
    void clearMouseClick(int kind);
    void getMouseClick(int kind, int &x, int &y);

    int getMaxX();
    int getMaxY();

    int getch();
    int kbhit();

private:
    enum { INIT_PROCESS, INIT_SUCCESS, INIT_FAIL };
    int isInitialized;

    bool closeFlag;
    int id, width, height;
    char title[100], className[20];

    HANDLE thread = 0;
    HANDLE keyboardMutex = 0, mouseMutex = 0, drawMutex = 0;
    std::queue<int> keyboardQueue;

    std::vector<mouseEvent> mouseVector;
    int mouseX = 0, mouseY = 0;

    HWND windowHandle = 0;
    HINSTANCE instanceHandle = 0;
    HDC memDC = 0;
    HBITMAP outputBitmap = 0;
    HDC outputDC = 0;
    HPEN pen = 0;
    HFONT font = 0;
    HBRUSH brush = 0, backgroundBrush = 0;

    int mainColor = WHITE, brushColor = WHITE, backgroundColor = BLACK;
    int penWidth = 1, penStyle = PS_SOLID;
    DWORD penPatternCount;
    DWORD penPattern[16];
    char *fillPattern = NULL;
    char fontFace[50] = "System";
    int fontAngle_tenths = 0, fontAttr = 0, fontSize = 10;

    void (*onDestroyedFunc)(int);
};

class Regraph {
private:
    Regraph() { }
    static void onWindowDestroyed(int id);
    static RegraphWindow* currentWindow();
    static HDC& currentDC();
public:
    static RegraphWindow* findWindowByID(int id, int *out_index = NULL);
    static RegraphWindow* findWindowByHWND(HWND hwnd);

    static int initwindow(int width, int height, const char *title, bool closeflag);
    static void closegraph(int windowID, bool doExit = false);
    static void setcurrentwindow(int window);
    static int getcurrentwindow();

    static void sector(int x, int y, int sa, int ea, int xr, int yr);
    static void circle(int x, int y, int radius);
    static void ellipse(int x, int y, int sa, int ea, int xr, int yr);
    static void rectangle(int left, int top, int right, int bottom);
    static void bar(int left, int top, int right, int bottom);
    static void bar3d(int left, int top, int right, int bottom, int depth, int topflag);
    static void drawpoly(int numpoints, int *points);
    static void fillpoly(int numpoints, int *points);
    static void fillellipse(int x, int y, int xrad, int yrad);
    static void floodfill(int x, int y, int borderColor);

    static void cleardevice();
    static void moveto(int x, int y);
    static void moverel(int dx, int dy);
    static void lineto(int x, int y);
    static void linerel(int dx, int dy);
    static void line(int startx, int starty, int endx, int endy);

    static void outtext(const char *textstring);
    static void outtextxy(int x, int y, const char *textstring);
    static void settextjustify(int horiz, int vert);
    static void settextstyle(int font, int direction, int charsize);
    static void settextstyle(const char *face, int attr, int angle, int size);
    static int textheight(const char *textstring);
    static int textwidth(const char *textstring);

    static int getpixel(int x, int y);
    static void putpixel(int x, int y, int color);
    static void setcolor(int color);
    static int getcolor();
    static void setbkcolor(int bkcolor);
    static int getbkcolor();

    static void setbktransparent(bool transparent);
    static bool getbktransparent();
    static void setlinestyle(int style, unsigned pattern, int thick);
    static void setfillstyle(int style, int color, bool trnspBk);
    static void setfillpattern(char *upattern, int color, bool trnspBk);
    static void getfillpattern(char *pattern);

    static void getimage(int left, int top, int right, int bottom, void *bitmap);
    static void putimage(int left, int top, void *bitmap, int op);

    static int mousex();
    static int mousey();
    static int ismouseclick(int kind);
    static void clearmouseclick(int kind);
    static void getmouseclick(int kind, int &x, int &y);

    static int getx();
    static int gety();
    static int getwindowwidth();
    static int getwindowheight();
    static int getmaxx();
    static int getmaxy();

    static int getch();
    static int kbhit();

private:
    static int currentWindowID, currentWindowIndex;
    static std::vector<RegraphWindow> windowList;
};

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
// более продвинутая функция для установки шрифта. Можно явно указать имя шрифта, его атрибуты, угол наклона и размер
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
void setbkcolor(int bkcolor);    // не очищает экран, только устанавливает цвет фона; для очистки см. cleardevice()
int getbkcolor();

void setbktransparent(bool transparent);
bool getbktransparent();
void setlinestyle(int linestyle, unsigned upattern, int thickness);
void setfillstyle(int pattern, int color, bool transparentBk = false);
void setfillpattern(char *upattern, int color, bool transparentBk = false);
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

int getch(); // (см. define) коды стрелок - 37-40:  ←37  ↑38 →39 ↓40;   F1-F12 ARE 112-123
int kbhit();

//}
#endif // REGRAPH_H
