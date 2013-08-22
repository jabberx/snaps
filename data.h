#include <SDL/SDL.h>
#include "defs.h"

extern Cloud cloud;
extern Snapshot snap;

extern float *zbuffer;
extern int32_t *Xbuf, *Ybuf, *Zbuf;
extern int8_t *NXbuf, *NYbuf, *NZbuf;
extern uint8_t *SHbuf;
extern float yaw, pitch, cosyaw, sinyaw, cospitch, sinpitch;
extern float camx, camy, camz;
extern float viewx, viewy, viewz;
extern float lightx, lighty, lightz;
extern float fov;
extern const double DTR, RTD;
extern const double PI;

extern const int WIDTH, HEIGHT;
extern const float shrink_val;

extern SDL_Event event;
extern int32_t MOUSEX, MOUSEY;
extern int32_t KEY[128];
extern int32_t BUTTON[5];
extern int32_t exit_flag;

extern SDL_Surface *screen;
extern uint32_t *img;

enum buttons{LB,MB,RB,WUP,WDOWN };
enum keys{BACKSPACE,TAB,CLEAR,ENTER,PAUSE,ESCAPE,SPACE,EXCLAIM,QUOTEDBL,
      HASH,DOLLAR,AMPERSAND,QUOTE,LEFTPAREN,RIGHTPAREN,ASTERISK,PLUS,
      COMMA,MINUS,PERIOD,SLASH,key_0,key_1,key_2,key_3,key_4,key_5,
      key_6,key_7,key_8,key_9,COLON,SEMICOLON,LESS,EQUALS,GREATER,
      QUESTION,AT,LEFTBRACKET,BACKSLASH,RIGHTBRACKET,CARET,UNDERSCORE,
      BACKQUOTE,key_a,key_b,key_c,key_d,key_e,key_f,key_g,key_h,key_i,
      key_j,key_k,key_l,key_m,key_n,key_o,key_p,key_q,key_r,key_s,
      key_t_,key_u,key_v,key_w,key_x,key_y,key_z,DEL,KP0,KP1,KP2,
      KP3,KP4,KP5,KP6,KP7,KP8,KP9,KP_PERIOD,KP_DIVIDE,KP_MULTIPLY,
      KP_MINUS,KP_PLUS,KP_ENTER,KP_EQUALS,UP,DOWN,RIGHT,LEFT,INSERT,
      HOME,END,PAGEUP,PAGEDOWN,F1,F2,F3,F4,F5,F6,F7,F8,F9,F10,
      F11,F12,F13,F14,F15,NUMLOCK,CAPSLOCK,SCROLLOCK,RSHIFT,LSHIFT,
      RCTRL,LCTRL,RALT,LALT };