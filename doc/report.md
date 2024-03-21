# 课程设计项目一：推箱子游戏 C-Chest

## 程序运行截图

## 程序设计亮点

- 纯C语言，使用CMake构建使能多文件编译/资源文件链接；
- 基于Windows API实现显示/播放音乐；
- 通过选择性刷新解决了闪屏问题；
- 使用数组存储地图信息，基于Windows控制台对UTF－8的支持渲染地图。对于未使用新版终端的设备，我们使用汉字和符号来渲染图形。
- 使用动态分配空间的数组栈存储操作信息，实现高效的撤回操作。可在低内存下实现大于亿次的撤回。

## 程序模块示意图

![程序模块示意图](./structure.svg)

## 程序设计与实现

### 模块简析

- 菜单模块

我们将菜单模块的打印内容放在了menu.c中，便于调用。

```cpp
void Menu_ingame(int state)
{
printf("\t \u25fc菜单\n");
if(state == 0) printf("->");
printf("\t重新开始\n");
if(state == 1) printf("->");
printf("\t继续游戏\n");
if(state == 2) printf("->");
printf("\t保存游戏\n");
if(state == 3) printf("->");
printf("\t退出游戏\n");
}
```

我们使用一个state变量来决定箭头显示的位置，以此实现使用方向键来选择的功能。

在game.c中，我们实现了select()函数，通过循环控制state变量的值，并在函数中触发选择的相关事件。

```cpp
bool Select(int *sel, int row)
{
    int ch = getch();
    if(ch == 224){//Arrow
        _beginthread(&SelectBeep, 0, NULL);
        ch = getch();
        if(ch == 72) (*sel)--;
        if(ch == 80) (*sel)++;
        if((*sel) < 0) (*sel) = row-1;
        if((*sel) > row-1) (*sel) = 0;
    }
    if(ch == 13){//Enter
        _beginthread(&SelectBeep, 0, NULL);
        return true;
    }
    return false;
}
```

我们在需要出现菜单的位置循环调用select函数并检测其返回值。若返回值为真则说明发生了选择事件。那么程序就可以根据state的值进入相应的事件。

```cpp
if(ch == 27){//ESC
    int ch1 = 0;
    while(1){
        system("cls");
        Menu_ingame(ch1);
        if(Select(&ch1,4)){
            switch(ch1){
                case 0:
                    Generate_map(crt_map, crt_stage);restart
                    return 0;
                case 1:
                    return 0;//continue
                case 2:
                    Save_map(crt_map);
                    break;
                case 3:
                    return 1;//exit game
                    break;
                default:
                    break;
            }
        }
    }
}
```

- 游戏流程

在game.c中，我们实现了load()函数。该函数是游戏加载的入口。我们将在这里启动地图的加载并且处理一些数据结构的初始化。

```cpp
void Load(int stage)
```

我们希望游戏的加载是以关卡为单位，这样就可以方便地实现关卡之间跳转的功能。游戏的流程也可以通过该函数递归地执行下去。

首先我们清除历史操作记录，这使得操作记录仅在单关卡内生效。

```cpp
Stack_destroy(&history_command);
Stack_init(&history_command);
```

根据关卡的不同，我们加载不同的显示颜色。

```cpp
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
SetConsoleTextAttribute(hConsole, ground_color[stage]);
```

为了实现无需退出游戏的“重新开始”功能，我们每次加载一个关卡都会创建一份临时地图。

```cpp
int crt_map[15][15];
if(stage == -1){
    stage = farthest;
    Read_map(crt_map);
}
else Generate_map(crt_map, stage);
crt_stage = stage;
```

若从继续游戏菜单项进入游戏，则自动跳转至上次游玩的关卡。

接下来游戏进入Map_cycle函数的循环中。该函数主要进行地图和游戏信息的绘制。

```cpp
while(1){
    if(Map_cycle(crt_map)){
        SetConsoleTextAttribute(hConsole, BLACK);
        return;
    }
}
```

```cpp
bool Map_cycle(int *crt_map)
{
    printf("        关卡 %d : %s\n",crt_stagestage_name       [crt_stage]);
    bool win = true;
    for(int i = 0; i < ROW; i++){
        for(int j = 0; j < COL; j++){
            int data = *((crt_map+i*COL) + j);
            Display_data(data);
            if(data == -1 || data == -2){
                player[0] = i;
                player[1] = j;
            }
            if(data == 2) win = false;
        }
        printf("\n");
    }
    printf("      按\"方向键\" 来移动；\n     按Z键撤回上一作；     \n");
    //printf("......")....
}
```

地图从数字到图像的转换是通过在display.c中实现的Display_data来完成的。

```cpp
void Display_data(int data);
```

绘制完地图后首先检测是否胜利（在for循环中进行标记），若未胜利则进行下一帧的操作。

```cpp
if(Next_frame(crt_map)) return 1;
```

获取操作后，若可以进行移动，则使用Move函数移动玩家（对地图进行修改），并将该次操作加入历史记录，结束这一帧的判断。

```cpp
    bool Next_frame(int *crt_map)
    {
        int ch = getch();
        int addr = player[0]*COL + player[1];
        if(ch == 224){//Arrow
            ch = getch();
            if(ch == DOWN){
                if(Movable(*(crt_map+addr+COL), *(crt_m+addr  +COL*2)))         Move(addr+COLcrt_map, 0);
                else _beginthread(&FailedBeep, 0, NULL);
            }
        if(ch == UP){}//........
        }
    }
```

```cpp
void Move(int target, int *crt_map, int dir){
    Command command;
    command.dir = dir;
    command.target = target;
    //...
    Stack_push(&history_command, command);//Addcommandhistory
    crt_step[crt_stage]++;
    switch(dir){
        case 0://DOWN
            if(chest) Move_chest(crt_map, target, targe+COL);
            Move_player(crt_map, target-COL, target);
            break;
        case 1://UP
            if(chest) Move_chest(crt_map, target,target-COL);
            Move_player(crt_map, target+COL, target);
        //......
    }
}
```

移动操作完成后，Map_cycle函数会根据Next_frame的返回值向Load函数传递退出的信号。通过Next_frame使游戏胜利会被Map_cycle函数检测到，并最终递归地调用Load函数读取下一关。

```cpp
//in Map_cycle()
if(win){
    printf("         你成功了！\n   按下Enter键前往下一关\n");
    Updata_step();
    printf("  走过步数: %d, 最佳记录: %d\n", crt_ste[crt_stage], best_step[crt_stage]);
    crt_stage++;
    farthest = crt_stage;
    int ch = getch();
    if(ch == 13){//Enter
        Load(crt_stage);
        return 1;
    }
    return 1;
}
```

```cpp
//in Load()
if(Map_cycle(crt_map)){
    SetConsoleTextAttribute(hConsole, BLACK);
    return;
}
```

- 信息保存

简单来说，游戏在运行中会存储以下信息：
　　
- 当前关卡和最远关卡；当前步数和最远步数；当前地图和操作记录。它们均作为全局变量在各个文件中出现和被引用。

```cpp
//in save.c
int crt_stage;
int farthest;
int crt_step[MAX_STAGE] = {0};
int best_step[MAX_STAGE] = {0};
```

```cpp
//in game.c and so on
extern int crt_stage;
extern int farthest;
extern int crt_step[MAX_STAGE];
extern int best_step[MAX_STAGE];
```

在游戏内菜单中选择保存游戏时，程序会调用Save_map函数并在程序文件夹下生成一个存档文件，并在下次主菜单选择继续游戏时调用Load_map函数读取该存档并加载相应的变量。

- 音频效果

每次按下按键时，游戏都会发出不同的音效。这是通过定义在music.c中的Beep函数们实现的。

```cpp
void SelectBeep(const void* data) {
    UNUSED(data);
    Beep(800, 20);
    Beep(1000, 20);
    _endthread();
}
//and many other beeps...
```

我们在检测按键结束后新建一个线程以调用Beep函数，避免主线程操作被堵塞。

```cpp
//in select() prototype
if(ch == 224){//Arrow
    _beginthread(&SelectBeep, 0, NULL);
    //......
}
```

类似的，我们的游戏BGM将在一开始作为一个新线程被执行。

```cpp
//in int main()
Init_rc();
SetConsoleOutputCP(CP_UTF8);
_beginthread(GameBGM, 0, NULL);
```

### 数据结构描述

1. 地图

    使用一个全局的int型二维数组。使用宏定义来决定地图上各自数字代表元素。每份地图的大小都是15x15的正方形，玩家能够行走的地图块将被中放置在地图当中。

    ```cpp
    int map[MAX_STAGE][15][15] = {
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 8, 9, 9,
    9, 9, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 1, 1, 1, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 8, 9, 9, 1, 3, 1, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 1, 0, 1, 1, 1, 1, 9, 9, 9, 9,
    9, 9, 9, 1, 1, 1, 2, 0, 2, 3, 1, 9, 9, 9, 9,
    9, 9, 9, 1, 3, 0, 2,-1, 1, 1, 1, 9, 9, 9, 9,
    9, 9, 9, 1, 1, 1, 1, 2, 1, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 1, 3, 1, 9, 9, 9, 9, 9, 9,
    9, 8, 9, 9, 9, 9, 1, 1, 1, 9, 9, 9, 8, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 8, 9, 9, 8, 9, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    //stage 1
    //......
    ```

2. 操作记录

    使用一个栈记录一个动态分配的数组。每成功进行一次操作，程序会将家推动的目标点录入该二维数组并将其入栈。当玩家触发撤回操作时程将弹出栈顶，通过game.c中的（函数）逆操作达成撤回操作。

    ```cpp
    typedef struct {
        int target;
        int dir;
        bool chest;
    } Command;
    typedef struct {
        Command* arr;
        int top;
    } Stack;
    ```

3. Windows API句柄 HANDLE等结构体

    该类全局变量承担了设置控制台窗口相关变量（颜色、刷新等）的功能。

    ```cpp
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, ground_color[stage]);
    ```

## 开发中遇到的问题及解决办法

- 问题一：多文件编译开发

多文件编译的模块化开发形式带来的好处是显而易见的。

- 首先，你可以很快速地查找、定位到函数原型；

- 其次，使用多文件编译意味着你必须安装外部gcc库，你就能够添加其他C语言库，避免重复造轮；

- 最后，使用多文件编译也使能了协作开发。团队的各个成员可以专注开发各自负责的函数原型而不用担心在一篇cpp文件中挤成一团。

（题外话，C-Chest在[本人自建的git平台上完成开发](http://git.mflink.top/MoonFeather/C-Chest)。可惜这次课设并没有小组合作，无法进行多人协同开发。）

若要使能C语言的多文件开发，我们一般偏好使用CMake或Makefile来构建项目，C-Chest使用了CMake。我们在工作目录下放置CMakeLists.txt文件，并在其中配置项目信息。

```cmake
cmake_minimum_required(VERSION 3.5)
project(C-Chest) #项目名
aux_source_directory(. DIR_SRCS) #指定工作目录下的所有源文件
add_executable(C-Chest ${DIR_SRCS} bgm.rc) #编译生成可执行文件
#这里将bgm.rc资源文件也加入了可执行文件中。
target_link_libraries(C-Chest winmm) #将其它库链接到项目中
```

确保CMake和Make已安装，在工作环境中运行：

```bash
# Make sure you have set "CC" environment to your gccexecutable file.
cmake .
```

CMake会根据CMakeLists.txt的内容自动生成Makefile和所需资源到工目录下的build文件夹。切至build文件夹中，运行make。

```bash
make
```

程序即编译完成。

- 问题二：闪屏问题

传统的控制台程序开发中，我们使用system("cls")来清屏，然而这个操不知为何低效且缓慢，每次清屏都会造成控制台屏幕的闪烁。

针对这个问题，我们在游戏过程中禁用了system("cls")，取而代之的是下面的命令：

```cpp
//in Map_cycle() prototype
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
```

该语句并没有清空屏幕上的内容，而仅仅使用Windows 控制台API将光标的位置更新到了缓冲区的最左上方。这在减少性能损耗的同时也解决了闪屏问题。

- 问题三：撤回操作

很容易能想到，撤回操作对应的是先进后出的数据结构，也就是栈。然而存储的信息是值得商榷的。

朴素的想法是存储玩家操作之后的地图，并在撤回时将栈顶的地图还原至当前地图。

然而这种思路的问题也显而易见——高内存占用。对于50x50的地图来说，若使用这种方法，每进行一次移动操作都会增添2kb左右的内存占用。而推箱子游戏普遍的解题步数在200步左右。也就是说每张地图的栈内存消耗能够达到约5mb。若是玩家进行无意义的反复操作，这一消耗还会进一步扩大。

与精密的软件或游戏不同，推箱子这一游戏的操作具有很强的确定性且并不复杂。基于此，我们可以存储玩家的操作步骤，撤回时就将操作步骤逆转过来即可。

```cpp
//in game.c
void Undo_command(int *crt_map, Stack *s){
    Command last_command = Stack_pop(s);
    if(last_command.dir == -1) return;
    int dir = last_command.dir;
    int target = last_command.target;
    bool chest = last_command.chest;
    crt_step[crt_stage]--;
    switch(dir){
        case 0://Last time: DOWN
            Move_player(crt_map, target, target-COL);
            if(chest) Move_chest(crt_map, target+COL,target);
            break;
        case 1://Last time: UP
            Move_player(crt_map, target, target+COL);
            if(chest) Move_chest(crt_map, target-COL,target);
            break;
        case 2://Last time: LEFT
            Move_player(crt_map, target, target+1);
            if(chest) Move_chest(crt_map, target-1, target);
            break;
        case 3://Last time: RIGHT
            Move_player(crt_map, target, target-1);
            if(chest) Move_chest(crt_map, target+1, target);
            break;
        default:
            break;
    }
}
```

这样做的好处是在保证撤回操作的稳定性前提下，缓解了程序内存的使用。

## 开发感悟

这是我第一次自己从代码开始一步一步构建的一款游戏，也是我第一次使用CMake进行真正的C语言软件开发。

老实说，作为课设项目，它完全不需要拥有这么多功能。

凡尔赛的是，我用了三天写完了游戏所需的所有功能，却花了一周时间来完善它。这确实是一件很蠢的事情，但是开发这个游戏确实让我感到很开心。看到每一个功能原型从一开始的能跑变得越来越完善是一件让人很有成就感的事情。

虽然开发过程大体是开心的，但是这次开发还是让我还是觉得C语言不适合用来开发游戏。除了单片机或者老芯片这种和C语言强行绑定的平台，大部分现代人运行游戏的平台不需要用到C语言的高性能，而开发者需要面向对象特性来避免反复造轮。从这个意义上讲，使用C语言开发一款游戏是一件有点“西西弗斯”的事。
