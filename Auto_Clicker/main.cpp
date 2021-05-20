/*
 * How I want to do the programing in the thing.
 * functions
 *      type(words,speed) : (keywords [delete, tab, delete, control, ctrl, shift, enter, \n, alt, F#])
 *      hold(letters,duration?) : (same keywords as above)
 *      release(letters) : (keywords)
 *      move(x,y,relitive?) : relitive means moving relitively to where it currently is
 *      click(buttion, amount) : buttion [left,right], amount [num, inf]
 *
 *      goto_line(linenum) : for making loops
 */

#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <thread>
#include <sstream>

using namespace std;
/*
 * ////////////////////Places where I got alot of help / code\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
 *
 * // input part \\
 * http://www.cplusplus.com/articles/EbqpX9L8/
 *
 * // Old input stuff \\
 * https://www.youtube.com/watch?v=6-vlLvBnIR0
 * https://www.geeksforgeeks.org/returning-multiple-values-from-a-function-using-tuple-and-pair-in-c/
 *
 *
 * // clicker part \\
 * https://forums.codeguru.com/showthread.php?377394-Windows-SDK-User-Interface-How-can-I-emulate-mouse-events-in-an-application
 *
 *
 * // thread part \\
 * http://www.cplusplus.com/reference/thread/thread/
 *
 *
 *
 * https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
 */


void GetCodeFile(string code);

//keysDown prototype
void keysDown();



//LeftClick prototype
void LeftClick();
//RightClick prototype
void RightClick();
//MouseMove prototype
void MouseMove(int, int);


//TypeChar prototype
void TypeChar(int);
//Type prototype
void Type(string);
//HoldChar prototype
void HoldChar(int);
//ReleaseChar prototype
void ReleaseChar(int);



//MouseThread prototype
void MouseThread();
//KeyThread prototype
void KeyThread();

// globals
string pressed = "";
bool leftSpam = false;
bool rightSpam = false;
bool working = true;


const string Caps = "QWERTYUIOPASDFGHJKLZXCVBNM"; // the alfabet is arbitrarily ordered. Change my mind. 65-90
const string Lower = "qwertyuioplkjhgfdsazxcvbnm";


const string Oddballs = ";=,-./[\\]'";
const string ShiftOddballs = ":+<_>|{|}\"";

const int OddballValues[] ={186,187,188,189,190,191,219,220,221,222};

const string ShiftNumbers = "!@#$%^&*()";
const int ShiftNumbersValues[] ={49,50,51,52,53,54,55,56,57,48};



// 13 enter VK_RETURN
// 8 delete VK_DELETE
// 32 space VK_SPACE
// 96 - 105 numpad numbers (numlock on)

// 37 left arrow VK_LEFT
// 38 up arrow VK_UP
// 39 right arrow VK_RIGHT
// 40 down arrow VK_DOWN

// 112-123 : F1-F12

/***************Main****************/

int main()
{


    KeyThread();


    //thread first (MouseThread);     // spawn new thread that calls MouseThread()
    //thread second (KeyThread);  // spawn new thread that calls KeyThread()

    // synchronize threads:
    //first.join();                // pauses until first finishes
    //second.join();               // pauses until second finishes


}

/***************Main****************/


void KeyThread() {
    //the while-loop to check the key state every 100 milliseconds
    while(working)
    {
        //string pressed = keysDown();
        keysDown();


        char chType[]="abcdefghijklmnopqrstuvwxyz"; // 65-90
        char inType[]="0123456789"; // 48-57
        string oddType[] = {"Lshift", "Rshift", "Lctrl", "Rctrl", "Lalt", "Ralt"}; // 160-165
        char symbolTypeP1[] = ";=,-./"; // 186-191
        char symbolTypeP2[] = {'[','\\',']','\''}; // 219-222

        // 65-90 A-Z
        // 48-57 0-9
        // 32 space
        // 13 enter/return
        // 27 esc
        // 16,160 Lshift
        // 16,161 Rshift
        // 17,162 Lctrl
        // 17,163 Rctrl
        // 18,164 Lalt
        // 18,165 Ralt
        //
        // 186 ;
        // 187 =
        // 188 ,
        // 189 -
        // 190 .
        // 191 /
        //
        // 219 [
        // 220 \\
        // 221 ]
        // 222 '
        //
        //
        // 186,187,188,189,190,191
        // 219,220,221,222

        ///*


        // for symbolTypeP1
        for (int val = 186; val < 192; val++) { // thease are the code id's that we need to replace to make it look nice
            while (pressed.find(to_string(val)) != string::npos) { // Find all of them, even though there only tends to be 1
                pressed.replace(pressed.find(to_string(val)), 3, string(1,symbolTypeP1[(val-186)]) ); // replace them
            }
        }

        // for symbolTypeP2
        for (int val = 219; val < 223; val++) { // thease are the code id's that we need to replace to make it look nice
            while (pressed.find(to_string(val)) != string::npos) { // Find all of them, even though there only tends to be 1
                pressed.replace(pressed.find(to_string(val)), 3, string(1,symbolTypeP2[(val-219)]) ); // replace them
            }
        }

        // for odd
        for (int val = 160; val < 166; val++) { // thease are the code id's that we need to replace to make it look nice
            while (pressed.find(to_string(val)) != string::npos) { // Find all of them, even though there only tends to be 1
                pressed.replace(pressed.find(to_string(val)), 3, oddType[(val-160)] ); // replace them
            }
        }

        // for odd
        for (int val = 16; val < 19; val++) { // thease are the code id's that we need to replace to make it look nice
            while (pressed.find(to_string(val)) != string::npos) { // Find all of them, even though there only tends to be 1
                pressed.erase(pressed.find(to_string(val)), 3); // replace them
            }
        }



        // for char
        for (int val = 65; val < 91; val++) { // thease are the code id's that we need to replace to make it look nice
            while (pressed.find(to_string(val)) != string::npos) { // Find all of them, even though there only tends to be 1
                pressed.replace(pressed.find(to_string(val)), 2, string(1,chType[(val-65)]) ); // replace them
            }
        }

        // for int
        for (int val = 48; val < 58; val++) { // thease are the code id's that we need to replace to make it look nice
            while (pressed.find(to_string(val)) != string::npos) { // Find all of them, even though there only tends to be 1
                pressed.replace(pressed.find(to_string(val)), 2, string(1,inType[(val-48)]) ); // replace them
            }
        }

        //*/

        if (pressed != "") { // so its not printing literaly nothing
            cout << "Keys down: " << pressed << endl;

            GetCodeFile(pressed); // tries to do same as stuff below.


            // shift + z + x
            if (pressed == "= - ") {
                Sleep(500);
                leftSpam = !leftSpam;
            }

            // Rshift + Rctrl
            if (pressed == "Rshift Rctrl ") {
                // Select all, paste
                Sleep(500);
                HoldChar(VK_CONTROL);
                TypeChar('a'); // ctrl a : select all
                TypeChar('v'); // ctrl v : paste
                ReleaseChar(VK_CONTROL);
                //Type("So this is just a way for me to type insanely fast for a realy quick coppy paste. lerl");
            }

            // left+right arrow
            if (pressed == "Lshift Lctrl ") {
                // down 2 home deleate space
                Sleep(500);
                //TypeChar('a');
                TypeChar(40); //down
                TypeChar(40); // down
                TypeChar(36); // home
                TypeChar(8); // delete
                TypeChar(32); //space
            }



            // f + Lshift
            //if (pressed == "f Lshift ") {
            //    Type("So this is just a way for me to type insanely fast for a realy quick coppy paste. lerl");
            //}


            // spams
            if (leftSpam)
                LeftClick();
            if (rightSpam)
                RightClick();



            if(pressed == "27 ") // escape
                working = false;
        }


       Sleep(50); // it needs this delay trust me. (in miliseconds)

    }
    //working = false;
}



// this will have to be for the gui, sorry. It is too slow when in its own thread for turning on/off
/*
void MouseThread() {
    while (working){
        if (leftSpam)
            cout << "ho" << endl;//LeftClick();

        Sleep(100); // it needs this delay trust me. (in miliseconds)
    }
}
*/



//keylist function
void keysDown() {
    // gives a string of all the keys currently down, as number string
    // https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes

    pressed = ""; // reset the string for the new info, this can overflow if I dont do this

    for (int ascii=3; ascii<254; ascii++) { // a listing of every posible key in "ascii"
        if(GetAsyncKeyState(ascii)) { // get if the key is currently down

            //char key = ascii; // change it to a char for printing and adding to string
            //cout << "Key pressed -> \" " << key << " \"ascii value = "<< ascii << endl; // print it

            pressed += to_string(ascii); // add it to the pressed list
            pressed += " "; // add a space to the pressed list. this is for clean reading
        }
    }
    //return (pressed);
}



// THE FOLOWING HAS BEEN BLAZINGLY STOLEN FROM https://forums.codeguru.com/showthread.php?377394-Windows-SDK-User-Interface-How-can-I-emulate-mouse-events-in-an-application
void LeftClick ( )
{
  INPUT    Input={0};
  // left down
  Input.type      = INPUT_MOUSE;
  Input.mi.dwFlags  = MOUSEEVENTF_LEFTDOWN;
  ::SendInput(1,&Input,sizeof(INPUT));

  // left up
  ::ZeroMemory(&Input,sizeof(INPUT));
  Input.type      = INPUT_MOUSE;
  Input.mi.dwFlags  = MOUSEEVENTF_LEFTUP;
  ::SendInput(1,&Input,sizeof(INPUT));
}

void RightClick ( )
{
  INPUT    Input={0};
  // right down
  Input.type      = INPUT_MOUSE;
  Input.mi.dwFlags  = MOUSEEVENTF_RIGHTDOWN;
  ::SendInput(1,&Input,sizeof(INPUT));

  // right up
  ::ZeroMemory(&Input,sizeof(INPUT));
  Input.type      = INPUT_MOUSE;
  Input.mi.dwFlags  = MOUSEEVENTF_RIGHTUP;
  ::SendInput(1,&Input,sizeof(INPUT));
}


void MouseMove (int x, int y )
{
  double fScreenWidth    = ::GetSystemMetrics( SM_CXSCREEN )-1;
  double fScreenHeight  = ::GetSystemMetrics( SM_CYSCREEN )-1;
  double fx = x*(65535.0f/fScreenWidth);
  double fy = y*(65535.0f/fScreenHeight);
  INPUT  Input={0};
  Input.type      = INPUT_MOUSE;
  Input.mi.dwFlags  = MOUSEEVENTF_MOVE|MOUSEEVENTF_ABSOLUTE;
  Input.mi.dx = fx;
  Input.mi.dy = fy;
  ::SendInput(1,&Input,sizeof(INPUT));
}

// THE ABOVE HAS BEEN BLAZINGLY STOLEN FROM https://forums.codeguru.com/showthread.php?377394-Windows-SDK-User-Interface-How-can-I-emulate-mouse-events-in-an-application





int CleanUp(int letter) {
    if (Lower.find(char(letter)) != string::npos){
        letter -= 32;
    } else if (Oddballs.find(char(letter)) != string::npos){
        letter = OddballValues[Oddballs.find(char(letter))];
    }
    return (letter);
}



void TypeChar(int key) {
    key = CleanUp(key);
    //cout << char(key) << endl;

    // Stolzen from https://batchloaf.wordpress.com/2012/04/17/simulating-a-keystroke-in-win32-c-or-c-using-sendinput/
    INPUT Input={0};

    // Set up a generic keyboard event.
    Input.type = INPUT_KEYBOARD;
    Input.ki.wScan = 0; // hardware scan code for key
    Input.ki.time = 0;
    Input.ki.dwExtraInfo = 0;

    // Press the key
    Input.ki.wVk = key; // virtual-key code for the key
    Input.ki.dwFlags = 0; // 0 for key press
    SendInput(1, &Input, sizeof(INPUT));

    // Release the key
    Input.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
    SendInput(1, &Input, sizeof(INPUT));
}


void HoldChar(int key) {
    // Stolzen from https://batchloaf.wordpress.com/2012/04/17/simulating-a-keystroke-in-win32-c-or-c-using-sendinput/
    INPUT Input={0};

    // Set up a generic keyboard event.
    Input.type = INPUT_KEYBOARD;
    Input.ki.wScan = 0; // hardware scan code for key
    Input.ki.time = 0;
    Input.ki.dwExtraInfo = 0;

    // Press the key
    Input.ki.wVk = key; // virtual-key code for the key
    Input.ki.dwFlags = 0; // 0 for key press
    SendInput(1, &Input, sizeof(INPUT));

}


void ReleaseChar(int key) {
    // Stolzen from https://batchloaf.wordpress.com/2012/04/17/simulating-a-keystroke-in-win32-c-or-c-using-sendinput/
    INPUT Input={0};

    // Set up a generic keyboard event.
    Input.type = INPUT_KEYBOARD;
    Input.ki.wScan = 0; // hardware scan code for key
    Input.ki.time = 0;
    Input.ki.dwExtraInfo = 0;

    // Press the key
    Input.ki.wVk = key; // virtual-key code for the key

    // Release the key
    Input.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
    SendInput(1, &Input, sizeof(INPUT));
}




void Type(string words) {

    bool Shift = false;
    bool Ctrl = false;

    for(int letter : words){
        Shift = false;
        Ctrl = false;
        letter = CleanUp(letter);


        // This is to get proper keys since the keyboard doesent match ascii
        if (char(letter) == ' '){ // if the letter is a space enter space
            letter = VK_SPACE;

        } else if (Caps.find(char(letter)) != string::npos){ // if its a caps char be shift
            Shift = true;

        } else if (ShiftOddballs.find(char(letter)) != string::npos){ // if the key is one of the shifted odballs
            Shift = true;
            letter = OddballValues[ShiftOddballs.find(char(letter))]; // again ascii problems

        } else if (ShiftNumbers.find(char(letter)) != string::npos){ // for the charicters that you get from shift hitting the number keys on the
            Shift = true;
            letter = ShiftNumbersValues[ShiftNumbers.find(char(letter))]; // get the number keys
        }

         // hold shift and use key
        if (Shift) {
            HoldChar(VK_SHIFT); // hold shift
            TypeChar(letter);
            ReleaseChar(VK_SHIFT); // release key

        //
        } else if (Ctrl) {
            HoldChar(VK_CONTROL); // hold ctrl
            TypeChar(letter);
            ReleaseChar(VK_CONTROL); // release ctrl

        // type normal keys, no shift/ctrl
        } else {
            TypeChar(letter);
        }
        cout << letter << " : " << char(letter) << endl;

    }

}







///*


void Out(string stuff) {
    cout << stuff << endl;
}

void Hype(string stuff) {
    stringstream data(stuff);
    int x = 0; // so dumb
    data >> x;  // extreem dumb

    cout <<"Much hype: " << x+3 << endl;
}


void FileRunner(string fileName) {
    fileName = "C:\\Users\\Quiltic\\Desktop\\Programs\\Major projects\\AutoClicker\\QT (C++)\\Auto_Clicker\\" + fileName;
    ifstream file(fileName);
    string line;

    while(getline(file, line)){
        int half = line.find_first_of(":!:");  // get seperator marker
        string first = line.substr(0,half);
        string second = line.substr(half+3, line.length());
        cout << "Running command: '" << first << "' with variables: '" << second << "'" << endl;

        // this is where the code goes to be exicuted, since c++ doesent have nice way of doing this to my knowledge.
        if (first == "Out")
            Out(second);
        if (first == "LeftClick")
            LeftClick();
        if (first == "RightClick")
            RightClick();
        if (first == "Type")
            Type(second);
    }
}

void GetCodeFile(string code) {
    ifstream file("C:\\Users\\Quiltic\\Desktop\\Programs\\Major projects\\AutoClicker\\QT (C++)\\Auto_Clicker\\KeyCodes.txt");
    string line;
    while(getline(file, line)){
        int half = line.find_first_of(":!:"); // get seperator marker
        string first = line.substr(0,half); // first half
        string second = line.substr(half+3, line.length()); // second half

        if (second[second.length()-1] != ' ') // I forget to add the space at the end alot so this just helps
            second += " ";

        if (code == second) {
            cout << "Running: " << first << " From code: '" << second << "'"<< endl;
            FileRunner(first);
        }
    }
}
//*/



//#include <iostream>
//#include <Windows.h>
//#include<conio.h>
//using namespace std;


/*
 * ////////////////////Places where I got alot of help / code\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
 *
 * // input part \\
 * http://www.cplusplus.com/articles/EbqpX9L8/
 *
 * // Old input stuff \\
 * https://www.youtube.com/watch?v=6-vlLvBnIR0
 * https://www.geeksforgeeks.org/returning-multiple-values-from-a-function-using-tuple-and-pair-in-c/
 *
 *
 * // clicker part \\
 * https://forums.codeguru.com/showthread.php?377394-Windows-SDK-User-Interface-How-can-I-emulate-mouse-events-in-an-application
 *
 *
 * // thread part \\
 * http://www.cplusplus.com/reference/thread/thread/
 *
 *
 *
 * https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
 */




/*




pair<char,int> get_key(){
    int asciiValue = getch();
    char key=asciiValue;
    return ( make_pair(key,asciiValue) );
}











int main()
{
    pair<char, int> keyData;

    cout << "press a key to check its ascii value\nPress ESC to exit\n" << endl;

    while(1)
    {
        if(GetAsyncKeyState('C') & 0x8000) // sCheck if high-order bit is set (1 << 15)
            cout << "Hello World!" << endl;



        keyData = get_key();

        if(keyData.first == 'a')
            LeftClick();


        if(keyData.second == 27)
            break;

        cout << "Key pressed -> \" " << keyData.first << " \"ascii value = "<< keyData.second << endl;
    }
    return 0;
}
*/
/*
int main()
{
    bool working = true;
    while (working) {
        if(GetKeyState('A') & 0x8000) { // sCheck if high-order bit is set (1 << 15)
            cout << "Hello World!" << endl;
            working = false;
        }
    }

    return 0;
}
*/
/*
// thread example
#include <iostream>       // std::cout
#include <thread>         // std::thread

void foo()
{
  // do stuff...
}

void bar(int x)
{
  // do stuff...
}

int main()
{
  std::thread first (foo);     // spawn new thread that calls foo()
  std::thread second (bar,0);  // spawn new thread that calls bar(0)

  std::cout << "main, foo and bar now execute concurrently...\n";

  // synchronize threads:
  first.join();                // pauses until first finishes
  second.join();               // pauses until second finishes

  std::cout << "foo and bar completed.\n";

  return 0;
}
*/
