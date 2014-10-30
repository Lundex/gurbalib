#include "../domain.h"

inherit "/std/monster";

static nomask void clothe(void) {
   equip_monster(({
      NOKICLIFFS_ARMOURS_DIR + "/monk_robe",
      NOKICLIFFS_ARMOURS_DIR + "/monk_sandals",
      NOKICLIFFS_ARMOURS_DIR + "/rope_belt"
   }));
}

void setup(void) {
   set_gender("male");
   clothe();
}

