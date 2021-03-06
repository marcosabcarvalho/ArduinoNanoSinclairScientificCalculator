//tedious but fast, must lines compile to 1 instruction.
//this whole file compiles to less than 1KB of code

void allSegmentOutput() {
  SegmentA.output();
  SegmentB.output();
  SegmentC.output();
  SegmentD.output();
  SegmentE.output();
  SegmentF.output();
  SegmentG.output();
  SegmentDP.output();
}

void allSegmentOff() {
  SegmentA.high();
  SegmentB.high();
  SegmentC.high();
  SegmentD.high();
  SegmentE.high();
  SegmentF.high();
  SegmentG.high();
  SegmentDP.high();
}

void allSegmentInput() {
  SegmentA.input();
  SegmentB.input();
  SegmentC.input();
  SegmentD.input();
  SegmentE.input();
  SegmentF.input();
  SegmentG.input();
  SegmentDP.input();

  SegmentA.high();
  SegmentB.high();
  SegmentC.high();
  SegmentD.high();
  SegmentE.high();
  SegmentF.high();
  SegmentG.high();
  SegmentDP.high();
}

void allDigitOutput() {
  Digit3.output();
  Digit4.output();
  Digit5.output();
  Digit6.output();
  Digit7.output();
  Digit8.output();
  Digit9.output();
}

void allDigitOff() {
  Digit3.low();
  Digit4.low();
  Digit5.low();
  Digit6.low();
  Digit7.low();
  Digit8.low();
  Digit9.low();
}

void allKeyRowOff() {
  KeyRowA.input();
  KeyRowB.input();
  KeyRowC.input();

  KeyRowA.low();
  KeyRowB.low();
  KeyRowC.low();
}

void allKeyRowIdle() {
  KeyRowA.output();
  KeyRowB.output();
  KeyRowC.output();

  KeyRowA.high();
  KeyRowB.high();
  KeyRowC.high();
}

void outputDigit(signed char digit) {

  //decimal point is turned on automatically by void display()
  /*
    if (digit < 0)
    {
      SegmentDP.low();
      digit ^= 255;
      digit++;
    }
    else
    {
      SegmentDP.high();
    }
  */

  allDigitOff();

  switch (digit) {
    case 0:
      SegmentA.low();
      SegmentB.low();
      SegmentC.low();
      SegmentD.low();
      SegmentE.low();
      SegmentF.low();
      SegmentG.high();
      break;
    case 1:
      SegmentA.high();
      SegmentB.low();
      SegmentC.low();
      SegmentD.high();
      SegmentE.high();
      SegmentF.high();
      SegmentG.high();
      break;
    case 2:
      SegmentA.low();
      SegmentB.low();
      SegmentC.high();
      SegmentD.low();
      SegmentE.low();
      SegmentF.high();
      SegmentG.low();
      break;
    case 3:
      SegmentA.low();
      SegmentB.low();
      SegmentC.low();
      SegmentD.low();
      SegmentE.high();
      SegmentF.high();
      SegmentG.low();
      break;
    case 4:
      SegmentA.high();
      SegmentB.low();
      SegmentC.low();
      SegmentD.high();
      SegmentE.high();
      SegmentF.low();
      SegmentG.low();
      break;
    case 5:
      SegmentA.low();
      SegmentB.high();
      SegmentC.low();
      SegmentD.low();
      SegmentE.high();
      SegmentF.low();
      SegmentG.low();
      break;
    case 6:
      SegmentA.low();
      SegmentB.high();
      SegmentC.low();
      SegmentD.low();
      SegmentE.low();
      SegmentF.low();
      SegmentG.low();
      break;
    case 7:
      SegmentA.low();
      SegmentB.low();
      SegmentC.low();
      SegmentD.high();
      SegmentE.high();
      SegmentF.high();
      SegmentG.high();
      break;
    case 8:
      SegmentA.low();
      SegmentB.low();
      SegmentC.low();
      SegmentD.low();
      SegmentE.low();
      SegmentF.low();
      SegmentG.low();
      break;
    case 9:
      SegmentA.low();
      SegmentB.low();
      SegmentC.low();
      SegmentD.high();
      SegmentE.high();
      SegmentF.low();
      SegmentG.low();
      break;
    case 10:
      SegmentA.high();
      SegmentB.high();
      SegmentC.high();
      SegmentD.high();
      SegmentE.high();
      SegmentF.high();
      SegmentG.low();
      break;
    default:
      allSegmentOff();
      break;
  }
}

void selectDigit(byte digit) {

  allDigitOff();

  switch (digit) {
    case 0:
      break;
    case 1:
      break;
    case 2:
      Digit3.high();
      break;
    case 3:
      Digit4.high();
      break;
    case 4:
      Digit5.high();
      break;
    case 5:
      Digit6.high();
      break;
    case 6:
      Digit7.high();
      break;
    case 7:
      Digit8.high();
      break;
    case 8:
      Digit9.high();
      break;
  }
}

void display() {
  for (byte i = 0; i < 9; i++) {
    outputDigit(digits[i]);
    selectDigit(i);

    //SINCLAIR behavior: turn decimal point on automatically at fixed position
    if (i == 3) {
      SegmentDP.low();
    }
    else
    {
      SegmentDP.high();
    }

    backgroundWork();
  }
}

char readKey() {
  byte key = 0;

  allDigitOff();
  allSegmentInput();

  for (byte i = 0; i < 3; i++)
  {
    allKeyRowIdle();
    switch (i) {
      case 0:
        KeyRowA.low();
        delayMicroseconds(2); //for reliability on first read instruction, allow for .low on line before to settle
        if (!SegmentA.read()) key = 1;
        if (!SegmentB.read()) key = 2;
        if (!SegmentC.read()) key = 3;
        if (!SegmentD.read()) key = 4;
        if (!SegmentE.read()) key = 5;
        if (!SegmentF.read()) key = 6;
        if (!SegmentG.read()) key = 7;
        if (!SegmentDP.read()) key = 8;
        break;
      case 1:
        KeyRowB.low();
        delayMicroseconds(2);
        if (!SegmentA.read()) key = 9;
        if (!SegmentB.read()) key = 10;
        if (!SegmentC.read()) key = 11;
        if (!SegmentD.read()) key = 12;
        if (!SegmentE.read()) key = 13;
        if (!SegmentF.read()) key = 14;
        if (!SegmentG.read()) key = 15;
        if (!SegmentDP.read()) key = 16;
        break;
      case 2:
        KeyRowC.low();
        delayMicroseconds(2);
        if (!SegmentA.read()) key = 17;
        if (!SegmentB.read()) key = 18;
        break;
    }
  }

  allKeyRowOff();
  allSegmentOutput();

  return key;
}
