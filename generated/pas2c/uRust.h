#pragma once

#include "pas2c.h"

#include "SDLh.h"
#include "uTypes.h"
static const string255 HWEngineFutureLibName = STRINIT("hwengine_future");
typedef pointer TRGameField;
typedef pointer TRAI;
TRGameField create_empty_game_field(LongWord width,LongWord height);
void get_game_field_parameters(TRGameField game_field,LongInt (*width),LongInt (*height),LongInt (*play_width),LongInt (*play_height));
void dispose_game_field(TRGameField game_field);
Word land_get(TRGameField game_field,LongInt x,LongInt y);
void land_set(TRGameField game_field,LongInt x,LongInt y,Word value);
PWordArray land_row(TRGameField game_field,LongInt row);
void land_fill(TRGameField game_field,LongInt x,LongInt y,Word border,Word fill);
LongWord land_pixel_get(TRGameField game_field,LongInt x,LongInt y);
void land_pixel_set(TRGameField game_field,LongInt x,LongInt y,LongWord value);
PLongWordArray land_pixel_row(TRGameField game_field,LongInt row);
TRGameField generate_outline_templated_game_field(LongWord feature_size,PChar seed,PChar template_type,PChar data_path);
TRGameField generate_wfc_templated_game_field(LongWord feature_size,PChar seed,PChar template_type,PChar data_path);
TRGameField generate_maze_game_field(LongWord feature_size,PChar seed,PChar template_type,PChar data_path);
void apply_theme(TRGameField game_field,PChar data_path,PChar theme_name);
typedef LongWord TAmmoCounts[61];
typedef TAmmoCounts * PAmmoCounts;
typedef struct __HedgehogState {
            real x;
            real y;
            LongWord angle;
            boolean looking_to_the_right;
            boolean is_moving;
        } HedgehogState;
TRAI create_ai(TRGameField game_field);
void ai_clear_team(TRAI ai);
void ai_add_team_hedgehog(TRAI ai,real x,real y,PAmmoCounts ammo_counts);
void ai_think(TRAI ai);
boolean ai_have_plan();
void ai_get_action(TRAI ai,HedgehogState (*current_hedgehog_state),string255 (*action));
void dispose_ai(TRAI ai);

