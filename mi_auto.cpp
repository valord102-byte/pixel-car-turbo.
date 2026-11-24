#include "raylib.h"

int main() {
    // 1. Abrir ventana de 800x600 píxeles
    InitWindow(800, 600, "Mi Primer Pixel Car");
    SetTargetFPS(60);

    // Variables del jugador, carretera, enemigos y estado del juego
    int autoX = 375;
    int autoY = 450;
    int lineaY = 0;

    // Enemigo 1 (Azul)
    int enemigoX = 250;
    int enemigoY = -100;

    // Enemigo 2 (Amarillo - empieza más arriba para que no bajen pegados)
    int enemigo2X = 480;
    int enemigo2Y = -420;

    int puntos = 0;
    int vidas = 3;

    // 2. Bucle principal del juego
    while (!WindowShouldClose()) {
        
        // SI TIENES VIDAS, EL JUEGO AVANZA NORMALMENTE
        if (vidas > 0) {
            // Controles del jugador
            if (IsKeyDown(KEY_RIGHT)) autoX += 5;
            if (IsKeyDown(KEY_LEFT))  autoX -= 5;
            if (IsKeyDown(KEY_UP))    autoY -= 5;
            if (IsKeyDown(KEY_DOWN))  autoY += 5;

            // Límites de la carretera
            if (autoX < 200) autoX = 200;
            if (autoX > 550) autoX = 550;
            if (autoY < 0)   autoY = 0;
            if (autoY > 520) autoY = 520;

            // Movimiento de la línea blanca
            lineaY += 8 + (puntos / 20);
            if (lineaY > 600) lineaY = -100;

            // Movimiento del Enemigo 1 (Azul)
            enemigoY += 6 + (puntos / 20);
            if (enemigoY > 600) {
                enemigoY = -100;
                enemigoX = GetRandomValue(210, 360); // Carril izquierdo
                puntos += 10;
            }

            // Movimiento del Enemigo 2 (Amarillo)
            enemigo2Y += 7 + (puntos / 20);
            if (enemigo2Y > 600) {
                enemigo2Y = -150;
                enemigo2X = GetRandomValue(390, 540); // Carril derecho
                puntos += 10;
            }

            // Detección de choques
            Rectangle rectJugador  = { (float)autoX, (float)autoY, 50, 80 };
            Rectangle rectEnemigo1 = { (float)enemigoX, (float)enemigoY, 50, 80 };
            Rectangle rectEnemigo2 = { (float)enemigo2X, (float)enemigo2Y, 50, 80 };

            // Si chocas con el Azul
            if (CheckCollisionRecs(rectJugador, rectEnemigo1)) {
                vidas -= 1;
                enemigoY = -100;
                enemigoX = GetRandomValue(210, 360);
            }

            // Si chocas con el Amarillo
            if (CheckCollisionRecs(rectJugador, rectEnemigo2)) {
                vidas -= 1;
                enemigo2Y = -200;
                enemigo2X = GetRandomValue(390, 540);
            }
        } 
        // SI TE QUEDASTE SIN VIDAS (GAME OVER), ESPERA A QUE PRESIONES ENTER
        else {
            if (IsKeyPressed(KEY_ENTER)) {
                vidas = 3;
                puntos = 0;
                autoX = 375;
                autoY = 450;
                enemigoY = -100;
                enemigo2Y = -420;
            }
        }

        // 3. Dibujar en pantalla
        BeginDrawing();
            ClearBackground(DARKGREEN);
            DrawRectangle(200, 0, 400, 600, DARKGRAY);
            DrawRectangle(395, lineaY, 10, 80, WHITE);
            DrawRectangle(50, 100, 120, 200, GRAY);

            // Auto del jugador (Rojo)
            DrawRectangle(autoX, autoY, 50, 80, RED);
            DrawRectangle(autoX + 8, autoY + 15, 34, 15, SKYBLUE);
            DrawRectangle(autoX + 48, autoY + 12, 8, 18, BLACK);
            DrawRectangle(autoX - 6, autoY + 12, 8, 18, BLACK);
            DrawRectangle(autoX - 6, autoY + 52, 8, 18, BLACK);
            DrawRectangle(autoX + 48, autoY + 52, 8, 18, BLACK);

            // Auto Enemigo 1 (Azul)
            DrawRectangle(enemigoX, enemigoY, 50, 80, BLUE);
            DrawRectangle(enemigoX + 8, enemigoY + 50, 34, 15, SKYBLUE);
            DrawRectangle(enemigoX + 48, enemigoY + 12, 8, 18, BLACK);
            DrawRectangle(enemigoX - 6, enemigoY + 12, 8, 18, BLACK);
            DrawRectangle(enemigoX - 6, enemigoY + 52, 8, 18, BLACK);
            DrawRectangle(enemigoX + 48, enemigoY + 52, 8, 18, BLACK);

            // Auto Enemigo 2 (Amarillo)
            DrawRectangle(enemigo2X, enemigo2Y, 50, 80, GOLD);
            DrawRectangle(enemigo2X + 8, enemigo2Y + 50, 34, 15, BLACK);
            DrawRectangle(enemigo2X + 48, enemigo2Y + 12, 8, 18, BLACK);
            DrawRectangle(enemigo2X - 6, enemigo2Y + 12, 8, 18, BLACK);
            DrawRectangle(enemigo2X - 6, enemigo2Y + 52, 8, 18, BLACK);
            DrawRectangle(enemigo2X + 48, enemigo2Y + 52, 8, 18, BLACK);

            // Marcador de Puntos y Vidas
            DrawText(TextFormat("PUNTOS: %i", puntos), 20, 20, 25, YELLOW);
            DrawText(TextFormat("VIDAS: %i", vidas), 20, 55, 25, RED);

            // Pantalla de GAME OVER encima de todo cuando vidas == 0
            if (vidas <= 0) {
                DrawRectangle(150, 200, 500, 200, Fade(BLACK, 0.85f));
                DrawText("GAME OVER", 275, 230, 40, RED);
                DrawText(TextFormat("Puntaje Final: %i", puntos), 285, 290, 25, WHITE);
                DrawText("Presiona ENTER para jugar de nuevo", 205, 340, 20, YELLOW);
            }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
