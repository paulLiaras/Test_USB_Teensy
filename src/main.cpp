#include <Audio.h>

#ifndef USB_AUDIO
#error "Erreur : La pile USB_AUDIO n'est pas activée dans platformio.ini !"
#endif

#if defined(AUDIO_USB_CHANNEL_COUNT) && AUDIO_USB_CHANNEL_COUNT != 6
#error "Erreur : Le nombre de canaux USB n'est pas configuré sur 6 !"
#endif


AudioSynthWaveform          monoSine;       // Générateur de signal mono interne


AudioOutputUSBHex           usbOut;         

// On envoie le signal mono sur les canaux 0 (Gauche) et 1 (Droite)
AudioConnection          patchCord1(monoSine, 0, usbOut, 0); 
AudioConnection          patchCord2(monoSine, 0, usbOut, 1); 

void setup() {
  
  AudioMemory(24); 
  
  // Démarre la génération : amplitude 0.5 (50%), fréquence 440 Hz (Note La), type sinusoïde
  monoSine.begin(0.5, 440.0, WAVEFORM_SINE);
}

void loop() {
 
}