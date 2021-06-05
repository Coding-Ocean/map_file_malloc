#define _EX

#ifdef _EX
#include"libOne.h"
void gmain() {
    window(1000, 1000);
    while (notQuit) {
    }
}
#endif

#ifdef _SAMPLE
#include"libOne.h"
void gmain() {
    window(1900, 1000, full);
    //画像読み込み
    int blockImg = loadImage("assets\\block.png");
    int itemBlockImg = loadImage("assets\\item.png");
    //ファイルを開く
    const char* fileName = "assets\\map.txt";
    FILE* fp = 0;
    fopen_s(&fp, fileName, "rb");//"rb"→read binary
    WARNING(fp == 0, fileName, "ファイル読み込みエラー");
    //ファイルサイズ取得
    fseek(fp, 0, SEEK_END);
    int fileSize = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    //読み込む配列を確保
    char* map = (char*)malloc(fileSize);
    WARNING(map == 0, "メモリ確保エラー", "");
    //データを読み込む
    fread(map, sizeof(char), fileSize, fp);
    fclose(fp);
    //行数、列数を数える（最後の行も必ず改行して終わっていることが条件）
    int rows = 0;
    int cols = 0;//改行２文字分を含んだ列数になる
    int cnt = 0;
    for (int i = 0; i < fileSize; i++) {
        cnt++;
        //行の最後の文字
        if (map[i] == '\n') {
            if (rows == 0) {
                //最初の行の列数
                cols = cnt;
            }
            else if (cols != cnt) {
                //行ごとの列数が違ったらエラー
                WARNING(1, "列数が不揃い", "");
            }
            //行を数えてカウンタをリセット
            rows++;
            cnt = 0;
        }
    }
    if (fileSize % cols != 0) {
        WARNING(1, "最後の行を改行していない", "");
    }
    //マップスクロール・表示用データ
    int size = 100;//１つのブロックサイズ
    float worldX = 0;//現在表示しているワールド座標
    int dispCols = (int)width / size + 1;//表示すべき列数
    float worldWidth = size * (cols - 2);//ワールドの横幅
    float endWorldX = worldWidth - width;//表示できる最後の座標
    //メインループ
    hideCursor();
    while (notQuit) {
        //スクロール
        worldX += 5;
        if (worldX > endWorldX)worldX = endWorldX;
        //描画-----------------------------------------------------------
        clear();
        //　空色背景
        noStroke();
        fill(60, 120, 240);
        rect(0, 0, width, height);
        //　マップ
        int startCol = (int)worldX / size;//表示開始列
        int endCol = startCol + dispCols;//表示終了列
        for (int c = startCol; c < endCol; c++) {
            float px = -worldX + size * c;
            for (int r = 0; r < rows; r++) {
                float py = size * r;
                switch (map[r * cols + c]) {
                case 'b':
                    image(blockImg, px, py);
                    break;
                case 'i':
                    image(itemBlockImg, px, py);
                    break;
                default:
                    break;
                }
            }
        }
    }
    //マップデータ開放
    free(map);
}
#endif