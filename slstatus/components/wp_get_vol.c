/* Created by William Rabbermann */
#include "../util.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TMP_BUF_SIZE 14
#define VOL_BUF_SIZE 14

const char *alsa_master_vol(void) {
  bool MASTER_IS_MUTED = true;
  char tmp_buf[TMP_BUF_SIZE];
  short b;
  unsigned short i = 0;

  FILE *fp = popen("wpctl get-volume 50 | tail -c 5", "r");

  char ch;
  while ((ch = fgetc(fp)) != EOF && i < TMP_BUF_SIZE)
    tmp_buf[i++] = ch;
  tmp_buf[i] = '\0';
  pclose(fp);

  b = i - 1;
  while (b >= 0) {
    if ('[' == tmp_buf[b]) {
      if (tmp_buf[b + 1] == 'o' && tmp_buf[b + 2] == 'n')
        MASTER_IS_MUTED = false;
      b -= 3;
      break;
    }
    b--;
  }

  /*	if (MASTER_IS_MUTED) return bprintf("MUTE"); */
  /*	else */
  /*	{ */
  char vol_buf[VOL_BUF_SIZE];
  while (b >= 0) {
    if ('[' == tmp_buf[b])
      break;
    b--;
  }

  i = 0;
  while (i < VOL_BUF_SIZE) {
    b++;
    if (']' == tmp_buf[b]) {
      vol_buf[i] = '\0';
      break;
    } else
      vol_buf[i++] = tmp_buf[b];
  }

  static char *vol_symbol[] = {
      "󰕿",
      "󰖀",
      "󰕾",
      "󰕾",
  };

  float vol_perc = atof(vol_buf) * 100;
  int vol_char = vol_perc / 50;

  return bprintf("%s %g", vol_symbol[vol_char], vol_perc);
}
/* } */
