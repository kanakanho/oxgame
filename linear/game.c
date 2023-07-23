#include <stdio.h>

//
void print_game(int game[3][3], int input_array[3][3], char key);
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

void print_game(int game[3][3], int input_array[3][3], char key) {
  // 前回のゲームの描画
  printf("     入力用       計算記号     現在の画面\n");
  printf("┏             ┓             ┏             ┓\n");
  printf("┃  %d | %d | %d  ┃             ┃  %c | %c | %c  ┃\n",
         input_array[0][0], input_array[0][1], input_array[0][2],
         mark(game[0][0]), mark(game[0][1]), mark(game[0][2]));
  printf("┃ --- --- --- ┃    ┏━━━┓    ┃ --- --- --- ┃\n");
  printf("┃  %d | %d | %d  ┃    ┃ %c ┃    ┃  %c | %c | %c  ┃\n",
         input_array[1][0], input_array[1][1], input_array[1][2], key,
         mark(game[1][0]), mark(game[1][1]), mark(game[1][2]));
  printf("┃ --- --- --- ┃    ┗━━━┛    ┃ --- --- --- ┃\n");
  printf("┃  %d | %d | %d  ┃             ┃  %c | %c | %c  ┃\n",
         input_array[2][0], input_array[2][1], input_array[2][2],
         mark(game[2][0]), mark(game[2][1]), mark(game[2][2]));
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
    for (int j = 0; i < 3; i++) {
      if (game[i][j] != 0) {
        game_check += 1;
      }
    }
  }
  print_game(game, sample_array, key);
  printf("プレイヤー%dのターンです。\n", player);
  if (game_check <= 8) {
    printf("?の計算記号を入力してください(x,+)");
    scanf(" %c", &key);
  } else
    key = 'x';
  printf("\e[1;1H\e[2J");
  // inputの処理
  switch (key) {
    case 'x':
      while (input_num <= 9) {
        print_game(game, sample_array, key);
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
      calc_x(game, input_array);
      break;
    case '+':
      while (1) {
        print_game(game, sample_array, key);
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
      break;
    default:
      printf("\e[1;1H\e[2J");
      printf("「 x 」か「 + 」を入力してください。\n");
      input_game(game, player);
  }
}

void calc_x(int game[3][3], int input_array[3][3]) {
  int tmp_game[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
  // input_arrayからgameを生成
  if (input_array[0][0] == 1 && input_array[1][1] == 1) {
    // そのまま
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        tmp_game[i][j] = game[i][j];
      }
    }
  }
  if (input_array[0][0] == 1 && input_array[1][2] == 1) {
    // 1行目→1行目、2行目→3行目、3行目→2行目
    for (int i = 0; i < 3; i++) {
      tmp_game[0][i] = game[0][i];
      tmp_game[1][i] = game[2][i];
      tmp_game[2][i] = game[1][i];
    }
  }
  if (input_array[0][1] == 1 && input_array[1][0] == 1) {
    // 1行目→2行目、2行目→1行目、3行目→3行目
    for (int i = 0; i < 3; i++) {
      tmp_game[0][i] = game[1][i];
      tmp_game[1][i] = game[0][i];
      tmp_game[2][i] = game[2][i];
    }
  }
  if (input_array[0][1] == 1 && input_array[1][2] == 1) {
    // 1行目→3行目、2行目→1行目、3行目→2行目
    for (int i = 0; i < 3; i++) {
      tmp_game[0][i] = game[2][i];
      tmp_game[1][i] = game[0][i];
      tmp_game[2][i] = game[1][i];
    }
  }
  if (input_array[0][2] == 1 && input_array[1][0] == 1) {
    // 1行目→2行目、2行目→3行目、3行目→1行目
    for (int i = 0; i < 3; i++) {
      tmp_game[0][i] = game[1][i];
      tmp_game[1][i] = game[2][i];
      tmp_game[2][i] = game[0][i];
    }
  }
  if (input_array[0][2] == 1 && input_array[1][1] == 1) {
    // 1行目→3行目、2行目→2行目、3行目→1行目
    for (int i = 0; i < 3; i++) {
      tmp_game[0][i] = game[2][i];
      tmp_game[1][i] = game[1][i];
      tmp_game[2][i] = game[0][i];
    }
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