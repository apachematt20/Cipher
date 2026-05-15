#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 4096

/* Scambia due byte tramite puntatore */
static inline void swap(unsigned char *a, unsigned char *b) {
    unsigned char tmp = *a;
    *a = *b;
    *b = tmp;
}

/* Key-Scheduling Algorithm (KSA): Inizializza lo stato interno (S-box) con la password */
void rc4_ksa(unsigned char *S, const unsigned char *key, size_t key_len) {
    for (int i = 0; i < 256; i++) {
        S[i] = i;
    }
    
    int j = 0;
    for (int i = 0; i < 256; i++) {
        j = (j + S[i] + key[i % key_len]) % 256;
        swap(&S[i], &S[j]);
    }
}

/* Pseudo-Random Generation Algorithm (PRGA): Elabora il file generando la keystream in XOR */
void process_file(FILE *in, FILE *out, const unsigned char *key, size_t key_len) {
    unsigned char S[256];
    rc4_ksa(S, key, key_len); // Inizializza lo stato per la sessione

    int i = 0, j = 0;
    size_t bytes_read;
    unsigned char buffer[BUFFER_SIZE];
    unsigned char out_buffer[BUFFER_SIZE];

    /* Legge, cifra/decifra e scrive in blocchi per non saturare la RAM */
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), in)) > 0) {
        for (size_t k = 0; k < bytes_read; k++) {
            i = (i + 1) % 256;
            j = (j + S[i]) % 256;
            swap(&S[i], &S[j]);
            
            // Genera il byte di keystream e fa lo XOR con il byte del file
            unsigned char keystream_byte = S[(S[i] + S[j]) % 256];
            out_buffer[k] = buffer[k] ^ keystream_byte;
        }
        fwrite(out_buffer, 1, bytes_read, out);
    }
}

int main(int argc, char *argv[]) {
    // Controllo argomenti CLI
    if (argc != 4) {
        fprintf(stderr, "Uso: %s <file_input> <file_output> <password>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *input_path = argv[1];
    const char *output_path = argv[2];
    const unsigned char *password = (const unsigned char *)argv[3];
    size_t pw_len = strlen((const char *)password);

    if (pw_len == 0) {
        fprintf(stderr, "Errore: la password non puo' essere vuota.\n");
        return EXIT_FAILURE;
    }

    // Apertura file in modalità binaria ("rb", "wb") per gestire immagini/eseguibili
    FILE *in_file = fopen(input_path, "rb");
    if (!in_file) {
        perror("Errore apertura file input");
        return EXIT_FAILURE;
    }

    FILE *out_file = fopen(output_path, "wb");
    if (!out_file) {
        perror("Errore creazione file output");
        fclose(in_file);
        return EXIT_FAILURE;
    }

    // Avvia il processo di cifratura/decifratura
    process_file(in_file, out_file, password, pw_len);

    printf("Operazione completata con successo.\n");

    // Pulizia risorse
    fclose(in_file);
    fclose(out_file);

    return EXIT_SUCCESS;
}

