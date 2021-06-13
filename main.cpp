#include <iostream>
#include <string>
#include <ostream>
#include <fstream>
#include <sstream>
#include "bst.h"

using namespace std;

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        cerr << "Please provide name of input and output files";
        return 1;
    }
    cout << "Input file: " << argv[1] << endl;

    ifstream in(argv[1]);

    if (!in)
    {
        cerr << "Unable to open " << argv[1] << " for input";
        return 2;
    }
    cout << "Output file: " << argv[2] << endl;

    ofstream out(argv[2]);

    if (!out)
    {
        in.close();
        cerr << "Unable to open " << argv[2] << " for output";
        return 3;
    }

    BST<int> BstNum;
    BST<string> BstString;

    string line, command;
    string checker;
    string item;
    int itemVal;
    while (getline(in, line))
    {
        if (line.size() == 0) continue;
        istringstream iss(line);
        iss >> command;

        if (command == "INT")
        {
            checker = "INT";
            out << "INT true" << endl;
        }

        else if (command == "STRING")
        {
            checker = "STRING";
            out << "STRING true" << endl;
        }

        if (command == "add")
        {
            iss >> item;
            if (checker == "INT")
            {
                itemVal = stoi(item);
                if (BstNum.addNode(itemVal))
                {
                    out << "add " << item << " true" << endl;
                }

                else
                {
                    out << "add " << item << " false" << endl;
                }
            }

            else
            {
                if (BstString.addNode(item))
                {
                    out << "add " << item << " true" << endl;
                }
                else
                {
                    out << "add " << item << " false" << endl;
                }
            }


        }
        else if (command == "remove")
        {
            iss >> item;
            if (checker == "INT")
            {

                itemVal = stoi(item);

                if (BstNum.removeNode(itemVal))
                {
                    out << command << " " << item << " true" << endl;
                }

                else
                {
                    out << command << " " << item << " false" << endl;
                }
            }

            else
            {
                if (BstString.removeNode(item))
                {
                    out << command << " " << item << " true" << endl;
                }

                else
                {
                    out << command << " " << item << " false" << endl;
                }
            }

        }
        else if (command == "clear")
        {
            if (checker == "INT")
            {

                BstNum.clearTree();
                out << command << " true" << endl;
            }

            else
            {
                BstString.clearTree();
                out << command << " true" << endl;
            }

        }
        else if (command == "size")
        {

            if (checker == "INT")
            {


                out << "size " << BstNum.GetTreeSize() << endl;
            }

            else
            {
                out << "size " << BstString.GetTreeSize() << endl;
            }

        }
        else if (command == "print")
        {
            if (checker == "INT")
            {
                out << "print:";
                out << BstNum.toString() << endl;
            }

            else
            {
                out << "print:";
                out << BstString.toString() << endl;
            }


        }
        else if (command == "find")
        {
            iss >> item;
            if (checker == "INT")
            {

                itemVal = stoi(item);
                if (BstNum.FinderFunc(itemVal))
                {
                    out << command << " " << itemVal << " found" << endl;
                }

                else
                {
                    out << command << " " << itemVal << " not found" << endl;
                }
            }

            else
            {
                if (BstString.FinderFunc(item))
                {
                    out << command << " " << item << " found" << endl;
                }

                else
                {
                    out << command << " " << item << " not found" << endl;
                }
            }

        }
        else if (command == "tree")
        {

        }


    }



    return 0;
}
