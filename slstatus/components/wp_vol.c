#include "../util.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *wireplumber(void) {
  char tmp_buf[64];
  FILE *fp = popen("wpctl get-volume @DEFAULT_AUDIO_SINK@", "r");
  fgets(tmp_buf, sizeof(tmp_buf), fp);
  pclose(fp);

  static char *vol_symbol[] = {"", "", ""};

  char *vol_start = strrchr(tmp_buf, ' ') + 1;
  if (!vol_start || strstr(vol_start, "[MUTED]")) {
    return bprintf("");
  }

  char vol_buf[6] = {0};
  int i = 0;
  while (i < 5 && vol_start[i] != ' ' && vol_start[i] != '[' &&
         vol_start[i] != '\n') {
    vol_buf[i] = vol_start[i++];
  }

  float vol_perc = atof(vol_buf) * 100;
  int vol_icon = vol_perc > 70 ? 2 : vol_perc > 30 ? 1 : 0;

  return bprintf("%s %.0f%%", vol_symbol[vol_icon], vol_perc);
}
