#include "Automata.h"

optional<Automata> Automata::create_automata(vector<string>& menu,
                                             vector<int>& prices) {
  if (menu.size() != prices.size()) {
    return std::nullopt;
  } else {
    return Automata(menu, prices);
  }
}

Automata::Automata(vector<string>& menu_, vector<int>& prices_) {
  cash = 0;
  menu = menu_;
  prices = prices_;
  state = STATES::OFF;
}

void Automata::on() {
  if (state == STATES::OFF) {
    state = STATES::WAIT;
  }
}

void Automata::off() { state = STATES::OFF; }

int Automata::coin(BANKNOTES banknote) {
  if (state == STATES::OFF || state == STATES::COOK) {
    return (int)banknote;
  }

  cash += (int)banknote;
  state = STATES::ACCEPT;
  return 0;
}

unordered_map<string, int> Automata::et_menu() {
  unordered_map<string, int> inter_menu;
  for (int i = 0; i < menu.size(); i++) {
    inter_menu[menu[i]] = prices[i];
  }
  return inter_menu;
}

Automata::STATES Automata::get_state() { return state; }

int Automata::find_index_drink(string drink) {
  int index = 0;
  while (index < menu.size() && menu[index] != drink) {
    index++;
  }
  if (index == menu.size()) {
    return -1;
  }
  return index;
}

bool Automata::check(int need_money) {
  if (cash < need_money) {
    return false;
  }
  return true;
}

int Automata::change() {
  int change = cash;
  cash = 0;
  return change;
}

int Automata::finish() {
  state = STATES::WAIT;
  return change();
}

int Automata::cook(string drink) {
  cash -= prices[find_index_drink(drink)];
  state = STATES::COOK;

  // Готовит...

  return finish();
}

int Automata::choice(string drink) {
  if (state != STATES::ACCEPT && state != STATES::CHECK) {
    return 0;
  }

  int index_drink = find_index_drink(drink);
  if (index_drink == -1) {
    return 0;
  }

  state = STATES::CHECK;
  int need_money = prices[index_drink];
  if (!check(need_money)) {
    return 0;
  }

  return cook(drink);
}

int Automata::cancel() {
  if (state != STATES::ACCEPT && state != STATES::CHECK) {
    return 0;
  }

  state = STATES::WAIT;
  return change();
}