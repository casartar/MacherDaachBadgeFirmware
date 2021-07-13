// Quadrat / Split bewegt sich von links nach rechts und wieder von rechts nach links
// Man kann mit Buttons zwischen Quadrat und Split wechseln
// Man kann mit Buttons pausieren und die Pause wieder weg machen

void output_init_quadrat() {
  output_quadrat(true);
}

void output_quadrat() {
  output_quadrat(false);
}
// Es wird ein Quadrat gemalt (ledOn = 1) oder ein Quadrat entfernt (ledOn = 0)
void male_quadrat(uint8_t pos_x, uint8_t pos_y, bool ledOn, uint8_t groesse) {

  for (uint8_t i = 0; i < groesse; i++) // x-Reihe
  {
    for (uint8_t k = 0; k < groesse; k++) // y-Spalte
    {
      matrixSetPixel(i + pos_x, k + pos_y, ledOn); // Pixel an/aus machen bei bestimmter Position
    }
  }
}
// Es wird ein Split gemalt(ledOn = 1) oder ein Split entfernt(ledOn = 0)
void male_split(uint8_t pos_x, uint8_t pos_y, bool ledOn, uint8_t ygroesse, uint8_t xgroesse) {

  for (uint8_t m = 0; m < xgroesse; m++) // x-Reihe
  {
    for (uint8_t n = 0; n < ygroesse; n = n + 2) // y-Spalte
    {
      matrixSetPixel(m + pos_x, n + pos_y, ledOn); // Pixel an/aus machen bei bestimmter Position
    }
  }
}
// Es gibt ein Richtungswechsel wenn einer benoetigt wird(an den Raendern)
uint8_t linksrechts(uint8_t alterichtung, uint8_t pos_row) {
  // Wenn die x-Reihe der LEDs vorbei ist
  // Wenn das Objekt ganz rechts ist, bewegt es sich wieder nach links
  if (pos_row == 4)
  {
    return -1;
  }
  // Wenn das Objekt ganz links ist, bewegt es sich wieder nach rechts
  else if (pos_row == 0) {
    return +1;
  }
  // Wenn das Objekt nicht ganz links oder ganz rechts ist, behaelt es die Richtung in die es sich vorher bewegt hat
  else {
    return alterichtung;
  }
}
// Die LEDs werden an oder aus geschaltet
bool LEDanaus(bool ledOn) {
  // Wenn die LEDs an waren, werden die LEDs ausgeschaltet
  if (ledOn == true)
  {
    return false;
  }
  // Wenn die LEDs aus waren, werden die LEDs angeschaltet
  else if (ledOn == false)
  {
    return true;
  }
}

void output_quadrat(bool init) {
  static uint8_t quadrat_groesse; // groesse vom Quadrat( 4 = 4x4 Quadrat)
  static uint8_t quadrat_pos_row; // xpos vom Quadrat
  static uint8_t quadrat_pos_colum; // ypos vom Quadrat
  static uint8_t xsplit_groesse; // groesse vom Split in x-Richtung ( 4 = 4 LEDs pro "Reihe")
  static uint8_t ysplit_groesse; // groesse vom Split in y-Richtung ( 8 = 4 "Reihen")
  static uint8_t split_pos_row;  // xpos vom Split
  static uint8_t split_pos_colum;  // xpos vom Split
  static int8_t bewegungsrichtung; // +1 = rechts / -1 = links
  static bool ledOn; // 0 = LED aus / 1 = LED an
  static bool split; // false = kein split / true = split
  static bool pause; // false = keine pause / true = pause

  if (init) {
    quadrat_pos_row = 0;
    quadrat_pos_colum = 2;
    quadrat_groesse = 4;
    split_pos_row = 0;
    split_pos_colum = 0;
    ysplit_groesse = 8;
    xsplit_groesse = 4;
    ledOn = true;
    split = false;
    pause = false;
    bewegungsrichtung = -1;
  }

  // Der Button 2 befindet sich rechts, Der Button 1 befindet sich links, wenn der rechte Button gedrueckt wird, erscheint ein Split / wenn der linke Button gedrueckt wird erscheint ein Quadrat
  if ((button_1_state == BUTTON_HELD) && (button_2_state == BUTTON_INACTIVE))
  {
    split = false;
    pause = false;
  }
  else if ((button_2_state == BUTTON_HELD) && (button_1_state == BUTTON_INACTIVE))
  {
    split = true;
    pause = false;
  }

  // Es gibt eine Pause wenn beide Buttons gleichzeitig gedrueckt wurden, um Pause aufhoeren zu lassen, muss man den linken oder rechten Button druecken
  if ((button_2_state == BUTTON_PRESSED) && (button_1_state == BUTTON_PRESSED))
  {
    pause = true;
  }

  // Split

  if (countdown == 0 && split == true && pause == false)
  {

    ledOn = LEDanaus(ledOn);

    // Split entfernen(ledOn = 0)
    male_split(split_pos_row, split_pos_colum, ledOn, ysplit_groesse, xsplit_groesse);

    // Quadrat entfernen(ledOn = 0)
    male_quadrat(quadrat_pos_row, quadrat_pos_colum, ledOn, quadrat_groesse);

    bewegungsrichtung = linksrechts(bewegungsrichtung, split_pos_row);

    // Die Bewegungsrichtung wird geaendert oder bleibt / links -> rechts, rechts -> links
    split_pos_row += bewegungsrichtung;

    ledOn = LEDanaus(ledOn);

    // Split malen(ledOn = 1)
    male_split(split_pos_row, split_pos_colum, ledOn, ysplit_groesse, xsplit_groesse);

    countdown = TIME_1_S; //der countdown wird jedesmal von 1 auf 0 gesetzt, er macht das dass Objekt sich jede Sekunde weiter bewegt, Zeit umstellbar
  }

  // Quadrat

  if (countdown == 0 && split == false && pause == false)
  {

    ledOn = LEDanaus(ledOn);

    // Split entfernen(ledOn = 0)
    male_split(split_pos_row, split_pos_colum, ledOn, ysplit_groesse, xsplit_groesse);

    // Quadrat entfernen(ledOn = 0)
    male_quadrat(quadrat_pos_row, quadrat_pos_colum, ledOn, quadrat_groesse);

    bewegungsrichtung = linksrechts(bewegungsrichtung, quadrat_pos_row);

    // Die Bewegungsrichtung wird geaendert oder bleibt / links -> rechts, rechts -> links
    quadrat_pos_row += bewegungsrichtung;

    ledOn = LEDanaus(ledOn);

    // Quadrat malen(ledOn = 1)
    male_quadrat(quadrat_pos_row, quadrat_pos_colum, ledOn, quadrat_groesse);

    // Der countdown wird immer wieder von 0 auf 1 gesetzt und dann wieder von 1 auf 0 gesetzt. Das macht das dass Objekt sich jede 1 Sekunde weiter bewegt, die Zeit ist umstellbar
    countdown = TIME_1_S; 

  }
}
