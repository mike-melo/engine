#include <Windows.h>
#include <WinBase.h>
#include <WinDef.h>
#include <WinNT.h>
#include <Wincon.h>
#include <io.h>
#include <stdio.h>
#include <fcntl.h>

void initConsole() {
   int hCrt;
   FILE *hf;

   AllocConsole();
   hCrt = _open_osfhandle(
             (long) GetStdHandle(STD_OUTPUT_HANDLE),
             _O_TEXT
          );
   hf = _fdopen( hCrt, "w" );
   *stdout = *hf;
   setvbuf( stdout, NULL, _IONBF, 0 );
}
