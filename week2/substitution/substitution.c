#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

string substitute(string plain_text, string key, char cipher_text[]);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage %s key\n", argv[0]);
        return 1;
    }
    else if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    else
    {
        string key = argv[1];
        for (int i = 0; key[i] != '\0'; i++)
        {
            if (!isalpha(key[i]))
            {
                printf("Key must contain alphabetic characters only.\n");
                return 1;
            }
        }

        string plain_text = get_string("plaintext: ");
        char cipher_text[strlen(plain_text)];
        printf("ciphertext: %s\n", substitute(plain_text, key, cipher_text));
    }
}

string substitute(string plain_text, string key, char cipher_text[])
{
    for (int i = 0; plain_text[i] != '\0'; i++)
    {
        if (!isalpha(plain_text[i]))
        {
            cipher_text[i] = plain_text[i];
        }
        else
        {
            char cipher_char = key[tolower(plain_text[i]) - 'a'];
            cipher_text[i] = isupper(plain_text[i]) ? toupper(cipher_char) : tolower(cipher_char);
        }
    }

    return cipher_text;
}