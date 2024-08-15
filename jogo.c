#include "raylib.h"

#define NUM_CARROS 2

typedef struct Carro {
    Rectangle rect;
    Texture2D textura;
    float velocidade;
    bool chegouLinhaChegada;
} Carro;

void gerarVelocidades(Carro carros[], int numCarros, float minVelocidade, float maxVelocidade) {
    for (int i = 0; i < numCarros; i++) {
        carros[i].velocidade = GetRandomValue(minVelocidade * 10, maxVelocidade * 10) / 20.0f;
    }
}

void DrawMenu() {

    Color textColor = BLACK;

    int fontSize = 40;

    Vector2 titlePosition = { GetScreenWidth() / 2 - MeasureText("Serious Game", fontSize) / 2, 80 };
    Vector2 startTextPosition = { GetScreenWidth() / 2 - MeasureText("Pressione a tecla espaço para começar", fontSize) / 2, 200 };
    Vector2 exitTextPosition = { GetScreenWidth() / 2 - MeasureText("Pressione a tecla ESC para sair", fontSize) / 2, 300 };

    DrawText("Serious Game", titlePosition.x, titlePosition.y, fontSize, textColor);

    DrawText("Pressione ESPAÇO para começar", startTextPosition.x, startTextPosition.y, fontSize, textColor);

    DrawText("Pressione ESC para sair", exitTextPosition.x, exitTextPosition.y, fontSize, textColor);
}

int main(void) {
    const int larguraTela = 900;
    const int alturaTela = 900;

    InitWindow(larguraTela, alturaTela, "Serious Game");

    Texture2D fundo = LoadTexture("fundo.png");

    bool menuAtivo = true;

    while (!WindowShouldClose()) {
    if (menuAtivo) {
        
        if (IsKeyPressed(KEY_SPACE)) {
            menuAtivo = false;
        }
        if (IsKeyPressed(KEY_ESCAPE)) {
            break; 
        }

        BeginDrawing();
        ClearBackground(BLUE);

            DrawTexture(fundo, 0, 0, WHITE);

            DrawMenu();

            EndDrawing();
        } else {
            Image carroImage1 = LoadImage("carro1.png");
            Image carroImage2 = LoadImage("carro2.png");

            Texture2D carroTexture1 = LoadTextureFromImage(carroImage1);
            Texture2D carroTexture2 = LoadTextureFromImage(carroImage2);

            UnloadImage(carroImage1);
            UnloadImage(carroImage2);

            Carro carros[NUM_CARROS];

            carros[0].rect = (Rectangle){0, 200, (float)carroTexture1.width, (float)carroTexture1.height}; // Carro 1
            carros[1].rect = (Rectangle){0, 550, (float)carroTexture2.width, (float)carroTexture2.height}; // Carro 2
            carros[0].textura = carroTexture1;
            carros[1].textura = carroTexture2;

            for (int i = 0; i < NUM_CARROS; i++) {
                carros[i].chegouLinhaChegada = false;
            }

            gerarVelocidades(carros, NUM_CARROS, 0.1f, 0.3f);

            while (!WindowShouldClose() && !menuAtivo) {
                for (int i = 0; i < NUM_CARROS; i++) {
                    if (!carros[i].chegouLinhaChegada) {
                        carros[i].rect.x += carros[i].velocidade;

                        if (carros[i].rect.x >= GetScreenWidth()) {
                            carros[i].chegouLinhaChegada = true;
            if (IsKeyPressed(KEY_ESCAPE)) {
                menuAtivo = true; 
                break;
            }
                        }
                    }
                }

                bool algumCarroChegou = false;
                for (int i = 0; i < NUM_CARROS; i++) {
                    if (carros[i].chegouLinhaChegada) {
                        algumCarroChegou = true;
                        break;
                    }
                }

                if (algumCarroChegou) {
                    menuAtivo = true;
                    break;
                }

                BeginDrawing();
                ClearBackground(GRAY);

                DrawTexture(fundo, 0, 0, WHITE);

                for (int i = 0; i < NUM_CARROS; i++) {
                    DrawTexture(carros[i].textura, (int)carros[i].rect.x, (int)carros[i].rect.y, WHITE);
                }

                EndDrawing();
            }

        }
    }

    UnloadTexture(fundo);

    CloseWindow();

    return 0;
}
