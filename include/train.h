// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TRAIN_H_
#define INCLUDE_TRAIN_H_

class Train {
 private:
  struct Wagon {
    bool bulb;
    Wagon *nextWagon;
    Wagon *prevWagon;
  };
  int totalMoves;
  Wagon *entryPoint;

 public:
  Train();
  void appendWagon(bool bulbState);
  int calcLength();
  int getTotalMoves();
};

#endif  // INCLUDE_TRAIN_H_
