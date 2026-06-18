#include <Audio.h>

// Sécurités
#ifndef USB_AUDIO
#error "Erreur : La pile USB_AUDIO n'est pas activée dans platformio.ini !"
#endif
#if defined(AUDIO_USB_CHANNEL_COUNT) && AUDIO_USB_CHANNEL_COUNT != 6
#error "Erreur : Le nombre de canaux USB n'est pas configuré sur 6 !"
#endif

// Objets communs
AudioInputUSBHex            usbIn;          // Entrée USB Hexaphonique (depuis le PC)
AudioOutputUSBHex           usbOut;         // Sortie USB Hexaphonique (vers le PC)

// --- LES INTERFACES TDM2 ---
AudioOutputTDM2             tdmOut;
AudioInputTDM2              tdmIn;

// ===================================================================
// LE ROUTAGE HEXAPHONIQUE (PC -> USB -> TDM2 -> DAISY -> TDM2 -> USB -> PC)
// ===================================================================

// A) USB IN -> TDM OUT (Vers Daisy, ports pairs 0, 2, 4, 6, 8, 10 = slots 0 à 5)
AudioConnection patchUsbToTdm1(usbIn, 0, tdmOut, 0);
AudioConnection patchUsbToTdm2(usbIn, 1, tdmOut, 2);
AudioConnection patchUsbToTdm3(usbIn, 2, tdmOut, 4);
AudioConnection patchUsbToTdm4(usbIn, 3, tdmOut, 6);
AudioConnection patchUsbToTdm5(usbIn, 4, tdmOut, 8);
AudioConnection patchUsbToTdm6(usbIn, 5, tdmOut, 10);

// B) TDM IN -> USB OUT (Depuis Daisy, ports pairs 0, 2, 4, 6, 8, 10 vers PC)
AudioConnection patchTdmToUsb1(tdmIn, 0, usbOut, 0);
AudioConnection patchTdmToUsb2(tdmIn, 2, usbOut, 1);
AudioConnection patchTdmToUsb3(tdmIn, 4, usbOut, 2);
AudioConnection patchTdmToUsb4(tdmIn, 6, usbOut, 3);
AudioConnection patchTdmToUsb5(tdmIn, 8, usbOut, 4);
AudioConnection patchTdmToUsb6(tdmIn, 10, usbOut, 5);

// ===================================================================
// SETUP & LOOP
// ===================================================================
void setup() {
  Serial.begin(9600);
  AudioMemory(60); 
}

void loop() {
}