#include "raylib.h"
#include <stdlib.h>
#include "list.h"

#define W 1280
#define H 720
#define NW 120
#define NH 80

void draw_node(int x, int y, Node *n, Color c)
{
    /* value | next */
    DrawRectangleLinesEx((Rectangle){x, y, NW, NH}, 3, c);
    DrawLineEx((Vector2){x + 80, y}, (Vector2){x + 80, y + NH}, 3, c);
    DrawText(TextFormat("%d", n->value), x + 16, y + 22, 32, c);
    DrawCircle(x + 100, y + NH / 2, 7, n->next ? SKYBLUE : GRAY);
    DrawText(n->next ? "->" : "NULL", x + NW + 10, y + 22, 28, n->next ? WHITE : GRAY);
}

void draw_list(Node *scan, int search)
{
    int n = 0;
    for (Node *p = head; p; p = p->next) n++;

    int x = (W - n * (NW + 70) - 90) / 2;
    int y = (H - NH) / 2;

    DrawText("HEAD", x, y - 50, 28, RED);
    x += 90;

    for (Node *p = head; p; p = p->next) {
        Color c = WHITE;
        if (p == scan) c = (search == 2) ? GREEN : YELLOW; /* yellow walk, green hit */
        draw_node(x, y, p, c);
        x += NW + 70;
    }
    if (!head) DrawText("NULL", x, y + 22, 28, GRAY);
}

int main(void)
{
    InitWindow(W, H, "linked list");
    SetTargetFPS(60);
    int m = GetCurrentMonitor();
    SetWindowPosition((GetMonitorWidth(m) - W) / 2, (GetMonitorHeight(m) - H) / 2);

    int val = 10;
    insert_tail(10);
    insert_tail(20);
    insert_tail(30);

    Node *scan = NULL; /* node currently being checked */
    int search = 0;    /* 0 idle, 1 walking, 2 found, 3 miss */
    float t = 0;

    while (!WindowShouldClose()) {
        if (search != 1) {
            if (IsKeyPressed(KEY_UP)) val += 10;
            if (IsKeyPressed(KEY_DOWN) && val > 0) val -= 10;
            if (IsKeyPressed(KEY_H)) insert_head(val);
            if (IsKeyPressed(KEY_T)) insert_tail(val);
            if (IsKeyPressed(KEY_X)) delete_head();
            if (IsKeyPressed(KEY_C)) { free_list(); val = 10; search = 0; scan = NULL; }
            if (IsKeyPressed(KEY_S) && head) {
                scan = head;
                search = 1;
                t = 0;
            }
        } else {
            t += GetFrameTime();
            if (t >= 0.5f) {
                t = 0;
                if (scan->value == val) search = 2;
                else {
                    scan = scan->next;
                    if (!scan) search = 3;
                }
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("H  head    T  tail    X  delete    C  clear    S  search", 20, 20, 28, LIGHTGRAY);
        DrawText(TextFormat("value  %d    (up / down)", val), 20, 60, 28, YELLOW);
        if (search == 1) DrawText(TextFormat("searching for %d ...", val), 20, 100, 28, SKYBLUE);
        if (search == 2) DrawText(TextFormat("found %d", val), 20, 100, 28, GREEN);
        if (search == 3) DrawText(TextFormat("%d not found", val), 20, 100, 28, SKYBLUE);
        draw_list(scan, search);
        EndDrawing();
    }

    free_list();
    CloseWindow();
    return 0;
}
