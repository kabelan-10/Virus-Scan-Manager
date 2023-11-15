#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <conio.h>

class AntivirusScanner
{
public:
    std::vector<std::string> virusSignatures = {
        "89C3 B440 8A2E 2004 8A0E 2104 BA00 05CD 21E8 D500 BF50 04CD"};

    AntivirusScanner(const std::string &dirpath) : dirpath(dirpath) {}

    void scan()
    {
        std::ifstream fin("file_list.txt");
        std::string file_name;

        while (std::getline(fin, file_name))
        {
            int response = scanFile(file_name);

            if (response == 1)
            {
                std::cout << "---------------------------------------------------------\n";
                std::cout << "Caution! A Virus has been Detected in the following file:\n"
                          << file_name << "\n";
                std::cout << "Press Enter Key to Delete it or any other key to skip.";
                char ask = _getch();

                if (ask == 13)
                {
                    if (remove(file_name.c_str()) != 0)
                    {
                        std::cerr << "Error deleting the file: " << file_name << std::endl;
                    }
                    else
                    {
                        std::cout << "File deleted successfully.\n";
                    }
                }
            }
        }

        fin.close();

        std::cout << "---------------------------------------------------------\n";
        std::cout << "Scan Complete. Thank You for using our antivirus.\n";
    }

private:
    std::string dirpath;

    int scanFile(const std::string &file_name)
    {
        std::cout << "Scanning file: " << file_name << std::endl;
        std::ifstream file(file_name);

        if (!file)
        {
            std::cerr << "Error opening file: " << file_name << std::endl;
            return 0; // Unable to open the file
        }

        std::string line;

        while (std::getline(file, line))
        {
            for (const std::string &signature : virusSignatures)
            {
                if (line.find(signature) != std::string::npos)
                {
                    return 1;
                }
            }
        }

        return 0;
    }
};

int main()
{
    std::string dirpath;
    std::cout << "---------------------------------------------------------\n";
    std::cout << "Welcome to our Antivirus Scanner\n";
    std::cout << "Enter the directory you want to scan: ";
    std::cin >> dirpath;

    char comm[300];
    strcpy(comm, "dir /B /S ");
    strcat(comm, dirpath.c_str());
    strcat(comm, " > file_list.txt");

    if (system(comm) != 0)
    {
        std::cerr << "Error running 'dir' command" << std::endl;
        return 1;
    }

    AntivirusScanner scanner(dirpath);
    scanner.scan();

    return 0;
}