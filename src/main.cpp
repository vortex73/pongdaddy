#include <iostream>
#include <ostream>
#include <raylib.h>
#include <unistd.h>
#include <sys/socket.h>
 
#define PORT 8008
#define WIDTH 1000
#define HEIGHT 700
#define PADDLEH 100
#define PADDLEW 10

class Puck{
    public:
        Color color;
        double x,y;
        int movx;
        int movy;
        int r;
        void drawcric(){
            DrawCircle(x, y, r, color);
        }
        void newpos(){
            if (x>=WIDTH-r) {
                movx*=-1;
            }
            if (y>=HEIGHT-r ||y<=r ) {
                movy*=-1;
            }
            x+=movx;
            y+=movy;
        }
};

class striker{
    public:
        Color color;
        float width,height;
        float x, y;
        int mov;
        void draw(){
            DrawRectangle(x, y, width, height, color);
        }
        void newpos(){
            if (y<=0) {
                y = 0;
            }
            if (y>=HEIGHT-height) {
                y = HEIGHT-height;
            }
            if (IsKeyDown(KEY_K)) {
                y-=mov;
            }
            if (IsKeyDown(KEY_J)) {
                y+=mov;
            }
        }
};

int main (int argc, char *argv[]) {
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    std::cout << "[INFO] Starting Game" << std::endl;
    Puck ball;
    striker p1;
    striker p2;
    InitWindow(WIDTH, HEIGHT, "Multiplayer Pong");
    SetTargetFPS(60);

    p1.mov = 10;
    p1.y = HEIGHT/2;
    p1.x = 10;
    p1.color = RAYWHITE;
    p1.width = PADDLEW;
    p1.height = PADDLEH;

    p2.mov = 10;
    p2.y = HEIGHT/2;
    p2.x = WIDTH-20;
    p2.color = RAYWHITE;
    p2.width = PADDLEW;
    p2.height = PADDLEH;

    ball.color = RAYWHITE;
    ball.r = 20;
    ball.x = HEIGHT/2;
    ball.y = WIDTH/2;
    ball.movx = 10;
    ball.movy = 10;
    while (!WindowShouldClose()) {
        BeginDrawing();

        if (CheckCollisionCircleRec(Vector2{(float)ball.x,(float)ball.y}, ball.r, Rectangle{p1.x,p1.y,p1.width,p1.height})) {
            ball.movx*=-1;
        }


        p1.newpos();
        p2.draw();
        p1.draw();
        ball.newpos();
        ball.drawcric();
        Color color = {51, 51, 51, 255};
       // DrawRectangle(10, HEIGHT/2-PADDLEH/2, PADDLEW, PADDLEH, RAYWHITE);
       // DrawRectangle(WIDTH-15, HEIGHT/2-PADDLEH/2, PADDLEW, PADDLEH, RAYWHITE);
        ClearBackground(color);
        EndDrawing();
    }
    CloseWindow();
    close(sfd);
    return 0;
}