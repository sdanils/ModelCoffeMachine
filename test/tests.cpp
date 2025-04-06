// Copyright 2022 GHA Test Team

#include <gtest/gtest.h>

#include "Automata.h"

TEST(automata_test, create_automata_test) {
  vector<string> menu = {"kapuchino", "amerikano", "expresso"};
  vector<int> prices = {50, 62, 140};

  optional<Automata> coffe_machine_o = Automata::create_automata(menu, prices);
  EXPECT_NE(coffe_machine_o, std::nullopt);
  Automata& coffe_machine = *coffe_machine_o;

  unordered_map<string, int> menu_automata = coffe_machine.et_menu();
  EXPECT_EQ(menu_automata.size(), 3);
}

TEST(automata_test, on_off_test) {
  vector<string> menu = {"kapuchino", "amerikano", "expresso"};
  vector<int> prices = {50, 62, 140};

  optional<Automata> coffe_machine_o = Automata::create_automata(menu, prices);
  Automata& coffe_machine = *coffe_machine_o;

  coffe_machine.on();
  EXPECT_EQ(coffe_machine.get_state(), Automata::STATES::WAIT);
  coffe_machine.off();
  EXPECT_EQ(coffe_machine.get_state(), Automata::STATES::OFF);
}

TEST(automata_test, correct_choice) {
  vector<string> menu = {"kapuchino", "amerikano", "expresso"};
  vector<int> prices = {50, 62, 140};

  optional<Automata> coffe_machine_o = Automata::create_automata(menu, prices);
  Automata& coffe_machine = *coffe_machine_o;
  coffe_machine.on();

  EXPECT_EQ(coffe_machine.coin(Automata::BANKNOTES::FIF), 0);
  EXPECT_EQ(coffe_machine.get_state(), Automata::STATES::ACCEPT);
  EXPECT_EQ(coffe_machine.choice("kapuchino"), 0);
  EXPECT_EQ(coffe_machine.get_state(), Automata::STATES::WAIT);
}

TEST(automata_test, uncorrect_choice) {
  vector<string> menu = {"kapuchino", "amerikano", "expresso"};
  vector<int> prices = {50, 62, 140};

  optional<Automata> coffe_machine_o = Automata::create_automata(menu, prices);
  Automata& coffe_machine = *coffe_machine_o;
  coffe_machine.on();

  coffe_machine.coin(Automata::BANKNOTES::FIF);
  EXPECT_EQ(coffe_machine.get_state(), Automata::STATES::ACCEPT);
  EXPECT_EQ(coffe_machine.choice("amerikano"), 0);
  EXPECT_EQ(coffe_machine.get_state(), Automata::STATES::CHECK);
}

TEST(automata_test, corre_choice_change) {
  vector<string> menu = {"kapuchino", "amerikano", "expresso"};
  vector<int> prices = {50, 62, 140};

  optional<Automata> coffe_machine_o = Automata::create_automata(menu, prices);
  Automata& coffe_machine = *coffe_machine_o;
  coffe_machine.on();

  coffe_machine.coin(Automata::BANKNOTES::HUN);
  EXPECT_EQ(coffe_machine.get_state(), Automata::STATES::ACCEPT);
  EXPECT_EQ(coffe_machine.choice("amerikano"), 38);
  EXPECT_EQ(coffe_machine.get_state(), Automata::STATES::WAIT);
}

TEST(automata_test, cancel_after_coin) {
  vector<string> menu = {"kapuchino", "amerikano", "expresso"};
  vector<int> prices = {50, 62, 140};

  optional<Automata> coffe_machine_o = Automata::create_automata(menu, prices);
  Automata& coffe_machine = *coffe_machine_o;
  coffe_machine.on();

  coffe_machine.coin(Automata::BANKNOTES::HUN);
  EXPECT_EQ(coffe_machine.get_state(), Automata::STATES::ACCEPT);
  EXPECT_EQ(coffe_machine.cancel(), (int)Automata::BANKNOTES::HUN);
  EXPECT_EQ(coffe_machine.get_state(), Automata::STATES::WAIT);
}

TEST(automata_test, cancel_after_uncorre_choice) {
  vector<string> menu = {"kapuchino", "amerikano", "expresso"};
  vector<int> prices = {50, 62, 140};

  optional<Automata> coffe_machine_o = Automata::create_automata(menu, prices);
  Automata& coffe_machine = *coffe_machine_o;
  coffe_machine.on();

  coffe_machine.coin(Automata::BANKNOTES::FIF);
  EXPECT_EQ(coffe_machine.choice("amerikano"), 0);
  EXPECT_EQ(coffe_machine.cancel(), (int)Automata::BANKNOTES::FIF);
  EXPECT_EQ(coffe_machine.get_state(), Automata::STATES::WAIT);
}

TEST(automata_test, cancel_in_wait) {
  vector<string> menu = {"kapuchino", "amerikano", "expresso"};
  vector<int> prices = {50, 62, 140};

  optional<Automata> coffe_machine_o = Automata::create_automata(menu, prices);
  Automata& coffe_machine = *coffe_machine_o;
  coffe_machine.on();

  EXPECT_EQ(coffe_machine.cancel(), 0);
  EXPECT_EQ(coffe_machine.get_state(), Automata::STATES::WAIT);
}

TEST(automata_test, coin_after_uncorrect_choice) {
  vector<string> menu = {"kapuchino", "amerikano", "expresso"};
  vector<int> prices = {50, 62, 140};

  optional<Automata> coffe_machine_o = Automata::create_automata(menu, prices);
  Automata& coffe_machine = *coffe_machine_o;
  coffe_machine.on();

  EXPECT_EQ(coffe_machine.coin(Automata::BANKNOTES::FIF), 0);
  EXPECT_EQ(coffe_machine.choice("amerikano"), 0);
  EXPECT_EQ(coffe_machine.coin(Automata::BANKNOTES::FIF), 0);
  EXPECT_EQ(coffe_machine.choice("amerikano"), 38);
  EXPECT_EQ(coffe_machine.get_state(), Automata::STATES::WAIT);
}

TEST(automata_test, choice_without_coin) {
  vector<string> menu = {"kapuchino", "amerikano", "expresso"};
  vector<int> prices = {50, 62, 140};

  optional<Automata> coffe_machine_o = Automata::create_automata(menu, prices);
  Automata& coffe_machine = *coffe_machine_o;
  coffe_machine.on();

  EXPECT_EQ(coffe_machine.choice("amerikano"), 0);
  EXPECT_EQ(coffe_machine.get_state(), Automata::STATES::WAIT);
}

TEST(automata_test, full_cycle) {
  vector<string> menu = {"kapuchino", "amerikano", "expresso"};
  vector<int> prices = {50, 62, 140};

  optional<Automata> coffe_machine_o = Automata::create_automata(menu, prices);
  Automata& coffe_machine = *coffe_machine_o;
  coffe_machine.on();
  EXPECT_EQ(coffe_machine.get_state(), Automata::STATES::WAIT);

  coffe_machine.coin(Automata::BANKNOTES::FIF);
  EXPECT_EQ(coffe_machine.get_state(), Automata::STATES::ACCEPT);

  EXPECT_EQ(coffe_machine.choice("amerikano"), 0);
  EXPECT_EQ(coffe_machine.get_state(), Automata::STATES::CHECK);

  coffe_machine.coin(Automata::BANKNOTES::FIF);
  EXPECT_EQ(coffe_machine.get_state(), Automata::STATES::ACCEPT);

  EXPECT_EQ(coffe_machine.choice("amerikano"), 38);
  EXPECT_EQ(coffe_machine.get_state(), Automata::STATES::WAIT);

  coffe_machine.off();
  EXPECT_EQ(coffe_machine.get_state(), Automata::STATES::OFF);
}