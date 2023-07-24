#include <stdio.h>
#include <string.h>

#define RED "\e[31m"
#define GREEN "\e[32m"
#define CYAN "\e[36m"
#define RESET "\e[0m"
#define BOLD "\e[1m"
#define BG_WHITE "\e[47m"

#define CLEAR() printf("\e[2J")
#define MOVE(x, y) printf("\e[%d;%dH", (y), (x))

// プロトタイプ宣言
void finGame();
void startGame();
void operationSelect(int board[3][3]);
void selectedX(int isFull, int input, int inputArr[3][3], int board[3][3],
               char key);
void selectedPls(int board[3][3], char key);

int player = 1;

int main() {
  // ゲームを開始する
  startGame();

  // ゲームの終了
  finGame();

  return 0;
}

// ターミナルをクリアする
void clearTerm() {
  MOVE(1, 1);
  CLEAR();
}

// key = 'x' の場合の board の生成を行う関数
void calc(int board[3][3], int in[3][3]) {
  int tmp[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

  // 行列計算をする
  for (int i = 0; i < 3; i++) {
    tmp[i][0] = in[i][0] * board[0][0] + in[i][1] * board[1][0] +
                in[i][2] * board[2][0];

    tmp[i][1] = in[i][0] * board[0][1] + in[i][1] * board[1][1] +
                in[i][2] * board[2][1];

    tmp[i][2] = in[i][0] * board[0][2] + in[i][1] * board[1][2] +
                in[i][2] * board[2][2];
  }

  // tmp を board に置き換える
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      board[i][j] = tmp[i][j];
    }
  }
}

// 1,2をO,Xに変換する関数
char getMark(int i) {
  switch (i) {
    case 1:
      return 'O';

    case 2:
      return 'X';

    default:
      return ' ';
  }
}

// 演算子に対応する色を取得
char* getOpeColor(char ope) {
  switch (ope) {
    case 'x':
      return RED;

    case '+':
      return GREEN;

    default:
      return BG_WHITE;
  }
}

// 横線を引く
void printLine(int isNewline) {
  printf("┃ %s━━━ ━━━ ━━━%s ┃", CYAN, RESET);
  if (isNewline) printf("\n");
}

// 入力用のボードを横一列表示する
void printInputBoardLine(int inputArr[3][3], int curtPos, int col) {
  printf("┃ ");
  for (int i = 0; i < 3; i++) {
    char* bgColor = curtPos - col * 3 == inputArr[0][i] ? BG_WHITE : "";
    int n = inputArr[col][i];
    printf("%s %d " RESET, bgColor, n);

    if (i != 2) printf(CYAN "┃" RESET);
  }
}

// 現在の画面のボードを横一列表示する
void printCurrentBoardLine(int board[3][3], int col) {
  for (int i = 0; i < 3; i++) {
    char* fontStyle = board[col][i] ? BOLD : "";
    char* fontColor = board[col][i] == 1 ? RED : "";
    char mark = getMark(board[col][i]);
    printf("%s%s%c " RESET, fontStyle, fontColor, mark);

    if (i != 2)
      printf(CYAN "┃ " RESET);
    else
      printf(RESET " ┃");
  }
}

// ゲーム画面の描画する
void printBoard(int board[3][3], int inputArr[3][3], char ope, int curtPos) {
  // 色の設定
  char opeColor[10] = {"\0"};
  strcpy(opeColor, getOpeColor(ope));

  // ヘッダー
  printf("     入力用       計算記号     現在の画面\n");
  printf("┏━           ━┓             ┏━           ━┓\n");

  // 2行目の描画
  printInputBoardLine(inputArr, curtPos, 0);
  printf(" ┃             ┃  ");
  printCurrentBoardLine(board, 0);
  printf("\n");

  // 3行目の描画
  printLine(0);
  printf("    ┏━━━┓    ");
  printLine(1);

  // 4行目の描画
  printInputBoardLine(inputArr, curtPos, 1);
  printf(" ┃    ┃%s%s %c %s┃    ┃  ", opeColor, BOLD, ope, RESET);
  printCurrentBoardLine(board, 1);
  printf("\n");

  // 5行目の描画
  printLine(0);
  printf("    ┗━━━┛    ");
  printLine(1);

  // 6行目の描画
  printInputBoardLine(inputArr, curtPos, 2);
  printf(" ┃             ┃  ");
  printCurrentBoardLine(board, 2);
  printf("\n");

  // 7行目の描画
  printf("┗━           ━┛             ┗━           ━┛\n");
}

// 入力が 0, 1 かどうか
int isZeroOrOne(int n) { return n == 0 || n == 1; };

// プレイヤーの色を取得
char* getPlayerColor() {
  if (player == 1)
    return RED;
  else
    return RESET;
}

// ボードに空きがあるか
int countOne(int board[3][3]) {
  int count = 0;

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (board[i][j] != 0) {
        count++;
      }
    }
  }
  return count;
}

// 入力を受け付け、処理する関数
void operationSelect(int board[3][3]) {
  // 入力の処理
  // 変数の宣言と初期化
  int isFull = 0;
  int input = 0;
  int inputArr[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
  int defaultArr[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  char key = '?';

  // playerの色の設定
  char* opeColor[10] = {"\0"};
  *opeColor = getPlayerColor();
  printf(BOLD "%s%c%s のターンです。\n", *opeColor, getMark(player), RESET);

  if (countOne(board) == 9) {  // 盤面に空きが ない 場合
    key = 'x';
  } else {  // 盤面に空きが ある 場合
    printf("?の計算記号を入力してください(x,+)");
    scanf(" %c", &key);
  }

  clearTerm();

  // それぞれの計算記号毎の処理
  switch (key) {
    case 'x':
      selectedX(isFull, input, inputArr, board, key);
      calc(board, inputArr);
      break;

    case '+':
      selectedPls(board, key);
      break;

    default:  // 不正な入力の処理
      getchar();
      printf("「 x  」か「 +  」を入力してください。\n");
      printBoard(board, defaultArr, '?', 0);
      operationSelect(board);
      break;
  }
}

// x が選択された時の処理
void selectedX(int isFull, int input, int inArr[3][3], int board[3][3],
               char key) {
  int curtPos = 1;
  int defaultArr[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

  while (curtPos <= 9) {
    // 盤面に空きがない場合
    if (isFull == 9)
      printf("新たに入力するスペースがないため「x」が選択されました。\n");

    // 値の入力
    printBoard(board, defaultArr, key, curtPos);
    printf("%dに入力したい数字を入力してください(0,1)", curtPos);
    scanf("%d", &input);

    // 不正な入力, 入力ミス
    if (isZeroOrOne(input) == 0) {
      getchar();
      clearTerm();
      printf("0か1の数字を入力してください。\n");
      continue;
    }

    // 1が3つ以上ある場合
    if (countOne(inArr) > 3) {
      clearTerm();
      printf("1は3つまでしか入力できません。\n");
      continue;
    }

    // 現在位置から行列の生成
    int row = (curtPos - 1) % 3;
    int col = (curtPos - 1) / 3;
    if (input == 0) {
      inArr[col][row] = 0;
    } else {
      // 同じ列, 行にすでに 1 がないか
      clearTerm();
      if (inArr[col][0] || inArr[col][1] || inArr[col][2]) {
        printf("同じ列に1は1つまでしか入力できません。\n");
        continue;
      } else if (inArr[0][row] || inArr[1][row] || inArr[2][row]) {
        printf("同じ行に1は1つまでしか入力できません。\n");
        continue;
      } else {
        inArr[col][row] = 1;
      }
    }

    // 次の位置に移動
    curtPos++;
    clearTerm();
  }

  // 不正な入力の処理
  // input_arryの値が全ての0の時の処理
  int haveOne = 0;
  for (int i = 0; i < 3; i++) {
    for (int n = 0; n < 3; n++) {
      haveOne += inArr[i][n];
    }
  }
  if (haveOne == 0) {
    printf("最低でも1つは1を選んでください。\n");
    printBoard(board, defaultArr, '?', 0);
    operationSelect(board);
  }
}

// + が選択された時の処理
void selectedPls(int board[3][3], char key) {
  int defaultArr[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  int input = 0;
  while (1) {
    // 値の入力
    printBoard(board, defaultArr, key, 0);
    printf("%cを入力する場所の数字を1~9から選んで入力してください。",
           getMark(player));
    scanf(" %d", &input);
    // 不正な入力の処理
    // 入力ミスの処理
    if (input < 1 || input > 9) {
      clearTerm();
      printf("1~9の数字を入力してください。\n");
      getchar();
      continue;
    }
    // 既に入力されている場所の処理
    int x = (input - 1) % 3;
    int y = (input - 1) / 3;
    if (board[y][x] != 0) {
      clearTerm();
      printf("その場所に入力することはできません。\n");
      continue;
    }
    break;
  }

  // board に代入
  int x = (input - 1) % 3;
  int y = (input - 1) / 3;
  board[y][x] = player;
  clearTerm();
}

// 勝敗が付いているか判定を行う関数
int getIsFinish(int game[3][3]) {
  // 縦横斜に同じ1,2が並んでいるか判定
  for (int i = 0; i < 3; i++) {
    if (game[i][0] == game[i][1] && game[i][1] == game[i][2] &&
        game[i][0] != 0) {
      return 1;
    } else if (game[0][i] == game[1][i] && game[1][i] == game[2][i] &&
               game[0][i] != 0) {
      return 1;
    }
  }

  if (game[0][0] == game[1][1] && game[1][1] == game[2][2] && game[0][0] != 0) {
    return 1;
  } else if (game[0][2] == game[1][1] && game[1][1] == game[2][0] &&
             game[0][2] != 0) {
    return 1;
  }
  return 0;
}

// ゲームを終了する
void finGame() {
  clearTerm();
  printf("ゲームを終了します。\n");
  printf("Thank you for playing!\n");
}

// ゲームを開始する
void startGame() {
  char isContinue = 'y';
  do {
    // ゲームの初期化
    int counter = 0;
    int isFin = 0;
    int board[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

    // ゲームの実行
    clearTerm();

    while (!isFin) {
      // プレイヤーの指定
      player = counter % 2 + 1;
      counter++;

      // 画面を描画
      int defaultArr[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
      printBoard(board, defaultArr, '?', 0);

      // 入力の処理
      operationSelect(board);

      // 勝敗の判定
      isFin = getIsFinish(board);
      if (isFin) {
        printf("プレイヤー%dの勝利です!\n", player);
        break;
      }
    }

    // ゲーム終了時の処理
    printf("もう一度プレイしますか？(y/n) ");
    scanf(" %c", &isContinue);
  } while (isContinue == 'y');
}
