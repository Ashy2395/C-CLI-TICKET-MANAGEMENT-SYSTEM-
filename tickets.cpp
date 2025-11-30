#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <limits>


struct ticket
{
    int id;
    std::string summary;
    std::string status;
    std::string assignee;
};

class TicketingSystem
{
    private:
    std::vector<ticket> tickets;
    std::string filename = "tickets.csv";
    int next_id = 1;

    public:
    TicketingSystem()
    {
        load_tickets();
    }

    private:

    void load_tickets()
    {
        std::ifstream in (filename);
        if(!in) return;

        std::string line;

        while(std::getline(in,line))
        {
            if(line.empty()) continue;
            std::stringstream ss (line);

            ticket t;
            
            std::string file;
            if(!std::getline(ss, file, ',')) continue;
            t.id = std::stoi(file);

            std::getline(ss, t.summary, ',');

            std::getline(ss, t.status, ',');
            
            std::getline(ss, t.assignee);

            tickets.push_back(t);

            if(t.id>=next_id)
            {
                next_id= t.id+1;
            } 
        }
    }

    public:

    void show_menu()
    {
        std::cout << "\n=== Ticketing System ===\n";
        std::cout << "1. List all\n  2. Add ticket\n  3. Update status\n  4. Search by assignee\n  5. Save & Quit\n  Choice: ";
    }

    void list_all()
    {
        if (tickets.empty()) { std::cout << "No tickets\n"; return; }
        std::cout << "\nID | Summary               | Status       | Assignee\n";
        std::cout << "-----------------------------------------------------\n";
        for (const auto &t: tickets)
        {
            std::cout<< std::right << std::setw(3)<<t.id << "|" 
                     << std::left << std::setw(22) << t.summary.substr(0,20) << "|"
                     << std::setw(12) <<t.status <<"|"
                     << t.assignee<<"\n";
        }
    }

    void add_ticket() 
    { 
        ticket t;
        t.id = next_id++;
        std::cout<<"summary";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, t.summary);
        if(t.summary.empty()) t.summary ="no summary\n";
        std::cout<<"assignee";
        std::getline(std::cin, t.assignee);
        if(t.assignee.empty()) t.assignee ="Unassigned";
        t.status = "open";
        tickets.push_back(t);
        std::cout<<"created ticket #" << t.id << "\n";
    }

    void update_status() {
        std::cout << "Ticket ID: ";
        int id; if (!(std::cin >> id)) { std::cin.clear(); std::cin.ignore(10000,'\n'); std::cout << "Invalid id\n"; return; }
        auto it = find_ticket(id);
        if (it == tickets.end()) { std::cout << "Ticket not found\n"; return; }
        std::cout << "Current: " << it->status << "\n";
        std::cout << "New status (Open/In Progress/Closed): ";
        std::cin.ignore(10000,'\n');
        std::string s; std::getline(std::cin, s);
        if (!s.empty()) it->status = s;
        std::cout << "Updated.\n";
    }

    void search_assignee() {
        std::cout << "Assignee name: ";
        std::cin.ignore(10000,'\n');
        std::string name; std::getline(std::cin, name);
        bool found = false;
        for (const auto &t : tickets) {
            if (!name.empty() && t.assignee.find(name) != std::string::npos) {
                std::cout << t.id << ": " << t.summary << " [" << t.status << "]\n";
                found = true;
            }
        }
        if (!found) std::cout << "No tickets found for '" << name << "'\n";
    }

    std::vector<ticket>::iterator find_ticket(int id) {
        return std::find_if(tickets.begin(), tickets.end(),
                            [id](const ticket &t){ return t.id == id; });
    }

    
    void save_tickets()
    {
        std::ofstream out ("tickets.csv");
        if (!out) {std::cout<< "Cannot open file to save\n";return;}

        for (const auto &t: tickets)
        {
            out << t.id << " , " << t.summary << " , " << t.status << " , " << t.assignee <<"\n";
        }

        std::cout << "Saved " << tickets.size() << " tickets";
    }
};

int main()
{

    TicketingSystem system;
    int choice = 0;
    while (true)
    {
        system.show_menu();
        if(!(std::cin>>choice))
        {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout<<"Please enter a number";
            continue;
        }
        if (choice == 5) {system.save_tickets(); break;}
        else if (choice == 1) system.list_all();
        else if (choice == 2) system.add_ticket();
        else if (choice == 3) system.update_status();
        else if (choice == 4) system.search_assignee();
        else std::cout<<"Invalid Choice\n";
    }
    return 0;
}
