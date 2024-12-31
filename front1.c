#include <stdio.h>
#include <string.h>
#include <conio.h>
struct admin
{
    int rmn, size, id;
    char TOR;
} record;

void addroom()
{
    FILE *fp;
    fp = fopen("admin.txt", "a");

    int n, i;
    struct admin record;
    printf("entre the no. records");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        printf("\nEnter records %d details:\n", i + 1);
        printf("ROOM NO. ");
        scanf("%d", &record.rmn);
        printf("Size Of Room ");
        scanf("%d", &record.size);
        printf("Booking Press(1 for book / 0 for not book) ");
        scanf("%d", &record.id);
        getchar(); // To consume the newline character left by scanf
        // Write the record to the file
        fwrite(&record, sizeof(struct admin), 1, fp);
    }

    printf("Records saved to file successfully.\n");
    fclose(fp);
}
void searchroom()
{
    FILE *fp;
    struct admin e;
    int rm, flag = 0;
    fp = fopen("admin.txt", "r+");
    if (fp == NULL)
    {
        printf("File is not created");
    }
    printf("Entre the ROOM NO you want to search");
    scanf("%d", &rm);
    while ((fread(&e, sizeof(e), 1, fp) > 0))
    {
        if (e.rmn == rm)
        {
            flag = 1;
            printf("record is found\n");
            printf("%d \t %d \t %d\n", e.rmn, e.size, e.id);
        }
    }
    if (flag = 0)
    {
        printf("Record is Not found");
    }
    fclose(fp);
}
void emproom()
{
    FILE *fp;
    fp = fopen("admin.txt", "r");
    struct admin e;
    while (fread(&e, sizeof(e), 1, fp) != NULL)
    {
        if (e.id == 0)
            printf("Room no is %d\t Room size is  %d \tStatus %d\n", e.rmn, e.size, e.id);
    }
}
void nonemproom()
{
    FILE *fp;
    fp = fopen("admin.txt", "r");
    struct admin e;
    while (fread(&e, sizeof(e), 1, fp) != NULL)
    {
        if (e.id == 1)
            printf("Room no is %d Room size is  %d Book \n", e.rmn, e.size, e.id);
    }
}
void viewroom()
{
    struct admin record;
    FILE *fp;
    fp = fopen("admin.txt", "r+");
    printf(".......RECORDS.........\nROOM NO. ROOM SIZE ROOM STATUS\n");

    while (fread(&record, sizeof(struct admin), 1, fp))
    {
        printf("%d\t %d\t     %d\n", record.rmn, record.size, record.id);
    }
    fclose(fp);
}

void deletebook() {}
void searchbook()
{
    struct admin e;
    FILE *fp;
    fp = fopen("temp1.txt", "r+");
    if (fp == NULL)
    {
        printf("You don't have any booking");
    }

    while (fread(&e, sizeof(e), 1, fp) != NULL)
    {
        if (e.id == 1)
            printf("Room no is %d Room size is  %d \n", e.rmn, e.size);
    }
    fclose(fp);
}
void viewroom1()
{
    struct admin e, e1;
    FILE *fp;
    int x, n, flag = 0, rm, i = 1;
    fp = fopen("admin.txt", "r+");

    while (fread(&e, sizeof(e), 1, fp) != NULL)
    {
        if (e.id == 0)
            printf("Room no is %d Room size is  %d \n", e.rmn, e.size);
    }
    FILE *temp = fopen("temp.txt", "wb"); // Temporary  file to store updated data
    FILE *temp1 = fopen("temp1.txt", "wb");
    rewind(fp);

    printf("Do you wish to book\n1.YES\n2.NO\n");
    scanf("%d", &x);
    switch (x)
    {
    case 1:

        if (fp == NULL)
        {
            printf("File is not created");
        }
        printf("Entre the ROOM NO you want to Book\n");
        scanf("%d", &rm);
        while (fread(&e1, sizeof(e1), 1, fp) != NULL)
        {
            if (e1.rmn == rm)
            {
                flag = 1;
                e1.id = 1;

                printf("Your room is booked");
                fwrite(&e1, sizeof(struct admin), 1, temp1);
            }
            fwrite(&e1, sizeof(struct admin), 1, temp);
        }
        fclose(fp);
        fclose(temp);
        fclose(temp1);

        remove("admin.txt");
        rename("temp.txt", "admin.txt");
        if (flag = 0)
        {
            printf("Record is Not found");
        }

        break;

    default:
        printf("THANK YOU FOR VISIT");
        break;
    }
}
void user()
{

    int n;
    char c;
    do
    {
        printf(".......operations.......\n1.View Room\n2.Delete Booking\n3.Search Booking\n4.Exit\n");
        scanf("%d", &n);
        switch (n)
        {
        case 1:
            viewroom1();
            break;
        case 2:
            deletebook();
            break;
        case 3:
            searchbook();
            break;

        default:
            break;
        }
        printf("Yo you wish to contine ");
        scanf("%s", &c);
    } while ((c == 'y') || (c == 'Y'));
}
void Admin()

{
    int n;
    char c = 'y';
    while ((c == 'y' || (c == 'Y')))
    {
        printf(".......operations.......\n1.Add Room\n2.View Room\n3.Empty rooms Room\n4.Non.Empty Room\n5.Search Room\n");
        scanf("%d", &n);

        switch (n)
        {
        case 1:
            addroom();
            break;
        case 2:
            viewroom();
            break;
        case 3:
            emproom();
            break;
        case 4:
            nonemproom();

            break;
        case 5:
            searchroom();
            break;

        default:
            break;
        }
        printf("Do you wish to more change");
        scanf("%s", &c);
    }
}
void main()
{
    int n;
    char c;
    do
    {
        printf(".........Menu.......\n1.Admin\n2.User\n");
        scanf("%d", &n);
        switch (n)
        {
        case 1:
            Admin();
            break;
        case 2:
            user();
            break;
        default:
            break;
        }

        printf("you want to contine");
        scanf("%s", &c);
    } while (c == 'y' || c == 'Y');
    getch();
}