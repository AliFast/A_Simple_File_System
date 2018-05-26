#include<iostream>
#include<fstream>
#include<stdio.h>
#include<string.h>
#include<string>
#define NUM_BLOCK 100
#define BLOCK_SIZE 50
#define RELIABILITY 0.95
#define PERIOD 2147483647.0
#define ERROR -1
#define NO_ERROR 0
#define ROOT 0

//check fwrite . complete fread 

using namespace std;


static int threshold;
static char *bList[NUM_BLOCK];
int currDirectory;
int index;
int openFiles[NUM_BLOCK];
int openFilesIndex = 0;
bool fileOrFolderFlag;
char HD[NUM_BLOCK*BLOCK_SIZE];
char freeBNUMLeast;
char freeBNUM;
int freeBNUMint;
char currDirectoryLeast;
char currDirectorySL;

void initDisk();//DONE
int dRead(); //DONE
int dWrite(int addr, char *buf);

int fOpen(char*name);//DONE
int fClose(int fileID);//DONE
int fRead(int fileID, char* buffer, int length);//DONE
int fSeek(int fileID, int position);//DONE
int fMkdir(char* name);//DONE
int fCd(char* name);//DONE
int fWrite(int fileID, char* buffer, int length);//DONE
int fLs(char* name);//DONE
int fols(char* name);//DONE
int findSpace();//DONE
int isfOpen(int fileID);//DONE


int main() {
	currDirectory = ROOT;
	index = ROOT;
	fileOrFolderFlag = false; //set the flag when changing directory
	freeBNUMLeast = '1';
	freeBNUM = '0';
	freeBNUMint = 1;
	currDirectoryLeast = '0';
	currDirectorySL = '0';
	char* input = new char[10];
	initDisk();
	while (true) {
		cout << "Enter cd to change Directory" << endl;
		cout << "Enter mk to Make Directory" << endl;
		cout << "Enter fo to Open file" << endl;
		cout << "Enter fr to read file" << endl;
		cout << "Enter fw to write in file" << endl;
		cout << "Enter fc to close file" << endl;
		cout << "Enter fs to change offset of file" << endl;
		cout << "Enter s to to save Disk Changes" << endl;
		cout << "Enter v to View Current Directory" << endl;
		cout << "Enter e to EXIT" << endl;
		cin.getline(input, 10);
		int fid = 0;
		if (input[0] == 'c' && input[1]=='d') {
			cout << "Enter name of Directory You want to Change too.It must be two characters\n";
			cin >> input;
			int flag=fCd(input);
			if (flag == ERROR) {
				cout << "cannot change directory. Either directory does not exist or enter valid director" << endl;
			}
			else {
				cout << "directory changed" << endl;
			}

		}
		else if (input[0] == 'm' && input[1]=='k') {
			cout << "Enter name of Directory You want to Make too.It must be two characters\n";
			cin.getline(input, 10);
			int flag = fMkdir(input);
			if (flag == ERROR) {
				cout << "cannot make directory. Either directory already exist or enter valid directory name" << endl;
			}
			else cout << "Folder made" << endl;
		}
		else if(input[0] == 'f' && input[1]=='o'){
			cout << "Enter name of File You want to Open.It must be two characters\n";
			cin >> input;
			int fid = fOpen(input);
			if (fid == ERROR) {
				cout << "cannot open file. Either file is already open or enter valid file name" << endl;
			}
			else {
				cout << "File ID : " << fid << endl;
			}
		}
		else if (input[0] == 'f' && input[1]=='r') {
			int f = 0;
			cout << "Enter File ID : ";
			cin >> f;
			int flag1 = isfOpen(f);
			if(flag1 == NO_ERROR) {
				cout << "Enter No. of characters you want to read" << endl;
				int n;
				cin >> n;
				if (n > 0) {
					char* w = new char[n];
					
					int flag = fRead(f, w, n);
					if (flag == ERROR) {
						cout << "cannot read. Either file is already closed or enter valid file input" << endl;
					}else
						cout << w << endl;
				}
				else cout << "Enter a positive no." << endl;
			}
			else {
				cout << "Enter Valid File ID" << endl;
			}
		}
		else if (input[0] == 'f' && input[1]=='w') {
			int f = 0;
			cout << "Enter File ID : ";
			cin >> f;
			int flag1 = isfOpen(f);
			if (flag1 == NO_ERROR) {
				cout << "Enter what you want to write" << endl;
				cin.ignore();
				char* w = new char [400];
				cin.getline(w, 400);
				int flag = fWrite(f, w, strlen(w)+1);
				if (flag == ERROR) {
					cout << "cannot write to file. Either file is already closed or enter valid file input" << endl;
				}
				cout << w << endl;
			}
			else {
				cout << "Enter Valid File ID" << endl;
			}

		}
		else if (input[0] == 'f' && input[1]=='c') {
			int f = 0;
			cout << "Enter File ID : ";
			cin >> f;
			int flag1 = isfOpen(f);
			if (flag1 == NO_ERROR) {
				fClose(f);
			}
			else {
				cout << "Enter Valid File ID" << endl;
			}

		}
		else if (input[0] == 'f' && input[1] == 's') {
			int f = 0;
			cout << "Enter File ID : ";
			cin >> f;
			int flag1 = isfOpen(f);
			if (flag1 == NO_ERROR) {
				cout << "Enter position" << endl;
				int n = 0;
				cin >> n;
				if (n > 0) {
					fSeek(f, n);
				}
				else {
					cout << "Enter Positive No." << endl;
				}
			}
			else {
				cout << "Enter Valid File ID" << endl;
			}

		}
		else if (input[0] == 'e') {

					ofstream file("t1.txt");
					if (file.fail()) {
						cout << "HD IS CORRUPT\n";
						return 0;
					}

					int i = 0;
					for (int m = 0; m < NUM_BLOCK; m++) {
						for (int n = 0; n < BLOCK_SIZE; n++)
						{
							file << HD[i++];

						}
						file << endl;
					}
					file.close();

				


				return 0;

		}
		else if (input[0] == 's') {
			ofstream file("t1.txt");
			if (file.fail()) {
				cout << "HD IS CORRUPT\n";
				return 0;
			}

			int i = 0;
			for (int m = 0; m < NUM_BLOCK; m++) {
				for (int n = 0; n < BLOCK_SIZE; n++)
				{
					file << HD[i++];

				}
				file << endl;
			}
			file.close();

		}
		else if (input[0] == 'v') {
			dRead();
		}
	}

	
	

	
	return 0;
}


int isfOpen(int fileID) {

	for (int i = 0; i < openFilesIndex; i++) {
		if (openFiles[i] == fileID) {
			
			return NO_ERROR;
		}
	}

	return ERROR;
}

int fLs(char* name) {
	

	
	index = currDirectory * 50;
	int index_new = currDirectory * 50;
	int currDirectory_new = 0;

	for (int j = 0; j < 46; j++) {
		if (HD[index] == name[0] && HD[index + 1] == name[1] && HD[index + 2] == 'F' && HD[index + 3] == 'I' && HD[index + 4] == 'L') {

		
			return NO_ERROR;
			
		}
		else {
			if (j == 43) {
				char position[3];
				
				position[1] = HD[index_new + 49];
				position[0] = HD[index_new + 48];
				position[2] = '\0';
				sscanf_s(position, "%d", &currDirectory_new);
				
				if (currDirectory_new > 0) {
					index = currDirectory_new * 50;					
					index_new = currDirectory_new * 50;
					j = 0;
				}
				else {
					return ERROR;
				}
			}
			else {
				index++;
			}
		}

	}



}

int fols(char* name) {

	index = currDirectory * 50;
	int index_new = currDirectory * 50;
	int currDirectory_new = 0;
	for (int j = 0; j < 44; j++) {
		if (HD[index] == name[0] && HD[index + 1] == name[1] && HD[index + 2] == 'F' && HD[index + 3] == 'O' && HD[index + 4] == 'L') {


			return NO_ERROR;

		}
		else {
			if (j == 43) {
				
				char position[3];
				
				position[1] = HD[index_new + 49];
				position[0] = HD[index_new + 48];
				position[2] = '\0';
				sscanf_s(position, "%d", &currDirectory_new);

				if (currDirectory_new > 0) {
					index = currDirectory_new * 50;
					j = 0;
					index_new = currDirectory_new * 50;
				}
				else {
					return ERROR;
				}
			}
			else {
				index++;
			}
		}

	}

}


int fWrite(int fileID, char* buffer, int length) {

	if (fileID > 0 && length > 0 && buffer!=NULL) {
		
		int flag = isfOpen(fileID);
		if (flag == NO_ERROR) {
			index = fileID * 50;
			int n = 0;
			char position[3];
			position[0] = HD[index + 1];//checking offset
			position[1] = HD[index];
			position[2] = '\0';

			char fileSize[3];
			fileSize[0] = HD[index + 3];
			fileSize[1] = HD[index + 2];//checking size
			fileSize[2] = '\0';
			int index_new = fileID * 50;
			int currDirectory_new = 0;

			int integ = 0;
			sscanf_s(position, "%d", &integ);
			int fSize = 0;
			sscanf_s(fileSize, "%d", &fSize);
			int k = 0;

			if (integ > 0) {
				index = index + integ;
			}
			else {
				index = index + 4;// file position pointer  2 byte 
			}

			for (; n < length &&  buffer[n] != '\0'; n++) {

				if (fSize == 43) {
					
					char position[3];

					position[1] = HD[index_new + 49];
					position[0] = HD[index_new + 48];
					position[2] = '\0';
					sscanf_s(position, "%d", &currDirectory_new);

					if (currDirectory_new == 0) {
						HD[index_new + 48] = freeBNUM;
						HD[index_new + 49] = freeBNUMLeast;

						freeBNUMLeast++;

						freeBNUMint++;

						if (freeBNUMLeast == '9') {
							freeBNUMLeast = '0';
							freeBNUM++;
						}
					}
					


						position[1] = HD[index_new + 49];
						position[0] = HD[index_new + 48];
						position[2] = '\0';

						sscanf_s(position, "%d", &currDirectory_new);
						index_new = currDirectory_new * 50;
						index = index_new;
						fSize = 0;
					
				}
				else {
					if (buffer[n] !=  ' ') {
						HD[index++] = buffer[n];
						fSize++;
					}
					else {
						HD[index++] = '0';
						fSize++;
					}
				}
			}

			return n;
		}
	}
	else {
		return ERROR;
	}

}

int fOpen(char*name) {

	if (name != NULL && strlen(name) == 2) {
		
		int flag = fLs(name);
		
		
		if (flag == NO_ERROR) {
			char num[3];
			num[1] = HD[index - 1];
			num[0] = HD[index - 2];
			num[2] = '\0';
			int integ = 0;
			sscanf_s(num, "%d", &integ);
			for (int n = 0; n < openFilesIndex; n++) {
				if (openFiles[n] = integ) {
					cout << "File is already open" << endl;
					return ERROR;
				}
				
			}
			cout << "file found and fileID is returned" << endl;
			openFiles[openFilesIndex++] = integ;
			return integ;
		}
		else {
			
			int flag1=findSpace();
			

				if (flag1==NO_ERROR) {
					
					index = index - 7;
						HD[index++] = freeBNUM;
						HD[index++] = freeBNUMLeast;

						freeBNUMLeast++;
						

						freeBNUMint++;
						if (freeBNUMLeast == '9') {
							freeBNUMLeast = '0';
							freeBNUM++;
						}



						HD[index++] = name[0];
						HD[index++] = name[1]; 
						HD[index++] = 'F';
						HD[index++] = 'I';
						HD[index++] = 'L';
						
					}
				cout << "File not found but created new File in the Current Directory and fileID is returned" << endl;
				openFiles[openFilesIndex++]= freeBNUMint - 1;

				return freeBNUMint - 1;
			
		}

	}
	else {
		cout << "Enter a Valid File Name" << endl;
	}
	
}

int fClose(int fileID) {
	if (fileID > 0) {
		for (int i = 0; i < openFilesIndex; i++) {
			if (openFiles[i] == fileID) {
				openFiles[i] = 0;
				cout << "file closed" << endl;
				return NO_ERROR;
			}
		}
		cout << "File was not open" << endl;
		return ERROR;
	}
	else {
		cout << "Invalid File ID" << endl;
		return ERROR;
	}

}

int fRead(int fileID, char* buffer, int length) {
	if (fileID > 0 && length > 0) {
		int flag = isfOpen(fileID);
		if (flag == NO_ERROR)
		{
			index = fileID * 50;
			int n = 0;
			char position[3];
			position[0] = HD[index + 1];
			position[1] = HD[index];
			position[2] = '\0';
			int index_new = fileID * 50;
			int integ = 0;
			sscanf_s(position, "%d", &integ);
			int k = 0;

			if (integ > 0) {
				index = index + integ;

			}
			else {
				index = index + 4;//4 spaces for file parent and file position pointer each 2 byte 
			}
			int fSize = 0;
			for (; n < length ; n++) {
				if(fSize == 43){
				
					
					int currDirectory_new = 0;
					
					char position[3];

					position[1] = HD[index_new + 49];
					position[0] = HD[index_new + 48];
					position[2] = '\0';
					sscanf_s(position, "%d", &currDirectory_new);
					if (currDirectory_new == 0) {
						break;
					}
					else {
						index = currDirectory_new * 50;
						index_new = currDirectory_new * 50;
						fSize = 0;
					}

				}
				if (HD[index] == '0' && HD[index + 1] == '0' && HD[index + 2] == '0') break;
				if (HD[index] != '0') {
					buffer[n] = HD[index++];
					fSize++;
				}
				else {
					buffer[n] = ' ';
					fSize++;
				}
			}

			buffer[n] = '\0';
			return n;
		}
		else
			return ERROR;

	}
	else {
		return ERROR;
	}

}


int fSeek(int fileID, int position) {

	if (fileID > 0 && position) {
		int flag = isfOpen(fileID);
		if (flag == NO_ERROR) {
			index = fileID * 50;
			char ks[4];
			sprintf_s(ks, "%d", position);
			if(strlen(ks) == 1)
				HD[index] = '0';
			else
				HD[index] = ks[1];
			HD[index + 1] = ks[0];
			return 0;
		}
		else
			return ERROR;
	}
	else {
		return -1;
	}

}


int findSpace() {

	int counter = 0;
	index = currDirectory * 50;
	int i;

	while(true) 
	{
		for (i = 0; i < 43; i++) {
			if (counter == 7) {
				return NO_ERROR;
			}
			else {

				if (HD[index++] == '0')
					++counter;
				else
					counter = 0;
			}
		}



		if (i == 43) {

			int index_new = currDirectory * 50;
			char position[3];
			int currDirectory_new = 0;
			position[1] = HD[index_new + 49];
			position[0] = HD[index_new + 48];
			position[2] = '\0';
			sscanf_s(position, "%d", &currDirectory_new);

			if (currDirectory_new > 0) {
				if (index == 4994) {
					cout << "Disk Out of Space. Buy a new one" << endl;
					return ERROR;
				}
				index = currDirectory_new * 50;
				i = 0;
			}
			else {
				int index_new = currDirectory * 50;
				int currDirectory_new = 0;
				HD[index_new + 48] = freeBNUM;
				HD[index_new + 49] = freeBNUMLeast;

				freeBNUMLeast++;
				HD[freeBNUMint * 50] = currDirectorySL;
				HD[freeBNUMint * 50 + 1] = currDirectoryLeast;


				freeBNUMint++;

				if (freeBNUMLeast == '9') {
					freeBNUMLeast = '0';
					freeBNUM++;
				}

				if (currDirectoryLeast == '9') {
					currDirectoryLeast = '0';
					currDirectorySL++;
				}

				char position[3];
				
				position[1] = HD[index_new + 49];
				position[0] = HD[index_new + 48];
				position[2] = '\0';
				sscanf_s(position, "%d", &currDirectory_new);
				index = currDirectory_new * 50;

			}
		}
	}
}

int fMkdir(char* name) {
	
	
		int flag = fols(name);


		if(flag == ERROR)
		{
			if (name != NULL && strlen(name) == 2) 
			{
				int flag1 = findSpace();


				index = index - 7;
				HD[index++] = freeBNUM;
				HD[index++] = freeBNUMLeast;

				freeBNUMLeast++;
				HD[freeBNUMint * 50] = currDirectorySL;
				HD[freeBNUMint * 50 + 1] = currDirectoryLeast;


				freeBNUMint++;

				if (freeBNUMLeast == '9') {
					freeBNUMLeast = '0';
					freeBNUM++;
				}

				if (currDirectoryLeast == '9') {
					currDirectoryLeast = '0';
					currDirectorySL++;
				}

				HD[index++] = name[0];
				HD[index++] = name[1]; ;
				HD[index++] = 'F';
				HD[index++] = 'O';
				HD[index++] = 'L';
				return NO_ERROR;
			}
			else
			{
				cout << "FOLDER ALREADY EXISTS with this name in CURRENT DIRECTORY" << endl;
				return ERROR;
			}
		}
		else{
			cout << "FOLDER ALREADY EXISTS with this name in CURRENT DIRECTORY" << endl;
			return ERROR;
		}

	}
	

		
	


	int fCd(char* name) {

		if(name != NULL && strlen(name) == 2)
		{

			if (name == "pa") {
				index = currDirectory * 50;
				char position[3];
				position[0] = HD[index + 1];
				position[1] = HD[index];
				position[2] = '\0';

				int integ = 0;
				sscanf_s(position, "%d", &integ);

				currDirectory = integ;

				return 0;
			}

			bool flag = false;

			int flag1 = fols(name);


			char position[3];
			position[0] = HD[index - 2];
			position[1] = HD[index - 1];
			position[2] = '\0';

			int integ = 0;
			sscanf_s(position, "%d", &integ);

			currDirectory = integ;
			return NO_ERROR;


		}
		else {
			return ERROR;
		}
	}
	
	




void initDisk() {
	
	ifstream myFile("t1.txt");
	if (myFile.fail()) {
		cout << "HD IS CORRUPT\n";
		exit(1);

	}
	int i = 0;
	while (i != NUM_BLOCK*BLOCK_SIZE)
	{
		myFile >> HD[i++];
	}

	myFile.close();

	//threshold = (int)(RELIABILITY*PERIOD);
	//Sleep(3);
}

int dRead() {

	int index_d = currDirectory * 50;
	
	for (int l = 0; l < 44; l++) {
		if (l == 43) {
			int index_s = currDirectory * 50;
			int currDirectory_new = 0;
			char position[3];

			position[1] = HD[index_s + 49];
			position[0] = HD[index_s + 48];
			position[2] = '\0';
			sscanf_s(position, "%d", &currDirectory_new);
			if (currDirectory_new > 0) {
				index_d = currDirectory_new * 50;
				
			}
			else
				break;
		}
		else {
			if (HD[index_d] == '0' && HD[index_d + 1] == '0' && HD[index_d + 2] == '0') {
				break;
			}
			else {
				index_d = index_d + 2;
				cout << HD[index_d]; ++index_d; cout << HD[index_d]; //++index_d;
				if (HD[index_d+1] == 'F' && HD[index_d+2] == 'O' && HD[index_d+3] == 'L') {
					cout << "  Folder" << endl;
					index_d = index_d + 3;
				}
				else if (HD[index_d+1] == 'F' && HD[index_d+2] == 'I' && HD[index_d+3] == 'L') {
					cout << "  FILE " << endl;
					index_d = index_d + 3;
				}
			}
		}
	}

	return NO_ERROR;
}

int dWrite(int addr, char *buf) {

	int i;
	char* bufPtr;
	if (addr >= NUM_BLOCK)return ERROR;
	if (rand() > threshold)return ERROR;
	if (bList[addr] == NULL) {
		bList[addr] = (char*)malloc(BLOCK_SIZE);
	}
	bufPtr = bList[addr];
	for (i = 0; i < BLOCK_SIZE; i++) {
		*bufPtr++ = buf[i];

	}

	return NO_ERROR;
}
