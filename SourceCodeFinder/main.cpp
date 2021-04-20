//Don't Be a Jerk: The Open Source Software License.
//Last Update: March 19, 2015
//
//This software is free and open source.
//
//- *I* am the software author. *I* might be a *we*, but that's OK.
//- *You* are the user of this software. *You* might also be a *we*, and that's also OK!
//
//> This is free software.  I will never charge you to use, license, or obtain this software.  Doing so would make me a jerk.
//
//> I will never take down or start charging for what is available today.  Doing so would make me a jerk.
//
//> You may use this code (and by "code" I mean *anything* contained within in this project) for whatever you want.  Personal use, Educational use, Corporate use, Military use, and all other uses are OK!  Limiting how you can use something free would make me a jerk.
//
//> I offer no warranty on anything, ever.  I've tried to ensure that there are no gaping security holes where using this software might automatically send your credit card information to aliens or erase your entire hard drive, but it might happen.  I'm sorry.  However, I warned you, so you can't sue me.  Suing people over free software would make you a jerk.
//
//> If you find bugs, it would be nice if you let me know so I can fix them.  You don't have to, but not doing so would make you a jerk.
//
//> Speaking of bugs, I am not obligated to fix anything nor am I obligated to add a feature for you.  Feeling entitled about free software would make you a jerk.
//
//> If you add a new feature or fix a bug, it would be nice if you contributed it back to the project.  You don't have to, but not doing so would make you a jerk.   The repository/site you obtained this software from should contain a way for you to contact me.  Contributing to open source makes you awesome!
//
//> If you use this software, you don't have to give me any credit, but it would be nice.
//
//Don't be a jerk.
//Enjoy your free software!

/**
 * Program Title: SourceCodeFinder
 * file: main.cpp
 * author: The Aarnold
 * date: 13th August 2019
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
#include <iterator>
#include <exception>
#if defined(__unix__)
	#include <boost/filesystem.hpp> // Not using c++17 filesystem because of implementation problems on unix
	using namespace boost::filesystem;
#else
	#include <filesystem>
#endif


// Prototypes
void main_loop();
void index_src_files(path const&);
int line_count(path const&);
std::vector<std::string> format_input(std::string const&);
void execute(std::vector<std::string> const&);

// Globals
std::set<std::string> const ext = {".h", ".hpp", ".inl", ".c", ".cpp"};
std::vector<path> filesIndex;
bool running = true;

int main(int argc, char* argv[])
{
   std::vector<std::string> roots;
   std::string command;
   int totalLines = 0;

   if (argc > 1)
      for (int i = 1; i < argc; ++i)
         roots.push_back(argv[i]); // Root directory can be passed as program argument
   else // If no arguments, asking the user
   {
      std::cout << "Enter root directory : ";
      std::string line;
      std::getline(std::cin, line);
      for (auto& root : format_input(line))
         roots.push_back(root);
   }

   try
   {
      for (auto& root : roots)
         index_src_files(root); // Index every source files found in root dir and sub dirs
                                     // See "ext" global std::set for recognized file extensions

      for (path& var : filesIndex) // Compute total lines, not actually lines of code as it is the number of lines in every files
      {
         printf("%s\n", var.string().c_str());
         totalLines += line_count(var);
      }

      printf("Total files : %d \n", static_cast<int>(filesIndex.size())); // Print found source files
      printf("Total lines : %d \n\n", totalLines); // Print line count

      main_loop();
   }
   catch (filesystem_error const& e)
   {
      std::cout << e.what() << std::endl;
   }
   catch (std::exception const& e)
   {
      std::cout << e.what() << std::endl;
   }

	return 0;
}

void main_loop() // For command execution, type "quit" to stop the program
{
   std::string command;
   std::vector<std::string> argv;

   while (running)
   {
      printf("LP1> "); // CMD style ! (LP1 stands for LooseProject#1)
      std::getline(std::cin, command); // Get user input
      execute(format_input(command)); // Format the input and (try to) execute the parsed command
   }
}

void index_src_files(path const& root)
{
   std::vector<path> temp;
   std::queue<path> directories;

   if (!exists(root))
   {
      printf("%s does not exist !\n", root.c_str());
      return;
   }
   if (!is_directory(root))
   {
      printf("%s is not a directory !\n", root.c_str());
      return;
   }

   directories.push(root);

   while (directories.size())
   {
      path dir = directories.front();
      directories.pop();

      std::copy(directory_iterator(dir), directory_iterator(), std::back_inserter(temp));

      for (path& obj : temp)
      {
         if (is_directory(obj))
            directories.push(obj);
         else if (is_regular_file(obj) && ext.find(obj.extension().string()) != ext.end())
            filesIndex.push_back(obj);
      }

      temp.clear();
   }
}

int line_count(path const& filename)
{
   std::ifstream file;
   std::string line;
   int lineCount = 0;

   try
   {
      file.open(filename.string());
   }
   catch (std::ifstream::failure& e)
   {
      printf("Unable to read file at %s : %s\n", filename.c_str(), e.what());
      return 0;
   }

   while (std::getline(file, line))
      lineCount++;

   file.close();

   return lineCount;
}

// Count occurences of c in str
int occurences(std::string const& str, std::string const& c)
{
   int occurs = 0;
   size_t pos = str.find(c);
   size_t lastPos = 0;

   while (pos != std::string::npos)
   {
      lastPos = pos + 1;
      pos = str.find(c, lastPos);
      ++occurs;
   }

   return occurs;
}

std::vector<std::string> format_input(std::string const& str)
{
   // TODO Improve parsing performances (because it's probably messy)
   std::vector<std::string> args;
   std::string temp;
   size_t pos;
   size_t lastPos = 0;

   do
   {
      pos = str.find(" ", lastPos);
      temp = str.substr(lastPos, pos - lastPos);
      lastPos = pos + 1;
      if (temp.empty())
         continue;

      args.push_back(temp);
   } while (pos != std::string::npos); // Probably the first time in 4 years I'm using a do...while. Wow.

   return args;
}

void execute(std::vector<std::string> const& argv) // TODO More commands ?
{
   size_t argc = argv.size();
   if (argc < 1)
      return;

   if (argv[0] == "quit")
      running = false;
   if (argv[0] == "howmany") // TODO Only search in specific file(s)
   {
      if (argc < 2)
      {
         std::cout << "No char to count !\n";
         return;
      }

      std::ifstream file;
      std::string line;
      std::vector<int> totalOccurs(argc - 1, 0);

      for (path& filename : filesIndex)
      {
         try
         {
            file.open(filename.string());
         }
         catch (std::ifstream::failure& e)
         {
            printf("Unable to read file at %s : %s\n", filename.c_str(), e.what());
            continue;
         }

         while (std::getline(file, line))
            for (size_t i = 1; i < argc; ++i)
               totalOccurs[i - 1] += occurences(line, argv[i]);

         file.close();
      }

      for (size_t i = 1; i < argc; ++i)
         printf("%s occurs %d times\n", argv[i].c_str(), totalOccurs[i - 1]);
   }
}
