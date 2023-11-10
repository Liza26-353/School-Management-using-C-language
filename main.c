#include<stdio.h>

struct student
{
 int rollno;
 char name[30];
 float mark;
}stud;

void search()
{
 FILE *fp2;
 int r, s, avl;
 printf("\n\tEnter the ID no you want to search  :");
 scanf("%d", &r);
 avl = avlrollno(r);
 if (avl == 0)
  printf("\tID No %d is not available in the file\n",r);
 else
 {
  fp2 = fopen("Record", "r");
  while (fread(&stud, sizeof(stud), 1, fp2))
  {
   s = stud.rollno;
   if (s == r)
   {
    printf("\n\tRoll no = %d", stud.rollno);
    printf("\n\tName    = %s", stud.name);
    printf("\n\tCGP     = %.2f\n", stud.mark);
   }
  }
  fclose(fp2);
 }
}


void insert()
{
 FILE *fp;
 fp = fopen("Record", "a");
 printf("\tEnter the ID no   :");
 scanf("%d", &stud.rollno);
 printf("\tEnter the Name      :");
 scanf("%s", &stud.name);
 printf("\tEnter the CGP      :");
 scanf("%f", &stud.mark);
 fwrite(&stud, sizeof(stud), 1, fp);
 fclose(fp);
}


void disp()
{
 FILE *fp1;
 fp1 = fopen("Record", "r");
 printf("\n\tID Number\t Name \t\t CGP\n\n");
 while (fread(&stud, sizeof(stud),1,fp1))
 printf("\t  %d\t\t%s\t\t%.2f\n", stud.rollno, stud.name, stud.mark);
 fclose(fp1);
}




void deletefile()
{
 FILE *fpo;
 FILE *fpt;
 int r, s;
 printf("\tEnter the ID no you want to delete :");
 scanf("%d", &r);
 if (avlrollno(r) == 0)
  printf("\tID no %d is not available in the file\n", r);
 else
 {
  fpo = fopen("Record", "r");
  fpt = fopen("TempFile", "w");
  while (fread(&stud, sizeof(stud), 1, fpo))
  {
   s = stud.rollno;
   if (s != r)
    fwrite(&stud, sizeof(stud), 1, fpt);
  }
  fclose(fpo);
  fclose(fpt);
  fpo = fopen("Record", "w");
  fpt = fopen("TempFile", "r");
  while (fread(&stud, sizeof(stud), 1, fpt))
   fwrite(&stud, sizeof(stud), 1, fpo);
  printf("\n\tRECORD DELETED\n");
  fclose(fpo);
  fclose(fpt);
 }

}


void update()
{
 int avl;
 FILE *fpt;
 FILE *fpo;
 int s, r, ch;
 printf("\tEnter ID number to update:");
 scanf("%d", &r);
 avl = avlrollno(r);
 if (avl == 0)
 {
  printf("\tID number %d is not Available in the file", r);
 }
 else
 {
  fpo = fopen("Record", "r");
  fpt = fopen("TempFile", "w");
  while (fread(&stud, sizeof(stud), 1, fpo))
  {
   s = stud.rollno;
   if (s != r)
    fwrite(&stud, sizeof(stud), 1, fpt);
   else
   {
    printf("\n\t1. Edit Name of ID Number %d", r);
    printf("\n\t2. Edit CGP of ID Number %d", r);
    printf("\n\t3. Edit both Name and CGP of ID Number %d", r);
    printf("\nEnter your choice:");
    scanf("%d", &ch);
    switch (ch)
    {
    case 1:
     printf("\tEnter Name:");
     scanf("%s", &stud.name);
     break;
    case 2:
     printf("\tEnter CGP : ");
     scanf("%f", &stud.mark);
     break;
    case 3:
     printf("\tEnter Name: ");
     scanf("%s", &stud.name);
     printf("\tEnter CGP: ");
     scanf("%f", &stud.mark);
     break;
    default:
     printf("\tInvalid Selection");
     break;
    }
    fwrite(&stud, sizeof(stud), 1, fpt);
   }
  }
  fclose(fpo);
  fclose(fpt);
  fpo = fopen("Record", "w");
  fpt = fopen("TempFile", "r");
  while (fread(&stud, sizeof(stud), 1, fpt))
  {
   fwrite(&stud, sizeof(stud), 1, fpo);
  }
  fclose(fpo);
  fclose(fpt);
  printf("\tRECORD UPDATED");
 }
}



int avlrollno(int rno)
{
 FILE *fp;
 int c = 0;
 fp = fopen("Record", "r");
 while (!feof(fp))
 {
  fread(&stud, sizeof(stud), 1, fp);

  if (rno == stud.rollno)
  {
   fclose(fp);
   return 1;
  }
 }
 fclose(fp);
 return 0;
}

int empty()
{
 int c = 0;
 FILE *fp;
 fp = fopen("Record", "r");
 while (fread(&stud, sizeof(stud), 1, fp))
  c = 1;
 fclose(fp);
 return c;
}




void main()
{
 int c, emp;


  printf("\n    *****Student Management By Liza*****\n");
  printf("\n\t1.Search Student Info  \n\t2.Add Student info \n\t3.Delete Student Info");
  printf("\n\t4.Show Student Details   \n\t5.Edit Info\n");
  printf("\n\t6.CLEAR SCREAN  \n\t7.EXIT  \n");
  printf("    ****************************\n");

  while(1)
  {

  printf("\n\tEnter Category :");
  scanf("%d", &c);
  printf("\n");
  switch (c)
  {
       	case 1:
  				search();
   				break;

		case 2:
               insert();
               break;

        case 3:
   	     		deletefile();
  				break;

        case 4:
  				 emp = empty();
   					if (emp == 0)
    				printf("\n\tThe file is EMPTY\n");
  					 else
   				 disp();
   					break;

  		 case 5:
                update();
                break;

        case 6:
               system("cls");
               main();
               break;

        case 7:
               exit(1);
               break;

 		 default:
   				printf("\n\tYour choice is wrong\nPlease try again...\n");
   				break;

  }
 }
}
