// Shows sing characters of passed string one after the other
void outputString(char * text){
  char * t;
  int offsetASCII = 0;
  int xOffset=0;
  int yOffset=0;
  
  for (t = text; *t != '\0'; t++){
    displayCharacter(ASCII[(int)*t]);
    delay(500);
  }
}
