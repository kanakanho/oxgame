#include <stdio.h>
#include <string.h>

#define Red "\e[31m"
#define Green "\e[32m"
#define Cyan "\e[36m"
#define Reset "\e[0m"
#define Bold "\e[1m"
#define BackWhite "\e[47m"

// プロトタイプ宣言
void print_game(int game[3][3], int input_array[3][3], char key, int input_num);
char mark(int i);
void input_game(int game[3][3], int player);
void input_x(int game_check, int input, int input_array[3][3], int game[3][3],
             char key, int first_count, int player);
void input_plus(int game[3][3], int input, int input_array[3][3], char key,
                int player);
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
      }

      // カウンターの更新
      counter++;
    }
    // ゲーム終了時の処理
    char continue_game = 'n';
    printf("もう一度プレイしますか？(y/n) ");
    scanf(" %c", &continue_game);
    if (continue_game == 'n') break;
  }
  // ゲームの終了
  printf("\e[1;1H\e[2J");
  printf("ゲームを終了します。\n");
  printf("Thank you for playing!\n");
  return 0;
}

// ゲーム画面の描画する関数
void print_game(int game[3][3], int input_array[3][3], char key,
                int input_num) {
  // 色の設定
  char color[10] = {"\0"};
  if (key == 'x')
    strcpy(color, Red);
  else if (key == '+')
    strcpy(color, Green);
  else
    strcpy(color, BackWhite);

  // ゲームの描画

  // 表題の描画
  printf("     入力用        計算記号      現在の画面\n");

  // 1行目の描画
  printf("┏━           ━┓\n");
  printf("┃ ");
  for (int i = 0; i < 3; i++) {
    printf("%s %d %s", input_array[0][i] == input_num ? BackWhite : "",
           input_array[0][i], input_array[0][i] == input_num ? Reset : "");
    if (i != 2)
      printf("%s┃%s", Cyan, Reset);
    else
      printf(" %s┃\n", Reset);
  }
  printf("┃ %s━━━ ━━━ ━━━%s ┃\n", Cyan, Reset);
  printf("┃ ");
  // 入力用の描画
  for (int i = 0; i < 3; i++) {
    printf("%s %d %s", input_array[1][i] == input_num ? BackWhite : "",
           input_array[1][i], input_array[1][i] == input_num ? Reset : "");
    if (i != 2)
      printf("%s┃%s", Cyan, Reset);
    else
      printf(" %s┃\n", Reset);
  }
  printf("┃ %s━━━ ━━━ ━━━%s ┃\n", Cyan, Reset);
  printf("┃ ");
  // 入力用の描画
  for (int i = 0; i < 3; i++) {
    printf("%s %d %s", input_array[2][i] == input_num ? BackWhite : "",
           input_array[2][i], input_array[2][i] == input_num ? Reset : "");
    if (i != 2)
      printf("%s┃%s", Cyan, Reset);
    else
      printf(" %s┃\n", Reset);
  }
  printf("┗━           ━┛\n");
  // カーソルの移動
  printf("\e[5A\e[20C");
  printf("┏━━━┓\n");
  printf("\e[20C");
  printf("┃%s%s %c %s┃\n", color, Bold, key, Reset);
  printf("\e[20C");
  printf("┗━━━┛\n");

  // カーソルの移動
  printf("\e[5A\e[30C");

  printf("┏━           ━┓\n");
  printf("\e[30C");
  printf("┃  ");
  // 現在の画面の描画
  for (int i = 0; i < 3; i++) {
    printf("%s%s%c%s ", game[0][i] ? Bold : "", game[0][i] == 1 ? Red : "",
           mark(game[0][i]), game[0][i] ? Reset : "");
    if (i != 2)
      printf("%s┃%s ", Cyan, Reset);
    else
      printf(" %s┃\n", Reset);
  }
  printf("\e[30C");
  printf("┃ %s━━━ ━━━ ━━━%s ┃\n", Cyan, Reset);
  printf("\e[30C");
  printf("┃  ");
  // 現在の画面の描画
  for (int i = 0; i < 3; i++) {
    printf("%s%s%c%s ", game[1][i] ? Bold : "", game[1][i] == 1 ? Red : "",
           mark(game[1][i]), game[1][i] ? Reset : "");
    if (i != 2)
      printf("%s┃%s ", Cyan, Reset);
    else
      printf(" %s┃\n", Reset);
  }
  printf("\e[30C");
  printf("┃ %s━━━ ━━━ ━━━%s ┃\n", Cyan, Reset);
  printf("\e[30C");
  printf("┃  ");
  // 現在の画面の描画
  for (int i = 0; i < 3; i++) {
    printf("%s%s%c%s ", game[2][i] ? Bold : "", game[2][i] == 1 ? Red : "",
           mark(game[2][i]), game[2][i] ? Reset : "");
    if (i != 2)
      printf("%s┃%s ", Cyan, Reset);
    else
      printf(" %s┃\n", Reset);
  }
  printf("\e[30C");
  printf("┗━           ━┛\n");
}

// 入力を受け付け、処理する関数
void input_game(int game[3][3], int player) {
  // 入力の処理
  // 変数の宣言と初期化
  int game_check = 0;
  int input = 0;
  int input_array[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
  int sample_array[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  int first_count = 0;
  char key = '?';
  // 計算記号の決定
  print_game(game, sample_array, key, input);
  // playerの色の設定
  char color[10] = {"\0"};
  if (player == 1)
    strcpy(color, Red);
  else if (player == 2)
    strcpy(color, Reset);
  printf("\e[1m%s%c\e[0m のターンです。\n", color, mark(player));
  // gameに空きがあるか確認
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (game[i][j] != 0) game_check += 1;
    }
  }
  // 空きがない場合の処理
  if (game_check < 9) {
    printf("?の計算記号を入力してください(x,+)");
    scanf(" %c", &key);
  } else {
    key = 'x';
  }
  printf("\e[1;1H\e[2J");
  // それぞれの計算記号毎の処理
  switch (key) {
    case 'x':
      input_x(game_check, input, input_array, game, key, first_count, player);
      break;
    case '+':
      input_plus(game, input, input_array, key, player);
      break;
    default:
      // 不正な入力の処理
      printf("\e[1;1H\e[2J");
      printf("「 x  」か「 +  」を入力してください。\n");
      input_game(game, player);
  }
}

void input_x(int game_check, int input, int input_array[3][3], int game[3][3],
             char key, int first_count, int player) {
  int input_num = 1;
  int sample_array[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  while (input_num <= 9) {
    // gameに空きがない場合の処理
    if (game_check == 9)
      printf(
          "新たに入力するスペースがないため「x "
          "」が選択されました。\n");
    // 値の入力
    print_game(game, sample_array, key, input_num);
    printf("%dに入力したい数字を入力してください(0,1)", input_num);
    scanf("%d", &input);
    // 不正な入力の処理
    // 入力ミスの処理
    if (input != 0 && input != 1) {
      printf("\e[1;1H\e[2J");
      printf("0か1の数字を入力してください。\n");
      continue;
    }
    // 1の過多の処理
    if (first_count > 3) {
      printf("\e[1;1H\e[2J");
      printf("1は3つまでしか入力できません。\n");
      continue;
    }
    // input_numから行列の生成
    int x = (input_num - 1) % 3;
    int y = (input_num - 1) / 3;
    switch (input) {
      // そのまま反映
      case 0:
        input_array[y][x] = 0;
        break;
      case 1:
        // 不正な入力の処理
        // 既に1が入力されている場合の処理
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
        // 入力の反映
        input_array[y][x] = 1;
        first_count++;
        break;
      default:
        break;
    }
    // input_numの更新
    input_num++;
    printf("\e[1;1H\e[2J");
  }
  // 不正な入力の処理
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
  // gameの生成
  calc_x(game, input_array);
}

void input_plus(int game[3][3], int input, int input_array[3][3], char key,
                int player) {
  int sample_array[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  while (1) {
    // 値の入力
    print_game(game, sample_array, key, input);
    printf("%cを入力する場所の数字を1~9から選んで入力してください。",
           mark(player));
    scanf("%d", &input);
    // 不正な入力の処理
    // 入力ミスの処理
    if (input < 1 || input > 9) {
      printf("\e[1;1H\e[2J");
      printf("1~9の数字を入力してください。\n");
      continue;
    }
    // 既に入力されている場所の処理
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
}

// key = 'x' の場合の gameの生成を行う関数
void calc_x(int game[3][3], int input_array[3][3]) {
  // 変数の初期化
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

// 勝敗の判定を行う関数
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

// 1,2をO,Xに変換する関数
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