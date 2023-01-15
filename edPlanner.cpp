#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct node{
    string data;
    node* next;
    bool locked;
};


vector<string> unique_classes(string file_name);
int look_for(vector<string> classes, string goal);
void print(vector<vector<bool> > adj_matrix);
vector<vector<bool> > fill(vector<vector<bool> > adj_matrix, vector<string> classes, string file_name);

int main(){
    cout << "Rosa de guadlupe is winning!" << endl;

    //1->2

    // create list of classes with names
    // go through file and check if class already exists in the list
    //
    // step 1: make matrix
    // step 2: define edges
    // step 3: succeed
    //
    //

    //template for other machines.
    //vector<string> classes = unique_classes("classes.txt");

    //unique to machine 

    string pathToData = "/Users/luisurena/Downloads/rose-2/classes.txt";


    vector<string> classes = unique_classes(pathToData);

    int size = classes.size();

    cout << endl;
    cout << "PRINTING CLASSES" << endl;

    for(int i = 0; i < size; i++){
        cout << classes.at(i) << endl;
    }

    //cout << "cs3: " << look_for(classes, "cs3") << endl;


    //create adj matrix
    vector<vector<bool> > adj_matrix;
    for(unsigned int i = 0; i < classes.size(); i++){
        vector<bool> temp;
        for(unsigned int j = 0; j < classes.size(); j++){
            temp.push_back(false);
        }
        adj_matrix.push_back(temp);
    }


    //print adj matrix
    cout << endl;
    cout << "PRINTING ADJ MATRIX" << endl;
    cout << "size: " << adj_matrix.size() << endl;

    print(adj_matrix);

    adj_matrix = fill(adj_matrix, classes, pathToData);

    cout << endl;
    cout << "FILLING OUT ADJ MATRIX" << endl;
    cout << "size: " << adj_matrix.size() << endl;

    print(adj_matrix);
}

int look_for(vector<string> classes, string goal){
    for(unsigned int i = 0; i < classes.size(); i++){
        if(classes.at(i) == goal){
            return i;
        }
    }

    return -1;
}

vector<string> unique_classes(string file_name){

    vector<string> classes;

    fstream fin;
    fin.open(file_name);

    if(!fin.is_open()){
        cout << "file not opened" << endl;
    }
    int size = 0;
    bool contains = false;

    string temp;

    while(fin >> temp){

        string pre = temp.substr(0, temp.find(','));
        string cls = temp.substr(temp.find(',') + 1, temp.size());

        for(unsigned int i = 0; i < classes.size(); i++){
            if(classes.at(i) == pre){
                contains = true;
            }
        }
        if(!contains){
            classes.push_back(pre);
        }
        contains = false;


        for(unsigned int i = 0; i < classes.size(); i++){
            if(classes.at(i) == cls){
                contains = true;
            }
        }
        if(!contains){
            classes.push_back(cls);
        }
        contains = false;
    }

    return classes;
}


void print(vector<vector<bool> > adj_matrix){
    for(unsigned int i = 0; i < adj_matrix.size(); i++){

        cout << "[";
        
        for(unsigned int j = 0; j < adj_matrix.at(i).size() - 1; j++){
            cout << adj_matrix.at(i).at(j) << ",";
        }
        cout << adj_matrix.at(i).at(adj_matrix.size() -1) << "]";
        cout << endl;
    }
}
vector<vector<bool> > fill(vector<vector<bool> > adj_matrix, vector<string> classes, string file_name){
    fstream fin;
    fin.open(file_name);
    string temp;


    while(fin >> temp){
        string pre = temp.substr(0, temp.find(','));
        string cls = temp.substr(temp.find(',') + 1, temp.size());
        int x = look_for(classes, cls);
        int y = look_for(classes, pre);

        adj_matrix.at(y).at(x) = 1;
    }


    return adj_matrix;
}
