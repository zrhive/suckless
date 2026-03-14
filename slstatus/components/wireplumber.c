#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "../util.h"

const char *wireplumber(void) {
  // Volume: 0.65 [MUTED]
  FILE *fp = popen("wpctl get-volume @DEFAULT_AUDIO_SINK@", "r"); //20

  char tmp_buf[25];
  char ch;
  unsigned short i = 0;
	while ((ch = fgetc(fp)) != EOF && i < 24) {
    tmp_buf[i++] = ch;
  }
	tmp_buf[i] = '\0';
	pclose(fp);

  bool mute = false;
  for (int b = 0; b < strlen(tmp_buf) - 6; b++) {
    if (tmp_buf[b] == '[') {
      if (strncmp(&tmp_buf[b], "[MUTED]", 7) == 0) {
        mute = true;
        break;
      }
    }
  }

  if (mute) return bprintf("");
  else {
    char vol_buf[6];
    float volume;
    int perc;

    static char *symbol[] = { "", "", "", };

    // if (sscanf(tmp_buf, "Volume: %5s", vol_buf) == 1) {
    if (sscanf(tmp_buf, "Volume: %s", vol_buf) == 1) {
      sscanf(vol_buf, "%f", &volume);
      int perc = (int)(volume * 100);

      return bprintf("%s %d%%", symbol[perc / 34], perc);
    }
  }
}
