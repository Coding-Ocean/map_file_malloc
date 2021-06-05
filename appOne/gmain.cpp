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
    //�摜�ǂݍ���
    int blockImg = loadImage("assets\\block.png");
    int itemBlockImg = loadImage("assets\\item.png");
    //�t�@�C�����J��
    const char* fileName = "assets\\map.txt";
    FILE* fp = 0;
    fopen_s(&fp, fileName, "rb");//"rb"��read binary
    WARNING(fp == 0, fileName, "�t�@�C���ǂݍ��݃G���[");
    //�t�@�C���T�C�Y�擾
    fseek(fp, 0, SEEK_END);
    int fileSize = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    //�ǂݍ��ޔz����m��
    char* map = (char*)malloc(fileSize);
    WARNING(map == 0, "�������m�ۃG���[", "");
    //�f�[�^��ǂݍ���
    fread(map, sizeof(char), fileSize, fp);
    fclose(fp);
    //�s���A�񐔂𐔂���i�Ō�̍s���K�����s���ďI����Ă��邱�Ƃ������j
    int rows = 0;
    int cols = 0;//���s�Q���������܂񂾗񐔂ɂȂ�
    int cnt = 0;
    for (int i = 0; i < fileSize; i++) {
        cnt++;
        //�s�̍Ō�̕���
        if (map[i] == '\n') {
            if (rows == 0) {
                //�ŏ��̍s�̗�
                cols = cnt;
            }
            else if (cols != cnt) {
                //�s���Ƃ̗񐔂��������G���[
                WARNING(1, "�񐔂��s����", "");
            }
            //�s�𐔂��ăJ�E���^�����Z�b�g
            rows++;
            cnt = 0;
        }
    }
    if (fileSize % cols != 0) {
        WARNING(1, "�Ō�̍s�����s���Ă��Ȃ�", "");
    }
    //�}�b�v�X�N���[���E�\���p�f�[�^
    int size = 100;//�P�̃u���b�N�T�C�Y
    float worldX = 0;//���ݕ\�����Ă��郏�[���h���W
    int dispCols = (int)width / size + 1;//�\�����ׂ���
    float worldWidth = size * (cols - 2);//���[���h�̉���
    float endWorldX = worldWidth - width;//�\���ł���Ō�̍��W
    //���C�����[�v
    hideCursor();
    while (notQuit) {
        //�X�N���[��
        worldX += 5;
        if (worldX > endWorldX)worldX = endWorldX;
        //�`��-----------------------------------------------------------
        clear();
        //�@��F�w�i
        noStroke();
        fill(60, 120, 240);
        rect(0, 0, width, height);
        //�@�}�b�v
        int startCol = (int)worldX / size;//�\���J�n��
        int endCol = startCol + dispCols;//�\���I����
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
    //�}�b�v�f�[�^�J��
    free(map);
}
#endif