#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

size_t X;
size_t Y;
char ** b;
char ** r;
char ** nv;
char ** p;

char ** allocate() {
    char ** m;
    m = malloc(sizeof(char*) * X);
    for (size_t x = 0; x < X; x++) {
        m[x] = malloc(Y);
    }
    return m;
}

void dealloc(char ** m) {
    for (size_t x = 0; x < X; x++) {
        free(m[x]);
    }
    free(m);
}

void set(char ** m, char val) {
    for (size_t x = 0; x < X; x++) {
        for (size_t y = 0; y < Y; y++) {
            m[x][y] = val;
        }
    }
}
void gen(size_t x, size_t y);
void left(size_t x, size_t y) {
    r[x-1][y] = 0;
    gen(x-1, y);
}
void right(size_t x, size_t y) {
    r[x][y] = 0;
    gen(x+1, y);
}
void up(size_t x, size_t y) {
    b[x][y] = 0;
    gen(x, y+1);
}
void down(size_t x, size_t y) {
    b[x][y-1] = 0;
    gen(x, y-1);
}

void gen(size_t x, size_t y) {
    nv[x][y] = 0;
    void (*options[4])(size_t, size_t);
    int count = 0;
    if (x-1 < X && (nv[x-1][y] || rand() % 50 == 0)) options[count++] = left;
    if (x+1 < X && (nv[x+1][y] || rand() % 50 == 0)) options[count++] = right;
    if (y-1 < Y && (nv[x][y-1] || rand() % 50 == 0)) options[count++] = down;
    if (y+1 < Y && (nv[x][y+1] || rand() % 50 == 0)) options[count++] = up;
    if (count) {
        options[rand() % count](x, y);
        if (count > 1) gen(x, y);
    }
}

void add_wall(FILE * out, double x, double y, size_t id, double r) {
    fprintf(out, "<StaticObject CastShadows=\"true\" Collides=\"true\" FileIndex=\"0\" Group=\"0\" ID=\"%ld\" Name=\"wall_%ld\" Rotation=\"0 %lf 0\" Scale=\"1 1 1\" Tag=\"\" WorldPos=\"%lf 0 %lf\" />\n", id, id, r, x, y);
}

void add_pillar(FILE * out, double x, double y, size_t id) {
    fprintf(out, "<StaticObject CastShadows=\"true\" Collides=\"true\" FileIndex=\"3\" Group=\"0\" ID=\"%ld\" Name=\"pillar_%ld\" Rotation=\"0 0 0\" Scale=\"1 1 1\" Tag=\"\" WorldPos=\"%lf 0 %lf\" />\n", id, id, x, y);
}

void add_light(FILE * out, double x, double y, double r, size_t id) {
    fprintf(out, "<Entity Active=\"true\" FileIndex=\"0\" Group=\"0\" ID=\"%ld\" Name=\"torch_%ld\" Rotation=\"0 %lf 0\" Scale=\"1 1 1\" Tag=\"\" WorldPos=\"%lf 2 %lf\">\n", id, id, r, x, y);
    fprintf(out, "<UserVariables>\n");
    fprintf(out, "<Var Name=\"CastShadows\" Value=\"true\" />\n");
    fprintf(out, "<Var Name=\"StaticPhysics\" Value=\"false\" />\n");
    fprintf(out, "<Var Name=\"IsAffectedByDecal\" Value=\"false\" />\n");
    fprintf(out, "<Var Name=\"CallbackFunc\" Value=\"\" />\n");
    fprintf(out, "<Var Name=\"ConnectedProps\" Value=\"\" />\n");
    fprintf(out, "<Var Name=\"ConnectionStateChangeCallback\" Value=\"\" />\n");
    fprintf(out, "<Var Name=\"FullGameSave\" Value=\"false\" />\n");
    fprintf(out, "<Var Name=\"PlayerLookAtCallback\" Value=\"\" />\n");
    fprintf(out, "<Var Name=\"PlayerLookAtCallbackAutoRemove\" Value=\"false\" />\n");
    fprintf(out, "<Var Name=\"PlayerInteractCallback\" Value=\"\" />\n");
    fprintf(out, "<Var Name=\"PlayerInteractCallbackAutoRemove\" Value=\"false\" />\n");
    fprintf(out, "<Var Name=\"Lit\" Value=\"true\" />\n");
    fprintf(out, "<Var Name=\"ConnectedLight\" Value=\"\" />\n");
    fprintf(out, "<Var Name=\"ConnectionLightAmount\" Value=\"1\" />\n");
    fprintf(out, "<Var Name=\"ConnectionLightUseOnColor\" Value=\"true\" />\n");
    fprintf(out, "<Var Name=\"ConnectionLightUseSpec\" Value=\"false\" />\n");
    fprintf(out, "</UserVariables>\n");
    fprintf(out, "</Entity>\n");

}

void add_monster(FILE * out, size_t  id, double x, double y, double r) {
    fprintf(out, "<Entity Active=\"true\" FileIndex=\"3\" Group=\"%ld\" ID=\"%ld\" Name=\"servant_grunt_%ld\" Rotation=\"0 %lf 0\" Scale=\"1 1 1\" Tag=\"\" WorldPos=\"%lf 0 %lf\">\n", id, id, id, r, x, y);
    fprintf(out, "<UserVariables>\n");
    fprintf(out, "<Var Name=\"CallbackFunc\" Value=\"\" />\n");
    fprintf(out, "<Var Name=\"DisableTriggers\" Value=\"false\" />\n");
    fprintf(out, "<Var Name=\"Hallucination\" Value=\"false\" />\n");
    fprintf(out, "<Var Name=\"HallucinationEndDist\" Value=\"3\" />\n");
    fprintf(out, "</UserVariables>\n");
    fprintf(out, "</Entity>\n");
}

void print_xml() {
    FILE *out = fopen("/home/caligo/.steam/steam/steamapps/common/Amnesia The Dark Descent/custom_stories/test/maps/test.map", "w");
    fprintf(out, "<Level>\n");
    fprintf(out, "<MapData FogActive=\"false\" FogColor=\"1 1 1 1\" FogCulling=\"true\" FogEnd=\"20\" FogFalloffExp=\"1\" FogStart=\"0\" GlobalDecalMaxTris=\"300\" Name=\"\" SkyBoxActive=\"false\" SkyBoxColor=\"1 1 1 1\" SkyBoxTexture=\"../../../../../../../../\">\n");
    fprintf(out, "<MapContents>\n");
    fprintf(out, "<FileIndex_StaticObjects NumOfFiles=\"4\">\n");
    fprintf(out, "<File Id=\"0\" Path=\"static_objects/castlebase/wall/default.dae\" />\n");
    fprintf(out, "<File Id=\"1\" Path=\"static_objects/castlebase/ceiling/arched.dae\" />\n");
    fprintf(out, "<File Id=\"2\" Path=\"static_objects/castlebase/floor/deafult.dae\" />\n");
    fprintf(out, "<File Id=\"3\" Path=\"static_objects/castlebase/wall/welder_convex.dae\" />\n");
    fprintf(out, "</FileIndex_StaticObjects>\n");
    fprintf(out, "<FileIndex_Entities NumOfFiles=\"4\">\n");
    fprintf(out, "<File Id=\"0\" Path=\"entities/lamp/torch_static01/torch_static01.ent\" />\n");
    fprintf(out, "<File Id=\"1\" Path=\"entities/item/lantern/lantern.ent\" />\n");
    fprintf(out, "<File Id=\"2\" Path=\"entities/item/potion_oil/potion_oil_large.ent\" />\n");
    fprintf(out, "<File Id=\"3\" Path=\"entities/enemy/servant_grunt/servant_grunt.ent\" />\n");
    fprintf(out, "</FileIndex_Entities>\n");
    fprintf(out, "<FileIndex_Decals NumOfFiles=\"0\" />\n");
    fprintf(out, "<StaticObjects>\n");

    double rs = 4;
    size_t id = 2;
    for (size_t y = 0; y < Y; y++) {
        add_wall(out, -(rs/2), y * rs, id++, M_PI/2);
        add_pillar(out, -(rs/2), y * rs - (rs/2), id++);
    }
    add_pillar(out, -(rs/2), Y * rs - (rs/2), id++);
    for (size_t x = 0; x < X; x++) {
        add_wall(out, x * rs, - (rs/2), id++, 0);
        add_pillar(out, x * rs - (rs/2), - (rs/2), id++);
    }
    add_pillar(out, X * rs - (rs/2), - (rs/2), id++);
    for (size_t x = 0; x < X; x++) {
        for (size_t y = 0; y < Y; y++) {
            fprintf(out, "<StaticObject CastShadows=\"true\" Collides=\"true\" FileIndex=\"2\" Group=\"0\" ID=\"%ld\" Name=\"floor_deafult_%ld\" Rotation=\"0 0 0\" Scale=\"2 2 2\" Tag=\"\" WorldPos=\"%lf 0 %lf\" />\n", id, id, x * rs, y * rs);
            id++;
            fprintf(out, "<StaticObject CastShadows=\"true\" Collides=\"true\" FileIndex=\"1\" Group=\"0\" ID=\"%ld\" Name=\"roof_%ld\" Rotation=\"0 0 0\" Scale=\"0.4 0.4 0.4\" Tag=\"\" WorldPos=\"%lf 4 %lf\" />\n", id, id, x * rs, y * rs);
            id++;
            if (b[x][y]) {
                add_wall(out, x * rs, y * rs + (rs / 2), id++, 0);
                add_wall(out, x * rs, y * rs + (rs / 2), id++, M_PI);
                p[x][y] = 1;
                if (x-1 < X) p[x-1][y] = 1;
            }
            if (r[x][y]) {
                add_wall(out, x * rs + (rs / 2), y * rs, id++, -M_PI/2);
                add_wall(out, x * rs + (rs / 2), y * rs, id++, M_PI/2);
                p[x][y] = 1;
                if (y-1 < Y) p[x][y-1] = 1;
            }
        }
    }
    for (size_t x = 0; x < X; x++) {
        for (size_t y = 0; y < Y; y++) {
            if (p[x][y]) add_pillar(out, x * rs + (rs/2), y * rs + (rs / 2), id++);
        }
    }
    fprintf(out, "</StaticObjects>\n");
    fprintf(out, "<Primitives />\n");
    fprintf(out, "<Decals />\n");
    fprintf(out, "<Entities>\n");
    fprintf(out, "<Area Active=\"true\" AreaType=\"PlayerStart\" Group=\"0\" ID=\"1\" Mesh=\"\" Name=\"PlayerStartArea_1\" Rotation=\"0 0 0\" Scale=\"1 1 1\" Tag=\"\" WorldPos=\"0 0.5 0\">\n");
    fprintf(out, "<UserVariables />\n");
    fprintf(out, "</Area>\n");
//    for (size_t y = 0; y < Y; y++) {
//        if (rand() % 2 == 0) add_light(out, -(rs/2), y * rs, M_PI/2, id++);
//    }

//    for (size_t x = 0; x < X; x++) {
//        add_light(out, x * rs, - (rs/2), 0, id++);
//    }
    for (size_t x = 0; x < X; x++) {
        for (size_t y = 0; y < Y; y++) {
            if (x != 0 && y !=0)
            if (rand() % 50 == 0) add_monster(out, id++, x*rs, y*rs, (M_PI*2)/((rand()%4)+1));
        }
    }
    fprintf(out, "<Entity Active=\"true\" FileIndex=\"1\" Group=\"0\" ID=\"%ld\" Name=\"lantern_1\" Rotation=\"0 0 0\" Scale=\"1 1 1\" Tag=\"\" WorldPos=\"0 0 1.25\">\n", id++);
    fprintf(out, "<UserVariables>\n");
    fprintf(out, "<Var Name=\"CastShadows\" Value=\"true\" />\n");
    fprintf(out, "<Var Name=\"StaticPhysics\" Value=\"false\" />\n");
    fprintf(out, "<Var Name=\"IsAffectedByDecal\" Value=\"false\" />\n");
    fprintf(out, "<Var Name=\"CallbackFunc\" Value=\"\" />\n");
    fprintf(out, "<Var Name=\"ConnectedProps\" Value=\"\" />\n");
    fprintf(out, "<Var Name=\"ConnectionStateChangeCallback\" Value=\"\" />\n");
    fprintf(out, "<Var Name=\"FullGameSave\" Value=\"false\" />\n");
    fprintf(out, "<Var Name=\"PlayerLookAtCallback\" Value=\"\" />\n");
    fprintf(out, "<Var Name=\"PlayerLookAtCallbackAutoRemove\" Value=\"false\" />\n");
    fprintf(out, "<Var Name=\"PlayerInteractCallback\" Value=\"\" />\n");
    fprintf(out, "<Var Name=\"PlayerInteractCallbackAutoRemove\" Value=\"false\" />\n");
    fprintf(out, "<Var Name=\"CustomSubItemTypeName\" Value=\"\" />\n");
    fprintf(out, "</UserVariables>\n");
    fprintf(out, "</Entity>\n");
    fprintf(out, "<Entity Active=\"true\" FileIndex=\"2\" Group=\"0\" ID=\"%ld\" Name=\"potion_oil_large_1\" Rotation=\"0 0 0\" Scale=\"1 1 1\" Tag=\"\" WorldPos=\"-0.5 0 1.25\">\n", id++);
    fprintf(out, "<UserVariables>\n");
    fprintf(out, "<Var Name=\"CastShadows\" Value=\"true\" />\n");
    fprintf(out, "<Var Name=\"StaticPhysics\" Value=\"false\" />\n");
    fprintf(out, "<Var Name=\"IsAffectedByDecal\" Value=\"false\" />\n");
    fprintf(out, "<Var Name=\"CallbackFunc\" Value=\"\" />\n");
    fprintf(out, "<Var Name=\"ConnectedProps\" Value=\"\" />\n");
    fprintf(out, "<Var Name=\"ConnectionStateChangeCallback\" Value=\"\" />\n");
    fprintf(out, "<Var Name=\"FullGameSave\" Value=\"false\" />\n");
    fprintf(out, "<Var Name=\"PlayerLookAtCallback\" Value=\"\" />\n");
    fprintf(out, "<Var Name=\"PlayerLookAtCallbackAutoRemove\" Value=\"false\" />\n");
    fprintf(out, "<Var Name=\"PlayerInteractCallback\" Value=\"\" />\n");
    fprintf(out, "<Var Name=\"PlayerInteractCallbackAutoRemove\" Value=\"false\" />\n");
    fprintf(out, "<Var Name=\"CustomSubItemTypeName\" Value=\"\" />\n");
    fprintf(out, "</UserVariables>\n");
    fprintf(out, "</Entity>\n");
    add_light(out, 0, - (rs/2), 0, id++);
    add_light(out, (X-1)*rs, ((Y-1)*rs)+ (rs/2), M_PI, id++);

    fprintf(out, "</Entities>\n");
    fprintf(out, "<Misc />\n");
    fprintf(out, "<StaticObjectCombos />\n");
    fprintf(out, "</MapContents>\n");
    fprintf(out, "</MapData>\n");
    fprintf(out, "</Level>\n");
    fclose(out);
}

int main() {
    srand((unsigned int)time(0));
    printf("Maze width and height: ");
    scanf("%ld", &X);
    scanf("%ld", &Y);
    b = allocate();
    r = allocate();
    nv = allocate();
    p = allocate();

    set(b, 1);
    set(r, 1);
    set(nv, 1);
    set(p, 0);

    gen(0, 0);
    print_xml();

    dealloc(b);
    dealloc(r);
    dealloc(nv);
    dealloc(p);
    return 0;
}