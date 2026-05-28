static char *expected;
void
expect(char *expect, XKeyEvent *ignored)
{
	if (sel && expected && strstr(expected, expect)) {
		puts(expect);
		printitem(sel);
		cleanup();
		exit(1);
	} else if (!sel && expected && strstr(expected, expect)){
		puts(expect);
		cleanup();
		exit(1);
	}
}
