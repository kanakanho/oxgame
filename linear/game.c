#include <stdio.h>

//
void print_game(int game[3][3][3]);
char mark(int i);
void input_game(int game[3][3][3], int player);
int judge_game(int game[3][3][3]);

int main() {
  while (1) {
    // ゲームの初期化
    int counter = 0;
    int state = 0;
    int game[3][3][3] = {{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
                         {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
                         {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}};
    // ゲームの実行
    while (state == 0) {
      // プレイヤーの判定
      int player = counter % 2 + 1;

      // ゲームの描画
      print_game(game);

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
    printf("もう一度プレイしますか？(y/n)\n");
    scanf("%c", &continue_game);
    if (continue_game == 'n') {
      break;
    }
  }
  return 0;
}

void print_game(int game[3][3][3]) {
  // ゲームの描画
  for (int i = 0; i < 3; i++) {
    printf("%d|%d|%d\n", game[i][0][0], game[i][0][1], game[i][0][2]);
    printf("-----\n");
    printf("%d|%d|%d\n", game[i][1][0], game[i][1][1], game[i][1][2]);
    printf("-----\n");
    printf("%d|%d|%d\n", game[i][2][0], game[i][2][1], game[i][2][2]);
    switch (i) {
      case 0:
        printf("top\n");
        break;
      case 1:
        printf("mid\n");
        break;
      case 2:
        printf("bottom\n");
        break;
      default:
        break;
    }
  }
}

void input_game(int game[3][3][3], int player) {
  // 入力の処理
  int input = 0;
  printf("プレイヤー%dのターンです。どこに置きますか？\n", player);
  printf("1|2|3\n");
  printf("-----\n");
  printf("4|5|6\n");
  printf("-----\n");
  printf("7|8|9\n");
  scanf("%d", &input);
  // 入力ミスの判定
  if (input < 1 || input > 9) {
    printf("無効な入力です。1~9の数字を入力してください。\n");
    input_game(game, player);
  }
  // 入力の処理
  int row = (input - 1) / 3;
  int col = (input - 1) % 3;
  // 入力ミスの判定
  if (game[0][row][col] != 0) {
    printf("無効な入力です。別の場所を選んでください。\n");
    input_game(game, player);
  }
  // 配列に入力
  for (int i = 2; i >= 0; i--) {
    if (game[i][row][col] == 0) {
      game[i][row][col] = player;
      break;
    }
  }
}

int judge_game(int game[3][3][3]) {
  // 縦横斜に同じ1,2が並んでいるか
  for (int i = 1; i <= 2; i++) {
    for (int n = 0; n < 3; n++) {
      if (game[n][0][0] == i && game[n][0][1] == i && game[n][0][2] == i &&
          game[n][0][0] != 0)
        return i;
      if (game[n][1][0] == i && game[n][1][1] == i && game[n][1][2] == i &&
          game[n][1][0] != 0)
        return i;
      if (game[n][2][0] == i && game[n][2][1] == i && game[n][2][2] == i &&
          game[n][2][0] != 0)
        return i;
      if (game[n][0][0] == i && game[n][1][0] == i && game[n][2][0] == i &&
          game[n][0][0] != 0)
        return i;
      if (game[n][0][1] == i && game[n][1][1] == i && game[n][2][1] == i &&
          game[n][0][1] != 0)
        return i;
      if (game[n][0][2] == i && game[n][1][2] == i && game[n][2][2] == i &&
          game[n][0][2] != 0)
        return i;
      if (game[n][0][0] == i && game[n][1][1] == i && game[n][2][2] == i &&
          game[n][0][0] != 0)
        return i;
      if (game[n][0][2] == i && game[n][1][1] == i && game[n][2][0] == i &&
          game[n][0][2] != 0)
        return i;
      if (game[0][0][n] == i && game[0][1][n] == i && game[0][2][n] == i &&
          game[0][0][n] != 0)
        return i;
      if (game[1][0][n] == i && game[1][1][n] == i && game[1][2][n] == i &&
          game[1][0][n] != 0)
        return i;
      if (game[2][0][n] == i && game[2][1][n] == i && game[2][2][n] == i &&
          game[2][0][n] != 0)
        return i;
      if (game[0][0][n] == i && game[1][1][n] == i && game[2][2][n] == i &&
          game[0][0][n] != 0)
        return i;
      if (game[0][2][n] == i && game[1][1][n] == i && game[2][0][n] == i &&
          game[0][2][n] != 0)
        return i;
      if (game[0][n][0] == i && game[1][n][1] == i && game[2][n][2] == i &&
          game[0][n][0] != 0)
        return i;
      if (game[0][n][2] == i && game[1][n][1] == i && game[2][n][0] == i &&
          game[0][n][2] != 0)
        return i;
      if (game[0][0][0] == i && game[1][1][1] == i && game[2][2][2] == i &&
          game[0][0][0] != 0)
        return i;
      if (game[0][0][2] == i && game[1][1][1] == i && game[2][2][0] == i &&
          game[0][0][2] != 0)
        return i;
      if (game[0][2][0] == i && game[1][1][1] == i && game[2][0][2] == i &&
          game[0][2][0] != 0)
        return i;
      if (game[0][2][2] == i && game[1][1][1] == i && game[2][0][0] == i &&
          game[0][2][2] != 0)
        return i;
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