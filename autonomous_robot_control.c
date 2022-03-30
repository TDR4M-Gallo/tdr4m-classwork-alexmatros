#include <PRIZM.h>
PRIZM prizm;

int phase = 0;

void setup() {
  prizm.PrizmBegin();
  prizm.setMotorInvert(1, 1);
}

void loop() {
  if (phase == 0) {
    phase_ZERO();

    if (lineDetected() == true) {
      phase++;
    }
  }

  if (phase == 1) {
    phase_ONE();
    phase++;
  }

  if (phase == 2) {
    phase_TWO();
    
    if (prizm.readSonicSensorCM(4) < 60) {
      phase++;
    }
  }

  if (phase == 3) {
    phase_THREE();
    phase++;
  }

  if (phase == 4) {
    phase_FOUR();

    if (lineDetected() == true) {
      phase++;
    }
  }

  if (phase == 5) {
    phase_FIVE();
  }
}

void phase_ZERO() {
  prizm.setMotorPowers(35, 35);
}

void phase_ONE() {
  prizm.setMotorPowers(125, 125);

  turnOntoLine(1, 90);
}

void phase_TWO() {
  followLine();
}

void phase_THREE() {
  prizm.setMotorPowers(125, 125);
  
  turnOntoLine(0, 45);
}

void phase_FOUR() {
  prizm.setMotorPowers(35, 35);
}

void phase_FIVE() {
  followLine();
}


bool lineDetected() {
  if (prizm.readLineSensor(3) == 1) {
    return true;
  }
  else {
    return false;
  }
}

void turnOntoLine(int direction, int degree) { // 0: left, 1: right
  prizm.setMotorPowers(125, 125);

  delay(500);

  if (degree == 90) {
    if (direction == 1) {
      prizm.setMotorPowers(60, -25);
    }
    else if (direction == 0) {
      prizm.setMotorPowers(-25, 60);
    }

    delay(700);
  }

  if (degree == 45) {
    if (direction == 1) {
      prizm.setMotorPowers(60, -25);
    }
    else if (direction == 0) {
      prizm.setMotorPowers(-25, 60);
    }

    delay(450);
  }

  prizm.setMotorPowers(125, 125);
  delay(500);
}

void followLine() {
  if (prizm.readLineSensor(3) == 0) {
    prizm.setMotorPowers(125, 30);
  }
  if (prizm.readLineSensor(3) == 1) {
    prizm.setMotorPowers(30, 125);
  }
}
