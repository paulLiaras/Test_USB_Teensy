#include <Audio.h>

// Sécurités
#ifndef USB_AUDIO
#error "Erreur : La pile USB_AUDIO n'est pas activée dans platformio.ini !"
#endif

// Objets communs
AudioInputUSB               usbIn;          // Entrée USB Stéréo (depuis le PC)
AudioOutputUSB              usbOut;         // Sortie USB Stéréo (vers le PC)

// --- LES INTERFACES TDM2 ---
AudioOutputTDM2             tdmOut;
AudioInputTDM2              tdmIn;

// ===================================================================
// LE ROUTAGE STÉRÉO (PC -> USB -> TDM2 -> DAISY -> TDM2 -> USB -> PC)
// ===================================================================

// A) USB IN (Stéréo) -> TDM OUT (Vers Daisy, ports pairs 0 et 2 = slots 0 et 1)
AudioConnection patchUsbToTdmL(usbIn, 0, tdmOut, 0);
AudioConnection patchUsbToTdmR(usbIn, 1, tdmOut, 2);

// B) TDM IN (Depuis Daisy, ports pairs 0 et 2) -> USB OUT (Stéréo vers PC)
AudioConnection patchTdmToUsbL(tdmIn, 0, usbOut, 0);
AudioConnection patchTdmToUsbR(tdmIn, 2, usbOut, 1);

// ===================================================================
// SETUP & LOOP
// ===================================================================
void setup() {
  Serial.begin(9600);
  AudioMemory(60); 
}

void loop() {
}