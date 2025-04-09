#include <stdio.h>
int main() {
    char alphabet[61] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
    'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x',
    'y', 'z', '(', '<', '=', '+', ')', '[', '*', '/', ']', '{',
    '>', '!', '-', '}', '?', '\\', '&', '|', '%', '_', ';',
    '"', '#', '.', '\'', '0', '1', '2', '3', '4', '5', '6', '7',
    '8', '9'};
    char c;
    int flag = 0;
    char a;
    /* Karakterleri oku */
    while (scanf("%c", &c) == 1) 
    {
        if (c == '@') 
        {
            printf("/*There are: ");
        scanf("%c", &c); /*boşluğu atlamak için*/
        while(scanf("%c", &c) == 1)
        {
            if(c == '\n')
            {
                break;
            }
            else
            {
                int i;
                int j;
                for (i = 0; i < 61; i++) 
                {
                    if (c == alphabet[i]) 
                    {
                        {                        
                        int new_index = (i - 5) % 61; /* 5 geri indeksi hesapla (Mesela i = 0 ise -5 % 61 = 56) */
                        printf("%c", alphabet[new_index]); /* Yeni karakteri yazdır */
                        }
                    }
                }
            }
        }
        printf(" characters as comment.*/\n");
        }
        else /* Yorum satırı içinde değiliz, karakteri 5 geri dönüştür */
        {
            if(c == '\n')
            {
                printf("\n");
            }
            else if (c != ' ' && c != '\t') 
            { /* Boşluk ve tab karakterlerini yorum satırı içinde değilken kontrol et */
                int i;
                for (i = 0; i < 61; i++) 
                {
                    if (c == alphabet[i]) {
                        int new_index = (i - 5) % 61; /* 5 ileri indeksi hesapla */
                        printf("%c", alphabet[new_index]); /* Yeni karakteri yazdır */
                        break; /* Döngüyü sonlandır */
                    }
                }
            } 
            else if (c == '\t' || c == '\n' || c == ' ') 
            {
            printf("%c", c);
            }
        }
    }
    return 0;
}

/* “./homework1_2 < encrypted.txt > decrypted.txt” */
/*“gcc --ansi 220104004064_part2.c -o homework1_2”. */