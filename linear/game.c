#include <stdio.h>
#include <string.h>

//
void print_game(int game[3][3], int input_array[3][3], char key, int input_num);
char mark(int i);
void input_game(int game[3][3], int player);
void calc_x(int game[3][3], int input_array[3][3]);
int judge_game(int game[3][3]);

int main() {
  while (1) {
    // ゲームの初期化
    int counter = 0, state = 0;
    int game[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    // ゲームの実行
    printf("\e[1;1H\e[2J");
    while (state == 0) {
      // プレイヤーの判定
      int player = counter % 2 + 1;

      // 入力の処理
      input_game(game, player);

      // 勝敗の判定
      state = judge_game(game);
      if (state == 1 || state == 2) {
        printf("プレイヤー%dの勝利です!\n", state);
        break;
      } else if (counter == 26) {
        printf("引き分けです!\n");
        break;
      }

      // カウンターの更新
      counter++;
    }
    // ゲームの終了
    char continue_game = 'n';
    printf("もう一度プレイしますか？(y/n) ");
    scanf(" %c", &continue_game);
    if (continue_game == 'n') break;
  }
  printf("ゲームを終了します。\n");
  printf("Thank you for playing!\n");
  return 0;
}

void print_game(int game[3][3], int input_array[3][3], char key,
                int input_num) {
  char color[10] = {"\0"};
  if (key == 'x')
    strcpy(color, "\x1b[31m");
  else if (key == '+')
    strcpy(color, "\x1b[32m");
  else
    strcpy(color, "\e[47m");

  // ゲームの描画
  printf("     入力用       計算記号     現在の画面\n");
  printf("┏             ┓             ┏             ┓\n");
  printf(
      "┃ %s %d %s┃%s %d %s┃%s %d %s ┃             ┃  %s%s%c%s ┃ %s%s%c%s ┃ "
      "%s%s%c%s \e[m ┃\n",
      input_array[0][0] == input_num ? "\e[47m" : "", input_array[0][0],
      input_array[0][0] == input_num ? "\x1b[0m" : "",
      input_array[0][1] == input_num ? "\e[47m" : "", input_array[0][1],
      input_array[0][1] == input_num ? "\x1b[0m" : "",
      input_array[0][2] == input_num ? "\e[47m" : "", input_array[0][2],
      input_array[0][2] == input_num ? "\x1b[0m" : "",
      game[0][0] ? "\e[1m" : "", game[0][0] == 1 ? "\e[31m" : "",
      mark(game[0][0]), game[0][0] ? "\e[0m" : "", game[0][1] ? "\e[1m" : "",
      game[0][1] == 1 ? "\e[31m" : "", mark(game[0][1]),
      game[0][1] ? "\e[0m" : "", game[0][2] ? "\e[1m" : "",
      game[0][2] == 1 ? "\e[31m" : "", mark(game[0][2]),
      game[0][2] ? "\e[0m" : "");
  printf("┃ ━━━ ━━━ ━━━ ┃    ┏━━━┓    ┃ ━━━ ━━━ ━━━ ┃\n");
  printf(
      "┃ %s %d %s┃%s %d %s┃%s %d %s ┃    ┃%s\x1b[1m %c \x1b[0m\e[0m┃    ┃  "
      "%s%s%c%s ┃ "
      "%s%s%c%s ┃ %s%s%c%s \e[m ┃\n",
      input_array[1][0] == input_num ? "\e[47m" : "", input_array[1][0],
      input_array[1][0] == input_num ? "\x1b[0m" : "",
      input_array[1][1] == input_num ? "\e[47m" : "", input_array[1][1],
      input_array[1][1] == input_num ? "\x1b[0m" : "",
      input_array[1][2] == input_num ? "\e[47m" : "", input_array[1][2],
      input_array[1][2] == input_num ? "\x1b[0m" : "", color, key,
      game[1][0] ? "\e[1m" : "", game[1][0] == 1 ? "\e[31m" : "",
      mark(game[1][0]), game[1][0] ? "\e[0m" : "", game[1][1] ? "\e[1m" : "",
      game[1][1] == 1 ? "\e[31m" : "", mark(game[1][1]),
      game[1][1] ? "\e[0m" : "", game[1][2] ? "\e[1m" : "",
      game[1][2] == 1 ? "\e[31m" : "", mark(game[1][2]),
      game[1][2] ? "\e[0m" : "");
  printf("┃ ━━━ ━━━ ━━━ ┃    ┗━━━┛    ┃ ━━━ ━━━ ━━━ ┃\n");
  printf(
      "┃ %s %d %s┃%s %d %s┃%s %d %s ┃             ┃  %s%s%c%s ┃ %s%s%c%s ┃ "
      "%s%s%c%s \e[m ┃\n",
      input_array[2][0] == input_num ? "\e[47m" : "", input_array[2][0],
      input_array[2][0] == input_num ? "\x1b[0m" : "",
      input_array[2][1] == input_num ? "\e[47m" : "", input_array[2][1],
      input_array[2][1] == input_num ? "\x1b[0m" : "",
      input_array[2][2] == input_num ? "\e[47m" : "", input_array[2][2],
      input_array[2][2] == input_num ? "\x1b[0m" : "",
      game[2][0] ? "\e[1m" : "", game[2][0] == 1 ? "\e[31m" : "",
      mark(game[2][0]), game[2][0] ? "\e[0m" : "", game[2][1] ? "\e[1m" : "",
      game[2][1] == 1 ? "\e[31m" : "", mark(game[2][1]),
      game[2][1] ? "\e[0m" : "", game[2][2] ? "\e[1m" : "",
      game[2][2] == 1 ? "\e[31m" : "", mark(game[2][2]),
      game[2][2] ? "\e[0m" : "");
  printf("┗             ┛             ┗             ┛\n");
}

void input_game(int game[3][3], int player) {
  // 入力の処理
  int game_check = 0;
  int input = 0;
  int input_num = 1;
  int input_array[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
  int sample_array[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  int first_count = 0;
  char key = '?';
  // gameに空きがあるか確認
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (game[i][j] != 0) game_check += 1;
    }
  }
  print_game(game, sample_array, key, input);
  printf("プレイヤー%dのターンです。\n", player);
  if (game_check < 9) {
    printf("?の計算記号を入力してください(x,+)");
    scanf(" %c", &key);
  } else {
    key = 'x';
  }
  printf("\e[1;1H\e[2J");
  // inputの処理
  switch (key) {
    case 'x':
      while (input_num <= 9) {
        if (game_check == 9)
          printf("新たに入力するスペースがないため「x 」が選択されました。\n");
        print_game(game, sample_array, key, input_num);
        printf("%dに入力したい数字を入力してください(0,1)", input_num);
        scanf("%d", &input);
        if (input != 0 && input != 1) {
          printf("\e[1;1H\e[2J");
          printf("0か1の数字を入力してください。\n");
          continue;
        }
        // input_numから行列の生成
        int x = (input_num - 1) % 3;
        int y = (input_num - 1) / 3;
        if (first_count > 3) {
          printf("\e[1;1H\e[2J");
          printf("1は3つまでしか入力できません。\n");
          continue;
        }
        // input_arrrayの生成
        switch (input) {
          case 0:
            input_array[y][x] = 0;
            break;
          case 1:
            if (input_array[y][0] == 1 || input_array[y][1] == 1 ||
                input_array[y][2] == 1) {
              printf("\e[1;1H\e[2J");
              printf("同じ列に1は1つまでしか入力できません。\n");
              continue;
            } else if (input_array[0][x] == 1 || input_array[1][x] == 1 ||
                       input_array[2][x] == 1) {
              printf("\e[1;1H\e[2J");
              printf("同じ行に1は1つまでしか入力できません。\n");
              continue;
            }
            input_array[y][x] = 1;
            first_count++;
            break;
          default:
            break;
        }
        input_num++;
        printf("\e[1;1H\e[2J");
      }
      // input_arryの値が全ての0の時の処理
      int input_sum = 0;
      for (int i = 0; i < 3; i++) {
        for (int n = 0; n < 3; n++) {
          input_sum += input_array[i][n];
        }
      }
      if (input_sum == 0) {
        printf("最低でも1つは1を選んでください。\n");
        input_game(game, player);
      }
      calc_x(game, input_array);
      break;
    case '+':
      while (1) {
        print_game(game, sample_array, key, input);
        printf("%cを入力する場所の数字を1~9から選んで入力してください。",
               mark(player));
        scanf("%d", &input);
        if (input < 1 || input > 9) {
          printf("\e[1;1H\e[2J");
          printf("1~9の数字を入力してください。\n");
          continue;
        }
        // 不正な入力の判定
        int x = (input - 1) % 3;
        int y = (input - 1) / 3;
        if (game[y][x] != 0) {
          printf("\e[1;1H\e[2J");
          printf("その場所に入力することはできません。\n");
          continue;
        }
        break;
      }
      // input_arrayの生成
      int x = (input - 1) % 3;
      int y = (input - 1) / 3;
      game[y][x] = player;
      printf("\e[1;1H\e[2J");
      break;
    default:
      printf("\e[1;1H\e[2J");
      printf("「 x  」か「 +  」を入力してください。\n");
      input_game(game, player);
  }
}

void calc_x(int game[3][3], int input_array[3][3]) {
  int tmp_game[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
  // 行列計算をする
  for (int i = 0; i < 3; i++) {
    tmp_game[i][0] = input_array[i][0] * game[0][0] +
                     input_array[i][1] * game[1][0] +
                     input_array[i][2] * game[2][0];
    tmp_game[i][1] = input_array[i][0] * game[0][1] +
                     input_array[i][1] * game[1][1] +
                     input_array[i][2] * game[2][1];
    tmp_game[i][2] = input_array[i][0] * game[0][2] +
                     input_array[i][1] * game[1][2] +
                     input_array[i][2] * game[2][2];
  }
  // tmp_gameからgameを生成
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      game[i][j] = tmp_game[i][j];
    }
  }
}

int judge_game(int game[3][3]) {
  // 縦横斜に同じ1,2が並んでいるか判定
  for (int i = 0; i < 3; i++) {
    if (game[i][0] == game[i][1] && game[i][1] == game[i][2] &&
        game[i][0] != 0) {
      return 1;
    } else if (game[0][i] == game[1][i] && game[1][i] == game[2][i] &&
               game[0][i] != 0) {
      return 1;
    }
    if (game[0][0] == game[1][1] && game[1][1] == game[2][2] &&
        game[0][0] != 0) {
      return 1;
    } else if (game[0][2] == game[1][1] && game[1][1] == game[2][0] &&
               game[0][2] != 0) {
      return 1;
    }
  }
  return 0;
}

char mark(int i) {
  switch (i) {
    case 1:
      return 'O';
    case 2:
      return 'X';
    default:
      return ' ';
  }
}