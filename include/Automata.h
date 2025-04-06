// Copyright 2025 <Copyright Owner>

#pragma once

#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

using std::optional;
using std::string;
using std::unordered_map;
using std::vector;

class Automata {
 public:
  enum class BANKNOTES {
    FIF = 50,
    HUN = 100,
    THUN = 200,
    FHUN = 500,
  };

  enum class STATES {
    OFF,
    WAIT,
    ACCEPT,
    CHECK,
    COOK,
  };

  /**
   * @brief Фабричный метод создания обьекта автомата
   * @details Используется для проверки передаваемых массивов
   **/
  static optional<Automata> create_automata(const vector<string>& menu,
                                            const vector<int>& prices);

  void on();
  void off();
  int coin(BANKNOTES);
  unordered_map<string, int> et_menu();
  STATES get_state();

  /**
   * @brief Выбор напитка клиентом
   * @param drink Строка названия напитка
   * @return Сдача после приготовления напитка или ноль, если приготовления не
   *было
   **/
  int choice(string drink);

  /**
   * @brief Выход из состояния выбора напитка
   * @return Внесённые деньги
   **/
  int cancel();

 private:
  int cash;
  vector<string> menu;
  vector<int> prices;
  STATES state;

  Automata(const vector<string>& menu, const vector<int>& prices);
  bool check(int need_money);
  int cook(string drink);
  int finish();

  /**
   * @brief Имитация выдачи сдачи
   **/
  int change();
  /**
   * @brief Ищет индекс напитка в меню
   * @param drink Строка названия
   * @return Индекс напитка
   **/
  int find_index_drink(string drink);
};
