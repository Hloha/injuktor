README for Injector
This is a simple injector program that allows you to inject a DLL into a target process using the WinAPI functions.

Usage
To use this program, follow the steps below:

write in launch options -insecure

Compile the program using a C++ compiler.
Run the compiled program in a command prompt or terminal.
Enter the path to the DLL file you want to inject.

![image](https://user-images.githubusercontent.com/122258065/220181653-7fd22fdf-c8c1-422b-9389-f6783dd917ec.png)

Enter the PID of the target process.

![image](https://user-images.githubusercontent.com/122258065/220182292-814c5595-f2a1-457d-bd43-8a108027faea.png)
Wait for the injection to complete.
Functions
This program includes the following functions:

getDLLpath(char*)
This function prompts the user to enter the path to the DLL file they want to inject. It takes a char* parameter that is used to store the entered path.

getPID(int*)
This function prompts the user to enter the PID of the target process. It takes an int* parameter that is used to store the entered PID.

getProc(HANDLE*, DWORD)
This function opens a handle to the target process using the entered PID. It takes a HANDLE* parameter to store the handle and a DWORD parameter for the target process's PID. It returns -1 if the handle cannot be opened.

InjectDLL(DWORD, char*)
This function injects the specified DLL file into the target process. It takes a DWORD parameter for the target process's PID and a char* parameter for the DLL file's path. It returns -1 if any errors occur during the injection.

Dependencies
This program uses the following WinAPI functions:

OpenProcess
GetProcAddress
VirtualAllocEx
WriteProcessMemory
CreateRemoteThread
WaitForSingleObject
VirtualFreeEx
CloseHandle
Note
This program is for educational purposes only. Please use it responsibly and do not use it to harm others.
