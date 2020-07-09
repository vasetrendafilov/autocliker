#include <iostream>
#include <windows.h>
#include <WinUser.h>
#include <fstream>
#include <vector>
#include <string>

using namespace std;
//Typing prom
HKL kbl = GetKeyboardLayout(0);
INPUT ip;

void typeInput(char c){

  if(c == '_' || c=='%'){
    Sleep(10);
    ip.ki.wVk = (c == '^') ? VK_SPACE : VK_RETURN;
    ip.ki.wScan = MapVirtualKeyA(ip.ki.wVk, MAPVK_VK_TO_VSC);
    SendInput(1, &ip, sizeof(INPUT));
  }else{
    ip.type = INPUT_KEYBOARD;
    ip.ki.time = 0;
    ip.ki.dwFlags = KEYEVENTF_UNICODE;
    if ((int)c<65 && (int)c>90){
      ip.ki.wScan = 0;
      ip.ki.wVk = VkKeyScanEx( c, kbl );
    }else{
      ip.ki.wScan = c;
      ip.ki.wVk = 0;
    }
    ip.ki.dwExtraInfo = 0;
    SendInput(1, &ip, sizeof(INPUT));
  }
}
void mouseTrack(){
  POINT mouse;
  while(1){
    if( GetAsyncKeyState( 'X' ) & 0x8000 ) break;
    if( GetAsyncKeyState('Y') & 0x8000 ){
      GetCursorPos(&mouse);
      cout << mouse.x <<" / "<< mouse.y << endl;
    }
    Sleep(200);
  }
}
int isPixel(string pixel){
  const string c = "pixel.exe " + pixel;
  return pixel != "0" ? system(c.c_str()) : 0;
}

int main(){
  //proms
  int choice,xy[2000],xyCount=0,xyPos=0;//coordinates
  int sleep[1000],sleepCount=0,pixelCount=0;//sleep and pixel  prom
  int step[1000],stepCount=0,pos=0,textCount=0,textPos=0;//step and strings
  string text[10000],pixel[1000];

  //Citanje i zacuvuvanje na datotekite
  ifstream xyDoc("coordinates.txt",ios::in);
  ifstream stepsDoc("steps.txt",ios::in);
  ifstream sleepDoc("sleep.txt",ios::in);
  ifstream pixelDoc("pixel.txt",ios::in);
  ifstream stringsDoc("strings.txt",ios::in);
  if(xyDoc.is_open() && stepsDoc.is_open() && stringsDoc.is_open()){
    int temp;
    while (xyDoc >> temp) xy[xyCount++] = temp;
    xyDoc.close();
    while (stepsDoc >> temp) step[stepCount++] = temp;
    stepsDoc.close();
    while (sleepDoc >> temp) sleep[sleepCount++] = temp;
    sleepDoc.close();
    string stemp;
    while (stringsDoc >> stemp) text[textCount++] = stemp;
    stringsDoc.close();
    while (pixelDoc >> stemp) pixel[pixelCount++] = stemp;
    pixelDoc.close();
    if(stepCount != sleepCount && stepCount != pixelCount){
      cout<<"Imas greska vo fajlovite pauzata , step i pixel ne se sixroni"<<endl;
      cin.ignore();
      cin.ignore();
      return 0;
    }
  }else{
    cout << "Text files not found!";
    cin.ignore();
    cin.ignore();
    return 0;
  }//end citanje doc
  cout << "1) Track mouse coordinates \n2) Run autoclicker/spammer"<<endl;
  cin >> choice;
  if (choice == 1){
    system("cls");
    cout << "Type [x] to stop the tracking! Press [y] to get coordinates!"<<endl;
    cout << "[ x  /  y ]"<<endl;
    mouseTrack();
  }else{
    cout << "starting in 3..." << endl;
    Sleep(1000);
    cout << "starting in 2..." << endl;
    Sleep(1000);
    cout << "starting in 1..." << endl;
    Sleep(1000);
    while (textPos < textCount) {
      while (pos < stepCount){
        Sleep(sleep[pos]);
        if(step[pos] == 3){
          for(int i = 0; i < text[textPos].size(); ++i) typeInput(text[textPos][i]);
          textPos++;
        }else if(step[pos] == 4){
          SetCursorPos(xy[xyPos],xy[xyPos+1]);
          mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
          xyPos+=2; Sleep(100);
          SetCursorPos(xy[xyPos] ,xy[xyPos+1]);
          mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
          xyPos+=2;
        }else{
          SetCursorPos(xy[xyPos],xy[xyPos+1]);
          if(isPixel(pixel[pos])){
            cout<<"Pogodi"<<endl;
            Sleep(1000);
            continue;
          }
          mouse_event( step[pos] == 1 ? MOUSEEVENTF_LEFTDOWN : MOUSEEVENTF_RIGHTDOWN , 0, 0, 0, 0);
          mouse_event( step[pos] == 1 ? MOUSEEVENTF_LEFTUP : MOUSEEVENTF_RIGHTUP , 0, 0, 0, 0);
          xyPos+=2;
        }
        pos++;
      }
      pos=0;
      xyPos=0;
    }
  system("cls");
  cout<<"Pominati se site stringovi dodaj odnovo novi!"<<endl;
  }
  cin.ignore();
  cin.ignore();
  return 0;
}
