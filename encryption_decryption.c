#include "stdio.h"
#include <string.h>
#include <ctype.h> 
#include <conio.h> 
#include <stdlib.h>

int ori_pin =  910320;

int choose();

int get_pin(){
	int ch;
	
	printf("Please enter 6-bit PIN!\n");
	scanf("%d",&ch);
	fflush(stdin);
//	printf("the input pin you gave is %d\n",ch);
	
	return ch;
}

int menu(){
	printf("---------------------------Welcome!---------------------------\n");
	printf("\n");
	printf("------------encryption or decryption files------------\n");
	printf("*                                                    *\n");
	printf("*      -----------------------------------           *\n");
	printf("*               programmed by Bobbi                  *\n");
	printf("*      -----------------------------------           *\n");
	printf("\n");
	printf("\n");
	printf("please choose what you want to do from the menu!\n");
	printf("1. encrytion\n");
	printf("2. decryption\n");
	printf("3. chance the pin\n");
	printf("4. log out\n");

	return 0;
}

int redo(){
	char action;

	printf("You have finished what you want to do\n");
	printf("What do you want to do next?\n");
	printf("a: back to menu;\n");
	printf("b: quit the program.\n");

	while(1){
		scanf("%c",&action);

		if((action != 'a') && (action != 'b')){
			printf("There isn't this choice!Please do it again!\n");
		}else if(action == 'b'){
			menu();
			choose();
			break;
		}else if(action == 'a'){
			return EXIT_SUCCESS;
		}
	}
}

int encrypFile(char *path, char *secret_key, char *new_path){
	FILE *fppath, *fptarget;
	char buffer[30];
	int readCount, keyLen = strlen(secret_key), i;

	fppath = fopen(path, "rb");
	if(fppath == NULL){
		printf("Failed to open the file, please check the path and name of the file!\n");
		return 0;
	}

	fptarget = fopen(new_path,"wb");
	if(fptarget == NULL){
		printf("Failed to write the file, please check the path and name of the file!\n");
		return 0;
	}

	while((readCount = fread(buffer, 1, keyLen, fppath)) > 0 ){
		for(i = 0; i < readCount; i++){
			buffer[i] ^= secret_key[i];
		}
		fwrite(buffer, 1, readCount,fptarget );
	}

	fclose(fppath);
	fclose(fptarget);
}

int encryp(){
	char path[30];
	char secret_key[30];
	char new_path[30];

	printf("you choose to encryped the file.\n ");

	printf("Please enter the path of your file that you want to encryped.\n");
	scanf("%s",path);
	printf("your file path is %s\n",path);

	printf("Please enter your secret key: \n");
	scanf("%s",secret_key);
	printf("Your secret key is %s\n",secret_key);

	printf("Please enter the path you want to store your new file: \n");
	scanf("%s",new_path);
	printf("the path you want to store your new file is %s\n",new_path);
	
	if(encrypFile(path,secret_key,new_path)){
		printf("Encryped the file successfully!\n ");
	}else{
		printf("Failed encryped file!\n");
	}

	if(redo() == 'a'){ 
		printf("choose A!\n");
	}
	return 0;
}

int decryp(){
	char path[30];
	char secret_key[30];
	char new_path[30];

	printf("you choose to decryped the file.\n ");

	printf("Please enter the path of your file that you want to decryped.\n");
	scanf("%s",path);
	printf("your file path is %s\n",path);

	printf("Please enter your secret key: \n");
	scanf("%s",secret_key);
	printf("Your secret key is %s\n",secret_key);

	printf("Please enter the path you want to store your new file: \n");
	scanf("%s",new_path);
	printf("the path you want to store your new file is %s\n",new_path);

	if(encrypFile(path,secret_key,new_path)){
		printf("Encryped the file successfully!\n ");
	}else{
		printf("Failed encryped file!\n");
	}

	if(redo() == 'a'){ 
		printf("choose A!\n");
	}
	
	return 0;
}
int change_pin(){
	int new_pin_1,new_pin_2;

	printf("please enter your new pin:\n");
	scanf("%d",&new_pin_1);
	printf("Please enter your new pin again: \n");
	scanf("%d",&new_pin_2);

		if(new_pin_1 == new_pin_2){
			printf("You have successfully changed your pin!\n");
			ori_pin = new_pin_1;
		}
		else{
			printf("Not same!\n");
		}

	redo();
	return 0;
}

int change(){
	int pin;
	printf("you choose to change the pin.\n ");
	printf("Please enter your old pin.\n ");
	
	int in_times;
	in_times = 0;

	while(in_times <= 3){
		scanf("%d",&pin);
		if(pin == ori_pin){
			printf("your pin is right!\n");
			change_pin();
			break;
		}else {
			printf("Wrong number!\n");
			in_times++;
			printf("input time is %d, you can still enter %d times\n",in_times, 3-in_times);
			if(in_times == 3){
				printf("you have no chance!\n");
				break;
			}
		}
	}
	getchar();
	
	return 0;
}

int quit(){
	printf("you choose to log out.\n ");
	printf("Thank you for your use!\n ");
	printf("Good bye\n ");
	getchar();
	return EXIT_SUCCESS;
}

int choose(){
	int choose;
	fflush(stdin);
	scanf("%d", &choose);
	printf("your choice is %d\n",choose);

	switch(choose){
		case 1 :  encryp(); break;
        case 2 :  decryp(); break;
        case 3 :  change(); break;
        case 4 :  quit();   break;
        default: printf("error!\n");
	}
	return 0;
}

int main(){

	int in_times;
	in_times = 0;
	int input_pin;

	while(in_times <= 3){
		input_pin = get_pin();

		if(input_pin == ori_pin){
			printf("your pin is right!\n");
			menu();
			choose();
			break;
		}else {
			printf("Wrong number!\n");
			in_times++;
			printf("input time is %d, you can still enter %d times\n",in_times, 3-in_times);
			if(in_times == 3){
				printf("you have no chance!\n");
				break;
			}
		}
	}
	getchar();
	return 0;
}
