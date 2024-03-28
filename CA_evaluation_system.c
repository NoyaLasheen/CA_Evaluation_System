#include <stdio.h>
#include <stdlib.h>

struct Student
{
    int reg_no;
    char section[5];
    char name[50];
    float math_marks;
    float phy_marks;
    float eng_marks;
    float c_marks;
    float mech_marks;
    float total;
    float cgpa;
    char  grade;
}student;

char choice2;

FILE *fp;

int reg_no;

int search_student(int reg_no)
{
    rewind(fp);
   
    while (fread(&student, sizeof(student), 1, fp))
    {
        if (student.reg_no == reg_no)
        {
            return 1;
        }
    }

}

void add_student()
{
    int found = 0;
    printf("Enter registration number: ");
    scanf("%d", &reg_no);

    found = search_student(reg_no);

    if (found == 1)
    {
        printf("\nStudent already exists!\n");
    }
    else
    {
        student.reg_no = reg_no;

        printf("Enter section: ");
        scanf("%s", student.section);

        printf("Enter name: ");
        scanf("%s", student.name);

        printf("Enter maths marks(out of 100): ");
        scanf("%f", &student.math_marks);

        printf("Enter physics marks(out of 100): ");
        scanf("%f", &student.phy_marks);

        printf("Enter english marks(out of 100): ");
        scanf("%f", &student.eng_marks);

        printf("Enter C programming marks(out of 100): ");
        scanf("%f", &student.c_marks);

        printf("Enter Mechanical marks(out of 100): ");
        scanf("%f", &student.mech_marks);
        student.total = student.math_marks + student.phy_marks + student.eng_marks + student.c_marks + student.mech_marks;
        student.cgpa = student.total / 100 * 2;

        if(student.cgpa >= 9)
            student.grade = 'O';
        else if(student.cgpa <9 && student.cgpa >= 8)
            student.grade = 'A';
        else if(student.cgpa <8 && student.cgpa >= 7)
            student.grade = 'B';
        else if(student.cgpa <7 && student.cgpa >= 6)
            student.grade = 'C';
        else if(student.cgpa <6 && student.cgpa >= 4)
            student.grade = 'D';
        else 
            student.grade = 'E';

        fwrite(&student, sizeof(student), 1, fp);
    }
}

void modify_data()
{
    FILE *temp_fp;
    int found = 0;

    printf("Enter registration number: ");
    scanf("%d", &reg_no);

    found = search_student(reg_no);

    if (found == 0)
    {
        printf("\nStudent not found!\n");
    }
    else
    {        
        temp_fp = fopen("temp.dat", "wb");
        if (temp_fp == NULL)
        {
            printf("Error opening file\n");
            return;
        }
        else
        {
            rewind(fp);
            while (fread(&student, sizeof(student), 1, fp))
            {
                if (student.reg_no != reg_no)
                {
                    fwrite(&student, sizeof(student), 1, temp_fp);
                }
                else
                {
                    student.reg_no = reg_no;
            
                    printf("Enter section: ");
                    scanf("%s", student.section);

                    printf("Enter name: ");
                    scanf("%s", student.name);

                    printf("Enter maths marks(out of 100): ");
                    scanf("%f", &student.math_marks);

                    printf("Enter physics marks(out of 100): ");
                    scanf("%f", &student.phy_marks);

                    printf("Enter english marks(out of 100): ");
                    scanf("%f", &student.eng_marks);

                    printf("Enter C programming marks(out of 100): ");
                    scanf("%f", &student.c_marks);
            
                    printf("Enter Mechanical marks(out of 100): ");
                    scanf("%f", &student.mech_marks);

                    student.total = student.math_marks + student.phy_marks + student.eng_marks + student.c_marks + student.mech_marks;
                    student.cgpa = student.total / 100 * 2;
                    if(student.cgpa >= 9)
                        student.grade = 'O';
                    else if(student.cgpa <9 && student.cgpa >= 8)
                        student.grade = 'A';
                    else if(student.cgpa <8 && student.cgpa >= 7)
                        student.grade = 'B';
                    else if(student.cgpa <7 && student.cgpa >= 6)
                        student.grade = 'C';
                    else if(student.cgpa <6 && student.cgpa >= 4)
                        student.grade = 'D';
                    else 
                        student.grade = 'E';

                    fwrite(&student, sizeof(student), 1, temp_fp);
                }
            }
        }
        fclose(temp_fp);
        fclose(fp);
        remove("student.dat");
        rename("temp.dat", "student.dat");
        printf("\nStudent data modified successfully\n");
        fp = fopen("student.dat", "rb+");
    }
}


void display_all()
{
    rewind(fp);

    printf("\nReg.No.\tSection\tName\tMaths\tPhysics\tEnglish\tC Programming\tMechanical\ttotal\tCGPA\tGrade\n");
    printf("=====================================================================================================\n");

    while (fread(&student, sizeof(student), 1, fp))
    {
        printf("%d\t%s\t%s\t%.2f\t%.2f\t%.2f\t", student.reg_no, student.section, student.name, student.math_marks, student.phy_marks, student.eng_marks);
        printf("%.2f\t\t%.2f\t\t%.2f\t%.2f\t%c\n",student.c_marks,student.mech_marks,student.total, student.cgpa,student.grade);
    }
    printf("-----------------------------------------------------------------------------------------------------\n");
}

void display_student()
{
    int reg_no;
    int found = 0;
    printf("Enter registration number: ");
    scanf("%d", &reg_no);

    found = search_student(reg_no);

    if (found == 1)
    {   
        printf("\n");
        printf("Reg. No.:               %d\n", student.reg_no);
        printf("Section:                %s\n", student.section);
        printf("Name:                   %s\n", student.name);
        printf("Maths Marks:            %.2f\n", student.math_marks);
        printf("Physics Marks:          %.2f\n", student.phy_marks);
        printf("English Marks:          %.2f\n", student.eng_marks);
        printf("C Programming Marks:    %.2f\n", student.c_marks);
        printf("Mechanical Marks:       %.2f\n", student.mech_marks);
        printf("Total Marks:            %.2f\n", student.total);
        printf("CGPA:                   %.2f\n", student.cgpa);
        printf("Grade:                  %c\n", student.grade);
    }
    else

    {
        printf("\nStudent not found\n");
        printf("If you would like to add the student record enter Y ");
        fflush(stdin);
        scanf("%c", &choice2);
        if (choice2 == 'Y')
            add_student();
    }
}

void delete_student()
{
    FILE *temp_fp;

    int found = 0;
    int reg_no;

    printf("Enter registration number: ");
    scanf("%d", &reg_no);

    found = search_student(reg_no);

    if (found == 1)
    {
        temp_fp = fopen("temp.dat", "wb");
        if (temp_fp == NULL)
        {
            printf("Error opening file\n");
            return;
        }

        while (fread(&student, sizeof(student), 1, fp))
        {
            if (student.reg_no != reg_no)
            {
                fwrite(&student, sizeof(student), 1, temp_fp);
            }
        }

        fclose(temp_fp);
        fclose(fp);
        remove("student.dat");
        rename("temp.dat", "student.dat");
        printf("\nStudent deleted successfully\n");
        fp = fopen("student.dat","rb+");
    }
    else
    {
        printf("\nStudent not found\n");
        remove("temp.dat");
    }

}

int main()
{
    int choice, reg_no;
    fp = fopen("student.dat", "rb+");
    // showing error if file is
    // unable to open.
    if (fp == NULL)
    {
        fp = fopen("student.dat", "wb+");
        if (fp == NULL)
        {
            printf("\nCannot open file...");
            exit(1);
        }
    }
    while (1)
    {
        printf("\nCA Evaluation System\n");
        printf("====================\n");
        printf("1. Add student\n");
        printf("2. Modify student data\n");
        printf("3. Display all students\n");
        printf("4. Display a student\n");
        printf("5. Delete a student\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            add_student();
            break;
        case 2:
            modify_data();
            break;
        case 3:
            display_all();
            break;
        case 4:
            display_student();
            break;
        case 5:
            delete_student();
            break;
        case 6:
            fclose(fp);
            return 0;
        }
    }
}