#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

#define MAX_CHARACTER 128

struct data {
    char id[MAX_CHARACTER];
    char firstName[MAX_CHARACTER];
    char lastName[MAX_CHARACTER];
    char class[MAX_CHARACTER];
};

void line();
void message();
int menuView();

int create()
{
    FILE *fp;
    struct data student;
    int idLength = 17;
    char dataId[MAX_CHARACTER];
    
    printf("\n=== Create Data ===\n\n");
    printf("NIM Praktikan\t\t: ");
   
    fflush(stdin);
    gets(student.id);

    if(strlen(student.id) == idLength)
    {
        for(int i = 0; i < 2; i++)
        {
            char singelChar = student.id[i];

            if(singelChar >= 64 && singelChar <= 90) continue;
        
            printf("\n");
            message("Tidak boleh ada karakter asing, hanya A-Z dan 0-9.");
            return create();
        }

        for(int i = 2; i < idLength; i++)
        {
            char singelChar = student.id[i];

            if(singelChar >= 48 && singelChar <= 57) continue;
        
            printf("\n");
            message("Tidak boleh ada karakter asing, hanya A-Z dan 0-9.");
            return create();
        }

        fp = fopen("data.txt", "r");

        if(fp)
        {
            while(!feof(fp))
            {
                fscanf(fp, "%[^|]|%*[^|]|%*[^|]|%*[^|]|\n", dataId);
                
                if(strcmp(student.id, dataId) == 0)
                {
                    printf("\n");
                    message("NIM telah digunakan.");
                    fclose(fp);
                    return create();
                }
            }
        }

        fclose(fp);

        printf("\n\nNama Depan Praktikan\t: ");
        fflush(stdin);
        gets(student.firstName);

        printf("\n\nNama Belakang Praktikan\t: ");
        fflush(stdin);
        gets(student.lastName);

        printf("\n\nKelas Pemrograman Dasar\t: ");
        fflush(stdin);
        gets(student.class);
        strupr(student.class);

        fp = fopen("data.txt", "a");

        fprintf(fp, "%s|%s|%s|%s|\n", student.id, student.firstName, student.lastName, student.class);
        fclose(fp);

        printf("\n");
        message("Data berhasil ditambahkan.");
        return 0;
    }
    else
    {
        printf("\n");
        message("NIM tidak boleh kurang dari atau lebih dari 17 karakter!");
        return create();
    }
}

void read()
{
    FILE *fp;
    struct data student;
    printf("\n=== List Data ===\n\n");
    fp = fopen("data.txt", "r");
    
    if(fp)
    {
        int number = 0;

        if(fscanf(fp, "%*[^|]|%*[^|]|%*[^|]|%*[^|]|\n") != EOF)
        {
            rewind(fp);
            line();
            printf("|%-3s |%-20s  |%-32s  |%-32s  |%-10s|\n", "NO", "NIM", "NAMA DEPAN", "NAMA BELAKANG", "KELAS");
            line();
            
            while(!feof(fp))
            {
                fscanf(fp, "%[^|]|%[^|]|%[^|]|%[^|]|\n", student.id, student.firstName, student.lastName, student.class);
                printf("|%-3d |%-20s  |%-32s  |%-32s  |%-10s|\n", number + 1, student.id, student.firstName, student.lastName , student.class);
                number++;
            }

            line();
        }
        else
        {
            message("Data masih kosong.");
        }
    }
    else
    {
        message("Data tidak tersedia.");
    }
    fclose(fp);
}

int update()
{
    FILE *fp, *tmp;
    struct data student;
    char searchId[MAX_CHARACTER];
    int isFinded = 0;

    printf("\n=== Update Data ===\n\n");
    printf("Masukan NIM Praktikan\t: ");
    scanf("%s", searchId);
    strupr(searchId);
    
    fp = fopen("data.txt", "r");
    tmp = fopen("tmp.txt", "w");


    while(!feof(fp))
    {
        fscanf(fp, "%[^|]|%[^|]|%[^|]|%[^|]|\n", student.id, student.firstName, student.lastName, student.class);

        if(strcmp(searchId, student.id) == 0)
        {
            isFinded = 1;

            printf("\n\nNama Depan Praktikan\t: ");
            fflush(stdin);
            gets(student.firstName);

            printf("\n\nNama Belakang Praktikan\t: ");
            fflush(stdin);
            gets(student.lastName);

            printf("\n\nKelas Pemrograman Dasar\t: ");
            fflush(stdin);
            gets(student.class);
            strupr(student.class);

            fprintf(tmp, "%s|%s|%s|%s|\n", student.id, student.firstName, student.lastName, student.class);
            continue;
        }
        else
        {
            fprintf(tmp, "%s|%s|%s|%s|\n", student.id, student.firstName, student.lastName, student.class);
        }
    }
    
    fclose(fp);
    remove("data.txt");
    
    fclose(tmp);
    rename("tmp.txt", "data.txt");
    
    printf("\n");

    if(isFinded) message("Data berhasil diubah.");
    else message("Data tidak dapat ditemukan.");

    return 0;
}

int destroy()
{
    FILE *fp, *tmp;
    struct data student;
    char searchId[MAX_CHARACTER];
    int isFinded = 0;

    printf("\n=== Delete Data ===\n\n");
    printf("Masukan NIM Praktikan\t: ");
    scanf("%s", searchId);
    strupr(searchId);

    fp = fopen("data.txt", "r");
    tmp = fopen("tmp.txt", "w");

    while(!feof(fp))
    {
        fscanf(fp, "%[^|]|%[^|]|%[^|]|%[^|]|\n", student.id, student.firstName, student.lastName, student.class);

        if(strcmp(searchId, student.id) == 0)
        {
            isFinded = 1;
            continue;
        }
        else
        {
            fprintf(tmp, "%s|%s|%s|%s|\n", student.id, student.firstName, student.lastName, student.class);
        }
    }
    
    fclose(fp);
    remove("data.txt");

    fclose(tmp);
    rename("tmp.txt", "data.txt");

    printf("\n");

    if(isFinded) message("Data berhasil dihapus.");
    else message("Data tidak dapat ditemukan.");

    return 0;
}

int search()
{
    FILE *fp;
    struct data student;
    char searchId[MAX_CHARACTER];

    printf("\n=== Search Data ===\n\n");
    printf("Masukan NIM Praktikan\t: ");
    scanf("%s", searchId);
    strupr(searchId);
    printf("\n");

    fp = fopen("data.txt", "r");

    while(!feof(fp))
    {
        fscanf(fp, "%[^|]|%[^|]|%[^|]|%[^|]|\n", student.id, student.firstName, student.lastName, student.class);

        if(strcmp(searchId, student.id) == 0)
        {
            line();
            printf("\nNIM Praktikan\t\t: %s\n\nNama Depan Praktikan\t: %s\n\nNama Belakang Praktikan\t: %s\n\nKelas Pemrograman Dasar\t: %s\n\n", student.id, student.firstName, student.lastName , student.class);
            line();

            fclose(fp);
            return 0;
        }
    }
    fclose(fp);
    
    message("Data tidak dapat ditemukan.");
    return 0;
}

int main()
{
    printf("Now Loading");
    Sleep(1000);
    printf(". ");
    Sleep(1000);
    printf(". ");
    Sleep(1000);
    printf(". ");
    Sleep(1000);
    printf(". ");
    Sleep(1000);
    printf(". \n\n");
    system("cls");

    int menu;
    do
    {
        menu = menuView();
        system("cls");

        switch(menu)
        {
            case 1:
                create();
            break;
            case 2:
                read();
            break;
            case 3:
                update();
            break;
            case 4:
                destroy();
            break;
            case 5:
                search();
            break;
        }
    } while (menu != 0);

    return 0;
}

void line()
{
    for (int i = 0; i < 110; i++) printf("-");
    printf("\n");
}

void message(char *message)
{
    line();
    printf("\n%s\n\n", message);
    line();
}

int menuView()
{
    int menu;
    
    printf("\nSistem Pendataan Akun I-Lab Infotech\n\n=== Pilihan Menu ===\n\n1. Create Data.\n2. Show Data.\n3. Update Data.\n4. Delete Data.\n5. Search Data.\n0. Exit.\n\nPilih Menu: ");
    scanf("%d", &menu);

    return menu;
}