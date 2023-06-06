#include "GameFrontend.h"
#include "globalBoard.h"
#include <alsa/asoundlib.h>


string matrix[8][8] = {{"1_1", "1_2", "1_3", "1_4", "1_5", "1_6", "1_7", "1_8"},
                       {"2_1", "2_2", "2_3", "2_4", "2_5", "2_6", "2_7", "2_8"},
                       {"3_1", "3_2", "3_3", "3_4", "3_5", "3_6", "3_7", "3_8"},
                       {"4_1", "4_2", "4_3", "4_4", "4_5", "4_6", "4_7", "4_8"},
                       {"5_1", "5_2", "5_3", "5_4", "5_5", "5_6", "5_7", "5_8"},
                       {"6_1", "6_2", "6_3", "6_4", "6_5", "6_6", "6_7", "6_8"},
                       {"7_1", "7_2", "7_3", "7_4", "7_5", "7_6", "7_7", "7_8"},
                       {"8_1", "8_2", "8_3", "8_4", "8_5", "8_6", "8_7", "8_8"}};

bool victory = false;
bool fail = false;

int playMusic() {
    // Inicjalizacja urządzenia ALSA
    snd_pcm_t *pcmHandle;
    snd_pcm_open(&pcmHandle, "default", SND_PCM_STREAM_PLAYBACK, 0);

    // Konfiguracja parametrów dźwięku
    snd_pcm_set_params(pcmHandle,
                       SND_PCM_FORMAT_S16_LE,   // Format próbek: 16-bitowe, Little Endian
                       SND_PCM_ACCESS_RW_INTERLEAVED,  // Dostęp do danych: interleave
                       2,    // Liczba kanałów: stereo
                       44100,   // Częstotliwość próbkowania: 44.1 kHz
                       1,    // Liczba zapętleń: 1 (zapętlenie)
                       50000);   // Opóźnienie w mikrosekundach: 50 ms

    // Wczytanie pliku audio
    const char *fileName = "/home/karolina/University/saper/funky.wav";
    FILE *file = fopen(fileName, "rb");
    if (!file) {
        printf("Błąd podczas otwierania pliku: %s\n", fileName);
        return 1;
    }

    // Bufor danych dźwiękowych
    const size_t bufferSize = 8192;
    char buffer[bufferSize];

    // Odtwarzanie zapętlonej muzyki
    while (true) {
        size_t bytesRead = fread(buffer, 1, bufferSize, file);
        if (bytesRead == 0) {
            // Powrót na początek pliku po odtworzeniu całej zawartości
            fseek(file, 0, SEEK_SET);
            continue;
        }

        snd_pcm_writei(pcmHandle, buffer, bytesRead / 4);  // Przekazanie danych do urządzenia ALSA
    }

    // Zamknięcie urządzenia ALSA
    snd_pcm_close(pcmHandle);

    return 0;
}


int main(int argc, char **argv) {

    thread musicThread(playMusic);

    glutInit(&argc, argv);

    GameFrontend gameFrontend = *new GameFrontend();
    gameFrontend.run();

    musicThread.join();

    return 0;
}
