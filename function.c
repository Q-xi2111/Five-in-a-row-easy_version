#include <stdio.h>
#include <stdlib.h>//使用system("cls");需要包含这个头文件
#define MAPSIZE 19
int map[MAPSIZE][MAPSIZE];

int flag;
void init();//初始化
int isWin(int x, int y);//判断胜利
int playerMove(int x, int y);//玩家移动
void menuView();//菜单视图
void gameView_ShowMap();//显示游戏地图
void winView();//胜利视图

void gameView();


int main()
{
    menuView();
    return 0;
}

void init() {
    //初始化游戏地图
    int n, m;
    flag = 0;
    for (n = 0; n < 19; n++) {
        for (m = 0; m < 19; m++) {
            map[n][m] = 0;
        }
    }
}



int determine_win_row(int x, int y, int target, int array[MAPSIZE][MAPSIZE]) {
    int sum = 0;
    for (int i = 0; i < MAPSIZE; i++) {
        if (array[x - 1][i] == target) {
            sum++;
        } else {
            sum = 0;
        }
        if (sum == 5) {
            return 1;
        }
    }
    return 0;
}

int determine_win_col(int x, int y, int target, int array[MAPSIZE][MAPSIZE]) {
    int sum = 0;
    for (int i = 0; i < MAPSIZE; i++) {
        if (array[i][y - 1] == target) {
            sum++;
        } else {
            sum = 0;
        }
        if (sum == 5) {
            return 1;
        }
    }
    return 0;
}

static int checkDiagonal(int startX, int startY, int target, int dx, int dy, int array[MAPSIZE][MAPSIZE]) {
    int sum = 0;
    int x = startX;
    int y = startY;

    while (x >= 0 && x < MAPSIZE && y >= 0 && y < MAPSIZE) {
        if (array[x][y] == target) {
            sum++;
        } else {
            sum = 0;
        }
        if (sum == 5) {
            return 1;
        }
        x += dx;
        y += dy;
    }
    return 0;
}

int checkAllDiagonals(int x, int y, int target, int array[MAPSIZE][MAPSIZE]) {
    // 从左上到右下
    if (checkDiagonal(x - (y - 1), 0, target, 1, 1, array)) return 1;
    if (checkDiagonal(0, y - (x - 1), target, 1, 1, array)) return 1;

    // 从右上到左下
    if (checkDiagonal(x - (19 - y), 18, target, -1, -1, array)) return 1;
    if (checkDiagonal(19 - y + x, 19, target, -1, -1, array)) return 1;

    return 0;
}

void menuView() {
    //显示游戏的主菜单
    int a;//用于模式选择或退出
    int statu;//游戏模式
repeat:
    printf("欢迎来到五子棋游戏\n");
    printf("模式一：开始游戏\n");
    printf("模式二：游戏说明\n");
    printf("模式三：退出\n");
    printf("请选择相应的模式：");
    scanf_s("%d", &statu);
    if (statu == 1) {
        gameView();
        scanf_s("%d", &a);
        goto repeat;
    }
    else if (statu == 2) {
        printf("游戏说明：\n");
        printf("这是一个五子棋游戏，玩家轮流在棋盘上下棋，第一个连成五个相同棋子的玩家获胜。\n");
        printf("请选择相应的模式：");
        scanf_s("%d", &a);
        goto repeat;
    }
    else if (statu == 3) {
        exit(0);
    }
}


void gameView_ShowMap() {
    int i, j;
    // 打印列号
    printf("    ");  // 用于对齐
    for (i = 0; i < MAPSIZE; i++) {
        printf("%3d", i + 1);  // 列号从1开始
    }
    printf("\n");

    // 打印棋盘
    for (j = 0; j < MAPSIZE; j++) {
        printf("%3d ", j + 1);  
        for (i = 0; i < MAPSIZE; i++) {
            printf("%3d", map[j][i]);  // 打印棋盘内容
        }
        printf("\n");
    }
    printf("请输入您要下的棋子的坐标(注意坐标间隔一个空格，输入其它符号程序崩溃):");
}
   

void winView() {

    if (flag % 2 == 0) {//判断当前玩家是否获胜
        printf("黑棋获胜！\n游戏结束，按任意键返回");
    }
    else {
        printf("白棋获胜！\n游戏结束，按任意键返回");
    }
}
void gameView() {
    init();
    int x, y;
    int result;
    while (1) {
        system("cls");//清屏
        gameView_ShowMap();
        while (1) {
            scanf_s("%d %d", &x, &y);
            if (playerMove(x, y))
                break;
        }
        playerMove(x, y);//玩家移动
        //判断是否有玩家获胜
        result = isWin(x, y);
        if (result) {
            winView();
            break;
        }

    }
}
   
int isWin(int x, int y) {
    int target = (flag % 2 == 0) ? 1 : 2; // 当前玩家的棋子类型
    int result = 0;

    // 检查横行
    result = determine_win_row(x, y, target, map);
    if (result) return result;

    // 检查竖列
    result = determine_win_col(x, y, target, map);
    if (result) return result;

    // 检查对角线
    result = checkAllDiagonals(x, y, target, map);
    if (result) return result;

    return 0; // 没有获胜
}


int playerMove(int x, int y) {
    if (x > 0 && x < 20 && y>0 && y < 20) {//检查输入是否在有效范围内{
        if (map[x - 1][y - 1] == 0) {//检查该位置是否为空

            if (flag % 2) {//如果是白棋玩家的回合（flag为奇数）
                map[x - 1][y - 1] = 2;
                flag++;
            }
            else {
                map[x - 1][y - 1] = 1;
                flag++;
            }
        }
        else {
            printf("该位置已经被占用\n");
            printf("请重新输入坐标：");
        }
    }
    else {
        printf("无效的输入\n");
        printf("请重新输入坐标：");
    }
}
