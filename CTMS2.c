/*
                Call Taxi Management System
___________________________________________________________________________________________________________________________________________
    This code code is for Logging in three types of users, namely; Administrator,Mediator,Customer, and Driver,
    into a database(TEXT FORMAT). This code is originally made modular, such that the administrator, the mediator, the driver , and
    the customer operate as individual programs and update the database through cloud storage which can be implemented in due course.
    For ease of operation and understanding all the modules are made accessible within the same program.

    Description:
        1. Administrator: the user who manages all the databases
        2. Mediator: the user who receives 'call' from the customer and registers them
        3. Driver: drops off the customer at their specified drop-off point
    Requirements:
        Computer systems to run the program(for administrator and mediator)
        Driver screen with an input method(preferably touch user interface)
        Customer screen embedded behind the driver's seat(similar to Driver screen)
Authors: Rohith S, Vignesh Balaji, Surya Prakash
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

float waitCharge=12,costPERkm=20,regDisc;int feedback; //Variables for calculating Bill
char DriverID[5]="1001",rideCount[3]="0",cabstat[10]="Standby",cabID[5]="1001",cabType[3]="Micro",Tfare[50],Insur[5]="365";
char Dname[20],pwd[6];
int pos=1;
char u[5],p[7];
char d[20];     //user ID,password,User name,attendance,ride Count,OTP,Cab ID,Cab type, Total fare,Insurance detail

char o[5];       //variables for verifying OTP
int choice,cotp;         //Variable to select operation from user
int c=1;            //Variable for completing a ride
int cc=0;           //Variable to store confirmation from user

/*  Variables to store after ride details  */
float TotalDistance;
float TotalFare;
int waitHH,waitMM,waitSS;
/* Function prototypes for administrator operations */
void logina();
void ahomepage();
void addDriver();
void addMed();
void viewDriver();
void viewMed();
/*Function prototyping for driver screen*/
int SecurityMatch(char user[30], char pass[30]);
void dhomepage();
void cabStatus();
void otpverify();
void logout();

/*Function prototyping for customer screen*/
void cPanic();
void cFeedback();
void afterRide();


void dhomepage(){       //displays all the available operations and receives input from user to perform one of the operations
    FILE *f=fopen("driver.txt","r+");
    choice=0;
    while(pos){
        printf("HOMEPAGE\n1. Update cab status\n2. Verify customer OTP\n3. Log out\nEnter the operation to be performed:\n");
        scanf("%d",&choice);
        if(choice==1){
            cabStatus();
            break;
        }
        else if(choice==2){
            otpverify();
            break;
        }
        else if(choice==3){
            logout();
            break;
        }
        else{
            printf("Invalid input. try again");
        }
    }
    fclose(f);
}
int SecurityMatch(char user[30], char pass[30]){  //accesses the database and compares the entered user ID and Password
    char filename[10],t;
    FILE *ptr;
    int a,b=1,f=0;
    char id[50],name[30];
    char arr[100];
    ptr=fopen("driver.txt","r");
    while(!feof(ptr))
    {
        fscanf(ptr," %s",&id);strcpy(DriverID,id);
        fscanf(ptr," %s",&name);strcpy(Dname,name);
        fscanf(ptr," %s",&pwd);
        fscanf(ptr,"%d",&a);
        if( (strcmp(user,id)==0) && (strcmp(pass,pwd)==0) ){
            f=1;
        }

    }
    if(f)
                {printf("\nUser and password correct!!!\n");dhomepage();}
    else
               {printf("\nUser or password incorrect!\n\n");}
    fclose(ptr);
}
void logind(){          //Driver login page: Prompted for user ID and password
    while(pos){
        printf("Welcome driver\n");
        printf("Enter user id:");
        scanf("%s",u);
        printf("Enter password:");
        scanf("%s",p);
        SecurityMatch(u,p);

    }
    dhomepage();
    }
void cabStatus(){       //Updates the status of the cab to the database:{Standby/Running/Absent}
    int choice;
    while(1){
        printf("Enter the status of your cab\n");
        printf("1. Standby\n2. Running\n3. Absent\n4. Homepage\n");
        scanf("%d",&choice);
        if(choice==1){
            strcpy(cabstat,"Standby");
            printf("Successfully updated!\n");choice=4;
        }
        if(choice==2){
            strcpy(cabstat,"Running");
            printf("Successfully updated!\n");choice=4;
        }
        if(choice==3){
            strcpy(cabstat,"Absent");
            printf("Successfully updated!\n");choice=4;
        }
        if(choice==4){
            printf("Returning to homepage....\n");
            dhomepage();
            break;
        }
        else{
            printf("Invalid option\n");
        }
    }
}
void otpverify(){       //Verifies the One-time password(OTP) with the driver OTP assigned by the Mediator
    printf("Enter customer OTP(or -1 to go to homepage):\n");
    while(1){
            int otp=atoi(o);
        scanf("%d",&cotp);
        if(cotp==otp){
            printf("OTP verified successfully!!\nRide started\n(Enter 0 to complete ride\n)");
            scanf("%d",&c);
            if(c){
                afterRide();
                break;
            }
            else{printf("Enter -1 to complete ride\n");}
        }
        else if(cotp==-1){
            printf("Returning to homepage....\n");
            dhomepage();
            break;
        }
        else{
            printf("OTP verification failed\n");
        }
    }
}
void logout(){          //routine used to log out from the program and terminate the program
    cc=0;
    printf("Are you sure you wish to log out?(1/0)\n");
    scanf("%d",&cc);
    if(cc){
        printf("Logging out....\n");
        pos=0;
    }
    else{
        printf("Returning to homepage....\n");dhomepage();
    }
}
void cFeedback(){       //receives the customers feedback in the form of integer values

    printf("Between 1 to 5, how would you describe your ride??\n");
    scanf("%d",&feedback);
}
void cFare(int t,float d ){ //for calculating the total fare
    TotalFare=TotalDistance*costPERkm + t*waitCharge;   //Total fare exclusive of discount
    TotalFare*=regDisc/100;                             //Regular customer discount
}
void afterRide(){       //function that is called at the end of the ride
    printf("Enter the total wait time:(h,m,s)\n");
    scanf("%d",&waitHH);                            //Entering wait time
    scanf("%d",&waitMM);
    scanf("%d",&waitSS);
    printf("Enter the total distance travelled:\n");//Enter total distance covered
    scanf("%f",&TotalDistance);
    cFare((waitHH*60+waitMM+waitSS/60),TotalDistance);
    printf("Total fare to be collected:%f",TotalFare);//Generating total bill

}
void cPanic(){          //A routine that receives input from the customer to alert the mediator in case of any emergencies
    int ccc=0,x=atoi(DriverID);
    printf("Enter 1 to send alert to mediator:\n");
    scanf("%d",&ccc);
    if(ccc==1){
    FILE *q;
    int flag=0;
    q=fopen("alert.txt","a");
    char word[10];
    sprintf(word,"alert %d\n",x);
    fprintf(q,word);
    fclose(q);
    }
}


void addMed(){          //routine that is used to add mediator entry in the database, after recruitment
    char filename[10],t;
    FILE *ptr;
    int a,b=1;
    char id[50],name[30],pwd[20];
    char arr[100];
    ptr=fopen("mediator.txt","a");
    //fprintf(ptr,"100 surya prakash 1\n101 rohith rohith 1\n102 vignesh balaji 0\n");
    printf("Enter 1 to add mediator:");
    scanf("%d",&b);
    printf("ID NAME PASSWORD ATT:\n");
    if(b==1)
    {
        scanf("%s %s %s %d",id, name, pwd, &a);
        fprintf(ptr,"%s %s %s %d",id, name, pwd, a);
    }
    fclose(ptr);
    ptr=fopen("mediator.txt","r");
    printf("\nMediators present\n");
    while(!feof(ptr))
    {
        fscanf(ptr," %s",&id);
        fscanf(ptr," %s",&name);
        fscanf(ptr," %s",&pwd);
        fscanf(ptr,"%d",&a);
         if(a==1)
         {
           printf("\n%s %s %s",id,name,pwd);
         }
    }
    fclose(ptr);
    return 0;
    }
void viewMed(){         //routine to view all the mediator entries in the database
    char filename[10],t;
    FILE *ptr;
    int a,b=1;
    char id[50],name[30],pwd[20];
    char arr[100];
    ptr=fopen("mediator.txt","r");
    printf("\nMediators:\n");
     printf("ID NAME PASSWORD :\n");
    while(!feof(ptr))
    {
        fscanf(ptr," %s",&id);
        fscanf(ptr," %s",&name);
        fscanf(ptr," %s",&pwd);
        fscanf(ptr,"%d",&a);
         {
           printf("\n%s | %s  |%s",id,name,pwd);
         }
    }
    fclose(ptr);
    }
void addDriver(){       //Routine used to add driver entry in the database, after recruitment
    char filename[10],t;
    FILE *ptr;
    int a,b=1;
    char id[50],name[30],pwd[20];
    char arr[100];
    ptr=fopen("driver.txt","a");
    //fprintf(ptr,"200 saran sabari 1\n201 karthi keyan 1\n202 sabarish selva 0\n");//sample initializers for new file
    printf("Enter 1 to add driver:");
    scanf("%d",&b);
    printf("ID NAME PASSWORD ATT:\n");
    if(b==1)
    {
        scanf("%s %s %s %d",id, name, pwd, &a);
        fprintf(ptr,"%s %s %s",id, name, pwd);
    }
    fclose(ptr);
    ptr=fopen("driver.txt","r");
    printf("\ndriver present\n");
    while(!feof(ptr))
    {
        fscanf(ptr," %s",&id);
        fscanf(ptr," %s",&name);
        fscanf(ptr," %s",&pwd);
        fscanf(ptr,"%d",&a);
         if(a==1)
         {
           printf("\n%s %s %s",id,name,pwd);
         }
    }
    fclose(ptr);

    }
void viewDriver(){      //routine to view all the driver entries in the database
    char filename[10],t;
    FILE *ptr;
    int a,b=1;
    char id[50],name[30],pwd[20];
    char arr[100];
    ptr=fopen("driver.txt","r");
    printf("\ndriver present\n");
    while(!feof(ptr))
    {
        fscanf(ptr," %s",&id);
        fscanf(ptr," %s",&name);
        fscanf(ptr," %s",&pwd);
        fscanf(ptr,"%d",&a);
           printf("\n%s | %s | %s | %d",id,name,pwd,a);
    }
    fclose(ptr);

    }
void logina(){          //Login page for Administrator login

    char a[15],b[15];
    int i,c,d;
    char userid[15]="adminvb";
    char password[15]="electricforce";
    printf("Welcome admin!!");
    while(1)
    {
     printf("\nEnter the user ID:\n");
     scanf("%s",a);
     c=strcmp(a,userid);
     printf("Enter the password:\n");
      scanf("%s",b);
      d=strcmp(b,password);
      if(!c&&!d)
      {
       printf("Login is successful :)\n");
       ahomepage();
       break;
       }
       else
        printf("UserID or password is incorrect :/\n");
      }
}
void ahomepage(){       //Homepage for administrator
    int choice;       //displays all the available operations and receives input from user to perform one of the operations
    choice=0;
    while(1){
        printf("HOMEPAGE\n1. Add mediator\n2. Add driver\n3. View mediators\n4. View drivers\n5. Log out\nEnter the operation to be performed:\n");
        scanf("%d",&choice);
        if(choice==1){
            addMed();
            break;
        }
        else if(choice==2){
            addDriver();
            break;
        }
        else if(choice==3){
            viewMed();
            break;
        }
        else if(choice==4){
            viewDriver();
            break;
        }
        else if(choice==5){
            logout();
            break;
        }
        else{
            printf("Invalid input. try again");
        }
    }
}

void loginm(){          //Routine for Mediator login and other operations


    int x,y=1;
    while(x!=1)
    {
        int n;
        printf("Enter 1 to attend the call\n");     //receiving call from customer
        scanf("%d",&n);
        if(n==1)
        {
            int a,no;
            char cus_name[30],cus_location[20],cus_ph[15],drop_location[20],mode[10];
            printf("Enter customer name\n");
            scanf(" %s",cus_name);
            printf("Enter customer location\n");
            scanf("%s",cus_location);
            printf("Enter customer phone number\n");
            scanf("%s",cus_ph);
            printf("Enter mode of travel\n");                       //mode of travel:1 way/ 2 way/ tourism
            printf("Enter 1 for one way drop\nEnter 2 for two way drop\nEnter 3 for tourism\n");
            scanf("%d",&a);
            printf("Enter number of passengers\n");
            scanf("%d",&no);
            printf("Enter the drop location\n");
            scanf("%s",drop_location);
            FILE *fp;
            fp=fopen("customer_database","a");
            fprintf(fp,"\n%d.customer name:%s",y,cus_name);
            fprintf(fp,"\n  customer location:%s",cus_location);
            fprintf(fp,"\n  customer phone number:%s",cus_ph);
            fprintf(fp,"\n  number of passengers:%d",no);
            if(a==1)
            fprintf(fp,"\n  customer mode of travel:One way");
            else if(a==3)
            fprintf(fp,"\n  customer mode of travel:Two way");
            else
            fprintf(fp,"\n  customer mode of travel:Tourism");
            fprintf(fp,"\n  drop location:%s",drop_location);
            /*OTP generation*/
            int length=4;
                int num=1;
                int temp;
                srand((unsigned int) time(0));
            while(num--)
            {
                    temp = length;
                    printf("\n");
                    while(temp--)
                        {
                        o[temp]=rand() % 56 + 65;   //creating a string containing random numbers

                        srand(rand());
                        }
                        temp = length;
            }
            printf("OTP is:%s\n",o);
            fprintf(fp,"\n  OTP:%s",o);
            fclose(fp);
            printf("\nMail/SMS sent:\"Please wait for some time until the cab driver contacts you\" to the customer\n");
            printf("Enter 1 to exit or press any key to continue\n");
            scanf("%d",&x);
        }
        y++;
        printf("%d\n",y);
    }
    /* Checking for panic alerts from customer */
    FILE *q;
    int flag=0;
    q=fopen("alert.txt","r");
    char word[]="alert",w2[1000];
    while(fscanf(q,"%s",w2)!=EOF){
        if(strcmp(word,w2)==0)
            flag=1;
    }
    fclose(q);
    if(flag==1){
        printf("warning");
        FILE *d;
        char drive[1000];
        d=fopen("driver.txt","r");
        while(fscanf(d,"%s",drive)!=EOF)
            printf("\n%s",drive);
    }
    return 0;
}
main(){
    int option;
    /*User type prompt*/
    printf("Enter the type of user:\n1. Admin\n2. Customer\n3. Mediator\n4. Driver\n");
    scanf("%d",&option);
    if(option == 1){
        logina();       //Administrator login routine call
    }
    else if(option ==2){
        int ch=0;       //Customer screen simulation
        cPanic();
        while(1){
            if(ch==0){
                printf("Enter any natural number to simulate end ride\n");
                scanf("%d",&ch);
            }
            else{cFeedback();printf("Thank you for your valuable feedback!!\n");break;}

        }
    }
    else if (option == 3){
        loginm();       //Mediator login routine call
    }
    else if(option == 4){
        logind();       //Driver login routine call
    }
    else{
        printf("Invalid option :/\n\n");    //Error message
    }
}
