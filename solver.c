
#include "mouse_hal.h"
#include <stdio.h>
#include <string.h>

#define CAP (MM_MAX_SIZE * MM_MAX_SIZE)
#define INF 10000

static mm_maze_t maze;
static uint8_t walls[MM_MAX_SIZE][MM_MAX_SIZE];
static uint8_t known[MM_MAX_SIZE][MM_MAX_SIZE];
static unsigned short visits[MM_MAX_SIZE][MM_MAX_SIZE];
static int dist[MM_MAX_SIZE][MM_MAX_SIZE];
static int px, py, heading;
static const int dx[4] = {0, 1, 0, -1};
static const int dy[4] = {1, 0, -1, 0};

static int inside(int x, int y)
{
    return x >= 0 && y >= 0 && x < maze.width && y < maze.height;
}

static int goal_cell(int x, int y)
{
    return x >= maze.goal_x0 && x <= maze.goal_x1 &&
           y >= maze.goal_y0 && y <= maze.goal_y1;
}

/* Set both sides of a shared boundary, when the neighbor exists. */
static void observe(int x, int y, int d, int is_wall)
{
    int nx = x + dx[d], ny = y + dy[d];
    uint8_t b = MM_WALL(d);
    known[y][x] |= b;
    if (is_wall) {
        walls[y][x] |= b;
        mm_show_wall(x, y, d);
    } else {
        walls[y][x] &= (uint8_t)~b;
    }
    if (inside(nx, ny)) {
        int rev = (d + 2) % 4;
        uint8_t rb = MM_WALL(rev);
        known[ny][nx] |= rb;
        if (is_wall) walls[ny][nx] |= rb;
        else walls[ny][nx] &= (uint8_t)~rb;
    }
}

static void initialize_map(void)
{
    int x, y;
    memset(walls, 0, sizeof walls);
    memset(known, 0, sizeof known);
    memset(visits, 0, sizeof visits);
    for (y = 0; y < maze.height; ++y) {
        for (x = 0; x < maze.width; ++x) {
            if (y == maze.height - 1) observe(x, y, MM_NORTH, 1);
            if (x == maze.width - 1) observe(x, y, MM_EAST, 1);
            if (y == 0) observe(x, y, MM_SOUTH, 1);
            if (x == 0) observe(x, y, MM_WEST, 1);
        }
    }
    px = py = 0;
    heading = MM_NORTH;
}

static void read_walls(void)
{
    uint8_t s = mm_sense();
    observe(px, py, (heading + 3) % 4, !!(s & MM_SEE_LEFT));
    observe(px, py, heading, !!(s & MM_SEE_FRONT));
    observe(px, py, (heading + 1) % 4, !!(s & MM_SEE_RIGHT));
    visits[py][px]++;
    mm_mark(px, py, MM_COLOR_CYAN);
}

/* True for a traversable edge. In explore mode, unknown means possible. */
static int passage(int x, int y, int d, int confirmed_only)
{
    int nx = x + dx[d], ny = y + dy[d];
    uint8_t bit = MM_WALL(d);
    if (!inside(nx, ny) || (walls[y][x] & bit)) return 0;
    if (confirmed_only && !(known[y][x] & bit)) return 0;
    return 1;
}

/* Multi-source breadth-first search from destination cells. */
static void flood(int to_goal, int confirmed_only, int show_labels)
{
    int qx[CAP], qy[CAP], head = 0, tail = 0;
    int x, y, d;
    for (y = 0; y < maze.height; ++y)
        for (x = 0; x < maze.width; ++x)
            dist[y][x] = INF;

    for (y = 0; y < maze.height; ++y) {
        for (x = 0; x < maze.width; ++x) {
            if ((to_goal && goal_cell(x, y)) || (!to_goal && x == 0 && y == 0)) {
                dist[y][x] = 0;
                qx[tail] = x; qy[tail++] = y;
            }
        }
    }
    while (head < tail) {
        x = qx[head]; y = qy[head++];
        for (d = 0; d < 4; ++d) {
            int nx = x + dx[d], ny = y + dy[d];
            /* The opposite cell's edge should have matching known/wall state. */
            if (!passage(x, y, d, confirmed_only)) continue;
            if (dist[ny][nx] != INF) continue;
            dist[ny][nx] = dist[y][x] + 1;
            qx[tail] = nx; qy[tail++] = ny;
        }
    }
    if (show_labels) {
        for (y = 0; y < maze.height; ++y) {
            for (x = 0; x < maze.width; ++x) {
                char label[11];
                if (dist[y][x] == INF) mm_label(x, y, "X");
                else {
                    snprintf(label, sizeof label, "%d", dist[y][x]);
                    mm_label(x, y, label);
                }
            }
        }
    }
}

static int rotate_to(int d)
{
    int turn = (d - heading + 4) % 4;
    int request = (turn == 3) ? -1 : turn;
    if (mm_turn(request) != MM_OK) return 0;
    heading = d;
    return 1;
}

/* A blocked move updates the map instead of corrupting our position. */
static int advance(int d)
{
    mm_status_t r;
    if (!rotate_to(d)) return -1;
    r = mm_forward(1);
    if (r == MM_BLOCKED) {
        observe(px, py, d, 1);
        mm_log("unexpected wall at (%d,%d) dir=%d", px, py, d);
        return 0;
    }
    if (r != MM_OK) return -1;
    px += dx[d];
    py += dy[d];
    if (!inside(px, py)) return -1;
    return 1;
}

/* Preferred next edge for the current distance field. */
static int choose_step(int confirmed_only)
{
    int d, choice = -1, best_distance = INF, best_visits = 0x7fffffff;
    int best_turns = 100;
    for (d = 0; d < 4; ++d) {
        int nx, ny, v, turns;
        if (!passage(px, py, d, confirmed_only)) continue;
        nx = px + dx[d]; ny = py + dy[d];
        v = visits[ny][nx];
        turns = (d - heading + 4) % 4;
        if (turns == 3) turns = 1;
        if (dist[ny][nx] < best_distance ||
            (dist[ny][nx] == best_distance && v < best_visits) ||
            (dist[ny][nx] == best_distance && v == best_visits && turns < best_turns)) {
            best_distance = dist[ny][nx];
            best_visits = v;
            best_turns = turns;
            choice = d;
        }
    }
    return choice;
}

static void reset_if_requested(void)
{
    if (mm_reset_requested()) {
        px = py = 0;
        heading = MM_NORTH;
        mm_reset_done();
        mm_log("operator reset: returning position to start, retaining map");
    }
}

static int navigate(int to_goal, int confirmed_only)
{
    /* One read at each cell, plus extra attempts when discovering a blockage. */
    int limit = maze.width * maze.height * 64;
    int step;
    for (step = 0; step < limit; ++step) {
        int d, r;
        reset_if_requested();
        read_walls();
        if (to_goal ? goal_cell(px, py) : (px == 0 && py == 0)) return 1;
        flood(to_goal, confirmed_only, 1);
        if (dist[py][px] == INF) {
            mm_log("no %s route from (%d,%d)", confirmed_only ? "confirmed" : "possible", px, py);
            return 0;
        }
        d = choose_step(confirmed_only);
        if (d < 0 || dist[py + dy[d]][px + dx[d]] >= dist[py][px]) {
            mm_log("no downhill neighbor from (%d,%d)", px, py);
            return 0;
        }
        r = advance(d);
        if (r < 0) {
            mm_log("motion fault at (%d,%d)", px, py);
            return 0;
        }
    }
    mm_log("navigation safety limit reached");
    return 0;
}

static void report_map(void)
{
    int x, y;
    mm_map_begin();
    for (y = 0; y < maze.height; ++y)
        for (x = 0; x < maze.width; ++x)
            mm_map_cell(x, y, walls[y][x], known[y][x]);
    mm_map_end();
}

void solver_run(void)
{
    mm_begin("T30");
    maze = mm_maze();
    if (maze.width < 1 || maze.height < 1 ||
        maze.width > MM_MAX_SIZE || maze.height > MM_MAX_SIZE) {
        mm_log("unsupported maze size");
        return;
    }
    initialize_map();
    mm_log("starting exploration of %dx%d, goal (%d,%d)-(%d,%d)",
           maze.width, maze.height, maze.goal_x0, maze.goal_y0, maze.goal_x1, maze.goal_y1);
    if (!navigate(1, 0)) goto finish;
    mm_log("goal reached at (%d,%d), t=%lu ms", px, py, (unsigned long)mm_millis());
    if (!navigate(0, 0)) goto finish;
    mm_log("returned home, t=%lu ms", (unsigned long)mm_millis());
    if (!navigate(1, 1)) {
        mm_log("no confirmed path for speed run");
        goto finish;
    }
    mm_mark(px, py, MM_COLOR_GREEN);
    mm_log("speed run complete, t=%lu ms", (unsigned long)mm_millis());
finish:
    report_map();
}
