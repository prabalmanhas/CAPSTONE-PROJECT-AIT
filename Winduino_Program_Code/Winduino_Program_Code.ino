// CAPSTONE PROJECT - PRABAL AND TEAM - WINDUINO - DITCH THE LOGIN HASSLE, EMBRACE THE TAP
uint8_t buf[8] = { 0 };
#include <SPI.h>
#include <MFRC522.h> // HERE WE IMPORTED TEH MFRC522 RFID LIBRARY FOR FETCHING UNIQUE RFID
#define SS_PIN 10
#define RST_PIN 9
int gled = 7; // optional
int rled = 4;// optional
MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance.
String card_ID=""; // 
String password="" ; // MY WINDOWS LOGIN PIN
String rfid=""; // THE UNIQUE ID OF RFID TAG WHICH WILL BE MAPPED TO OUR WINDOWS LAPTOP FOR LOGIN AUTOMATION
void setup() {
  Serial.begin(9600); // INTIALIZING THE SERIAL COMMUNICATION WITH OUR PC
  SPI.begin();  // INIT SPI BUS
  mfrc522.PCD_Init(); // INIT MFRC522
  pinMode(gled,OUTPUT);
  pinMode(rled,OUTPUT);
}
void loop() {
  // SCANS THE NEARBY RFID TAGS OR CARDS
   if ( ! mfrc522.PICC_IsNewCardPresent()) {
  return;
 }
 if ( ! mfrc522.PICC_ReadCardSerial()) {
  return;//IF CARD CONTAINS THE UID, IT RETURN 1
 }
 for (byte i = 0; i < mfrc522.uid.size; i++) {
   card_ID += mfrc522.uid.uidByte[i];
 }
 // AUTOMATING THE KEYSTRIKES PROCEDURE WITHOUT PHYSICAL INTERCATION
       if(card_ID==rfid){digitalWrite(gled,HIGH); // IF CARD ID IS MATCHED WITH RFID TAG, GREEN SIGNAL INDICATOR IS TURNED ON 
      typeLiteralString(password);
      pressKey("enter"); releaseKey("enter"); // PRESSES THE ENTER KEY 
     digitalWrite(gled,LOW); delay(200);digitalWrite(gled,HIGH); delay(200);digitalWrite(gled,LOW);
      }
      if (card_ID != rfid) {
        digitalWrite(rled, HIGH);
        delay(200);
        digitalWrite(rled, LOW); 
        delay(200);
        digitalWrite(rled, HIGH); 
        delay(200);
        digitalWrite(rled, LOW);  
        } else {
    goto cont;
}
  // RED SIGNAL IS WRONG RFID TAG
delay(1000);
cont:
delay(1000);
card_ID="";
}
boolean isModifier(int keycode) {
    boolean result = false;
    if (keycode >= 224 && keycode <= 231) {
        result = true;
    }
    return result;
}

void pressModifier(String keyname) {
    pressModifier(getKeycode(keyname));
}
void pressModifier(int keycode) {
    int modifiermask = 0;
    if (isModifier(keycode)) {
        modifiermask = getModifierMask(keycode);
        buf[0] = buf[0] | modifiermask;
        Serial.write(buf, 8);
    }
}

void releaseModifier(String keyname) {
    releaseModifier(getKeycode(keyname));
}
void releaseModifier(int keycode) {
    int modifiermask = 0;
    if (isModifier(keycode)) {
        modifiermask = getModifierMask(keycode);
        buf[0] = buf[0] & (~modifiermask);
        Serial.write(buf, 8);
    }
}
void releaseAllModifiers() {
    buf[0] = B00000000;
    Serial.write(buf, 8);
}

void pressKey(String keyname) {
    pressKey(getKeycode(keyname));
}
void pressKey(int keycode) {
    buf[2] = keycode;
    Serial.write(buf, 8);
}

void releaseKey(String keyname) {
    releaseKey(getKeycode(keyname));
}
void releaseKey(int keycode) {
// FIND THE KEYCODE
    int i=0;
    for (i=2; i<8; i++) {
        if (buf[i] == keycode) {
            buf[i] = 0;
        }
    }
    Serial.write(buf, 8); // SENDS THE KEY REPORT
}
void releaseAllKeys() {
    int i=0;
    for (i=2; i<8; i++) {
        buf[i] = 0;
    }
    Serial.write(buf, 8); // SENDS THE KEY REPORT
}

void pressSequenceOfKeys(const char * keySequence[], int numberOfKeys) {
    int i = 0;
    for (i=0; i<numberOfKeys; i++) {
        pressKey(keySequence[i]);
        releaseKey(keySequence[i]);
    }
}

void typeLiteralString(String string) {
    char charArray[string.length()+1];
    string.toCharArray(charArray, string.length()+1);
    typeLiteralString(charArray, string.length());
}
void typeLiteralString(char string[], int stringLength) {
    releaseAllKeys();
    releaseAllModifiers();

    boolean charNeedsShift = false;
    boolean shiftIsPressed = false;

    int i=0;
    for (i=0; i<stringLength; i++) {
        charNeedsShift = characterNeedsShift(string[i]);
        if (charNeedsShift && !shiftIsPressed) {
            pressModifier("left_shift");
            shiftIsPressed = true;
        }
        else if (!charNeedsShift && shiftIsPressed) {
            releaseModifier("left_shift");
            shiftIsPressed = false;
        }
        pressKey(String(string[i]));
        releaseKey(String(string[i]));
    }

    releaseAllModifiers();
}

boolean characterNeedsShift(char character) {
    int needsModifier = false;
    if (
        (character >= 33 && character <= 38)
        || (character >= 40 && character <= 43)
        || (character == 58)
        || (character == 60)
        || (character >= 62 && character <= 90)
        || (character >= 94 && character <= 95)
        || (character >= 123 && character <= 126)
    ) {
        needsModifier = true;
    }
    return needsModifier;
}

int getKeycode(String keyname) {
    String key = String(keyname);
    key.toLowerCase();

    int keycode = 0; // 0 MEANS NO KEY IS PRESSED
    if      (key == "a") { keycode =  4; }
    else if (key == "b") { keycode =  5; }
    else if (key == "c") { keycode =  6; }
    else if (key == "d") { keycode =  7; }
    else if (key == "e") { keycode =  8; }
    else if (key == "f") { keycode =  9; }
    else if (key == "g") { keycode = 10; }
    else if (key == "h") { keycode = 11; }
    else if (key == "i") { keycode = 12; }
    else if (key == "j") { keycode = 13; }
    else if (key == "k") { keycode = 14; }
    else if (key == "l") { keycode = 15; }
    else if (key == "m") { keycode = 16; }
    else if (key == "n") { keycode = 17; }
    else if (key == "o") { keycode = 18; }
    else if (key == "p") { keycode = 19; }
    else if (key == "q") { keycode = 20; }
    else if (key == "r") { keycode = 21; }
    else if (key == "s") { keycode = 22; }
    else if (key == "t") { keycode = 23; }
    else if (key == "u") { keycode = 24; }
    else if (key == "v") { keycode = 25; }
    else if (key == "w") { keycode = 26; }
    else if (key == "x") { keycode = 27; }
    else if (key == "y") { keycode = 28; }
    else if (key == "z") { keycode = 29; }

    else if (key == "1" || key == "!") { keycode = 30; }
    else if (key == "2" || key == "@") { keycode = 31; }
    else if (key == "3" || key == "#") { keycode = 32; }
    else if (key == "4" || key == "$") { keycode = 33; }
    else if (key == "5" || key == "%") { keycode = 34; }
    else if (key == "6" || key == "^") { keycode = 35; }
    else if (key == "7" || key == "&") { keycode = 36; }
    else if (key == "8" || key == "*") { keycode = 37; }
    else if (key == "9" || key == "(") { keycode = 38; }
    else if (key == "0" || key == ")") { keycode = 39; }

    else if (key == "enter" || key == "return")     { keycode = 40; }
    else if (key == "escape" || key == "")    { keycode = 41; }
    else if (key == "backspace" || key == "") { keycode = 42; }
    else if (key == "tab" || key == "  ")      { keycode = 43; }
    else if (key == "space" || key == " ")      { keycode = 44; }

    else if (key == "-" || key == "_")  { keycode = 45; }
    else if (key == "=" || key == "+")  { keycode = 46; }
    else if (key == "[" || key == "{")  { keycode = 47; }
    else if (key == "]" || key == "}")  { keycode = 48; }
    else if (key == "\\" || key == "|") { keycode = 49; }
    else if (key == ";" || key == ":")  { keycode = 51; }
    else if (key == "'" || key == "\"") { keycode = 52; }
    else if (key == "`" || key == "~")  { keycode = 53; }
    else if (key == "," || key == "<")  { keycode = 54; }
    else if (key == "." || key == ">")  { keycode = 55; }
    else if (key == "/" || key == "?")  { keycode = 56; }
    else if (key == "capslock")         { keycode = 58; }

    else if (key == "f1")      { keycode = 59; }
    else if (key == "f2")      { keycode = 60; }
    else if (key == "f3")      { keycode = 61; }
    else if (key == "f4")      { keycode = 62; }
    else if (key == "f5")      { keycode = 63; }
    else if (key == "f6")      { keycode = 64; }
    else if (key == "f7")      { keycode = 65; }
    else if (key == "f8")      { keycode = 66; }
    else if (key == "f9")      { keycode = 67; }
    else if (key == "f10")     { keycode = 68; }
    else if (key == "f11")     { keycode = 69; }
    else if (key == "f12")     { keycode = 70; }

    else if (key == "print_screen")    { keycode = 70; }
    else if (key == "scroll_lock")     { keycode = 71; }
    else if (key == "pause")           { keycode = 72; }
    else if (key == "insert")          { keycode = 73; }
    else if (key == "home")            { keycode = 74; }
    else if (key == "page_up")         { keycode = 75; }
    else if (key == "delete")          { keycode = 76; }
    else if (key == "end")             { keycode = 77; }
    else if (key == "page_down")       { keycode = 78; }

    else if (key == "right_arrow")     { keycode = 79; }
    else if (key == "left_arrow")      { keycode = 80; }
    else if (key == "down_arrow")      { keycode = 81; }
    else if (key == "up_arrow")        { keycode = 82; }

    else if (key == "numlock" || key == "clear")   { keycode = 83; }
    else if (key == "left_control")  { keycode = 224; }
    else if (key == "left_shift")    { keycode = 225; }
    else if (key == "left_alt")      { keycode = 226; }
    else if (key == "left_gui")      { keycode = 227; }

    else if (key == "right_control") { keycode = 228; }
    else if (key == "right_shift")   { keycode = 229; }
    else if (key == "right_alt")     { keycode = 230; }
    else if (key == "right_gui")     { keycode = 231; }

    return keycode;
}

int getModifierMask(String keyname) {
    return getModifierMask(getKeycode(keyname));
}
int getModifierMask(int keycode) {
    int modifiermask = 0;
    if      (keycode == 224) { modifiermask = B00000001; } // left ctrl
    else if (keycode == 225) { modifiermask = B00000010; } // left shift
    else if (keycode == 226) { modifiermask = B00000100; } // left alt
    else if (keycode == 227) { modifiermask = B00001000; } // left gui
    else if (keycode == 228) { modifiermask = B00010000; } // right ctrl
    else if (keycode == 229) { modifiermask = B00100000; } // right shift
    else if (keycode == 230) { modifiermask = B01000000; } // right alt
    else if (keycode == 231) { modifiermask = B10000000; } // right gui

    return modifiermask;
}
    
