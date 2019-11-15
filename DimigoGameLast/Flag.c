#include "Flag.h"
#include "SpriteResources.h"

// 캐릭터를 받고 깃발을 생성하여 반환합니다.
GameObject* create_flag(bool is_coco_flag) {
  GameObject* flag = init_game_object(flag_sprites);
  flag->sprite_index = is_coco_flag ? 0 : 1;
  flag->collidable = true;

  strncpy(flag->tag, "flag", sizeof(flag->tag));

  return flag;
}