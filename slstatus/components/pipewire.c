#include "../util.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *wireplumber(void) {
  // Volume: 0.65 [MUTED]
  FILE *fp = popen("wpctl get-volume @DEFAULT_AUDIO_SINK@", "r"); // 20

  char tmp_buf[25];
  char ch;
  unsigned short i = 0;
  while ((ch = fgetc(fp)) != EOF && i < 25) {
    tmp_buf[i++] = ch;
  }
  tmp_buf[i] = '\0';
  pclose(fp);

  bool is_mute = false;
  short b = i - 1;
  while (b >= 0) {
    if ('[' == tmp_buf[b]) {
      if (tmp_buf[b + 1] == 'm' && tmp_buf[b + 2] == 'u')
        is_mute = true;
      b -= 3;
      break;
    }
    b--;
  }

  if (is_mute)
    return bprintf("");
  else {
    char vol_buf[6];
    float vol_perc;

    static char *vol_symbol[] = {
        "",
        "",
        "",
    };

    i = 0;
    while (i < 6) {
      b++;
      if (' ' == tmp_buf[b]) {
        vol_buf[i] = '\0';
        break;
      } else
        vol_buf[i++] = tmp_buf[b];
    }

    vol_perc = atof(vol_buf) * 100;
    int vol_idx = (int)(vol_perc / 33);
    if (vol_idx > 2)
      vol_idx = 2;

    return bprintf("%s %.0f%%", vol_symbol[vol_idx], vol_perc);
    // return bprintf("%s %g", vol_symbol[vol_perc / 4], vol_perc);
  }
}
