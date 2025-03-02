#include <math.h>
#include <stdio.h>
#include <string.h>

double cube(double number);

void sayhito(char name[], int age) { // does not return anything

    printf("Hi %s! Are you %d years old?\n",name,age);
}

int maxim(int a, int b, int c) {

    if (a >= b && a >= c) {
        return a;
    }else if (!(b <= a || b <= c)) {
        return b;
    }else{
        return c;
    }
}

void feedback(int grade){

    switch (grade) {
        case 'A':
            printf("You did great on the test!");
            break;
        case 'B':
            printf("You did good on the test!");
            break;
        case 'C':
            printf("You did ok on the test!");
            break;
        case 'D':
            printf("You did poorly on the test!");
            break;
        case 'F':
            printf("You failed the test!");
            break;
        default:
            printf("You entered an invalid grade!");
    }
}

struct Student {
    char name[20];
    char major[20];
    int age;
    double grade;
};

int main() {

    /* printf() function */
    //***************************************************************************************************************************
    // printf("Hello World\n");
    // printf("%d\n",10);
    // printf("%f\n",9.99);
    // printf("%c\n",'A');
    // printf("%f\n",9+0.99);
    // printf("%f\n", 5/4); does not work !!
    // printf("%d\n", 5/4);
    // printf("%f\n",9/4.0);

    /* char name[] = "John";
    int age = 18;
    printf("Hello, %s! Are you %d years old?\n",name,age);
    printf("%p\n", &age); // print the address  where it is stored 'age' in hexadecimal */

    /* scanf() function */
    //***************************************************************************************************************************
    // int n;
    // scanf("%d",&n); // n <- an int value from the user

    // double m;
    // scanf("%lf",&m); // m <- a double value from the user

    // char p[100];
    // scanf("%s",p); // user input : Angela Walker; string in p <- Angela [ reads until space ]

    // char q;
    // scanf(" %c",&q); // the space is important, otherwise is not going to work

    /* char first_name[20];
    char last_name[20];
    printf("Enter your name: ");
    scanf("%s%s", first_name,last_name);
    printf("Your name is %s %s", first_name, last_name); */


    /* fgets() function */
    //***************************************************************************************************************************
    //char s[100];
    //fgets(s, 100, stdin); // stdin : from keyboard; 100 : how many characters we let the user input; s : where to store the string
                         // user input : Angela Walker; string in p <- Angela Walker\n [ adds a new line character ]


    /* Data types */
    //***************************************************************************************************************************
    // int a = 10;
    // const int A = 10; // or 'int const' : cannot be changed
    // int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9}; // array[0] <- 1
    // int array2d[][] = { {1,2} , {3,4} , {5,6} , {7,8} , {9,0} }; // array2d[0][1]=2
    // int *p = &a ; declaration of a pointer for a
    // double b = 9.99;
    // double *p = &b ; declaration of a pointer for b
    // printf("%f\n", *p) // * difference operator : grabs the value stored at the address of p
    // char c = 'A';
    // char d[] = "10";

    /* Mathematics function */
    //***************************************************************************************************************************
    // const int number1 = 8;
    // const int number2 = 2;
    // double number3 = 9.4;
    // double result = 0;
    // result = pow(number1,number2); // the pow(nr1,nr2) [number1^number2] function returns a decimal number
    // result = sqrt(number1);  // the sqrt(nr) function return a decimal number
    // result = pow(number1,1.0/3.0); // the 3-th root of a number
    // result = ceil (number3); // result <- 10.0
    // result = floor (number3); // result <- 9.0

    /* Functions */
    //***************************************************************************************************************************
    // sayhito("Kally",19);
    // printf("The cub value for 3 is %f\n", cube(3));
    // feedback('C');

    /* Struct */
    //***************************************************************************************************************************
    /*struct Student student; // the initialisation
    student.grade = 5.5;
    student.age = 18;
    strcpy(student.name,"John Price");
    strcpy(student.major,"Computer Sience");
    printf("The strudent %s from %s department has the %f grade.",student.name,student.major,student.grade); */

    /* Loops */
    //***************************************************************************************************************************
    /*int index = 0;
    while (index <= 9) {
        printf("%d ", index);
        index+=2;
    }

    index=0;
    do {
        printf("%d ", index);
        index+=2;
    }while (index<=9);

    int i;
    for (i=1; i<=9; i+=2) {
        printf("%d ", i);
    }

    int v[]={1,2,3,4,5,6,7,8,9,10};
    for (i=0; i<=9; i++) {

        if (v[i]%2==0) {
            printf("%d ", v[i]);
        }
    } */

    /* Files */
    //***************************************************************************************************************************

    /* FILE *fp;
    fp = fopen("student.txt", "w");
    fprintf(fp, "Denis Histon\n");
    fclose(fp); */

    /* char line[255];
    FILE *fp = fopen("student.txt", "r");
    fgets(line, 255, fp);
    printf("%s", line);
    fgets(line, 255, fp);
    printf("%s", line); */


    return 0;
}

double cube(double number) {

    return number * number * number;
}
