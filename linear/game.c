#include <stdio.h>

//
void print_game(int game[3][3]);
char mark(int i);
void input_game(int game[3][3], int player);
int judge_game(int game[3][3]);

int main() {
  while (1) {
    // ゲームの初期化
    int counter = 0, state = 0;
    int game[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
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
    printf("もう一度プレイしますか？(y/n) ");
    scanf(" %c", &continue_game);
    if (continue_game == 'n') break;
  }
  printf("ゲームを終了します。\n");
  printf("Thank you for playing!\n");
  return 0;
}

void print_game(int game[3][3]) {
  // ゲームの描画
  printf("%d|%d|%d\n", game[0][0], game[0][1], game[0][2]);
  printf("-----\n");
  printf("%d|%d|%d\n", game[1][0], game[1][1], game[1][2]);
  printf("-----\n");
  printf("%d|%d|%d\n", game[2][0], game[2][1], game[2][2]);
}

void input_game(int game[3][3], int player) {
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
  if (game[row][col] != 0) {
    printf("無効な入力です。別の場所を選んでください。\n");
    input_game(game, player);
  }
  if (game[row][col] == 0) {
    game[row][col] = player;
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