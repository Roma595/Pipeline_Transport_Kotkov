#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "Utilities.h"
#include "Data.h"
#include "Search.h"
#include "Graph.h"

void printMainMenu() {
    std::cout << "1. Add Pipe" << std::endl;
    std::cout << "2. Add CS" << std::endl;
    std::cout << "3. View all objects" << std::endl;
    std::cout << "4. Search pipe" << std::endl;
    std::cout << "5. Search station" << std::endl;
    std::cout << "6. Graph" << std::endl;
    std::cout << "7. Save" << std::endl;
    std::cout << "8. Load" << std::endl;
    std::cout << "0. Exit" << std::endl;
}
void printSearchPipesMenu() {
    std::cout << "1. Print Pipes" << std::endl;
    std::cout << "2. Delete Pipes" << std::endl;
    std::cout << "3. Edit Pipes" << std::endl;
    std::cout << "0. Cancel" << std::endl;
}
void printSearchStationsMenu() {
    std::cout << "1. Print Stations" << std::endl;
    std::cout << "2. Delete Stations" << std::endl;
    std::cout << "3. Edit Stations" << std::endl;
    std::cout << "0. Cancel" << std::endl;
}
void printSearchPipe() {
    std::cout << "1. Search by name" << std::endl;
    std::cout << "2. Search by status" << std::endl;
    std::cout << "3. Search by ID" << std::endl;
    std::cout << "0. Cancel" << std::endl;
}
void printSearchStation() {
    std::cout << "1. Search by name" << std::endl;
    std::cout << "2. Search by workshops" << std::endl;
    std::cout << "3. Search by ID" << std::endl;
    std::cout << "0. Cancel" << std::endl;
}
void printGraphMenu() {
    std::cout << "1. Add edge" << std::endl;
    std::cout << "2. View edges"<< std::endl;
    std::cout << "3. Delete edge" << std::endl;
    std::cout << "4. Clear graph" << std::endl;
    std::cout << "5. Topological sort" << std::endl;
    std::cout << "0. Cancel" << std::endl;
}

std::unordered_set <Data::ID> Input_sequence() {
    std::unordered_set<Data::ID> ids;
    std::string input;
    while (true) {
        std::cin >> std::ws;
        std::cin >> input;
        if (input == "end") {
            break;
        }
        std::istringstream ss(input);
        int new_item;
        ss >> new_item;
        if (ss)
            ids.insert(new_item);
    }
    return ids;
}

void add_pipe(Data& data) {
    Pipe pipe;
    pipe.input_pipe();
    int id = data.add_pipe(pipe);
    std::cout << "\nAdd pipe with ID = " << id - 1 << std::endl;
}

void delete_pipes(Data& data, std::vector<Data::ID>& found_pipes) {
    for (auto id : found_pipes) {
        data.delete_pipe(id);
    }
}

void delete_stations(Data& data, std::vector<Data::ID>& found_stations) {
    for (auto id : found_stations) {
        data.delete_station(id);
    }
}

void add_station(Data& data) {
    CompressorStation station;
    station.input_station();
    int id = data.add_station(station);
    std::cout << "\nAdd station with ID = " << id - 1 << std::endl;
}

void view_all_data(Data& data) {
    if (!data.getPipes().empty() || !data.getStations().empty()) {
        data.print(std::cout, true);
    }
    else {
        std::cout << "Data is empty." << std::endl;
    }
}

void search_pipes_by_status(Data& data, std::vector<Data::ID>& found_pipes) {
    bool status;
    std::cout << "Enter status (1 - work , 0 - in repair): ";
    status = validity_enter_interactive<bool>(0, 1);
    found_pipes = Search::search_by_filter<Pipe>(
        data,
        [status](const Pipe& pipe)
        {return pipe.getStatus() == status; });
}
void search_pipes_by_name(Data& data, std::vector<Data::ID>& found_pipes) {
    std::string name;
    std::cout << "Enter name: ";
    std::cin.ignore(100, '\n');
    std::getline(std::cin, name);
    found_pipes = Search::search_by_filter<Pipe>(data,
        [&name](const Pipe& pipe) {return (pipe.getName().find(name) != std::string::npos); }
    );
}
void search_pipes_by_id(Data& data, std::vector<Data::ID>& found_pipes) {
    std::cout << "Enter ids (ending with 'end' with space): ";
    std::unordered_set<Data::ID> ids = Input_sequence();
    found_pipes = Search::search_by_id<Pipe>(data, ids);
}
void search_stations_by_name(Data& data, std::vector<Data::ID>& found_stations) {
    std::string name;
    std::cout << "Enter name: ";
    std::cin.ignore(1000, '\n');
    std::getline(std::cin, name);
    found_stations = Search::search_by_filter<CompressorStation>(data,
        [&name](const CompressorStation& station)
        {return (station.getName().find(name) != std::string::npos); });
}
void search_stations_by_percent(Data& data, std::vector<Data::ID>& found_stations) {
    float low, high;
    std::cout << "Enter low percent: ";
    low = validity_enter_interactive<float>(0.0, 100.0);
    std::cout << "Enter high percent: ";
    high = validity_enter_interactive<float>(low, 100.0);
    found_stations = Search::search_by_filter<CompressorStation>(
        data,
        [low, high](const CompressorStation& station) {
            float percent = station.getWorkshopsInUse() * 100 / station.getWorkshops();
            return (percent >= low && percent <= high);
        });
}

void search_stations_by_id(Data& data, std::vector<Data::ID>& found_stations) {
    std::cout << "Enter ids (ending with 'end' with space): ";
    std::unordered_set<Data::ID> ids = Input_sequence();
    found_stations = Search::search_by_id<CompressorStation>(data, ids);
}

void edit_pipes(Data& data, std::vector<Data::ID>& found_pipes) {
    std::cout << "Enter new status for pipes (1 - work, 0 - in repair): ";
    bool status = validity_enter_interactive(0, 1);
    for (Data::ID id : found_pipes) {
        get_by_id_from_map(id, data.getPipes()).setStatus(status);
    }
}

void edit_stations(Data& data, std::vector<Data::ID>& found_stations) {
    std::cout << "Enter percent of use workshops: ";
    float percent = validity_enter_interactive<float>(0.0, 100.0);
    for (Data::ID id : found_stations) {
        CompressorStation& station = get_by_id_from_map(id, data.getStations());
        int workshops_in_use = (int)(station.getWorkshops() * percent / 100);
        station.setWorkshopsInUse(workshops_in_use);
    }
}

bool find_id_in_array(int id, std::vector<Data::ID>& array) {
    for (int i : array) {
        if (i == id) {
            return true;
        }
    }
    return false;
}

std::vector<Data::ID> search_pipe_by_diameter(Data& data,int diameter) {
    std::vector<Data::ID> ids_pipes = Search::search_by_filter<Pipe>(data,
        [diameter](const Pipe& pipe)
        {return pipe.getDiameter() == diameter; });
    return ids_pipes;
}

void add_pipe_without_diameter(Data& data, int diameter) {
    Pipe pipe;
    pipe.input_pipe_without_diameter(diameter);
    data.add_pipe(pipe);
}

void add_edge(Data& data) {
    if (data.getStations().empty()) {
        std::cout << "There are no stations" << std::endl;
        return;
    }
    std::cout << "Enter station source: ";
    int source = validity_enter_interactive(0, data.getNextStationId()-1);

    std::cout << "Enter station drain: ";
    int drain = validity_enter_interactive(0, data.getNextStationId()-1);
    if (source == drain) {
        std::cout << "Source should be != drain" << std::endl;
        return;
    }
    if (!data.getStations().contains(source) || !data.getStations().contains(drain)) {
        std::cout << "There are no stations with this ids" << std::endl;
        return;
    }

    std::cout << "Enter diameter of pipe: ";
    int diameter = 0;
    std::cin >> diameter;
    while (diameter != 500 && diameter != 700 && diameter != 1000 && diameter != 1400) {
        std::cin.ignore(1000, '\n');
        std::cout << "Diameter should be 500, 700, 1000 or 1400" << std::endl;
        std::cin >> diameter;
    }
    auto ids_pipes = search_pipe_by_diameter(data, diameter);
    std::vector<Data::ID> free_pipes = data.get_free_pipes(ids_pipes);
    if (free_pipes.empty()) {
        std::cout << "Do you want add new pipe?(Y or N) " << std::endl;

        std::string s = "";
        std::cin >> s;
        while (s != "Y" && s != "N") {
            std::cout << "The answer should be Y or N" << std::endl;
            std::cin >> s;
        }
        if (s == "Y") {
            add_pipe_without_diameter(data, diameter);
            ids_pipes = search_pipe_by_diameter(data, diameter);
            free_pipes = data.get_free_pipes(ids_pipes);
        }
        else {
            return;
        }
    }
    std::cout << "Found pipes with diameter = " << diameter << "\n" << std::endl;
    print_from_map_by_ids(free_pipes, data.getPipes());
    
    std::cout << "\nEnter id pipe: ";
    int id = -1;
    bool status = false;
    while (!status) {
        std::cout << "The id number must be from the list" << std::endl;
        id = validity_enter_interactive(0, data.getNextPipeId()-1);
        status = find_id_in_array(id, free_pipes);
    }
        
    data.add_edge(id, source, drain);

    std::cout << "Edge is added" << std::endl;
}

void view_edges(Data& data) {
    data.view_edges();
}

void delete_edge(Data& data) {
    std::cout << "Enter edge id: ";
    int id = validity_enter_interactive<int>(0, data.getAll<Pipe>().size());
    data.delete_edge(id);
}

std::string enter_filename() {
    std::string file_name;
    std::cout << "Enter file name (filename.txt): ";
    std::cin.ignore(100, '\n');
    std::getline(std::cin, file_name);
    return file_name;
}

void save_to_file(Data& data) {
    if (!data.getPipes().empty() || !data.getStations().empty()) {
        std::ofstream file(enter_filename());
        if (!file) {
            std::cout << "Error, can't open file" << std::endl;
            return;
        }
        data.save(file, false);
        std::cout << "Saving successfully\n" << std::endl;
    }
    else {
        std::cout << "Data is empty." << std::endl;
        return;
    }
}
void load_from_file(Data& data) {
    std::ifstream file(enter_filename());
    if (!file) {
        std::cout << "Error, can't open file" << std::endl;
        return;
    }
    data.load_data(file);
    std::cout << "Loading successfully\n" << std::endl;
}

void workWithSearchPipeMenu(Data& data) {
    if (!data.getPipes().empty()) {
        std::vector<Data::ID> found_pipes;

        printSearchPipe();
        std::cout << "\n>";
        int option = validity_enter_interactive(0, 3);
        switch (option) {
        case 1:
            search_pipes_by_name(data, found_pipes);
            break;
        case 2:
            search_pipes_by_status(data, found_pipes);
            break;
        case 3:
            search_pipes_by_id(data, found_pipes);
            break;
        case 0:
            return;
        }

        std::cout << "\nFound: " << found_pipes.size() << " pipes.\n" << std::endl;

        if (found_pipes.size() != 0) {
            do {
                printSearchPipesMenu();
                std::cout << "\n>";
                option = validity_enter_interactive(0, 3);
                switch (option) {
                case 1:
                    print_from_map_by_ids(found_pipes, data.getPipes());
                    break;
                case 2:
                    delete_pipes(data, found_pipes);
                    return;
                case 3:
                    edit_pipes(data, found_pipes);
                    break;
                case 0:
                    return;
                }
            } while (option != 0);
        }
    }
    else {
        std::cout << "Data is empty." << std::endl;
        return;
    }
}

void workWithSearchStationMenu(Data& data) {
    if (!data.getStations().empty()) {
        std::vector<Data::ID> found_stations;

        printSearchStation();
        std::cout << "\n>";
        int option = validity_enter_interactive(0, 3);
        switch (option) {
        case 1:
            search_stations_by_name(data,found_stations);
            break;
        case 2:
            search_stations_by_percent(data, found_stations);
            break;
        case 3:
            search_stations_by_id(data, found_stations);
            break;
        case 0:
            return;
        }

        std::cout << "\nFound: " << found_stations.size() << " stations.\n" << std::endl;

        if (found_stations.size() != 0) {
            do {
                printSearchStationsMenu();
                std::cout << "\n>";
                option = validity_enter_interactive(0, 3);
                switch (option) {
                case 1:
                    print_from_map_by_ids(found_stations, data.getStations());
                    break;
                case 2:
                    delete_stations(data, found_stations);
                    return;
                case 3:
                    edit_stations(data, found_stations);
                    break;
                case 0:
                    return;
                }

            } while (option != 0);
        }
    }
    else {
        std::cout << "Data is empty." << std::endl;
        return;
    }
}

void workWithGraphMenu(Data& data) {
    int option = 0;
    do {
        printGraphMenu();
        option = validity_enter_interactive(0, 5);
        switch (option){
        case 1:
            add_edge(data);
            break;
        case 2:
            view_edges(data);
            break;
        case 3:
            delete_edge(data);
            break;
        case 4: {
            data.getEdges().clear();
            std::cout << "Graph is clear" << std::endl;
            break;
        }
        case 5: {
            Graph graph(data);
            std::vector<int> result = graph.topologicalSort();
            for (int i = 0; i < result.size(); i++) {
                std::cout << result[i] << " ";
            }
            std::cout << std::endl;
        }
        default:
            break;
        }
    } while (option != 0);
}

void work_with_main_menu() {
    Data data;
    int option = 0;
    Data::ID id = 0;
    do {
        printMainMenu();
        std::cout << "\n>";
        option = validity_enter_interactive(0, 8);
        switch (option)
        {
        case 1:  
            add_pipe(data);
            
            break;
        case 2: 
            add_station(data);
            break;
        case 3: 
            view_all_data(data);
            break;
        case 4:
            workWithSearchPipeMenu(data);
            break;
        case 5:      
            workWithSearchStationMenu(data);
            break;
        case 6: {
            workWithGraphMenu(data);
            break;
        }
        case 7:    
            save_to_file(data);
            break;
        case 8:
            load_from_file(data);
            break;
        case 0:
            return;
        default:
            std::cout << "Error, option number should be from 0 to 7" << std::endl;
            break;
        }
    } while (option != 0);
}


