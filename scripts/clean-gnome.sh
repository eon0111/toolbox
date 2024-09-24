#!/bin/bash

PAQUETES="libreoffice* gnome-2048 gnome-calendar gnome-chess gnome-contacts gnome-mahjongg gnome-klotski gnome-mines gnome-music gnome-nibbles gnome-robots gnome-sudoku gnome-taquin gnome-tetravex gnome-weather"

apt autoremove -y $PAQUETES
apt purge -y $PAQUETES
