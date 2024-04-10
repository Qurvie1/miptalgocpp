#include <iostream>

char numbers[10][6][5];

void NumberDefinition(char numbers[10][6][5], char time[6][21], int position, int* number_question) {
  int p = 6;  // переменные, чтоб в цикле не писать числа
  int q = 5;
  if (position == 0) {  // проверяем, есть ли столбец 0 в начале
    for (int i = 0; i < p; ++i) {
      if (time[i][0] != '.') {
        number_question[0] = -1;  // ERROR
        return;
      }
    }
  }
  auto is_number = new bool[10]{};  // подходит ли нам какая-то цифра
  for (int m = 0; m < 2 * q; ++m) {
    is_number[m] = true;
  }
  int counter = 10;
  int i = 1 + 5 * position;  // начальная позиция цифры по строке в подаваемом массиве
  int t = 0;                 // типа индекс цифры по строке в массице ЦИФР
  while (t < q) {                        // идём по номеру столбца в цифре
    for (int m = 0; m < p; ++m) {        // идём по номеру строки
      for (int n = 0; n < 2 * q; ++n) {  // идём по конкретным цифрам
        if (time[m][i + t] == '#' && numbers[n][m][t] != '#') {
          if (is_number[n]) {
            is_number[n] = false;
            --counter;
          }
        }
      }
    }
    ++t;
  }
  int n = 0;
  for (int j = 0; j < 2 * q; ++j) {  // в чём идея: если нам подходит
    if (is_number[j]) {
      number_question[n++] = j;
    }
  }
  if (counter == 0) {
    number_question[0] = -1;
  }
  delete[] is_number;
}

int main() {
  int a = 10;
  int b = 6;
  int c = 5;
  for (int i = 0; i < a; ++i) {
    for (int j = 0; j < b; ++j) {
      for (int k = 0; k < c; ++k) {
        numbers[i][j][k] = '.';
      }
    }
  }
  numbers[0][0][1] = '#';
  numbers[0][0][2] = '#';
  numbers[0][1][0] = '#';
  numbers[0][1][3] = '#';
  numbers[0][2][0] = '#';
  numbers[0][2][3] = '#';
  numbers[0][3][0] = '#';
  numbers[0][3][3] = '#';
  numbers[0][4][0] = '#';
  numbers[0][4][3] = '#';
  numbers[0][5][1] = '#';
  numbers[0][5][2] = '#';

  numbers[1][0][3] = '#';
  numbers[1][1][2] = '#';
  numbers[1][1][3] = '#';
  numbers[1][2][3] = '#';
  numbers[1][2][1] = '#';
  numbers[1][3][3] = '#';
  numbers[1][4][3] = '#';
  numbers[1][5][3] = '#';

  numbers[2][0][1] = '#';
  numbers[2][0][2] = '#';
  numbers[2][1][3] = '#';
  numbers[2][1][0] = '#';
  numbers[2][2][3] = '#';
  numbers[2][3][2] = '#';
  numbers[2][4][1] = '#';
  numbers[2][5][0] = '#';
  numbers[2][5][1] = '#';
  numbers[2][5][2] = '#';
  numbers[2][5][3] = '#';

  numbers[3][0][0] = '#';
  numbers[3][0][1] = '#';
  numbers[3][0][2] = '#';
  numbers[3][0][3] = '#';
  numbers[3][1][3] = '#';
  numbers[3][2][2] = '#';
  numbers[3][3][3] = '#';
  numbers[3][4][3] = '#';
  numbers[3][5][0] = '#';
  numbers[3][5][1] = '#';
  numbers[3][5][2] = '#';

  numbers[4][0][0] = '#';
  numbers[4][0][3] = '#';
  numbers[4][1][0] = '#';
  numbers[4][1][3] = '#';
  numbers[4][2][0] = '#';
  numbers[4][2][3] = '#';
  numbers[4][3][0] = '#';
  numbers[4][3][1] = '#';
  numbers[4][3][2] = '#';
  numbers[4][3][3] = '#';
  numbers[4][4][3] = '#';
  numbers[4][5][3] = '#';

  numbers[5][0][0] = '#';
  numbers[5][0][1] = '#';
  numbers[5][0][2] = '#';
  numbers[5][0][3] = '#';
  numbers[5][1][0] = '#';
  numbers[5][2][0] = '#';
  numbers[5][2][1] = '#';
  numbers[5][2][2] = '#';
  numbers[5][3][3] = '#';
  numbers[5][4][0] = '#';
  numbers[5][4][3] = '#';
  numbers[5][5][1] = '#';
  numbers[5][5][2] = '#';

  numbers[6][0][1] = '#';
  numbers[6][0][2] = '#';
  numbers[6][0][3] = '#';
  numbers[6][1][0] = '#';
  numbers[6][2][0] = '#';
  numbers[6][2][1] = '#';
  numbers[6][2][2] = '#';
  numbers[6][3][0] = '#';
  numbers[6][3][3] = '#';
  numbers[6][4][0] = '#';
  numbers[6][4][3] = '#';
  numbers[6][5][1] = '#';
  numbers[6][5][2] = '#';

  numbers[7][0][1] = '#';
  numbers[7][0][2] = '#';
  numbers[7][0][3] = '#';
  numbers[7][0][0] = '#';
  numbers[7][1][3] = '#';
  numbers[7][2][2] = '#';
  numbers[7][3][1] = '#';
  numbers[7][4][1] = '#';
  numbers[7][5][1] = '#';

  numbers[8][0][1] = '#';
  numbers[8][0][2] = '#';
  numbers[8][1][0] = '#';
  numbers[8][1][3] = '#';
  numbers[8][2][1] = '#';
  numbers[8][2][2] = '#';
  numbers[8][3][0] = '#';
  numbers[8][3][3] = '#';
  numbers[8][4][0] = '#';
  numbers[8][4][3] = '#';
  numbers[8][5][1] = '#';
  numbers[8][5][2] = '#';

  numbers[9][0][1] = '#';
  numbers[9][0][2] = '#';
  numbers[9][1][0] = '#';
  numbers[9][1][3] = '#';
  numbers[9][2][0] = '#';
  numbers[9][2][3] = '#';
  numbers[9][3][1] = '#';
  numbers[9][3][2] = '#';
  numbers[9][3][3] = '#';
  numbers[9][4][3] = '#';
  numbers[9][5][1] = '#';
  numbers[9][5][1] = '#';
  numbers[9][5][2] = '#';
  numbers[9][5][0] = '#';
  char time[6][21]{};
  auto number_question = new int[10]{};
  for (int i = 0; i < 2 * c; ++i) {  // фиктивные числа, потому что нас интересуют только 0, ..., 9
    number_question[i] = 100;
  }
  for (int i = 0; i < b; ++i) {
    for (int k = 0; k < 2 * a; ++k) {
      std::cin >> time[i][k];
    }
  }
  int positions = 4;
  int answer = 0;
  int counter = 0;
  auto new_time = new int[5]{};
  for (int i = 0; i < positions; ++i) {
    if (answer == -1 || answer == -2) {
      break;
    }
    NumberDefinition(numbers, time, i, number_question);
    if (number_question[0] == -1) {
      answer = -2;
      break;
    }
    for (int k = 0; k < 2 * c; ++k) {
      if (i == 0 && number_question[k] != 100) {
        if (number_question[k] == 1 || number_question[k] == 2 ||
            number_question[k] == 0) {  // цифры, которые нам подходят.
          new_time[0] =
              number_question[k];  // записываем первое попавшееся число, чтоб не париться со случаем counter == 1
          ++counter;  // так как в случае counter == 1 сразу запишется это число
        }
        if (counter > 1) {  // > 1 число - AMBIGUITY
          answer = -1;
          break;
        }
        if (counter == 0) {
          answer = -2;
          break;
        }
      }
      if (i == 1 && number_question[k] != 100) {
        if (new_time[0] == 1 ||
            new_time[0] == 0) {  // если первое число 1 или 0, то нам подходит любое, лишь бы не AMBIGUITY
          ++counter;
          new_time[i] = number_question[k];  // такой же принцип
        }
        if (counter > 1) {
          answer = -1;
          break;
        }
        if (new_time[0] == 2) {
          if (number_question[k] < 4) {
            ++counter;
            new_time[i] = number_question[k];
          }
          if (counter > 1) {
            answer = -1;
            break;
          }
          if (counter == 0) {
            answer = -2;
            break;
          }
        }
      }
      if (i == 2 && number_question[k] != 100) {
        if (number_question[k] < 6) {
          ++counter;
          new_time[i] = number_question[k];
        }
        if (counter > 1) {
          answer = -1;
          break;
        }
        if (counter == 0) {
          answer = -2;
          break;
        }
      }
      if (i == 3 && number_question[k] != 100) {
        ++counter;
        new_time[i] = number_question[k];
        if (counter > 1) {
          answer = -1;
          break;
        }
      }
    }
    counter = 0;
    for (int j = 0; j < 2 * c; ++j) {
      number_question[j] = 100;
    }
  }
  if (answer == -1) {
    std::cout << "AMBIGUITY\n";
  }
  if (answer == -2) {
    std::cout << "ERROR\n";
  }
  if (answer == 0) {
    std::cout << new_time[0] << new_time[1] << ':' << new_time[2] << new_time[3] << '\n';
  }
  delete[] new_time;
  delete[] number_question;
  return 0;
}