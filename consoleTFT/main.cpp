#include "framework.h"

// 콘솔창 크기
const int SCREEN_WIDTH = 80;
const int SCREEN_HEIGHT = 25;

CHAR_INFO consoleBuffer[SCREEN_WIDTH * SCREEN_HEIGHT];
HANDLE hConsole;


void InitializeConsole() {
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
}

// 시작시작 = 프로그램 시작시간
chrono::steady_clock::time_point StartTime_chrono;
// 현재 시간의 이전 시간
chrono::steady_clock::time_point PrevTime_chrono;
double PrevTime;
// 현재 시간
chrono::steady_clock::time_point CurrentTime_chrono;
double CurrentTime;
// 델타 = 현재시간 - 이전시간
double DeltaTime;

void InitializeChrono()
{
    // 시간 갱신 크로노 함수 
    StartTime_chrono = chrono::high_resolution_clock::now();
    CurrentTime_chrono = StartTime_chrono;
    PrevTime_chrono = StartTime_chrono;
}

void UpdateChrono() 
{
    // 시간 갱신 크로노 함수
    CurrentTime_chrono = chrono::high_resolution_clock::now();
    DeltaTime = chrono::duration<double, chrono::milliseconds::period>(CurrentTime_chrono - PrevTime_chrono).count();
    DeltaTime /= 1000.f;
    PrevTime_chrono = CurrentTime_chrono;
    CurrentTime = chrono::duration<double, chrono::milliseconds::period>(CurrentTime_chrono - StartTime_chrono).count();
    CurrentTime /= 1000.f;
}

// 1성
// 가렌 다리우스 렉사이 말파이트 시비르 
// 아리 야스오 잭스 초가스 카직스  
// 케이틀린 코그모 고부코
// 
// 2성
// 나르 니코 럭스 리븐 세나 쉔 아트록스 
// 요릭 자이라 잔나 키아나 킨드레드 티모
//
// 3성
// 다이애나 바드 볼리베어 소라카 쓰레쉬
// 아무무 아펠리오스 알룬 요네 일라오이 
// 조이 탐켄치 트리스타나
//
// 4성
// 갈리오 노틸러스 리신 릴리아 모르가나
// 사일러스 신드라 애니 애쉬 오른 카이사 케인
// 
// 5성 
// 라칸 리산드라 세트 아지르 오공 우디르
// 이렐리아 자야 흐웨이

int money = 5;
int level = 1;
int levelCount = 0;
int LCount[10] = { 2, 4, 8 ,16, 32,64,128,256,512,1024 };

float second = 10;
char key;



void Render() {
    SMALL_RECT writeArea = { 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1 };
    WriteConsoleOutput(hConsole, consoleBuffer, { SCREEN_WIDTH, SCREEN_HEIGHT }, { 0, 0 }, &writeArea);
}

void UpdateConsoleBuffer() {
    for (int y = 0; y < SCREEN_HEIGHT; ++y) {
        for (int x = 0; x < SCREEN_WIDTH; ++x) {
            consoleBuffer[x + SCREEN_WIDTH * y].Char.AsciiChar = ' ';
            consoleBuffer[x + SCREEN_WIDTH * y].Attributes = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED;
        }
    }

    // Write your content to the console buffer here
    // For example:
    // Write "추가할 캐릭터를 넣어주세요" at position (0,0)
    // Write "Money : " + money + " Level : " + level at position (0,1)
    // Write "levelCount : " + levelCount + " / " + LCount[level] at position (0,2)
    // Write "D : 리롤 비용 2, F : 렙업 비용 4" at position (0,3)
    // Write the timer at position (0,4)
    // Write any additional content you have

    // Example:
    // Write "추가할 캐릭터를 넣어주세요" at position (0,0)
    //const char* message = "추가할 캐릭터를 넣어주세요";
    //for (int i = 0; i < strlen(message); ++i) {
    //    consoleBuffer[i].Char.AsciiChar = message[i];
    //}

    // Write the timer at position (0,0)
    std::string timer_str = std::to_string(second) + " S";
    for (int i = 0; i < timer_str.length(); ++i) {
        consoleBuffer[i + 0 * SCREEN_WIDTH].Char.AsciiChar = timer_str[i];
    }
    // Write "D : 리롤 비용 2, F : 렙업 비용 4" at position (0,1)
    const char* actions_message = "D : ReRoll, F : LevelUp";
    for (int i = 0; i < strlen(actions_message); ++i) {
        consoleBuffer[i + 1 * SCREEN_WIDTH].Char.AsciiChar = actions_message[i];
    }
    // Write "Money : " + money + " Level : " + level at position (0,2)
    std::string money_level_str = "Money : " + std::to_string(money) + " Level : " + std::to_string(level);
    for (int i = 0; i < money_level_str.length(); ++i) {
        consoleBuffer[i + 2 * SCREEN_WIDTH].Char.AsciiChar = money_level_str[i];
    }

    // Write "levelCount : " + levelCount + " / " + LCount[level] at position (0,3)
    std::string level_count_str = "levelCount : " + std::to_string(levelCount) + " / " + std::to_string(LCount[level]);
    for (int i = 0; i < level_count_str.length(); ++i) {
        consoleBuffer[i + 3 * SCREEN_WIDTH].Char.AsciiChar = level_count_str[i];
    }
}

void Update() {
   

    second -= DeltaTime;

    if (_kbhit()) {
        key = _getch();

        switch (key) {
        case 'd':
        case 'D':
            break;
        case 'f':
        case 'F':
            if (money >= 4) {
                money -= 4;
                levelCount += 4;
            }
            break;
        }
    }

    if (second < 0.0f) {
        levelCount += 2;
        second = 10.0f;
        money += 5;
        if (money / 10 != 0) {
            money += min(money / 10, 5);
        }
    }
    if (levelCount >= LCount[level]) {
        level++;
        levelCount = 0;
    }
}





 int main() {
    InitializeConsole();
    InitializeChrono();

    
    while (true) {
        UpdateChrono();
        UpdateConsoleBuffer();
        Render();
        Update();
        Sleep(50);
    }

    return 0;
}
