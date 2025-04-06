#include <map>
#include <optional>
#include <string>
#include <vector>

using std::map;
using std::optional;
using std::string;
using std::vector;

class Automata {
 public:
  enum class BANKNOTES {
    FIF = 50,
    HUN = 100,
    THUN = 200,
    FHUN = 500,
  };

  /**
   * @brief Фабричный метод создания обьекта автомата
   * @details Используется для проверки передаваемых массивов
   **/
  static optional<Automata> create_automata(vector<string>& menu,
                                            vector<int> prices);

  void on();
  void off();
  int coin(BANKNOTES);
  map<string, int> et_menu();
  int choice(string);
  int cancel();

 private:
  enum class STATES {
    OFF,
    WAIT,
    ACCEPT,
    CHECK,
    COOK,
  };

  int cash;
  vector<string> menu;
  vector<int> prices;
  STATES state;

  Automata(vector<string>& menu, vector<int> prices);
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