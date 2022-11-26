#include<stdio.h>
#include<string.h>
#include <process.h>

struct User
{
    int uid,sem;
    char name[100], pass[100], email[100];
    int numOfFriend;
    int friends[100];
};

struct User user[100];
int n,q;

void getData()
{
    FILE *fp;
    fp = fopen("userDB.txt", "r");

    for(int i = 0; ; i++)
    {
        if( feof(fp) )
        {
            break ;
        }
        fscanf(fp, "%d", &user[i].uid);
        fscanf(fp, "%d", &user[i].sem);
        if( fgets (user[i].name, 100, fp)!=NULL )
        {
            fgets(user[i].name,100,fp);
        }
        fscanf(fp, "%s", user[i].pass);
        fscanf(fp, "%s", user[i].email);
        fscanf(fp, "%d", &user[i].numOfFriend);

        for(int j = 0; j < user[i].numOfFriend; j++)
        {
            fscanf(fp, "%d", &user[i].friends[j]);
        }
        n = i;
    }

    fclose(fp);
}

void writeData()
{
    FILE *fp;
    fp = fopen("userDB.txt", "w");

    for(int i = 0; i<n ; i++)
    {
        fprintf(fp, "%d\n", user[i].uid);
        fprintf(fp, "%d\n", user[i].sem);

        fprintf(fp, "%s", user[i].name);
        fprintf(fp, "%s\n", user[i].pass);
        fprintf(fp, "%s\n", user[i].email);
        fprintf(fp, "%d\n", user[i].numOfFriend);
        for(int j = 0; j < user[i].numOfFriend; j++)
        {
            fprintf(fp, "%d ", user[i].friends[j]);
        }
        fprintf(fp, "\n");

    }

    fclose(fp);
}

void showInfo()
{

    for(int i = 0; i<n ; i++)
    {
        if(q == user[i].sem)
        {

            printf("Name - %s", user[i].name);
            printf("Password - %s\n", user[i].pass);
            printf("Email - %s\n", user[i].email);
            printf("Friends - %d\n", user[i].numOfFriend);

            printf("\n\n");
        }
    }
}

void addInfo()
{

    char nm[100],pswrd[100], mail[100];
    int semstr;
    printf("Name: ");

     if( fgets(nm,100,stdin)!=NULL )
        {
            fgets(nm,100,stdin);
        }


    printf("Enter Password: ");
    scanf("%s", pswrd);
    printf("Enter Email: ");
    scanf("%s", mail);
    printf("Enter Semester: ");
    scanf("%d", &semstr);

    user[n].uid = n+1;
    user[n].sem = semstr;
    strcpy(user[n].name, nm);
    strcpy(user[n].pass, pswrd);
    strcpy(user[n].email,mail);
    user[n].numOfFriend = 0;
    n++;


}

void deleteInfo()
{
    int pos = -1,temp1,arr[100];
    for(int i = 0; i<n; i++)
    {
        temp1 = user[i].numOfFriend;
        if(q == user[i].uid)
        {
            pos = i;
        }
    }

    for(int i = 0; i<n; i++)
    {

        for(int j = 0; j<temp1; j++)
        {

            if(q == user[i].friends[j])
            {
                user[i].numOfFriend = user[i].numOfFriend-1;
            }
        }
    }

    if(pos != -1)
    {
        for(int i = pos; i<n-1; i++)
        {
            user[i] = user[i+1];
            for(int j = 0; j<temp1; j++)
            {
                user[i].friends[j] = user[i].friends[j+1];
            }
        }
        n--;
    }
}

int addFriend(int id1,int id2)
{
    for(int i = 0; i<n; i++)
    {
        if(user[i].uid == id1)
        {
            user[i].numOfFriend++;
            user[i].friends[user[i].numOfFriend-1] = id2;
        }
        if(user[i].uid == id2)
        {
            user[i].numOfFriend++;
            user[i].friends[user[i].numOfFriend-1] = id1;
        }
    }
}

void strongPass()
{

    for(int i = 0; i<n; i++)
    {
        int cnt = 0,cnt1 = 0, cnt2 = 0, cnt3 = 0, cnt4= 0,sum;
        int size = strlen(user[i].pass);
        if(size >= 8)
        {
            cnt++;
        }
        for(int j = 0; j<size; j++)
        {
            if(user[i].pass[j] >= 'A' &&  user[i].pass[j]<= 'Z')
            {
                cnt1 = 1;
            }
            if(user[i].pass[j] >= 'a' &&  user[i].pass[j]<= 'z')
            {
                cnt2 = 1;
            }
            if(user[i].pass[j] == '#' || user[i].pass[j] == '$' || user[i].pass[j] == '&' || user[i].pass[j] == '@' || user[i].pass[j] == '*')
            {
                cnt3 = 1;
            }
            if(user[i].pass[j] >= '0' && user[i].pass[j] <= '9')
            {
                cnt4= 1;
            }
        }
        sum = cnt+cnt1+cnt2+cnt3+cnt4;
        if(sum == 5)
        {

            printf("Name - %s", user[i].name);
            printf("Password - %s\n\n", user[i].pass);
        }

    }
}
void searchName()
{
    char str[100];
    printf("Enter Name: ");
    scanf("%s", str);
    for(int i = 0; i<n; i++)
    {
        if(strstr(user[i].name,str) != NULL)
        {
            printf("%s", user[i].name);
            printf("%s\n\n", user[i].email);
        }
    }
}

int main()
{
    while(1){

            getData();
    int x,f1,f2;
    printf("1. Semester Wise User\n");
    printf("2. Delete User\n");
    printf("3. Add User\n");
    printf("4. Make Friend\n");
    printf("5. Check Password\n");
    printf("6. Search by Name\n");
    printf("0. Exit\n");

    printf("Enter Number: ");
    scanf("%d", &x);
    system("cls");

    if(x == 1){
            printf("Enter Semester: ");
    scanf("%d", &q);
        showInfo();
    }
    if(x == 2){
        getData();
        printf("Enter UID: ");
        scanf("%d", &q);
        deleteInfo();
         writeData();
    }

    if(x == 3){
        addInfo();
        writeData();
    }
    if(x == 4){
        printf("Enter UID: ");
        scanf("%d", &f1);
        printf("Enter UID: ");
        scanf("%d", &f2);

        addFriend(f1,f2);
        writeData();
    }

    if(x == 5){
        printf("Users With Strong Passwords Are: \n\n");
        strongPass();
    }

    if(x == 6){
        searchName();
    }
    if(x == 0){
        exit(1);
    }
    }

}
