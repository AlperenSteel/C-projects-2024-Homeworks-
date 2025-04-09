/*Yusuf Alperen CELIK*/
/*
    The aim of this project was to encrypt a text wri4en to a file with the Caesar encryp8on method.
    While doing this encryp8on, the sec8ons between the comment lines will not be included in the
    encryp8on. A special pointer ('@') will be assigned to the star8ng point of this comment line, then
    the number of characters in the comment line will be counted, and then this number will be
    encrypted and an encrypted file will be created.
*/
#include <stdio.h>
int main() {
    /*  Şifreleme şuna göre yapılacak Ex. Student ID: ********* >  ********** = 23 = 2 + 3 = 5 */
    /* KEY IS 5*/
    /* “gcc --ansi encrypt_part1.c -o homework1_1” */
    /* Kod derlendikten sonra “./homework1_1 < input.txt > encrypted.txt” */
    char alphabet[61] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
    'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x',
    'y', 'z', '(', '<', '=', '+', ')', '[', '*', '/', ']', '{',
    '>', '!', '-', '}', '?', '\\', '&', '|', '%', '_', ';',
    '"', '#', '.', '\'', '0', '1', '2', '3', '4', '5', '6', '7',
    '8', '9'};
    char c;
    int comment_char_count = 0; /* Yorum satırındaki karakter sayısını tutacak değişken */
    /* Karakterleri oku */
    while (scanf("%c", &c) == 1) {
        if (c == '/') {
            scanf("%c", &c);
            if (c == '*') {
                while (scanf("%c", &c) == 1) {
                    if (c == '*') {
                        if (scanf("%c", &c) == 1 && c == '/') {
                            /* Yorum satırındaki toplam karakter sayısını şifrele ve yazdır */
                            int encrypted_count = 0;
                            int temp_count = comment_char_count;
                            printf("@ ");
                            if(comment_char_count > 9 && comment_char_count <= 99) /* basamak basamak yazdırmak için*/
                            {
                                if(temp_count /10 <= 9 && temp_count /10 >= 5)
                                {
                                    printf("%c", alphabet[(temp_count/10) - 5]); /* Mesela 9 --> e ye denk gelecek*/
                                }
                                else if(temp_count/10 >= 0 && temp_count/10 < 5)
                                {
                                    printf("%c", alphabet[(temp_count/10) + 56]);
                                }
                                if((temp_count % 10) <= 9 && (temp_count % 10) > 5)
                                {
                                    printf("%c", alphabet[(temp_count % 10) - 5]);
                                }
                                else if(temp_count%10 >= 0 && temp_count%10 < 5)
                                {
                                    printf("%c", alphabet[(temp_count%10) + 56]);
                                }
                            }    
                            else
                            {
                                if(temp_count <= 9 && temp_count >= 5)
                                {
                                    printf("%c", alphabet[temp_count - 5]);
                                }
                                else if(temp_count < 5 && temp_count >= 0)
                                {
                                    printf("%c", alphabet[temp_count + 56]);
                                }
                                
                            }           
                            comment_char_count = 0; /* Yorum satırındaki karakter sayısını sıfırla */
                            break;
                        }
                    }
                    else {
                        if (c != ' ') /* Boşluk karakterini yorum satırı içindeyken hesaba katma */
                            comment_char_count++; /* Yorum satırındaki boşluk dışımdaki her karakteri say */
                    }
                }
            }
            else
            {
                /* Yorum satırı başlamadığı için / karakterini şifreleyip ekrana bas */
                if (c != ' ' && c != '\t') { /* Boşluk ve tab karakterlerini yorum satırı içinde değilken kontrol et */
                    int i;
                    for (i = 0; i < 61; i++) 
                    {
                        if (c == alphabet[i]) 
                        {
                            int new_index = (i + 5) % 61; /* 5 ileri indeksi hesapla */
                            printf("-%c", alphabet[new_index]); /* Yeni karakteri yazdır */
                            break; /* Döngüyü sonlandır */
                        }
                    }
                }
                else
                {
                    printf("-%c", c); /*print - and space */
                }
            }
        } 
        else
        { /* Yorum satırı içinde değiliz, karakteri 5 ileriye dönüştür */
            if (c != ' ' && c != '\t') { /* Boşluk ve tab karakterlerini yorum satırı içinde değilken kontrol et */
                int i;
                for (i = 0; i < 61; i++) 
                {
                    if (c == alphabet[i]) 
                    {
                        int new_index = (i + 5) % 61; /* 5 ileri indeksi hesapla */
                        printf("%c", alphabet[new_index]); /* Yeni karakteri yazdır */
                        break; /* Döngüyü sonlandır */
                    }
                }
            } 
            else 
            { /* Boşluk karakterini ve tab'ı yorum satırı içinde değilken olduğu gibi yazdır*/
                printf("%c", c);
            } 
        }
        if (c == '\n') { /* Satır sonu kontrolü */
            printf("\n");
        }
    }
    return 0;
}
