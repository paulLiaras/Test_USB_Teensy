#include <Audio.h>


 #define USE_STEREO_MIX 


// Sécurités
#ifndef USB_AUDIO
#error "Erreur : La pile USB_AUDIO n'est pas activée dans platformio.ini !"
#endif
#if defined(AUDIO_USB_CHANNEL_COUNT) && AUDIO_USB_CHANNEL_COUNT != 6
#error "Erreur : Le nombre de canaux USB n'est pas configuré sur 6 !"
#endif

// Objets communs
AudioInputUSBHex            usbIn;          
AudioOutputUSBHex           usbOut;         

// ===================================================================
// ARCHITECTURE CONDITIONNELLE
// ===================================================================
#ifdef USE_STEREO_MIX
  // --- MODE STÉRÉO ---
  AudioMixer4              mixerLeft;
  AudioMixer4              mixerRight;

  AudioConnection          patchCord1(usbIn, 0, mixerLeft, 0); 
  AudioConnection          patchCord2(usbIn, 1, mixerLeft, 1); 
  AudioConnection          patchCord3(usbIn, 2, mixerLeft, 2); 
  
  AudioConnection          patchCord4(usbIn, 3, mixerRight, 0); 
  AudioConnection          patchCord5(usbIn, 4, mixerRight, 1); 
  AudioConnection          patchCord6(usbIn, 5, mixerRight, 2); 

  AudioConnection          patchCord7(mixerLeft, 0, usbOut, 0);
  AudioConnection          patchCord8(mixerRight, 0, usbOut, 1);

#else
  // --- MODE HEXAPHONIQUE (Miroir direct) ---
  AudioConnection          patchCord1(usbIn, 0, usbOut, 0); 
  AudioConnection          patchCord2(usbIn, 1, usbOut, 1); 
  AudioConnection          patchCord3(usbIn, 2, usbOut, 2); 
  AudioConnection          patchCord4(usbIn, 3, usbOut, 3); 
  AudioConnection          patchCord5(usbIn, 4, usbOut, 4); 
  AudioConnection          patchCord6(usbIn, 5, usbOut, 5); 
#endif

// ===================================================================
// SETUP & LOOP
// ===================================================================
void setup() {
  AudioMemory(60); 

#ifdef USE_STEREO_MIX
  // Application du gain uniquement si le mixeur existe
  for (int i = 0; i < 3; i++) {
    mixerLeft.gain(i, 0.4); 
    mixerRight.gain(i, 0.4);
  }
#endif
}

void loop() {
}