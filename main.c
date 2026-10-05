#include <stdio.h>
#include <string.h>
#include <ctype.h>



#define BLOCK_SIZE 16
unsigned char sbox[256] = {
    0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5,
    0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
    0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0,
    0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
    0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC,
    0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
    0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A,
    0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
    0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0,
    0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
    0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B,
    0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
    0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85,
    0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
    0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5,
    0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
    0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17,
    0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
    0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88,
    0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
    0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C,
    0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
    0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9,
    0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
    0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6,
    0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
    0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E,
    0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
    0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94,
    0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
    0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68,
    0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16
};
unsigned char rcon[10] =
{
    0x01, 0x02, 0x04, 0x08,
    0x10, 0x20, 0x40, 0x80,
    0x1B, 0x36
};
unsigned char inv_sbox[256] = {
    0x52, 0x09, 0x6A, 0xD5, 0x30, 0x36, 0xA5, 0x38,
    0xBF, 0x40, 0xA3, 0x9E, 0x81, 0xF3, 0xD7, 0xFB,
    0x7C, 0xE3, 0x39, 0x82, 0x9B, 0x2F, 0xFF, 0x87,
    0x34, 0x8E, 0x43, 0x44, 0xC4, 0xDE, 0xE9, 0xCB,
    0x54, 0x7B, 0x94, 0x32, 0xA6, 0xC2, 0x23, 0x3D,
    0xEE, 0x4C, 0x95, 0x0B, 0x42, 0xFA, 0xC3, 0x4E,
    0x08, 0x2E, 0xA1, 0x66, 0x28, 0xD9, 0x24, 0xB2,
    0x76, 0x5B, 0xA2, 0x49, 0x6D, 0x8B, 0xD1, 0x25,
    0x72, 0xF8, 0xF6, 0x64, 0x86, 0x68, 0x98, 0x16,
    0xD4, 0xA4, 0x5C, 0xCC, 0x5D, 0x65, 0xB6, 0x92,
    0x6C, 0x70, 0x48, 0x50, 0xFD, 0xED, 0xB9, 0xDA,
    0x5E, 0x15, 0x46, 0x57, 0xA7, 0x8D, 0x9D, 0x84,
    0x90, 0xD8, 0xAB, 0x00, 0x8C, 0xBC, 0xD3, 0x0A,
    0xF7, 0xE4, 0x58, 0x05, 0xB8, 0xB3, 0x45, 0x06,
    0xD0, 0x2C, 0x1E, 0x8F, 0xCA, 0x3F, 0x0F, 0x02,
    0xC1, 0xAF, 0xBD, 0x03, 0x01, 0x13, 0x8A, 0x6B,
    0x3A, 0x91, 0x11, 0x41, 0x4F, 0x67, 0xDC, 0xEA,
    0x97, 0xF2, 0xCF, 0xCE, 0xF0, 0xB4, 0xE6, 0x73,
    0x96, 0xAC, 0x74, 0x22, 0xE7, 0xAD, 0x35, 0x85,
    0xE2, 0xF9, 0x37, 0xE8, 0x1C, 0x75, 0xDF, 0x6E,
    0x47, 0xF1, 0x1A, 0x71, 0x1D, 0x29, 0xC5, 0x89,
    0x6F, 0xB7, 0x62, 0x0E, 0xAA, 0x18, 0xBE, 0x1B,
    0xFC, 0x56, 0x3E, 0x4B, 0xC6, 0xD2, 0x79, 0x20,
    0x9A, 0xDB, 0xC0, 0xFE, 0x78, 0xCD, 0x5A, 0xF4,
    0x1F, 0xDD, 0xA8, 0x33, 0x88, 0x07, 0xC7, 0x31,
    0xB1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xEC, 0x5F,
    0x60, 0x51, 0x7F, 0xA9, 0x19, 0xB5, 0x4A, 0x0D,
    0x2D, 0xE5, 0x7A, 0x9F, 0x93, 0xC9, 0x9C, 0xEF,
    0xA0, 0xE0, 0x3B, 0x4D, 0xAE, 0x2A, 0xF5, 0xB0,
    0xC8, 0xEB, 0xBB, 0x3C, 0x83, 0x53, 0x99, 0x61,
    0x17, 0x2B, 0x04, 0x7E, 0xBA, 0x77, 0xD6, 0x26,
    0xE1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0C, 0x7D
};


void write_hex_block(FILE *output, unsigned char block[16])
{
    const char hex[] = "0123456789ABCDEF";

    for (int i = 0; i < 16; i++)
    {
        
        fputc(hex[(block[i] >> 4) & 0x0F], output);

        
        fputc(hex[block[i] & 0x0F], output);
    }
}



void add_padding(unsigned char block[BLOCK_SIZE], size_t n)
{
    unsigned char padding = BLOCK_SIZE - n;

    for (size_t i = n; i < BLOCK_SIZE; i++)
    {
        block[i] = padding;
    }
}



void print_block(unsigned char block[BLOCK_SIZE])
{
    for (int i = 0; i < BLOCK_SIZE; i++)
    {
        printf("%02X ", block[i]);
    }

    printf("\n");
}


void load_state(unsigned char state[4][4],
                unsigned char block[16])
{
    for (int i = 0; i < 16; i++)
    {
        state[i % 4][i / 4] = block[i];
    }
}


void store_state(unsigned char block[16],
                 unsigned char state[4][4])
{
    for (int i = 0; i < 16; i++)
    {
        block[i] = state[i % 4][i / 4];
    }
}


void add_round_key(unsigned char state[4][4],
                   unsigned char round_key[4][4])
{
    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            
            state[row][col] ^= round_key[row][col];
        }
    }
}


void rot_word(unsigned char word[4])
{
    unsigned char temp = word[0];

    word[0] = word[1];
    word[1] = word[2];
    word[2] = word[3];
    word[3] = temp;
}


void sub_word(unsigned char word[4])
{
    for (int i = 0; i < 4; i++)
    {
        word[i] = sbox[word[i]];
    }
}


void g_function(unsigned char word[4], unsigned char rcon)
{
    
    unsigned char temp = word[0];

    word[0] = word[1];
    word[1] = word[2];
    word[2] = word[3];
    word[3] = temp;

    
    for (int i = 0; i < 4; i++)
    {
        word[i] = sbox[word[i]];
    }

    
    word[0] = word[0] ^ rcon;
}


void key_expansion(unsigned char key[16],
                   unsigned char expanded_key[176])
{
    
    for (int i = 0; i < 16; i++)
    {
        expanded_key[i] = key[i];
    }

    
    int bytes_generated = 16;
    int rcon_index = 0;

    unsigned char temp[4];

    while (bytes_generated < 176)
    {
        
        for (int i = 0; i < 4; i++)
        {
            temp[i] = expanded_key[bytes_generated - 4 + i];
        }

        
        if (bytes_generated % 16 == 0)
        {
            g_function(temp, rcon[rcon_index]);
            rcon_index++;
        }

        
        for (int i = 0; i < 4; i++)
        {
            expanded_key[bytes_generated] =
                expanded_key[bytes_generated - 16] ^ temp[i];

            bytes_generated++;
        }
    }
}


void sub_bytes(unsigned char state[4][4])
{
    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            state[row][col] = sbox[state[row][col]];
        }
    }
}


void shift_rows(unsigned char state[4][4])
{
    unsigned char temp;

    

    
    temp = state[1][0];

    state[1][0] = state[1][1];
    state[1][1] = state[1][2];
    state[1][2] = state[1][3];
    state[1][3] = temp;

    
    temp = state[2][0];

    state[2][0] = state[2][2];
    state[2][2] = temp;

    temp = state[2][1];

    state[2][1] = state[2][3];
    state[2][3] = temp;

    
    temp = state[3][0];

    state[3][0] = state[3][3];
    state[3][3] = state[3][2];
    state[3][2] = state[3][1];
    state[3][1] = temp;
}


unsigned char xtime(unsigned char x)
{
    if (x & 0x80)
    {
        
        return (x << 1) ^ 0x1B;
    }
    else
    {
        return x << 1;
    }
}


void mix_columns(unsigned char state[4][4])
{
    for (int col = 0; col < 4; col++)
    {
        unsigned char a = state[0][col];
        unsigned char b = state[1][col];
        unsigned char c = state[2][col];
        unsigned char d = state[3][col];

        state[0][col] =
            xtime(a) ^
            (xtime(b) ^ b) ^
            c ^
            d;

        state[1][col] =
            a ^
            xtime(b) ^
            (xtime(c) ^ c) ^
            d;

        state[2][col] =
            a ^
            b ^
            xtime(c) ^
            (xtime(d) ^ d);

        state[3][col] =
            (xtime(a) ^ a) ^
            b ^
            c ^
            xtime(d);
    }
}


void aes_encrypt_block(unsigned char block[16],
                       unsigned char expanded_key[176])
{
    unsigned char state[4][4];
    unsigned char round_key[4][4];

    
    load_state(state, block);

    
    for (int i = 0; i < 16; i++)
    {
        round_key[i % 4][i / 4] =
            expanded_key[i];
    }

    add_round_key(state, round_key);

    
    for (int round = 1; round <= 9; round++)
    {
        sub_bytes(state);
        shift_rows(state);
        mix_columns(state);

        for (int i = 0; i < 16; i++)
        {
            round_key[i % 4][i / 4] =
                expanded_key[round * 16 + i];
        }

        add_round_key(state, round_key);
    }

    
    sub_bytes(state);
    shift_rows(state);

    for (int i = 0; i < 16; i++)
    {
        round_key[i % 4][i / 4] =
            expanded_key[160 + i];
    }

    add_round_key(state, round_key);

    
    store_state(block, state);
}


void inv_shift_rows(unsigned char state[4][4])
{
    unsigned char temp;

    

    
    temp = state[1][3];

    state[1][3] = state[1][2];
    state[1][2] = state[1][1];
    state[1][1] = state[1][0];
    state[1][0] = temp;

    
    temp = state[2][0];

    state[2][0] = state[2][2];
    state[2][2] = temp;

    temp = state[2][1];

    state[2][1] = state[2][3];
    state[2][3] = temp;

    
    temp = state[3][0];

    state[3][0] = state[3][1];
    state[3][1] = state[3][2];
    state[3][2] = state[3][3];
    state[3][3] = temp;
}


void inv_sub_bytes(unsigned char state[4][4])
{
    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            state[row][col] =
                inv_sbox[state[row][col]];
        }
    }
}


unsigned char multiply_9(unsigned char x)
{
    unsigned char x2 = xtime(x);
    unsigned char x4 = xtime(x2);
    unsigned char x8 = xtime(x4);

    return x8 ^ x;
}

unsigned char multiply_B(unsigned char x)
{
    unsigned char x2 = xtime(x);
    unsigned char x4 = xtime(x2);
    unsigned char x8 = xtime(x4);

    return x8 ^ x2 ^ x;
}

unsigned char multiply_D(unsigned char x)
{
    unsigned char x2 = xtime(x);
    unsigned char x4 = xtime(x2);
    unsigned char x8 = xtime(x4);

    return x8 ^ x4 ^ x;
}

unsigned char multiply_E(unsigned char x)
{
    unsigned char x2 = xtime(x);
    unsigned char x4 = xtime(x2);
    unsigned char x8 = xtime(x4);

    return x8 ^ x4 ^ x2;
}


void inv_mix_columns(unsigned char state[4][4])
{
    for (int col = 0; col < 4; col++)
    {
        unsigned char a = state[0][col];
        unsigned char b = state[1][col];
        unsigned char c = state[2][col];
        unsigned char d = state[3][col];

        state[0][col] =
            multiply_E(a) ^
            multiply_B(b) ^
            multiply_D(c) ^
            multiply_9(d);

        state[1][col] =
            multiply_9(a) ^
            multiply_E(b) ^
            multiply_B(c) ^
            multiply_D(d);

        state[2][col] =
            multiply_D(a) ^
            multiply_9(b) ^
            multiply_E(c) ^
            multiply_B(d);

        state[3][col] =
            multiply_B(a) ^
            multiply_D(b) ^
            multiply_9(c) ^
            multiply_E(d);
    }
}


void aes_decrypt_block(unsigned char block[16],
                       unsigned char expanded_key[176])
{
    unsigned char state[4][4];
    unsigned char round_key[4][4];

    
    load_state(state, block);

    
    for (int i = 0; i < 16; i++)
    {
        round_key[i % 4][i / 4] =
            expanded_key[160 + i];
    }

    add_round_key(state, round_key);

    
    for (int round = 9; round >= 1; round--)
    {
        inv_shift_rows(state);
        inv_sub_bytes(state);

        for (int i = 0; i < 16; i++)
        {
            round_key[i % 4][i / 4] =
                expanded_key[round * 16 + i];
        }

        add_round_key(state, round_key);
        inv_mix_columns(state);
    }

    
    inv_shift_rows(state);
    inv_sub_bytes(state);

    for (int i = 0; i < 16; i++)
    {
        round_key[i % 4][i / 4] =
            expanded_key[i];
    }

    add_round_key(state, round_key);

    
    store_state(block, state);
}

#include <stdio.h>




void print_bytes(unsigned char data[16])
{
    for (int i = 0; i < 16; i++)
    {
        printf("%02X ", data[i]);
    }

    printf("\n");
}


int hex_value(char c)
{
    if (c >= '0' && c <= '9')
        return c - '0';

    if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;

    if (c >= 'a' && c <= 'f')
        return c - 'a' + 10;

    return -1;
}


int hex_to_bytes(const char *hex, unsigned char *bytes)
{
    
    if (strlen(hex) != 32)
        return -1;

    for (int i = 0; i < 16; i++)
    {
        int high = hex_value(hex[2 * i]);
        int low  = hex_value(hex[2 * i + 1]);

        if (high == -1 || low == -1)
            return -1;

        bytes[i] = (high << 4) | low;
    }

    return 0;
}


int read_hex_block(FILE *input, unsigned char block[16])
{
    char hex[33];

    size_t n = fread(hex, 1, 32, input);

    if (n == 0)
        return 0;

    if (n != 32)
        return -1;

    hex[32] = '\0';

    if (hex_to_bytes(hex, block) != 0)
        return -1;

    return 1;
}


int encrypt_file(FILE *input, FILE *output, unsigned char expanded_key[176])
{
    unsigned char current[16];
    unsigned char next[16];

    size_t current_n;
    size_t next_n;

    
    current_n = fread(current, 1, 16, input);

    while (1)
    {
        
        if (current_n < 16)
        {
            unsigned char padding = 16 - current_n;

            for (size_t i = current_n; i < 16; i++)
            {
                current[i] = padding;
            }

            aes_encrypt_block(current, expanded_key);
            write_hex_block(output, current);

            return 0;
        }

        
        next_n = fread(next, 1, 16, input);

        if (next_n == 0)
        {
            
            aes_encrypt_block(current, expanded_key);
            write_hex_block(output, current);

            
            for (int i = 0; i < 16; i++)
            {
                current[i] = 0x10;
            }

            aes_encrypt_block(current, expanded_key);
            write_hex_block(output, current);

            return 0;
        }

        
        aes_encrypt_block(current, expanded_key);
        write_hex_block(output, current);

        
        memcpy(current, next, 16);
        current_n = next_n;
    }
}


int decrypt_file(FILE *input, FILE *output, unsigned char expanded_key[176])
{
    unsigned char current[16];
    unsigned char next[16];

    int current_status;
    int next_status;

    
    current_status = read_hex_block(input, current);

    if (current_status == 0)
    {
        printf("Error: Empty ciphertext file.\n");
        return -1;
    }

    if (current_status == -1)
    {
        printf("Error: Invalid ciphertext format.\n");
        return -1;
    }

    while (1)
    {
        
        next_status = read_hex_block(input, next);

        
        aes_decrypt_block(current, expanded_key);

        if (next_status == 1)
        {
            
            fwrite(current, 1, 16, output);
            memcpy(current, next, 16);
        }
        else if (next_status == 0)
        {
            
            unsigned char padding = current[15];

            if (padding < 1 || padding > 16)
            {
                printf("Error: Invalid padding.\n");
                return -1;
            }

            for (int i = 16 - padding; i < 16; i++)
            {
                if (current[i] != padding)
                {
                    printf("Error: Invalid padding.\n");
                    return -1;
                }
            }

            fwrite(current, 1, 16 - padding, output);
            return 0;
        }
        else
        {
            printf("Error: Invalid ciphertext format.\n");
            return -1;
        }
    }
}


void vigenere_encrypt_file(FILE *input, FILE *output, const char *key)
{
    int c;
    int key_index = 0;
    int key_length = strlen(key);

    while ((c = fgetc(input)) != EOF)
    {
        if (c >= 'A' && c <= 'Z')
        {
            int shift = toupper(key[key_index % key_length]) - 'A';

            c = ((c - 'A' + shift) % 26) + 'A';
            key_index++;
        }
        else if (c >= 'a' && c <= 'z')
        {
            int shift = toupper(key[key_index % key_length]) - 'A';

            c = ((c - 'a' + shift) % 26) + 'a';
            key_index++;
        }

        fputc(c, output);
    }
}


void vigenere_decrypt_file(FILE *input, FILE *output, const char *key)
{
    int c;
    int key_index = 0;
    int key_length = strlen(key);

    while ((c = fgetc(input)) != EOF)
    {
        if (c >= 'A' && c <= 'Z')
        {
            int shift = toupper(key[key_index % key_length]) - 'A';

            c = ((c - 'A' - shift + 26) % 26) + 'A';
            key_index++;
        }
        else if (c >= 'a' && c <= 'z')
        {
            int shift = toupper(key[key_index % key_length]) - 'A';

            c = ((c - 'a' - shift + 26) % 26) + 'a';
            key_index++;
        }

        fputc(c, output);
    }
}


int valid_vigenere_key(const char *key)
{
    if (strlen(key) == 0)
        return 0;

    for (int i = 0; key[i] != '\0'; i++)
    {
        if (!isalpha((unsigned char)key[i]))
            return 0;
    }

    return 1;
}


void aes_encrypt_string(const char *input,
                        char *output,
                        unsigned char expanded_key[176])
{
    size_t length = strlen(input);
    size_t pos = 0;
    size_t out_pos = 0;

    while (pos < length || length % 16 == 0)
    {
        unsigned char block[16];
        size_t remaining = length - pos;
        size_t copy_n = remaining < 16 ? remaining : 16;

        memset(block, 0, 16);

        if (copy_n > 0)
            memcpy(block, input + pos, copy_n);

        unsigned char padding = 16 - copy_n;

        for (size_t i = copy_n; i < 16; i++)
            block[i] = padding;

        aes_encrypt_block(block, expanded_key);

        for (int i = 0; i < 16; i++)
        {
            sprintf(output + out_pos, "%02X", block[i]);
            out_pos += 2;
        }

        pos += copy_n;

        if (copy_n < 16)
            break;
    }

    output[out_pos] = '\0';
}


int aes_decrypt_string(const char *input,
                       char *output,
                       unsigned char expanded_key[176])
{
    size_t hex_length = strlen(input);

    
    if (hex_length == 0 || hex_length % 32 != 0)
    {
        return -1;
    }

    size_t output_pos = 0;

    for (size_t pos = 0; pos < hex_length; pos += 32)
    {
        char hex_block[33];
        unsigned char block[16];

        memcpy(hex_block, input + pos, 32);
        hex_block[32] = '\0';

        if (hex_to_bytes(hex_block, block) != 0)
        {
            return -1;
        }

        aes_decrypt_block(block, expanded_key);

        
        if (pos + 32 == hex_length)
        {
            unsigned char padding = block[15];

            if (padding < 1 || padding > 16)
            {
                return -1;
            }

            for (int i = 16 - padding; i < 16; i++)
            {
                if (block[i] != padding)
                {
                    return -1;
                }
            }

            for (int i = 0; i < 16 - padding; i++)
            {
                output[output_pos++] = block[i];
            }
        }
        else
        {
            for (int i = 0; i < 16; i++)
            {
                output[output_pos++] = block[i];
            }
        }
    }

    output[output_pos] = '\0';

    return 0;
}


int main(int argc, char *argv[])
{
    

    if (argc != 7)
    {
        
        printf("Usage:\n");

        printf("  File:\n");
        printf("    %s encrypt/decrypt aes file <input> <output> <hex-key>\n",
               argv[0]);

        printf("    %s encrypt/decrypt vigenere file <input> <output> <key>\n",
               argv[0]);

        printf("\n");

        printf("  String:\n");
        printf("    %s encrypt/decrypt aes string <input> - <hex-key>\n",
               argv[0]);

        printf("    %s encrypt/decrypt vigenere string <input> - <key>\n",
               argv[0]);

        return 1;
    }

    
    if (strcmp(argv[1], "encrypt") != 0 &&
        strcmp(argv[1], "decrypt") != 0)
    {
        printf("Invalid operation. Use encrypt or decrypt.\n");
        return 1;
    }

    if (strcmp(argv[2], "aes") != 0 &&
        strcmp(argv[2], "vigenere") != 0)
    {
        printf("Invalid cipher. Use aes or vigenere.\n");
        return 1;
    }

    if (strcmp(argv[3], "file") != 0 &&
        strcmp(argv[3], "string") != 0)
    {
        printf("Invalid mode. Use file or string.\n");
        return 1;
    }


    
    
    
    

    if (strcmp(argv[2], "aes") == 0)
    {
        unsigned char key[16];
        unsigned char expanded_key[176];

        
        if (hex_to_bytes(argv[6], key) != 0)
        {
            printf("Invalid AES-128 key.\n");
            printf("Key must contain exactly 32 hexadecimal characters.\n");
            return 1;
        }

        key_expansion(key, expanded_key);


        

        if (strcmp(argv[3], "string") == 0)
        {
            
            if (strcmp(argv[5], "-") != 0)
            {
                printf("For string mode, output must be '-'.\n");
                return 1;
            }

            if (strcmp(argv[1], "encrypt") == 0)
            {
                
                char encrypted[4096];

                aes_encrypt_string(
                    argv[4],
                    encrypted,
                    expanded_key
                );

                printf("Encrypted: %s\n", encrypted);
            }
            else
            {
                char decrypted[4096];

                if (aes_decrypt_string(
                        argv[4],
                        decrypted,
                        expanded_key) != 0)
                {
                    printf("AES string decryption failed.\n");
                    return 1;
                }

                printf("Decrypted: %s\n", decrypted);
            }

            return 0;
        }


        

        FILE *input = fopen(argv[4], "rb");

        if (input == NULL)
        {
            printf("Could not open input file.\n");
            return 1;
        }

        FILE *output = fopen(argv[5], "wb");

        if (output == NULL)
        {
            printf("Could not open output file.\n");
            fclose(input);
            return 1;
        }

        int result;

        if (strcmp(argv[1], "encrypt") == 0)
        {
            result = encrypt_file(
                input,
                output,
                expanded_key
            );
        }
        else
        {
            result = decrypt_file(
                input,
                output,
                expanded_key
            );
        }

        fclose(input);
        fclose(output);

        if (result != 0)
        {
            printf("AES operation failed.\n");
            return 1;
        }

        printf("AES operation completed successfully.\n");

        return 0;
    }


    
    
    

    if (strcmp(argv[2], "vigenere") == 0)
    {
        if (!valid_vigenere_key(argv[6]))
        {
            printf("Invalid Vigenere key.\n");
            printf("Key must contain only alphabetic characters.\n");
            return 1;
        }


        

        if (strcmp(argv[3], "string") == 0)
        {
            if (strcmp(argv[5], "-") != 0)
            {
                printf("For string mode, output must be '-'.\n");
                return 1;
            }

            

            int key_index = 0;
            int key_length = strlen(argv[6]);

            if (strcmp(argv[1], "encrypt") == 0)
            {
                for (int i = 0; argv[4][i] != '\0'; i++)
                {
                    char c = argv[4][i];

                    if (c >= 'A' && c <= 'Z')
                    {
                        int shift =
                            toupper(argv[6][key_index % key_length]) - 'A';

                        c = ((c - 'A' + shift) % 26) + 'A';

                        key_index++;
                    }
                    else if (c >= 'a' && c <= 'z')
                    {
                        int shift =
                            toupper(argv[6][key_index % key_length]) - 'A';

                        c = ((c - 'a' + shift) % 26) + 'a';

                        key_index++;
                    }

                    putchar(c);
                }

                putchar('\n');
            }
            else
            {
                for (int i = 0; argv[4][i] != '\0'; i++)
                {
                    char c = argv[4][i];

                    if (c >= 'A' && c <= 'Z')
                    {
                        int shift =
                            toupper(argv[6][key_index % key_length]) - 'A';

                        c = ((c - 'A' - shift + 26) % 26) + 'A';

                        key_index++;
                    }
                    else if (c >= 'a' && c <= 'z')
                    {
                        int shift =
                            toupper(argv[6][key_index % key_length]) - 'A';

                        c = ((c - 'a' - shift + 26) % 26) + 'a';

                        key_index++;
                    }

                    putchar(c);
                }

                putchar('\n');
            }

            return 0;
        }


        

        FILE *input = fopen(argv[4], "rb");

        if (input == NULL)
        {
            printf("Could not open input file.\n");
            return 1;
        }

        FILE *output = fopen(argv[5], "wb");

        if (output == NULL)
        {
            printf("Could not open output file.\n");
            fclose(input);
            return 1;
        }

        if (strcmp(argv[1], "encrypt") == 0)
        {
            vigenere_encrypt_file(
                input,
                output,
                argv[6]
            );
        }
        else
        {
            vigenere_decrypt_file(
                input,
                output,
                argv[6]
            );
        }

        fclose(input);
        fclose(output);

        printf("Vigenere operation completed successfully.\n");

        return 0;
    }

    return 0;
}