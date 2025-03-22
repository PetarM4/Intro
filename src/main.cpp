/**************************************************************
* Programmer Name: Petar Minic
* File Name: Project Pt 2
* Date of Last Modification: 3/21/2025
* I have everything good for the most part... except the drawing part :(
* I basically made two different coord lists instead of one so that there
* was an "original shape" and a "modified shape". However, I cannot seem 
* to print either shape correctly when using subdivide. Something ends up
* there (in red), just not the correct shape.
*
**************************************************************/


#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "List.h"
using namespace std;

void display() {
    cout << "     M   E   N   U     " << endl;
    cout << "-----------------------" << endl;
    cout << "1. Split" << endl;
    cout << "2. Average" << endl;
    cout << "3. Subdivide" << endl;
    cout << "4. Draw" << endl;
    cout << "5. View coordinates" << endl;
    cout << "6. Save coordinates" << endl;
    cout << "7. Exit" << endl;
    cout << "Choose an option: " << endl;
    cout << "-----------------------";
}

int main() {
    string filename = "C:/Users/pm570618/Source/Repos/PetarM4/Intro/PointsTest.txt";
    LinkedList list;
    list.readFromFile(filename); 

    LinkedList modifiedList = *list.copy();

    int userChoice;
    bool splitPerformed = false;

    std::vector<sf::Vertex> originalVertices;
    std::vector<sf::Vertex> modifiedVertices;

    Node* temp = list.head;
    while (temp != nullptr) {
        originalVertices.push_back(sf::Vertex{ {static_cast<float>(temp->x), static_cast<float>(temp->y)}, sf::Color::Blue });
        temp = temp->next;
    }

    while(true){

    display();

    cin >> userChoice;


        if (userChoice == 1) {          //Split

            if (!splitPerformed) {
                modifiedList.split();
                splitPerformed = true;
                cout << "Split performed!" << endl;
            }
            else {
                cout << "Split already performed. Maybe try average or subdivide?" << endl;
            }

        }
        else if (userChoice == 2) {     //Average

            if (splitPerformed) {
                modifiedList.average();
                splitPerformed = false; // Reset after averaging
                cout << "Average performed!" << endl;
            }
            else {
                cout << "Please perform split before averaging." << endl;
            }

        }
        else if (userChoice == 3) {     //Subdivide

            modifiedList.subdivide();
            splitPerformed = false;
            cout << "Subdivide performed." << endl;

        }
        else if (userChoice == 4) {     //Draw Coordinates
            modifiedVertices.clear();

            temp = modifiedList.head;
            while (temp != nullptr) {
                modifiedVertices.push_back(sf::Vertex{ {static_cast<float>(temp->x), static_cast<float>(temp->y)}, sf::Color::Red });
                temp = temp->next;
            }
            while (temp != nullptr) {
                originalVertices.push_back(sf::Vertex{ {static_cast<float>(temp->x), static_cast<float>(temp->y)}, sf::Color::Blue });
                temp = temp->next;
            }

            auto window = sf::RenderWindow(sf::VideoMode({ 1000,1000}), "My Window");
            window.setFramerateLimit(144);

            while (window.isOpen())
            {
                while (const std::optional event = window.pollEvent())
                {
                    if (event->is<sf::Event::Closed>())
                    {
                        window.close();
                    }
                }

                window.clear();

                window.draw(originalVertices.data(), originalVertices.size(), sf::PrimitiveType::LineStrip);

                window.draw(modifiedVertices.data(), modifiedVertices.size(), sf::PrimitiveType::LineStrip);


                window.display();
            }
        }
        else if (userChoice == 5) {     //View Coordinates
            
            cout << "Original Coordinates" << endl;
            list.display();
            cout << "Modified Coordinates" << endl;
            modifiedList.display();

        }
        else if (userChoice == 6) {     //Save Coordinates

            modifiedList.saveToFile("C:/Users/pm570618/Source/Repos/PetarM4/Intro/PointsTest.txt");
            cout << "Coordinates saved!" << endl;

        }
        else if (userChoice == 7) {     //Quit
            cout << "Quitting..." << endl;
            return 0;
        }
        else {                          //If the input is not a number from 1 to 7
            cout << "You chose an inorrect option. Please try again." << endl;
        }

        cout << endl;
    }
}