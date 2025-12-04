#include <stdio.h>
void add(float a,float b){
    printf("sum = %f",a+b);
}
void sub(float a,float b){
    printf("sub = %f",a-b);
}
void mul(float a,float b){
    printf("mul = %f",a*b);
}
void div(float a,float b){
    if(b == 0){
        printf("can't divide by zero!!");
    }
    else{
        printf("div = %f",a+b);
    }
    
}

void main(){
    printf("!!WELCOME!! \n");
    float a,b;
    printf("enter 2 numbers \n");
    scanf("%f %f",&a,&b);
    int choice;
    printf("1. addtion \n 2. subtraction \n 3. multiplication \n 4. division \n 5. exit");
    scanf("%d",&choice);
    while(choice != 5){
    switch(choice){
        case 1:
            add(a,b);
            break;
        case 2:
            sub(a,b);
            break;
        case 3:
            mul(a,b);
            break;
        case 4:
            div(a,b);
            break;
        default:
            printf("enter a number between 1 to 4\n");
    }
    printf("\n");
    printf("1. addtion \n 2. subtraction \n 3. multiplication \n 4. division \n 5. exit\n");
    scanf("%d\n",&choice);
}
printf("THANK YOU");

}