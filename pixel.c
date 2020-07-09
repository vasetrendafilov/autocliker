#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main(int argc, char const *argv[]) {
    POINT _cursor;
    FARPROC pGetPixel;
    HINSTANCE _hGDI = LoadLibrary("gdi32.dll");
    if(_hGDI)
    {
        pGetPixel = GetProcAddress(_hGDI, "GetPixel");
        HDC _hdc = GetDC(NULL);
        if(_hdc){
          if(argc == 2){
            GetCursorPos(&_cursor);
            COLORREF _color = (*pGetPixel) (_hdc, _cursor.x, _cursor.y);
            if(_color == atoi(argv[1])) return 1;
            return 0;
          }
          printf("[y]Get color [x] Close program\n");
          while(1){
            Sleep(250);
            if( GetAsyncKeyState( 'X' ) & 0x8000 ) break;
            GetCursorPos(&_cursor);
            COLORREF _color = (*pGetPixel) (_hdc, _cursor.x, _cursor.y);
            if( GetAsyncKeyState( 'Y' ) & 0x8000 )   printf("%d \n",_color);
          }
        }
        FreeLibrary(_hGDI);
    }
  return 0;

}
