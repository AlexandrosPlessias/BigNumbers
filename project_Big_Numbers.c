#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/*-----------------------Struct & Heads----------------------------------- */
typedef struct bigNumber    // This struct is used to save big number.
{
    char digitOfNumber;
    struct bigNumber *next;
} bigNumber;

struct bigNumber *headOfFistNumber;    // GLOBAL Head pointer.
struct bigNumber *headOfSecondNumber;  // GLOBAL Head pointer.
struct bigNumber *headOfResultNumber;  // GLOBAL Head pointer.

/*-----------------------Signatures--------------------------------------- */
void TextArt();                                // Welcome text.
int Menu();                                    // Display menus and choice.
void calcSimulation();                         // Simulation until the user presses the 0.
void readAndSaveNumber(int listCode);          // Dynamic reading character by character and storage to stack.
void insertDigitInBigNumber(int listCode, char digit);      // Add character to the stack of listCode Number (i.e. at Head of the single-linked list).
void insertZero(int listCode,double position); // Add character (here zero) in the penultimate node of the stack (before the sign).
double sizeOfNumber (int listCode);            // Calculate the size of the number (i.e. nodes) called before the alignmentNumbers().
void alignmentNumbers();                       // Calculates how many zeros should be added to the first and second number to be equal.
void addFunction ();                           // Addition operation request numbers, find signs,  calls addNumbers(), shows the result and then free the stacks.
void addNumbers(char sign);                    // Adds the first and the second number and places the sign that is given as an argument .
void subFunction();                            // Subtraction operation request numbers, find sings, calls subNumbers(), shows the result and then free the stacks.
void subNumbers(bigNumber* subtracter ,bigNumber* subtrahend,char sign);    // Sub subtracter by subtrahend and places the sign that is given as an argument.
int greaterFirstOrSecond( double position);     // Check digits for a specific position (and at 2 numbers) and inform us about who is bigger or whether they are equal.
void printNumber(int listCode );               // Display the Big Number given as argument and hide first zeros.
void freeList(int listCode);                   // Empty stack and initialize head pointers.
void clearBuffer();                            // Clean input Buffer.


/*---------------------Start of main--------------------------------------- */
int main(void){
    TextArt();
    calcSimulation();
    printf("\n                               Goodbye !!!\n");
    return 0;
}


/*----------------------Functions-----------------------------------------*/
void TextArt()  // Welcome text & Do you want to continue?.
{
    char ch;
    printf("     ____  _         _   _                 _");
    printf("\n    | __ )(_) __ _  | \\ | |_   _ _ __ ___ | |__   ___ _ __ ___ ");
    printf("\n    |  _ \\| |/ _` | |  \\| | | | | '_ ` _ \\| '_ \\ / _ \\ '__/ __|");
    printf("\n    | |_) | | (_| | | |\\  | |_| | | | | | | |_) |  __/ |  \\__ \\");
    printf("\n    |____/|_|\\__, | |_| \\_|\\__,_|_| |_| |_|_.__/ \\___|_|  |___/");
    printf("\n             |___/");
    printf("\n            ____      _            _       _        ____ ");
    printf("\n           / ___|__ _| | ___ _   _| | __ _| |_ ___ |  _ \\");
    printf("\n          | |   / _` | |/ __| | | | |/ _` | __/ _ \\| |_) |");
    printf("\n          | |__| (_| | | (__| |_| | | (_| | || (_) |  _ <");
    printf("\n           \\____\\__,_|_|\\___|\\__,_|_|\\__,_|\\__\\___/|_| \\_\\");
    printf("\n\n\n      Addition & Subtraction for Big Numbers (sings Supported).");
    do
    {
        printf("\n                   Do you want to continue, y/n? ");
        ch=getchar();
        clearBuffer();
    }
    while ((ch != 'y') && (ch != 'n')); // Ask the user if want to start Simulation or not!

    if (ch=='n')
        exit(0);
}


int Menu()  // Display menus and choice.
{

    char menu;
    int choice;

    do
    {
        printf("\n                  +================================+");
        printf("\n                  |             Menu               |");
        printf("\n                  +================================+");
        printf("\n                  |  Options:                      |");
        printf("\n                  |         1. Addition            |");
        printf("\n                  |         2. Subtraction         |");
        printf("\n                  |         0. Exit                |");
        printf("\n                  +================================+\n");

        printf("\n                 Please, select a option from 0 to 2: ");
        menu=getchar();
        printf("                           Option %c selected.\n",menu);

        if(!((menu=='1') || (menu=='2') ||(menu=='0')))
        {
            printf("\n           *** Try to choice between [0 - 2] next time. ***\n\n");
            clearBuffer();
        }
    }
    while (!((menu=='1') || (menu=='2') ||(menu=='0')));

    choice = menu -'0' ;
    return choice;
}


void calcSimulation() // Simulation until the user presses the 0.
{
    int choice;
    do
    {
        headOfFistNumber=NULL;
        headOfSecondNumber=NULL;
        headOfResultNumber=NULL;
        choice= Menu();
        clearBuffer();
        if(choice==1)
            addFunction();
        else if (choice==2)
            subFunction();
    }
    while (choice!=0);
}


void readAndSaveNumber(int listCode) // Dynamic reading character by character and storage to stack.
{
    char charBuffer;  // Char Buffer.
    int first=-1;     // First == 0 in first while loop.
    int properFormat; // Format flag.
    int zeroFirst;    // Zero flag.
    int signPresed;   // Sign flag

    do{
        (listCode==1)?(printf("\n\nPlease, give first Big Number (with or without sign):\n")):(printf("\n\nPlease, give second Big Number (with or without sign):\n"));
        properFormat=1;
        zeroFirst=0;
        signPresed=0;

        // Until the format is acceptable.
        while(1)
        {
            first++;
            charBuffer=getchar();

            // Checking user input.
            // If don't give sign add '+';
            if((isdigit(charBuffer))&&(first==0))
            {
                (listCode==1)?(insertDigitInBigNumber(1,'+')):(insertDigitInBigNumber(2,'+'));
                // Don't add first 0.
                if(charBuffer!='0'){
                    (listCode==1)?(insertDigitInBigNumber(1,charBuffer)):(insertDigitInBigNumber(2,charBuffer));
                }else{
                       zeroFirst=1;
                }
            }
            // Give number.
            else if(isdigit(charBuffer))
            {
                if((charBuffer=='0')&&(zeroFirst==1)){
                // Do nothing.
                }else{
                    (listCode==1)?(insertDigitInBigNumber(1,charBuffer)):(insertDigitInBigNumber(2,charBuffer));
                    zeroFirst=0;
                }
            }
            // Press enter first without type anything before.
            else if((charBuffer=='\n')&&(first==0))
            {
                properFormat=0;
                break;
            }
            // Press enter and press enter after sign and no number.
            else if(charBuffer=='\n')
            {
                if ((signPresed==1)&&(first==1)){
                        properFormat=0;
                }
                break;
            }
            // Give first sign.
            else if(((charBuffer=='+')||(charBuffer=='-'))&&(first==0))
            {
                (listCode==1)?(insertDigitInBigNumber(1,charBuffer)):(insertDigitInBigNumber(2,charBuffer));
                zeroFirst=1;
                signPresed=1;
            }
            // Press anything other than numbers & signs.
            else
            {
                properFormat=0;
            }
        }

        // If the format is not suitable then initialize flags, message display, clean buffer & free.
        if(properFormat==0){
            printf("Please, try to give numbers only and + or - in start of number if you want.");
            (listCode==1)?( printf("\nPlease press ENTER and type again First Number ...")):(printf("\nPlease press ENTER type again Second Number ..."));
            first=-1;
            freeList(listCode);
            clearBuffer();
        }
    }while (properFormat==0);
}


void insertDigitInBigNumber(int listCode, char digit)  // Add character to the stack of listCode Number (i.e. at Head of the single-linked list).
{

    bigNumber *newDigit;

    newDigit = (bigNumber*) malloc( sizeof( bigNumber ));   // Memory allocation to create new nodes.

    if ( newDigit != NULL )       // If space available store the digit in struct.
    {
			newDigit->digitOfNumber=digit; // Copies of user data at new node.
			if(listCode==1){
				newDigit->next = headOfFistNumber; // The Memory allocation from before is a node of the stack, which linked in stack with next.
				headOfFistNumber=newDigit;  // Now this node becomes the new head of the stack.
			}else if(listCode==2)
			{
				newDigit->next = headOfSecondNumber; // The Memory allocation from before is a node of the stack, which linked in stack with next.
				headOfSecondNumber=newDigit;  // Now this node becomes the new head of the stack.
			}else if(listCode==3){
				newDigit->next = headOfResultNumber; // The Memory allocation from before is a node of the stack, which linked in stack with next.
				headOfResultNumber=newDigit;  // Now this node becomes the new head of the stack.
			}else{
                printf("WRONG LIST CODE !!!\n");
                exit(0);
			}
    }else{
        printf("No memory available.\n" );
        exit(0);
    }
}


void insertZero(int listCode, double position) // Add character (here zero) in the penultimate node of the stack (before the sign).
{
    // Two utility Pointers.
    bigNumber  *LeftDigit=NULL,*RightDigit=NULL;

    if(listCode==1){
        RightDigit=headOfFistNumber;
    }else if(listCode==2){
        RightDigit=headOfSecondNumber;
    }else{
        printf("WRONG LIST CODE !!!\n");
        exit(0);
    }

    bigNumber *newDigit;
    newDigit=(bigNumber *)malloc(sizeof(bigNumber));

    if ( newDigit != NULL )       //if space available (after the input check from the last function) store the data of the client in struct
        {
        double i;
        for(i=1; i<position; i++) // Find position i want and the next one.
        {
            LeftDigit=RightDigit;
            RightDigit=RightDigit->next;
        }
        newDigit->digitOfNumber='0';    // Add '0' at new node.
        LeftDigit->next=newDigit;   // The Memory allocation from before is a node of the stack, which linked in stack with next.
        LeftDigit=newDigit; // Now this node becomes the new head in position i want.
        LeftDigit->next=RightDigit; // The new node lined with the next.
    }else{
        printf("No memory available.\n" );
        exit(0);
    }
}


double sizeOfNumber (int listCode) // Calculate the size of the number (i.e. nodes) called before the alignmentNumbers().
{
    // Utility Pointer.
    bigNumber *temp;

    if(listCode==1){
        temp=headOfFistNumber;
    }else if(listCode==2){
        temp=headOfSecondNumber;
    }else{
        printf("WRONG LIST CODE !!!\n");
        exit(0);
    }

    double count=0;
    if ( temp == NULL )
        printf( "\n\nList is empty." );
    else{
        // Pass from node to node until you find the end of the list (i.e. NULL) and increase counter.
        while ( temp != NULL ){
            count++;
            temp = temp->next;
        }
    }
    return count;
}


void alignmentNumbers () // Calculates how many zeros should be added to the first and second number to be equal.
{
    int i=0;
    if (sizeOfNumber(1)==sizeOfNumber(2)){
        return;
    }else if (sizeOfNumber(1)>sizeOfNumber(2)){
        // Calculations of amounts zeros should be added
        double zeroStuffing=sizeOfNumber(1)-sizeOfNumber(2);
        for(i=0; i<zeroStuffing; i++)
        {
            insertZero(2,sizeOfNumber(2)); //Adding these at end (real in semifinal) of the number.
        }
    }else { // (sizeOfNumber(1)<sizeOfNumber(2))
        // Calculations of amounts zeros should be added
        double zeroStuffing=sizeOfNumber(2)-sizeOfNumber(1);
        for(i=0; i<zeroStuffing; i++){
            insertZero(1,sizeOfNumber(1)); //Adding these at end (real in semifinal) of the number.
        }
    }
}

void addFunction () // Addition operation request numbers, find sings,  calls addNumbers(), shows the result and then free the stacks.
{
    // Request numbers.
    readAndSaveNumber(1);
    readAndSaveNumber(2);

    bigNumber  *tempHeadFirst=NULL, *tempHeadSecond=NULL;
	char signOfFirst=' ';
    char signOfSecond=' ';

    tempHeadFirst=headOfFistNumber;
    tempHeadSecond=headOfSecondNumber;

    //Find first number sign.
    while (tempHeadFirst->next !=NULL){
        tempHeadFirst=tempHeadFirst->next;
    }

    //Find second number sign.
    while (tempHeadSecond->next !=NULL){
        tempHeadSecond=tempHeadSecond->next;
    }

    signOfFirst = tempHeadFirst->digitOfNumber ;
    signOfSecond = tempHeadSecond->digitOfNumber ;

    // Possible options.
    if (sizeOfNumber(1) > sizeOfNumber(2)){
        if((signOfFirst=='+')&&(signOfSecond=='-'))
            subNumbers(headOfFistNumber,headOfSecondNumber,'+'); // a-b WITH '+'.
        else if ((signOfFirst=='-')&&(signOfSecond=='+'))
            subNumbers(headOfFistNumber,headOfSecondNumber,'-'); // a-b WITH '-'.
        else if ((signOfFirst=='+')&&(signOfSecond=='+'))
            addNumbers('+');                                     // a+b WITH '+'.
        else if((signOfFirst=='-')&&(signOfSecond=='-'))
            addNumbers('-');                                     // a+b WITH '-'.
    }else if(sizeOfNumber(1) < sizeOfNumber(2)){
        if((signOfFirst=='+')&&(signOfSecond=='-'))
            subNumbers(headOfSecondNumber,headOfFistNumber,'-'); // b-a WITH '-'.
        else if ((signOfFirst=='-')&&(signOfSecond=='+'))
            subNumbers(headOfSecondNumber,headOfFistNumber,'+'); // b-a WITH '+'.
        else if ((signOfFirst=='+')&&(signOfSecond=='+'))
            addNumbers('+');                                     // a+b WITH '+'.
        else if((signOfFirst=='-')&&(signOfSecond=='-'))
            addNumbers('-');                                    // a+b WITH '-'.
    }else if (sizeOfNumber(1) == sizeOfNumber(2)){
        double newSize;
        double i=0;

        // In every loop Search for not equal digits call the correct function and break.
        do{
			newSize =(sizeOfNumber(1) -i)-1;
            // If digit of First number in greater than the corresponding of second Number
            if (greaterFirstOrSecond(newSize)==1){
				if((signOfFirst=='+')&&(signOfSecond=='-'))
					subNumbers(headOfFistNumber,headOfSecondNumber,'+'); // a-b WITH '+'.
				else if ((signOfFirst=='-')&&(signOfSecond=='+'))
                    subNumbers(headOfFistNumber,headOfSecondNumber,'-'); // a-b WITH '-'.
				else if ((signOfFirst=='+')&&(signOfSecond=='+'))
                    addNumbers('+');                                     // a+b WITH '+'.
				else if((signOfFirst=='-')&&(signOfSecond=='-'))
					addNumbers('-');                                     // a+b WITH '-'.

				break;
			}
			// If digit of First number in lesser than the corresponding of second Number
			else if(greaterFirstOrSecond(newSize)==2){
				if((signOfFirst=='+')&&(signOfSecond=='-'))
					subNumbers(headOfSecondNumber,headOfFistNumber,'-'); // b-a WITH '-'.
				else if ((signOfFirst=='-')&&(signOfSecond=='+'))
					subNumbers(headOfSecondNumber,headOfFistNumber,'+'); // b-a WITH '+'.
				else if ((signOfFirst=='+')&&(signOfSecond=='+'))
					addNumbers('+');                                     // a+b WITH '+'.
				else if((signOfFirst=='-')&&(signOfSecond=='-'))
					addNumbers('-');                                     // a+b WITH '-'.

				break;
			} else if (greaterFirstOrSecond(newSize)==0){
					// Do nothing
            }
            i++;
        }while (newSize!=0);

		// Case First number equal with Second number.
        if(newSize==0){
            if((signOfFirst=='+')&&(signOfSecond=='-'))
					subNumbers(headOfSecondNumber,headOfFistNumber,'-'); // a-a=0 WITH '-'.
            else if ((signOfFirst=='-')&&(signOfSecond=='+'))
					subNumbers(headOfSecondNumber,headOfFistNumber,'+'); // a-a=0 WITH '+'.
            else if ((signOfFirst=='+')&&(signOfSecond=='+'))
					addNumbers('+');                                     // a+a=2a WITH '+'.
            else if((signOfFirst=='-')&&(signOfSecond=='-'))
					addNumbers('-');                                    // a+a=-2a WITH '-'
        }
    }

    printf("\nResult:\n");
    printNumber(3);
    printf("\n");

    freeList(1);
    freeList(2);
    freeList(3);
    }


void addNumbers(char sign) // Adds the first and the second number and places the sign that is given as an argument .
{
    bigNumber *headFirst, *headSecond;

    headFirst=headOfFistNumber;
    headSecond=headOfSecondNumber;

    int tempFistNumberDigit;
    int tempSecondNumberDigit;
    int resultNumberDigit=0;
    char curDigit;

    alignmentNumbers();

    // Pass all the nodes until the penultimate.
    while (headFirst->next !=NULL){
        tempFistNumberDigit=0;
        tempSecondNumberDigit=0;
        curDigit = ' ';

        // Digit of first number from char to integer also add remainder if exists.
        tempFistNumberDigit = ((headFirst->digitOfNumber)- '0')+(resultNumberDigit/10);
        resultNumberDigit =0;
        // Digit of second number from char to integer.
        tempSecondNumberDigit = (headSecond->digitOfNumber)-'0';

        // Add Digit of first number & Digit of first number.
        resultNumberDigit=tempFistNumberDigit+tempSecondNumberDigit;
        // Take resultNumberDigit%10 and convert to char.
        curDigit = (resultNumberDigit%10) + '0' ;
        insertDigitInBigNumber(3,curDigit);

        // Next Digits.
        headFirst = headFirst->next;
        headSecond = headSecond->next;
    }

    if((resultNumberDigit/10)!=0){
        insertDigitInBigNumber(3,(resultNumberDigit/10)+'0');
    }

    // Add sign.
    insertDigitInBigNumber(3,sign);
}


void subFunction ()  // Subtraction operation request numbers, find sings, calls subNumbers(), shows the result and then free the stacks.
{

    // Request numbers.
    readAndSaveNumber(1);
    readAndSaveNumber(2);

    bigNumber  *tempHeadFirst=NULL, *tempHeadSecond=NULL;
    char signOfFirst=' ';
    char signOfSecond= ' ';

    tempHeadFirst=headOfFistNumber;
    tempHeadSecond=headOfSecondNumber;

    //Find first number sign.
    while (tempHeadFirst->next !=NULL){
        tempHeadFirst=tempHeadFirst->next;
    }

    //Find second number sign.
    while (tempHeadSecond->next !=NULL){
        tempHeadSecond=tempHeadSecond->next;
    }

    signOfFirst = tempHeadFirst->digitOfNumber ;
    signOfSecond = tempHeadSecond->digitOfNumber ;

    // Possible options.
    if (sizeOfNumber(1) > sizeOfNumber(2)){
        if((signOfFirst=='+')&&(signOfSecond=='-'))
            addNumbers('+');                                     // a+b WITH '+'.
        else if ((signOfFirst=='-')&&(signOfSecond=='+'))
            addNumbers('-');                                     // a+b WITH '-'.
        else if ((signOfFirst=='+')&&(signOfSecond=='+'))
            subNumbers(headOfFistNumber,headOfSecondNumber,'+'); // a-b WITH '+'.
        else if((signOfFirst=='-')&&(signOfSecond=='-'))
            subNumbers(headOfFistNumber,headOfSecondNumber,'-'); // a-b WITH '-'.
    }else if(sizeOfNumber(1) < sizeOfNumber(2)){
        if((signOfFirst=='+')&&(signOfSecond=='-'))
            addNumbers('+');                                     // a+b WITH '+'.
        else if ((signOfFirst=='-')&&(signOfSecond=='+'))
            addNumbers('-');                                     // a+b WITH '-'.
        else if ((signOfFirst=='+')&&(signOfSecond=='+'))
            subNumbers(headOfSecondNumber,headOfFistNumber,'-'); //b-a WITH '-'.
        else if((signOfFirst=='-')&&(signOfSecond=='-'))
            subNumbers(headOfSecondNumber,headOfFistNumber,'+'); //b-a WITH '+'.
    }else if (sizeOfNumber(1) == sizeOfNumber(2)){
        double newSize;
        double i=0;

        // In every loop Search for not equal digits call the correct function and break.
        do{
            newSize =(sizeOfNumber(1) -i)-1;
            // If digit of First number in greater than the corresponding of second Number
            if (greaterFirstOrSecond(newSize)==1)
            {
                if((signOfFirst=='+')&&(signOfSecond=='-'))
                    addNumbers('+');                                     // a+b WITH '+'.
                else if ((signOfFirst=='-')&&(signOfSecond=='+'))
                    addNumbers('-');                                     // a+b WITH '-'.
                else if ((signOfFirst=='+')&&(signOfSecond=='+'))
                    subNumbers(headOfFistNumber,headOfSecondNumber,'+'); //a-b WITH '+'.
                else if((signOfFirst=='-')&&(signOfSecond=='-'))
                    subNumbers(headOfFistNumber,headOfSecondNumber,'-'); //a-b WITH '-'.

                break;
            }
            // If digit of First number in lesser than the corresponding of second Number
            else if(greaterFirstOrSecond(newSize)==2){
                if((signOfFirst=='+')&&(signOfSecond=='-'))
                    addNumbers('+');                                     // a+b WITH '+'.
                else if ((signOfFirst=='-')&&(signOfSecond=='+'))
                    addNumbers('-');                                     // a+b WITH '-'.
                else if ((signOfFirst=='+')&&(signOfSecond=='+'))
                    subNumbers(headOfSecondNumber,headOfFistNumber,'-'); //b-a WITH '-'.
                else if((signOfFirst=='-')&&(signOfSecond=='-'))
                    subNumbers(headOfSecondNumber,headOfFistNumber,'+'); //b-a WITH '+'.

                break;
            }
            else if (greaterFirstOrSecond(newSize)==0){
                // Do nothing
            }
            i++;
        }while (newSize!=0);

        // Case First number equal with Second number.
        if(newSize==0){
             if((signOfFirst=='+')&&(signOfSecond=='-'))
                    addNumbers('+');                                     // a+b WITH '+'.
                else if ((signOfFirst=='-')&&(signOfSecond=='+'))
                    addNumbers('-');                                     // a+b WITH '-'.
                else if ((signOfFirst=='+')&&(signOfSecond=='+'))
                    subNumbers(headOfFistNumber,headOfSecondNumber,'+'); //b-a WITH '-'.
                else if((signOfFirst=='-')&&(signOfSecond=='-'))
                    subNumbers(headOfFistNumber,headOfSecondNumber,'+'); //b-a WITH '+'.
        }
    }

    printf("\nResult:\n");
    printNumber(3);
    printf("\n");

    freeList(1);
    freeList(2);
    freeList(3);
}


void subNumbers(bigNumber* subtracter ,bigNumber* subtrahend,char sign) // Sub subtracter by subtrahend and places the sign that is given as an argument.
{

    bigNumber *headFirst=subtracter, *headSecond=subtrahend; // subtracter: a - subtrahend: b

    alignmentNumbers();

    int tempFistNumberDigit;
    int tempSecondNumberDigit;
    int resultNumberDigit=0;
    int ypol =0;
    char curDigit;

    // Pass all the nodes until the penultimate.
    while (headFirst->next !=NULL)
    {
        tempFistNumberDigit=0;
        tempSecondNumberDigit=0;
        resultNumberDigit =0;
        curDigit = ' ';

        // Digit of first number from char to integer.
        tempFistNumberDigit = (headFirst->digitOfNumber)- '0';
        // Digit of second number from char to integer also add remainder if exists.
        tempSecondNumberDigit = ((headSecond->digitOfNumber)-'0')+ypol;

        ypol =0;
        // Sub Digit of first number & Digit of first number.
        if(tempFistNumberDigit>=tempSecondNumberDigit)
        {
            resultNumberDigit=tempFistNumberDigit-tempSecondNumberDigit;
        }
        else    // tempFistNumberDigit< tempSecondNumberDigit
        {
            resultNumberDigit=(tempFistNumberDigit+10)-tempSecondNumberDigit;
            ypol =1;
        }

        // Take resultNumberDigit%10 and convert to char.
        curDigit = resultNumberDigit + '0';
        insertDigitInBigNumber(3,curDigit);

        // Next Digits.
        headFirst = headFirst->next;
        headSecond = headSecond->next;
    }

    if(ypol!=0)
    {
        insertDigitInBigNumber(3,(ypol+'0'));
    }

    // Add sign.
    insertDigitInBigNumber(3,sign);
}


int greaterFirstOrSecond( double position) // Check digits for a specific position (and at 2 numbers) and inform us about who is bigger or whether they are equal.
{
    // Two utility Pointers.
    bigNumber  *DigitFirstNum=NULL;
    bigNumber  *DigitSecondNum=NULL;

    DigitFirstNum=headOfFistNumber;
    DigitSecondNum=headOfSecondNumber;

    double i;
    for(i=1; i<position; i++) // Find position i want .
    {
        DigitFirstNum=DigitFirstNum->next;
        DigitSecondNum=DigitSecondNum->next;
    }

    int difference=((DigitFirstNum->digitOfNumber)-'0')-((DigitSecondNum->digitOfNumber)-'0');

    // Checking.
    if(difference==0)
        return 0;
    else if(difference>0)
        return 1;   // a>b
    else
        return 2;   //a<b
}


void printNumber(int listCode ) // Display the Big Number given as argument and hide first zeros.
{
    // Utility pointer.
    bigNumber *temp;

    if(listCode==1){
        temp=headOfFistNumber;
    }else if(listCode==2){
        temp=headOfSecondNumber;
    }else if(listCode==3){
        temp=headOfResultNumber;
    }else{
        printf("WRONG LIST CODE !!!\n");
        exit(0);
    }

    if ( temp == NULL )
        printf( "\n\nList is empty." );
    else{
        // Pass all the nodes until the end.

         printf("%c",temp->digitOfNumber); // Print signs
        do{
                temp = temp->next; // skip'0's
        }while (temp->digitOfNumber=='0');

        while ( temp != NULL )
        {
            printf("%c",temp->digitOfNumber); // Print of each digit
            temp = temp->next; // Go to next.
        }
    }
    free(temp);
}


void freeList(int listCode) // Empty stack and initialize head pointers.
{

    // Utility pointers.
    bigNumber *nextDigit;
    bigNumber *temp;

    // Utility shows at the head.
    if(listCode==1)
    {
        temp=headOfFistNumber;
    }
    else if(listCode==2)
    {
        temp=headOfSecondNumber;
    }
    else if(listCode==3)
    {
        temp=headOfResultNumber;
    }
    else
    {
        printf("WRONG LIST CODE !!!\n");
        exit(0);
    }

    while(temp!=NULL)
    {
        // NewDigit shows at next node of stack.
        nextDigit=temp->next;
        // Free current node.
        free(temp);
        // Show in next node of stack.
        temp=nextDigit;
    }

    // Initialize head.
    if(listCode==1)
    {
        headOfFistNumber=NULL;
    }
    else if(listCode==2)
    {
        headOfSecondNumber=NULL;
    }
    else if(listCode==3)
    {
      headOfResultNumber=NULL;
    }
    else
    {
        printf("WRONG LIST CODE !!!\n");
        exit(0);
    }

}


void clearBuffer() // Clean input Buffer.
{
    char c;
    do{
        c = getchar();
    }while (c != '\n' && c != EOF && c != '\r' );
}

