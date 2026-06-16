#include <Audio.h>

#ifndef USB_AUDIO
#error "Erreur : La pile USB_AUDIO n'est pas activée dans platformio.ini !"
#endif

#if defined(AUDIO_USB_CHANNEL_COUNT) && AUDIO_USB_CHANNEL_COUNT != 6
#error "Erreur : Le nombre de canaux USB n'est pas configuré sur 6 !"
#endif


AudioInputUSBHex            usbIn;          


AudioOutputUSBHex           usbOut;         

// On relie les 6 premiers canaux de l'USB vers le retour USB
AudioConnection          patchCord1(usbIn, 0, usbOut, 0); 
AudioConnection          patchCord2(usbIn, 1, usbOut, 1); 
AudioConnection          patchCord3(usbIn, 2, usbOut, 2); 
AudioConnection          patchCord4(usbIn, 3, usbOut, 3); 
AudioConnection          patchCord5(usbIn, 4, usbOut, 4); 
AudioConnection          patchCord6(usbIn, 5, usbOut, 5); 

void setup() {
  
  AudioMemory(60); // Augmenté pour éviter de manquer de mémoire avec 6 canaux
}

void loop() {
 
}