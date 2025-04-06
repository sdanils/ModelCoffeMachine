#include <iostream>

#include "Automata.h"

int main() {
  vector<string> menu = {"kapuchino", "amerikano", "expresso"};
  vector<int> prices = {50, 62, 140};

  optional<Automata> coffe_machine_o = Automata::create_automata(menu, prices);
  if (coffe_machine_o == std::nullopt) return -1;
  Automata& coffe_machine = *coffe_machine_o;
  coffe_machine.on();
  Automata::BANKNOTES note = Automata::BANKNOTES::FIF;
  int coins = 0;

  coffe_machine.coin(note);
  coins += coffe_machine.choice("amerikano");
  coins += coffe_machine.choice("kapuchino");

  note = Automata::BANKNOTES::THUN;
  coffe_machine.coin(note);
  coins += coffe_machine.choice("expresso");
  coins += coffe_machine.choice("amerikano");
  coins += coffe_machine.cancel();

  return 0;
}