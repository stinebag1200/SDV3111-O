#include <iostream>
#include <string>
#include <conio.h>
#include <iomanip>
#include <sstream>
using namespace std;

const int BOX_WIDTH = 80;   // Width of the box in characters
const int BIT_WIDTH = 32;   // 32 bits
const int CONSOLE_HEIGHT = 25; // You can change this to match your terminal

// --- Bitwise Operations ---
void TurnOn(int& bitfield, int bitIndex) { bitfield |= (1 << bitIndex); }
void TurnOff(int& bitfield, int bitIndex) { bitfield &= ~(1 << bitIndex); }
void Toggle(int& bitfield, int bitIndex) { bitfield ^= (1 << bitIndex); }
bool IsBitOn(int& bitfield, int bitIndex) { return (bitfield & (1 << bitIndex)) != 0; }
void Negate(int& bitfield) { bitfield = ~bitfield; }
void RightShift(int& bitfield) { bitfield >>= 1; }
void LeftShift(int& bitfield) { bitfield <<= 1; }

// --- String Formatting ---
string ToBinary(int value) {
    string binary = "";
    for (int i = 31; i >= 0; i--) binary += ((value >> i) & 1) ? '1' : '0';
    return binary;
}
string ToHex(int value) {
    stringstream ss;
    ss << uppercase << hex << (unsigned int)value;
    return ss.str();
}
string ToOctal(int value) {
    stringstream ss;
    ss << oct << (unsigned int)value;
    return ss.str();
}

// --- UI Helpers ---
void ClearScreen() { system("cls"); }

void PrintBoxLine() {
    cout << '+';
    for (int i = 0; i < BOX_WIDTH - 2; ++i) cout << '-';
    cout << "+\n";
}
void PrintBoxContent(const string& content, bool center = true) {
    int pad = BOX_WIDTH - 2 - (int)content.length();
    int leftPad = center ? pad / 2 : 0;
    int rightPad = center ? (pad - leftPad) : pad;
    cout << '|';
    for (int i = 0; i < leftPad; ++i) cout << ' ';
    cout << content;
    for (int i = 0; i < rightPad; ++i) cout << ' ';
    cout << "|\n";
}
void PrintBoxEmpty(int lines = 1) {
    for (int i = 0; i < lines; ++i) PrintBoxContent("", false);
}
void PrintVerticalPadding(int boxHeight) {
    int pad = (CONSOLE_HEIGHT - boxHeight) / 2;
    if (pad < 0) pad = 0;
    for (int i = 0; i < pad; ++i) cout << endl;
}

void DisplayMainMenu() {
    ClearScreen();
    int boxHeight = 12; // number of box lines
    PrintVerticalPadding(boxHeight);
    PrintBoxLine();
    PrintBoxEmpty(2);
    PrintBoxContent("== Systems Programming - Bit Manipulation Lab ==");
    PrintBoxEmpty(2);
    PrintBoxContent("1. Binary");
    PrintBoxEmpty();
    PrintBoxContent("2. Hexadecimal");
    PrintBoxEmpty();
    PrintBoxContent("3. Octal");
    PrintBoxEmpty(2);
    PrintBoxContent("Escape: Exit");
    PrintBoxEmpty(2);
    PrintBoxLine();
}

void DisplayBitfield(int bitfield, int selectedBit) {
    string binary = ToBinary(bitfield);
    string bits = "Bits: " + binary;
    PrintBoxContent(bits, false);

    string indicator = "      ";
    for (int i = 0; i < BIT_WIDTH; ++i)
        indicator += (i == (BIT_WIDTH - 1 - selectedBit)) ? '^' : ' ';
    PrintBoxContent(indicator, false);
}

void DisplayBitMenu(const string& mode, int& bitfield, int& selectedBit) {
    ClearScreen();
    int boxHeight = 16; // adjust if you add/remove lines
    PrintVerticalPadding(boxHeight);
    PrintBoxLine();

    string fieldLabel, fieldValue;
    if (mode == "Binary") {
        fieldLabel = "Bitfield Value:";
        fieldValue = to_string(bitfield);
    }
    else if (mode == "Hex") {
        fieldLabel = "Hex Field Value:";
        fieldValue = ToHex(bitfield);
    }
    else if (mode == "Octal") {
        fieldLabel = "Oct Field Value:";
        fieldValue = ToOctal(bitfield);
    }

    PrintBoxEmpty();
    PrintBoxContent(fieldLabel, false);
    PrintBoxContent(fieldValue, false);
    PrintBoxEmpty();
    PrintBoxContent("== Controls ==");
    PrintBoxEmpty();
    PrintBoxContent("I: Turn On              O: Turn Off", false);
    PrintBoxContent("Space: Toggle Bit       N: Negate", false);
    PrintBoxContent("Q: Shift Left           E: Shift Right", false);
    PrintBoxContent(">: Move Left            <: Move Right", false);
    PrintBoxContent("Escape: Main Menu", false);
    PrintBoxEmpty();
    string bitStatus = "Bit Status: " + string(IsBitOn(bitfield, selectedBit) ? "On" : "Off");
    PrintBoxContent(bitStatus, false);
    PrintBoxEmpty();
    DisplayBitfield(bitfield, selectedBit);
    PrintBoxEmpty();
    PrintBoxLine();
}

int main() {
    int bitfield = 0;   // Start with zero in all views!
    int selectedBit = 0;
    char input;
    int currentMenu = 0; // 0 = main, 1 = binary, 2 = hex, 3 = octal

    while (true) {
        switch (currentMenu) {
        case 0: // Main Menu
            DisplayMainMenu();
            input = _getch();
            switch (input) {
            case '1': currentMenu = 1; break;
            case '2': currentMenu = 2; break;
            case '3': currentMenu = 3; break;
            case 27: return 0;
            }
            break;
        case 1: // Binary Menu
            DisplayBitMenu("Binary", bitfield, selectedBit);
            input = _getch();
            switch (input) {
            case 'i': case 'I': TurnOn(bitfield, selectedBit); break;
            case 'o': case 'O': TurnOff(bitfield, selectedBit); break;
            case ' ':           Toggle(bitfield, selectedBit); break;
            case 'n': case 'N': Negate(bitfield); break;
            case 'q': case 'Q': LeftShift(bitfield); break;
            case 'e': case 'E': RightShift(bitfield); break;
            case '>': case '.': if (selectedBit > 0) selectedBit--; break;
            case '<': case ',': if (selectedBit < 31) selectedBit++; break;
            case 27:            currentMenu = 0; break;
            }
            break;
        case 2: // Hex Menu
            DisplayBitMenu("Hex", bitfield, selectedBit);
            input = _getch();
            switch (input) {
            case 'i': case 'I': TurnOn(bitfield, selectedBit); break;
            case 'o': case 'O': TurnOff(bitfield, selectedBit); break;
            case ' ':           Toggle(bitfield, selectedBit); break;
            case 'n': case 'N': Negate(bitfield); break;
            case 'q': case 'Q': LeftShift(bitfield); break;
            case 'e': case 'E': RightShift(bitfield); break;
            case '>': case '.': if (selectedBit > 0) selectedBit--; break;
            case '<': case ',': if (selectedBit < 31) selectedBit++; break;
            case 27:            currentMenu = 0; break;
            }
            break;
        case 3: // Octal Menu
            DisplayBitMenu("Octal", bitfield, selectedBit);
            input = _getch();
            switch (input) {
            case 'i': case 'I': TurnOn(bitfield, selectedBit); break;
            case 'o': case 'O': TurnOff(bitfield, selectedBit); break;
            case ' ':           Toggle(bitfield, selectedBit); break;
            case 'n': case 'N': Negate(bitfield); break;
            case 'q': case 'Q': LeftShift(bitfield); break;
            case 'e': case 'E': RightShift(bitfield); break;
            case '>': case '.': if (selectedBit > 0) selectedBit--; break;
            case '<': case ',': if (selectedBit < 31) selectedBit++; break;
            case 27:            currentMenu = 0; break;
            }
            break;
        }
    }
    return 0;
}
