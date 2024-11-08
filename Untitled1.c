#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
struct data{
        char a[100];
        char b[100];
        char c[100];
        char d[100];
        char e[100];
        char f[100];
        char g[100];
    };
struct book
{
    char bookname[50];
    int booknumber;
    int quantity;
};
struct student
{
    char studentname[30];
    char studentid[30];
    int number;
};
struct library
{
    char studentname1[100];
    char studentid1[100];
    char bookname1[100];
    int bookID;
    int issuedate;
    int returndate;
    int no;
};
int check(char *);
void issuebook();
void returnbook();
void details();
void rewritestudentsdata(char *);
void rewritebooksdata(int);
void rewritestudentsdata1(char *);
void rewritebooksdata1(char *);
void addbook(void);
void addstudent(void);
int main()
{
    int choice;
    do
    {
        printf("\n\n1.Issue book\n2.Retrun book\n3.Check detail\n4.Add new book (Only if you are librarian)\n5.Add new student data (Only if you are librarian)\n0.exit\n");
        printf("Enter the choice:");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            issuebook();
            break;
        case 2:
            returnbook();
            break;
        case 3:
            details();
            break;
        case 4:
            addbook();
            break;
        case 5:
            addstudent();
            break;
        case 0:exit(0);
        default:printf("Please enter correct choice\n");
        }
    } while (choice != 0);
    return 0;
}
void issuebook()
{
    printf("List of Books avaliable\n");
    FILE *fp, *fp1, *fp2;
    fp = fopen("booksdata.txt", "r");
    fp2 = fopen("librarydata.txt", "a");
    struct book b;
    int i = 1;
    while (!feof(fp))
    {

        fscanf(fp, "%s", b.bookname);
        fscanf(fp, "%d", &b.booknumber);
        fscanf(fp, "%d", &b.quantity);
        if(feof(fp)){
        break;}
        printf("%d.%s\n", i, b.bookname);
        printf("Number of Copies avaliable:%d\n", b.quantity);
        i++;
    }
    fclose(fp);
    fp = fopen("booksdata.txt", "r");
    i = 1;
    int n, c;
    char id[30];
    printf("Enter the book number u need:");
    scanf("%d", &n);
    while (!feof(fp))
    {
        fscanf(fp, "%s", b.bookname);
        fscanf(fp, "%d", &b.booknumber);
        fscanf(fp, "%d", &b.quantity);
        if (i == n)
        {
            printf("Enter student id:");
            scanf("%s", id);
            c = check(id);
            if (c == 0)
            {
                struct library crc;
                struct student s;
                fp1 = fopen("studentsdata.txt", "r");
                while (!feof(fp1))
                {
                    fscanf(fp1, "%s", s.studentname);
                    fscanf(fp1, "%s", s.studentid);
                    fscanf(fp1, "%d", &s.number);
                    c = strcasecmp(id, s.studentid);
                    if (c == 0)
                    {
                        strcpy(crc.studentname1, s.studentname);
                        strcpy(crc.studentid1, s.studentid);
                        strcpy(crc.bookname1, b.bookname);
                        crc.bookID = b.booknumber;
                        s.number = s.number + 1;
                        crc.no = s.number;
                        printf("Enter issue Date in YYYY-MM-DD form:");
                        scanf("%d", &crc.issuedate);
                        crc.returndate = crc.issuedate + 15;
                        int j, k, l;
                        j = crc.returndate % 100;
                        crc.returndate = crc.returndate / 100;
                        k = crc.returndate % 100;
                        crc.returndate = crc.returndate / 100;
                        l = crc.returndate;
                        if (j > 31 && (k == 1 || k == 3 || k == 5 || k == 7 || k == 8 || k == 10 || k == 12))
                        {
                            k = k + 1;
                            j = j - 31;
                        }
                        if (j > 30 && (k == 4 || k == 6 || k == 9 || k == 11))
                        {
                            k = k + 1;
                            j = j = 31;
                        }
                        if (k == 2 && j > 29)
                        {
                            if (j % 4 == 0 || j % 400 == 0)
                            {
                                k = k + 1;
                                j = j - 29;
                            }
                        }
                        if (k == 2 && j > 28)
                        {
                            k = k + 1;
                            j = j - 28;
                        }
                        fprintf(fp2, "StudentName:");
                        fputs(crc.studentname1, fp2);
                        fprintf(fp2, "\n");
                        fprintf(fp2, "StudentID:");
                        fputs(crc.studentid1, fp2);
                        fprintf(fp2, "\n");
                        fprintf(fp2, "Bookname:");
                        fputs(crc.bookname1, fp2);
                        fprintf(fp2, "\n");
                        fprintf(fp2, "BookID:%d\n", crc.bookID);
                        int day,mo;
                        day=crc.issuedate%100;
                        crc.issuedate=crc.issuedate/100;
                        mo=crc.issuedate%100;
                        crc.issuedate=crc.issuedate/100;
                        fprintf(fp2, "IssueDate:%d-%d-%d",day,mo,crc.issuedate);
                        fprintf(fp2, "\n");
                        fprintf(fp2, "ReturnDate:%d-%d-%d\n",j,k,crc.returndate);
                        fprintf(fp2, "Numberofbooksissuedis:%d\n\n", crc.no);
                        rewritestudentsdata(s.studentid);
                        rewritebooksdata(b.booknumber);
                    }
                }
            }
            else
                printf("You entered wrong student ID\n");
        }
      i++;
    }
    if (n>i)
        printf("chose existing book\n");
    fclose(fp);
    fclose(fp1);
    fclose(fp2);
}
void returnbook()
{
    struct data r;
    char id[100]={"StudentID:"};
    char u[100]={"BookID:"};
    FILE *fp,*fp1;
    fp=fopen("librarydata.txt","r");
    fp1=fopen("tempdata.txt","w");
    char k[10],l[10];
    int i,j=0;
    printf("Enter the student ID:");
    scanf("%s",k);
    printf("Enter book ID:");
    scanf("%s",l);
    strcat(id,k);
    strcat(u,l);
    while(!feof(fp)){
        fscanf(fp,"%s",r.a);
        fscanf(fp,"%s",r.b);
        fscanf(fp,"%s",r.c);
        fscanf(fp,"%s",r.d);
        fscanf(fp,"%s",r.e);
        fscanf(fp,"%s",r.f);
        fscanf(fp,"%s",r.g);
        if(feof(fp)) break;
        i =strcasecmp(id,r.b);
        int y=strcasecmp(u,r.d);
        if(i==0 && y==0){
            rewritestudentsdata1(r.b);
            rewritebooksdata1(r.d);
        }
        else{
            fputs(r.a,fp1);
            fprintf(fp1,"\n");
            fputs(r.b,fp1);
            fprintf(fp1,"\n");
            fputs(r.c,fp1);
            fprintf(fp1,"\n");
            fputs(r.d,fp1);
            fprintf(fp1,"\n");
            fputs(r.e,fp1);
            fprintf(fp1,"\n");
            fputs(r.f,fp1);
            fprintf(fp1,"\n");
            fputs(r.g,fp1);
            fprintf(fp1,"\n\n");

        }
        j++;
    }
    fclose(fp);
    fclose(fp1);
    fp = fopen("librarydata.txt","w");
    fp1 =fopen("tempdata.txt","r");
    while(!feof(fp1)){
     char c = fgetc(fp1);
     while(c!= EOF){
        fputc(c,fp);
        c=fgetc(fp1);
     }}
     fclose(fp);
     fclose(fp1);
}
void details()
{
    struct data d;
    char id[100]={"StudentID:"};
    FILE *fp;
    fp=fopen("librarydata.txt","r");
    char k[10];
    int i,j=0;
    printf("Enter the student ID:");
    scanf("%s",k);
    strcat(id,k);
    while(!feof(fp)){
        fscanf(fp,"%s",d.a);
        fscanf(fp,"%s",d.b);
        fscanf(fp,"%s",d.c);
        fscanf(fp,"%s",d.d);
        fscanf(fp,"%s",d.e);
        fscanf(fp,"%s",d.f);
        fscanf(fp,"%s",d.g);
        if(feof(fp))
        break;
        i =strcasecmp(id,d.b);
        if(i==0){
            printf("%s\n",d.a);
            printf("%s\n",d.b);
            printf("%s\n",d.c);
            printf("%s\n",d.d);
            printf("%s\n",d.e);
            printf("%s\n",d.f);
            printf("%s\n",d.g);

        }
    }
}
int check(char a[])
{
    FILE *fp3;
    int k;
    fp3 = fopen("studentsdata.txt", "r");
    struct student s;
    while (!feof(fp3))
    {
        fscanf(fp3, "%s", s.studentname);
        fscanf(fp3, "%s", s.studentid);
        fscanf(fp3, "%d", &s.number);
        k = strcasecmp(a, s.studentid);
        if (k == 0)
        {
            fclose(fp3);
            return 0;
        }
    }
    fclose(fp3);
    return 1;
}
void rewritestudentsdata(char b[]){
    FILE *fp1,*fp2;
    struct student s;
    int i,k;
    char c;
    fp1 = fopen("studentsdata.txt","r");
    fp2 = fopen("tempdata.txt","w");
    while(!feof(fp1)){
        fscanf(fp1, "%s", s.studentname);
        fscanf(fp1, "%s", s.studentid);
        fscanf(fp1, "%d", &s.number);
        if(feof(fp1))
        break;
        i=strcasecmp(s.studentid,b);
        if(i==0)
        {
            k = s.number+1;
        fprintf(fp2,"%s\n",s.studentname);
        fprintf(fp2,"%s\n",s.studentid);
        fprintf(fp2,"%d\n",k);
        }
        else{
        fprintf(fp2,"%s\n",s.studentname);
        fprintf(fp2,"%s\n",s.studentid);
        fprintf(fp2,"%d\n",s.number);
        }
    }
    fclose(fp1);
    fclose(fp2);
    fp1 = fopen("studentsdata.txt","w");
    fp2 = fopen("tempdata.txt","r");
     while(!feof(fp2)){
        c = fgetc(fp2);
     while(c!= EOF){
        fputc(c,fp1);
        c=fgetc(fp2);
     }
     }
     fclose(fp1);
     fclose(fp2);
}
void rewritebooksdata(int a){
    FILE *fp,*fp2;
    struct book b;
    fp = fopen("booksdata.txt","r");
    fp2 = fopen("tempdata.txt","w");
    while (!feof(fp))
    {
        fscanf(fp, "%s", b.bookname);
        fscanf(fp, "%d", &b.booknumber);
        fscanf(fp, "%d", &b.quantity);
        if(feof(fp))
        break;
    if(a==b.booknumber)
        {
            fputs(b.bookname,fp2);
            fprintf(fp2,"\n");
            fprintf(fp2,"%d\n",b.booknumber);
            b.quantity = b.quantity-1;
            fprintf(fp2,"%d\n",b.quantity);
        }
    else
        {
            fputs(b.bookname,fp2);
            fprintf(fp2,"\n");
            fprintf(fp2,"%d\n",b.booknumber);
            fprintf(fp2,"%d\n",b.quantity);
        }
    }
    fclose(fp);
    fclose(fp2);
    fp = fopen("booksdata.txt","w");
    fp2 =fopen("tempdata.txt","r");
    while(!feof(fp2)){
     char c = fgetc(fp2);
     while(c!= EOF){
        fputc(c,fp);
        c=fgetc(fp2);
     }}
     fclose(fp);
     fclose(fp2);
}
 void rewritestudentsdata1(char a[]){
     FILE *fp1,*fp2;
    struct student s;
    int i,k,len=0,j;
    char b[100]= {"StudentID:"};
    char c,e[100]= {"StudentID:"};
    fp1 = fopen("studentsdata.txt","r");
    fp2 = fopen("chidu.txt","w");
    while(!feof(fp1)){
        fscanf(fp1, "%s\n", s.studentname);
        fscanf(fp1, "%s\n", s.studentid);
        fscanf(fp1, "%d", &s.number);
         c = fgetc(fp1);
         if(c==EOF)
         break;
        len++;
    }
    fclose(fp1);
    fp1 = fopen("studentsdata.txt","r");
        for(int y=0;y<len;y++){
        fscanf(fp1, "%s\n", s.studentname);
        fscanf(fp1, "%s\n", s.studentid);
        fscanf(fp1, "%d", &s.number);
        strcat(b,s.studentid);
        i=strcasecmp(a,b);
        if(i==0)
        {
            k = s.number-1;
        fprintf(fp2,"%s\n",s.studentname);
        fprintf(fp2,"%s\n",s.studentid);
        fprintf(fp2,"%d\n",k);
        }
        else{
        fprintf(fp2,"%s\n",s.studentname);
        fprintf(fp2,"%s\n",s.studentid);
        fprintf(fp2,"%d\n",s.number);
        }
         strcpy(b,e);
    }
    fclose(fp1);
    fclose(fp2);
    fp1 = fopen("studentsdata.txt","w");
    fp2 = fopen("chidu.txt","r");
     while(!feof(fp2)){
        c = fgetc(fp2);
     while(c!= EOF){
        fputc(c,fp1);
        c=fgetc(fp2);
     }
     }
     fclose(fp1);
     fclose(fp2);
 }
void  rewritebooksdata1(char a[]){
          FILE *fp,*fp2;
    struct book b;
    int i,j=0;
    int digit=0;
     for(i=7;i<11;i++){
         digit = (digit*10)+(a[i]-'0');
        }
    char c;
    fp = fopen("booksdata.txt","r");
    fp2 = fopen("chidu.txt","w");
    while (!feof(fp))
    {
        fscanf(fp,"%s",b.bookname);
        fscanf(fp,"%d",&b.booknumber);
        fscanf(fp,"%d",&b.quantity);
        c = fgetc(fp);
        if(c==EOF)
        break;
        j++;
    }   fclose(fp);
    fp=fopen("booksdata.txt","r");
    for(int k=0;k<j;k++){
        fscanf(fp,"%s",b.bookname);
        fscanf(fp,"%d",&b.booknumber);
        fscanf(fp,"%d",&b.quantity);
        if(digit==b.booknumber)
        {
            fputs(b.bookname,fp2);
            fprintf(fp2,"\n");
            fprintf(fp2,"%d\n",b.booknumber);
            b.quantity = b.quantity+1;
            fprintf(fp2,"%d\n",b.quantity);
        }
    else{
            fputs(b.bookname,fp2);
            fprintf(fp2,"\n");
            fprintf(fp2,"%d\n",b.booknumber);
            fprintf(fp2,"%d\n",b.quantity);
        }
    }
    fclose(fp);
    fclose(fp2);
    fp = fopen("booksdata.txt","w");
    fp2 =fopen("chidu.txt","r");
    while(!feof(fp2)){
     char c = fgetc(fp2);
     while(c!= EOF){
        fputc(c,fp);
        c=fgetc(fp2);
     }}
     fclose(fp);
     fclose(fp2);
}
void addbook(){
    struct book b;
    printf("Enter book name:");
    scanf("%s",b.bookname);
    printf("enter booknumber:");
    scanf("%d",&b.booknumber);
    printf("Enter number of copies:");
    scanf("%d",&b.quantity);
     FILE *fp;
    fp= fopen("booksdata.txt","a");
    fprintf(fp,"\n");
    fputs(b.bookname,fp);
    fprintf(fp,"\n");
    fprintf(fp,"%d\n",b.booknumber);
    fprintf(fp,"%d\n",b.quantity);
}
void addstudent(){
    struct student s;
    printf("Enter book Student name:");
    scanf("%s",s.studentname);
    printf("Enter studentID:");
    scanf("%s",s.studentid);
    s.number=0;
    FILE *fp;
    fp=fopen("studentsdata.txt","a");
    fprintf(fp,"\n");
    fputs(s.studentname,fp);
    fprintf(fp,"\n");
    fputs(s.studentid,fp);
    fprintf(fp,"\n");
    fprintf(fp,"%d\n",s.number);
}
