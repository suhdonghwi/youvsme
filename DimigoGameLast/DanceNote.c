#include "DanceNote.h"
#include "SpriteResources.h"

void on_render_dance_note(GameObject* dance_note, HDC main_dc) {
  DanceNoteData* data = dance_note->data;
  dance_note->pos.x += data->speed;

  if (dance_note->pos.x < -100 || dance_note->pos.x > 1300)
    dance_note->alive = false;
}

GameObject* create_dance_note(DanceDirection dir, HBITMAP* sprites, int speed) {
  if (dir == DANCE_NONE) return NULL;

  GameObject* dance_note = init_game_object(sprites);
  dance_note->sprite_index = 4 + dir;
  dance_note->on_render = on_render_dance_note;
  dance_note->collidable = true;

  switch (dir) {
    case DANCE_UP:
      strcpy(dance_note->tag, "dance_up");
      break;
    case DANCE_RIGHT:
      strcpy(dance_note->tag, "dance_right");
      break;
    case DANCE_DOWN:
      strcpy(dance_note->tag, "dance_down");
      break;
    case DANCE_LEFT:
      strcpy(dance_note->tag, "dance_left");
      break;
  }

  DanceNoteData* data = malloc(sizeof(DanceNoteData));
  if (data == NULL) return NULL;
  data->speed = speed;

  dance_note->data = data;

  return dance_note;
}
