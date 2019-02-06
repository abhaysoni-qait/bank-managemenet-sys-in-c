#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

// this structure represts a date
struct date{
    int month;
    int day;
    int year;
    };

// this structure represents time in hour and minute
struct time{
    int hour;
    int minute;
};
    
// this structure represents a transaction record
struct transactionRecord {
    int account_number;  //account number of account on which this tranaction would b performed
    struct date d;         //date of transaction 
    struct time t;
    char type[15];       //deposited or withdrawn
    float amount;        //amount involved in this process
    float old_amt;       //account balance before this transaction was performed
    float new_amt;       //account balance after this transaction
};

//this structure is for storing user and his account related information
struct userRecord{
    char name[60];         //account holder name
    char username[30];  //account username Unique for ever account (used for login)
    char pass[30];      //account password (used for login)
    long long int acc_no;  //randomly generated account number
    struct date dob;         //date of birth of account holder
    char address[60];   //primary address of account holder
    char email[40];     //account holder contact info
    double phone;       //account holder contact info
    char acc_type[10];  //saving, credit or fixed
    float balance;      //current baalnce of account
    struct date opening_date; //account was opened on following date
    long long int aadhar_number; // account holder aadhar number
    int isLoggedIn;   //for checking if user is logged in or log out 0->logout 1->login 
    };



// this function is specifically for using color in console of linux

void menu();
void new_acc();
struct userRecord getUserViaUsernameAndPassword(char*, char*);
void view_user_profile(struct userRecord);
void userScreen(struct userRecord);
struct userRecord updateBalanceInDatabase(float, struct userRecord);
void deposit(struct userRecord);
void withdrawal(struct userRecord);
void enterTransactionInBankRecords(float, struct userRecord);
void print_passbook(struct userRecord);
struct transactionRecord createTransactionRecord(float, struct userRecord);

// this function is specifically for using color in console of linux
void red () {
  printf("\033[1;31m");
}

// this function is specifically for using color in console of linux
void yellow() {
  printf("\033[1;33m");
}


void reset () {
  printf("\033[0m");
}

//for creating delay
void fordelay(int j) {
    int i,k;
    for(i=0;i<j;i++){
    	k=i;
	}
         
}

//loading Screen for effect
void loading_screen(){
	int i = 0;
	printf("\n\n\nLOADING");
        for(i=0;i<=6;i++)
        {
            fordelay(100000000);
            printf(".");
        }
        system("clear");
}

//find total digits in any number passed as argument
int findTotalDigits(long long int num){
   if(num == 0){
    return 0;
  }
  return 1 + findTotalDigits(num/10);
}


//returns 1 when date is valid according to the policy given 
//else return false
int validateDate(struct date d){
    int valid = 0;
    if(d.month>0 && d.month<=12){
        if(d.day>0 && d.day<=31){
            if(d.year>1950 && findTotalDigits(d.year)==4){
                valid = 1;
                return valid;
            }
        }
    }
    return valid;
}

//this function generates random 10 digit Number
long long int getRandomTenDigitNumber(){
    long long int r;
    srand((unsigned)time(NULL)); //for increasing randomness
    r=1000000000+rand()%999999999;
    return r;
}

//this function generates random 11 digit Number
long long int getRandomElevenDigitNumber(){
    long long int r;
    srand((unsigned)time(NULL)); //for increasing randomness
    r=10000000000+rand()%9999999999;
    return r;
}

//this function generates random 12 digit Number
long long int getRandomTwelveDigitNumber(){
    long long int r;
    srand((unsigned)time(NULL)); //for increasing randomness
    r=100000000000+rand()%99999999999;
    return r;
}

//Closing Screen when the application will be shuting Down
void close(void) {
    // system("cls");
    system("clear");
    red();
    printf("Created By Abhay Soni");
    fordelay(100000000);
    // system("cls");
    system("clear");
    yellow();
    printf("*Created By Abhay Soni*");
    fordelay(100000000);
    // system("cls");
    system("clear");
    red();
    printf("**Created By By Abhay Soni**");
    fordelay(100000000);
    // system("cls");
    system("clear");
    yellow();
    printf("***Created By By Abhay Soni***");
    fordelay(100000000);
    // system("cls");
    system("clear");
    red();
    printf("##***Created By By Abhay Soni***##");
    fordelay(300000000);
}

// validate Username based on the policy;
// username should not contain any special character, numeric or alpha character;
// username should be atleast 5 character long;
//username should be not longer than 20 in length
// returns 1 when username is valid and 0 when not
int validateUsername(char* username){
    int status = 1;
    int i;

    if(strlen(username)<5 || strlen(username)>20 ){
        status = 0;
        return status;
    }

    for(i=0; username[i]!='\0'; i++){
		if( username[i]>=97 && username[i]<=122 ){

		}else{
			status = 0;
			return status;
		}
    }
    return status;
}

// validate name based on the policy;
// name should not contain any special character, numeric or alpha character;
// name should be atleast 3 character long;
// name should be not longer than 40 in length
// returns 1 when name is valid and 0 when not
int validateName(char* name){
    int status = 1;
    int i;

    if(strlen(name)<3 || strlen(name)>40 ){
        status = 0;
        return status;
    }

    for(i=0; name[i]!='\0'; i++){
		if( (name[i]>=97 && name[i]<=122) || (name[i]>=97 && name[i]<=122) ){

		}else{
			status = 0;
			return status;
		}
    }
    return status;
}

//this function checks if an email is validate
int validateEmail(char* email){
    int status=1;
    //logic to validate email address
    return status;
}

//this function is for validating aadhar Number
int validateAadhar(long long int aadhar){
    int status = 0;
    // printf("status of aadhar : %d", findTotalDigits(aadhar));
    if(findTotalDigits(aadhar)==12){
        status = 1;
        return status;
    }
    return status;
}


//this function validates password (Implementation depends upon policy provided)
//password should contain 1 alpha, 1 lower, 1 numeric and 1 special character and should have atleast 8 characters
int validatePassword (char *password){
  int status = 1;
  int digitflag = 0;
  int upperflag = 0;
  int lowerflag = 0;
  int specialflag =0;
  int i;
  if (strlen (password) < 8) {
      printf ("Length is less than 8");
      return status;
    } else {
      for (i = 0; i < strlen (password); i++) {
	  	if (isdigit (password[i]))
	    	digitflag++;
	  	if (isupper (password[i]))
	    	upperflag++;
	  	if (islower (password[i]))
	    	lowerflag++;
	  	if(password[i]>=33 && password[i]<=47)
	    	specialflag++;
	    	}
    }
    
    if (digitflag == 0)
	printf ("\nNo digits");
      if (upperflag == 0)
	printf ("\nNo Upper Case Letters");
      if (lowerflag == 0)
	printf ("\nNo Lower Case Letters");
	  if (specialflag == 0)
	printf("\n No special characters");
	
	if(digitflag>0 && upperflag>0 && lowerflag>0 && specialflag>0) {
	    status = 1;
	    return status;
	}
	return status;
}

// this method returns todays date 
struct date getCurrentDate(){
    struct date d;
    time_t now;
    time(&now);
    struct tm *local = localtime(&now);
    d.day = local->tm_mday;  
    d.month = local->tm_mon + 1;   	
    d.year = local->tm_year + 1900;
    return d;
}


// this method returns current Time
struct time getCurrentTime(){
    struct time t;
    time_t now;
    time(&now);
    struct tm *local = localtime(&now);
    t.hour = local->tm_hour;      	// get hours since midnight (0-23)
    t.minute= local->tm_min;  
    return t;
}

//get username from user
void inputName(char* name){
    // char name[30];
    enter_name_input:
    red();
    printf("\n##name can not contain any special character or numeric values and should contain atleast 2 character and less than 40)");
    printf("\nEnter the name:  ");
    yellow();
    scanf("%s", name);
    if(validateName( name)==0){
        red();
        printf("\nPlease enter a valid name:  ");
        goto enter_name_input;
    }
    // return name;
}

//get username from user
void inputUsername(char* uname){
    // char uname[30];
    red();
    printf("##username should not contain any special, numeric or alpha character and should be atleast 5 character in length and less than 20");
    enter_username_inputUsername:
    printf("\nEnter your Username :  ");
    yellow();
    scanf("%s", uname);
    if(validateUsername(uname)==0){
        red();
        printf("##Invalid Username : username should not contain any special, numeric or alpha character and should be atleast 5 character in length and less than 20 ! Try Again\n\n");
        goto enter_username_inputUsername;
    }
    // return uname;
}

//input aadhar number from user
long long int inputAadhar(){
    long long int aadhar_number;
    // enter_aadhar_number:
    red();
    printf("\nEnter Your Aadhar Number :  ");
    yellow();
    scanf("%lli", &aadhar_number);
    // printf("status of aadhar here phata: %d", findTotalDigits(aadhar));
    // if(validateAadhar(aadhar_number)){
    //     yellow();
    //     printf("\nEnter a Valid aadhar");
    //     goto enter_aadhar_number;
    // }
    return aadhar_number;
}

//get Date from user
struct date inputDate(){
    struct date d;
    red();
    printf("\nEnter the date of birth(dd/mm/yyyy):  ");
    yellow();
    scanf("%d/%d/%d",&d.day, &d.month, &d.year);
    return d;
}

//get password from user
void inputPassword(char* pass){
    // char* pass;
    enter_password_input:
    red();
    printf("\nPassword should contain 1 alpha, 1 lower, 1 numeric and 1 special character and should have atleast 8 characters");
    printf("\nEnter a Valid password");
    yellow();
    scanf("%s", pass);
    if(validatePassword( pass)==0){
    	printf("\n Please try a different password");
    	goto enter_password_input;
    }
    // return pass;
}

//get address from user
void inputAddress(char* address){
    // char* address;
    red();
    printf("\nEnter the address:  ");
    yellow();
    scanf("%s",address);
    yellow();
    // return address;
}

//get email from user
void inputEmail(char* email){
    // char* email;
    enter_email:
    red();
    printf("\nPlease Enter Your Primary Email Address :  ");
    yellow();
    scanf("%s", email);
    if(validateEmail(email)==0){
        printf("\nPlease Enter a Validate Email Address");
        goto enter_email;
    }
    // return email;
}

//get Mobile Number from user
double inputMobileNumber(){
    double mobileNumber;
    red();
    printf("\nEnter the phone number: ");
    yellow();
    scanf("%lf", &mobileNumber);
    return mobileNumber;
}


//this method show the available type of accounts that you can open in this bank
void selectAccountType(char* type){
    int account_choice;
    // char* type;
    choose_act_type:
    red();
    printf("\nType of account:\n\t1.Saving\n\t2.Current\n\t3.Fixed1(for 1 year)\n\t4.Fixed2(for 2 years)\n\t5.Fixed3(for 3 years)\n\n\tEnter your choice:");
    yellow();
    scanf("%d",&account_choice);
    switch(account_choice){
        case 1:
            strcpy(type, "savings");
        break;
        case 2:
            strcpy(type, "current");
        break;
        case 3:
            strcpy(type, "fixed1");
        break;
        case 4:
            strcpy(type, "fixed2");
        break;
        case 5:
            strcpy(type, "fixed3");
        break;
        default:
            red();
            printf("\nPlease enter a valid choice! Retry\n");
            goto choose_act_type;
        break;
    }
    // return type;
}

//generate random and unique account Number based on the type of account that is gonna be opening
long long int generateAccountNumber(char* account_type){
    long long int acc_no;
    switch(account_type[0]){
        case 's':
            acc_no=getRandomTenDigitNumber();
        break;
        case 'c':
            acc_no=getRandomElevenDigitNumber();
        break;
        case 'f':
            acc_no=getRandomTwelveDigitNumber();
        break;
        default:
            red();
            printf("\nPlease enter a valid choice!\n");
        break;
    }
    return acc_no;
}

//checks if user with this username already exists in database
int checkIfUserWithThisUsernameAlreadyExist(FILE *recordFile, char* username){
    struct userRecord check;
    while(fscanf(recordFile,"%s %s %s %lli %d/%d/%d %s %s %lf %s %f %d/%d/%d %lli\n",check.name, check.username, check.pass, &check.acc_no, &check.dob.day, &check.dob.month, &check.dob.year, check.address, check.email, &check.phone, check.acc_type, &check.balance, &check.opening_date.day, &check.opening_date.month, &check.opening_date.year, &check.aadhar_number)!=EOF)
    {
        if (strcmp(check.username, username)==0){
            // system("cls");
            system("clear");
            red();
            printf("\nuser already Registered With same username please Enter Something else\n");
            return 0;
        }
    }
    return 1;
}

//input Opening Balance from user
double inputBalance(){
    int balance;
    balance_input:
    red();
    printf("\nOpening Balance should be 1000 or greater than 1000\nEnter the amount to deposit: INR  ");
    yellow();
    scanf("%f",&balance);
    if(balance<1000){
        red();
        printf("\nOpening Balance should be 1000 or greater than 1000 ! RETRY");
        goto balance_input;
    }
    return balance;    
}


//creating a new bank account
void new_acc(){
    FILE *recordFile;
    recordFile=fopen("record.dat","a+");
    struct userRecord newUser;
    // system("cls");
    system("clear");
    yellow();
    printf("\t\t\t\xB2\xB2\xB2  Open New Bank Account  \xB2\xB2\xB2\xB2");
    newUser.opening_date = getCurrentDate();
    printf("\n\n## Account Opening Date : %d/%d/%d ##\n\n", newUser.opening_date.day, newUser.opening_date.month, newUser.opening_date.year);
    
    enter_username_newAccount:
    inputUsername(newUser.username);
    // strcpy(newUser.username, inputUsername());
    if(checkIfUserWithThisUsernameAlreadyExist(recordFile, newUser.username)==0){
        goto enter_username_newAccount;
    }
    
    inputName(newUser.name);
    inputAddress(newUser.address);
    selectAccountType(newUser.acc_type);
    inputEmail(newUser.email);
    newUser.phone = inputMobileNumber();
    newUser.dob = inputDate();
    newUser.aadhar_number = inputAadhar();
    newUser.acc_no = generateAccountNumber(newUser.acc_type);
    char rePass[30];
    enter_password:
    inputPassword(newUser.pass);
    red();
    printf("\nRe-Enter password for confirmation");
    yellow();
	scanf("%s", rePass);
    if(strcmp(newUser.pass, rePass)==0){
        //good to go
    }else{
        red();
        printf("\npassword and Repassword does not match! Try Again");
        goto enter_password;
    } 

    newUser.balance = inputBalance();
    
    fprintf(recordFile,"%s %s %s %lli %d/%d/%d %s %s %lf %s %f %d/%d/%d %lli\n",newUser.name, newUser.username, newUser.pass, newUser.acc_no, newUser.dob.month, newUser.dob.day, newUser.dob.year, newUser.address, newUser.email, newUser.phone, newUser.acc_type, newUser.balance, newUser.opening_date.month, newUser.opening_date.day, newUser.opening_date.year, newUser.aadhar_number);
    red();
    fclose(recordFile);
    system("clear");
    printf("\nAccount created successfully!");
    fordelay(100000000);
    menu();

}

//gets userRecord from database if username and password matches
struct userRecord validateUser(char* username, char* pass){
    struct userRecord check;
    check.isLoggedIn=0;
    FILE *recordFile;
    recordFile=fopen("record.dat","a+");
    printf("\n##we are matching your credentials\n");
    while(fscanf(recordFile,"%s %s %s %lli %d/%d/%d %s %s %lf %s %f %d/%d/%d %lli\n",check.name, check.username, check.pass, &check.acc_no, &check.dob.day, &check.dob.month, &check.dob.year, check.address, check.email, &check.phone, check.acc_type, &check.balance, &check.opening_date.day, &check.opening_date.month, &check.opening_date.year, &check.aadhar_number)!=EOF)
    {
    	// printf("comaring %s : %s", username, check.username);
        if (strcmp(check.username, username)==0){
        	printf("\n##user corressponding to provided username Found ! matching Password");
            fordelay(1000000);
            if(strcmp(check.pass, pass)==0){
                check.isLoggedIn=1;
                red();
                printf("\n\n##User Successfully found Please Wait, while we are loading your Data");
                yellow();
                fordelay(100000000);
                loading_screen();
                return check;
            }else{
                printf("\n Password did Not Match");
            }
        }else{
            printf("User Not Found check your username");
        }
    }
    fclose(recordFile);
    return check;
}

void choiceScreen(struct userRecord user){
    red();
    enter_choice_profile:
    printf("\n\n\n 1>> Enter 1 to exist and goto Menu \n 2>> 0 to directly Exist \n\n"); 
    int choice;
    yellow();
    scanf("%d", &choice);
    if(choice==1){
        loading_screen();
        userScreen(user);
    }else if(choice == 0){
        close();
    }else{
        printf("\n ##Please enter a valid choice");
        goto enter_choice_profile;
    }
}

//this methods prints all the user info (of the user whose structure is passed as an argument)
void view_user_profile(struct userRecord user){
    yellow();
    printf("\n #Username : %s", user.username);
    printf("\n #Account Number : %lli", user.acc_no);
    printf("\n #Account Type : %s", user.acc_type);
    printf("\n #Name : %s", user.name);
    printf("\n #Aadhar Card Number : %lli", user.aadhar_number);
    printf("\n #Mobile Number : %fl", user.phone);
    printf("\n #DOB : %d/%d/%d", user.dob.day, user.dob.month, user.dob.year);
    printf("\n #Account Opening : %d/%d/%d", user.opening_date.day, user.opening_date.month, user.opening_date.year);
    printf("\n #Email : %s", user.email);
    printf("\n #Current Balance : %f", user.balance);
    choiceScreen();

}


//Clearing user values, for safety;
void logout(struct userRecord user){
    user.isLoggedIn = 0;
    strcpy(user.username,"");
    strcpy(user.name,"");
    strcpy(user.acc_type,"");
    strcpy(user.pass,"");
    strcpy(user.email,"");
    strcpy(user.address,"");
    user.phone=0;
    user.aadhar_number=0;
    user.acc_no=0;
    user.balance=0.0;
    user.opening_date.day=0;
    user.opening_date.month=0;
    user.opening_date.year=0;
    user.dob.day=0;
    user.dob.month=0;
    user.dob.year=0;
}


//this screen appear
void userScreen(struct userRecord user){
    int choice;
    system("clear");
    red();
    printf("\n\n\n\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2 Welcome %s \xB2\xB2\xB2\xB2\xB2\xB2\xB2\n\n",user.name);
    printf("\n 1.View Your Profile");
    printf("\n 2.Deposit");
    printf("\n 3.Withdrawal");
    printf("\n 4.Print Passbook");
    printf("\n 5.Logout");
    choose_option_userscreen:
    yellow();
    printf("\n\nPlease Enter Your choice");
    red();
    scanf("%d", &choice);
    
    switch (choice)
    {
        case 1:
            view_user_profile( user);
            break;
        case 2:
            deposit( user);
            break;
        case 3:
            withdrawal( user);
            break;
        case 4:
            print_passbook( user);
            break;
        case 5:
            logout( user);
            menu();
        default:
            printf("\n##Please choose a valid option\n");
            goto choose_option_userscreen;
            break;
    }
}

// this method updates the current balance with new balance after deposit/withrwal in userrecords;
// this method makes an entry of this transaction in bank transactions records
// if both of the above operations are done successfully it even updates the cache of logged in user with new balance;
struct userRecord updateBalanceInDatabase(float amountInAction, struct userRecord user){
    FILE *old, *newRec;
    struct userRecord check;
    old=fopen("record.dat","a+");
    newRec=fopen("new.dat","w");
    yellow();
    while(fscanf(old,"%s %s %s %lli %d/%d/%d %s %s %lf %s %f %d/%d/%d %lli\n", check.name, check.username, check.pass, &check.acc_no, &check.dob.day, &check.dob.month, &check.dob.year, check.address, check.email, &check.phone, check.acc_type, &check.balance, &check.opening_date.month, &check.opening_date.day, &check.opening_date.year, &check.aadhar_number)!=EOF) {
        if(check.acc_no==user.acc_no) {
            if(strcmp(user.acc_type, "fixed1")==0 || strcmp(user.acc_type, "fixed2")==0 || strcmp(user.acc_type, "fixed3")==0) {
                printf("\n ##Sorry But this is a Fixed Account and No Transaction could be made on this");
                fprintf(newRec,"%s %s %s %lli %d/%d/%d %s %s %lf %s %f %d/%d/%d %lli\n", check.name, check.username, check.pass, check.acc_no, check.dob.day, check.dob.month, check.dob.year, check.address, check.email, check.phone, check.acc_type, check.balance, check.opening_date.month, check.opening_date.day, check.opening_date.year, check.aadhar_number);
            } else {
                float actionCash = amountInAction;
                enterTransactionInBankRecords( actionCash, user);
                printf("actual balance : %f", user.balance);
                fprintf(newRec,"%s %s %s %lli %d/%d/%d %s %s %lf %s %f %d/%d/%d %lli\n", check.name, check.username, check.pass, check.acc_no, check.dob.day, check.dob.month, check.dob.year, check.address, check.email, check.phone, check.acc_type, user.balance, check.opening_date.month, check.opening_date.day, check.opening_date.year, check.aadhar_number);
                user.balance+=amountInAction;
            }
        } else {
            fprintf(newRec,"%s %s %s %lli %d/%d/%d %s %s %lf %s %f %d/%d/%d %lli\n", check.name, check.username, check.pass, check.acc_no, check.dob.day, check.dob.month, check.dob.year, check.address, check.email, check.phone, check.acc_type, check.balance, check.opening_date.month, check.opening_date.day, check.opening_date.year, check.aadhar_number);
        }
    }
    //delete old file and rename new file as record.dat;
    fclose(old);
    fclose(newRec);
    remove("record.dat");
    rename("new.dat", "record.dat");
    red();
    printf("#Database Updated ! Trasaction Successfull");
    fordelay(1000000000);
    return user;
}

//this methods checks if deposit is possible or not and if yes than forwards the request
//depositing amout should be greater than 500
void deposit(struct userRecord user){
    system("clear");
    yellow();
    printf("\n\n\n\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2 Welcome %s \xB2\xB2\xB2\xB2\xB2\xB2\xB2\n\n",user.name);
    enter_depositAmt_deposit:
    printf("\n###Enter the Amount You want to deposit : ");
    float depositingAmount;
    red();
    scanf("%f", &depositingAmount);
    if(depositingAmount>500){
        user = updateBalanceInDatabase(depositingAmount, user);
        yellow();
        printf("#Your Updated balance is %f", user.balance);
        fordelay(1000000000);
        userScreen(user);
    }else{
        yellow();
        printf("\n **Sorry Depositing amount should be greater than 500");
        fordelay(1000000000);
        int choice;
        printf("Do you still want to deposit money (greater than 500) \n 1>Yes\nEnter Your Choice");
        scanf("%d",&choice);
        if(choice==1){
            deposit(user);
        }
    }
    userScreen(user);
}

//this methods checks if withdrawal is possible or not and if yes than forwards the request
//500 is the minimum amount that can be withdrawn
void withdrawal(struct userRecord user){
    // system("cls");
    system("clear");
    yellow();
    printf("\n\n\n\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2 Welcome %s \xB2\xB2\xB2\xB2\xB2\xB2\xB2\n\n",user.name);
    enter_withdrawalAmt_withdrawal:
    printf("\n ###Enter the Amount you want to withdrawal : ");
    float withdrawalAmount;
    red();
    scanf("%f", &withdrawalAmount);
    yellow();
    if(withdrawalAmount>500){
        red();
        if(user.balance>withdrawalAmount){
            withdrawalAmount*=-1;
            user = updateBalanceInDatabase(withdrawalAmount, user);
            printf("\n#Your Updated balance is %f", user.balance);
            fordelay(1000000000);
            userScreen(user);
        }else{
            printf("\n\n##Sorry You dont have sufficient Baalance in your account to make this transaction");
            fordelay(1000000000);
            userScreen(user);
        }
    }else{
        red();
        printf("\n **Sorry Withdrawal amount should be greater than 500");
        fordelay(1000000000);
        int choice;
        printf("Do you still want to  try again (greater than 500) \n 1>Yes\nEnter Your Choice");
        scanf("%d",&choice);
        if(choice==1){
            withdrawal(user);
        }
    }
    userScreen(user);
}

//appends new transaction records in bank transaction history file
void enterTransactionInBankRecords(float actionCash, struct userRecord user){
    FILE *transactionRecordFile;
    transactionRecordFile=fopen( "tran_records.dat", "a+");
    struct transactionRecord tr;
    tr = createTransactionRecord(actionCash, user);
    fprintf(transactionRecordFile,"%lli %s %d/%d/%d %d:%d %f %f %f\n", tr.account_number, tr.type, tr.d.day, tr.d.month, tr.d.year, tr.t.hour, tr.t.minute, tr.old_amt, tr.amount, tr.new_amt);
    fclose(transactionRecordFile);
    return;
}

//this function creates a transaction record based on the arguments passed
struct transactionRecord createTransactionRecord(float actionCash, struct userRecord user){
    struct transactionRecord tr;
    tr.account_number=user.acc_no;
    tr.old_amt = user.balance;
    tr.amount= actionCash;
    //we are not updating user balance, we will update that memory block once whole process is succesffuly completed
    tr.new_amt = tr.old_amt + tr.amount;
    if( actionCash>0){
        strcpy(tr.type,"deposit");
    }else{
        strcpy(tr.type,"withdraw");
    }
    tr.d = getCurrentDate();
    tr.t = getCurrentTime();
    return tr;
}

//validate entered username and pass based on username and pass Policy
//after validating sends the username and pass for getting user data from records with username and password matches
void login(){
    char username[60];
    char pass[30];
    int attempts=0;
    struct userRecord user;
    red();
    loading_screen();
    yellow();
    // system("cls");
    // system("color 9");
    // printf("\n\n\t\t\tBANKING MANAGEMENT SYSTEM BY Aishwarya Sinha");
    write_username_login:
	printf("\n\n\n\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2 Please Enter Your Login Credentials \xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    printf("\n\nEnter Username :   ");
    red();
    scanf("%s", username);
    yellow();
    write_password_login:
    printf("\n\nEnter Password :   ");
    red();
    scanf("%s", pass);
    yellow();
    attempts++;
    if(attempts==3){
    	printf("\n\n##Sorry ! No Attempts Left");
    	fordelay(1000000000);
    	menu();
	}

    user =  validateUser(username, pass);

    if(user.isLoggedIn==0 && attempts<3){
        system("clear");
        printf("## %d Attempts left", 3-attempts);
        goto write_username_login;
    }else{
        userScreen(user);
    }
}

//this is the Welcome screen of the application
void menu(void){   
    int choice;
    // system("cls");
    // system("color 9");
    system("clear");
    yellow();
    // printf("\n\n\t\t\tBANKING MANAGEMENT SYSTEM BY Aishwarya Sinha");
    printf("\n\n\t\t\tBANKING MANAGEMENT SYSTEM BY Aishwarya Sinha");
    printf("\n\n\n\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2 WELCOME TO THE MAIN MENU \xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    printf("\n\n\t\t1.Login\n\t\t2.SignUp For new Account\n\t\t3.Exit\n\n\n\n\n\t\t Enter your choice:");
    red();
    scanf("%d",&choice);

    // system("cls");
    switch(choice)
    {
        case 1:
            login();
        break;
        case 2:
            new_acc();
        break;
        case 3:
            close();
        break;
        default: 
        	printf("Enter a valid response");
        	loading_screen();
        	menu(); 
        break;
    }

}

//this methods prints passbook of the user
//it uses account number to search for all the transaction made using that account
//from transaction record and prints it in the predefined way 
void print_passbook(struct  userRecord user) {
	FILE *transactionRecordFile;
    transactionRecordFile=fopen("tran_records.dat","a+");
    struct transactionRecord tr;
    system("clear");
    printf("\t\t\t\xB2\xB2\xB2  Open New Bank Account  \xB2\xB2\xB2\xB2");
    printf("\n\nAccount Number\tType\tDate\tTime\tAmount\tOld Balance\tNew Balance\n\n");
    while(fscanf(transactionRecordFile,"%lli %s %d/%d/%d %d:%d %f %f %f\n", &tr.account_number, tr.type, &tr.d.day, &tr.d.month, &tr.d.year, &tr.t.hour, &tr.t.minute, &tr.old_amt, &tr.amount, &tr.new_amt)!=EOF){
        if(tr.account_number==user.acc_no){
            printf("\n%lli\t   %s\t%d/%d/%d %d:%d\t%.1f\t%.1f\t%.1f\n", tr.account_number, tr.type, tr.d.day, tr.d.month, tr.d.year, tr.t.hour, tr.t.minute, tr.amount, tr.old_amt, tr.new_amt);
        }
    }
    fclose(transactionRecordFile);
    choieScreen(user);
}

//Entry point of our application
int main() {
    red();
    loading_screen();
    menu();
    return 0;
}
