#include "data.h"

void SDL_Initialize() 
{
#ifdef FULLSCREEN
	screen = SDL_SetVideoMode(WIDTH, HEIGHT, DEPTH, 
									SDL_HWSURFACE|SDL_FULLSCREEN);
#else
	screen = SDL_SetVideoMode(WIDTH, HEIGHT, DEPTH, SDL_HWSURFACE);
#endif
	img = (Uint32*)malloc(WIDTH*HEIGHT*sizeof(Uint32));
}
void SDL_FlipScreen() 
{
	if(SDL_MUSTLOCK(screen)) if(SDL_LockSurface(screen)<0) return;
	memcpy(screen->pixels, img, WIDTH*HEIGHT*sizeof(int));
	if(SDL_MUSTLOCK(screen)) SDL_UnlockSurface(screen);
	SDL_Flip(screen);
}

__inline void SDL_DrawPixel(int x, int y, Uint32 col) 
{
	y = HEIGHT-1-y;
	img[x + y*WIDTH + 0] = col; 
}

void SDL_HandleEvents() 
{
  while(SDL_PollEvent(&event)) {
    if(event.type==SDL_MOUSEMOTION) {
      MOUSEX=event.motion.x; MOUSEY=event.motion.y; }
    if(event.type==SDL_QUIT) {
      exit_flag=1;
      SDL_Quit();
      exit(1); }
    if(event.type==SDL_MOUSEBUTTONDOWN) {
      MOUSEX=event.motion.x; MOUSEY=event.motion.y;
      if(event.button.button==SDL_BUTTON_LEFT)BUTTON[LB]=1;
      if(event.button.button==SDL_BUTTON_MIDDLE)BUTTON[MB]=1;
      if(event.button.button==SDL_BUTTON_RIGHT)BUTTON[RB]=1;
      if(event.button.button==SDL_BUTTON_WHEELUP)BUTTON[WUP]=1;
      if(event.button.button==SDL_BUTTON_WHEELDOWN)BUTTON[WDOWN]=1; }
    if(event.type==SDL_MOUSEBUTTONUP) {
      MOUSEX=event.motion.x; MOUSEY=event.motion.y;
      if(event.button.button==SDL_BUTTON_LEFT)BUTTON[LB]=0;
      if(event.button.button==SDL_BUTTON_MIDDLE)BUTTON[MB]=0;
      if(event.button.button==SDL_BUTTON_RIGHT)BUTTON[RB]=0;
      if(event.button.button==SDL_BUTTON_WHEELUP)BUTTON[WUP]=0;
      if(event.button.button==SDL_BUTTON_WHEELDOWN)BUTTON[WDOWN]=0; }
    if(event.type==SDL_KEYDOWN) {
      int bset=1;
      if(event.key.keysym.sym==SDLK_BACKSPACE)KEY[BACKSPACE]=bset;
      if(event.key.keysym.sym==SDLK_TAB)KEY[TAB]=bset;
      if(event.key.keysym.sym==SDLK_CLEAR)KEY[CLEAR]=bset;
      if(event.key.keysym.sym==SDLK_RETURN)KEY[ENTER]=bset;
      if(event.key.keysym.sym==SDLK_PAUSE)KEY[PAUSE]=bset;
      if(event.key.keysym.sym==SDLK_ESCAPE)KEY[ESCAPE]=bset;
      if(event.key.keysym.sym==SDLK_SPACE)KEY[SPACE]=bset;
      if(event.key.keysym.sym==SDLK_EXCLAIM)KEY[EXCLAIM]=bset;
      if(event.key.keysym.sym==SDLK_QUOTEDBL)KEY[QUOTEDBL]=bset;
      if(event.key.keysym.sym==SDLK_HASH)KEY[HASH]=bset;
      if(event.key.keysym.sym==SDLK_DOLLAR)KEY[DOLLAR]=bset;
      if(event.key.keysym.sym==SDLK_AMPERSAND)KEY[AMPERSAND]=bset;
      if(event.key.keysym.sym==SDLK_QUOTE)KEY[QUOTE]=bset;
      if(event.key.keysym.sym==SDLK_LEFTPAREN)KEY[LEFTPAREN]=bset;
      if(event.key.keysym.sym==SDLK_RIGHTPAREN)KEY[RIGHTPAREN]=bset;
      if(event.key.keysym.sym==SDLK_ASTERISK)KEY[ASTERISK]=bset;
      if(event.key.keysym.sym==SDLK_PLUS)KEY[PLUS]=bset;
      if(event.key.keysym.sym==SDLK_COMMA)KEY[COMMA]=bset;
      if(event.key.keysym.sym==SDLK_MINUS)KEY[MINUS]=bset;
      if(event.key.keysym.sym==SDLK_PERIOD)KEY[PERIOD]=bset;
      if(event.key.keysym.sym==SDLK_SLASH)KEY[SLASH]=bset;
      if(event.key.keysym.sym==SDLK_0)KEY[key_0]=bset;
      if(event.key.keysym.sym==SDLK_1)KEY[key_1]=bset;
      if(event.key.keysym.sym==SDLK_2)KEY[key_2]=bset;
      if(event.key.keysym.sym==SDLK_3)KEY[key_3]=bset;
      if(event.key.keysym.sym==SDLK_4)KEY[key_4]=bset;
      if(event.key.keysym.sym==SDLK_5)KEY[key_5]=bset;
      if(event.key.keysym.sym==SDLK_6)KEY[key_6]=bset;
      if(event.key.keysym.sym==SDLK_7)KEY[key_7]=bset;
      if(event.key.keysym.sym==SDLK_8)KEY[key_8]=bset;
      if(event.key.keysym.sym==SDLK_9)KEY[key_9]=bset;
      if(event.key.keysym.sym==SDLK_COLON)KEY[COLON]=bset;
      if(event.key.keysym.sym==SDLK_SEMICOLON)KEY[SEMICOLON]=bset;
      if(event.key.keysym.sym==SDLK_LESS)KEY[LESS]=bset;
      if(event.key.keysym.sym==SDLK_EQUALS)KEY[EQUALS]=bset;
      if(event.key.keysym.sym==SDLK_GREATER)KEY[GREATER]=bset;
      if(event.key.keysym.sym==SDLK_QUESTION)KEY[QUESTION]=bset;
      if(event.key.keysym.sym==SDLK_AT)KEY[AT]=bset;
      if(event.key.keysym.sym==SDLK_LEFTBRACKET)KEY[LEFTBRACKET]=bset;
      if(event.key.keysym.sym==SDLK_BACKSLASH)KEY[BACKSLASH]=bset;
      if(event.key.keysym.sym==SDLK_RIGHTBRACKET)KEY[RIGHTBRACKET]=bset;
      if(event.key.keysym.sym==SDLK_CARET)KEY[CARET]=bset;
      if(event.key.keysym.sym==SDLK_UNDERSCORE)KEY[UNDERSCORE]=bset;
      if(event.key.keysym.sym==SDLK_BACKQUOTE)KEY[BACKQUOTE]=bset;
      if(event.key.keysym.sym==SDLK_a)KEY[key_a]=bset;
      if(event.key.keysym.sym==SDLK_b)KEY[key_b]=bset;
      if(event.key.keysym.sym==SDLK_c)KEY[key_c]=bset;
      if(event.key.keysym.sym==SDLK_d)KEY[key_d]=bset;
      if(event.key.keysym.sym==SDLK_e)KEY[key_e]=bset;
      if(event.key.keysym.sym==SDLK_f)KEY[key_f]=bset;
      if(event.key.keysym.sym==SDLK_g)KEY[key_g]=bset;
      if(event.key.keysym.sym==SDLK_h)KEY[key_h]=bset;
      if(event.key.keysym.sym==SDLK_i)KEY[key_i]=bset;
      if(event.key.keysym.sym==SDLK_j)KEY[key_j]=bset;
      if(event.key.keysym.sym==SDLK_k)KEY[key_k]=bset;
      if(event.key.keysym.sym==SDLK_l)KEY[key_l]=bset;
      if(event.key.keysym.sym==SDLK_m)KEY[key_m]=bset;
      if(event.key.keysym.sym==SDLK_n)KEY[key_n]=bset;
      if(event.key.keysym.sym==SDLK_o)KEY[key_o]=bset;
      if(event.key.keysym.sym==SDLK_p)KEY[key_p]=bset;
      if(event.key.keysym.sym==SDLK_q)KEY[key_q]=bset;
      if(event.key.keysym.sym==SDLK_r)KEY[key_r]=bset;
      if(event.key.keysym.sym==SDLK_s)KEY[key_s]=bset;
      if(event.key.keysym.sym==SDLK_t)KEY[key_t_]=bset;
      if(event.key.keysym.sym==SDLK_u)KEY[key_u]=bset;
      if(event.key.keysym.sym==SDLK_v)KEY[key_v]=bset;
      if(event.key.keysym.sym==SDLK_w)KEY[key_w]=bset;
      if(event.key.keysym.sym==SDLK_x)KEY[key_x]=bset;
      if(event.key.keysym.sym==SDLK_y)KEY[key_y]=bset;
      if(event.key.keysym.sym==SDLK_z)KEY[key_z]=bset;
      if(event.key.keysym.sym==SDLK_DELETE)KEY[DEL]=bset;
      if(event.key.keysym.sym==SDLK_KP0)KEY[KP0]=bset;
      if(event.key.keysym.sym==SDLK_KP1)KEY[KP1]=bset;
      if(event.key.keysym.sym==SDLK_KP2)KEY[KP2]=bset;
      if(event.key.keysym.sym==SDLK_KP3)KEY[KP3]=bset;
      if(event.key.keysym.sym==SDLK_KP4)KEY[KP4]=bset;
      if(event.key.keysym.sym==SDLK_KP5)KEY[KP5]=bset;
      if(event.key.keysym.sym==SDLK_KP6)KEY[KP6]=bset;
      if(event.key.keysym.sym==SDLK_KP7)KEY[KP7]=bset;
      if(event.key.keysym.sym==SDLK_KP8)KEY[KP8]=bset;
      if(event.key.keysym.sym==SDLK_KP9)KEY[KP9]=bset;
      if(event.key.keysym.sym==SDLK_KP_PERIOD)KEY[KP_PERIOD]=bset;
      if(event.key.keysym.sym==SDLK_KP_DIVIDE)KEY[KP_DIVIDE]=bset;
      if(event.key.keysym.sym==SDLK_KP_MULTIPLY)KEY[KP_MULTIPLY]=bset;
      if(event.key.keysym.sym==SDLK_KP_MINUS)KEY[KP_MINUS]=bset;
      if(event.key.keysym.sym==SDLK_KP_PLUS)KEY[KP_PLUS]=bset;
      if(event.key.keysym.sym==SDLK_KP_ENTER)KEY[KP_ENTER]=bset;
      if(event.key.keysym.sym==SDLK_KP_EQUALS)KEY[KP_EQUALS]=bset;
      if(event.key.keysym.sym==SDLK_UP)KEY[UP]=bset;
      if(event.key.keysym.sym==SDLK_DOWN)KEY[DOWN]=bset;
      if(event.key.keysym.sym==SDLK_RIGHT)KEY[RIGHT]=bset;
      if(event.key.keysym.sym==SDLK_LEFT)KEY[LEFT]=bset;
      if(event.key.keysym.sym==SDLK_INSERT)KEY[INSERT]=bset;
      if(event.key.keysym.sym==SDLK_HOME)KEY[HOME]=bset;
      if(event.key.keysym.sym==SDLK_END)KEY[END]=bset;
      if(event.key.keysym.sym==SDLK_PAGEUP)KEY[PAGEUP]=bset;
      if(event.key.keysym.sym==SDLK_PAGEDOWN)KEY[PAGEDOWN]=bset;
      if(event.key.keysym.sym==SDLK_F1)KEY[F1]=bset;
      if(event.key.keysym.sym==SDLK_F2)KEY[F2]=bset;
      if(event.key.keysym.sym==SDLK_F3)KEY[F3]=bset;
      if(event.key.keysym.sym==SDLK_F4)KEY[F4]=bset;
      if(event.key.keysym.sym==SDLK_F5)KEY[F5]=bset;
      if(event.key.keysym.sym==SDLK_F6)KEY[F6]=bset;
      if(event.key.keysym.sym==SDLK_F7)KEY[F7]=bset;
      if(event.key.keysym.sym==SDLK_F8)KEY[F8]=bset;
      if(event.key.keysym.sym==SDLK_F9)KEY[F9]=bset;
      if(event.key.keysym.sym==SDLK_F10)KEY[F10]=bset;
      if(event.key.keysym.sym==SDLK_F11)KEY[F11]=bset;
      if(event.key.keysym.sym==SDLK_F12)KEY[F12]=bset;
      if(event.key.keysym.sym==SDLK_F13)KEY[F13]=bset;
      if(event.key.keysym.sym==SDLK_F14)KEY[F14]=bset;
      if(event.key.keysym.sym==SDLK_F15)KEY[F15]=bset;
      if(event.key.keysym.sym==SDLK_NUMLOCK)KEY[NUMLOCK]=bset;
      if(event.key.keysym.sym==SDLK_CAPSLOCK)KEY[CAPSLOCK]=bset;
      if(event.key.keysym.sym==SDLK_SCROLLOCK)KEY[SCROLLOCK]=bset;
      if(event.key.keysym.sym==SDLK_RSHIFT)KEY[RSHIFT]=bset;
      if(event.key.keysym.sym==SDLK_LSHIFT)KEY[LSHIFT]=bset;
      if(event.key.keysym.sym==SDLK_RCTRL)KEY[RCTRL]=bset;
      if(event.key.keysym.sym==SDLK_LCTRL)KEY[LCTRL]=bset;
      if(event.key.keysym.sym==SDLK_RALT)KEY[RALT]=bset;
      if(event.key.keysym.sym==SDLK_LALT)KEY[LALT]=bset; }
    if(event.type==SDL_KEYUP) {
      int bset=0;
      if(event.key.keysym.sym==SDLK_BACKSPACE)KEY[BACKSPACE]=bset;
      if(event.key.keysym.sym==SDLK_TAB)KEY[TAB]=bset;
      if(event.key.keysym.sym==SDLK_CLEAR)KEY[CLEAR]=bset;
      if(event.key.keysym.sym==SDLK_RETURN)KEY[ENTER]=bset;
      if(event.key.keysym.sym==SDLK_PAUSE)KEY[PAUSE]=bset;
      if(event.key.keysym.sym==SDLK_ESCAPE)KEY[ESCAPE]=bset;
      if(event.key.keysym.sym==SDLK_SPACE)KEY[SPACE]=bset;
      if(event.key.keysym.sym==SDLK_EXCLAIM)KEY[EXCLAIM]=bset;
      if(event.key.keysym.sym==SDLK_QUOTEDBL)KEY[QUOTEDBL]=bset;
      if(event.key.keysym.sym==SDLK_HASH)KEY[HASH]=bset;
      if(event.key.keysym.sym==SDLK_DOLLAR)KEY[DOLLAR]=bset;
      if(event.key.keysym.sym==SDLK_AMPERSAND)KEY[AMPERSAND]=bset;
      if(event.key.keysym.sym==SDLK_QUOTE)KEY[QUOTE]=bset;
      if(event.key.keysym.sym==SDLK_LEFTPAREN)KEY[LEFTPAREN]=bset;
      if(event.key.keysym.sym==SDLK_RIGHTPAREN)KEY[RIGHTPAREN]=bset;
      if(event.key.keysym.sym==SDLK_ASTERISK)KEY[ASTERISK]=bset;
      if(event.key.keysym.sym==SDLK_PLUS)KEY[PLUS]=bset;
      if(event.key.keysym.sym==SDLK_COMMA)KEY[COMMA]=bset;
      if(event.key.keysym.sym==SDLK_MINUS)KEY[MINUS]=bset;
      if(event.key.keysym.sym==SDLK_PERIOD)KEY[PERIOD]=bset;
      if(event.key.keysym.sym==SDLK_SLASH)KEY[SLASH]=bset;
      if(event.key.keysym.sym==SDLK_0)KEY[key_0]=bset;
      if(event.key.keysym.sym==SDLK_1)KEY[key_1]=bset;
      if(event.key.keysym.sym==SDLK_2)KEY[key_2]=bset;
      if(event.key.keysym.sym==SDLK_3)KEY[key_3]=bset;
      if(event.key.keysym.sym==SDLK_4)KEY[key_4]=bset;
      if(event.key.keysym.sym==SDLK_5)KEY[key_5]=bset;
      if(event.key.keysym.sym==SDLK_6)KEY[key_6]=bset;
      if(event.key.keysym.sym==SDLK_7)KEY[key_7]=bset;
      if(event.key.keysym.sym==SDLK_8)KEY[key_8]=bset;
      if(event.key.keysym.sym==SDLK_9)KEY[key_9]=bset;
      if(event.key.keysym.sym==SDLK_COLON)KEY[COLON]=bset;
      if(event.key.keysym.sym==SDLK_SEMICOLON)KEY[SEMICOLON]=bset;
      if(event.key.keysym.sym==SDLK_LESS)KEY[LESS]=bset;
      if(event.key.keysym.sym==SDLK_EQUALS)KEY[EQUALS]=bset;
      if(event.key.keysym.sym==SDLK_GREATER)KEY[GREATER]=bset;
      if(event.key.keysym.sym==SDLK_QUESTION)KEY[QUESTION]=bset;
      if(event.key.keysym.sym==SDLK_AT)KEY[AT]=bset;
      if(event.key.keysym.sym==SDLK_LEFTBRACKET)KEY[LEFTBRACKET]=bset;
      if(event.key.keysym.sym==SDLK_BACKSLASH)KEY[BACKSLASH]=bset;
      if(event.key.keysym.sym==SDLK_RIGHTBRACKET)KEY[RIGHTBRACKET]=bset;
      if(event.key.keysym.sym==SDLK_CARET)KEY[CARET]=bset;
      if(event.key.keysym.sym==SDLK_UNDERSCORE)KEY[UNDERSCORE]=bset;
      if(event.key.keysym.sym==SDLK_BACKQUOTE)KEY[BACKQUOTE]=bset;
      if(event.key.keysym.sym==SDLK_a)KEY[key_a]=bset;
      if(event.key.keysym.sym==SDLK_b)KEY[key_b]=bset;
      if(event.key.keysym.sym==SDLK_c)KEY[key_c]=bset;
      if(event.key.keysym.sym==SDLK_d)KEY[key_d]=bset;
      if(event.key.keysym.sym==SDLK_e)KEY[key_e]=bset;
      if(event.key.keysym.sym==SDLK_f)KEY[key_f]=bset;
      if(event.key.keysym.sym==SDLK_g)KEY[key_g]=bset;
      if(event.key.keysym.sym==SDLK_h)KEY[key_h]=bset;
      if(event.key.keysym.sym==SDLK_i)KEY[key_i]=bset;
      if(event.key.keysym.sym==SDLK_j)KEY[key_j]=bset;
      if(event.key.keysym.sym==SDLK_k)KEY[key_k]=bset;
      if(event.key.keysym.sym==SDLK_l)KEY[key_l]=bset;
      if(event.key.keysym.sym==SDLK_m)KEY[key_m]=bset;
      if(event.key.keysym.sym==SDLK_n)KEY[key_n]=bset;
      if(event.key.keysym.sym==SDLK_o)KEY[key_o]=bset;
      if(event.key.keysym.sym==SDLK_p)KEY[key_p]=bset;
      if(event.key.keysym.sym==SDLK_q)KEY[key_q]=bset;
      if(event.key.keysym.sym==SDLK_r)KEY[key_r]=bset;
      if(event.key.keysym.sym==SDLK_s)KEY[key_s]=bset;
      if(event.key.keysym.sym==SDLK_t)KEY[key_t_]=bset;
      if(event.key.keysym.sym==SDLK_u)KEY[key_u]=bset;
      if(event.key.keysym.sym==SDLK_v)KEY[key_v]=bset;
      if(event.key.keysym.sym==SDLK_w)KEY[key_w]=bset;
      if(event.key.keysym.sym==SDLK_x)KEY[key_x]=bset;
      if(event.key.keysym.sym==SDLK_y)KEY[key_y]=bset;
      if(event.key.keysym.sym==SDLK_z)KEY[key_z]=bset;
      if(event.key.keysym.sym==SDLK_DELETE)KEY[DEL]=bset;
      if(event.key.keysym.sym==SDLK_KP0)KEY[KP0]=bset;
      if(event.key.keysym.sym==SDLK_KP1)KEY[KP1]=bset;
      if(event.key.keysym.sym==SDLK_KP2)KEY[KP2]=bset;
      if(event.key.keysym.sym==SDLK_KP3)KEY[KP3]=bset;
      if(event.key.keysym.sym==SDLK_KP4)KEY[KP4]=bset;
      if(event.key.keysym.sym==SDLK_KP5)KEY[KP5]=bset;
      if(event.key.keysym.sym==SDLK_KP6)KEY[KP6]=bset;
      if(event.key.keysym.sym==SDLK_KP7)KEY[KP7]=bset;
      if(event.key.keysym.sym==SDLK_KP8)KEY[KP8]=bset;
      if(event.key.keysym.sym==SDLK_KP9)KEY[KP9]=bset;
      if(event.key.keysym.sym==SDLK_KP_PERIOD)KEY[KP_PERIOD]=bset;
      if(event.key.keysym.sym==SDLK_KP_DIVIDE)KEY[KP_DIVIDE]=bset;
      if(event.key.keysym.sym==SDLK_KP_MULTIPLY)KEY[KP_MULTIPLY]=bset;
      if(event.key.keysym.sym==SDLK_KP_MINUS)KEY[KP_MINUS]=bset;
      if(event.key.keysym.sym==SDLK_KP_PLUS)KEY[KP_PLUS]=bset;
      if(event.key.keysym.sym==SDLK_KP_ENTER)KEY[KP_ENTER]=bset;
      if(event.key.keysym.sym==SDLK_KP_EQUALS)KEY[KP_EQUALS]=bset;
      if(event.key.keysym.sym==SDLK_UP)KEY[UP]=bset;
      if(event.key.keysym.sym==SDLK_DOWN)KEY[DOWN]=bset;
      if(event.key.keysym.sym==SDLK_RIGHT)KEY[RIGHT]=bset;
      if(event.key.keysym.sym==SDLK_LEFT)KEY[LEFT]=bset;
      if(event.key.keysym.sym==SDLK_INSERT)KEY[INSERT]=bset;
      if(event.key.keysym.sym==SDLK_HOME)KEY[HOME]=bset;
      if(event.key.keysym.sym==SDLK_END)KEY[END]=bset;
      if(event.key.keysym.sym==SDLK_PAGEUP)KEY[PAGEUP]=bset;
      if(event.key.keysym.sym==SDLK_PAGEDOWN)KEY[PAGEDOWN]=bset;
      if(event.key.keysym.sym==SDLK_F1)KEY[F1]=bset;
      if(event.key.keysym.sym==SDLK_F2)KEY[F2]=bset;
      if(event.key.keysym.sym==SDLK_F3)KEY[F3]=bset;
      if(event.key.keysym.sym==SDLK_F4)KEY[F4]=bset;
      if(event.key.keysym.sym==SDLK_F5)KEY[F5]=bset;
      if(event.key.keysym.sym==SDLK_F6)KEY[F6]=bset;
      if(event.key.keysym.sym==SDLK_F7)KEY[F7]=bset;
      if(event.key.keysym.sym==SDLK_F8)KEY[F8]=bset;
      if(event.key.keysym.sym==SDLK_F9)KEY[F9]=bset;
      if(event.key.keysym.sym==SDLK_F10)KEY[F10]=bset;
      if(event.key.keysym.sym==SDLK_F11)KEY[F11]=bset;
      if(event.key.keysym.sym==SDLK_F12)KEY[F12]=bset;
      if(event.key.keysym.sym==SDLK_F13)KEY[F13]=bset;
      if(event.key.keysym.sym==SDLK_F14)KEY[F14]=bset;
      if(event.key.keysym.sym==SDLK_F15)KEY[F15]=bset;
      if(event.key.keysym.sym==SDLK_NUMLOCK)KEY[NUMLOCK]=bset;
      if(event.key.keysym.sym==SDLK_CAPSLOCK)KEY[CAPSLOCK]=bset;
      if(event.key.keysym.sym==SDLK_SCROLLOCK)KEY[SCROLLOCK]=bset;
      if(event.key.keysym.sym==SDLK_RSHIFT)KEY[RSHIFT]=bset;
      if(event.key.keysym.sym==SDLK_LSHIFT)KEY[LSHIFT]=bset;
      if(event.key.keysym.sym==SDLK_RCTRL)KEY[RCTRL]=bset;
      if(event.key.keysym.sym==SDLK_LCTRL)KEY[LCTRL]=bset;
      if(event.key.keysym.sym==SDLK_RALT)KEY[RALT]=bset;
      if(event.key.keysym.sym==SDLK_LALT)KEY[LALT]=bset; } } }