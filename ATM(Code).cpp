#include <iostream>
#include <string.h>
#include<cmath>
using namespace std;
/*

 made by :   Omar Yasser Ezzat Ibrahem , sec:3 , bn:13;
             Omar Mahmoud Ibrahim Azzam ,  sec:3 , bn:12;
             Omar Mohamed  Abdelaziz Abdelkader , sec:3 , bn:11;

 -YOU CAN ENTER ZERO AMOUNT IN DEPOSIT,TRANSFER AND WITHDRAW AS A METHOD FOR EXITING AND RETURNING
 TO MENU.


  */

//this works as a user object model
//which contains all user data

class User
{
private :

    float amount;
    char cardNum[100];
    char userName[100];
public :

    char* getName()
    {
        return userName;
    }
    char* getNum()
    {
        return cardNum;
    }

    void setName(char* name)
    {
        strcpy(userName,name);
    }
    void setNum(char *num)
    {
        strcpy(cardNum,num);
    }
    float getAmount()
    {
        return amount;
    }
    void setDefaultAmount()
    {
        amount = 0;
    }
    void setAmountDeposit(float newAmount)
    {
        amount = amount + newAmount;
    }
    void setAmountWithdraw(float newAmount)
    {
        amount = newAmount;
    }
};

User users[100];

bool checkSymm(char* arr)//to check if the account number is easy or not
{
    for(int i =0; i<strlen(arr)-1; i++)
    {
        if(arr[i] != arr[i+1])
        {
            return false;
        }
    }
    return true;
}

int findUser(char cardNumber[100])
{
    for(int i=0; i< 100; i++)
    {

        if(strcmp(users[i].getNum(),cardNumber) == 0)
        {

            //when the card number is found return the index at which it is found
            return i;
        }
    }
    return -1;
}
//prints data of user
void printData(User usr)
{
    cout<<"Name : " <<usr.getName()<<endl;
    cout<<"Card number : " <<usr.getNum()<<endl;
    cout<<"Amount : "<< usr.getAmount()<<endl;
    return;
}

//This class handles all the interactions with the main function
//and the user model
class ATM
{
private :
    User currentUser;
    int userCount = 0;
public :
    //the array containing all users in the program
    //creates new account with amount set to zero as a default amount
    void createAcc()
    {

        bool check_digit=true;
        bool checkName=true;
        int nameCheck=0;
        int checkLength = 0;
        int length_num;
        char name[100];
        char num[100];
        User user1;
        cout<<"Please enter account name: ";
        cin.ignore();
        while(checkName)//enters name and checks if name contains numbers or special characters
        {

            cin.getline(name,100);
            for(int i =0; i<strlen(name); i++)
            {
                if(!isalpha(name[i])&(name[i]!=' '))
                {
                    nameCheck++;
                }
            }
            if(nameCheck>0)
            {
                nameCheck=0;
                cout<<"Can't have non alphabetical characters in the name.\nPlease enter your name again: ";
            }
            else if(strlen(name)==0)
            {
                cout<<"Can't have empty input.\nPlease enter a name: ";
            }
            else
            {
                checkName=false;
            }

        }
        while(check_digit)//enters number
        {
            cout<<"Please enter the account number(10 numbers): ";
            cin>>num;
            length_num = strlen(num);
            while(length_num!=10)//make sure account number is exactly ten numbers
            {
                cout<<"Invalid number.\nPlease enter exactly ten numbers with no characters."<<endl;
                cout<<"Please enter the account number(10 numbers): ";
                cin>>num;
                length_num=strlen(num);
            }
            for(int i = 0; i<10; i++)
            {
                if(isdigit(num[i]))//makes sure account number doesn't contain characters or special characters
                {
                    checkLength++;
                }
            }
            if(checkLength == 10)
            {
                check_digit=false;
            }
            else
            {
                checkLength=0;
                cout<<"You Can't enter characters in the account number."<<endl;
            }
            if(findUser(num) != -1)//makes sure account number isn't used before
            {
                checkLength = 0;
                cout<<"account number is used before."<<endl;
                check_digit=true;
            }
            else if(checkSymm(num))
            {
                checkLength = 0;
                check_digit = true;
                cout<<"Account number is too easy.\nPLease enter different combination."<<endl;
            }


        }
        user1.setName(name);
        user1.setNum(num);
        user1.setDefaultAmount();
        users[userCount] = user1;
        printData(user1);
        userCount++;
    }


    void deposit()
    {
        int length_num,find_u,i;
        int checkLength=0;
        int checkDigit=-1;
        char num[100];
        bool error=true;
        bool checkFloos = true;
        bool accExist=false;
        bool check_digit=true;
        char floos[100];
        for(int i = 0; i<100; i++)
        {
            floos[i] = {'0'};
        }
        float money;
        while(check_digit)
        {
            cout<<"Please enter the account number(10 numbers): ";
            cin>>num;
            length_num = strlen(num);
            while(length_num!=10)
            {
                cout<<"Invalid number.\nPlease enter exactly ten numbers with no characters."<<endl;
                cout<<"Please enter the account number(10 numbers): ";
                cin>>num;
                length_num=strlen(num);
            }
            for(int i = 0; i<10; i++)
            {
                if(isdigit(num[i]))
                {
                    checkLength++;
                }
            }
            if(checkLength == 10)
            {
                check_digit=false;
            }
            else
            {
                checkLength=0;
                cout<<"You Can't enter characters in the account number."<<endl;

            }
        }
        find_u=findUser(num);
        if(find_u==-1)
        {
            cout<<"This account does not exist.\nExiting........"<<endl;
            accExist = false;
        }
        else
        {
            i=find_u;
            accExist = true;
        }
        if(!accExist)
        {
            return;
        }
        cout<<"Please enter the amount to be deposited: ";
        while(checkFloos)
        {
            cin>>floos;
            for(int i = 0; i<100; i++)
            {
                if(!isdigit(floos[i]) & (floos[i] != '.'))
                {
                    checkDigit++;
                }
            }
            if(checkDigit>0)
            {
                for(int i = 0; i<100; i++)
                {
                    floos[i] = {'0'};
                }
                checkDigit = -1;
                cout<<"you cant enter characters in the amount.\nPlease enter amount again: ";
            }
            else
            {
                checkFloos = false;
            }
        }
        money = atof(floos);
        users[i].setAmountDeposit(1.01*money);
        printData(users[i]);

    }

    //withdraws money form user object
    void withdraw()
    {
        int length_num,find_u,i;
        int checkLength=0;
        int checkDigit=-1;
        char num[100];
        char floos[100];
        float money;
        bool accExist = false;
        bool checkFloos = true;
        bool check_digit=true;
        for(int i = 0; i<100; i++)
        {
            floos[i] = {'0'};
        }
        while(check_digit)
        {
            cout<<"Please enter the account number(10 numbers): ";
            cin>>num;
            length_num = strlen(num);
            while(length_num!=10)
            {
                cout<<"Invalid number.\nPlease enter exactly ten numbers with no characters."<<endl;
                cout<<"Please enter the account number(10 numbers): ";
                cin>>num;
                length_num=strlen(num);
            }
            for(int i = 0; i<10; i++)
            {
                if(isdigit(num[i]))
                {
                    checkLength++;
                }
            }
            if(checkLength == 10)
            {
                check_digit=false;
            }
            else
            {
                checkLength=0;
                cout<<"You Can't enter characters in the account number."<<endl;

            }
        }
        find_u=findUser(num);
        if(find_u==-1)
        {
            cout<<"This account does not exist.\nExiting........"<<endl;
            accExist = false;
        }
        else
        {
            i=find_u;
            accExist = true;
        }
        if(!accExist)
        {
            return;
        }
        //assign the index int to the index of the object with the wanted card number
        int index = findUser(num);
        //check if the card number is found
        //if found ((index != -1)) do the operation
        if(index != -1)
        {
            if(users[index].getAmount()!=0)
            {
                cout<<"Please enter the amount to be withdrawn: ";
                while(checkFloos)
                {
                    cin>>floos;
                    for(int i = 0; i<100; i++)
                    {
                        if(!isdigit(floos[i]) & (floos[i] != '.'))
                        {
                            checkDigit++;
                        }
                    }
                    if(checkDigit>0)
                    {
                        for(int i = 0; i<100; i++)
                        {
                            floos[i] = {'0'};
                        }
                        checkDigit = -1;
                        cout<<"you cant enter characters in the amount.\nPlease enter amount again: ";
                    }
                    else
                    {
                        checkFloos = false;
                    }
                }
                money = atof(floos);
                //users[index] refers to the user with the entered account number
                //get the current amount in the chosen user object
                float amount = users[index].getAmount();
                if(amount < (money + money*0.03))
                {
                    cout<<"Not enough money for this operation.\nExiting......."<<endl;
                    printData(users[index]);
                    return;
                }
                else
                {
                    //sets the amount to the new amount after the withdrawal process
                    users[index].setAmountWithdraw(amount - (money + money*0.03));
                    printData(users[index]);
                }
            }
            else cout<<"This account is empty.\nExiting....."<<endl;
        }
        else
        {
            cout<<"This account does not exist.\nExiting....."<<endl;
            return;
        }

    }

    void transfer()
    {
        int length_num,find_u,i,j;
        int checkLength1 = 0;
        int checkLength2 = 0;
        int checkDigit=-1;
        float money;
        char floos[100];
        char num[100];
        bool error1=true;
        bool accFirstExist = false;
        bool accSecondExist = false;
        bool error2=true;
        bool trans=true;
        bool checkFloos = true;
        for(int i = 0; i<100; i++)
        {
            floos[i] = {'0'};
        }
        //checks that the card number is proper
        while(error1)
        {
            cout<<"Please enter the number of the sending account(10 numbers) :";
            cin>>num;
            length_num = strlen(num);
            while(length_num!=10)
            {
                cout<<"Invalid number.\nPlease enter exactly ten numbers with no characters."<<endl;
                 cout<<"Please enter the number of the sending account(10 numbers) :";
                cin>>num;
                length_num=strlen(num);
            }
            for(int i = 0; i<10; i++)
            {
                if(isdigit(num[i]))
                {
                    checkLength1++;
                }
            }
            if(checkLength1 == 10)
            {
                error1=false;
            }
            else
            {
                checkLength1=0;
                cout<<"You Can't enter characters in the account number."<<endl;
            }


        }
        find_u=findUser(num);
        if(find_u==-1)
        {
            cout<<"The account does not exist.\nExiting....."<<endl;

        }
        else
        {
            i=find_u;

            accFirstExist = true;
        }
        if(!accFirstExist)
        {
            return;
        }
        //receiving starts here
        if(users[i].getAmount()!=0)
        {
            while(error2)
            {
                cout<<"please enter the number of the receiving account(10 numbers) :";
                cin>>num;
                length_num = strlen(num);
                while(length_num!=10)
                {
                    cout<<"Invalid number.\nPlease enter exactly ten numbers with no characters."<<endl;
                    cout<<"please enter the number of the receiving account (10 numbers): ";
                    cin>>num;
                    length_num=strlen(num);
                }
                for(int i = 0; i<10; i++)
                {
                    if(isdigit(num[i]))
                    {
                        checkLength2++;
                    }
                }
                if(checkLength2 == 10)
                {
                    error2=false;
                }
                else
                {
                    checkLength2=0;
                    cout<<"You Can't enter characters in the account number."<<endl;
                }


            }
            find_u=findUser(num);
            if(find_u==-1)
            {
                cout<<"The receiving account does not exist.\nExiting....."<<endl;
                return;
            }
            else
            {
                j=find_u;
                accSecondExist = true;
            }
            while(trans)
            {
                cout<<"Please enter the amount to be transferred: ";
                while(checkFloos)
                {
                    cin>>floos;
                    for(int i = 0; i<100; i++)
                    {
                        if(!isdigit(floos[i]) & (floos[i] != '.'))
                        {
                            checkDigit++;
                        }
                    }
                    if(checkDigit>0)
                    {
                        for(int i = 0; i<100; i++)
                        {
                            floos[i] = {'0'};
                        }
                        checkDigit = -1;
                        cout<<"you can't enter characters in the amount.\nPlease enter amount again :";
                    }
                    else
                    {
                        checkFloos = false;
                    }
                }
                money = atof(floos);//converts characters of array to float
                if (users[i].getAmount()<1.015*money)
                {
                    cout<<"There's not enough money for this operation."<<endl;
                    cout<<"You have: "<<users[i].getAmount()<<" in the sending account."<<endl;
                    return;
                }
                else
                {
                    trans=false;
                }
            }
            users[i].setAmountWithdraw(users[i].getAmount()-1.015*money);
            users[j].setAmountDeposit(0.985*money);
            cout<<"Sending account: "<<endl;
            printData(users[i]);
            cout<<"Receiving account: "<<endl;
            printData(users[j]);
        }
        else cout<<"The sending account is empty."<<endl;
    }
};


int main()
{
    int opNum;
    //char tempCard[100];
    ATM atm;
    char clearer[100];//just to initialize arrays

    for(int i =0; i<100; i++)
    {
        User user;
        for(int z = 0; z<100; z++)
        {
            clearer[z] = {'0'};
        }
        for(int j = 0; j<100; j++)
        {
            clearer[j] = {'0'};
        }
        user.setName(clearer);
        user.setDefaultAmount();
        user.setNum(clearer);
        users[i] = user;
    }

    //specifies the application statues
    bool active = true;
    //the program main loop
    //terminates when the user enters the exit command
    while(active)
    {
        cout<<"1---Create new account"<<endl;
        cout<<"2---Deposit"<<endl;
        cout<<"3---Transfer to another account"<<endl;
        cout<<"4---Withdraw"<<endl;
        cout<<"5---Exit"<<endl;
        cout<<"Please enter the number of operation: ";
        if(cin>>opNum)
        {
            if(opNum==1)
            {
                atm.createAcc();
            }
            else if(opNum==2)
            {
                atm.deposit();
            }
            else if(opNum==4)
            {
                atm.withdraw();
            }
            else if(opNum==3)
            {
                atm.transfer();
            }
            else if(opNum==5)
            {
                active = false;
            }
            else
            {
                cout<<"Invalid operation.\nPlease enter a valid operation number."<<endl;
            }
        }
        else
        {
            cout<<"Invalid input.\nPlease enter a valid operation number."<<endl;
            cin.clear();
            cin.ignore(1000,'\n');

        }

    }
    return 0;

}
