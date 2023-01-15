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


vector<int> whichCoursesDontHaveParents(vector<int>& v, vector<vector<bool> >adjmat){

    for(int cols =0; cols < adjmat.size();++cols){
       int gothrurows=0;
       while(gothrurows<adjmat.size()-1 && adjmat.at(gothrurows).at(cols)==0){
            ++gothrurows;
       }
       if(adjmat.at(gothrurows).at(cols)){
            gothrurows=0;
       }else if(gothrurows>=v.size() && adjmat.at(gothrurows).at(cols)==0){
            v.push_back(cols);
       }
    }


    return v;

}



int rs(string course, vector<string> courses, vector<vector<bool> > adj_matrix){

  int col=0;
  int numRow=(look_for(courses, course));

  while(col<adj_matrix.size()-1 && adj_matrix.at(numRow).at(col)==0){
        if(col >= adj_matrix.size()-1 && adj_matrix.at(numRow).at(adj_matrix.size()) == 0){
            return 0;
        }
        ++col;
  }
  
    vector<int> longestFound;

    for(int i = 0; i < adj_matrix.size(); ++i){
    if(adj_matrix.at(look_for(courses, course)).at(i)==1){
        longestFound.push_back(1+rs(courses.at(i),courses,adj_matrix));
    }
    }

    int largest=-1;

    for(int i = 0; i < longestFound.size(); ++i){
    if(longestFound.at(i)>largest){
        largest = longestFound.at(i); 
    }
    }

    return largest;

} 
int longestPath(string course,vector<string> courses, vector<vector<bool> > adj_matrix){
    
return rs(course, courses,adj_matrix);

}





int main(){
    // create list of classes with names

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

    print(adj_matrix);

    adj_matrix = fill(adj_matrix, classes, pathToData);
    cout << endl;

    print(adj_matrix);

    vector<int> theOnesWithoutParents;

    theOnesWithoutParents=whichCoursesDontHaveParents(theOnesWithoutParents,adj_matrix);
    
    // for(int i =0; i < theOnesWithoutParents.size();++i){
    //     cout << classes.at(theOnesWithoutParents.at(i));
    //     cout << longestPath(classes.at(theOnesWithoutParents.at(i)), classes, adj_matrix);
    //     cout<<endl;
    // }

    vector<pair<string, int> > longest; 
    

    for(int i =0; i < theOnesWithoutParents.size();++i){
        pair<string, int> temp;
        temp.first = classes.at(theOnesWithoutParents.at(i));
        temp.second = longestPath(classes.at(theOnesWithoutParents.at(i)), classes, adj_matrix);
        
        longest.push_back(temp);

    }

    for(int i =0; i < longest.size();++i){
        cout << longest.at(i).first<< " ";
        cout << longest.at(i).second;
        cout<<endl;
    }


    
    
    



}//end main 




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
